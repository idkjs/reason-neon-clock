/* check if the speechSynthesis api is available on the global window object, if not don;t try to speak */
@val external window: _ = "window"
let isSpeech = Js.typeof(window) != "speechSynthesis"
Js.log2("isSpeech: ",isSpeech)
Js.log2("window: ",window)
module Speaker = {
  @react.component
  let make = (~active, ~text, ~isSpeech=isSpeech) => {
    /* A `ComponentDidUpdate` via `React.useEffect1`.We check the passed in props to see what we should do, then do it. */
    React.useEffect1(() => {
      switch (active, isSpeech) {
      | (true, true) => Speech.speak(text, _ => ())
      | (_, _) => ()
      }

      None
    }, [active, isSpeech]) // Here we are listing dependency on which component will be re-rendered.
    <div />
  }
}

module TimeReadout = {
  @react.component
  let make = (~time) => {
    /* Get the passed in `time` props and transform it with our utility function so we can use it to get calculations. Working with `Js.Date.t` is a mess! */
    let (seconds, minutes, _hours) = Utils.globalTime(~time)
    /* If this calculation is true, then its a time that we want the program to speak to us out loud. If its false, do not announce the time. We pass this to the `Speaker` module below which deals with it in */
    let shouldSpeak = seconds === 0 && mod(minutes, 15) === 0
    let display = time->Js.Date.fromFloat->Js.Date.toLocaleString
    let (sentence, _timeText, highlighted) = Config.timeReadout(~time)
    let highlight = {
      open Belt
      highlighted->Array.mapWithIndex((idx, h) =>
        h
          ? <span key={string_of_int(idx)} className="glow">
              {Utils.phrases->Array.get(idx)->Option.getWithDefault("")
                |> React.string}
            </span>
          : <span key={string_of_int(idx)}>
              {Utils.phrases->Array.get(idx)->Option.getWithDefault("")
                |> React.string}
            </span>
      )
    }
    <div className="readout">
      <p className="phrases"> {highlight->React.array} </p>
      <p className="timer"> {display->React.string} </p>
      <Button
        label=sentence onClick={_event => Speech.speak(sentence, _ => ())}
      />
      <Speaker active=shouldSpeak text=sentence />
    </div>
  }
}
module UseClock = {
  type state = {
    count: int,
    timerId: option<Js.Global.intervalId>,
  }

  type action =
    | IncreaseCount
    | SetTimerId(Js.Global.intervalId)

  let useClock = () => {
    let (state, dispatch) = React.useReducer((state, action) =>
      switch action {
      | IncreaseCount => {...state, count: state.count + 1}
      | SetTimerId(timerId) => {...state, timerId: Some(timerId)}
      }
    , {count: 0, timerId: None})
    React.useEffect1(() => {
      let timerId = Js.Global.setInterval(() => dispatch(IncreaseCount), 1000)
      Some(() => Js.Global.clearInterval(timerId))
    }, [state.timerId])
    /* Return Js.Date.now on every tick */
    // Js.Date.now();
    GlobalTime.time()
  }
}

@react.component
let make = (~time) =>
  <div className="clock"> <StandardClock time /> <TimeReadout time /> </div>

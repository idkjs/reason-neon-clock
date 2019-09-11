external castToUtterance: 'a => SpeechSynthesis.Utterance.t = "%identity";
[@bs.val] external window: _ = "window";
let isSpeech = Js.typeof(window) != "speechSynthesis";

module Speaker = {
  [@react.component]
  let make = (~active, ~text, ~isSpeech=isSpeech) => {
    Js.log4("isSpeech", isSpeech, "active", active);
    React.useEffect1(
      () => {
        switch (active, isSpeech) {
        | (true, true) => Speech.speak(text, _ => ())
        | (_, _) => ()
        };

        None;
      },
      [|active, isSpeech|] // Here we are listing dependency on which component will be re-rendered.
    );
    <div />;
  };
};

module TimeReadout = {
  [@react.component]
  let make = () => {
    let (_, minute, second, display) = Time.getNow();
    let second = second->int_of_float;
    let minute = minute->int_of_float;

    let shouldSpeak = second === 0 && minute mod 15 === 0;
    Js.log2(" shouldSpeak ", shouldSpeak);
    // let shouldSpeak = true;
    let (sentence, _timeText, highlighted) = Time.timeReadout;
    let highlight =
      Belt.(
        Phrases.(
          highlighted->Array.mapWithIndex((idx, h) =>
            h
              ? <span key={string_of_int(idx)} className="glow">
                  {phrases->Array.get(idx)->Option.getWithDefault("")
                   |> React.string}
                </span>
              : <span key={string_of_int(idx)}>
                  {phrases->Array.get(idx)->Option.getWithDefault("")
                   |> React.string}
                </span>
          )
        )
      );
    <div className="readout">
      <p className="phrases"> highlight->React.array </p>
      <p className="timer"> display->React.string </p>
      <Speaker active=shouldSpeak text=sentence />
      <Button
        label="Time now?"
        onClick={_event => Speech.speak(sentence, _ => ())}
      />
    </div>;

  };
};

let useClock = () => {
  let (timer, setTimer) = React.useState(() => None);
  let (time, setTime) = React.useState(() => Js.Date.now());
  let timeLeft = () => {
    let now = Js.Date.now();
    let nextSec = (Js.Math.floor(now /. 1000.) + 1) * 1000;
    let timeLeft = nextSec - now->int_of_float;
    timeLeft->float_of_int;
  };

  React.useEffect1(
    () => {
      let timer =
        switch (timer) {
        | Some(timer) => timer
        | None =>
          let timer =
            Js.Global.setInterval(() => setTime(_ => Js.Date.now()), 1000);
          setTime(_ => timeLeft());
          setTimer(_ => Some(timer));
          timer;
        };
      Some(
        () => {
          Js.Global.clearInterval(timer);
        },
      );
    },
    [|timer|],
  );
  time;
};

[@react.component]
let make = () => {
  let time = useClock();
  React.useEffect(() => {
    Js.log2("Hey!", time);
    None;
  });
  let time = Js.Float.toString(time);
  <div className="clock">
    <StandardClock />
    <TimeReadout />
    <p className="timer"> time->React.string </p>
  </div>;
};
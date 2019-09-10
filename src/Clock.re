external castToUtterance: 'a => SpeechSynthesis.Utterance.t = "%identity";

module Speaker = {
  [@react.component]
  let make = (~active, ~text) => {
    React.useEffect1(
      () => {
        if (active) {
          Speech.speak(text, _
            => ());
            // SpeechSynthesis.speak(text);
        };
        None;
      },
      [|active|] // Here we are listing dependency on which component will be re-rendered.
    );
    // <> <p className="timer"> "display"->React.string </p> </>;
    <div />;
  };
};

module Button = {
  [@react.component]
  let make = (~label, ~onClick) => {
    <button onClick> {label |> ReasonReact.string} </button>;
  };
};

module TimeReadout = {
  [@react.component]
  let make = () => {
    let (_, minute, second, display) = Config.getNow();
    let second = second->int_of_float;
    let minute = minute->int_of_float;

    let shouldSpeak = second === 0 && minute mod 15 === 0;
    Js.log2(" shouldSpeak ", shouldSpeak);
    // let shouldSpeak = true;
    let (sentence, timeText, highlighted) = Time.timeReadout2;
    let highlight =
      Belt.(
        Phrases.(
          highlighted->Array.mapWithIndex((idx, h) =>
            h
              ? <span className="glow"> {phrases->Array.get(idx)->Option.getWithDefault("")|>React.string} </span>
              : <span> {phrases->Array.get(idx)->Option.getWithDefault("")|>React.string} </span>
          )
        )
      );
    <div className="readout">
      <p className="phrases"> highlight->React.array </p>
      <p className="timer"> display->React.string </p>
      <Speaker active=shouldSpeak text=sentence />
      <Button
        label="Speech:"
        onClick={_event => Speech.speak(sentence, _ => ())}
      />
      <Button
        label="SpeechSynthesis"
        onClick={_event => SpeechSynthesis.speak(sentence->castToUtterance)}
      />
    </div>;
  };
};

[@react.component]
let make = () => {
  <div className="clock">
    // <StandardClock time={time} />
     <TimeReadout /> </div>;
};
external castToUtterance: 'a => SpeechSynthesis.Utterance.t = "%identity";

// [%bs.raw {|require('./index.css')|}];
// [%bs.raw {|require('./less/index.less')|}];
let (hour, minute, second, display) = Config.getNow();
Js.log2("getNow", Config.getNow());
Js.log2("getNow", display);
let (
  isExact,
  isAbout,
  isNearly,
  minute,
  isOClock,
  isPast,
  isTo,
  hour,
  isNoon,
  isMidnight,
  isMorning,
  isAfternoon,
  isEvening,
) =
  Config.getReadoutConfig(hour, minute);

module Button = {
  [@react.component]
  let make = (~label, ~onClick) => {
    <button onClick> {label |> ReasonReact.string} </button>;
  };
};

[@react.component]
let make = () => {
  let (hour, minute, second, display)=Config.getNow();
  let second = second->int_of_float
  let minute = minute->int_of_float
  // let readoutConfig = Config.getReadoutConfig(time);
  // let highlighted = getHighlights(readoutConfig);
  // let timeText = phrases->Belt.Array.mapWithIndex(phrase, index) => highlighted[index]).join(' ') + '.';
  let timeText = "NEARLY"->castToUtterance;
    let timeText2 = "NEARLY";
  let shouldSpeak = second === 0 && minute mod 15 === 0;
  let shouldSpeak = true;

  <div className="readout">
    <Button
      label="START"
      onClick={_event => SpeechSynthesis.speak(timeText)}
    />
        <p className="timer"> display->React.string </p>
    <Button
      label="Speech"
      onClick={_event => Speech.speak(timeText2, _ => ())}
    />
    <Button
      label="SpeechSynthesis"
      onClick={_event => SpeechSynthesis.speak(timeText->castToUtterance)}
    />
  </div>;
};

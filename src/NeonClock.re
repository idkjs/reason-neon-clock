external castToUtterance: 'a => SpeechSynthesis.Utterance.t = "%identity";
let phrases = [|
  "IT IS",
  "ABOUT",
  "NEARLY",
  "TEN",
  "QUARTER",
  "TWENTY",
  "FIVE",
  "HALF",
  "PAST",
  "TO",
  "ONE",
  "TWO",
  "THREE",
  "FOUR",
  "FIVE",
  "SIX",
  "SEVEN",
  "EIGHT",
  "NINE",
  "TEN",
  "ELEVEN",
  "NOON",
  "MIDNIGHT",
  // "O\" CLOCK",
  "IN THE",
  "MORNING",
  "AFTERNOON",
  "EVENING",
|];

let getNow = () => {
  let now: Js.Date.t = Js.Date.now()->Js.Date.fromFloat;
  let hour = Js.Date.getHours(now);
  let minute = now |> Js.Date.getMinutes;
  let second = now |> Js.Date.getSeconds;
  let display = now |> Js.Date.toLocaleString;

  (hour, minute, second, display);
};
let (hour, minute, second, display) = getNow();
getNow()->Js.log;
Js.log2(" hour", hour);
// let getNow2 = {
//   let now: Js.Date.t = Js.Date.now()->Js.Date.fromFloat;
//   let hour = Js.Date.getHours(now);
//   let minute = now |> Js.Date.getMinutes;
//   let second = now |> Js.Date.getSeconds;
//   let display = now |> Js.Date.toLocaleString;

//   (hour, minute, second, display);
//   // [hour, minute, second, display];
// };
// getNow2->Js.log;
// let (hour, minute, second, display) = getNow2;
// Js.log2(" hour2", hour );
let getReadoutConfig = (hour, minute) => {
  let lastMinuteMark = Js.Math.floor(minute /. 5.) * 5;
  let hour = int_of_float(hour);
  let minute = int_of_float(minute);
  let distFromLast = minute - lastMinuteMark;
  let isExact = distFromLast === 0;
  let isNearly = !isExact && distFromLast > 2;
  let isAbout = !isExact && !isNearly;
  let nearestMinuteMark =
    isNearly ? (lastMinuteMark + 5) mod 60 : lastMinuteMark;
  let isOClock = nearestMinuteMark === 0;
  let isPast = !isOClock && nearestMinuteMark <= 30;
  let isTo = !isOClock && !isPast;
  // let minuteMark =
  //   isPast || isOClock ? nearestMinuteMark : 60 - nearestMinuteMark;
  let minuteMark =
    switch (isPast, isOClock) {
    | (true, true) => nearestMinuteMark
    | (_, _) => 60 - nearestMinuteMark
    };
  let nearestHour = isTo || isOClock && isNearly ? (hour + 1) mod 24 : hour;
  let nearestHour12 = nearestHour > 12 ? nearestHour - 12 : nearestHour;
  let isNoon = nearestHour === 12;
  let isMidnight = nearestHour === 0;
  let isMorning = !isMidnight && nearestHour < 12;
  let isAfternoon = nearestHour > 12 && nearestHour <= 18;
  let isEvening = nearestHour > 18;
  let isIsOClock =
    switch (isOClock, !isNoon, !isMidnight) {
    | (true, true, true) => true
    | (_, _, _) => false
    };
  let minute = minuteMark;
  let isOClock = isIsOClock;
  let hour = nearestHour12;
  (
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
  );
};
getReadoutConfig(hour, minute)->Js.log;
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
  getReadoutConfig(hour, minute);

// let getHighlights (config) {
//    [
//     true, // IT IS
//     config.isAbout, // ABOUT
//     config.isNearly, // NEARLY
//     config.minute === 10, // TEN
//     config.minute === 15, // QUARTER
//     config.minute === 20 || config.minute === 25, // TWENTY
//     config.minute === 5 || config.minute === 25, // FIVE
//     config.minute === 30, // HALF
//     config.isPast, // PAST
//     config.isTo, // TO
//     config.hour === 1, // ONE
//     config.hour === 2, // TWO
//     config.hour === 3, // THREE
//     config.hour === 4, // FOUR
//     config.hour === 5, // FIVE
//     config.hour === 6, // SIX
//     config.hour === 7, // SEVEN
//     config.hour === 8, // EIGHT
//     config.hour === 9, // NINE
//     config.hour === 10, // TEN
//     config.hour === 11, // ELEVEN
//     config.isNoon, // NOON
//     config.isMidnight, // MIDNIGHT
//     config.isOClock, // O' CLOCK
//     config.isMorning || config.isAfternoon || config.isEvening, // IN THE
//     config.isMorning, // MORNING
//     config.isAfternoon, // AFTERNOON
//     config.isEvening, // EVENING
//   ];
// };

// open SpeechSynthesis.Utterance;
let speak = text => {
  let synth = SpeechSynthesis.Utterance.create("synth");
  let rate: float = 0.7;
  let pitch: float = 0.6;
  // let voice = SpeechSynthesis.getVoices();
  let voices = SpeechSynthesis.x;
  // let voices = SpeechSynthesis.getVoices();
  let getVoice = arr => arr->Belt.Array.keep(voice => voice##lang == "en-GB");
  let voice = getVoice(voices)->castToUtterance;
  let utterance = SpeechSynthesis.Utterance.set_text(text);
  let voice = SpeechSynthesis.Utterance.set_voice(voice);
  let pitch = SpeechSynthesis.Utterance.set_pitch(pitch->castToUtterance);
  let rate = SpeechSynthesis.Utterance.set_rate(rate->castToUtterance);
  let speak = SpeechSynthesis.speak(text);
  // utterance;voice; pitch;rate; speak;
  (utterance, voice, pitch, rate, speak);
  // synth.speak(utterance)
};

// module StandardClock = {
//   [@react.component]
//   let make = (~time) => {

// let clockMarks = [| "XII", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI" |];
// let hourAngle = ((time.hour % 12) * 60 + time.minute) / 2;
// let minuteAngle = (time.minute * 60 + time.second) / 10;
// let secondAngle = time.second * 6;

//     <div className=standard-clock>
//       <div>
//         { clockMarks.map(mark => <span className=mark>{mark}</span>) }
//       </div>
//       <div>
//         { Array(60).fill(1).map(tick => <span className=tick />) }
//       </div>
//       <div className=inner-circle />
//       <div className=inner-circle-2 />
//       <div className=hour-hand style={{ transform: `rotate(${hourAngle}deg)` }} />
//       <div className=minute-hand style={{ transform: `rotate(${minuteAngle}deg)` }} />
//       <div className=second-hand style={{ transform: `rotate(${secondAngle}deg)` }} />
//       <div className=center />
//     </div>;
//       };
//   };
// };

// let Speaker ({ active, text }) {
//   if (!window.speechSynthesis) return null;
//   React.useEffect (() => {
//     if (active) speak(text);
//   });
//   return null;
// };

// module TimeReadout = {
//   [@react.component]
//   let make = () => {
//     let readoutConfig = getReadoutConfig(time);
// let highlighted = getHighlights(readoutConfig);
// let timeText = phrases.filter((phrase, index) => highlighted[index]).join(' ') + '.';
// let shouldSpeak = time.second === 0 && time.minute % 15 === 0;
//   };
// let readoutConfig = getReadoutConfig(time);
// let highlighted = getHighlights(readoutConfig);
// let timeText = phrases.filter((phrase, index) => highlighted[index]).join(' ') + '.';
// let shouldSpeak = time.second === 0 && time.minute % 15 === 0;
// <div className="readout">
//       <p className="phrases">
//         { phrases.map((phrase, index) => (
//           <span className={highlighted[index] ? "glow" : "}>
//             {phrase}
//           </span>
//         ))}
//       </p>
//       <p className='timer'>{time.display}</p>
//       <Speaker active={shouldSpeak} text={timeText} />
//     </div>;
// };
// [@react.component]
// let make = () => {
// let time = useClock();

//     <div className='clock'>
//       <StandardClock time={time} />
//       <TimeReadout time={time} />
//     </div>;
// };
// [@react.component]
// let make = () => <div className="clock"> "Testing"->React.string </div>;

[@react.component]
let make = () => {
  <div className="clock"> {React.string("message")} </div>;
};
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
  "OCLOCK",
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

// let (
//   isExact,
//   isAbout,
//   isNearly,
//   minute,
//   isOClock,
//   isPast,
//   isTo,
//   hour,
//   isNoon,
//   isMidnight,
//   isMorning,
//   isAfternoon,
//   isEvening,
// ) =
//   getReadoutConfig(hour, minute);
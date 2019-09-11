
module type Now = {let now: float;};

module TimeConfig = (N: Now) => {
  let now = N.now->Js.Date.fromFloat;
  let hour = Js.Date.getHours(now);
  let minute = now |> Js.Date.getMinutes;
  let second = now |> Js.Date.getSeconds;
  let display = now |> Js.Date.toLocaleString;
};

module GetNow =
  TimeConfig({
    let now = Js.Date.now();
  });

let hour = GetNow.hour;
Js.log2(" hour ", hour);
let minute = GetNow.minute;
Js.log2(" minute ", minute);
let second = GetNow.second;
Js.log2(" second ", second);
let display = GetNow.display;
Js.log2(" display ", display);
let getNow = () => {
  let hour = GetNow.hour;
  let minute = GetNow.minute;
  let second = GetNow.second;
  let display = GetNow.display;

  (hour, minute, second, display);
};
let (hour, minute, second, display) = getNow();
// let getReadoutConfig = (~hour, ~minute) => {
let getReadoutConfig = () => {
  let itIs = true;
  let hour = GetNow.hour;
  let minute = GetNow.minute;
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
  let config: Types.readOutConfig = {
    itIs,
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
  };
  config;
};
let config = getReadoutConfig();

/* reads `config` and generates and array of values to be used. Feels redundant...
 */
let getHighlights = [|
  config.itIs, // IT IS
  config.isAbout, // ABOUT
  config.isNearly, // NEARLY
  config.minute === 10, // TEN
  config.minute === 15, // QUARTER
  config.minute === 20 || config.minute === 25, // TWENTY
  config.minute === 5 || config.minute === 25, // FIVE
  config.minute === 30, // HALF
  config.isPast, // PAST
  config.isTo, // TO
  config.hour === 1, // ONE
  config.hour === 2, // TWO
  config.hour === 3, // THREE
  config.hour === 4, // FOUR
  config.hour === 5, // FIVE
  config.hour === 6, // SIX
  config.hour === 7, // SEVEN
  config.hour === 8, // EIGHT
  config.hour === 9, // NINE
  config.hour === 10, // TEN
  config.hour === 11, // ELEVEN
  config.isNoon, // NOON
  config.isMidnight, // MIDNIGHT
  config.isOClock, // O' CLOCK
  config.isMorning || config.isAfternoon || config.isEvening, // IN THE
  config.isMorning, // MORNING
  config.isAfternoon, // AFTERNOON
  config.isEvening // EVENING
|];

// Js.log2(" getHighlights ", getHighlights);

// let timeReadout = () => {
//   let highlighted = getHighlights;
//   Js.log2("highlighted", highlighted);
//   Js.log2("phrases", Phrases.phrases);

//   let timeText =
//     Belt.(
//       Phrases.(
//         highlighted->Array.mapWithIndex((idx, h) =>
//           h ? phrases->Array.get(idx) : None
//         )
//       )
//     );

//   Js.log2(" timeText ", timeText);
// };
// timeReadout();
let timeReadout = {
  // let readOutConfig = config;
  let highlighted = getHighlights;
  Js.log2("highlighted", highlighted);
  Js.log2("phrases", Phrases.phrases);

  let cleanup = arr =>
    arr->Belt.Array.keepMap(x => x)->Js.Array.joinWith(" ", _);
  let timeText =
    Belt.(
      Phrases.(
        highlighted->Array.mapWithIndex((idx, h) =>
          h ? phrases->Array.get(idx) : None
        )
      )
    );
  let phrase = cleanup(timeText);
  Js.log2(" clean timeText ", timeText);

  Js.log2(" timeText ", timeText);

  (phrase, timeText, highlighted);
} /* timeReadout2->Js.log*/;
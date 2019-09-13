/* Takes in the `time` prop and configures our `readOutConfig` so that the program know which words to use when it is speaking. The returned `config` object is passed to `getHighlights` which will tell us which phrases should be highlighted in the ui. The Ui highlights which phrases make up the current time. */

type readOutConfig = {
  itIs:bool,
  hour: int,
  isExact:bool,
  isAbout: bool,
  isAfternoon: bool,
  isEvening: bool,
  isMidnight: bool,
  isMorning: bool,
  isNearly: bool,
  isNoon: bool,
  isOClock: bool,
  isPast: bool,
  isTo: bool,
  minute: int,
};
let getReadoutConfig = (~time) => {
  let (_seconds, minutes, hours) = Utils.globalTime(~time);

  let itIs = true;
  let lastMinuteMark = Js.Math.floor(minutes->float_of_int /. 5.) * 5;
  let distFromLast = minutes - lastMinuteMark;
  let isExact = distFromLast === 0;
  let isNearly = !isExact && distFromLast > 2;
  let isAbout = !isExact && !isNearly;
  let nearestMinuteMark =
    isNearly ? (lastMinuteMark + 5) mod 60 : lastMinuteMark;
  let isOClock = nearestMinuteMark === 0;
  let isPast = !isOClock && nearestMinuteMark <= 30;
  let isTo = !isOClock && !isPast;

  let minuteMark =
    switch (isPast, isOClock) {
    | (true, true) => nearestMinuteMark
    | (_, _) => 60 - nearestMinuteMark
    };
  let nearestHour = isTo || isOClock && isNearly ? (hours + 1) mod 24 : hours;
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
  let config: readOutConfig = {
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

/* reads `config` and generates and array of values to be used. Feels redundant...
 */
let getHighlights = (~config: readOutConfig) => [|
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

let timeReadout = (~time)=>{
  let config = getReadoutConfig(~time);
  let highlighted =  getHighlights(~config);

  let cleanup = arr =>
    arr->Belt.Array.keepMap(x => x)->Js.Array.joinWith(" ", _);
  let timeText =
    Belt.(
      highlighted->Array.mapWithIndex((idx, h) =>
        h ? Utils.phrases->Array.get(idx) : None
      )
    );
  let phrase = cleanup(timeText);

  (phrase, timeText, highlighted);
};
/** Identity function */
/* this is a helper function to transform our current time into the a format we can use in our other modules. We have to do this 2 or 3 times so better to do it once. */

let globalTime = (~time: float) => {
  let seconds = time->Js.Date.fromFloat->Js.Date.getSeconds;
  let seconds = seconds->int_of_float;
  let minutes = time->Js.Date.fromFloat->Js.Date.getMinutes;
  let minutes = minutes->int_of_float;
  let hours = time->Js.Date.fromFloat->Js.Date.getHours;
  let hours = hours->int_of_float;
  (seconds,minutes,hours);
};

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

open ReactFrp.React;
open ReactReact;

module NeonClock = {
  open NeonClockBase;
  [@react.component]
  let make = (~time) => {
      <div className="clock">
        <StandardClock time />
        <TimeReadout time />
    </div>;
  };
};
/* Generate the current time */
let counter = ref(0);
/* Generate the current time with `Js.Date.now()` and pass it as the initial value to our hook. This hook is creats a signal with the  `S` function from the `ReactFrp` library which can be found [here](https://erratique.ch/software/react). This library is some old, but still good reactive programming `OCaml` lib which still works great today.  */
let (timeS, timeF) = S.create(GlobalTime.time());
let timeIncrement = () => {
  /* increment the counter ref which is passed to timerId */
  counter := counter^ + 1;
  /* update the date and set it on `timeF` which is our updated variable by calling `GlobalTime.time` again */
  timeF(GlobalTime.time());
};

let timerId = Js.Global.setInterval(timeIncrement, 1000);
/* Create a variable to pass to our react component which takes in  */
let vdomS = _ =>
  S.map(
    ~eq=(_, _) => false,
    time =>
      /* On each iteration, pass the new time value to the entry point for our ui */
      <NeonClock time />,
      // <div>
    // </div>,
    timeS,
  );
/* create the component and call `componentFromSignal` passing in our `vdomS` signal variable */
[@react.component]
let make = () => componentFromSignal(vdomS, ());
module Button = {
  [@react.component]
  let make = (~label, ~onClick) => {
    <button onClick> {label |> ReasonReact.string} </button>;
  };
};

type state = {
  seconds: int,
  isTicking: bool,
  display: string,
};

type action =
  | Start
  | Stop
  | Reset
  | Tick;

let padNumber = numString =>
  if (numString |> int_of_string < 10) {
    "0" ++ numString;
  } else {
    numString;
  };

let formatTime = seconds => {
  let mins = seconds / 60;
  let minsString = mins |> string_of_int |> padNumber;
  let seconds = seconds mod 60;
  let secondsString = seconds |> string_of_int |> padNumber;
  minsString ++ ":" ++ secondsString;
};

let updateTitle: string => unit = [%bs.raw
  {|
  function updateTitle(remaining) {
    document.title = "⏰ " + remaining + " ⏰";
  }|}
];

let useTicker = () => {
  let (time, setTime) = React.useState(() => Time.display);

  let tick = () => {
    Js.log2("time", time );
    setTime(_ => Time.display);
  };
  React.useEffect(() => {
    let ticker = Js.Global.setInterval(() => tick(), 1000);
    Some(() => Js.Global.clearInterval(ticker));
  });

  time;
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Start => {...state, isTicking: true}
        | Stop => {...state, isTicking: false}
        | Reset => {...state, seconds: 30}
        | Tick =>
          state.isTicking && state.seconds > 0
            ? {
              updateTitle(formatTime(state.seconds - 1));
              {...state, seconds: state.seconds - 1};
            }
            : state
        },
      // The second argument to useReducer is the initial state of the reducer.
      {isTicking: false, seconds: Time.second->int_of_float, display: Time.display},
    );
  // let (_, minute, second, display) = Time.getNow();/

  // To update the timer every second, we need to create an effect.
  React.useEffect0(() => {
    let timerId = Js.Global.setInterval(() => dispatch(Tick), 1000);
    Some(() => Js.Global.clearInterval(timerId));
  });
let (test)= useTicker();
Js.log2("time test", test );
let now = Js.Date.now();
  let now = now->Js.Date.fromFloat;
  let minute = now |> Js.Date.getMinutes;
  // let seconds = minute->int_of_float mod 60;
  let display = now |> Js.Date.toLocaleString;

  <div
    style={ReactDOMRe.Style.make(
      ~border="1px solid black",
      ~borderRadius="8px",
      ~maxWidth="180px",
      ~textAlign="center",
      (),
    )}>
    <p
      style={ReactDOMRe.Style.make(
        ~color="#444444",
        ~fontSize="42px",
        ~margin="16px 0",
        (),
      )}>
      {state.seconds |> formatTime |> ReasonReact.string}
    </p>
    <p className="timer"> state.display->React.string </p>
    <p className="timer"> "ticker"->React.string </p>
    <p className="timer"> {test->React.string} </p>
    <p className="timer"> {"display: " ++ display|>React.string} </p>

    {state.isTicking
       ? <Button label="STOP" onClick={_event => dispatch(Stop)} />
       : <>
           <Button label="START" onClick={_event => dispatch(Start)} />
           <Button label="RESET" onClick={_event => dispatch(Reset)} />
         </>}
  </div>;
};
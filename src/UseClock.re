let useClock = () => {
  let (timerId, setTimerId) = React.useState(() => None);
  let (time, setTime) = React.useState(() => Js.Date.now());
  let timeLeft = () => {
    let now = Js.Date.now();
    let nextSec = (Js.Math.floor(now /. 1000.) + 1) * 1000;
    let timeLeft = nextSec - now->int_of_float;
    timeLeft->float_of_int;
  };

  React.useEffect1(
    () => {
      let timerId =
        switch (timerId) {
        | Some(timerId) => timerId
        | None =>
          let timerId =
            Js.Global.setInterval(() => setTime(_ => Js.Date.now()), 1000);
          setTime(_ => timeLeft());
          setTimerId(_ => Some(timerId));

          timerId;
        };

      Some(() => Js.Global.clearInterval(timerId));
    },
    [|timerId|],
  );
  time->Js.Date.fromFloat;
};
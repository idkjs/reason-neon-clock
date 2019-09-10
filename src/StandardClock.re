// module StandardClock = {
  [@react.component]
  let make = () => {
    let (hour, minute, second, _display) = Time.getNow();
    let clockMarks = [|
      "XII",
      "I",
      "II",
      "III",
      "IV",
      "V",
      "VI",
      "VII",
      "VIII",
      "IX",
      "X",
      "XI",
    |];
    let second = second->int_of_float;
    let hour = hour->int_of_float;
    let minute = minute->int_of_float;
    let hourAngle = (hour mod 12 * 60 + minute) / 2;
    let minuteAngle = (minute * 60 + second) / 10;

    let secondAngle = second * 6;

    let hourstyle =
      ReactDOMRe.Style.make(~transform={j|rotate(deg($hourAngle))|j}, ());
    let minutestyle =
      ReactDOMRe.Style.make(~transform={j|rotate(deg($minuteAngle))|j}, ());
    let secondstyle =
      ReactDOMRe.Style.make(~transform={j|rotate(deg($secondAngle))|j}, ());
    let ticks = Belt.Array.make(60, <span className="tick" />);
    // let ticks = Belt.Array.makeUninitialized(60);
    <div className="standard-clock">
      <div>
        {clockMarks
         ->Belt.Array.mapWithIndex((idx,mark) =>
             <span key=string_of_int(idx) className="mark"> mark->React.string </span>
           )
         ->React.array}
      </div>
      <div> {ticks->Belt.Array.map(tick => tick)->React.array} </div>
      <div className="inner-circle" />
      <div className="inner-circle-2" />
      <div className="hour-hand" style=hourstyle />
      <div className="minute-hand" style=minutestyle />
      <div className="second-hand" style=secondstyle />
      <div className="center" />
    </div>;
  };
// };
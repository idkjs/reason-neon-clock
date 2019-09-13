[@react.component]
let make = (~time) => {
  let (seconds, minutes, hours) = Utils.globalTime(~time);
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

  /* This would be an example of creating a `local mutation` where you use the same variable name for multiple stages in the transformation. Here, the first `hourAngle` disappears when its transformed by the second `hourAngle`. See docs at https://reasonml.github.io/docs/en/mutation#tip-tricks */

  let hourAngle = (hours mod 12 * 60 + minutes) / 2;
  let hourAngle = hourAngle->float_of_int;
  let minuteAngle = (minutes * 60 + seconds) / 10;
  let minuteAngle = minuteAngle->float_of_int;
  let secondAngle = seconds * 6;
  let secondAngle = secondAngle->float_of_int;

  /* Here we use string concatination to pass in our calculated angles. This produces an output that looks like ```reason
     {transform: "rotate(82deg)"}
     ```
     when logged in the console. Not being strong in `css` I didn't realize that the `css` is expecting a string which we would get from changing the result of our calculation from an `int` or `float` to a string then attaching the `deg` to the end. I learned this in the usual way, by reading someone else's code. In this case, @persianturtles code [here](https://github.com/persianturtle/reason-app-shell-starter-kit/blob/dc43c75671c1d6959533df94033f8e93319facf4/src/App.re#L384-L397). Thanks, [@RRafatpanah](https://mobile.twitter.com/RRafatpanah)!
     */
  let hourstyle =
    ReactDOMRe.Style.make(
      ~transform="rotate(" ++ Js.Float.toString(hourAngle) ++ "deg)",
      (),
    );
  let minutestyle =
    ReactDOMRe.Style.make(
      ~transform="rotate(" ++ Js.Float.toString(minuteAngle) ++ "deg)",
      (),
    );
  let secondstyle =
    ReactDOMRe.Style.make(
      ~transform="rotate(" ++ Js.Float.toString(secondAngle) ++ "deg)",
      (),
    );

  let ticks = Belt.Array.makeUninitialized(60);
  /* Here we ignore the second argument because it doesnt exist as we created the array with `makeUninitialized` */
  let ticks =
    ticks->Belt.Array.mapWithIndex((idx, _tick) =>
      <span key={string_of_int(idx)} className="tick" />
    );
  <div className="standard-clock">
    /* Genrates roman numerals on clock face */

      <div>
        {clockMarks
         ->Belt.Array.mapWithIndex((idx, mark) =>
             <span key={string_of_int(idx)} className="mark">
               mark->React.string
             </span>
           )
         ->React.array}
      </div>
      /* Generate tick marks on clock face by fanning out the ticks. This is happening in the css because [Ganesh Prasad](https://github.com/GnsP) is a `css` wizard. */
      <div> ticks->React.array </div>
      <div className="inner-circle" />
      <div className="inner-circle-2" />
      <div className="hour-hand" style=hourstyle />
      <div className="minute-hand" style=minutestyle />
      <div className="second-hand" style=secondstyle />
      <div className="center" />
    </div>;
};
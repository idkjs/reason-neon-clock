open NeonClockBase;
[@react.component]
let make = (~time=NeonClockBase.UseClock.useClock()) => {
  <div className="clock"> <StandardClock time /> <TimeReadout time /> </div>;
};
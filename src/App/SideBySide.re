[@react.component]
let make = () => {
  <div style={ReactDOMRe.Style.make(~display="inline-block",~float="left", ())}>
    <NeonClockV1 />
    <NeonClockV2 />
  </div>;
};
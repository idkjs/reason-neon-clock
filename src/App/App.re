[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  Js.log2("url", url);
  let nowShowing =
    switch (url.path) {
    | []
    | ["/"]
    | ["v1"] =>
      ReasonReact.Router.replace("v1");
      <NeonClockV1 />;
    | ["v2"] => <NeonClockV2 />
    | _ => "NotFound"->React.string
    };
  ();
  <div className="clock">
  <header><a href="https://github.com/idkjs/reason-neon-clock">"github.com/idkjs/reason-neon-clock"->React.string</a></header>
   <Nav /> nowShowing </div>;
};
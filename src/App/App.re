[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

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
  <div>
    <Nav />
    nowShowing
  </div>;
};
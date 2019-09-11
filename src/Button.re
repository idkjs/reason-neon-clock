  [@react.component]
  let make = (~label, ~onClick) => {
    <button onClick> {label |> ReasonReact.string} </button>;
  };
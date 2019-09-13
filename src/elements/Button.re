[@react.component]
let make = (~label, ~onClick, ~className=?) => {
  <button ?className onClick>
    <span className="glow">
      {"Click to here-> " ++ label |> ReasonReact.string}
    </span>
  </button>;
};
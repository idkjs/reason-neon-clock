[@react.component]
let make = (~label, ~onClick, ~className=?) => {
  <button ?className onClick>
    <span className="glow">
      {"Click to here-> " ++ label |> React.string}
    </span>
  </button>;
};
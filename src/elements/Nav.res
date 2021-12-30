module Link = {
  let handleClick = (href, event) => {
    ReactEvent.Mouse.preventDefault(event)
    RescriptReactRouter.push(href)
  }

  @react.component
  let make = (~href, ~className="", ~children) =>
    <a href className onClick={handleClick(href)}> children </a>
}
@react.component
let make = () =>
  <nav style={ReactDOM.Style.make(~display="flex", ())}>
    <Link className="glow" href="/v1">
      <h4> {"ReactReact/ReactFRP "->React.string} </h4>
    </Link>
    <div> {" " ++ (" | " ++ " ") |> React.string} </div>
    <Link className="glow" href="/v2">
      <h4> {" ReasonHooks"->React.string} </h4>
    </Link>
  </nav>

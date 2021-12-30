switch ReactDOM.querySelector("#root") {
| Some(root) => ReactDOM.render(<SideBySide />, root)
| None => Js.log("Refresh browser")
}
/** Identity function */
let i = x => x;

let none = f => {
    f();
    None;
  };
let unwrapStr = (f, maybeStr) =>
  switch (maybeStr) {
  | Some(v) => f(v)
  | None => ""
  };

[@bs.module "react"] external createRef: unit => ReactDOMRe.domRef = "createRef";

external munge: ReactDOMRe.domRef => React.Ref.t(Js.nullable(Dom.element)) = "%identity";

let optionDomRef = domRef => domRef->munge->React.Ref.current->Js.Nullable.toOption;
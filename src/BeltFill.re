
type t('a) = array('a);
let size = Belt.Array.size;
let makeEmpty = (): t('a) => [||];
let fill = (arr: t('a), x: 'a) =>
  Belt.Array.fill(arr, ~offset=0, ~len=size(arr), x);
// let arr=makeEmpty();

// arr->Belt.Array.fill(~len=60,~offset=1)
// fill(arr,)->Js.log;
// arr->Belt.Array.fill(~len=60,~offset=1)->Belt.Array.map(tick => <span className="tick" />)
let arr: array(Js.undefined(string)) = Belt.Array.makeUninitialized(60);

Belt.Array.getExn(arr, 0) == Js.undefined;
Js.log2(" array ", arr );
open Belt;
Array.make(60, "<span className='tick' />")->Js.log;
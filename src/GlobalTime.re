/* Here I was trying to synchronize the clocks by making them refer to the same variable but not quite there yet. */
type t = float;
let time = ():t => Js.Date.now();
let avg = (a: float, b: float) : float => {
  (a +. b) /. 2.0;
};

Js.log2("Average of 3 and 4", avg(3.0, 4.0));
Js.log2("Average of 3?!", avg(3.0));

let call = (country: string, area: string, number: string)
  : string => {
    country ++ " " ++ area ++ " " ++ number;
};

Js.log2("Call Kim at", call("49", "030", "118 99"));

let callGermany = call("049");
let callBerlin = call("049", "030");

Js.log2("Call Germany:", callGermany);
Js.log2("Call Berlin:", callBerlin);
let callGermany2 =()=> call("049");
let callBerlin2 =()=> call("049", "030");

Js.log2("Call Germany2:", callGermany2());
Js.log2("Call Berlin2:", callBerlin2());

Js.log2("Call someone in Germany:", callGermany("040", "118 01"));
Js.log2("Call someone in Berlin:", callBerlin("118 23"));


module GreenDiv =
  [%style
    type props = {
      blue: string;
      green: string;}
    let _ = {j|
  background: green;
  color: blue;
|j}]
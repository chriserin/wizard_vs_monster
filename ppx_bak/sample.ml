let abc = (("123")[@reason.raw_literal "123"])
module GreenDiv =
  [%style
    (("\n  background: green;\n  color: blue;\n")[@reason.raw_literal
                                                   "\n  background: green;\n  color: blue;\n"])]
let _ = print_endline abc
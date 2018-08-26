module GreenDiv =
  struct
    let style =
      (("\n    color: valueA;\n  ")[@reason.raw_literal
                                     "\n    color: valueA;\n  "])
    type jsProps = {
      className: string;
      valueA: string;
      valueB: string;}[@@bs.deriving abstract]
    let make ~className  ~valueA  ~valueB  children =
      let props = jsProps ~className ~valueA ~valueB in
      let map =
        [((("valueA")[@reason.raw_literal "valueA"]), valueA);
        ((("valueB")[@reason.raw_literal "valueB"]), valueB)] in
      Style.makeWithProps props children style map
  end
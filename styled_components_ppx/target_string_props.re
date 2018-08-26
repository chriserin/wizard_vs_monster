module GreenDiv = {
  let style = "
    color: valueA;
  ";

  [@bs.deriving abstract]
  type jsProps = {
    className: string,
    valueA: string,
    valueB: string
  };

  let make = (~className="", ~valueA, ~valueB, children) => {
    let props = jsProps(~className, ~valueA, ~valueB);

    let map = [
      ("valueA", valueA),
      ("valueB", valueB),
    ];

    Style.makeWithProps(props, children, style, map);
  }
}

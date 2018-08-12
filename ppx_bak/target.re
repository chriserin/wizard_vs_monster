
module GreenDiv {
  let style = "";

  let make = (~className, children) => {
    Style.make(~className, children, style)
  }
}

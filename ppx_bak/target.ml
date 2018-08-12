module GreenDiv =
  struct
    let style = ""
    let make ~className  children = Style.make ~className children style
  end
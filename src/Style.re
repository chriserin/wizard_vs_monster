[@bs.module "styled-components"] [@bs.scope("default")] external div : (array(string)) => ReasonReact.reactClass = "div";
[@bs.module "styled-components"] external style : (string) => ((array(string)) => ReasonReact.reactClass) = "default";

[@bs.deriving abstract]
type jsProps = {
  className: string,
};


let make = (~className, children, style) => {

  let reactClass = div([| style |]);

  ReasonReact.wrapJsForReason(
    ~reactClass=reactClass,
    ~props=jsProps(~className),
    children,
  );
}

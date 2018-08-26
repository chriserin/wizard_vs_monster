[@bs.module "styled-components"] [@bs.scope("default")] external div : (array(string)) => ReasonReact.reactClass = "div";
/* [@bs.module "styled-components"] [@bs.scope("default")] [@bs.splice] external divWithProps : (array(string), array(string)) => ReasonReact.reactClass = "div"; */

let divWithProps: (array(string), array(string)) => ReasonReact.reactClass = [%raw "function(strings, args) {
  args.unshift(strings);
  return StyledComponents.default.div.apply(null, args);
}"
];

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

let makeWithProps = (props, children, style, propsMap) => {

  let keys = List.map(((k, v)) => k, propsMap);

  let regexOptionsWithStartPipe = List.fold_left((acc, item) => acc ++ "|" ++ item, "", keys);

  let regexOptions = String.sub(regexOptionsWithStartPipe, 1, String.length(regexOptionsWithStartPipe) - 1);
  let regexString = Printf.sprintf("%s", regexOptions);

  let regex = Js.Re.fromStringWithFlags(regexString, "g");

  let styleArray = Js.String.splitByRe(regex, style);

  let tokenMatches = Js.String.match(regex, style);

  let tokenValueFind = (token) => {
    let (_, value) = List.find((((k, v)) => token == k), propsMap);
    value;
  };

  let tokenValues = switch tokenMatches {
    | Some(matches) => List.map(tokenValueFind, Array.to_list(matches))
  }

  let arrayValues: array(string) = Array.of_list(tokenValues);

  Js.log(styleArray);
  Js.log(arrayValues);
  let reactClass = divWithProps(styleArray, arrayValues);

  ReasonReact.wrapJsForReason(
    ~reactClass=reactClass,
    ~props=props,
    children,
  );
}

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

    makeWithProps(props, children, style, map)
  }
}

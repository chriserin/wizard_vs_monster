[%bs.raw {|require('./Results.css')|}];

type state = {
  resultsLength: int
}

type action =
| NewLength(int)

let component = ReasonReact.reducerComponent("Results");

let make = (~results: list(Game.result), ~monster: Game.monster, _children) => {
  ...component,
  initialState: () => {resultsLength: 0},
  reducer: (NewLength(l), state:state) => ReasonReact.Update({...state, resultsLength: l}),
  render: self => {
    let name: string = monster.name;

    let messageDivs =
      List.map((result: Game.result) => <Result result />, results);

    let resultsLength:int = self.state.resultsLength;

    let top = (self.state.resultsLength - List.length(results)) * 24;

    let originalStyle = ReactDOMRe.Style.make(~top=string_of_int(top) ++ "px", ());

    let topStyle = if (self.state.resultsLength != List.length(results)) {
      let timeoutId = Js.Global.setTimeout(fun (_) => {
        self.send(NewLength(List.length(results)));
      }, 20);
      originalStyle;
    } else {
      ReactDOMRe.Style.unsafeAddProp(originalStyle, "transition", "top 1s ease");
    };

    <div className="results" >
      <div className="results-container" style=topStyle>
        (ReasonReact.array(Array.of_list(messageDivs)))
      </div>
    </div>;
  },
};

[%bs.raw {|require('./Result.css')|}];

let component = ReasonReact.statelessComponent("Monster");

let make = (~results:list(Game.result), ~monster:Game.monster, _children) => {
  ...component,
  render: self => {
    let name:string = monster.name;

    let messageDivs = List.map((result:Game.result) => {
      let message = switch(result) {
      | None => "Hey that monster is looking at you sorta funny."
      | HurtMonster(description) => description
      | DeadMonster(description) => description
      | NewMonster(description) => description
      };

      <div>(ReasonReact.string(message))</div>
    }, results);

    <div className="result">
      (ReasonReact.array(Array.of_list(messageDivs)))
    </div>;
  }
};

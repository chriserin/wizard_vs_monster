[%bs.raw {|require('./Result.css')|}];

let component = ReasonReact.statelessComponent("Monster");

let make = (~result:Game.result, ~monster:Game.monster, _children) => {
  ...component,
  render: self => {
    let name:string = monster.name;

    let message = switch(result) {
    | None => "Hey that monster is looking at you sorta funny."
    | HurtMonster(description) => description
    | DeadMonster(description) => description
    };

    <div className="result">
      <div>(ReasonReact.string(message))</div>
    </div>;
  }
};

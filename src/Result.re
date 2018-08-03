[%bs.raw {|require('./Result.css')|}];

let component = ReasonReact.statelessComponent("Result");

let monsterName = (name) =>
  <span className="result-monster">(ReasonReact.string(name))</span>;

let make = (~result, _children) => {
  ...component,
  render: self => {
    let message =
      switch ((result: Game.result)) {
      | None =>
        <div>
        </div>
      | DeadMonster(description) =>
        <div> (ReasonReact.string(description)) </div>
      | NewMonster({name: name}) =>
        <div> (ReasonReact.string("A")) (monsterName(name)) (ReasonReact.string("approaches"))</div>
      | MonsterAttack(Damage(damage)) =>
        <div> (ReasonReact.string(Printf.sprintf("Monster attacks for %i damage", damage))) </div>
      | HurtMonster(name, damage, spell) =>
        <div> (ReasonReact.string(Printf.sprintf("Using %s you hurt ", spell.name))) (monsterName(name)) (ReasonReact.string(Printf.sprintf("for %i damage ", damage))) </div>
      };

    <div className="result"> message </div>;
  },
};

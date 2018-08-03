
[@bs.module] external picture : string = "./monster-snake.svg";

[%bs.raw {|require('./Monster.css')|}];

let component = ReasonReact.statelessComponent("Monster");

let make = (~monster:Game.monster, _children) => {
  ...component,
  render: self => {
    let name:string = monster.name;
    let (min, max) = monster.attackStrength;

    <div className="monster">
      <div className="name">(ReasonReact.string(name))</div>
      <Stat name="Hitpoints" value={string_of_int(monster.hitpoints)}/>
      <Stat name="Attack" value={string_of_int(max)}/>
      <img src=(monster.image) />
    </div>;
  }
};

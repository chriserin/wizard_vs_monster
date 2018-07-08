
[@bs.module] external picture : string = "./monster-picture.svg";

[%bs.raw {|require('./Monster.css')|}];

let component = ReasonReact.statelessComponent("Monster");

let make = (~monster:Game.monster, _children) => {
  ...component,
  render: self => {
    let name:string = monster.name;

    <div className="monster">
      <div>(ReasonReact.string(name))</div>
      <div>(ReasonReact.string(Printf.sprintf("Hitpoints: %i", monster.hitpoints)))</div>
      <img src=picture />
    </div>;
  }
};

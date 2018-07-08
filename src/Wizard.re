
[@bs.module] external picture : string = "./wizard-picture.svg";

[%bs.raw {|require('./Wizard.css')|}];

let component = ReasonReact.statelessComponent("Wizard");

let make = (~wizard:Game.wizard, ~onSpell, _children) => {
  ...component,
  render: self => {
    let name:string = wizard.name;

    <div className="wizard">
      <div>(ReasonReact.string(name))</div>
      <div>(ReasonReact.string(Printf.sprintf("Age: %i", wizard.age)))</div>
      <img src=picture />
      <div onClick=((_event) => onSpell("Fire"))>(ReasonReact.string({js| Fire 🔥 |js}))</div>
    </div>;
  }
};

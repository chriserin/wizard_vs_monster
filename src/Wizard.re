
[@bs.module] external picture : string = "./wizard-picture.svg";

[%bs.raw {|require('./Wizard.css')|}];

let component = ReasonReact.statelessComponent("Wizard");

let make = (~wizard:Game.wizard, ~onSpell, _children) => {
  ...component,
  render: self => {
    let name:string = wizard.name;

    let spells = List.map((spell:Spells.spell) => {
      <div onClick=((_event) => onSpell(spell))>(ReasonReact.string(spell.name))</div>
    }, wizard.spells);

    <div className="wizard">
      <div>(ReasonReact.string(name))</div>
      <div>(ReasonReact.string(Printf.sprintf("Age: %i", wizard.age)))</div>
      <img src=picture />
      (ReasonReact.arrayToElement(Array.of_list(spells)))
    </div>;
  }
};

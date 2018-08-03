
[@bs.module] external picture : string = "./wizard-picture.svg";

[%bs.raw {|require('./Wizard.css')|}];

let component = ReasonReact.statelessComponent("Wizard");

let make = (~wizard:Game.wizard, ~onSpell, _children) => {
  ...component,
  render: self => {
    let name:string = wizard.name;

    let spells = List.map((spell:Spells.spell) => {
      <div className="spell" onClick=((_event) => onSpell(spell))>(ReasonReact.string(spell.name))</div>
    }, wizard.spells);

    <div className="wizard">
      <div className="name">(ReasonReact.string(name))</div>
      <Stat name="Age" value={string_of_int(wizard.age)}/>
      <Stat name="Hitpoints" value={string_of_int(wizard.hitpoints)}/>
      <img src=picture />
      (ReasonReact.array(Array.of_list(spells)))
    </div>;
  }
};

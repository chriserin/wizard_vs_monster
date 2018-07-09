[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo : string = "./wizard-logo.svg";

type action =
  | Fire
  | Spell(Spells.spell)


type state = {
  wizard: Game.wizard,
  monster: Game.monster,
  result: Game.result
}

let component = ReasonReact.reducerComponent("App");

let make = (~message, _children) => {
  ...component,
  initialState: () => {
    wizard: {
      age: 132,
      name: "Owain Gyn Dwr",
      hitpoints: 1000,
      spells: [Spells.fire],
    },
    monster: List.hd(Game.monsters),
    result: None
  },
  reducer: (action, state:state) => 
    switch (action) {
    | Fire => ReasonReact.Update(state)
    | Spell(spell) => {
        let ( wizard, monster, result) = Game.callSpell(spell, state.wizard, state.monster);
        ReasonReact.Update({...state, wizard, monster, result})
      }
    },
  render: self => {
    let theWiz = self.state.wizard;

    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (ReasonReact.string("Wizard vs Monster")) </h2>
      </div>
      <div>
        <Wizard wizard=(theWiz) onSpell=((spellName) => self.send(Spell(spellName)) )>
        </Wizard>
        <Monster monster=(self.state.monster)>
        </Monster>
      </div>
      <Result result=(self.state.result) monster=(self.state.monster) />
    </div>;
  },
};

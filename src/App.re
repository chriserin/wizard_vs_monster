[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo : string = "./wizard-logo.svg";

type action =
  | Fire
  | Spell(string)


type state = {
  wizard: Game.wizard,
  monster: Game.monster
}

let component = ReasonReact.reducerComponent("App");

let make = (~message, _children) => {
  ...component,
  initialState: () => {
    wizard: {
      age: 132,
      name: "Owain Gyn Dwr",
      hitpoints: 1000
    },
    monster: {
      name: "Snake",
      hitpoints: 20
    }
  },
  reducer: (action, state:state) => 
    switch (action) {
    | Fire => ReasonReact.Update(state)
    | Spell(name) => {
        let ( wizard, monster ) = Game.callSpell(Game.WizardSpell(name), state.wizard, state.monster);
        ReasonReact.Update({...state, wizard, monster})
      }
    },
  render: self => {
    let theWiz = self.state.wizard;

    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (ReasonReact.string("Wizard vs Monster")) </h2>
      </div>
      <Wizard wizard=(theWiz) onSpell=((spellName) => self.send(Spell(spellName)) )>
      </Wizard>
      <Monster monster=(self.state.monster)>
      </Monster>
    </div>;
  },
};

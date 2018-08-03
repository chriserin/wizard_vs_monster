[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo : string = "./wizard-logo.svg";

[@bs.module "styled-components"] [@bs.scope("default")] external div : string = "div";

let styledReason = div;

Js.log(styledReason)

type action =
  | Fire
  | Spell(Spells.spell)
  | Activity


type state = {
  wizard: Game.wizard,
  monster: Game.monster,
  results: list(Game.result)
}

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {
    wizard: {
      age: 132,
      name: "Owain Gyn Dwr",
      hitpoints: 1000,
      spells: [Spells.fire],
      monsterKills: 0,
    },
    monster: List.hd(Game.monsters),
    results: [NewMonster(List.hd(Game.monsters))]
  },
  reducer: (action, state:state) => 
    switch (action) {
    | Fire => ReasonReact.Update(state)
    | Spell(spell) => {
        let ( wizard, monster, spellResults) = Game.callSpell(spell, state.wizard, state.monster);

        let (wizard, attackResults) = if (!List.exists((result) => {
          switch(result) {
          | Game.DeadMonster(_) => true
          | _ => false
          };
        }, spellResults)) {
          let (wizard, attackResults) = Game.monsterAttack(wizard, monster);
          (wizard, List.map((attackResult) => Game.MonsterAttack(attackResult), attackResults));
        } else {
          (wizard, [])
        };

        ReasonReact.Update({wizard, monster, results: List.concat([attackResults, spellResults, state.results])});
      }
    },
  render: self => {
    let theWiz = self.state.wizard;

    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (ReasonReact.string("Wizard vs Monster")) </h2>
      </div>
      <div className="battle-board">
        <Wizard wizard=(theWiz) onSpell=((spellName) => self.send(Spell(spellName)) )>
        </Wizard>
        <Monster monster=(self.state.monster)>
        </Monster>
      </div>
      <Results results=(self.state.results) monster=(self.state.monster) />
    </div>;
  },
};

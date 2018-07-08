

type wizard = {
  age: int,
  name: string,
  hitpoints: int,
};

type monster = {
  name: string,
  hitpoints: int,
}

type spellAction =
  | WizardSpell(string)

let callSpell = (action:spellAction, wizard, monster) => {
  switch(action) {
    | WizardSpell("Fire") => 
      let hurtMonster:monster = {...monster, hitpoints: monster.hitpoints - 10};
      (wizard, hurtMonster)
  }
}

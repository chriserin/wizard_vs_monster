
[@bs.module] external snakesvg : string = "./monster-snake.svg";
[@bs.module] external bearsvg : string = "./monster-bear.svg";
[@bs.module] external wolfsvg : string = "./monster-wolf.svg";

type spellAction =
  | WizardSpell(string)

type wizard = {
  age: int,
  name: string,
  hitpoints: int,
  spells: list(Spells.spell),
  monsterKills: int
};

type monster = {
  name: string,
  image: string,
  hitpoints: int,
  spellAgainst: (Spells.spell, monster) => monster,
}

type result =
  | None
  | DeadMonster(string)
  | HurtMonster(string)

let monsters:list(monster) = [
  {
    name: "Snake",
    image: snakesvg,
    hitpoints: 20,
    spellAgainst: (spell, monster) => {
      let damage = Spells.damage(spell);
      {...monster, hitpoints: monster.hitpoints - damage};
    }
  },
  {
    name: "Bear",
    image: bearsvg,
    hitpoints: 40,
    spellAgainst: (spell, monster) => {
      let damage = Spells.damage(spell);
      {...monster, hitpoints: monster.hitpoints - damage};
    }
  },
  {
    name: "Wolf",
    image: wolfsvg,
    hitpoints: 40,
    spellAgainst: (spell, monster) => {
      let damage = Spells.damage(spell);
      {...monster, hitpoints: monster.hitpoints - damage};
    }
  }
];

let callSpell = (spell, wizard, monster) => {
  let hurtMonster = monster.spellAgainst(spell, monster);

  if (hurtMonster.hitpoints <= 0) {
    let uppedWizard = {...wizard, monsterKills: wizard.monsterKills + 1};
    let nextMonster = List.nth(monsters, uppedWizard.monsterKills);
    (uppedWizard, nextMonster, DeadMonster("You killed it"));
  } else if (hurtMonster.hitpoints < monster.hitpoints) {
    (wizard, hurtMonster, HurtMonster("You hurt it"));
  } else {
    (wizard, hurtMonster, None);
  };
}

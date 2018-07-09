
[@bs.module] external snakesvg : string = "./monster-snake.svg";
[@bs.module] external bearsvg : string = "./monster-bear.svg";

type spellAction =
  | WizardSpell(string)

type wizard = {
  age: int,
  name: string,
  hitpoints: int,
  spells: list(Spells.spell),
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
  }
]

let callSpell = (spell, wizard, monster) => {
  let hurtMonster = monster.spellAgainst(spell, monster);

  if (hurtMonster.hitpoints <= 0) {
    let hurtMonster = List.hd(List.tl(monsters));
    (wizard, hurtMonster, DeadMonster("You killed it"));
  } else if (hurtMonster.hitpoints < monster.hitpoints) {
    (wizard, hurtMonster, HurtMonster("You hurt it"));
  } else {
    (wizard, hurtMonster, None);
  };
}


[@bs.module] external snakesvg : string = "./monster-snake.svg";

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

let callSpell = (spell, wizard, monster) => {
  let hurtMonster = monster.spellAgainst(spell, monster);
  let result = if (hurtMonster.hitpoints <= 0) {
    DeadMonster("You killed it")
  } else if (hurtMonster.hitpoints < monster.hitpoints) {
    HurtMonster("You hurt it")
  } else {
    None
  };

  (wizard, hurtMonster, result)
}

let monsters:list(monster) = [
  {
    name: "Snake",
    image: snakesvg,
    hitpoints: 20,
    spellAgainst: (spell, monster) => {
      let damage = Spells.damage(spell);
      {...monster, hitpoints: monster.hitpoints - damage};
    }
  }
]

[@bs.module] external snakesvg : string = "./monster-snake.svg";
[@bs.module] external bearsvg : string = "./monster-bear.svg";
[@bs.module] external wolfsvg : string = "./monster-wolf.svg";

type spellAction =
  | WizardSpell(string);

type wizard = {
  age: int,
  name: string,
  hitpoints: int,
  spells: list(Spells.spell),
  monsterKills: int,
};

type attackResult = 
| Damage(int)
| NoDamage(int)

type monster = {
  name: string,
  image: string,
  hitpoints: int,
  attackStrength: (int, int),
  spellAgainst: (Spells.spell, monster) => monster,
  attack: (wizard, monster) => (wizard, attackResult),
};

type result =
  | None
  | DeadMonster(string)
  | HurtMonster(string, int, Spells.spell)
  | NewMonster(monster)
  | MonsterAttack(attackResult);

let damage = ((min, max)) => Random.int(max - min) + min;

let monsters: list(monster) = [
  {
    name: "Snake",
    image: snakesvg,
    hitpoints: 20,
    spellAgainst: (spell, monster) => {
      let damage = Spells.damage(spell);
      {...monster, hitpoints: monster.hitpoints - damage};
    },
    attackStrength: (0, 10),
    attack: (wizard, monster) => {
      let attackDamage = damage(monster.attackStrength);
      (
        {...wizard, hitpoints: wizard.hitpoints - attackDamage},
        Damage(attackDamage),
      );
    },
  },
  {
    name: "Bear",
    image: bearsvg,
    hitpoints: 40,
    spellAgainst: (spell, monster) => {
      let damage = Spells.damage(spell);
      {...monster, hitpoints: monster.hitpoints - damage};
    },
    attackStrength: (0, 10),
    attack: (wizard, monster) => {
      let attackDamage = damage(monster.attackStrength);
      (
        {...wizard, hitpoints: wizard.hitpoints - attackDamage},
        Damage(attackDamage),
      )
    },
  },
  {
    name: "Wolf",
    image: wolfsvg,
    hitpoints: 40,
    spellAgainst: (spell, monster) => {
      let damage = Spells.damage(spell);
      {...monster, hitpoints: monster.hitpoints - damage};
    },
    attackStrength: (0, 10),
    attack: (wizard, monster) => {
      let attackDamage = damage(monster.attackStrength);
      (
        {...wizard, hitpoints: wizard.hitpoints - attackDamage},
        Damage(attackDamage),
      );
    },
  },
];

let callSpell = (spell, wizard, monster) => {
  let hurtMonster = monster.spellAgainst(spell, monster);
  let results = [];

  if (hurtMonster.hitpoints <= 0) {
    let uppedWizard = {...wizard, monsterKills: wizard.monsterKills + 1};
    let nextMonster = List.nth(monsters, uppedWizard.monsterKills);
    (
      uppedWizard,
      nextMonster,
      [
        NewMonster(nextMonster),
        DeadMonster("You killed the " ++ monster.name),
      ],
    );
  } else if (hurtMonster.hitpoints < monster.hitpoints) {
    (
      wizard,
      hurtMonster,
      [
        HurtMonster(
          hurtMonster.name,
          monster.hitpoints - hurtMonster.hitpoints,
          spell,
        ),
      ],
    );
  } else {
    (wizard, hurtMonster, [None]);
  };
};

let monsterAttack = (wizard, monster) => {
  let (hurtWizard, result) = monster.attack(wizard, monster);
  (hurtWizard, [result]);
};

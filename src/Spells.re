type spell = {
  name: string,
  min: int,
  max: int,
  target: string,
};

let damage = (spell) => {
  Random.int(spell.max - spell.min) + spell.min
};

let fire = {
  name: {js| Fire 🔥 |js},
  min: 0,
  max: 10,
  target: "hitpoints"
};

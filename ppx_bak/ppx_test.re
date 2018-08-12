
let test_mapper = (_argv) => {
  ...Ast_mapper.default_mapper,
  expr: (mapper, expr) =>
    switch (expr) {
    | {pexp_desc: [@implicit_arity] Pexp_extension({txt: "test"}, PStr([]))} =>
      Ast_helper.Exp.constant([@implicit_arity] Pconst_integer("42", None))
    | other => default_mapper.expr(mapper, other)
    },
};

let () = Ast_mapper.register("ppx_test", test_mapper);

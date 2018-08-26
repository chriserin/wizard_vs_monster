
open Ast_helper

let declare_style loc style =
  Str.value Nonrecursive [
    Vb.mk (Pat.var {txt="style";loc=loc}) (Exp.constant (Const_string (style, None)))
  ]

let make_function (loc : Location.t) : Parsetree.structure_item = 
  Str.value Nonrecursive
     [Vb.mk (Pat.var {txt = "make"; loc=loc})
     (Exp.fun_ "?className" (Some (Exp.constant (Const_string ("", None))))
           (Pat.var {txt = "className"; loc=loc})
           (Exp.fun_ "" None
              (Pat.var {txt = "children"; loc=loc})
              (Exp.apply
                 (Exp.mk (Pexp_ident {txt = Ldot (Lident "Style", "make"); loc=loc}))
                 [("className",
                   Exp.mk (Pexp_ident {txt = Lident "className"; loc=loc}));
                  ("",
                   Exp.mk (Pexp_ident {txt = Lident "children"; loc=loc}));
                  ("",
                   Exp.mk (Pexp_ident {txt = Lident "style"; loc=loc}))])))]

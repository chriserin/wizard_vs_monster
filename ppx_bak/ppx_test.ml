open Ast_mapper
open Ast_helper

let oneplustwo loc =
  Exp.apply (Exp.ident {txt=Lident "+";loc})
    [
      ("", Exp.constant (Const_int 2));
          ("", Exp.constant (Const_int 3))
    ]

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

let component_module_contents loc style =
  [
    declare_style loc style;
    make_function loc
  ]

let component_module (loc : Location.t) (name : string) (style : string): Parsetree.structure_item =
  {
    pstr_desc=(
      Pstr_module (Mb.mk {txt=name; loc=loc} (Mod.mk (Pmod_structure (component_module_contents loc style)))));
    pstr_loc=loc
  }

let test_mapper _argv =
   {
      Ast_mapper.default_mapper with
      structure_item =
        (fun mapper structure_item ->
          match structure_item with
            | {
              pstr_desc=Pstr_module {pmb_expr={pmod_desc=Pmod_extension ({txt="style"}, PStr [{pstr_desc=Pstr_eval ({pexp_desc= Pexp_constant (Const_string (style, _))}, []) }])}; pmb_name={txt=name}};
                pstr_loc=loc
              } ->
              begin
                component_module loc name style
              end
            | other -> default_mapper.structure_item mapper other
        );
    }

let () =
    register "ppx_test" test_mapper

(* {pexp_desc = Pexp_ident { txt = Lident "x"; loc = Location.none; }} *)

(* 
module DivStyle = {
  let styleString = {js|
    background: green;
    color: blue;
  |js};
}
module BlackDiv =  Div.MakeComponent(DivStyle);
*)

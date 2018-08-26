open Ast_helper

let declare_style loc style =
  Str.value Nonrecursive [
    Vb.mk (Pat.var {txt="style";loc=loc}) (Exp.constant (Const_string (style, None)))
  ]

let prop_field_declarations loc names =
  let collect_fields (name: string) =
    Type.field {txt=name;loc=loc} (Typ.mk (Ptyp_constr ({txt=Lident "string";loc=loc}, [])))
    in
  List.map collect_fields names

let declare_props loc names =
  Str.type_ [
    Type.mk ~attrs: [({txt = "bs.deriving";loc=loc},
                  PStr [Str.eval (Exp.mk (Pexp_ident {txt = Lident "abstract";loc=loc}))]
                    )]
            ~kind:(Ptype_record (List.append [
              Type.field {txt="className";loc=loc} 
                         (Typ.mk (Ptyp_constr ({txt=Lident "string";loc=loc}, [])))
            ] (prop_field_declarations loc names)))
            {txt="jsProps";loc=loc}
  ]

let make_function_args names loc : (string * Parsetree.expression) list =
  let collect_args name =
    ("", Exp.mk (Pexp_ident {txt = Lident name; loc=loc}))
    in
  List.map collect_args names

let make_assignment_args names loc =
  let collect_args name =
    (name, Exp.mk (Pexp_ident {txt = Lident name; loc=loc}))
    in
  List.map collect_args names

let props_assignment_expression names loc =
  Exp.apply (Exp.mk (Pexp_ident {txt = Lident "jsProps"; loc=loc}))
    (make_assignment_args names loc)

let rec map_assignment_expression names loc =
  match names with
  | [] ->
    Exp.construct {txt=Lident "[]";loc=loc} None
  | hd :: tl ->
    Exp.construct {txt = Lident "::";loc=loc}
            (Some
             (Exp.tuple
                [Exp.tuple
                    [Exp.constant ?attrs:(Some [({txt="reason.raw_literal";loc=loc},
                                           PStr [Str.eval (Exp.constant (Const_string (hd, None)))]
                                          )])
                                        (Const_string (hd, None));
                     (Exp.ident {txt = Lident hd;loc=loc})];
                     map_assignment_expression tl loc
                 ]))

let function_body names loc =
  Exp.let_ Nonrecursive [Vb.mk (Pat.var {txt="props"; loc=loc}) (props_assignment_expression (List.filter (fun (name) -> name <> "children") names) loc)]
    (Exp.let_ Nonrecursive [Vb.mk (Pat.var {txt="map"; loc=loc}) (map_assignment_expression (List.filter (fun (name) -> name <> "children") names) loc)]
    (Exp.apply
     (Exp.mk (Pexp_ident {txt = Ldot (Lident "Style", "makeWithProps"); loc=loc}))
     (make_function_args ["props"; "children"; "style"; "map"] loc)))

let rec make_funs original_names names loc =
  match names with
  | ["children"] ->
    (Exp.fun_ "" None
      (Pat.var {txt = "children"; loc=loc})
      (function_body original_names loc)
    )
  | "classname" :: tl ->
     (Exp.fun_ "?className" (Some (Exp.constant (Const_string ("", None))))
           (Pat.var {txt = "className"; loc=loc})
           (make_funs original_names tl loc)
     )
  | hd :: tl ->
     (Exp.fun_ ("?" ^ hd) None
           (Pat.var {txt = hd; loc=loc})
           (make_funs original_names tl loc)
     )

let make_function (loc : Location.t) (names) : Parsetree.structure_item = 
  Str.value Nonrecursive
     [Vb.mk (Pat.var {txt = "make"; loc=loc})
            (make_funs (List.append (List.append ["classname"] names) ["children"]) (List.append (List.append ["classname"] names) ["children"]) loc)
     ]

  (*
let assign_transformed_props =
  {pstr_desc =
     Pstr_value (Nonrecursive,
      [{pvb_pat = {ppat_desc = Ppat_var {txt = "props"}};
        pvb_expr =
         {pexp_desc =
           Pexp_apply ({pexp_desc = Pexp_ident {txt = Lident "jsProps"}},
            [("className", {pexp_desc = Pexp_ident {txt = Lident "className"}});
             ("valueA", {pexp_desc = Pexp_ident {txt = Lident "valueA"}});
             ("valueB", {pexp_desc = Pexp_ident {txt = Lident "valueB"}})])}}])}*)

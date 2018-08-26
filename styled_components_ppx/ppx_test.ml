open Ast_mapper
open Ast_helper

exception PPXError of string

type nullable_structure_item =
  | Pstr of Parsetree.structure_item
  | None;;

type style_module_components = {
  style_string: string;
  prop_types_str: nullable_structure_item;
  prop_type_names: string list;
}

let component_module_contents loc style_module_components =
  match style_module_components with
  | { style_string=style; prop_types_str=None; prop_type_names=[]; } ->
    [
      Simple.declare_style loc style;
      Simple.make_function loc
    ]
  | { style_string=style; prop_types_str=str; prop_type_names=names; } ->
    [
      With_props.declare_style loc style;
      With_props.declare_props loc names;
      With_props.make_function loc names;
    ]
  | other -> raise (PPXError "Something bad happened")

let component_module (loc : Location.t) (name : string) (style_module_comps: style_module_components): Parsetree.structure_item =
  {
    pstr_desc=(
      Pstr_module (Mb.mk {txt=name; loc=loc} (Mod.mk (Pmod_structure (component_module_contents loc style_module_comps)))));
    pstr_loc=loc
  }

let process_types (types: Parsetree.label_declaration list) =
  let collect_name (prop_type_elem: Parsetree.label_declaration) =
    match prop_type_elem with
    | {
        pld_name={txt=name}
      } ->
      name
    in
  List.map collect_name types

let process_structure_items (items: Parsetree.structure) loc : style_module_components = 
  match items with
  | [{pstr_desc=Pstr_eval ({pexp_desc= Pexp_constant (Const_string (style, _))}, []) }] ->
      {style_string=style; prop_types_str=None; prop_type_names=[]}
  | [ {pstr_desc =
            Pstr_type
             [{
               ptype_name = {txt = "props"};
               ptype_kind = Ptype_record types;
              }]
             } as prop_types_str;
      {pstr_desc=Pstr_eval ({pexp_desc= Pexp_constant (Const_string (style, _))}, []) }
    ] ->
      {style_string=style; prop_types_str=(Pstr prop_types_str); prop_type_names=(process_types types)}
  | other -> raise (PPXError "Something bad happened")

let test_mapper _argv =
   {
      Ast_mapper.default_mapper with
      structure_item =
        (fun mapper structure_item ->
          match structure_item with
            | {
              pstr_desc=Pstr_module {pmb_expr={pmod_desc=Pmod_extension ({txt="style"}, PStr structure_items)}; pmb_name={txt=name}};
                pstr_loc=loc
              } ->
              begin
                component_module loc name (process_structure_items structure_items loc)
              end
            | other -> default_mapper.structure_item mapper other
        );
    }

let () =
    register "ppx_test" test_mapper

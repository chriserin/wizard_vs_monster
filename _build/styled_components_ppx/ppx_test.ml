open Ast_mapper
open Ast_helper

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
    []
  | other -> raise ("Something bad happened")

let component_module (loc : Location.t) (name : string) (style_module_comps: style_module_components): Parsetree.structure_item =
  {
    pstr_desc=(
      Pstr_module (Mb.mk {txt=name; loc=loc} (Mod.mk (Pmod_structure (component_module_contents loc style_module_components)))));
    pstr_loc=loc
  }

let process_types types =
  let collect_name prop_type_elem =
    match prop_type_elem with
    | {
        pld_name = {txt = name};
      } ->
      name
    in
  List.map collect_name types

let process_structure_items items loc = 
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
      {style_string=style, prop_types_str=Pstr prop_types_str, prop_type_names=(process_types types)}
  | _ -> raise (Location.Error (
    Location.error loc "[%style] accepts either a string of css rules *or* prop types and a string of css rules"
  ))

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
                component_module loc name (process_style_module structure_items)
              end
            | other -> default_mapper.structure_item mapper other
        );
    }

let () =
    register "ppx_test" test_mapper

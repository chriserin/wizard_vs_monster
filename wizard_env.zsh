echo "loading wizrd zsh env"

get_ast() {
  cat $1.re | refmt --parse re --print ml > $1.ml && ocamlfind ppx_tools/dumpast ./$1.ml
}

compile() {
  cd styled_components_ppx;
  ocamlfind ocamlopt -w -40 -o ppx -linkpkg -package compiler-libs.common simple.ml with_props.ml ppx_test.ml;
  cd -;
}

run_ppx() {
  cat styled_components_ppx/$1.re | refmt --parse re --print ml > styled_components_ppx/$1.ml;
  ocamlfind ppx_tools/rewriter styled_components_ppx/ppx styled_components_ppx/$1.ml | refmt --parse ml --print re
}

# fix it

- make this and libbpf as a submodule and a standalone package
- use bpftools instead of some c templates
- clang -Xclang -ast-dump=json -fsyntax-only client.bpf.c > ast.json
- 
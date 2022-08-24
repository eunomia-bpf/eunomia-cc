# fix me

- use bpftools instead of some c templates to dump related info
- clang -Xclang -ast-dump=json -fsyntax-only client.bpf.c > ast.json
- fix export static rodata var

# hard code now:
- event struct should name "event"
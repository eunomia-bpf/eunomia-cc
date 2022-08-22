# fix me

- make this and libbpf as a submodule and a standalone package
- use bpftools instead of some c templates
- clang -Xclang -ast-dump=json -fsyntax-only client.bpf.c > ast.json

# hard code now:

- BPF_MAP_TYPE_RINGBUF must be name with "rb"
- event struct should name "event"
- event should be in event.h, and ebpf in client.bpf.c
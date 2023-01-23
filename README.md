# The eBPF compile toolchain for eunomia-bpf

`eunomia-bpf` is a compilation framework and runtime library to build, distribute, dynamically load, and run CO-RE eBPF applications in multiple languages and WebAssembly.

It supports: 

- writing eBPF kernel code only (to build simple CO-RE libbpf eBPF applications)
- writing the kernel part in both BCC and libbpf styles
- writing eBPF userspace programs in multiple languages in a WASM module, and distributing it with simple JSON data or WASM OCI images. 

The runtime is based on libbpf only and provides CO-RE to BCC-style eBPF programs without depending on the LLVM library.

**The further development of this compiler toolchain will be move to [eunomia-bpf](https://github.com/eunomia-bpf/eunomia-bpf) main repository.**

# An eBPF compile template for ebpm

This repo use the similar structs as libbpf

see: https://github.com/eunomia-bpf/eunomia-bpf for details.

# Building

libbpf-bootstrap supports multiple build systems that do the same thing.
This serves as a cross reference for folks coming from different backgrounds.

## Install Dependencies

You will need `clang`, `libelf` and `zlib` to build the examples, package names may vary across distros.

On Ubuntu/Debian, you need:
```shell
$ apt install clang libelf1 libelf-dev zlib1g-dev
```

On CentOS/Fedora, you need:

```console
$ dnf install clang elfutils-libelf elfutils-libelf-devel zlib-devel
```

## Build

Makefile build:

```console
$ git submodule update --init --recursive       # check out libbpf
$ make
```

## build with you own ebpf code

just replaced `client.bpf.c` with you own ebpf code!

If you need:
- check the configs in `config.json`.
- declare your ring buffer output event in `event.h`, if you have it.

## Run with ecli

```console
$ git submodule update --init --recursive       # check
```

## container image

TODO: This will be used as a container image in the future.

## Github actions

TODO: use this as a github action.

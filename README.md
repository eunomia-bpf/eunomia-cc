# An eBPF compile template for ebpm

An compile set to help you focus on writing a single eBPF program in the kernel. Nothing more TODO!

The only file you will need to write is:

```console
your_program.bpf.c
your_program.h  # optional, if you want to use ringbuf to export events, can go with out it.
```

after that, simply run this:

```console
docker run -it -v/path/to/repo/:/src yunwei37/ebpm
```

you will get a `package.json` in your root dir. Just run:

```console
$ sudo ./ecli run package.json
```

to start it!

see: https://github.com/eunomia-bpf/eunomia-bpf for details.

## container image

simply run:

```console
docker run -it -v/path/to/repo/:/src yunwei37/ebpm
```

Or you can do that without a container, which is listed below:

## Github actions

TODO: use this as a github action.

# Building

This repo use the similar structs as libbpf-bootstrap.

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

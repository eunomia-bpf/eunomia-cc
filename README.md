# The eBPF compile toolchain for eunomia-bpf

An CO-RE compile set to help you focus on writing a single eBPF program in the kernel. Nothing more TODO!

- note this is not a template for new eunomia-bpf projects, You may find the [eunomia-bpf-template](https://github.com/eunomia-bpf/ebpm-template) there.
- This repo will focus on the compile of eBPF programs. For runtime, please see: [github.com/eunomia-bpf/eunomia-bpf](https://github.com/eunomia-bpf/eunomia-bpf)

## Usage

The only file you will need to write is:

```console
your_program.bpf.c
your_program.bpf.h  # optional, if you want to use ringbuf to export events, can go with out it.
```

after that, simply run this:

```console
docker run -it -v /path/to/repo/:/src yunwei37/ebpm:latest # use absolute path
```

you will get a `package.json` in your root dir. Just run:

```console
$ sudo ./ecli run package.json
```

to start it! you can download `ecli` tool from [eunomia-bpf/releases](https://github.com/eunomia-bpf/eunomia-bpf/releases), we have pre-build binaries for linux x86. Small and No dependencies, besides glibc and glibcxx. Or just run this:

```console
wget https://aka.pw/bpf-ecli -O ecli
chmod +x ecli
```

The ebpf compiled code can run on different kernel versions(CO-RE).
see: [github.com/eunomia-bpf/eunomia-bpf](https://github.com/eunomia-bpf/eunomia-bpf) for details.

## container image

simply run:

```console
docker run -it -v /path/to/repo/:/src yunwei37/ebpm
```

Or you can do that without a container, which is listed below:

## Github actions

Use this as a github action, to compile online: see [eunomia-bpf/ebpm-template)](https://github.com/eunomia-bpf/ebpm-template). Only three steps

1. use this repo as a github template: see [creating-a-repository-from-a-template](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template)
2. modify the `bootstrap.bpf.c`, commit it and wait for the workflow to stop
3. Run the `ecli` with remote url:

```console
$ sudo ./ecli run https://eunomia-bpf.github.io/ebpm-template/package.json
```

# Building

This repo use the similar structs as libbpf-bootstrap.

libbpf-bootstrap supports multiple build systems that do the same thing.
This serves as a cross reference for folks coming from different backgrounds.

## Install Dependencies

You will need `clang`, `libelf` and `zlib` to build the examples, package names may vary across distros.

On Ubuntu/Debian, you need:
```shell
$ apt install clang libelf1 libelf-dev zlib1g-dev llvm
```

On CentOS/Fedora, you need:

```console
$ dnf install clang elfutils-libelf elfutils-libelf-devel zlib-devel
```

## Build

Makefile build the toolchain:

```console
$ git submodule update --init --recursive       # check out libbpf
$ make
```

After the toolchain has been build, just run:

```console
$ cd ebpm-bootstrap
$ SOURCE_DIR=[you repo path] make build
```

to compile it.

## build with you own ebpf code

just replaced `client.bpf.c` with you own ebpf code!

If you need:
- check the configs in `config.json`.
- declare your ring buffer output event in `event.h`, if you have it.

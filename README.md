# The eBPF compile toolchain for eunomia-bpf

An CO-RE compile set to help you focus on writing a single eBPF program in the kernel. Nothing more TODO!

- note this is not a template for new eunomia-bpf projects, You may find the [eunomia-bpf-template](https://github.com/eunomia-bpf/ebpm-template) there.
- This repo will focus on the compile of eBPF programs. For runtime, please see: [github.com/eunomia-bpf/eunomia-bpf](https://github.com/eunomia-bpf/eunomia-bpf)

## Usage

The only file you will need to write is:

```shell
your_program.bpf.c
your_program.bpf.h  # optional, if you want to use ring buffer to export events
```

after that, simply run this:

```shell
$ docker run -it -v /path/to/repo/:/src yunwei37/ebpm:latest # use absolute path
```

you will get a `package.json` in your root dir. Just run:

```shell
$ sudo ./ecli run package.json
```

to start it! you can download `ecli` tool from [eunomia-bpf/releases](https://github.com/eunomia-bpf/eunomia-bpf/releases), we have pre-build binaries for linux x86. Small and No dependencies, besides glibc and glibcxx. Or just run this:

```shell
$ wget https://aka.pw/bpf-ecli -O ecli && chmod +x ecli
```

The ebpf compiled code can run on different kernel versions(CO-RE).
see: [github.com/eunomia-bpf/eunomia-bpf](https://github.com/eunomia-bpf/eunomia-bpf) for details.

## container image

simply run:

```shell
$ docker run -it -v /path/to/repo:/src yunwei37/ebpm
```

Or you can do that without a container, which is listed below:

## Github actions

Use this as a github action, to compile online: see [eunomia-bpf/ebpm-template)](https://github.com/eunomia-bpf/ebpm-template). Only three steps

1. use this repo as a github template: see [creating-a-repository-from-a-template](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template)
2. modify the `bootstrap.bpf.c`, commit it and wait for the workflow to stop
3. Run the `ecli` with remote url:

```shell
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
$ apt install clang libelf1 libelf-dev zlib1g-dev llvm python
```

On CentOS/Fedora, you need:

```shell
$ dnf install clang elfutils-libelf elfutils-libelf-devel zlib-devel
```

## Build locally

Makefile build the toolchain:

```shell
$ git submodule update --init --recursive       # check out libbpf
$ make
```

After the toolchain has been build, just run:

```shell
$ python ecc.py [you file to compile]
```

to compile it.

## Usage

1. We use the same c ebpf code as libbpf, so most libbpf ebpf c code can run without any modification.
2. Supported ebpf program types: `kprobe`, `tracepoint`, `fentry`, we will add more types in the future.
3. If you want to use ring buffer to export events, you need to add `your_program.bpf.h` to your repo, and
   define the export data type in it, the export data type should be a C `struct`, for example:

    ```c
    struct process_event {
        int pid;
        int ppid;
        unsigned exit_code;
        unsigned long long duration_ns;
        char comm[TASK_COMM_LEN];
        char filename[MAX_FILENAME_LEN];
        int exit_event;
    };
    ```

    The name and field types are not limited, but we will prefer use standard C types. If multiple struct
    exists in the header, we will use the first one. The feature is only enabled if we found a `BPF_MAP_TYPE_RINGBUF`
    map exists in the ebpf program.

## Road-map

- [ ] use lua for ebpf package load config
- [ ] add more ebpf program type support: `xdp`, `perf event` and `uprobe`
- [ ] add more possibilities from `libbpf`
- [ ] provide python, go and others sdk
- [ ] provide better support for old kernels

## License

MIT LICENSE
#!/bin/python
# the loader of eunomia-cc compile toolchain
import os
import argparse

# use to replace the build starter in make
# provide args to access

# 	$(Q)make compile
# 	$(Q)cp -f .output/package.json $(SOURCE_OUTPUT_PACKAGE_FILE)

def create_args():
    parser = argparse.ArgumentParser(description="eunomia-cc compile toolchain")
    parser.add_argument('file',type=str, default='*.bpf.c',
                    help='the ebpf source file to compile')
    parser.add_argument('-d','--dir', default='../', help='the dir to compile')
    parser.add_argument('-o','--output', default='package.json', help='the output file name')
    parser.add_argument('-i','--includes', default="../", help='include headers path')
    return parser.parse_args()

def main():
    args = create_args()

    # the input path
    output_path = os.path.join(args.dir, args.output)
    input_path = os.path.join(args.dir, args.file)
    input_headers_path = os.path.join(args.includes, "*.h")
    input_export_define_header = os.path.join(args.includes, "*.bpf.h")
    input_config_file = os.path.join(args.dir, "config.json")

    # the compile path
    compile_file_path = "./client.bpf.c"
    current_dir_path = "./"
    compile_export_define_header_path = "./event.h"
    compile_config_file_path = "./config.json"
    compile_output_path = ".output/package.json"

    os.system("make clean_cache")
    res = os.system("cp -f " + input_path + " " + compile_file_path)
    if res != 0:
        print("cannot read the source *.bpf.c file!")
        exit(1)
    os.system("cp -f " + input_headers_path + " " + current_dir_path)
    os.system("cp -f " + input_export_define_header + " " + compile_export_define_header_path)
    os.system("cp -f " + input_config_file + " " + compile_config_file_path)
    res = os.system("make compile")
    if res != 0:
        print("compile failed!")
        exit(0)
    os.system("cp -f " + compile_output_path + " " + output_path)


if __name__ == '__main__':
    main()

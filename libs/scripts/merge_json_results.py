import json

config_filename = "config.json"
ebpf_program_data = ".output/ebpf_program.json"

global_data = {}

with open(config_filename) as f:
    global_data = json.load(f)

with open(ebpf_program_data) as f:
    ebpf_data = json.load(f)
    global_data.update(ebpf_data)

print(json.dumps(global_data))

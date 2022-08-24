# add ringbuffer event type definition to json
import re
import json

import_filename = ".output/event_layout.txt"

json_data = {}
json_data['Fields'] = []

with open(import_filename) as f:
    line_num = 0
    while True:
        line = f.readline()
        line_num = line_num + 1
        # print(line_num, line)
        if not line:
            break
        if line == "":
            continue
        if line_num == 3:  # Type: struct event
            find = re.search(r"Type: struct (.*)$", line)
            if not find:
                print("Error: line 3 struct")
                break
            # print("Struct Name: ", find.group(1))
            json_data['Struct Name'] = find.group(1)
        elif line_num == 6:  # Size:1472
            find = re.search(r"Size:(\d*)$", line)
            if not find:
                print("Error: line 6 Size")
                break
            # print("Size: ", find.group(1))
            json_data['Size'] = find.group(1)
        elif line_num == 7:  # DataSize:1472
            find = re.search(r"DataSize:(\d*)$", line)
            if not find:
                print("Error: line 7 DataSize")
                break
            # print("DataSize: ", find.group(1))
            json_data['DataSize'] = find.group(1)
        elif line_num == 8:  # Alignment:64
            find = re.search(r"Alignment:(\d*)$", line)
            if not find:
                print("Error: line 8 Alignment")
                break
            # print("Alignment: ", find.group(1))
            json_data['Alignment'] = find.group(1)
        # FieldOffsets: [0, 32, 64, 96, 128, 192, 256, 384, 1408]
        elif line_num == 9:
            find = re.search(r"FieldOffsets: (.*)>", line)
            if not find:
                print("Error: line 9 FieldOffsets")
                break
            # print("FieldOffsets: ", find.group(1))
            json_data['FieldOffsets'] = json.loads(find.group(1))
        #   LLVMType:%struct.event = type { i32, i32, i32, i32, i64, i64, [16 x i8], [127 x i8], i32 }
        elif line.startswith("  LLVMType"):
            find = re.search(r"  LLVMType:.* = type \{ (.*) \}", line)
            if not find:
                print("Error: LLVMType")
                break
            # print("LLVMType: ", find.group(1))
            LLVMType = find.group(1).split(', ')
            json_data['LLVMType'] = LLVMType
        # FieldDecl 0x1af20c8 <line:12:2, col:6> col:6 pid 'int'
        else:
            find = re.search(r"FieldDecl .* <.*> col:\d+ (.*) '(.*)'", line)
            if not find:
                continue
            # print("FieldDecl: ", find.group(1), find.group(2))
            field_data = {}
            field_data['Name'], field_data['Type'] = find.group(
                1), find.group(2)
            json_data['Fields'].append(field_data)

# skip No export data
if json_data == {"Fields": []}:
    print("No export event data")
    exit(0)

# merge the types of LLVMType, FieldOffset and FieldDecl
assert(len(json_data['Fields']) == len(json_data['LLVMType']))
assert(len(json_data['Fields']) == len(json_data['FieldOffsets']))
for i in range(len(json_data['Fields'])):
    json_data['Fields'][i]['LLVMType'] = json_data['LLVMType'][i]
    json_data['Fields'][i]['FieldOffset'] = json_data['FieldOffsets'][i]
json_data.pop('LLVMType')
json_data.pop('FieldOffsets')

print(json.dumps(json_data, indent=4))

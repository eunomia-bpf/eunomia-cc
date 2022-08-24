#include "create_skel_json.h"

#include <argp.h>
#include <bpf/libbpf.h>
#include <signal.h>
#include <stdio.h>
#include <sys/resource.h>
#include <time.h>

#include "../.output/client.skel.h"
#include "base64_encode.h"

static cJSON *create_map_type(const char *name)
{
  if (strcmp(name, "rb") == 0)
  {
    cJSON *type = cJSON_CreateString("BPF_MAP_TYPE_RINGBUF");
    if (type == NULL)
    {
      return NULL;
    }
    return type;
  }

  if (strlen(name) > 6 && strncmp(name + strlen(name) - 6, "rodata", 6) == 0)
  {
    cJSON *type = cJSON_CreateString("RODATA");
    if (type == NULL)
    {
      return NULL;
    }
    return type;
  }
  cJSON *type = cJSON_CreateString("BPF_MAP_TYPE_HASH");
  if (type == NULL)
  {
    return NULL;
  }
  return type;
}

static cJSON *create_map_json(struct bpf_map_skeleton *bpf_map)
{
  if (!bpf_map)
  {
    return NULL;
  }
  cJSON *map = cJSON_CreateObject();
  if (map == NULL)
  {
    return NULL;
  }
  cJSON *name = cJSON_CreateString(bpf_map->name);
  if (name == NULL)
  {
    return NULL;
  }
  cJSON_AddItemToObject(map, "name", name);
  cJSON *type = create_map_type(bpf_map->name);
  if (type == NULL)
  {
    return NULL;
  }
  cJSON_AddItemToObject(map, "type", type);
  return map;
}

static cJSON *create_prog_json(struct bpf_prog_skeleton *bpf_prog)
{
  if (!bpf_prog)
  {
    return NULL;
  }
  cJSON *prog = cJSON_CreateObject();
  if (prog == NULL)
  {
    return NULL;
  }
  cJSON *name = cJSON_CreateString(bpf_prog->name);
  if (name == NULL)
  {
    return NULL;
  }
  cJSON_AddItemToObject(prog, "name", name);

  cJSON *type = cJSON_CreateString("BPF_PROG_TYPE_TRACEPOINT");
  if (type == NULL)
  {
    return NULL;
  }
  cJSON_AddItemToObject(prog, "type", type);
  return prog;
}


cJSON * create_skel_json(cJSON *config_json)
{
  if (!config_json) {
    return NULL;
  }
  struct client_bpf* obj = malloc(sizeof(struct client_bpf));
    if (!obj) {
        return NULL;
    }
  // TODO: this maybe unnecessary, use bpftool dump json instead

  if (client_bpf__create_skeleton(obj))
  {
    return NULL;
  }
  size_t out_len;
  cJSON *map = NULL;
  cJSON *maps = NULL;
  cJSON *prog = NULL;
  cJSON *progs = NULL;
  cJSON *data = NULL;
  cJSON *data_sz = NULL;
  unsigned char *base64_buffer = NULL;

  data_sz = cJSON_CreateNumber(obj->skeleton->data_sz);
  if (data_sz == NULL)
  {
    return NULL;
  }
  cJSON_AddItemToObject(config_json, "data_sz", data_sz);

  base64_buffer = base64_encode(obj->skeleton->data, obj->skeleton->data_sz, &out_len);
  data = cJSON_CreateString((const char *)base64_buffer);
  if (data == NULL)
  {
     return NULL;
  }
  cJSON_AddItemToObject(config_json, "data", data);
  free(base64_buffer);

  maps = cJSON_CreateArray();
  for (size_t i = 0; i < obj->skeleton->map_cnt; ++i)
  {
    map = create_map_json(&obj->skeleton->maps[i]);
    if (map == NULL)
    {
       return NULL;
    }
    cJSON_AddItemToArray(maps, map);
  }
  cJSON_AddItemToObject(config_json, "maps", maps);

  progs = cJSON_CreateArray();
  for (size_t i = 0; i < obj->skeleton->prog_cnt; ++i)
  {
    prog = create_prog_json(&obj->skeleton->progs[i]);
    if (map == NULL)
    {
       return NULL;
    }
    cJSON_AddItemToArray(progs, prog);
  }
  cJSON_AddItemToObject(config_json, "progs", progs);
  free(obj);
  return config_json;
}

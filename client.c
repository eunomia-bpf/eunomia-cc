// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <argp.h>
#include <bpf/libbpf.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>

#include "libs/cJSON.h"
#include "libs/create_skel_json.h"

const char *config_file_name = "config.json";

cJSON *parse_json_file(const char *file_name)
{
  FILE *f;
  long len;
  char *data;

  f = fopen(file_name, "rb");
  if (!f)
  {
    fprintf(stderr, "Failed to open config file %s\n", file_name);
    exit(1);
  }
  fseek(f, 0, SEEK_END);
  len = ftell(f);
  fseek(f, 0, SEEK_SET);
  data = (char *)malloc(len + 36);
  fread(data, 1, len, f);
  fclose(f);
  cJSON *result = cJSON_ParseWithLength(data, len);
  free(data);
  return result;
}

int main(int argc, char **argv)
{
  char *string;
  // TODO: this maybe unnecessary, use bpftools instead
  cJSON *config_json = parse_json_file(config_file_name);
  if (!config_json)
  {
    fprintf(stderr, "Failed to parse config file %s\n", config_file_name);
    exit(1);
  }
  config_json = create_skel_json(config_json);
  if (!config_json)
  {
    fprintf(stderr, "Failed to create skel json\n");
    exit(1);
  }
  string = cJSON_Print(config_json);
  if (string == NULL)
  {
    fprintf(stderr, "Failed to print monitor.\n");
  }
  printf("%s", string);

  cJSON_Delete(config_json);
  return 0;
}

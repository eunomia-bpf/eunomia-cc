// do not use this file
// FIX ME: this is for clang to dump AST
// do not use this file directly

#include "../event.h"

// make the compile not ignore event struct
void* use_event(struct event *e)
{
  return e;
}
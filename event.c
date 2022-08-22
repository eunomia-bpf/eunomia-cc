// do not use
// FIX ME: this is for clang to dump AST
// do not use this file directly

#include "event.h"

// make the compile not ignore event 
void* use_event(struct event *e)
{
  return e;
}
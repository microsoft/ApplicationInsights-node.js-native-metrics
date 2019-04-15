#include <nan.h>

#include "GcProfiler.hh"
#include "LoopProfiler.hh"
#include "ResourceProfiler.hh"

namespace ai {

NAN_MODULE_INIT(Init) {
  Nan::HandleScope scope;

  GcProfiler::Init(target);
  LoopProfiler::Init(target);
  ResourceProfiler::Init(target);
}

NODE_MODULE(native_metrics, Init)
}  // namespace ai

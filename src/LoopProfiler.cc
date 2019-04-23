#include <uv.h>
#include <algorithm>

#include "LoopProfiler.hh"

namespace ai {

const uint64_t SEC_TO_MICRO = 1000000;

/**
 * Get loop usage time in us
 */
uint64_t _getUsage() {
  uv_rusage_t usage;
  uv_getrusage(&usage);

  const uint64_t usageUs =
      ((usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) * SEC_TO_MICRO) +
      (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec);

  return usageUs;
}

/**
 * Grab latest data from profiler
 */
NAN_METHOD(LoopProfiler::Data) {
  Nan::HandleScope scope;
  auto self = LoopProfiler::Unwrap<LoopProfiler>(info.This());
  auto results = Nan::New<v8::Object>();

  Nan::Set(results, Nan::New("loopUsage").ToLocalChecked(),
           self->_tickUsage.toJSON());
  info.GetReturnValue().Set(results);
  self->_tickUsage.reset();
}

LoopProfiler::LoopProfiler() {
  _thisTickUsage = _getUsage();
  uv_check_init(uv_default_loop(), &_uvCheckHandle);
  uv_unref((uv_handle_t*)&_uvCheckHandle);
  _uvCheckHandle.data = (void*)this;
}

/**
 * Start collecting event loop info -- on uv_check_start
 */
void LoopProfiler::_uvCheckStartCB(uv_check_t* handle) {
  auto self = (LoopProfiler*)handle->data;
  const auto usage = _getUsage();

  self->_tickUsage += usage - self->_thisTickUsage;
  self->_thisTickUsage = usage;
}

}  // namespace ai

#pragma once

#include <nan.h>

#include "Metric.hh"
namespace ai {

#define LOOP_PROFILER "LoopProfiler"
class LoopProfiler : public Nan::ObjectWrap {
 public:
  LoopProfiler();

  static NAN_METHOD(New) {
    auto obj = new LoopProfiler();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  }

  static NAN_MODULE_INIT(Init) {
    auto inst = Nan::New<v8::FunctionTemplate>(New);
    inst->SetClassName(Nan::New(LOOP_PROFILER).ToLocalChecked());
    inst->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(inst, "start", Start);
    SetPrototypeMethod(inst, "stop", Stop);
    SetPrototypeMethod(inst, "data", Data);

    constructor().Reset(Nan::GetFunction(inst).ToLocalChecked());
    Nan::Set(target, Nan::New(LOOP_PROFILER).ToLocalChecked(),
             Nan::GetFunction(inst).ToLocalChecked());
  }

  static NAN_METHOD(Start) {
    auto self = LoopProfiler::Unwrap<LoopProfiler>(info.This());
    uv_check_start(&self->_uvCheckHandle, &LoopProfiler::_uvCheckStartCB);
  }

  static NAN_METHOD(Stop) {
    auto self = LoopProfiler::Unwrap<LoopProfiler>(info.This());
    uv_check_stop(&self->_uvCheckHandle);
  }

  static NAN_METHOD(Data);

 private:
  static Nan::Persistent<v8::Function>& constructor() {
    static Nan::Persistent<v8::Function> _newJsInst;
    return _newJsInst;
  }

  static void _uvCheckStartCB(uv_check_t* handle);

  uv_check_t _uvCheckHandle;
  uint64_t _thisTickUsage;
  Metric<uint64_t> _tickUsage;
};
#undef LOOP_PROFILER

}  // namespace ai

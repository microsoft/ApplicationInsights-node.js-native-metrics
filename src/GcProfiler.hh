#pragma once

#include <nan.h>
#include <map>

#include "Metric.hh"

namespace ai {

#define GC_PROFILER "GcProfiler"
class GcProfiler : public Nan::ObjectWrap {
 public:
  static NAN_METHOD(New);
  static NAN_MODULE_INIT(Init) {
    auto inst = Nan::New<v8::FunctionTemplate>(New);
    inst->SetClassName(Nan::New(GC_PROFILER).ToLocalChecked());
    inst->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(inst, "data", Data);
    SetPrototypeMethod(inst, "start", Start);
    SetPrototypeMethod(inst, "stop", Stop);

    constructor().Reset(Nan::GetFunction(inst).ToLocalChecked());
    Nan::Set(target, Nan::New(GC_PROFILER).ToLocalChecked(),
             Nan::GetFunction(inst).ToLocalChecked());
  }
  static NAN_METHOD(Data);
  static NAN_METHOD(Start) { _start(); }
  static NAN_METHOD(Stop) { _stop(); }

  GcProfiler() {
    _startTime = uv_hrtime();
    _self = this;
  }
  ~GcProfiler() {
    _stop();
    _self = NULL;
  }

 private:
  static GcProfiler* _self;

  static void _start() {
    Nan::AddGCPrologueCallback(_aiGcPrologueCB);
    Nan::AddGCEpilogueCallback(_aiGcEpilogueCB);
  }

  static void _stop() {
    Nan::RemoveGCPrologueCallback(_aiGcPrologueCB);
    Nan::RemoveGCEpilogueCallback(_aiGcEpilogueCB);
  }

  static NAN_GC_CALLBACK(_aiGcPrologueCB) {
    // GC is starting, starting measurements
    if (GcProfiler::_self) {
      GcProfiler::_self->_gcStart();
    }
  }

  static NAN_GC_CALLBACK(_aiGcEpilogueCB) {
    // GC is finished, wrap up measurements
    if (GcProfiler::_self) {
      GcProfiler::_self->_gcDone(type);
    }
  }

  static Nan::Persistent<v8::Function>& constructor() {
    static Nan::Persistent<v8::Function> _newJsInst;
    return _newJsInst;
  }

  void _gcStart() { _startTime = uv_hrtime(); }
  void _gcDone(const v8::GCType gcType);

  uint64_t _startTime;  // result of uv_hrtime
  std::map<v8::GCType, Metric<double>> _metrics;
};
#undef GC_PROFILER

}  // namespace ai

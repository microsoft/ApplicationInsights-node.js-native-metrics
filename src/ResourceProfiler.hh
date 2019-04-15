#pragma once

#include <nan.h>

namespace ai {

#define RESOURCE_PROFILER "ResourceProfiler"
class ResourceProfiler : public Nan::ObjectWrap {
 public:
  static NAN_METHOD(New) {
    auto obj = new ResourceProfiler();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  }

  static NAN_MODULE_INIT(Init) {
    auto profiler = Nan::New<v8::FunctionTemplate>(New);

    profiler->SetClassName(Nan::New(RESOURCE_PROFILER).ToLocalChecked());
    profiler->InstanceTemplate()->SetInternalFieldCount(1);
    SetPrototypeMethod(profiler, "read", Read);
    constructor().Reset(Nan::GetFunction(profiler).ToLocalChecked());
    Nan::Set(target, Nan::New(RESOURCE_PROFILER).ToLocalChecked(),
             Nan::GetFunction(profiler).ToLocalChecked());
  }

  static NAN_METHOD(Read);

  ResourceProfiler() { std::memset(&_usagePrevious, 0, sizeof(uv_rusage_t)); }

 private:
  static Nan::Persistent<v8::Function>& constructor() {
    static Nan::Persistent<v8::Function> _newJsInst;
    return _newJsInst;
  }

  void _read();

  v8::Local<v8::Object> _toJSON(const uv_rusage_t& usage);

  uv_rusage_t _usageDiff;
  uv_rusage_t _usagePrevious;
};
#undef RESOURCE_PROFILER

}  // namespace ai

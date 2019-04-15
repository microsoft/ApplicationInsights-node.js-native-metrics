#pragma once

#include <nan.h>
#include <uv.h>

#include "ResourceProfiler.hh"

namespace ai {

NAN_METHOD(ResourceProfiler::Read) {
  Nan::HandleScope scope;
  auto self = ResourceProfiler::Unwrap<ResourceProfiler>(info.This());
  auto results = Nan::New<v8::Object>();

  self->_read();
  Nan::Set(results, Nan::New("current").ToLocalChecked(),
           self->_toJSON(self->_usagePrevious));
  Nan::Set(results, Nan::New("diff").ToLocalChecked(),
           self->_toJSON(self->_usageDiff));

  info.GetReturnValue().Set(results);
}

void ResourceProfiler::_read() {
  uv_rusage_t _thisUsage;
  uv_getrusage(&_thisUsage);

  _usageDiff.ru_utime.tv_sec  = _thisUsage.ru_utime.tv_sec  - _usagePrevious.ru_utime.tv_sec;
  _usageDiff.ru_utime.tv_usec = _thisUsage.ru_utime.tv_usec - _usagePrevious.ru_utime.tv_usec;
  _usageDiff.ru_stime.tv_sec  = _thisUsage.ru_stime.tv_sec  - _usagePrevious.ru_stime.tv_sec;
  _usageDiff.ru_stime.tv_usec = _thisUsage.ru_stime.tv_usec - _usagePrevious.ru_stime.tv_usec;

  _usageDiff.ru_msgsnd    = _thisUsage.ru_msgsnd    - _usagePrevious.ru_msgsnd;
  _usageDiff.ru_msgrcv    = _thisUsage.ru_msgrcv    - _usagePrevious.ru_msgrcv;
  _usageDiff.ru_nsignals  = _thisUsage.ru_nsignals  - _usagePrevious.ru_nsignals;

  _usageDiff.ru_inblock = _thisUsage.ru_inblock - _usagePrevious.ru_inblock;
  _usageDiff.ru_oublock = _thisUsage.ru_oublock - _usagePrevious.ru_oublock;

  _usageDiff.ru_maxrss = _thisUsage.ru_maxrss - _usagePrevious.ru_maxrss;
  _usageDiff.ru_ixrss  = _thisUsage.ru_ixrss  - _usagePrevious.ru_ixrss;
  _usageDiff.ru_idrss  = _thisUsage.ru_idrss  - _usagePrevious.ru_idrss;
  _usageDiff.ru_isrss  = _thisUsage.ru_isrss  - _usagePrevious.ru_isrss;

  _usageDiff.ru_nvcsw   = _thisUsage.ru_nvcsw   - _usagePrevious.ru_nvcsw;
  _usageDiff.ru_nivcsw  = _thisUsage.ru_nivcsw  - _usagePrevious.ru_nivcsw;

  _usageDiff.ru_minflt = _thisUsage.ru_minflt - _usagePrevious.ru_minflt;
  _usageDiff.ru_majflt = _thisUsage.ru_majflt - _usagePrevious.ru_majflt;

  _usageDiff.ru_nswap = _thisUsage.ru_nswap - _usagePrevious.ru_nswap;

  std::memcpy(&_usagePrevious, &_thisUsage, sizeof(uv_rusage_t));
}

v8::Local<v8::Object> ResourceProfiler::_toJSON(const uv_rusage_t& usage) {
  auto resJson = Nan::New<v8::Object>();

  double userTime = ((double)(usage.ru_utime.tv_sec * 1e3) +
                  (double)(usage.ru_utime.tv_usec / 1e3));
  double sysTime = ((double)(usage.ru_stime.tv_sec * 1e3) +
                  (double)(usage.ru_stime.tv_usec / 1e3));
  Nan::Set(resJson, Nan::New("ru_utime").ToLocalChecked(), Nan::New<v8::Number>((double)userTime));
  Nan::Set(resJson, Nan::New("ru_stime").ToLocalChecked(), Nan::New<v8::Number>((double)sysTime));

  Nan::Set(resJson, Nan::New("ru_msgsnd").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_msgsnd));
  Nan::Set(resJson, Nan::New("ru_msgrcv").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_msgrcv));
  Nan::Set(resJson, Nan::New("ru_nsignals").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_nsignals));

  Nan::Set(resJson, Nan::New("ru_inblock").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_inblock));
  Nan::Set(resJson, Nan::New("ru_oublock").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_oublock));

  Nan::Set(resJson, Nan::New("ru_maxrss").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_maxrss));
  Nan::Set(resJson, Nan::New("ru_ixrss").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_ixrss));
  Nan::Set(resJson, Nan::New("ru_idrss").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_idrss));
  Nan::Set(resJson, Nan::New("ru_isrss").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_isrss));

  Nan::Set(resJson, Nan::New("ru_nvcsw").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_nvcsw));
  Nan::Set(resJson, Nan::New("ru_nivcsw").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_nivcsw));

  Nan::Set(resJson, Nan::New("ru_minflt").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_minflt));
  Nan::Set(resJson, Nan::New("ru_majflt").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_majflt));

  Nan::Set(resJson, Nan::New("ru_nswap").ToLocalChecked(), Nan::New<v8::Number>((double)usage.ru_nswap));

  return resJson;
}

}  // namespace ai

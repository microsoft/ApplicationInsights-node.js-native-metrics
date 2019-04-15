#include "GcProfiler.hh"

namespace ai {

const double MS_TO_NS = 1.0e6;

GcProfiler* GcProfiler::_self = NULL;

NAN_METHOD(GcProfiler::New) {
  if (_self != NULL) {
    return Nan::ThrowError("GcProfiler already exists");
  }

  auto obj = new GcProfiler();
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(GcProfiler::Data) {
  Nan::HandleScope scope;
  auto _this = GcProfiler::Unwrap<GcProfiler>(info.This());
  auto resData = Nan::New<v8::Object>();

  for (auto& metrics : _this->_metrics) {
    Nan::Set(resData, Nan::New(metrics.first), metrics.second.toJSON());
    metrics.second.reset();
  }

  info.GetReturnValue().Set(resData);
}

void GcProfiler::_gcDone(const v8::GCType gcType) {
  auto durationHr = uv_hrtime() - _startTime;
  _metrics[gcType] += (durationHr / MS_TO_NS);
}

}  // namespace ai

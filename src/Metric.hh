#pragma once

#include <nan.h>
#include <algorithm>

namespace ai {

template <typename T>
class Metric {
 public:
  Metric() { _total = _min = _max = _count = (T)0; }
  void reset() { _total = _min = _max = _count = (T)0; }

  Metric& operator+=(const T& val) {
    if (_count > 0) {
      _min = std::min(_min, val);
      _max = std::max(_max, val);
    } else {
      _min = _max = val;
    }

    _total += val;
    _count++;

    return *this;
  }

  v8::Local<v8::Object> toJSON() const {
    auto resJson = Nan::New<v8::Object>();

    Nan::Set(resJson, Nan::New("total").ToLocalChecked(),
             Nan::New<v8::Number>(total()));
    Nan::Set(resJson, Nan::New("min").ToLocalChecked(),
             Nan::New<v8::Number>(min()));
    Nan::Set(resJson, Nan::New("max").ToLocalChecked(),
             Nan::New<v8::Number>(max()));
    Nan::Set(resJson, Nan::New("count").ToLocalChecked(),
             Nan::New<v8::Number>(count()));

    return resJson;
  }

  const T& total() const { return _total; }
  const T& min() const { return _min; }
  const T& max() const { return _max; }
  const T& count() const { return _count; }

 private:
  T _total;
  T _min;
  T _max;
  T _count;
};

}  // namespace ai

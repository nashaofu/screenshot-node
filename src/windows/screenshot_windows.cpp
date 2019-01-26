#include <napi.h>
#include <iostream>
#include "prtscn_windows.h"

Napi::Value getScreenshotSync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 5)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsNumber())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  int x = info[0].As<Napi::Number>().Int32Value();
  int y = info[1].As<Napi::Number>().Int32Value();
  int width = info[2].As<Napi::Number>().Int32Value();
  int height = info[3].As<Napi::Number>().Int32Value();
  const char* str = info[4].As<Napi::String>().Utf8Value().data();
  Napi::Function cb = info[5].As<Napi::Function>();

//   IData rawData = getScreen(x, y, width, height);
	getScreen(x, y, width, height, str);

//   std::cout<<sizeof rawData.byte <<std::endl;
//   Napi::Value buf = Napi::Buffer<UInt8>::New(env, rawData.byte, rawData.length);
  cb.Call(env.Global(), {});
  return env.Null();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "getScreenshotSync"), Napi::Function::New(env, getScreenshotSync));
  return exports;
}

NODE_API_MODULE(addon, Init)

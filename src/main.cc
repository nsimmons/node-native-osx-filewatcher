#include <v8.h>
#include <node.h>
#include "fswait.h"

using namespace v8;

extern "C" {
  void watchFiles(const char *path, void (*cb)(int, char **));
}

static Handle<Function> cb;

void callback(int length, char **paths) {
  Handle<String> pathsToWatch(String::New(paths[0]));
  Handle<Value> argv[] = { pathsToWatch };
  cb->Call(Context::GetCurrent()->Global(), 1, argv);
}

Handle<Value> check(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 2) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsString() || !args[1]->IsFunction()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments. Expected string and callback")));
    return scope.Close(Undefined());
  }

  String::Utf8Value pathsToWatch(args[0]);
  cb = Handle<Function>::Cast(args[1]);

  watchFiles(*pathsToWatch, callback);
  return scope.Close(Undefined());
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "check", check);
}

NODE_MODULE(fswait, init)


















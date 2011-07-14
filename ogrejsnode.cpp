
#include <ogrejs.h>
#include <v8.h>
#include <node.h>

using namespace v8 ;

extern "C" {
  void init (Handle<Object> target)
  {
    initOgreJS(target);
  }

}
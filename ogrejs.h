
#ifndef OGREJS_H
#define OGREJS_H

#include <v8.h>

using namespace v8 ;

extern "C" {

void initOgreJS (Handle<Object> target) ;
}

#endif
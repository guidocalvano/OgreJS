#if !defined (V8_CONVERT_GLOB_HPP_INCLUDED)
#define V8_CONVERT_GLOB_HPP_INCLUDED
#include <v8.h>

namespace v8 { namespace convert {
    void SetupGlobBindings( v8::Handle<v8::Object> dest );
    
}} // namespaces
#endif /* V8_CONVERT_GLOB_HPP_INCLUDED */

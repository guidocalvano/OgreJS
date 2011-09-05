
#include <v8.h>
#include <node_object_wrap.h>



template < class UnwrapType >
class FixedTypeObjectWrap : public node::ObjectWrap
	{
	public:
	
	 static UnwrapType* unwrapFixedType( Local< Object > boundObject )
		{ return node::ObjectWrap::Unwrap<UnwrapType>( boundObject ) ;}
	
	} ;
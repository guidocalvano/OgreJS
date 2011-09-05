#include <EventEmitterJS.h>

#include <V8Toolkit.h>

v8::Persistent<v8::FunctionTemplate> EventEmitterJS:: prototypeTemplate ;

void EventEmitterJS :: init( )
	{
		
	 v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	 prototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 prototypeTemplate->SetClassName(v8::String::NewSymbol("EventEmitter"));

	v8::Handle<v8::ObjectTemplate> prototype = prototypeTemplate-> PrototypeTemplate() ;
	 
		 V8Toolkit:: setPrototypeTemplateFunction( prototype, "on", "function( event, func )		\
			{									\
			 this.emit( 'newListener', event, func ) ; 				\
												\
			 if( this.event[ event ] == undefined ) 				\
				this.event[ event ] = [ func ] ; 				\
			 else 									\
				this.event[ event ].push( func ) ; 				\
			}" ) ;
		 V8Toolkit:: setPrototypeTemplateFunction( prototype, "addListener", "function( event, func ){ return this.on( event, func ) ; }" ) ;

		 V8Toolkit:: setPrototypeTemplateFunction( prototype, "removeListener", 
			"function( event, func )					\
				{							\
				 for( var i in this.event[ event ] )			\
					{						\
					 if( this.event[event][ i ] == func )		\
						{					\
						 this.event[event].splice( i, 1 ) ;	\
						 return true ;				\
						}					\
					} 						\
				 return false ;						\
				}" 
			) ;

		 V8Toolkit:: setPrototypeTemplateFunction( prototype, "once", "function( event, func )	\
			{									\
			 if( this.onceFunc[event] == undefined ) this.onceFunc[event]=[] ;	\
												\
			 this.onceFunc[event][ func ] = true ;					\
												\
			 this.on( event, func ) ;						\
			}" ) ;


		 V8Toolkit:: setPrototypeTemplateFunction( prototype, "removeAllListeners", "function( event ){ this.event[ event ] = [] ; }" ) ;

		 V8Toolkit:: setPrototypeTemplateFunction( prototype, "listeners", "function( event ){ if( this.event[ event ] == undefined ) return [] ; else return this.event[ event ] ; }" ) ;


		 V8Toolkit:: setPrototypeTemplateFunction( prototype, "emit", 
			"function( event )								\
				{ 									\
				 var removeThese = [] ;							\
													\
				 if( this.event[ event ] == undefined ) 				\
					return ; 							\
				 else 									\
					{								\
					 var args = Array.prototype.slice.call(arguments);		\
					 var eventArgs = args.slice( 1 ) ;				\
					 for( var i in this.event[ event ] )				\
						{							\
						 this.event[ event ][ i ].apply( null, eventArgs ) ;	\
													\
					 	 if( this.onceFunc[event] != undefined && this.onceFunc[ event ][ this.event[ event ][ i ] ] == 1) \
							{						\
							 removeThese.push( this.event[ event ][ i ] ) ;	\
							 this.onceFunc[event].splice(  this.event[ event ][ i ], 1 ) ;\
							}						\
						}							\
				 	}								\
				 var removeThis ;  							\
				 while( removeThese.length > 0 )					\
					{								\
					 removeThis = removeThese.pop() ;				\
													\
					 this.removeListener( event, removeThis ) ;			\
					}								\
				}" 

		) ;
		
	}
	

 v8::Handle<v8::Value> EventEmitterJS:: New( const v8::Arguments& args ) 
	{
		printf( "emitter new \n") ;	 
		
	 args.This()-> Set( v8::String::New( "event" ), v8::Object::New() ) ;
	 args.This()-> Set( v8::String::New( "onceFunc" ), v8::Object::New() ) ;
	
	 return args.This() ;
	}

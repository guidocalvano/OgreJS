#ifndef WIDGET_JS_H
#define WIDGET_JS_H




#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <node_object_wrap.h>
#include <MyGuiEventEmitterJS.h>


class WidgetJS : public  MyGuiEventEmitterJS
    {
    public:
	 static v8::Persistent<v8::FunctionTemplate> widgetPrototypeTemplate ;  

     MyGUI::Widget* widget ;
	
	
     static void init( v8::Handle< v8::Object > target ) ;

	 template< class ChildType >
	 static void addSpatialFunctions( v8::Handle<v8::FunctionTemplate> t ) 
		{
		 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setPosition", setPositionBind<ChildType> ) ;
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setSize", setSizeBind<ChildType> ) ;
		}
		
	
	 template< class ChildType >
	 static void addCreateFunctions( v8::Handle<v8::FunctionTemplate> t ) 
		{
		 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "createStaticText", createStaticTextBind<ChildType> ) ;
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "createButton", createButtonBind<ChildType> ) ;
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "createPanel", createPanelBind<ChildType> ) ;
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "createEdit", createEditBind<ChildType> ) ;
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "createWindow", createWindowBind<ChildType> ) ;
	
		}
    

	 template< class ChildType >
	 static void addFocusFunctions( v8::Handle<v8::FunctionTemplate> t ) 
		{
		 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "focus", focusBind<ChildType> ) ;
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "blur",  blurBind<ChildType>  ) ;
		}    

     static v8::Handle<v8::Value> New( const v8::Arguments& args )  ;
     
     static v8::Handle<v8::Value> NewFromWidgetCpp( MyGUI::Widget* widget ) ;

	 static v8::Handle<v8::Value> destroy( const v8::Arguments& args ) ;


     static v8::Handle<v8::Value> focusConvert( WidgetJS* bound, const v8::Arguments& args ) ;

	 template< class ChildType >
     static v8::Handle<v8::Value> focusBind( const v8::Arguments& args )
		{
		 WidgetJS* bound = (WidgetJS*) node::ObjectWrap::Unwrap<ChildType>( args.This() ) ;

		 return focusConvert( bound, args ) ;			
		}


     static v8::Handle<v8::Value> blurConvert( WidgetJS* bound, const v8::Arguments& args ) ;

	 template< class ChildType >
     static v8::Handle<v8::Value> blurBind( const v8::Arguments& args )
		{
		 WidgetJS* bound = (WidgetJS*) node::ObjectWrap::Unwrap<ChildType>( args.This() ) ;

		 return blurConvert( bound, args ) ;			
		}


     static v8::Handle<v8::Value> createStaticTextConvert( WidgetJS* bound, const v8::Arguments& args ) ;

	 template< class ChildType >
     static v8::Handle<v8::Value> createStaticTextBind( const v8::Arguments& args ) 
		{
		 WidgetJS* bound = (WidgetJS*) node::ObjectWrap::Unwrap<ChildType>( args.This() ) ;

		 return createStaticTextConvert( bound, args ) ;
		}


     static v8::Handle<v8::Value> createButtonConvert( WidgetJS* bound, const v8::Arguments& args ) ;

	 template< class ChildType >
     static v8::Handle<v8::Value> createButtonBind( const v8::Arguments& args ) 
		{
		 WidgetJS* bound = (WidgetJS*) node::ObjectWrap::Unwrap<ChildType>( args.This() ) ;
		
		 return createButtonConvert( bound, args ) ;
		}
		

     static v8::Handle<v8::Value> createEditConvert( WidgetJS* bound, const v8::Arguments& args ) ;

	 template< class ChildType >
     static v8::Handle<v8::Value> createEditBind( const v8::Arguments& args ) 
		{
		 WidgetJS* bound = (WidgetJS*) node::ObjectWrap::Unwrap<ChildType>( args.This() ) ;

		 return createEditConvert( bound, args ) ;
		}
		

     static v8::Handle<v8::Value> createPanelConvert( WidgetJS* bound, const v8::Arguments& args ) ;

	 template< class ChildType >
     static v8::Handle<v8::Value> createPanelBind( const v8::Arguments& args )
		{
		 WidgetJS* bound = (WidgetJS*) node::ObjectWrap::Unwrap<ChildType>( args.This() ) ;
		
		 return createPanelConvert( bound, args ) ;			
		}


     static v8::Handle<v8::Value> createWindowConvert( WidgetJS* bound, const v8::Arguments& args ) ;

	 template< class ChildType >
     static v8::Handle<v8::Value> createWindowBind( const v8::Arguments& args )
		{
		 WidgetJS* bound = (WidgetJS*) node::ObjectWrap::Unwrap<ChildType>( args.This() ) ;

		 return createWindowConvert( bound, args ) ;			
		}


	 static v8::Handle<v8::Value> setPositionConvert( WidgetJS* bound, const v8::Arguments& args ) ;

	 template< class ChildType >
	 static v8::Handle<v8::Value> setPositionBind( const v8::Arguments& args ) 
		{
		 WidgetJS* bound = (WidgetJS*) node::ObjectWrap::Unwrap<ChildType>( args.This() ) ;
		
		 return setPositionConvert( bound, args ) ;						
		}

     static v8::Handle<v8::Value> setSizeConvert( WidgetJS* bound, const v8::Arguments& args ) ;

	 template< class ChildType >
     static v8::Handle<v8::Value> setSizeBind( const v8::Arguments& args ) 
		{
		 WidgetJS* bound = (WidgetJS*) node::ObjectWrap::Unwrap<ChildType>( args.This() ) ;

		 return setSizeConvert( bound, args ) ;						
		}
    } ;
    
#endif
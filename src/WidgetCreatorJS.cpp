
#include <WidgetCreatorJS.h>


class WidgetJS ;


      void WidgetCreatorJS:: addMethodsToPrototypeTemplate( v8::Persistent<v8::FunctionTemplate> prototypeTemplate ) 
        {
         NODE_SET_PROTOTYPE_METHOD_BORROWED( prototypeTemplate, "createButton", createButton ) ;
         NODE_SET_PROTOTYPE_METHOD_BORROWED( prototypeTemplate, "createWidget", createWidget ) ;

        } 
        
        
      v8::Handle<v8::Value> WidgetCreatorJS:: createButton( const v8::Arguments& args )
          {
           WidgetCreatorJS* widgetCreatorJS = node::ObjectWrap::Unwrap<WidgetCreatorJS>( args.This() ) ;

           MyGUI::Widget* creator = widgetCreatorJS-> widgetCreator ;


           MyGUI::ButtonPtr buttonPtr = creator-> createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main") ;
      
           v8::Handle< v8::Value> buttonObject = ButtonJS::NewFromButtonCpp( buttonPtr ) ;
      
           return buttonObject ;
          }

      v8::Handle<v8::Value> WidgetCreatorJS:: createWidget( const v8::Arguments& args )
          {
           WidgetCreatorJS* widgetCreatorJS = node::ObjectWrap::Unwrap<WidgetCreatorJS >( args.This() ) ;
    
           MyGUI::WidgetPtr widgetPtr = widgetCreatorJS-> widgetCreator-> createWidget<MyGUI::Widget>("Widget", 10, 10, 300, 26, MyGUI::Align::Default, "Main") ;
          
           v8::Handle< v8::Value> widgetObject = WidgetJS::NewFromWidgetCpp( widgetPtr ) ;
          
           return widgetObject ;
          }


/* del
void WidgetCreatorJS:: addMethodsToPrototypeTemplate( v8::Handle<v8::FunctionTemplate> prototypeTemplate )
    {
   	NODE_SET_PROTOTYPE_METHOD_BORROWED( prototypeTemplate, "createButton", createButton ) ;
    } 
     
     
template <class WidgetCreator>
v8::Handle<v8::Value> WidgetCreatorJS<WidgetCreator>:: createButton( const v8::Arguments& args ) 
     {
      WidgetCreator* widgetCreator = node::ObjectWrap::Unwrap<WidgetCreator>( args.This() ) ;

      MyGUI::ButtonPtr buttonPtr = widgetCreator-> createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main") ;
      
      v8::Handle< v8::Object> buttonObject = ButtonJS::NewFromButtonCpp( buttonPtr ) ;
      
      return buttonObject ;
     }


template <class WidgetCreator>     
v8::Handle<v8::Value> WidgetCreatorJS<WidgetCreator>:: createWidget( const v8::Arguments& args ) 
     {
      WidgetCreator* widgetCreator = node::ObjectWrap::Unwrap<WidgetCreator>( args.This() ) ;

      MyGUI::WidgetPtr widgetPtr = widgetCreator-> createWidget<MyGUI::Widget>("Widget", 10, 10, 300, 26, MyGUI::Align::Default, "Main") ;
      
      v8::Handle< v8::Object> widgetObject = ButtonJS::NewFromButtonCpp( widgetPtr ) ;
      
      return widgetObject ;
     }
*/
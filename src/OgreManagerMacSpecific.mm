#import <AppDelegate.h>


void OgreManager :: initPlatform()
	{
	 NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
         NSApplicationLoad();

    	 mAppDelegate = [[AppDelegate alloc] init];
	
    	 [NSApp setDelegate:mAppDelegate];

	 [NSApp finishLaunching];

 	 [NSApp activateIgnoringOtherApps:YES];  // TODO(deanm): Do we want this?
 	 [NSApp setWindowsNeedUpdate:YES];


         while (true)
 		{
   		 NSAutoreleasePool* pool = [NSAutoreleasePool new];
   
	   	 // TODO(deanm): Fix loop integration with newest version of Node.
   		 double next_waittime = 0.01;
   		 NSDate* next_date = [NSDate dateWithTimeIntervalSinceNow:next_waittime];
   		 // printf("Running a loop iteration with timeout %f\n", next_waittime);
   		 NSEvent* event = [NSApp nextEventMatchingMask:NSAnyEventMask
                            untilDate:[NSDate distantPast]
                            inMode:NSDefaultRunLoopMode // kCFRunLoopDefaultMode
                            dequeue:YES];

   		 if (event != nil) 
			{  // event is nil on a timeout.
      
			 // NSLog(@"Event: %@\n", event);
      			 [event retain];
      			 [NSApp sendEvent:event];
      			 [event release];
      			 [pool drain];
		    	}
    		 else 
			{
			 break ;
       			[pool drain];

			}
  		}

	
	 return ;
	}


void OgreManager :: pumpGUIEventQueue()
	{
        while (true)
 		{
   		 NSAutoreleasePool* pool = [NSAutoreleasePool new];
   
	   	 // TODO(deanm): Fix loop integration with newest version of Node.
   		 double next_waittime = 0.01;
   		 NSDate* next_date = [NSDate dateWithTimeIntervalSinceNow:next_waittime];
   		 // printf("Running a loop iteration with timeout %f\n", next_waittime);
   		 NSEvent* event = [NSApp nextEventMatchingMask:NSAnyEventMask
                            untilDate:[NSDate distantPast]
                            inMode:NSDefaultRunLoopMode // kCFRunLoopDefaultMode
                            dequeue:YES];

   		 if (event != nil) 
			{  // event is nil on a timeout.
      
			 // NSLog(@"Event: %@\n", event);
      			 [event retain];
      			 [NSApp sendEvent:event];
      			 [event release];
      			 [pool drain];
		    	}
    		 else 
			{
			 break ;
       			[pool drain];

			}
  		}

	
	 return ;
	}


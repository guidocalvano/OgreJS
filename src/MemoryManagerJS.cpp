// #include <sys/time.h>
// #include <sys/resource.h>


#include <MemoryManagerJS.h>

#include <mach/task.h>
#include <mach/mach_init.h>
#include <mach/task_policy.h>
// #include <mach/sched.h>

/*
#include <mach/vm_statistics.h>
#include <mach/mach_types.h> 
#include <mach/mach_init.h>
#include <mach/mach_host.h>
*/


MemoryManagerJS* MemoryManagerJS:: singleton = NULL ;


void MemoryManagerJS:: init( v8::Handle<v8::Object> obj )
	{
	 singleton = new MemoryManagerJS() ;
	
	 v8::Handle< v8::FunctionTemplate > f = v8::FunctionTemplate::New( allocateMemory ) ;
	 obj-> Set( v8::String::New( "allocateMemory" ), f->GetFunction()   ) ;
	
	}
	
	
MemoryManagerJS:: MemoryManagerJS()
	{
	 nonV8Memory 		= currentlyUsedMemory() ;
	
	 lastUpdatedMemory	= nonV8Memory ;
	}
	
	
void MemoryManagerJS:: updateV8AllocatedMemory() 
	{
	 long nextUpdatedMemory = currentlyUsedMemory() ;
	
	 v8::V8::AdjustAmountOfExternalAllocatedMemory( nextUpdatedMemory - lastUpdatedMemory ) ;
	
	 lastUpdatedMemory = nextUpdatedMemory ;
	
	}
	
	
long MemoryManagerJS:: currentlyUsedMemory()
	{
	/*
	 rusage usage ;
	
	 getrusage( RUSAGE_SELF, &usage ) ;
	
	 return usage.ru_ixrss ; // integral shared memory size
	*/
	
	 task_t task = MACH_PORT_NULL;
	    struct task_basic_info t_info;
	    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

	    if (KERN_SUCCESS != task_info(mach_task_self(),
	       TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count))
	    {
	        return -1;
	    }

//	 printf( "resident = %li\n", t_info.resident_size ) ;
//	 printf( "virtual = %li\n", t_info.virtual_size ) ;

   	 return t_info.resident_size ;
	
	/*
	int64_t myFreeMemory ;
	int64_t used_memory ;
	
	vm_size_t page_size;
	mach_port_t mach_port;
	mach_msg_type_number_t count;
	vm_statistics_data_t vm_stats;

	mach_port = mach_host_self();
	count = sizeof(vm_stats) / sizeof(natural_t);
	if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
	    KERN_SUCCESS == host_statistics(mach_port, HOST_VM_INFO, 
	                                    (host_info_t)&vm_stats, &count))
	{
	    myFreeMemory = (int64_t)vm_stats.free_count * (int64_t)page_size;

	    used_memory = ((int64_t)vm_stats.active_count + 
	                   (int64_t)vm_stats.inactive_count + 
	                   (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
	}
	
	return used_memory ;
	*/
	}
	
v8::Handle<v8::Value> MemoryManagerJS:: allocateMemory( const v8::Arguments& args ) 
	{
	 v8::V8::AdjustAmountOfExternalAllocatedMemory( args[ 0 ]-> ToInteger()-> Value() ) ;
	
	 return v8::Undefined() ;
	}
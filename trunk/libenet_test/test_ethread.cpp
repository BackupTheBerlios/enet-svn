#include <UnitTest++.h>
#include "../libenet/ethread.h"

class MyThread : public eThread {
public:
	MyThread(){};
	~MyThread(){};
	
	virtual void start(){
		while( testDestroy() == false ) {
			printf("inside thread %d\n", this->getThreadId());
			eThreadSleep(100);
		}
		printf("got a stop() request\n");
	}
};

TEST(TestStart)
{
	MyThread thr[10];
	
	for(size_t i=0; i<10; i++){
		thr[i].run();
	}
	eThreadSleep(1000);
	
	// put a stop request
	for(size_t i=0; i<10; i++){
		thr[i].requestStop();
	}

	// wait for thread to terminate itself
	for(size_t i=0; i<10; i++){
		thr[i].wait(-1);
	}
	
	printf("all threads terminated\n");

}

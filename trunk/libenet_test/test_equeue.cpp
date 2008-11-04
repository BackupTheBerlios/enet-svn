#include <UnitTest++.h>
#include "../libenet/equeue.h"
#include "../libenet/ethread.h"
#include "../libenet/emutex.h"

eQueue<std::string> g_queue;
eQueue<std::string> g_queue2;
eMutex g_mutex;
size_t g_counter ( 0 );

class ConsumerThread : public eThread
{
public:
	ConsumerThread() {};
	~ConsumerThread() {};

	virtual void start() {
		std::string item;
		while ( g_queue.get ( item, 1000 ) ) {
			eThreadSleep ( 1 );
			g_mutex.lock();
			g_counter++;
			g_mutex.unlock();
		}
	}
};

class WorkerThread : public eThread
{
public:
	WorkerThread() {};
	~WorkerThread() {};

	virtual void start() {
		while ( true ) {
			std::string item;

			if ( !g_queue2.get ( item, 500 ) ) {
				printf ( "queue timeout\n" );
			} else {
				printf ( "got item from queue\n" );
			}
		}
	}
};

TEST(TestGet)
{
	eQueue<std::string> myq;
	std::string output;

	// put one element on the queue
	CHECK(myq.put("eran"));
	CHECK(myq.get(output, -1));
	CHECK(myq.get(output, 10) == false);
	CHECK(myq.get(output, 10) == false);
}

TEST(TestPut)
{
	eQueue<std::string> myq;
	std::string output;

	// put one element on the queue
	CHECK(myq.put("eran"));
}

TEST(ConcurrentTest)
{
	ConsumerThread thr[10];

	for(size_t i=0; i<10; i++){
		thr[i].run();
	}

	for(size_t i=0; i<100; i++){
		g_queue.put("eran");
	}

	// wait for thread to terminate itself
	for(size_t i=0; i<10; i++){
		thr[i].wait(-1);
	}
	CHECK(g_counter==100);
}

//TEST ( BlockingTest )
//{
//	for ( size_t i=0; i<100; i++ ) {
//		g_queue2.put ( "eran" );
//	}
//
//	WorkerThread thr;
//	thr.run();
//
//#ifdef __WINDOWS__
//	Sleep(INFINITE);
//#else
//	sleep(10000);
//#endif
//}


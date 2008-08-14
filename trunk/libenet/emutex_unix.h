#if !defined(__WINDOWS__)

#ifndef __emuteximpl__
#define __emuteximpl__

#include <pthread.h>

class eMutexImpl {
	pthread_mutex_t m_mutex;
public:
	eMutexImpl();
	~eMutexImpl();
	
	void lock();
	void unlock();
	bool trylock();
};

#endif // __emuteximpl__
#endif //__WINDOWS__

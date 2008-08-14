#if defined(__WINDOWS__)

#ifndef __emuteximpl__
#define __emuteximpl__

#include <windows.h>

class eMutexImpl {
	CRITICAL_SECTION m_cs;
	
public:
	eMutexImpl();
	~eMutexImpl();
	
	void lock();
	void unlock();
	bool trylock();
};

#endif // __emuteximpl__
#endif //__WINDOWS__

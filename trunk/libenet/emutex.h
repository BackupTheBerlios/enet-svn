#ifndef __emutex_h__
#define __emutex_h__

#ifdef __WINDOWS__
#	include "emutex_win.h"
#else 
#	include "emutex_unix.h"
#endif

class eMutex
{
	eMutexImpl *m_impl;
	
public:
	eMutex(){
		m_impl = new eMutexImpl();
	}

	virtual ~eMutex(){
		delete m_impl;
	}
	
	void lock() {
		m_impl->lock();
	}
	
	void unlock() {
		m_impl->unlock();
	}
	
	bool trylock() {
		return m_impl->trylock();
	}
};

#endif //__emutex_h__


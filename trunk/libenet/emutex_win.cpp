#if defined(__WINDOWS__)

#include "emutex_win.h"
eMutexImpl::eMutexImpl()
{
	InitializeCriticalSection(&m_cs);
}

eMutexImpl::~eMutexImpl()
{
	DeleteCriticalSection(&m_cs);
}

void eMutexImpl::lock()
{
	EnterCriticalSection( &m_cs );
}

bool eMutexImpl::trylock()
{
	return TryEnterCriticalSection( &m_cs );
}

void eMutexImpl::unlock()
{
	LeaveCriticalSection( &m_cs );
}

#endif

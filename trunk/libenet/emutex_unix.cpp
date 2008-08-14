#if !defined(__WINDOWS__)

#include "emutex_unix.h"
eMutexImpl::eMutexImpl()
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutex_init(&m_mutex, &attr);
}

eMutexImpl::~eMutexImpl()
{
}

void eMutexImpl::lock()
{
	pthread_mutex_lock(&m_mutex);
}

bool eMutexImpl::trylock()
{
	return pthread_mutex_trylock(&m_mutex) == 0;
}

void eMutexImpl::unlock()
{
	pthread_mutex_unlock(&m_mutex);
}

#endif

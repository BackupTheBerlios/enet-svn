#include "TimeHelpers.h"

#ifndef __WINDOWS__

#include <unistd.h>

namespace UnitTest {

Timer::Timer()
{
    m_startTime.tv_sec = 0;
    m_startTime.tv_usec = 0;
}

void Timer::Start()
{
    gettimeofday(&m_startTime, 0);
}


int Timer::GetTimeInMs() const
{
    struct timeval currentTime;
    gettimeofday(&currentTime, 0);
    int const dsecs = currentTime.tv_sec - m_startTime.tv_sec;
    int const dus = currentTime.tv_usec - m_startTime.tv_usec;
    return dsecs*1000 + dus/1000;
}


void TimeHelpers::SleepMs (int ms)
{
    usleep(ms * 1000);
}

}
#else
#include <windows.h>

namespace UnitTest {

Timer::Timer()
    : m_startTime(0)
{
    m_threadId = ::GetCurrentThread();
    DWORD_PTR systemMask;
    ::GetProcessAffinityMask(GetCurrentProcess(), &m_processAffinityMask, &systemMask);
    
    ::SetThreadAffinityMask(m_threadId, 1);
	::QueryPerformanceFrequency(reinterpret_cast< LARGE_INTEGER* >(&m_frequency));
    ::SetThreadAffinityMask(m_threadId, m_processAffinityMask);
}

void Timer::Start()
{
    m_startTime = GetTime();
}

int Timer::GetTimeInMs() const
{
    __int64 const elapsedTime = GetTime() - m_startTime;
	double const seconds = double(elapsedTime) / double(m_frequency);
	return int(seconds * 1000.0f);
}

__int64 Timer::GetTime() const
{
    LARGE_INTEGER curTime;
    ::SetThreadAffinityMask(m_threadId, 1);
	::QueryPerformanceCounter(&curTime);
    ::SetThreadAffinityMask(m_threadId, m_processAffinityMask);
    return curTime.QuadPart;
}



void TimeHelpers::SleepMs(int const ms)
{
	::Sleep(ms);
}

}

#endif


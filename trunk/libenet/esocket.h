#ifndef __ESOCKET_H__
#define __ESOCKET_H__

#include <sys/types.h>

#ifdef __WINDOWS_
# include <winsock2.h>
typedef SOCKET socket_t;
#else
typedef int socket_t;
#endif

class eSocket
{
	socket_t m_socket;

public:
	eSocket();
	~eSocket();

	size_t sendData(const char* data, size_t len);
	size_t recvData(char **data, char *buffer, size_t bufsize);
	socket_t getHandle() {return m_socket;}
};

#endif  //__ESOCKET_H__

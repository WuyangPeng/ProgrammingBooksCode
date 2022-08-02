#ifndef ROBO_CAT_SHARED_H
#define ROBO_CAT_SHARED_H

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX

    #include "WinSock2.h"
    #include "Windows.h"
    #include "Ws2tcpip.h"
typedef int socklen_t;
    //typedef char* receiveBufer_t;
#else
    #include <errno.h>
    #include <fcntl.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/types.h>
//typedef void* receiveBufer_t;
typedef int SOCKET;
const int NO_ERROR = 0;
const int INVALID_SOCKET = -1;
const int WSAECONNRESET = ECONNRESET;
const int WSAEWOULDBLOCK = EAGAIN;
const int SOCKET_ERROR = -1;
#endif

#include "memory"

#include "cassert"
#include "deque"
#include "list"
#include "queue"
#include "string"
#include "unordered_map"
#include "unordered_set"
#include "vector"

using std::deque;
using std::list;
using std::queue;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class RoboCat;
class GameObject;

#include "RoboMath.h"

#include "ByteSwap.h"
#include "LinkingContext.h"
#include "MemoryBitStream.h"
#include "MemoryStream.h"

#endif  // ROBO_CAT_SHARED_H
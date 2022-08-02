#pragma once

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX

    #include "Windows.h"
    #include "WinSock2.h"
    #include "Ws2tcpip.h"
typedef int socklen_t;
//typedef char* receiveBufer_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/types.h>
    #include <netdb.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <unistd.h>
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

#include "SocketAddress.h"
#include "SocketAddressFactory.h"
#include "SocketUtil.h"
#include "StringUtils.h"
#include "TCPSocket.h"
#include "UDPSocket.h"

#include "MemoryBitStream.h"

#include "InputAction.h"
#include "InputState.h"
#include "Move.h"
#include "MoveList.h"

#include "GameObject.h"
#include "GameObjectRegistry.h"
#include "Mouse.h"
#include "RoboCat.h"
#include "ScoreBoardManager.h"
#include "StringUtils.h"
#include "Timing.h"
#include "World.h"
#include "Yarn.h"

#include "Engine.h"
#include "NetworkManager.h"
#include "ReplicationCommand.h"
#include "WeightedTimedMovingAverage.h"

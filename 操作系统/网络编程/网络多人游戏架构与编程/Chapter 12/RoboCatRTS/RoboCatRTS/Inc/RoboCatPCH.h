#pragma once

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX

    #include "WinSock2.h"
    #include "Windows.h"
    #include "Ws2tcpip.h"
#else
    #include <netinet/in.h>
    #include <sys/socket.h>
typedef int SOCKET;
const int NO_ERROR = 0;
const int INVALID_SOCKET = -1;
const int WSAECONNRESET = 10054;
#endif

#include "memory"

#include "array"
#include "cassert"
#include "deque"
#include "list"
#include "map"
#include "queue"
#include "random"
#include "string"
#include "unordered_map"
#include "unordered_set"
#include "vector"

using std::deque;
using std::list;
using std::map;
using std::queue;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class RoboCat;
class GameObject;

#include "RandGen.h"
#include "RoboMath.h"

#include "StringUtils.h"

#include "MemoryBitStream.h"

#include "Command.h"
#include "CommandList.h"
#include "InputAction.h"
#include "TurnData.h"

#include "GraphicsDriver.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "TextureManager.h"
#include <SDL.h>

#include "Timing.h"

#include "GameObject.h"
#include "GameObjectRegistry.h"
#include "GamerServices.h"
#include "NetworkManager.h"
#include "WeightedTimedMovingAverage.h"

#include "RoboCat.h"
#include "ScoreBoardManager.h"
#include "StringUtils.h"
#include "World.h"
#include "Yarn.h"

#include "Engine.h"

#include "HUD.h"
#include "WindowManager.h"

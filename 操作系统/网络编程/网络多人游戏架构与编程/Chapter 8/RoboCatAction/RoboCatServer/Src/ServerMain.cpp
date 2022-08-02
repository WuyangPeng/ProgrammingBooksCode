
#include <RoboCatServerPCH.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] const char** argv)
{
    if (Server::StaticInit())
    {
        return Server::sInstance->Run();
    }
    else
    {
        //error
        return 1;
    }
}

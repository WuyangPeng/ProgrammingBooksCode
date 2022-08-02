#include <iostream>

namespace Singleton1
{
    //^1
    class FileSystem
    {
    public:
        static FileSystem& instance()
        {
            // Lazy initialize.
            if (instance_ == nullptr)
                instance_ = new FileSystem();
            return *instance_;
        }

    private:
        FileSystem()
        {
        }

        static FileSystem* instance_;
    };
    //^1

    FileSystem* FileSystem::instance_;

    void test()
    {
        if (&FileSystem::instance() == nullptr)
        {
            std::cout << "singleton is null!" << std::endl;
        }
        else
        {
            std::cout << "singleton is ok" << std::endl;
        }
    }
}

namespace SingletonStatic
{
    //^local-static
    class FileSystem
    {
    public:
        static FileSystem& instance()
        {
            static FileSystem* instance = new FileSystem();
            return *instance;
        }

    private:
        FileSystem()
        {
        }
    };
    //^local-static

    void test()
    {
        if (&FileSystem::instance() == nullptr)
        {
            std::cout << "singleton is null!" << std::endl;
        }
        else
        {
            std::cout << "singleton is ok" << std::endl;
        }
    }
}

namespace Singleton2
{
    //^2
    class FileSystem
    {
    public:
        virtual ~FileSystem()
        {
        }
        virtual char* readFile(char* path) = 0;
        virtual void writeFile(char* path, char* contents) = 0;
    };
    //^2

    //^derived-file-systems
    class PS3FileSystem : public FileSystem
    {
    public:
        virtual char* readFile([[maybe_unused]] char* path)
        {
            // Use Sony file IO API...
            //^omit
            return NULL;
            //^omit
        }

        virtual void writeFile([[maybe_unused]] char* path, [[maybe_unused]] char* contents)
        {
            // Use sony file IO API...
        }
    };

    class WiiFileSystem : public FileSystem
    {
    public:
        virtual char* readFile([[maybe_unused]] char* path)
        {
            // Use Nintendo file IO API...
            //^omit
            return NULL;
            //^omit
        }

        virtual void writeFile([[maybe_unused]] char* path, [[maybe_unused]] char* contents)
        {
            // Use Nintendo file IO API...
        }
    };
    //^derived-file-systems
}

namespace Singleton3
{
#define PLAYSTATION3 1
#define WII 2
#define PLATFORM PLAYSTATION3

    class PS3FileSystem;
    class WiiFileSystem;

    //^3
    class FileSystem
    {
    public:
        static FileSystem& instance();

        virtual ~FileSystem()
        {
        }
        virtual char* readFile(char* path) = 0;
        virtual void writeFile(char* path, char* contents) = 0;

    protected:
        FileSystem()
        {
        }
    };
    //^3

    class PS3FileSystem : public FileSystem
    {
        virtual char* readFile([[maybe_unused]] char* path)
        {
            return nullptr;
        }

        virtual void writeFile([[maybe_unused]] char* path, [[maybe_unused]] char* contents)
        {
        }
    };

    class WiiFileSystem : public FileSystem
    {
        virtual char* readFile([[maybe_unused]] char* path)
        {
            return nullptr;
        }

        virtual void writeFile([[maybe_unused]] char* path, [[maybe_unused]] char* contents)
        {
        }
    };

    //^4
    FileSystem& FileSystem::instance()
    {
#if PLATFORM == PLAYSTATION3
        static FileSystem* instance = new PS3FileSystem();
#elif PLATFORM == WII
        static FileSystem* instance = new WiiFileSystem();
#endif

        return *instance;
    }
    //^4
}

namespace Singleton4
{
    //^5
    class FileSystem
    {
    public:
        static FileSystem& instance()
        {
            return instance_;
        }

    private:
        FileSystem()
        {
        }

        static FileSystem instance_;
    };
    //^5

    FileSystem FileSystem::instance_ = FileSystem();
}

namespace Singleton5
{
    //^6
    class FileSystem
    {
    public:
        FileSystem()
        {
            assert(!instantiated_);
            instantiated_ = true;
        }

        ~FileSystem()
        {
            instantiated_ = false;
        }

    private:
        static bool instantiated_;
    };

    bool FileSystem::instantiated_ = false;
    //^6
}

namespace Singleton7
{
#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 100

    //^8
    class Bullet
    {
    public:
        int getX() const
        {
            return x_;
        }
        int getY() const
        {
            return y_;
        }

        void setX(int x)
        {
            x_ = x;
        }
        void setY(int y)
        {
            y_ = y;
        }

    private:
        int x_, y_;
    };

    class BulletManager
    {
    public:
        Bullet* create(int x, int y)
        {
            Bullet* bullet = new Bullet();
            bullet->setX(x);
            bullet->setY(y);

            return bullet;
        }

        bool isOnScreen(Bullet& bullet)
        {
            return bullet.getX() >= 0 &&
                   bullet.getX() < SCREEN_WIDTH &&
                   bullet.getY() >= 0 &&
                   bullet.getY() < SCREEN_HEIGHT;
        }

        void move(Bullet& bullet)
        {
            bullet.setX(bullet.getX() + 5);
        }
    };
    //^8
}

namespace Singleton8
{
    //^9
    class Bullet
    {
    public:
        Bullet(int x, int y)
            : x_(x), y_(y)
        {
        }

        bool isOnScreen()
        {
            return x_ >= 0 && x_ < SCREEN_WIDTH &&
                   y_ >= 0 && y_ < SCREEN_HEIGHT;
        }

        void move()
        {
            x_ += 5;
        }

    private:
        int x_, y_;
    };
    //^9
}

namespace Singleton9
{
    class Log
    {
    public:
        virtual ~Log()
        {
        }
        virtual void write(const char* text) = 0;
    };

    //^10
    class GameObject
    {
    protected:
        Log& getLog()
        {
            return log_;
        }

    private:
        static Log& log_;
    };

    class Enemy : public GameObject
    {
        void doSomething()
        {
            getLog().write("I can log!");
        }
    };
    //^10
}

namespace Singleton10
{
    class Log
    {
    };
    class FileSystem
    {
    };
    class AudioPlayer
    {
    public:
        virtual void play(int id) = 0;
    };

    //^11
    class Game
    {
    public:
        static Game& instance()
        {
            return instance_;
        }

        // Functions to set log_, et. al. ...

        Log& getLog()
        {
            return *log_;
        }
        FileSystem& getFileSystem()
        {
            return *fileSystem_;
        }
        AudioPlayer& getAudioPlayer()
        {
            return *audioPlayer_;
        }

    private:
        static Game instance_;

        Log* log_;
        FileSystem* fileSystem_;
        AudioPlayer* audioPlayer_;
    };
    //^11

    Game Game::instance_ = Game();

    void foo()
    {
        int VERY_LOUD_BANG = 0;
        //^12
        Game::instance().getAudioPlayer().play(VERY_LOUD_BANG);
        //^12
    }
}

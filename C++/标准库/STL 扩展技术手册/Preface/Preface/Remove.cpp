#include "Preface.h"

#ifdef STLSOFT_COMPILER_IS_GCC

    #include <unixstl/filesystem/readdir_sequence.hpp>

#endif  // STLSOFT_COMPILER_IS_GCC

void Remove0()
{
    DIR* dir = opendir(".");
    if (dir != nullptr)
    {
        struct dirent* de;
        for (; (de = readdir(dir)) != nullptr;)
        {
            struct stat st;
            if (stat(de->d_name, &st) && (st.st_mode & S_IFMT) == S_IFREG)
            {
                remove(de->d_name);
            }
        }

        closedir(dir);
    }
}

void Remove1()
{
#ifdef STLSOFT_COMPILER_IS_GCC

    using namespace unixstl;

    readdir_sequence entries(".", readdir_sequence::files);
    std::for_each(entries.begin(), entries.end(), ::remove);

#endif  // STLSOFT_COMPILER_IS_GCC
}
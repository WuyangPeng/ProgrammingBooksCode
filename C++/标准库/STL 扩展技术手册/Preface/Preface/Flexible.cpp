#include "Preface.h"

template <typename T>
T max(T const& t1, T const& t2)
{
    return t1 < t2 ? t2 : t1;
}

void CompileError()
{
#if 0

    int i1 = 1;
    long l1 = 11;
    max(i1, l1);  // ±àÒë´íÎó

#endif  // 0
}

void DynamicLibrary()
{
    {
        char const* pathName = "";
        dynamic_library dl(pathName);
    }

    {
        std::string const& pathName = "";
        dynamic_library dl(pathName.c_str());
    }
}

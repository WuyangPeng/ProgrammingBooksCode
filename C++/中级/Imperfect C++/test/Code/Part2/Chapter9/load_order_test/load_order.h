
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

__declspec(dllimport) void funcA();

__declspec(dllimport) void funcB(void (*)());



#ifdef __cplusplus
} /* extern "C" */

struct LoadOrder
{
    LoadOrder(char const *s)
        : m_s(s)
    {
        printf("Loading: %s\n", m_s);
    }
    ~LoadOrder()
    {
        printf("Unloading: %s\n", m_s);
    }
private:
    char const *m_s;
};

#endif /* __cplusplus */

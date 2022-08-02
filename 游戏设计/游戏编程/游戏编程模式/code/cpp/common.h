#pragma once

// Makes the argument appear to be used so that we don't get an unused
// variable warning for it. Lets us leave that warning on to catch unintended
// unused variables.
template <class T>
void use([[maybe_unused]] const T& obj)
{
    // Do nothing.
}

#ifdef _DEBUG
    #define ASSERT(condition)                          \
        if (!(condition))                              \
        {                                              \
            std::cout << "FAIL: " #condition << "\n"   \
                      << __FILE__                      \
                      << ":" << __LINE__ << std::endl; \
            abort();                                   \
        }
#else // !_DEBUG
    #define ASSERT(condition) ((void)0)
#endif  // _DEBUG

void assert(bool condition)
{
    if (!condition)
    {
        printf("WTF\n");
        exit(1);
    }
}
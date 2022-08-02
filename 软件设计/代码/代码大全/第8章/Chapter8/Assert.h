#pragma once

void LogError([[maybe_unused]] const char* assertion, [[maybe_unused]] const char* condition, [[maybe_unused]] const char* message)
{
}

#define ASSERT(condition, message)                               \
    {                                                            \
        if (!(condition))                                        \
        {                                                        \
            LogError("Assertion failed: ", #condition, message); \
            exit(EXIT_FAILURE);                                  \
        }                                                        \
    }

 
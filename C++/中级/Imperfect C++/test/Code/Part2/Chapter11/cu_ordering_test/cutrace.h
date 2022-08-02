
#include <stdarg.h>

// CUTrace.h
extern "C" void CUTraceHelper(char const *file, char const *msg, va_list args);

#if 0
static void CUTrace(char const *message, ...)
{
  va_list args;

  va_start(args, message);

  CUTraceHelper(__BASE_FILE__, message, args);

  va_end(args);
}

class CUTracer
{
public:
    CUTracer()
    {
        CUTrace("Initialising\n");
    }
};
static CUTracer s_tracer;

#else /* ? 0 */

namespace
{
    void CUTrace(char const *message, ...)
    {
      va_list args;

      va_start(args, message);

      CUTraceHelper(__BASE_FILE__, message, args);

      va_end(args);
    }

    class CUTracer
    {
    public:
        CUTracer()
        {
            CUTrace("Initialising\n");
        }
    };
    CUTracer    s_tracer;
}


#endif /* 0 */

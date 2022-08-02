#include "ccc_shap.h"

#if defined(_MSC_VER)
   #define CCC_MSW
#endif
#if defined(_WINDOWS_) || defined (_Windows) || defined(WINVER) || defined(__WIN32__)
   #define CCC_MSW
#endif
#if defined(__GNUC__) && !defined(CCC_MSW)
   #define CCC_X11
#endif

#if defined(CCC_ASC)
#include "ccc_asc.h"
#elif defined(CCC_WXW)
#include "ccc_wxw.h"
#elif defined(CCC_X11)
#include "ccc_x11.h"
#elif defined(CCC_MSW)
#include "ccc_msw.h"
#else
#include "ccc_asc.h"
#endif

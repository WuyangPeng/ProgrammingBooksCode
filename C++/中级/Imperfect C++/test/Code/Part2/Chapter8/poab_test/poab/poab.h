
// Updated: 4th March 2004

#ifdef POAB_COMPILER_HAS_COMPATIBLE_VTABLES
# define POAB_COMPILER_HAS_COMPATIBLE_VTABLES
#endif /* POAB_COMPILER_HAS_COMPATIBLE_VTABLES */


#if defined(__BORLANDC__)           /* Borland C/C++ */
# include "poab/compiler_bcc.h"
#elif defined(__COMO__)             /* Comeau C/C++ */
# include "poab/compiler_como.h"
#elif defined(__DMC__)              /* Digital Mars C/C++ */
# include "poab/compiler_dmc.h"
#elif defined(__GNUC__)             /* GNU C/C++ */
# include "poab/compiler_gnuc.h"
#elif defined(__INTEL_COMPILER)     /* Intel C/C++ */
# include "poab/compiler_intel.h"
#elif defined(__MWERKS__)           /* Metrowerks C/C++ */
# include "poab/compiler_mwerks.h"
#elif defined(__WATCOMC__)          /* Watcom C/C++ */
# include "poab/compiler_watcom.h"
#elif defined(_MSC_VER)             /* Visual C++ */
# include "poab/compiler_vc.h"
#else /* ? compiler */
# error Compiler not recognised
#endif /* compiler */

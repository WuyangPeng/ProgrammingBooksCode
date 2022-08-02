
#if defined(__BORLANDC__)           /* Borland C/C++ */
# pragma pack(4)
#elif defined(__COMO__)             /* Comeau C/C++ */
# pragma pack(push, 4)
#elif defined(__DMC__)              /* Digital Mars C/C++ */
# pragma pack(push, 4)
#elif defined(__GNUC__)             /* GNU C/C++ */
# pragma pack(push, 4)
#elif defined(__INTEL_COMPILER)     /* Intel C/C++ */
# pragma pack(push, 4)
#elif defined(__MWERKS__)           /* Metrowerks C/C++ */
# pragma pack(push, 4)
#elif defined(__WATCOMC__)          /* Watcom C/C++ */
# pragma pack(push, 4)
#elif defined(_MSC_VER)             /* Visual C++ */
# pragma pack(push, 4)
#else /* ? compiler */
# error Compiler not recognised
#endif /* compiler */

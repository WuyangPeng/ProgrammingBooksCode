
#if defined(__BORLANDC__)           /* Borland C/C++ */
# pragma pack()
#elif defined(__COMO__)             /* Comeau C/C++ */
# pragma pack(pop)
#elif defined(__DMC__)              /* Digital Mars C/C++ */
# pragma pack(pop)
#elif defined(__GNUC__)             /* GNU C/C++ */
# pragma pack(pop)
#elif defined(__INTEL_COMPILER)     /* Intel C/C++ */
# pragma pack(pop)
#elif defined(__MWERKS__)           /* Metrowerks C/C++ */
# pragma pack(pop)
#elif defined(__WATCOMC__)          /* Watcom C/C++ */
# pragma pack(pop)
#elif defined(_MSC_VER)             /* Visual C++ */
# pragma pack(pop)
#else /* ? compiler */
# error Compiler not recognised
#endif /* compiler */

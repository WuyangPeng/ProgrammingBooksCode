
#if defined(__BORLANDC__)           /* Borland C/C++ */
# pragma warn .8059
#elif defined(__COMO__)             /* Comeau C/C++ */
#elif defined(__DMC__)              /* Digital Mars C/C++ */
#elif defined(__GNUC__)             /* GNU C/C++ */
#elif defined(__INTEL_COMPILER)     /* Intel C/C++ */
#elif defined(__MWERKS__)           /* Metrowerks C/C++ */
#elif defined(__WATCOMC__)          /* Watcom C/C++ */
#elif defined(_MSC_VER)             /* Visual C++ */
# if _MSC_VER > 1100
#  pragma warning(pop)
# else /* ? _MSC_VER > 1100 */
#  pragma warning(disable : 4103)
# endif /* _MSC_VER > 1100 */
#else /* ? compiler */
# error Compiler not recognised
#endif /* compiler */

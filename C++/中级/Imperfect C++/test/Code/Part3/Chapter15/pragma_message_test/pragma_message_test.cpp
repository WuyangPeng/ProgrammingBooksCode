#if defined(__BORLANDC__)
# pragma message("Borland")
#elif defined(__DMC__)
# pragma message("Digital Mars")
#elif defined(__GNUC__)
# pragma message("GCC")
#elif defined(__INTEL_COMPILER)
# pragma message("Intel C/C++")
#elif defined(__VECTORC)
# pragma message("Vector C")
#elif defined(__MWERKS__)
# pragma message("CodeWarrior")
#elif defined(__WATCOMC__)
# pragma message("Watcom")
#elif defined(__COMO__)
# pragma message("Comeau")
#elif defined(_MSC_VER)
# pragma message("Visual C++")
#else
# error Compiler not recognised
#endif /* compiler */

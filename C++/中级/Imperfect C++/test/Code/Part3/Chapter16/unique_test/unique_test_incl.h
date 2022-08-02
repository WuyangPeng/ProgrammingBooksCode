

inline int multiply(int i1, int i2)
{
#ifdef MESS_WITH_DEF
# pragma message("Messed with def")
    return i1 + i2; // Bad definition
#else /* ? MESS_WITH_DEF */
# pragma message("Correct def")
    return i1 * i2; // Correct definition
#endif /* MESS_WITH_DEF */
}

extern int do_multiply(int i1, int i2);
extern void *get_multiply();

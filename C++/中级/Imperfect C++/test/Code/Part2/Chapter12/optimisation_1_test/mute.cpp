
#if 0
# pragma optimize("gt", off)
//# pragma optimize("", on)
#endif /* 0 */

int main()
{
#if 0
    for(volatile int i = 0; i < 0x7fffffff; ++i)
    {}

    return 0;
#else /* ? 0 */
    /* volatile */ int i;

    for(i = 0; i < 0x7fffffff; ++i)
    {}

    return i;
#endif /* 0 */
}

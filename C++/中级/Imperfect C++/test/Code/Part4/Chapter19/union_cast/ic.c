
#ifdef __GNUC__
__inline
#else
__inline
#endif /* __GNUC__ */
int func(int i, int j)
{
    return i + j;
}

int main()
{
    return func(10, 20);
}

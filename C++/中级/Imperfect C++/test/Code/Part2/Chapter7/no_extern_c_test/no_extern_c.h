

class Thing5
{
    int Thing5::*pm;
};

int func1(Thing5 const&);
int func2(int p1, int p2, int p3);

#ifdef __cplusplus
extern "C++"
int func2(int p1, int p2)
{
    return func2(p1, p2, -1);
}
#endif /* __cplusplus */

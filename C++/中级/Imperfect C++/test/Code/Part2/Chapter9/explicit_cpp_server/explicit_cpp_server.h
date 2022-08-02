

#ifndef BUILDING_THING
# define THING_IMPEXP   __declspec(dllexport)
#else /* ? THING_IMPEXP */
# define THING_IMPEXP   __declspec(dllimport)
#endif /* BUILDING_THING */


class THING_IMPEXP Thing
{
public:
    void PublicMethod(char const *s);

private:
    void PrivateMethod(char const *s);
};

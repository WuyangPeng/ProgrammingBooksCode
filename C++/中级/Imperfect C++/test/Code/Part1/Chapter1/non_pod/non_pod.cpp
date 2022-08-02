
#include <stlsoft_constraints.h>

using stlsoft::must_be_pod;

struct not_subs
{};

class NonPOD
{
public:
  virtual ~NonPOD();
};

int main()
{
    must_be_pod<int>();       // int is POD (see Prologue)
    must_be_pod<not_subs>();  // not_subs is POD (see Prologue)
    must_be_pod<NonPOD>();    // NonPOD isn't: compile error

    return 0;
}
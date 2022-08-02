

class __declspec(dllexport) Mangle
{
public:
  void func(int i);
  void func(char const *);
};

extern "C" void process_Mangle(Mangle *pm);

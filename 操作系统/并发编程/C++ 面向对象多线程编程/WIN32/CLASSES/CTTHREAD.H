typedef void (* FunctionPtr) (void*);
class ct_thread{
private:
  DWORD ThreadId;
  HANDLE ThreadHandle;
  DWORD StackSize, ExitCode;

public:
  ct_thread(DWORD SSize = 4096);
  ~ct_thread(void);
  void begin(FunctionPtr PFN, void *X);
  void wait(void);
  unsigned long threadId(void);
};



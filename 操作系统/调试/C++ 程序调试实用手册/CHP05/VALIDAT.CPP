// validat.cpp
// Validating call stack
// Debug vs. Release versions
// Chris H. Pappas and William H. Murray, 1999

void __stdcall myFuncA(char *p)
{
   puts(p);
}

typedef void (*function_pointer)(char *);

void main( void )
{
   function_pointer pmyFuncA = (function_pointer)myFuncA;

   pmyFuncA("This is just a test.");
}

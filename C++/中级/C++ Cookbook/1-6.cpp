__declspec(dllexport) int m = 3;    // Exported data definition
extern __declspec(dllexport) int n; // Exported data declaration
__declspec(dllexport) void f( );    // Exported function declaration
class __declspec(dllexport) c {     // Exported class definition
   /* ... */
};

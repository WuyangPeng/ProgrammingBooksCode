extern __attribute__((visibility("default"))) int m; // exported
extern int n;                                        // not exported
__attribute__((visibility("default"))) void f( );    // exported
void g( );                                           // not exported
struct __attribute__((visibility("default"))) S { }; // exported
struct T { };                                        // not exported

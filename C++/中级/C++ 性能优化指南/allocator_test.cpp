# include <iostream>
# include <memory>
# include <string>

static bool new_instrumentation_on = false;

void instrument_new(bool f = true) {
    new_instrumentation_on = f;
}

void* operator new (size_t size) {
    void *p = malloc(size);
    if (new_instrumentation_on)
        std::cout << "new(" << size << ") allocated at 0x" << std::hex << p << std::dec << std::endl;
    return p; 
}
void operator delete (void *p) {	
    if (new_instrumentation_on)
        std::cout << "delete(0x" << p << ")" << std::dec << std::endl;
    free (p);
}

int string_allocator_test(int) {
    instrument_new();
    {
        puts("std::string s;");
        std::string s;
        puts("try appending 1 char");
        s = s + 'x';
        puts("try appending 20 char C-style string");
        s = s + "12345678901234567890";
        puts("try appending s");
        s = s + s;
        puts("for");
        for (int i = 0; i < 30; ++i)
            s = s + 'x';
        puts("delete s");
    }
    instrument_new(false);
    return 1;
}// end main
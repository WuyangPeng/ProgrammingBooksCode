# include <memory>
# include <iostream>

// instrumented class new, new[]

static bool new_instrumentation_on = false;

struct new_instrument {
	new_instrument() { new_instrumentation_on = true; }
   ~new_instrument() { new_instrumentation_on = false;}
};
void instrument_new(bool f = true) {
    new_instrumentation_on = f;
}

void* operator new (size_t size) {
    void *p = malloc(size);
    if (new_instrumentation_on)
        std::cout << "::operator new(" << size << ") allocated at 0x" << std::hex << p << std::dec << std::endl;
    return p; 
}
void* operator new[](size_t size) {
    void *p = malloc(size);
    if (new_instrumentation_on)
        std::cout << "::operator new[](" << size << ") allocated at 0x" << std::hex << p << std::dec << std::endl;
    return p; 
}
void operator delete (void *p) {	
    if (new_instrumentation_on)
        std::cout << "::operator delete(0x" << p << ")" << std::dec << std::endl;
    free (p);
}
void operator delete[](void *p) {
    if (new_instrumentation_on)
        std::cout << "::operator delete[](0x" << p << ")" << std::dec << std::endl;
    free (p);
}

class MyOwnAllocator {
public:
	void* operator new(size_t n);
	void operator delete(void* p);
	void* operator new[](size_t n);
	void operator delete[](void* p);
	void AllocateBuffer();
private:
    std::unique_ptr<short> p_;
};

void* MyOwnAllocator::operator new(size_t size) {
    void *p = malloc(size);
    if (new_instrumentation_on)
        std::cout << "MyOwnAllocator::operator new(" << size << ") allocated at 0x" << std::hex << p << std::dec << std::endl;
    return p; 
}
void MyOwnAllocator::operator delete (void *p) {	
    if (new_instrumentation_on)
        std::cout << "MyOwnAllocator::operator delete(0x" << p << ")" << std::dec << std::endl;
    free (p);
}
void* MyOwnAllocator::operator new[](size_t size) {
    void *p = malloc(size);
    if (new_instrumentation_on)
        std::cout << "MyOwnAllocator::operator new[](" << size << ") allocated at 0x" << std::hex << p << std::dec << std::endl;
    return p; 
}
void MyOwnAllocator::operator delete[](void *p) {	
    if (new_instrumentation_on)
        std::cout << "MyOwnAllocator::operator delete[](0x" << p << ")" << std::dec << std::endl;
    free (p);
}
void MyOwnAllocator::AllocateBuffer() {
	p_.reset(new short(12345));
}

int test_class_new(int testno, unsigned long) {
	bool rc = true;
	switch(testno) {
	case 0: return 1;
	case -1: return -1;
	case 1:
		{
			new_instrument ni;
			{
				std::unique_ptr<MyOwnAllocator> pmoa(new MyOwnAllocator);
				pmoa->AllocateBuffer();
				std::unique_ptr<MyOwnAllocator[]> pamoa(new MyOwnAllocator[3]);
				::new((void*)0) MyOwnAllocator;
			}
		//	int a[100], b[100];
		//	a = b; error: '=;' : left operand must be l-value
			struct { int x, y; int z[100]; } c,d;
			c = d;
		}
		break;
	}
	return rc ? 1 : 0;
}
class C {
public:
	int x_;
	int f0();
	int f1(int arg);
};

class C1 {
	C& c_;
public:
	C1(C& c) : c_(c) {}
	int f0();
	int f1(int arg);
};

class C2 {
	C1& c_;
public:
	C2(C1& c) : c_(c) {}
	int f0();
	int f1(int arg);
};

class C3 {
	C2& c_;
public:
	C3(C2& c) : c_(c) {}
	int f0();
	int f1(int arg);
};

class C4 {
	C3& c_;
public:
	C4(C3& c) : c_(c) {}
	int f0();
	int f1(int arg);
};

class C5 {
	C4& c_;
public:
	C5(C4& c) : c_(c) {}
	int f0();
	int f1(int arg);
};


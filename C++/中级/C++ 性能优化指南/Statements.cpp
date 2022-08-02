# include "test_driver.h"
# include "stopwatch03.h"
# include <iostream>
# include <cmath>
# include <vector>
# include <bitset>

struct Point {
	double x_, y_;
	static double epsilon;

	Point(double x, double y) : x_(x), y_(y) {/*empty*/}

	bool operator==(Point const& that) const {
		return fabs(this->x_-that.x_) < epsilon && fabs(this->y_-that.y_) < epsilon;
	}
};
double Point::epsilon = 1e-10;

//	rotate a set of points anti-clockwise theta radians
void rotate(std::vector<Point>& v, double theta) {
	for (size_t i = 0; i < v.size(); ++i) {
		double x = v[i].x_, y = v[i].y_;
	//	std::cout << "(" << x << "," << y << ") --> ";
		v[i].x_ = cos(theta)*x - sin(theta)*y;
		v[i].y_ = sin(theta)*x + cos(theta)*y;
	//	std::cout << "(" << v[0].x_ << "," << v[0].y_ << ")" << std::endl;
	}
}

void rotate_invariant(std::vector<Point>& v, double theta) {
	double sin_theta = sin(theta);
	double cos_theta = cos(theta);
	for (size_t i = 0; i < v.size(); ++i) {
		double x = v[i].x_, y = v[i].y_;
	//	std::cout << "(" << x << "," << y << ") --> ";
		v[i].x_ = cos_theta*x - sin_theta*y;
		v[i].y_ = sin_theta*x + cos_theta*y;
	//	std::cout << "(" << v[0].x_ << "," << v[0].y_ << ")" << std::endl;
	}
}

static inline unsigned rounded_div(unsigned numerator, unsigned denominator) {
	unsigned quotient  = numerator / denominator;
	unsigned remainder = numerator % denominator;
	if (remainder >= denominator >> 1)
		quotient += 1;
	return quotient;
}

static inline unsigned rounded_div_2(unsigned numerator, unsigned denominator) {
	unsigned round    = denominator >> 1;
	unsigned quotient = (numerator + round) / denominator;
	return quotient;
}

static inline unsigned part_size(unsigned& whole, unsigned& parts) {
	unsigned part_size = whole / parts;
	whole -= part_size;
	parts -= 1;
	return part_size;
}

void divide_into_parts(unsigned whole, unsigned parts) {
	if (parts == 0) return;
	std::cout << whole << " divided into " << parts << " parts has part sizes ";
	do {
		std::cout << part_size(whole, parts) << " ";
	} while (parts > 0);
	std::cout << std::endl;
}

// n in range 0..0x7fffffff
static inline unsigned msb_iterative(unsigned x)
{
	unsigned n=0x10000000;
	if (x == 0) return 1;
	while (x < n) 
	{
		n >>= 1;
	}
	return n;
}

static inline unsigned msb_closed(unsigned x)
{
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return(x & ~(x >> 1));
}

void test() { // test if I can call the constructor explicitly
	class FOO {
	public:
		int i_;
		FOO(int i):i_(i){}
	};
	FOO f(1);
	f.FOO::FOO(2);	//	explicit ctor call
	int j = f.i_;
}

inline bool is_power_2_iterative(unsigned n) {
	for (unsigned one_bits = 0; n != 0; n >>= 1)
		if ((n & 1) == 1)
			if (one_bits != 0)
				return false;
			else 
				one_bits += 1;
	return true;
}

inline bool is_power_2_closed(unsigned n) {
	return ((n != 0) && !(n & (n - 1)));
}

int test_statements(int test_no, unsigned long multiplier) {
	bool rc = true;
	switch (test_no) {
	case 0:	return 7;
	default:return -1;
	case 1: {
			const double pi = acos(-1.0);

			rc &= !(Point(0.0, 1.0) == Point(1.0, 0.0));

			std::vector<Point> v,w;
			v.push_back(Point(0.0, 0.0));
			w.push_back(Point(0.0, 0.0));

			v[0] = w[0] = Point(0.0, 1.0);
			rotate(v, pi/2.0);
			rotate_invariant(w, pi/2.0);
			rc &= (v[0] == Point(-1.0, 0.0));
			rc &= (v[0] == w[0]);

			v[0] = w[0] = Point(1.0, 0.0);
			rotate(v, pi/3.0);
			rotate_invariant(w, pi/3.0);
			rc &= (v[0] == Point(0.5, sin(pi/3.0)));
			rc &= (v[0] == w[0]);

			v[0] = w[0] = Point(1.0, 0.0);
			rotate(v, pi/4.0);
			rotate_invariant(w, pi/4.0);
			rc &= (v[0] == Point(cos(pi/4.0), cos(pi/4.0)));
			rc &= (v[0] == w[0]);
		}
		break;

	case 2: {//	cache loop end value
			char s[] = "This string has many space (0x20) chars. ";
			unsigned iterations = 10000 * multiplier;
			{	Stopwatch sw("string scan with strlen() evaluated each char");
				for (unsigned j = 0; j < iterations; ++j) {
					for (size_t i = 0; i < strlen(s); ++i)
						if (s[i] == ' ')
						   s[i] = ' ';
				}
			}
			{	Stopwatch sw("string scan with cached strlen()");
				for (unsigned j = 0; j < iterations; ++j) {
					for (size_t i = 0, len = strlen(s); i < len; ++i)
						if (s[i] == ' ')
							s[i] = ' ';
				}
			}
			{	Stopwatch sw("string scan with cached strlen(), do loop");
				for (unsigned j = 0; j < iterations; ++j) {
					size_t len = strlen(s);
					size_t i = 0;
					do {
						if (s[i] == ' ')
							s[i] = ' ';
						++i;
					} while (i < len);
				}
			}
			{	Stopwatch sw("string scan counting down");
				for (unsigned j = 0; j < iterations; ++j) {
					for (int i = (int)strlen(s)-1; i >= 0; --i)
						if (s[i] == ' ')
							s[i] = ' ';
				}
			}
			{	Stopwatch sw("string scan counting down, do loop");
				for (unsigned j = 0; j < iterations; ++j) {
					unsigned i = (unsigned)strlen(s);
					do {
						--i;
						if (s[i] == ' ')
							s[i] = ' ';
					} while (i > 0);
				}
			}
		}
		break;

	case 3: {//	remove invariant function calls
			const double pi = acos(-1.0);
			std::vector<Point> v;
			v.push_back(Point(1.0, 0.0));
			v.push_back(Point(7.0, 0.0));
			v.push_back(Point(6.0, 2.0));
			v.push_back(Point(7.0, 4.0));
			v.push_back(Point(6.0, 6.0));
			v.push_back(Point(7.0, 8.0));
			v.push_back(Point(6.0,10.0));
			v.push_back(Point(7.0,12.0));
			v.push_back(Point(6.0,14.0));
			v.push_back(Point(2.0,14.0));
			v.push_back(Point(1.0,12.0));
			v.push_back(Point(2.0,10.0));
			v.push_back(Point(1.0, 8.0));
			v.push_back(Point(2.0, 6.0));
			v.push_back(Point(1.0, 4.0));
			v.push_back(Point(2.0, 2.0));

			{
				Stopwatch sw("rotate");
				for (unsigned i = 0; i < 100000*multiplier; ++i)
					rotate(v, pi/1000);
			}
			{
				Stopwatch sw("rotate w/ invariant code removed");
				for (unsigned i = 0; i < 100000*multiplier; ++i)
					rotate_invariant(v, pi/1000);
			}
		}
		break;

	case 4: {// drive the even division example
		    divide_into_parts(10,3);
			divide_into_parts(17,6);
			divide_into_parts(15,5);
		}
		break;

	case 5:
		{//	float versus double 
			{	Stopwatch s("iterative fall - float");
			    for (unsigned i = 0; i < 10000*multiplier; ++i)
				{
					float d, t, a = -9.8f, v0 = 0.0f, d0 = 100.0f;
					for (t = 0.0f; t < 3.01f; t += 0.1f) {
						d = a*t*t + v0*t + d0;
					//	std::cout << "time " << t << " d " << d << std::endl;
						rc &= (d > 0);
					}
				}
			}
			{	Stopwatch s("iterative fall - double");
			    for (unsigned i = 0; i < 10000*multiplier; ++i)
				{
					double d, t, a = -9.8, v0 = 0.0, d0 = 100.0;
					for (t = 0.0; t < 3.01; t += 0.1) {
						d = a*t*t + v0*t + d0;
					//	std::cout << "time " << t << " d " << d << std::endl;
					}
				}
			}
		}
		break;

	case 6:
		{
			unsigned x = 0x444;
			std::cout << "x " << std::bitset<16>((short)x) 
				      << ", msb_iterative(x) " << std::bitset<16>((short)msb_iterative(x)) << "\n"
					  << ", msb_closed(x) " << std::bitset<16>((short)msb_closed(x)) << std::endl;

			unsigned iterations = 1000000 * multiplier;
			{	Stopwatch s("find msb iterative");
				for (unsigned i = 1; i < iterations; ++i)
					rc &= (msb_iterative(i) <= iterations);
			}
			{	Stopwatch s("find msb closed");
				for (unsigned i = 1; i < iterations; ++i)
					rc &= (msb_closed(i) <= iterations);
			}
		}
		break;

	case 7:
		{
			unsigned iterations = 100000 * multiplier;
			volatile bool ret = false;
			{
				Stopwatch sw("powers-of-2 iterative");
				for (unsigned i = 0; i < iterations; ++i)
					ret &= is_power_2_iterative(i);
			}
			{
				Stopwatch sw("powers-of-2 closed form");
				for (unsigned i = 0; i < iterations; ++i)
					ret &= is_power_2_closed(i);
			}
	}
		break;
	}
	return rc ? 1 : 0;
}

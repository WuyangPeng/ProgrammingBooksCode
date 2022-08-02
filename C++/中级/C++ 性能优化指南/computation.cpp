
# include <ctime>
# include <iostream>
# include <fstream>
# include <exception>
# include "Stopwatch03.h"	//	stopwatch class
# include "test_driver.h"

char* timetoa(char *buf, size_t bufsz) {
	if (buf == 0 || bufsz < 9)
		return nullptr; // invalid arguments

	time_t t  =  std::time(nullptr); // get time from O/S
	tm     tm = *std::localtime(&t); // break time into hours, minutes, seconds
	size_t sz = std::strftime(buf, bufsz, "%c", &tm); // format into buffer
	if (sz == 0) strcpy(buf, "XX:XX:XX"); // error
	return buf;
}

int test_log(int test_no, unsigned long multiplier) {
	bool rc = true;

	switch (test_no) {
	default: return -1;
	case 0:  return 3;
	case 1:
		{
			char buf[50];
			std::cout << timetoa(buf, sizeof(buf)) << std::endl;
		}
		break;

	case 2: 
		{
			char buf[50];
			Stopwatch sw("timetoa()");
			for (unsigned i = 0; i < 1000 * multiplier; ++i)
				timetoa(buf, sizeof(buf));
		}
		break;
	case 3:
		{
			char const filename[] = "log_tester.txt";
			std::ofstream out(filename);
			if (!out) {
				std::cout << "Can't open " << filename
					<< " for writing" << std::endl;
				return 0;
			}
			{
				char buf[50];
				timetoa(buf, sizeof(buf));
				Stopwatch sw("no timetoa()");
				for (unsigned i = 0; i < 1000 * multiplier; ++i)
					out << buf << " Test log line test log line test log line\n";
				out.flush();
			}
			out.seekp(0);
			{
				char buf[50];
				Stopwatch sw("timetoa() per 10 lines");
				for (unsigned i = 0; i < 1000 * multiplier; ++i) {
					if (i % 10 == 0)
						timetoa(buf, sizeof(buf));
					out << buf << " Test log line test log line test log line\n";
				}
				out.flush();
			}
			out.seekp(0);
			{
				char buf[50];
				Stopwatch sw("timetoa() per line");
				for (unsigned i = 0; i < 1000 * multiplier; ++i) {
					out << timetoa(buf, sizeof(buf)) << " Test log line test log line test log line\n";
				}
				out.flush();
			}
			std::remove(filename);
		}
		break;
	}
	return rc ? 1 : 0;
}

inline unsigned my_round_1(double d) {
	return (unsigned)(d + 0.5);
}

inline unsigned div0(unsigned n, unsigned d) {
	auto r = ldiv(n, d);
	return (r.rem > (d >> 1)) ? r.quot + 1 : r.quot;
}

inline unsigned div1(unsigned n, unsigned d) {
	unsigned q = n / d;
	unsigned r = n % d;
	return r > (d >> 1) ? q + 1 : q;
}

inline unsigned div2(unsigned n, unsigned d) {
	return (n + (d >> 1)) / d;
}

int test_fp(int test_no, unsigned long multiplier) {
	bool rc = true;
	switch (test_no)
	{
	default: return -1;
	case 0:  return 2;
	case 1:  
		{
			rc &= (div1(2, 5) == 0);
			rc &= (div2(2, 5) == 0);
			rc &= (div1(4, 7) == 1);
			rc &= (div2(4, 7) == 1);
		}
		break;

	case 2:
		{
			unsigned iterations = 1000000 * multiplier;
			{
				Stopwatch sw("floating round");
				for (unsigned i = 0; i < iterations; ++i)
					rc &= (i >= (unsigned)my_round_1((double)i / 3));
			}
			{
				Stopwatch sw("ldiv round");
				for (unsigned i = 0; i < iterations; ++i)
					rc &= (i >= div0(i, 3));
			}
			{
				Stopwatch sw("div1 round");
				for (unsigned i = 0; i < iterations; ++i)
					rc &= (i >= div1(i, 3));
			}
			{
				Stopwatch sw("div2 round");
				for (unsigned i = 0; i < iterations; ++i)
					rc &= (i >= div2(i, 3));
			}
	}
		break;
	}
	return rc ? 1 : 0;
}

extern int test_statements(int, unsigned long);

int(*func[])(int, unsigned long) = {
//	test_statements,
	test_log,
//	test_fp,
	0
};

int main(int argc, char** argv) {
	test_driver(func, argc, argv);
	return 0;
}
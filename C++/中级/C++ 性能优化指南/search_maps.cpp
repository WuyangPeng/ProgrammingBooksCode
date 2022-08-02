# include <iostream>		//  for std::cout
# include <string>			//	for std::string
# include <map>				//	for std::map
# include "charbuf.h"		//	simple char[] string
# include "stopwatch03.h"	//  stopwatch class

struct kv { // (key,value) pairs
    char const* key;
    unsigned    value;
};

static kv names[] = {
	{ "alpha",   1 },   { "bravo",   2 },   { "charlie", 3 },   { "delta",  4 },
    { "echo",    5 },   { "foxtrot", 6 },   { "golf",    7 },   { "hotel",  8 },
    { "india",   9 },   { "juliet", 10 },   { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 },  { "oscar",  15 },   { "papa",   16 },
    { "quebec", 17 },   { "romeo",  18 },   { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },   { "whiskey",23 },   { "xray",   24 },
    { "yankee", 25 },   { "zulu",   26 }
};
static kv test[] = {
	{ "adam",     0 },	{ "boy",     0 },	{ "charles", 0 },	{ "david",   0 },
	{ "ebenezer", 0 },	{ "ferris",  0 },	{ "george",  0 },	{ "henry",   0 },
	{ "ida",      0 },	{ "john",	 0 },	{ "karl",    0 },	{ "laurence",0 },
	{ "mary",	  0 },	{ "nora",    0 },	{ "ocean",   0 },	{ "panda",   0 },
	{ "quakka",   0 },	{ "robert",  0 },	{ "sam",     0 },	{ "tangle",  0 },
	{ "unice",    0 },	{ "vassily", 0 },	{ "waldo",   0 },	{ "xavier",  0 },
	{ "yabba",    0 },	{ "zebra",   0 },	{ "zymergy", 0 }
	,
	{ "alpha",   1 },   { "bravo",   2 },   { "charlie", 3 },   { "delta",  4 },
    { "echo",    5 },   { "foxtrot", 6 },   { "golf",    7 },   { "hotel",  8 },
    { "india",   9 },   { "juliet", 10 },   { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 },  { "oscar",  15 },   { "papa",   16 },
    { "quebec", 17 },   { "romeo",  18 },   { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },   { "whiskey",23 },   { "xray",   24 },
    { "yankee", 25 },   { "zulu",   26 }
};

bool less_for_c_strings_free(char const* p1, char const* p2) {
	return strcmp(p1,p2)<0; 
} 

int test_maps(int test_no, unsigned long multiplier) {
    bool rc = true;
    switch (test_no) {
    case 1:
        {
		}
        break;

	case 2:	//	map
		{
#	if _MSC_VER > 1600 // VS 2012 or greater
			std::map<std::string, unsigned> const kvmap 			{
				{ "alpha", 1 },		{ "bravo", 2 }, 
				{ "charlie", 3 },	{ "delta", 4 },
				{ "echo", 5 },		{ "foxtrot", 6 }, 
				{ "golf", 7 },		{ "hotel", 8 },
				{ "india", 9 },		{ "juliet", 10 }, 
				{ "kilo", 11 }, 	{ "lima", 12 },
				{ "mike", 13 },		{ "november", 14 }, 
				{ "oscar", 15 },	{ "papa", 16 },
				{ "quebec", 17 },	{ "romeo", 18 }, 
				{ "sierra", 19 },	{ "tango", 20 },
				{ "uniform", 21 },	{ "victor", 22 }, 
				{ "whiskey", 23 },	{ "xray", 24 },
				{ "yankee", 25 },	{ "zulu", 26 }
			};
#   else    //	VS 2010
			std::map<std::string, unsigned> kvmap;
			typedef std::map<std::string, unsigned>::value_type value_type;
			for (auto it = names; it != names + std::size(names); ++it)
				kvmap.insert(value_type(it->key, it->value));
#	endif

			Stopwatch st("map<string> std::less");
			for (unsigned long j = 0; j < multiplier; ++j)
				for (unsigned i = 0; i < std::size(test); ++i) {
					auto it = kvmap.find(test[i].key);
					rc &= (it == kvmap.end() || it->second < 27);
				}
		}
		{
			std::map<charbuf<>, unsigned> kvmap;
			for (auto it = names; it != names + std::size(names); ++it)
				kvmap[it->key] = it->value;

			Stopwatch st("map<charbuf>");
			for (unsigned long j = 0; j < multiplier; ++j)
				for (unsigned i = 0; i < std::size(test); ++i) {
					auto it = kvmap.find(test[i].key);
					rc &= (it == kvmap.end() || it->second < 27);
				}
		}
		//	std::map<char*, unsigned> kvmap; compiles, but doesn't work because < applies to pointers
		{
			std::map<char const*,  unsigned, bool(*)(char const*,char const*)> kvmap(less_for_c_strings_free);
			typedef std::map<char const*,  unsigned, bool(*)(char const*,char const*)>::value_type value_type;
			for (auto it = names; it != names + std::size(names); ++it)
				kvmap.insert(value_type(it->key, it->value));

			Stopwatch st("map<char*> free function");
			for (unsigned long j = 0; j < multiplier; ++j)
				for (unsigned i = 0; i < std::size(test); ++i) {
					auto it = kvmap.find(test[i].key);
					rc &= (it == kvmap.end() || it->second < 27);
				}
		}
		{
			struct less_for_c_strings {
				bool operator()(char const* p1, char const* p2) const { return strcmp(p1,p2)<0; }
			};
			std::map<char const*,  unsigned, less_for_c_strings> kvmap;
			typedef std::map<char const*,  unsigned, less_for_c_strings>::value_type value_type;
			for (auto it = names; it != names + std::size(names); ++it)
				kvmap.insert(value_type(it->key, it->value));

			Stopwatch st("map<char*> function-object");
			for (unsigned long j = 0; j < multiplier; ++j)
				for (unsigned i = 0; i < std::size(test); ++i) {
					auto it = kvmap.find(test[i].key);
					rc &= (it == kvmap.end() || it->second < 27);
				}
		}
		{
#	if (_MSC_VER < 1700) || (_MSC_VER > 1800)	
			auto comp = [](char const* p1, char const* p2) { return strcmp(p1,p2)<0; };
			std::map<char const*, unsigned, decltype(comp)> kvmap(comp);
			typedef std::map<char const*, unsigned, decltype(comp)>::value_type value_type;
			for (auto it = names; it != names + std::size(names); ++it)
				kvmap.insert(value_type(it->key, it->value));

			Stopwatch st("map<char*> lambda");
#	else
		/*	VS 2012-13 contained a bug in the standard library code that prevented
			them processing the lambda decltype. Turns out that a lambda with no 
			capture decays into a function pointer, so this construction works.
		*/
			auto comp = [](char const* p1, char const* p2) { return strcmp(p1, p2)<0; };
			std::map<char const*, unsigned, bool(*)(char const*, char const*)> kvmap(comp);
			typedef std::map<char const*, unsigned, decltype(comp)>::value_type value_type;
			for (auto it = names; it != names + std::size(names); ++it)
				kvmap.insert(value_type(it->key, it->value));

			Stopwatch st("map<char*> lambda decay");
#	endif
			for (unsigned long j = 0; j < multiplier; ++j)
				for (unsigned i = 0; i < std::size(test); ++i) {
					auto it = kvmap.find(test[i].key);
					rc &= (it == kvmap.end() || it->second < 27);
				}
		}
		break;

    case 0: return 2;
    default:return -1;
    }
    return (rc) ? 1 : 0;
}

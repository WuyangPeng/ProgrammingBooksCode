#include <iostream>
#include <cassert>
#include <cstring>

void StrCpy (char * strDest, char const * strSrc);
int StrCmp (char const * str1, char const * str2);
void StrNCpy (char * strDest, char const * strSrc, std::size_t len);

int main (int count, char * argv [])
{
	for (int i = 0; i < count; ++i)
	{
		std::cout << i << ": " << argv [i] << std::endl;
	}
	char src [] = "Original";
	char dst [10];
	StrCpy (dst, src);
	std::cout << dst << std::endl;
	int diff = StrCmp ("abc", "abc");
	assert (diff == 0);
	diff = StrCmp ("abc", "abcd");
	assert (diff < 0);
	diff = StrCmp ("abcd", "abc");
	assert (diff > 0);
	diff = StrCmp ("abcd", "abdd");
	assert (diff < 0);
	std::cout << "String comparison test: passed\n";
	StrNCpy (dst, "Source", 10);
	std::cout << dst << std::endl;
}

void StrCpy (char * strDest, char const * strSrc)
{
	int i = 0;
	char c;
	do
	{
		c = strSrc [i];
		strDest [i] = c;
		++i;
	} while (c != '\0');
}

int StrCmp (char const * str1, char const * str2)
{
	int i = 0;
	while (str1 [i] != '\0')
	{
	 	int diff = str1 [i] - str2 [i];
	 	// this also takes care of end of str2
	 	if (diff != 0)
	 		return diff;
	 	++i;
	}
	if (str2 [i] == '\0')
		return 0;
	// str1 is shorter
	return -1;
}

void StrNCpy (char * strDest, char const * strSrc, std::size_t len)
{
	for (std::size_t i = 0; i < len; ++i)
	{
		strDest [i] = strSrc [i];
		// early exit
		if (strSrc [i] == '\0')
			break;
	}
}

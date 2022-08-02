// Bartosz Milewski (c) 2000
#include "HTab.h"
#include <iostream>
#include <cstring>

char const * strTab [] = { "zero", "one", "two", "three" };

int main ()
{
	{
		HTable tab (3);
		int count = sizeof (strTab) / sizeof (char const *);
		for (int i = 0; i < count; ++i)
			tab.Add (strTab [i], i);
	}
	HTable tab (3);
	int count = sizeof (strTab) / sizeof (char const *);
	for (int i = 0; i < count; ++i)
		tab.Add (strTab [i], i);
	tab.Add ("four", 4);
	for (int i = 0; i < count; ++i)
	{
		char const * str = strTab [i];
		for (HTable::Seq seq (tab, str); !seq.AtEnd (); seq.Advance ())
		{
			if (std::strcmp (str, strTab [seq.GetValue ()]) == 0)
				std::cout << "Found " << str << " with value " << seq.GetValue () << std::endl;
		}
	}
}
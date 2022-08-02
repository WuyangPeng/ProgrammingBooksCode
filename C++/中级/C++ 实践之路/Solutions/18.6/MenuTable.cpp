#include "MenuTable.h"
// Bartosz Milewski (c) 2000

namespace Menu
{
	const Item programItems [] =
	{
		{CMD,        "&About...", "Program_About"},
		{SEPARATOR,  0,           0},
		{CMD,        "E&xit",     "Program_Exit"},
		{END,        0,           0}
	};
	const Item memoryItems [] =
	{
		{CMD,        "&Clear",    "Memory_Clear"},
		{SEPARATOR,  0,           0},
		{CMD,        "&Save...",  "Memory_Save"},
		{CMD,        "&Load...",  "Memory_Load"},
		{END,        0,           0}
	};
	//---- Menu bar ----
	const BarItem barItems [] =
	{
		{POP,   "P&rogram", "Program",   programItems},
		{POP,   "&Memory",  "Memory",    memoryItems},
		{END,   0,          0,           0}
	};
}
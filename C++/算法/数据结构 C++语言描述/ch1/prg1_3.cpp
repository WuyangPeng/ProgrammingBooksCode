// File prg1_3.cpp
// the program prompts the user for the pathname of a file.
// it uses string class operations to identify and output
// the pathname and filename. if the filename has the
// extension "cpp", create and output the name
// of an executable file whose extension "exe" replaces
// the extension "cpp"

#include <iostream>
#include <string>

using namespace std;

int main()
{
	string pathname, path, filename, executableFile;
	// index of '\' and '.'
	int backslashIndex, dotIndex;

	cout << "Enter the path name: ";
	cin >> pathname;


	// identify index of last '\'. note: because
	// escape codes such as '\n' begin with \,
	// C++ represents \ by '\\'
	backslashIndex = pathname.find_last_of('\\');

	// pathname is characters prior to the last '\'
	path = pathname.substr(0,backslashIndex);

	cout << "Path:       " << path << endl;

	// tail of pathname is the filename
	filename = pathname.substr(backslashIndex+1,-1);
	cout << "Filename:   " << filename << endl;

	// see if the filename has the extension ".cpp".
	// first find the index of the last '.'. if there
	// is no '.', dotIndex is -1
	dotIndex = filename.find_last_of('.');
	// test if there is a '.' and the remaining characters are
	// "cpp"
	if (dotIndex != -1 && filename.substr(dotIndex+1) == "cpp")
	{
		// setup string executable by erasing "cpp" and appending "exe"
		executableFile = filename;
		executableFile.erase(dotIndex+1,3);
		executableFile += "exe";
		cout << "Executable: " << executableFile << endl; 
	}

	return 0;
}

/*
Run 1:

Enter the path name: \class\programs\testfile
Path:       \class\programs
Filename:   testfile

Run 2:

Enter the path name: programs\strings\filedemo.cpp
Path:       programs\strings
Filename:   filedemo.cpp
Executable: filedemo.exe

Run 3:

Enter the path name: \program.cpp
Path:
Filename:   program.cpp
Executable: program.exe
*/

// File: hdecompress.cpp
// the program demonstrates Huffman decompression.
// after prompting for the name of the compressed
// file and the name for the decompressed file,
// an object of type hDecompress is declared, and
// the member function decompress() decompresses
// the file

#include <string>

#include "d_hdcomp.h"

using namespace std;

int main()
{
	string compFile, ucompFile;

	// prompt for the name of the compressed file and the
	// name for the decompressed file
	cout << "Compressed file name: ";
	cin >> compFile;
	cout << "Name for uncompressed file: ";
	cin >> ucompFile;

	hDecompress dcomp(compFile, ucompFile);

	// uncompress the file
	dcomp.decompress();

	return 0;
}

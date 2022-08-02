// File: hcompress.cpp
// the program demonstrates Huffman compression. the user
// enters the name of a file to compress and indicates
// whether the verbose option is desired. after compressing
// the file, the program outputs the compression ratio.
// if the Huffman tree has no more than 11 nodes, the tree
// is displayed

#include <iostream>
#include <string>

#include "d_hcomp.h"		// hCompress class
#include "d_util.h"		// for setreal()

using namespace std;

int main()
{
	string fileName;
	bool verbose;
	char response;

	// prompt for the source file name and whether
	// to use the verbose option for Huffman compression
	cout << "File name: ";
	cin >> fileName;
	cout << "Verbose (y or n): ";
	cin >> response;
	if (response == 'y')
		verbose = true;
	else
		verbose = false;

	cout << endl;

	// declare an hCompress object
	hCompress hc(fileName, verbose);

	// compress the file
	hc.compress();

	// output the compression ratio
	cout << "The compression ratio = "
		  << setreal(1,2) << hc.compressionRatio()
		  << endl << endl;

	if (hc.size() <= 11)
		// display the Huffman tree if the tree is small
		hc.displayTree();

	return 0;
}

/*
Run 1:

File name: demo.dat
   (16 'a'   4 'b'   8 'c'   6 'd'   20 'e'   3 'f')
Verbose (y or n): y

Frequency analysis ...
   File size: 57000 characters
   Number of unique characters: 6

Building the Huffman tree ...
   Number of nodes in Huffman tree: 11

Generating the Huffman codes ...

Tree has 11 entries.  Root index = 10

Index  Sym      Freq    Parent  Left   Right  NBits    Bits
   0     a     16000      9      -1     -1      2      10
   1     b      4000      6      -1     -1      4      0111
   2     c      8000      8      -1     -1      2      00
   3     d      6000      7      -1     -1      3      010
   4     e     20000      9      -1     -1      2      11
   5     f      3000      6      -1     -1      4      0110
   6   Int      7000      7       5      1
   7   Int     13000      8       3      6
   8   Int     21000     10       2      7
   9   Int     36000     10       0      4
  10   Int     57000      0       8      9

Generating the compressed file

The compression ratio = 3.39 (size of demo.huf = 16,822 bytes)

                                                  57000

        21000                                                   36000

 c:8000               13000                              a:16000       e:20000

               d:6000               7000

                             f:3000        b:4000

Run 2:

File name: webster.dict
	(234,946 words, each on a separate line.
	 Total of 2,721,849 characters)
Verbose (y or n): n

The compression ratio = 1.81 (size of webster.huf = 1,502,436 bytes)

Run 3:

File name: mspaint.exe
	(application. size = 344,064 bytes)
Verbose (y or n): n

The compression ratio = 1.36 (size of mspaint.huf = 253,663 bytes)
*/

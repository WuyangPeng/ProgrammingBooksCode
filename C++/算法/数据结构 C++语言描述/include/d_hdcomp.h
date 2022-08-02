#ifndef HUFFMAN_DECOMPRESS
#define HUFFMAN_DECOMPRESS

#include <iostream>
#include <fstream>
#include <string>

#include "d_except.h"
#include "d_bitvec.h"	// use BitVector for all bit handling
#include "d_hnode.h"		// diskHuffNode class

class hDecompress
{
	public:
		hDecompress(const string& cname, const string& uname);
			// constructor. calls setFiles() to open Huffman
			// compressed file cname and assign the output
			// file name uname.

		void setFiles(const string& cname, const string& uname);
			// open Huffman compressed file cname
			// and assign the output file name uname.
			// throws the fileOpenError exception if a file
			// cannot be opened

		void decompress();
			// decompress the file

	private:

		fstream source;
		fstream dest;
			// input and output streams

		bool filesOpen;
			// are source and dest open?
};

hDecompress::hDecompress(const string& cname,
								 const string& uname): filesOpen(false)
{
	setFiles(cname, uname);
}

void hDecompress::setFiles(const string& cname, const string& uname)
{
	if (filesOpen)
	{
		source.close();
		dest.close();
	}

	// a Huffman compressed file is a binary file
	source.open(cname.c_str(), ios::in | ios::binary);
	if (!source)
		throw fileOpenError(cname);

	// output using binary mode. we don't want '\n' expanded
	// to an end of line sequence. if the output file is a
	// textfile, its end of line characters were compressed
	// individually
	dest.open(uname.c_str(), ios::out | ios::binary | ios::trunc);

	if (!dest)
		throw fileOpenError(uname);

	filesOpen = true;
}

void hDecompress::decompress()
{
	int i, bitPos;

	// treeSize and totalBits are read from the compressed file
	short treeSize;
	long totalBits;
	// treeSize diskHuffNode nodes are read from the compressed file
	// into tree
	vector<diskHuffNode> tree;
	// totalBits number of binary bits are read from the compressed
	// file into bits
	bitVector bits;
	
	// input the Huffman tree size
	source.read((char *)&treeSize, sizeof(short));

	// resize the vector holding the Huffman tree and
	// input the tree
	tree.resize(treeSize);
	source.read((char *)&tree[0], sizeof(diskHuffNode) * treeSize);

	// input the number of bits of Huffman code
	source.read((char *)&totalBits, sizeof(long));

	// input the Huffman codes for the characters
	bits.read(source, totalBits);
	
	// restore the original file by using the Huffman codes to
	// traverse the tree and write out the corresponding
	// characters
	bitPos = 0;
	while (bitPos < totalBits)
	{
		// root of the tree is at index treeSize-1
		i = treeSize-1;
		// follow the bits until we arrive at a leaf node
		while (tree[i].left != -1)
		{
			// if bit is 0, go left; otherwise, go right
			if (bits.bit(bitPos) == 0)
				i = tree[i].left;
			else
				i = tree[i].right;
			// we have used the current bit. move to the
			// next one
			bitPos++;
		}
		// we are at a leaf node. output the character
		// to the file
		dest.put(tree[i].ch);
	}

	// close the two streams
	source.close();
	dest.close();

	filesOpen = false;
}

#endif	// HUFFMAN_DECOMPRESS

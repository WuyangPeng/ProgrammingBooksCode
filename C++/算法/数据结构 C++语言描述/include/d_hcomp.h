#ifndef HUFFMAN_COMPRESS
#define HUFFMAN_COMPRESS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <functional>

#include "d_hnode.h"		// Huffman node classes and node display
#include "d_pqueue.h"	// miniPQ class
#include "d_bitvec.h"	// use btVector for all bit handling

// number of ASCII characters
const int MAXCHARS = 256;

class hCompress
{
	public:
		hCompress(const string& fname, bool v = false);
			// constructor. call setFile() to open the
			// source file fname, and create a binary output file
			// by adding extension ".huf". any previous extension is
			// replaced. v determines if progress messages are
			// output

		void setFile(const string& fname);
			// open the source file fname and create a binary output
			// file with extension ".huf". throws the
			// fileOpenError exception if the input or output
			// file cannot be opened

		void compress();
			// compress the file

		double compressionRatio() const;
			// return the compression ratio

		int size() const;
			// return the number of nodes in the
			// Huffman tree

		void displayTree() const;
			// display the Huffman tree. recommended
			// only if tree size is <= 11

	private:

		fstream source;
		fstream dest;
			// input and output streams
		vector<int> charFreq, charLoc;
			// charFreq used to count character frequencies. charLoc
			// maintains Huffman tree indices for characters present
			// in the file
		int numberLeaves;
			// numberLeaves is number of leaf nodes (character nodes)
			// in the tree
		short treeSize;
			// number of Huffman tree nodes in the compressed file
		vector<huffNode> tree;
			// stores the Huffman tree
		bool verbose;
			// are progress messages output?
		long fileSize;
			// size of the source file
		long totalBits;
			// total number of bits used in the compressed image
			// of the source file
		bool oneChar;
			// does the tree have only 1 unique character?
		bool filesOpen;
			// are source and dest open?

		void freqAnalysis();
			// determine the frequencies of the characters in the
			// source file and store them in charFreq. while doing
			// this, determine numberLeaves. also tabulate
			// fileSize so we can see how much savings the
			// compression algorithm gives us

		void buildTree();
			// build the Huffman tree

		void generateCodes();
			// for each leaf node, go up the tree and determine the Huffman
			// code for the character. compute the total number of bits of
			// compressed data

		void writeCompressedData();
			// reread the source file and write the Huffman codes specified
			// by the Huffman tree to the stream dest

		void treeData();
			// output Huffman tree data
};

void hCompress::freqAnalysis()
{
	unsigned char ch;

	numberLeaves = 0;
	fileSize = 0;

	while (true)
	{
		// get the next character
#ifdef __GNUC__
		source.get(ch);
#else
		ch = source.get();
#endif	// __GNUC__

		if (!source)
			break;

		// found 1 more char in the source file
		fileSize++;

		// count an occurrence of ch
		charFreq[ch]++;

		// if first time we have found ch, count it as a leaf
		if (charFreq[ch] == 1)
			numberLeaves++;
	}
	if (verbose)
		cout << "   File size: " << fileSize << " characters" << endl
			  << "   Number of unique characters: "
			  << numberLeaves << endl << endl;
}

void hCompress::buildTree()
{
	// sequences through Huffman tree nodes
	int i, nodeIndex;
	// capture nodes coming out of the priority queue
	huffNode x, y;
	// priority queue used to build the Huffman tree
	miniPQ<huffNode, less<huffNode> > pq;

	// handle the special case of a file with only one
	// unique character
	if (numberLeaves == 1)
	{
		// set number of leaves to 2 and add a leaf node
		// at either index 0 or 1, since one of those
		// characters is not present in the file
		numberLeaves = 2;
		if (charFreq[0] != 0)
			charFreq[1] = 1;
		else
			charFreq[0] = 1;

		// record that we have added a "filler" node
		oneChar = true;
	}
	else
		oneChar = false;

	// the size of the tree is exactly 2*numberLeaves-1
	treeSize = 2*numberLeaves - 1;
	tree.resize(treeSize);

	// index of the tree node we are building
	nodeIndex = 0;

	// start by building each leaf node:
	//    value = char(i)
	//    left/right = NIL,
	//    frequency = charFreq[i]
	//    index = nodeIndex
	//		parent, numberOfBits, maxSizeOfBits default
	// record index of leaf node in charLoc. insert node into
	// the heap
	for (i=0; i < MAXCHARS; i++)
		if (charFreq[i] != 0)
		{
			tree[nodeIndex] = huffNode((unsigned char)(i), NIL, NIL,
				                        charFreq[i], nodeIndex);
			pq.push(tree[nodeIndex]);
			// record index of this leaf node for use in
			// writeCompressedData()
			charLoc[i] = nodeIndex;
			// get ready to build next node
			nodeIndex++;
		}

	// for numberLeaves-1 iterations, remove pairs of nodes,
	// create the parent, and insert the parent into the tree
	for (i=1; i <= numberLeaves-1; i++)
	{
		// remove the two nodes with least frequency. these are
		// copies of nodes in the vector, tree, at indices x.index
		// and y.index
		x = pq.top();
		pq.pop();
		y = pq.top();
		pq.pop();

		// create a parent (interior) node whose children are
		// at indices x.index, y.index in the array tree and
		// whose frequency is the sum of those in x and y. the
		// node's index is nodeIndex, and the parent of this node
		// is (temporarily) 0, and so are the number of bits and
		// the maximum size of the bitvector
		tree[nodeIndex] = huffNode(char(0), x.index, y.index,
											x.freq + y.freq,
											nodeIndex, 0, 0, 0);

		// use x.index and y.index to assign nodeIndex as the parent
		// of x and y
		tree[x.index].parent = nodeIndex;
		tree[y.index].parent = nodeIndex;

		// insert the new parent into the heap
		pq.push(tree[nodeIndex]);

		nodeIndex++;
	}
	if (verbose)
		cout << "   Number of nodes in Huffman tree: "
			  << treeSize << endl << endl;
}

void hCompress::generateCodes()
{
	int i, j;
	int bitNumber, current, parent;
	// use to compute each character's bit code
	bitVector bits(MAXBITSIZE);

	totalBits = 0;

	// the nodes tree[0], tree[1], ..., tree[numberLeaves-1] are
	// all leaf nodes. for each leaf, follow the parent index
	// up to the root and build the bit code for the character
	for (i=0; i < numberLeaves; i++)
	{
		// starting bit number of 0
		bitNumber = 0;
		// clear all the bits in the BitVector object bits
		bits.clear();
		// parent of our current leaf node
		parent = tree[i].parent;
		// identify the current node
		current = i;

		// continue generating bits until we hit the root,
		// whose parent is 0
		while (parent != 0)
		{
			// if the current node is the right child
			// of parent, add a 1 to bits at bitNumber.
			// otherwise, the bit is a 0, and bits
			// began with all zeros
			if (tree[parent].right == current)
				bits.set(bitNumber);
			// advance to the next bit number
			bitNumber++;
			// find the next parent
			current = parent;
			parent = tree[current].parent;
		}

		// the concluding value of bitNumber is the number of
		// bits in the Huffman code for tree[i].ch
		tree[i].numberOfBits = bitNumber;

		// copy the Huffman code from bits to tree[i].bits.
		// the order must be reversed
		for (j=bitNumber-1; j >= 0; j--)
			if (bits.bit(j) == 1)
				tree[i].bits.set(bitNumber-1-j);

		// add the bit contribution of the character
		// to the total number of bits. in other words,
		// add the path weight of the leaf node to the
		// external path weight
		totalBits += bitNumber * tree[i].freq;
	}
}

void hCompress::writeCompressedData()
{
	// vector that will contain the Huffman codes for
	// the compressed file
	bitVector compressedData(totalBits);
	int bitPos, i, j;
	unsigned char ch;

	// clear end-of-file for the source file and set file
	// pointer to the beginning of the file
	source.clear(0);
	source.seekg(0, ios::beg);

	// bitPos is used to put bits into compressedData
	bitPos = 0;

	// re-read the source file and generate the Huffman codes in
	// compressedData
	while (true)
	{
		// get the next character
#ifdef __GNUC__
		source.get(ch);
#else
		ch = source.get();
#endif	// __GNUC__

		if (!source)
			break;

		// index of the tree node containing ch
		i = charLoc[ch];

		// put the bit code for tree[i].ch into the bit vector
		for (j=0;j < tree[i].numberOfBits; j++)
		{
			// only need to call set() if tree[i].bits.bit(j) is 1
			if (tree[i].bits.bit(j) == 1)
				compressedData.set(bitPos);
			// always advance bitPos
			bitPos++;
		}
	}

	// write the bit codes to the output file
	compressedData.write(dest);
}

void hCompress::treeData()
{
	int i, j;

	cout << "Tree has " << treeSize << " entries.  Root index = "
		  << treeSize-1 << endl << endl;

	// table header
	cout << setw(3) << "Index" << setw(5) << "Sym" << setw(10)
		  << "Freq" << setw(10) << "Parent"
		  << setw(6) << "Left" << setw(8) << "Right"
		  << setw(7) << "NBits" << setw(8) << "Bits" << endl;

	// generate the table lines
	for (i=0;i < treeSize;i++)
	{
		cout << setw(4) << i;
		if (' ' <= tree[i].ch && tree[i].ch <= '~')
			cout << setw(6) << tree[i].ch;
		else if (i < numberLeaves)
		{
			cout << setw(4) << "0x";
			cout << setfill('0') << setw(2) << hex
				  << int(tree[i].ch) << dec << setfill(' ');
		}
		else
			cout << setw(6) << "Int";
		cout << setw(10) << tree[i].freq << setw(7)
			  << tree[i].parent << setw(8)
			  << tree[i].left << setw(7) << tree[i].right;
		if (tree[i].numberOfBits != 0)
			  cout << setw(7) << tree[i].numberOfBits;
		for (j=0;j < tree[i].numberOfBits;j++)
			if (tree[i].bits.bit(j))
				// only use setw(7) once
				if (j == 0)
					cout << setw(7) << 1;
				else
					cout << 1;
			else
				// only use setw(7) once
				if (j == 0)
					cout << setw(7) << 0;
				else
					cout << 0;
		cout << endl;
	}
	cout << endl;
}

// constructor must initialize charFreq and charLoc to
// have MAXCHARS characters
hCompress::hCompress(const string& fname, bool v):
	charFreq(MAXCHARS), charLoc(MAXCHARS), verbose(v), filesOpen(false)
{
	setFile(fname);
}

void hCompress::setFile(const string& fname)
{
	string ofname;
	int i;

	if (filesOpen)
	{
		source.close();
		dest.close();
	}

	// input using binary mode. we don't want the end of line
	// sequence translated to '\n'
	source.open(fname.c_str(), ios::in | ios::binary);

	if (!source)
		throw fileOpenError(fname);

	ofname = fname;

	// if the original file name ends with an extension (".xxx"),
	// remove the extension. in any case, add the extension ".huf".

	// find the last occurrence of '.'
	if ((i = ofname.find_last_of('.')) != -1)
		// there is an extension. remove everything
		// from '.' to the end of the string
		ofname.erase(i);
	// add ".huf" as the extension
	ofname += ".huf";

	// open the compressed image file in binary mode
	dest.open(ofname.c_str(), ios::out | ios::binary | ios::trunc);

	if (!dest)
		throw fileOpenError(ofname);

	filesOpen = true;
}

void hCompress::compress()
{
	int i;
	diskHuffNode tmp;

	if (verbose)
		cout << "Frequency analysis ..." << endl;
	// do the frequency analysis
	freqAnalysis();

	if (verbose)
		cout << "Building the Huffman tree ..." << endl;
	// build the Huffman tree
	buildTree();

	if (verbose)
		cout << "Generating the Huffman codes ..." << endl << endl;
	// generate the Huffman code for each character and compute
	// the total number of bits in the compressed characters
	generateCodes();
	// if verbose selected, output tree data now that the codes
	// are complete
	if (verbose)
		treeData();

	if (verbose)
		cout << "Generating the compressed file" << endl << endl;
	// output tree size
	dest.write((char *)&treeSize, sizeof(short));
	// output the tree. note that we output only the base class
	// portion of a huffNode object. all decompress needs is
	// the character and the child pointers
	for (i=0; i < treeSize; i++)
	{
		tmp = (diskHuffNode)tree[i];
		dest.write((char *) &tmp, sizeof(diskHuffNode));
	}
	// for a source file containing a single unique character,
	// delete the extra bit that was added to the total cost
	// because of the additional leaf node
	if (oneChar)
		totalBits--;
	// output the number of bits of Huffman code
	dest.write((char *)&totalBits, sizeof(long));
	// read through the source file and write the Huffman
	// codes for the characters found in tree to dest
	writeCompressedData();

	// close both files
	source.close();
	dest.close();

	filesOpen = false;
}

double hCompress::compressionRatio() const
{
	double compRatio;

	// determine the ratio of the size of the compressed file
	// to the size of the orginal
	compRatio = double(fileSize)/
		   ( sizeof(short) + treeSize*sizeof(diskHuffNode) +
			 sizeof(long) + (totalBits+7)/8 );

	return compRatio;
}

int hCompress::size() const
{
	return treeSize;
}

void hCompress::displayTree() const
{
	displayHuffmanTree(tree);
	cout << endl << endl << endl;
}

#endif	// HUFFMAN_COMPRESS

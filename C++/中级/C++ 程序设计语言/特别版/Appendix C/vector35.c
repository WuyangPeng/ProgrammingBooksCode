// Simple multidimensional vector test.

// pp 836-837

// No guarantees offered. Constructive comments to bs@research.att.com


#include<vector>
#include<iostream>
using namespace std;

vector< vector<int> > m(3, vector<int>(5));

void init_m()
{
	for (int i = 0; i<m.size(); i++)
		for (int j = 0; j<m[i].size(); j++) m[i][j] = 10*i+j;
}

void print_m()
{
	for (int i = 0; i<m.size(); i++) {
		for (int j = 0; j<m[i].size(); j++) cout << m[i][j] << '\t';
		cout << '\n';
	}
}

int main()
{
	init_m();
	print_m();
}

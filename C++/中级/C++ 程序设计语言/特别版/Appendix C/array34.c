// Simple multidimensional array test.
// Note that using  vectors is simpler

// pp 837-840

// No guarantees offered. Constructive comments to bs@research.att.com

#include<iostream>
using namespace std;

void print_m34(int m[3][4])
{
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<4; j++) cout << m[i][j] << '\t';
		cout << '\n';
	}
}

void print_mi4(int m[][4], int dim1)
{
	for (int i = 0; i<dim1; i++) {
		for (int j = 0; j<4; j++) cout << m[i][j] << '\t';
		cout << '\n';
	}
}

void print_mij(int* m, int dim1, int dim2)
{
	for (int i = 0; i<dim1; i++) {
		for (int j = 0; j<dim2; j++)
			cout << m[i*dim2+j] << '\t'; // obscure
		cout << '\n';
	}
}


int main()
{
	int v[3][4] = { {0,1,2,3}, {10,11,12,13}, {20,21,22,23} };

	print_m34(v);
	cout << '\n';
	print_mi4(v,3);
	cout << '\n';
	print_mij((int*)v,3,4);
	cout << '\n';
	print_mij(v[0],3,4);	// also ok
	cout << '\n';
//	print_mij(v,3,4);	// error
}

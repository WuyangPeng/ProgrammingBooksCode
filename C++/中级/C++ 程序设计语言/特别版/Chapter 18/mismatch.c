// Simple test program to demonstrate mismatch() and predicate

// pg 516 and pg 523

// No guarantees offered. Constructive comments to bs@research.att.com

#include<vector>
#include<list>
#include<algorithm>
#include<functional>
#include<iostream>
using namespace std;

void m1(vector<int>& vi, list<int>& li)
{
	typedef list<int>::iterator LI;
	typedef vector<int>::iterator VI;
	pair<VI,LI> p1 = mismatch(vi.begin(),vi.end(),li.begin(),less<int>());

	cout << "m1: " << *p1.first << " " << *p1.second << endl;
}

void m2(vector<int>& vi, list<int>& li)
{
	typedef list<int>::iterator LI;
	typedef vector<int>::iterator VI;
	pair<VI,LI> p1 = mismatch(vi.begin(),vi.end(),li.begin(),greater_equal<int>());

	cout << "m2: " << *p1.first << " " << *p1.second << endl;
}

void m3(vector<int>& vi, list<int>& li)
{
	typedef list<int>::iterator LI;
	typedef vector<int>::iterator VI;
	pair<LI,VI> p1 = mismatch(li.begin(),li.end(),vi.begin(),less_equal<int>());

	cout << "m3: " << *p1.second << " " << *p1.first << endl;
}

void m4(vector<int>& vi, list<int>& li)	// revised example from _algo.pred_
{

	typedef list<int>::iterator LI;
	typedef vector<int>::iterator VI;
	pair<VI,LI> p1 =  mismatch(vi.begin(),vi.end(),li.begin(),not2(less<int>()));
	cout << "m4: " << *p1.first << " " << *p1.second << endl;
}

int main()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	list<int> lst;
	lst.push_back(1);
	lst.push_back(1);
	lst.push_back(3);
	lst.push_back(3);
	lst.push_back(5);


	m1(v,lst);
	m2(v,lst);
	m3(v,lst);
	m4(v,lst);
}

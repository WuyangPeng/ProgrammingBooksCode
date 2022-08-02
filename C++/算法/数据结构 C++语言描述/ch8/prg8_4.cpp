// File: prg8_4.cpp
// the jobRequest class maintains information about the
// type of employee (Clerk, Supervisor, Manager, President),
// a job ID, and the number of minutes a job should take
// a company secretarial pool. the program inputs job data
// from the file "job.dat" inserts it into the priority queue
// jobPool. while popping elements from jobPool, the
// category of employee, job ID, and estimated job time
// are output. during the process, the vector jobServicesUse
// maintains the total service time for each category of
// employee. the function writeJobSummary() outputs the
// accumulated data

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>		// priority_queue class

#include "d_job.h"	// jobRequest class

using namespace std;

// output total pool time allocated to each employee category
void writeJobSummary(const vector<int>& jobServicesUse);

int main()
{
	// handle job requests
	priority_queue<jobRequest> jobPool;

	// job requests are read from fin
	ifstream fin;

	// time spent working for each category of employee
	vector<int> jobServicesUse(4,0);	// initial time 0 for each category

	jobRequest job;

	// open "job.dat" for input. exit program if open fails
	fin.open("job.dat");
	if (!fin)
	{
		cerr << "Cannot open file 'job.dat'" << endl;
		exit(1);
	}

	// read file. insert each job into priority queue jobPool.
	while (true)
	{
		fin >> job;
		if (!fin)
			break;

		// insert job into the priority queue
		jobPool.push(job);
	}
  
	// delete jobs from priority queue and output information
	cout << "Category     Job ID    Job Time" << endl << endl;
	while (!jobPool.empty())
	{
		// remove a job from the priority queue and output it
		job = jobPool.top();
		jobPool.pop();
		cout << job;

		// accumulate job time for the category of employee
		jobServicesUse[int(job.getStatus())] += job.getJobTime();
	}
	cout << endl;
    
	writeJobSummary(jobServicesUse);

	return 0;
}

void writeJobSummary(const vector<int>& jobServicesUse)
{
	cout << "Total Pool Usage"  << endl;
	cout << "   Clerk        "  << setw(3)
		  << jobServicesUse[0]   << endl;
	cout << "   Supervisor   "  << setw(3)
		  << jobServicesUse[1]   << endl;
	cout << "   Manager      "  << setw(3)
		  << jobServicesUse[2]   << endl;
	cout << "   President    "  << setw(3)
		  << jobServicesUse[3]   << endl;
}

/*
Input file "job.dat"

Supervisor 300 20
Clerk 301 30
Supervisor 302 40
President 303 25
Manager 304 10
Manager 305 40
President 306 50
Supervisor 307 70
Clerk 308 20
Clerk 309 20
Supervisor 310 60
Manager 311 30

Run:

Category     Job ID    Job Time

President      303        25
President      306        50
Manager        305        40
Manager        311        30
Manager        304        10
Supervisor     302        40
Supervisor     310        60
Supervisor     300        20
Supervisor     307        70
Clerk          301        30
Clerk          309        20
Clerk          308        20

Total Pool Usage
   Clerk         70
   Supervisor   190
   Manager       80
   President     75
*/

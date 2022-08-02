#ifndef JOBREQUEST
#define JOBREQUEST

#include <iostream>
#include <string>

using namespace std;

// class defining a job request
class jobRequest
{
	public:
		enum staff {Clerk=0, Supervisor=1, Manager=2, President=3};
			// employee priority level

		jobRequest();
			// default constructor. assign data members using stream
			// operator >>
		jobRequest(staff stat, int jid, int jtime);

		staff getStatus() const;
		int getJobID() const;
		int getJobTime() const;

		friend ostream& operator<< (ostream& ostr, const jobRequest& req);
		friend istream& operator>> (istream& istr, jobRequest& req);
			// I/O operations

		friend bool operator < (const jobRequest& a, const jobRequest& b);
			// compare job requests by status
	private:
		staff status;
		int jobID;
		int jobTime;
};

jobRequest::jobRequest()
{}

jobRequest::staff jobRequest::getStatus() const
{
  return status;
}

int jobRequest::getJobID() const
{
  return jobID;
}

int jobRequest::getJobTime() const
{
  return jobTime;
}

ostream& operator<< (ostream& ostr, const jobRequest& req)
{
	switch (req.status)
	{
		case jobRequest::President:	ostr << "President      ";
												break;
		case jobRequest::Manager:		ostr << "Manager        ";
												break;
		case jobRequest::Supervisor:	ostr << "Supervisor     ";
												break;
		case jobRequest::Clerk:			ostr << "Clerk          ";
												break;
	}
	ostr << req.jobID << "        " << req.jobTime << endl;

	return ostr;
}

istream& operator>> (istream& istr, jobRequest& req)
{
	 string empType;

	 // each line starts with a string that identifies the
	 // type of employee. assign status field
	 istr >> empType;

	 // return is we encounter EOF
	 if (!istr)
		 return istr;

	 switch(empType[0])
	 {
		case 'P':   req.status = jobRequest::President;
						break;
		case 'M':   req.status = jobRequest::Manager;
						break;
		case 'S':   req.status = jobRequest::Supervisor;
						break;
		case 'C':   req.status = jobRequest::Clerk;
						break;
	 }

	 // read the integer jobID and jobTime fields
	 istr >> req.jobID;        
	 istr >> req.jobTime;

	 return istr;
}

bool operator< (const jobRequest& a, const jobRequest& b)
{
	return a.status < b.status;
}


#endif  // JOBREQUEST

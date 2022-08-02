//NameFunctions.h

#include <string>		//string object
#include <vector>		//vector objects
using namespace std;

void FillVectors(vector<string> &names, vector<string> &origins);
string AskUserForName();
bool SearchForName(vector<string> &names, vector<string> &origins, 
				   string &userName, string &nameOrigin );

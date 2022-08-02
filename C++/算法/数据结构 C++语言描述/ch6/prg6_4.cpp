// File: prg6_4.cpp
// the class graduate stores the name of a degree candidate
// and the type of degree (BA or BS). the file "gradlist.dat"
// contains a list of degree candidates. the program reads
// the file and inserts each graduate into one of two lists
// of graduate objects, gradBS_list or gradBA_list. it uses
// insertOrder() so each list is in order by graduate name.
// the program next reads the file "noattend.dat" containing
// a list of graduates who will not attend the graduation
// ceremonies. using the function removeGraduate(), it erases
// each graduate in this file from either the list gradBS_list
// or gradBA_list, depending on the degree. using the function
// splice(), it joins the two lists together in the list
// diplomalist. the BS candidates are first, followed by the BA
// candidates. displaying this list gives the order in which
// the degree recipients will march in the graduation ceremony

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <list>

#include "d_util.h"		// for writeList()
#include "d_grad.h"		// contains the graduate class
#include "d_listl.h"		// for insertOrder() and splice()
#include "d_search.h"	// for list seqSearch()

// remove the object grad from the appropriate list
void removeGraduate(list<graduate>& gradList, const graduate& grad);

int main()
{
	// object read as an entry from the files
	graduate grad;
	
	// list holds graduates in two sections "BS" and "BA"
	list<graduate> gradBA_list, gradBS_list, diplomalist;


	// streams to input registrar's list and dean's list
	ifstream gradIn, noAttIn;

	// open registrar's list file
	gradIn.open("gradlist.dat");
	if (!gradIn)
	{
		cerr << "Cannot open file 'gradlist.dat'" << endl;
		exit(1);
	}

	// read registrar's list to end-of-file and add to list
	while(true)
	{
		gradIn >> grad;
		if (!gradIn)
			break;
		if(grad.getDegree() == "BS")
			insertOrder(gradBS_list, grad);
		else
			insertOrder(gradBA_list, grad);
	}

  	gradIn.close();

	// open file of those not attending graduation
	noAttIn.open("noattend.dat");
	if (!noAttIn)
	{
		cerr << "Cannot open file 'noattend.dat'" << endl;
		exit(1);
	}
		
	// read list of those not attending to end-of-file and
	// remove each graduate from the list
	while(true)
	{
		noAttIn >> grad;
		if (!noAttIn)
			break;
		if (grad.getDegree() == "BS")
			removeGraduate(gradBS_list,grad);
		else
			removeGraduate(gradBA_list, grad);
	}

	diplomalist = gradBS_list;
	splice<graduate>(diplomalist, diplomalist.end(), gradBA_list);
  	
	// output list of graduates at ceremony by sections. use
	// a newline separator between names
	cout << "Students at Graduation" << endl << endl;
  	writeList(diplomalist, "\n");

	return 0;
}

void removeGraduate(list<graduate>& gradList, const graduate& grad)
{
	// search for grad in the list
	list<graduate>::iterator iter =
		seqSearch<graduate> (gradList.begin(), gradList.end(), grad);

	// if found, call erase() to remove the element
	if (iter != gradList.end())
		gradList.erase(iter);
}

/*
<File "gradlist.dat">

Peterson, Bradley	BA
Frazer, Thomas	BA
Harnes, Bailey	BA
Kilmer, William	BA
Barnes, Nancy	BS
Miller, Sara	BS
Neeson, Rebecca	BS
Bailey, Julie	BS
Nelson, Harold	BS
O'Dell, Jack	BA
Johnson, Shannon	BS

<File "noattend.dat">

FFrazer, Thomas	BA
Johnson, Shannon	BS
Barnes, Nancy	BS

Run:

Students at Graduation

Bailey, Julie       BS
Miller, Sara        BS
Neeson, Rebecca     BS
Nelson, Harold      BS
Harnes, Bailey      BA
Kilmer, William     BA
O'Dell, Jack        BA
Peterson, Bradley   BA
*/

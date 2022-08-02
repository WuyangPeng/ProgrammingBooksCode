#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/**
   Reads numbers from a file and finds the maximum value
   @param in the input stream to read from
   @return the maximum value or 0 if the file has no numbers
*/            
double read_data(ifstream& in)
{  
   double highest;
   double next;
   if (in >> next)
      highest = next;
   else
      return 0;

   while (in >> next)
   {  
      if (next > highest)
         highest = next;
   }

   return highest;
}

int main()
{  
   string filename;
   cout << "Please enter the data file name: ";
   cin >> filename;

   ifstream infile;
   infile.open(filename.c_str());

   if (infile.fail()) 
   {
      cout << "Error opening " << filename << "\n";
      return 1;
   }

   double max = read_data(infile);
   cout << "The maximum value is " << max << "\n";

   infile.close();
   return 0;
}

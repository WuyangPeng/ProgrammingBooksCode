#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/**
   Reads numbers from a file and finds the maximum value
   @param in the input stream to read from
   @return the maximum value or 0 if the file has no numbers
*/            
double read_data(istream& in)
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
   double max;

   string input;
   cout << "Do you want to read from a file? (y/n) ";
   cin >> input;

   if (input == "y")
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

      max = read_data(infile);
      infile.close();
   }
   else
      max = read_data(cin);

   cout << "The maximum value is " << max << "\n";

   return 0;
}

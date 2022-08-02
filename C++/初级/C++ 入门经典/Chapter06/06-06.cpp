//DISPLAY 6.6 Formatting Output
//Illustrates output formatting instructions.
//Reads all the numbers in the file rawdata.dat and writes the numbers
//to the screen and to the file neat.dat in a neatly formatted way.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

void makeNeat(ifstream& messyFile, ofstream& neatFile,
             int numberAfterDecimalpoint, int fieldWidth);
//Precondition: The streams messyFile and neatFile have been connected
//to files using the function open.
//Postcondition: The numbers in the file connected to messyFile have been
//written to the screen and to the file connected to the stream neatFile.
//The numbers are written one per line, in fixed-point notation (that is, not in
//e-notation), with numberAfterDecimalpoint digits after the decimal point;
//each number is preceded by a plus or minus sign and each number is in a field
//of width fieldWidth. (This function does not close the file.)

int main( )
{
    ifstream fin;
    ofstream fout;

    fin.open("rawdata.dat");
    if (fin.fail( ))
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    fout.open("neat.dat");
    if (fout.fail( ))
    {
        cout << "Output file opening failed.\n";
        exit(1);
    }

    makeNeat(fin, fout, 5, 12);

    fin.close( );
    fout.close( );

    cout << "End of program.\n";
    return 0;
}
//Uses iostream, fstream, and iomanip:
void makeNeat(ifstream& messyFile, ofstream& neatFile,
              int numberAfterDecimalpoint, int fieldWidth)
{
    neatFile.setf(ios::fixed);
    neatFile.setf(ios::showpoint);
    neatFile.setf(ios::showpos);
    neatFile.precision(numberAfterDecimalpoint);
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.setf(ios::showpos);
    cout.precision(numberAfterDecimalpoint);

    double next;
    while (messyFile >> next)
    {
        cout << setw(fieldWidth) << next << endl;
        neatFile << setw(fieldWidth) << next << endl;
    }
}


//DISPLAY 6.1 Simple File Input/Output
//Reads three numbers from the file infile.dat, sums the numbers,
//and writes the sum to the file outfile.dat.
//(A better version of this program will be given in Display 6.2.)
#include <fstream>

int main( )
{
    using namespace std;
    ifstream inStream;
    ofstream outStream;

    inStream.open("infile.dat");
    outStream.open("outfile.dat");

    int first, second, third;
    inStream >> first >> second >> third;
    outStream << "The sum of the first 3\n"
               << "numbers in infile.dat\n"
               << "is " << (first + second + third)
               << endl;

    inStream.close( );
    outStream.close( );

    return 0;
}

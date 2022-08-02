//
// argc_v.cpp
// Debugging command-line arguments.
// Chris H. Pappas and William H. Murray, 2000
//

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

class sample {
  public:
    sample(int argc, char **argv);
};

sample::sample( int argc, char **argv )
{
  int iAccumulator = 0;

  if( argc == 1 ) {
    cout << "You only enetered the program name.\n"
         << "The program will now exit.";
    exit( EXIT_FAILURE );
  }

  for( int offset = 1; offset < argc; offset++)  {
    cout << *++argv << endl;      // or argv[ offset ];
    iAccumulator += atoi( *argv );// or argv[ offset ];
  };

  cout << iAccumulator << endl;
}

void main( int argc, char *argv[] )
{
  sample ARGC_V( argc, argv );
}


// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <sockinet.h>

int main ()
{
  isockinet is;

  try {
    is->bind (4020);
  }
  catch (sockerr e) {
    cerr << e.errstr () << endl;
    return 1;
  }

  return 0;
}

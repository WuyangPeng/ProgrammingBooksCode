/* /////////////////////////////////////////////////////////////////////////////
 * File:        istream_iterator_test.cpp
 *
 * Purpose:     Implementation file for the istream_iterator_test project.
 *
 * Created:     22nd January 2004
 * Updated:     22nd January 2004
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2004, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2004
 *              by Synesis Software Pty Ltd. There are no restrictions
 *              whatsoever to your use of the software. 
 *
 *              This source code is provided by Synesis Software Pty Ltd "as is"
 *              and any warranties, whether expressed or implied, including, but
 *              not limited to, the implied warranties of merchantability and
 *              fitness for a particular purpose are disclaimed. In no event
 *              shall the Synesis Software Pty Ltd be liable for any direct,
 *              indirect, incidental, special, exemplary, or consequential
 *              damages (including, but not limited to, procurement of
 *              substitute goods or services; loss of use, data, or profits; or
 *              business interruption) however caused and on any theory of
 *              liability, whether in contract, strict liability, or tort
 *              (including negligence or otherwise) arising in any way out of
 *              the use of this software, even if advised of the possibility of
 *              such damage. 
 *
 *              Neither the name of Synesis Software Pty Ltd nor the names of
 *              any subdivisions, employees or agents of Synesis Software Pty
 *              Ltd, nor the names of any other contributors to this software
 *              may be used to endorse or promote products derived from this
 *              software without specific prior written permission. 
 *
 * ////////////////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <vector>

#include <stlsoft.h>

#include <vector>

/* ////////////////////////////////////////////////////////////////////////// */

void print_int(int const &i)
{
    printf("%d ", i);
}

/* ////////////////////////////////////////////////////////////////////////// */

extern "C" void __stdcall Sleep(unsigned );

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("istream_iterator_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    int             i;
    int             iarray[] = { 1,3,5,7,11,13,17,19 };
    std::fstream    my_file("vector.dat",std::ios::out);// Add |ios::nocreate to avoid 
                                                   // creation if it doesn't exist
    std::vector<int>    v1
        ,               v2;

    for (i = 0;i<sizeof(iarray)/sizeof(iarray[0]); ++i) v1.push_back(iarray[i]);

//  Write v1 to file
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int,char>(my_file," "));
    std::cout << "Wrote vector v1 to file vector.dat" << std::endl;

//  Close file
    my_file.close();

    {
        std::fstream    my_file( "vector.dat", std::ios::in|std::ios::out);

        std::copy(  std::istream_iterator<int>(my_file)
                ,   std::istream_iterator<int>()
                ,   std::back_inserter(v2));

        std::for_each(v2.begin(), v2.end(), print_int);
        printf("\n");
    }

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

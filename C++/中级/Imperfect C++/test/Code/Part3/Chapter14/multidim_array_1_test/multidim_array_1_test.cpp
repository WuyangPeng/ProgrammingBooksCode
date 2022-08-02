/* /////////////////////////////////////////////////////////////////////////////
 * File:        multidim_array_1_test.cpp
 *
 * Purpose:     Implementation file for the multidim_array_1_test project.
 *
 * Created:     19th October 2003
 * Updated:     1st February 2004
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2003, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2003
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

#include <stlsoft.h>

/* ////////////////////////////////////////////////////////////////////////// */

void process3dArray(int ar[][10][20])
{
}

void process3dArray(int (*ar)[10])
{
}

void process3dArray(int *ar[10])
{
}

#if 0
void process3dArray(int **ar)
{
}
#endif /* 0 */

void process3dArray(int (*(*ar))[])
{
}

void process3dArray(int (*(*ar))[20])
{
}

void process3dArray(int *(*ar)[20])
{
}

#if 0
void process3dArray(int ar[][][])
{
}
#endif /* 0 */

void process3dArray(int (*(*(*ar))))
{
}

#if 0
void process3dArray(int ***ar)
{
}
#endif /* 0 */

//int (*(*ar))

/* ////////////////////////////////////////////////////////////////////////// */

#ifndef dimensionof
# define dimensionof    stlsoft_num_elements
#endif /* !dimensionof */

/* ////////////////////////////////////////////////////////////////////////// */

void display_offset()
{
    char    a3[2][3][4];

    for(size_t i = 0; i < dimensionof(a3); ++i)
    {
        for(size_t j = 0; j < dimensionof(a3[0]); ++j)
        {
            for(size_t k = 0; k < dimensionof(a3[0][0]); ++k)
            {
                printf("a3[%u][%u][%u] : a3 + %u\n", i, j, k, &a3[i][j][k] - &a3[0][0][0]);
            }
        }
    }
}

/* ////////////////////////////////////////////////////////////////////////// */

void print_array(short ar[], size_t dim0)
{
    printf("[Array:     ");
    for(size_t i = 0; i < dim0; ++i)
    {
        printf("%2d ", ar[i]);
    }
    printf("]\n");
}

void print_array_ptr(short (*par)[], size_t dim0)
{
    printf("[Array-ptr: ");
    for(size_t i = 0; i < dim0; ++i)
    {
        printf("%2d ", (*par)[i]);
    }
    printf("]\n");
}

void print_array_ptr(short ***par, size_t dim0, size_t dim1)
{
    printf("[Array-ptr: ");
    for(size_t i = 0; i < dim0; ++i)
    {
        for(size_t j = 0; j < dim1; ++j)
        {
            printf("%2d ", (*par[i])[j]);
        }
    }
    printf("]\n");
}

/* ////////////////////////////////////////////////////////////////////////// */

class Array1d
{
public:
    Array1d(size_t dim0)
        : m_values(new short[dim0])
        , m_dim0(dim0)
    {
        for(size_t i = 0; i < dim0; ++i)
        {
            m_values[i] = i;
        }
        printf("Array1d(): ");
        print_array(m_values, dim0);
    }
    Array1d(short *values, size_t dim0)
        : m_values(values)
        , m_dim0(dim0)
    {}

public:
    typedef short (*dim_ptr)[];

    dim_ptr operator &()
    {
        return (dim_ptr)m_values;
    }

    short &operator [](size_t index)
    {
        return m_values[index];
    }

    size_t dim0() const
    {
        return m_dim0;
    }

private:
    short   *m_values;
    size_t  m_dim0;
};

class Array2d
{
public:
    Array2d(size_t dim0, size_t dim1)
        : m_values(new short[dim0 * dim1])
        , m_dim0(dim0)
        , m_dim1(dim1)
    {
        for(size_t i = 0; i < dim0 * dim1; ++i)
        {
            m_values[i] = i;
        }
        printf("Array2d(): ");
        print_array(m_values, dim0 * dim1);
    }

    Array2d(short *values, size_t dim0, size_t dim1)
        : m_values(values)
        , m_dim0(dim0)
        , m_dim1(dim1)
    {}

public:
//  Array1d operator
    typedef short (***dim_ptr);

    dim_ptr operator &()
    {
        return (dim_ptr)&m_values;
    }

    Array1d operator [](size_t index)
    {
        return Array1d(&m_values[index * m_dim1], m_dim1);
    }

    size_t dim0() const
    {
        return m_dim0;
    }

    size_t dim1() const
    {
        return m_dim1;
    }

private:
    short   *m_values;
    size_t  m_dim0;
    size_t  m_dim1;
};

class Array3d
{
public:
    Array3d(size_t dim0, size_t dim1, size_t dim2)
        : m_values(new short[dim0 * dim1 * dim2])
        , m_dim0(dim0)
        , m_dim1(dim1)
        , m_dim2(dim2)
    {
        for(size_t i = 0; i < dim0 * dim1 * dim2; ++i)
        {
            m_values[i] = i;
        }
        printf("Array3d(): ");
        print_array(m_values, dim0 * dim1 * dim2);
    }

public:
//  Array1d operator
    typedef short (***dim_ptr)[];

    dim_ptr operator &()
    {
        return (dim_ptr)m_values;
    }

    Array2d operator [](size_t index)
    {
        return Array2d(&m_values[index * m_dim1 * m_dim2], m_dim1, m_dim2);
    }

    size_t dim0() const
    {
        return m_dim0;
    }

    size_t dim1() const
    {
        return m_dim1;
    }

    size_t dim2() const
    {
        return m_dim2;
    }

private:
    short   *m_values;
    size_t  m_dim0;
    size_t  m_dim1;
    size_t  m_dim2;
};


/* ////////////////////////////////////////////////////////////////////////// */

void process3dArray(int *ar, size_t X, size_t Y, size_t Z)
{
    typedef array_slice_3d<int> slice(ar, X, Y, Z);

}


extern "C" void __stdcall Sleep(unsigned long );

int main(int /* argc */, char ** /*argv*/)
{
    puts("multidim_array_1_test: " __STLSOFT_COMPILER_LABEL_STRING);

//  ::Sleep(100000);

    {
        int a3[2][3][4] = 
        {
                1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
            ,   101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112
        };

        process3dArray(&a3[0][0][0], 2, 3, 4);
    }


    display_offset();

    /* . */
    int a1[10];
    int a2[10][10];
    int a3[10][10][10];

    int *p1             =   &a1[0];
    int (*p2)[10]       =   &a2[0];
    int (*p3)[10][10]   =   &a3[0];

    Array1d a1d(4);
    Array2d a2d(3, 4);
    Array3d a3d(2, 3, 4);

    print_array(&a1d[0], a1d.dim0());
    print_array(&a2d[0][0], a2d.dim1());
    print_array(&a2d[1][0], a2d.dim1());
    print_array(&a2d[2][0], a2d.dim1());
    print_array(&a3d[0][0][0], a3d.dim2());
    print_array(&a3d[0][1][0], a3d.dim2());
    print_array(&a3d[0][2][0], a3d.dim2());
    print_array(&a3d[1][0][0], a3d.dim2());
    print_array(&a3d[1][1][0], a3d.dim2());
    print_array(&a3d[1][2][0], a3d.dim2());

    print_array_ptr(&a1d, a1d.dim0());

    print_array_ptr(&a2d[0], a2d.dim1());
    print_array_ptr(&a2d[1], a2d.dim1());
    print_array_ptr(&a2d[2], a2d.dim1());

    print_array_ptr(&a3d[0][0], a3d.dim2());
    print_array_ptr(&a3d[0][1], a3d.dim2());
    print_array_ptr(&a3d[0][2], a3d.dim2());
    print_array_ptr(&a3d[1][0], a3d.dim2());
    print_array_ptr(&a3d[1][1], a3d.dim2());
    print_array_ptr(&a3d[1][2], a3d.dim2());

    print_array_ptr(&a2d, a2d.dim0(), a2d.dim1());

//  print_array_ptr(&a2d[0], a2d.dim1());
/// print_array_ptr(&a2d[1], a2d.dim1());
//  print_array_ptr(&a2d[2], a2d.dim1());


    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

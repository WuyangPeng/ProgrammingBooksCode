/* /////////////////////////////////////////////////////////////////////////////
 * File:        rt_allocator_adapter_test.cpp
 *
 * Purpose:     Implementation file for the rt_allocator_adapter_test project.
 *
 * Created:     3rd January 2004
 * Updated:     3rd January 2004
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

#include <windows.h>
#include <stdio.h>

#include <stlsoft.h>

#if defined(unix) || \
    defined(__unix__)

#include <unixstl.h>

#elif defined(WIN32) || \
    defined(_WIN32)

#include <winstl.h>

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */

#include <MIAtor.h>

__SYNSOFT_GEN_USING(::SynesisStd::IAllocator)

#include <MRAtors.h>

__SYNSOFT_GEN_USING(::SynesisCrt::CrtAtor)

#include <vector>

/* ////////////////////////////////////////////////////////////////////////// */

template <typename T, IAllocator *A>
struct rt_allocator_adaptor
{
public:
    typedef T                   value_type;
    typedef value_type          *pointer;
    typedef value_type          &reference;
    typedef value_type const    *const_pointer;
    typedef value_type const    &const_reference;

    typedef size_t              size_type;
    typedef ptrdiff_t           difference_type;

    static pointer allocate(size_type n, void const *hint)
    {
        STLSOFT_SUPPRESS_UNUSED(hint);

        return static_cast<pointer>(A->Alloc(sizeof(value_type) * n));
    }

    static void deallocate(pointer p, size_type)
    {
        A->Free(p);
    }

    /// Deallocates a pointer
    ///
    /// \param p The memory block to deallocate
    static void deallocate(pointer p)
    {
        A->Free(p);
    }

    void construct(pointer p)
    {
        stlsoft_assert(p != NULL);

        new(p) value_type();
    }

    /// In-place destroys an instance
    ///
    /// \param p The instance whose destructor is to be called
    void destroy(pointer p) stlsoft_throw_0()
    {
        stlsoft_assert(p != NULL);

        stlsoft_destroy_instance(T, value_type, p);
    }

};

/* ////////////////////////////////////////////////////////////////////////// */

int AcmeLib_Init(IAllocator *ator);
void AcmeLib_Uninit();

void *AcmeLib_GiveMeBlock(size_t cb);
void AcmeLib_DoOtherStuff(int i);

/* ////////////////////////////////////////////////////////////////////////// */

IAllocator  *s_allocator;

int AcmeLib_Init(IAllocator *ator)
{
    s_allocator = ator;

    return 0;
}

void AcmeLib_Uninit()
{}

void AcmeLib_DoOtherStuff(int i)
{
    typedef std::vector<int, rt_allocator_adaptor<int, s_allocator> >       vector_t;

    vector_t    v(i);
}


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("rt_allocator_adapter_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    CrtAtor ator;

    AcmeLib_Init(&ator);

    AcmeLib_DoOtherStuff(100);

    AcmeLib_Uninit();

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

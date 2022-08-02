/* /////////////////////////////////////////////////////////////////////////////
 * File:        CArray_adaptors_test.cpp
 *
 * Purpose:     Implementation file for the CArray_adaptors_test project.
 *
 * Created:     4th August 2005
 * Updated:     1st May 2007
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2005-2007, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              This source code is placed into the public domain 2005
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

/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/integer_to_string.hpp>
#include <stlsoft/simple_string.hpp>
#include <stlsoft/iterators/contiguous_diluter_iterator.hpp>

#include <mfcstl/mfcstl.hpp>
#include <mfcstl/carray_adaptors.hpp>
//#include <mfcstl/string_access.hpp>

#include <afxwin.h>
#include <afxtempl.h>

/* Standard C Header Files */
#include <stdio.h>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <stack>
#include <string>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#ifdef __WATCOMC__
namespace std
{
	using ::exception;
}
#endif /* __WATCOMC__ */

/* ////////////////////////////////////////////////////////////////////////// */

void fill_MFC_CStringArray(CStringArray &ar)
{
	ar.Add("String 5");
	ar.Add("String 2");
	ar.Add("String 3");
	ar.Add("String 4");
	ar.Add("String 1");
}

void print_CString_to_cout(CString const &str)
{
	cout << "String: " << (void*)(char const *)str << ": " << (char const *)str << endl;
}

template <typename C>
void test_adaptor(C &c)
{
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;
	cout << "items (reverse):" << endl; std::for_each(c.rbegin(), c.rend(), print_CString_to_cout);	cout << endl;

	std::sort(c.begin(), c.end());
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;

#if 1
	std::sort(c.rbegin(), c.rend());
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;
#endif /* 0 */

	if(c == c)
	{}

	if(c != c)
	{}

	c.push_back("String 8");
	c.push_back("String 7");
	c.push_back("String 6");
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;

	c.erase(c.begin());
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;

	try
	{
		c.resize(1000000000);
	}
	catch(...)
	{}
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;

#if 0
	c[0] = "String 9";
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;
#endif /* 0 */

	c.erase(c.begin(), c.begin() + 1);
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;

	c.clear();
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;

	c.insert(c.end(), "String 10");
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;

	c.pop_back();
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;

	c.insert(c.end(), 1, "String 11");
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;

	c.insert(c.end(), c.begin(), c.end());
	cout << "items:" << endl; std::for_each(c.begin(), c.end(), print_CString_to_cout);	cout << endl;

	C	c2(c);
	cout << "items (2):" << endl; std::for_each(c2.begin(), c2.end(), print_CString_to_cout); cout << endl;

#if 0
	CArray_cadaptor<CStringArray>  ar3;
	ar3	=	c;

	cout << "copy:" << endl; std::for_each(ar3.begin(), ar3.end(), print_CString_to_cout); cout << endl;
#endif /* 0 */
}

class CStringArrayBigger
  : public CStringArray
{
private:
  int i;
};

static int main_(int /* argc */, char ** /*argv*/)
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	puts("CArray_adaptor test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

#if 0
    {
        mfcstl::CArray_cadaptor<CStringArraySameSize
                            ,   mfcstl::CArray_traits<CStringArray>
                            >   ar;
    }

    {
        mfcstl::CArray_cadaptor<CStringArrayBigger
                            ,   mfcstl::CArray_traits<CStringArray>
                            >   ar;
    }
#endif /* 0 */

#if 0
	{
        typedef mfcstl::CArray_cadaptor<CStringArrayX
									,	mfcstl::CArray_traits<CStringArray>
									>	array_t;

		array_t	ar;
	}
#endif /* 0 */

	if(0)
	{
        typedef std::stack< CString
                        ,   mfcstl::CArray_cadaptor<CStringArray>
                        >       stack_t;

        stack_t stk;

        stk.push("String 1");
        stk.push("String 2");
        stk.push("String 3");
        stk.push("String 4");
        stk.push("String 5");

        for(; !stk.empty(); stk.pop())
        {
            cout << stk.top() << endl;
        }

	}

	{
		using mfcstl::CArray_cadaptor;

		{
			CArray_cadaptor<CStringArray>	strings;

			cout << "Arch=" << 0 << ";" << endl;

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CArray_cadaptor<CStringArray>	strings(12);

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CArray_cadaptor<CStringArray>	strings(1);

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;

#if 0
			strings.erase(strings.begin());
#else /* ? 0 */
			strings.clear();
#endif /* 0 */

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CArray_cadaptor<CStringArray>	strings(12, "string");

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CArray_cadaptor<CStringArray>	strings(1, "string");

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CArray_cadaptor<CStringArray>	strings;

			strings.assign(1, "string");

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CArray_cadaptor<CStringArray>	strings;

			strings.push_back("string");

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CArray_cadaptor<CStringArray>	strings;

			strings.insert(strings.end(), "string");

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CArray_cadaptor<CStringArray>	strings;

			strings.insert(strings.end(), "string");
			strings.insert(strings.end(), "string");

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CString		ar[4];

			CArray_cadaptor<CStringArray>	strings(&ar[0], &ar[0] + STLSOFT_NUM_ELEMENTS(ar));

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CArray_cadaptor<CStringArray>	strings;

			strings.insert(strings.end(), 2, "string");

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CString		ar[97];

			CArray_cadaptor<CStringArray>	strings(&ar[0], &ar[0] + STLSOFT_NUM_ELEMENTS(ar));

			strings.insert(strings.end(), "string");
			strings.insert(strings.end(), "string");

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CString		ar[97];

			CArray_cadaptor<CStringArray>	strings(&ar[0], &ar[0] + STLSOFT_NUM_ELEMENTS(ar));

			strings.insert(strings.end(), "string");
			strings.insert(strings.end(), "string");

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;

			strings.insert(strings.end(), &ar[0], &ar[0] + STLSOFT_NUM_ELEMENTS(ar));

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;

			strings.insert(strings.end(), &ar[0], &ar[0] + STLSOFT_NUM_ELEMENTS(ar));

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CString		ar[4];

			CArray_cadaptor<CStringArray>	strings(stlsoft::contiguous_diluter_iterator<const CString>(&ar[0])
												,	stlsoft::contiguous_diluter_iterator<const CString>(&ar[0] + STLSOFT_NUM_ELEMENTS(ar)));

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CString		ar[4];

			CArray_cadaptor<CStringArray>	strings;
			
			strings.assign(	stlsoft::contiguous_diluter_iterator<const CString>(&ar[0])
						,	stlsoft::contiguous_diluter_iterator<const CString>(&ar[0] + STLSOFT_NUM_ELEMENTS(ar)));

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

		{
			CString		ar[4];

			CArray_cadaptor<CStringArray>	strings;
			
			strings.insert(	strings.begin()
						,	stlsoft::contiguous_diluter_iterator<const CString>(&ar[0])
						,	stlsoft::contiguous_diluter_iterator<const CString>(&ar[0] + STLSOFT_NUM_ELEMENTS(ar)));

			cout << "size=" << strings.size() << "; growIncrement=" << strings.grow_increment() << "; capacity=" << strings.capacity() << "; growIncrement=" << strings.grow_increment() << endl;
		}

	}


	{
		using mfcstl::CArray_cadaptor;

		CArray_cadaptor<CStringArray>	strings(1000, "String ");

		{ for(size_t i = 0; i < strings.size(); ++i)
		{
			char	sz[21];

			strings[i] += stlsoft::integer_to_string(sz, STLSOFT_NUM_ELEMENTS(sz), i);
		}}

		std::sort(strings.begin(), strings.end());
		std::sort(strings.rbegin(), strings.rend());

		CArray_cadaptor<CStringArray>	strings2(strings);

		MFCSTL_ASSERT(strings2 == strings);

		CArray_cadaptor<CStringArray>	strings3(strings.get_CArray());

		MFCSTL_ASSERT(strings3 == strings);

		CArray_cadaptor<CStringArray>	strings4(1000);

		CString		strar[4];

		CArray_cadaptor<CStringArray>	strings5(&strar[0], &strar[0] + STLSOFT_NUM_ELEMENTS(strar));
	}

	{
		using mfcstl::CArray_cadaptor;
		using mfcstl::CArray_iadaptor;

		CArray_cadaptor<CDWordArray>	cdwa(std::istream_iterator<char>(std::cin), std::istream_iterator<char>());

		std::copy(cdwa.begin(), cdwa.end(), std::ostream_iterator<char>(std::cout));
		cout << endl << endl;

		static const DWORD	dwords[] = 
		{
				0
			,	1
			,	2
			,	3
			,	4
		};

		CArray_cadaptor<CDWordArray>	cdwa2(&dwords[0], &dwords[0] + STLSOFT_NUM_ELEMENTS(dwords));

		std::copy(cdwa2.begin(), cdwa2.end(), std::ostream_iterator<DWORD>(std::cout));
		cout << endl << endl;

		CArray_cadaptor<CDWordArray>	cdwa3(cdwa2.get_CArray());

		std::copy(cdwa3.begin(), cdwa3.end(), std::ostream_iterator<DWORD>(std::cout));
		cout << endl << endl;
	}

	// Test equality
	{
		using mfcstl::CArray_cadaptor;
		using mfcstl::CArray_iadaptor;
#ifndef STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT
		using mfcstl::CArray_specific_traits;
#endif /* !STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */

		CStringArray										sa;

		CArray_cadaptor<CStringArray>						ca;
		CArray_iadaptor<CStringArray>						ia(sa);

		STLSOFT_STATIC_ASSERT(sizeof(ia) == sizeof(void*));

#ifdef STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT
		CArray_cadaptor<CArray<CString, CString const &> >	ca2;
#else /* ? STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */
		CArray_cadaptor<	CArray<	CString
								,	CString const &
								>
						,	CArray_specific_traits<	CString
												,	CString const &
												,	CStringArray
												>
						>									ca2;
#endif /* STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */

		std::vector<CString>								sv;

		if(ca == ca)	{}
		if(ca != ca)	{}

		if(ca == ia)	{}
		if(ca != ia)	{}
		if(ia == ca)	{}
		if(ia != ca)	{}

		if(ca2 == ca)	{}
		if(ca2 != ca)	{}

		if(ca == sa)	{}
		if(ca != sa)	{}
		if(sa == ca)	{}
		if(sa != ca)	{}

#if 0
		if(ca == sv)
		{}
#endif /* 0 */

		ca.push_back("String 1");
		ca.push_back("String 2");
		ca.push_back("String 3");

		ia.insert(ia.end(), ca.begin(), ca.end());
	}

	{
		using mfcstl::CArray_cadaptor;
		using mfcstl::CArray_iadaptor;
#ifndef STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT
		using mfcstl::CArray_specific_traits;
#endif /* !STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */

		CArray<float, float>						da;
#ifdef STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT
		CArray_iadaptor<CArray<float, float> >		ida(da);
#else /* ? STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */
		CArray_iadaptor<	CArray<	float
								,	float
								>
						,	CArray_specific_traits<float, float, CArray<	float
								,	float
								> >
						>							ida(da);
#endif /* STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */
		CArray_cadaptor<CDWordArray>				cdwa;

		ida == cdwa;
	}

	{
		using mfcstl::CArray_cadaptor;
		using mfcstl::CArray_iadaptor;

		CArray_cadaptor<CUIntArray>		cuia;
		CArray_cadaptor<CDWordArray>	cdwa;

		cuia == cdwa;
	}


	{
		std::string	s;

		std::sort(s.begin(), s.end());
		std::sort(s.rbegin(), s.rend());
	}

	{
		stlsoft::simple_string	s;

		std::sort(s.begin(), s.end());

		stlsoft::simple_string::reverse_iterator	rb_(s.end()), re_(s.begin());

		std::reverse_iterator<	stlsoft::simple_string::iterator
							,	stlsoft::simple_string::value_type
							,	stlsoft::simple_string::reference
							,	stlsoft::simple_string::pointer
							,	stlsoft::simple_string::difference_type
							>		rb(s.end()), re(s.begin());

#if 0
		std::sort(rb_, re_);
		std::sort(rb, re);
#else /* ? 0 */
#endif /* 0 */

		rb = rb_;	// ok
//		rb_ = rb;	// FAILS

		for(; rb_ != re_; ++rb_)
		{}

		for(; rb != re; ++rb)
		{}

//		std::reverse_iterator
	}

#if 0
	{
		std::vector<CString>	vs;

		std::sort(vs.begin(), vs.end());
		std::sort(vs.rbegin(), vs.rend());
	}
#endif /* 0 */

#if 0
	{
		CObArray		ar;
		CObArray const	&car	=	ar;

		ar.Add(new CException());

		CObject	const	**pp	=	car.GetData();

		*pp = NULL;
	}
#endif /* 0 */

#if 0
	{
		CArchive	ar_(NULL, 0);

		CArchive		&a = ar_;
		CObArray		ar;
		CObArray const	&car	=	ar;


		ar.GetData()[0]->IsSerializable();

		car.GetData()[0]->Serialize(a);

	}
#endif /* 0 */

	{
		mfcstl::CArray_cadaptor<CStringArray>								ar;
		mfcstl::CArray_cadaptor<CStringArray>::allocator_type::pointer	p	=	ar.get_allocator().allocate(10);

		ar.get_allocator().deallocate(p);
	}

	{ // 
		using mfcstl::CArray_cadaptor;

		CArray_cadaptor<CStringArray>  arf;

		cout << "Testing CArray_cadaptor" << endl
			 << "=====================" << endl << endl;

		fill_MFC_CStringArray(arf);

		test_adaptor(arf);

		const LPCTSTR	strings[] = 
		{
				"C-style string #1"
			,	"C-style string #2"
			,	"C-style string #3"
		};

		CArray_cadaptor<CStringArray>	c3(&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings));
		cout << "items (2):" << endl; std::for_each(c3.begin(), c3.end(), print_CString_to_cout);	cout << endl;

		std::list<LPCTSTR>			ls(&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings));
		CArray_cadaptor<CStringArray>	c4(ls.begin(), ls.end());
		cout << "items (2):" << endl; std::for_each(c3.begin(), c3.end(), print_CString_to_cout);	cout << endl;
		std::list<LPCTSTR> const	&cls	=	ls;
		CArray_cadaptor<CStringArray>	c5(cls.begin(), cls.end());
		cout << "items (2):" << endl; std::for_each(c3.begin(), c3.end(), print_CString_to_cout);	cout << endl;

		CArray_cadaptor<CStringArray>  arf2;

		fill_MFC_CStringArray(arf2);

		size_t	size1	=	arf.size();
		size_t	size2	=	arf2.size();

		cout << "items (1):" << endl; std::for_each(arf.begin(), arf.end(), print_CString_to_cout);	cout << endl;
		cout << "items (2):" << endl; std::for_each(arf2.begin(), arf2.end(), print_CString_to_cout);	cout << endl;

#ifdef MFCSTL_CARRAY_SWAP_MEMBERS_SUPPORT
		stlsoft::std_swap(arf, arf2);
#else /* ? MFCSTL_CARRAY_SWAP_MEMBERS_SUPPORT */
#endif /* MFCSTL_CARRAY_SWAP_MEMBERS_SUPPORT */

		size1	=	arf.size();
		size2	=	arf2.size();

		cout << "items (1):" << endl; std::for_each(arf.begin(), arf.end(), print_CString_to_cout);	cout << endl;
		cout << "items (2):" << endl; std::for_each(arf2.begin(), arf2.end(), print_CString_to_cout);	cout << endl;
	}

	{ // 
		using mfcstl::CArray_iadaptor;

		CStringArray				ar;
		CArray_iadaptor<CStringArray>  arp(ar);

		CStringArray				ar2;
		CArray_iadaptor<CStringArray>  ar2p(ar2);

		cout << "Testing CArray_iadaptor" << endl
			 << "====================" << endl << endl;

		fill_MFC_CStringArray(ar);
	}

    return 0;
}

int main(int argc, char *argv[])
{
#if 0
	::Sleep(100000);
#endif /* 0 */

	try
	{
		if(!AfxWinInit(::GetModuleHandle(NULL), 0, GetCommandLine(), 0))
		{
			cerr << "MFC failed to initialise" << endl;
		}

		return main_(argc, argv);
	}
	catch(std::exception &x)
	{
		cerr << "Unhandled error: " << x.what() << endl;
	}
	catch(CException *px)
	{
		char	sz[1001];

		px->GetErrorMessage(&sz[0], STLSOFT_NUM_ELEMENTS(sz));

		cerr << "Unhandled error: " << sz << endl;
	}
	catch(...)
	{
		cerr << "Unhandled unknown error" << endl;
	}

	return EXIT_FAILURE;
}

/* ////////////////////////////////////////////////////////////////////////// */

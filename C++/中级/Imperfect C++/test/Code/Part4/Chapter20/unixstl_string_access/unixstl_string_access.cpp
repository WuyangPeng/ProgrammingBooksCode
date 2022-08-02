/* /////////////////////////////////////////////////////////////////////////////
 * File:        unixstl_string_access.cpp
 *
 * Purpose:     unixstl_string_access main implementation file.
 *
 * Created:     13th January 2003
 * Updated:     23rd December 2003
 *
 * Copyright:   Synesis Software Pty Ltd, (c) 1999-2003. All rights reserved.
 *
 * Home:        www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////////// */

#define _STLSOFT_FORCE_ANY_COMPILER

#define USE_FFS

#include <stlsoft.h>
#include <unixstl.h>

#ifdef USE_FFS
# include <unixstl_glob_sequence.h>

typedef unixstl_ns_qual(glob_sequence)      sequence_t;
#else
# include <unixstl_readdir_sequence.h>

typedef unixstl_ns_qual(readdir_sequence)   sequence_t;
#endif /* !USE_FFS */

#include <stlsoft_conversion_veneer.h>

#include <stlsoft_string_access.h>

stlsoft_ns_using(c_str_ptr)

#include <unixstl_string_access.h>

unixstl_ns_using(c_str_ptr)

#include <stdio.h>

#include <algorithm>
#include <functional>

#include <string>
#include <vector>

typedef std::vector<std::string>            vector_string_t;

#include <windows.h>

/* ////////////////////////////////////////////////////////////////////////// */

bool _is_dir(char const *s)
{
    DWORD   dw = ::GetFileAttributes(s);

    fprintf(stdout, " %s\n", s);

    return dw != 0xFFFFFFFF && (dw & FILE_ATTRIBUTE_DIRECTORY);
}

#if 0
#ifdef USE_FFS
struct is_dir
    : std::unary_function<char const *, bool>
{
    bool operator ()(char const *e) const
    {
        return _is_dir(e);
    }
};
#else
struct is_dir
    : std::unary_function<struct dirent const *, bool>
{
    bool operator ()(struct dirent const *d) const
    {
        return _is_dir(d->d_name);
    }
};
#endif /* USE_FFS */
#else
template <typename A>
struct is_dir
    : std::unary_function<A, bool>
{
    bool operator ()(A a) const
    {
        return _is_dir(c_str_ptr(a));
    }
};
#endif /* 0 */

template<   typename CH
        ,   typename C
        >
size_t record_if_dir(CH const *entry, C &c)
{
  return _is_dir(entry) ? (c.push_back(entry), 1) : 0;
}

template<   typename SS
        ,   typename S
        ,   typename C
        >
size_t sub_dir_count(S const &rootDir, SS const &s, C &c)
{
    typedef ss_typename_type_k SS::const_iterator   const_it_t;

    const_it_t  begin   =   s.begin();
    const_it_t  end     =   s.end();
    size_t      cDirs   =   0;

    for(; begin != end; ++begin)
    {
#if 1
        cDirs += record_if_dir(c_str_ptr(*begin), c);
#else
        if(_is_dir(c_str_ptr(*begin)))
        {
            c.push_back(c_str_ptr(*begin));

            cDirs += 1;
        }
#endif /* 0 */
    }

    return cDirs;
}

void print_string(std::string const &s)
{
    fprintf(stdout, " dir: %s\n", s.c_str());
}

int main(int /* argc */, char ** /*argv*/)
{
    puts("unixstl_string_access: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
#ifdef USE_FFS
    std::string rootDir =   "\\Publishing\\*.*";
#else
    std::string rootDir =   ".";
#endif /* USE_FFS */
    sequence_t  entries(c_str_ptr(rootDir));
    size_t      cDirs   =   std::count_if(entries.begin(), entries.end(), is_dir<sequence_t::value_type>());    

    printf("Number of dirs = %d\n", cDirs);

    vector_string_t directories;
    size_t const    cDirsR  =   sub_dir_count(rootDir, entries, directories);

    printf("Number of sub-dirs = %u\n", cDirs);
    std::for_each(directories.begin(), directories.end(), print_string);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef STLSOFT_COMPILER_IS_GCC

    #include <unixstl/filesystem/readdir_sequence.hpp>

#endif  // STLSOFT_COMPILER_IS_GCC

#include <iostream>

void Rds()
{
#ifdef STLSOFT_COMPILER_IS_GCC

    typedef unixstl::readdir_sequence rds_t;
    rds_t files(".", rds_t::files);

    for (rds_t::const_iterator b = files.begin(); b != files.end(); ++b)
    {
        std::cout << *b << std::endl;
    }

    for (rds_t::const_iterator b = files.begin(), e = files.end(); b != e; ++b)
    {
        std::cout << *b << std::endl;
    }

    std::copy(files.begin(), files.end(), std::ostream_iterator<rds_t::value_type>(std::cout, "\n"));

#endif  // STLSOFT_COMPILER_IS_GCC
}
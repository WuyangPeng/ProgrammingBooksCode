/* /////////////////////////////////////////////////////////////////////////////
 * File:        VoterReg.cpp
 *
 * Purpose:     VoterReg main implementation file.
 *
 * Created:     20th January 2003
 * Updated:     20th January 2003
 *
 * Copyright:   Synesis Software Pty Ltd, (c) 1999-2003. All rights reserved.
 *
 * Home:        www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////////// */


#include <stlsoft.h>
#include <stlsoft_true_typedef.h>

#include <string>

/* ////////////////////////////////////////////////////////////////////////// */

#if 0

typedef std::string  forename_t;
typedef std::string  surname_t;

class VoterRegistry
{
//  . . .

// Operations
public:
  void add(forename_t const &fn, surname_t const &sn);
  void remove(surname_t const &fn, forename_t const &sn);
  bool contains(surname_t const &fn, forename_t const &sn) const;

//  ...
};

void fn()
{
    VoterRegistry  nameReg;
    forename_t    forename;
    surname_t     surname;

//  ... // read in forename and surname from storage or from user

    nameReg.add(forename, surname);
}

#elif 0

template <typename C>
class VoterRegistry
{
public:
  typedef std::basic_string<C>  forename_type;
  typedef std::basic_string<C>  surname_type;
  typedef size_t                size_type;

//  . . .

// Operations
public:
  void add(forename_type const &fn, surname_type const &sn);
  void remove(surname_type const &fn, forename_type const &sn);
  bool contains(surname_type const &fn, forename_type const &sn) const;

//  ...
};

void fn()
{
    VoterRegistry<char>                  nameReg;
    VoterRegistry<char>::forename_type   forename;
    VoterRegistry<char>::surname_type    surname;

//  ... // read in forename and surname from storage or from user

    nameReg.add(forename, surname);
}

#elif 1

stlsoft_gen_opaque(forename_u)
stlsoft_gen_opaque(surname_u)

template <typename C>
class VoterRegistry
{
private:
  typedef std::basic_string<C>                  string_type;

typedef struct __forename_u__stlsoft_htype{ int i;} const *forename_u;
typedef struct __surname_u__stlsoft_htype{ int i;} const *surname_u;

public:
  typedef stlsoft::true_typedef< string_type
                               , forename_u>    forename_type;
  typedef stlsoft::true_typedef< string_type
                               , surname_u >    surname_type;
  typedef size_t                                size_type;

// Operations
public:
  void add(surname_type const &fn, forename_type const &sn);
  void remove(surname_type const &fn, forename_type const &sn);
  bool contains(surname_type const &fn, forename_type const &sn) const;

    bool find(surname_type const &surname) const;
    bool find(forename_type const &forename) const;

};

void fn()
{
    VoterRegistry<char>                  nameReg;
    VoterRegistry<char>::forename_type   forename;
    VoterRegistry<char>::surname_type    surname;

//  ... // read in forename and surname from storage or from user

//  nameReg.add(forename, surname);
}

#elif 1
#elif 1
#endif /* 0 */


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    /* . */
    using namespace stlsoft;

    true_typedef<int, int>  i1 = 1000;
    int                     i2 = 1001;
    true_typedef<int, int>  i3 = i2;

    i1 <<= 2;
    i1 = ~i3;
    i3 = i2 + i3;


    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

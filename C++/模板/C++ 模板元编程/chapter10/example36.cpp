/*

    Copyright David Abrahams 2003-2004
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
            
    This file was automatically extracted from the source of 
    "C++ Template Metaprogramming", by David Abrahams and 
    Aleksey Gurtovoy.

    It was built successfully with GCC 3.4.2 on Windows using
    the following command: 

        g++ -I..\..\boost_1_32_0  -o%TEMP%\metaprogram-chapter10-example36.exe example36.cpp
        

*/


#include <boost/spirit/core.hpp>
#include <boost/spirit/attribute.hpp>
#include <boost/spirit/phoenix.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost::spirit;
using namespace phoenix;

// Make use of LL style _1, _2 and _3
phoenix::actor<phoenix::argument<0> > const _1 = phoenix::argument<0>();
phoenix::actor<phoenix::argument<1> > const _2 = phoenix::argument<1>();
phoenix::actor<phoenix::argument<2> > const _3 = phoenix::argument<2>();

struct vars : boost::spirit::closure<vars, double>
{
    member1 val;
};

struct calculator : public grammar<calculator, vars::context_t>
{
    template <class Tokenizer>
    struct definition
    {
        // All our rules have an attached int called "val", too...
        rule<Tokenizer, vars::context_t>
          expression, term, factor, group, integer;

        // ...except the top rule
        rule<Tokenizer> top;

        definition(calculator const& self)
        {
            top = expression[self.val = _1];
   

group       = '(' >> expression >> ')';
factor      = integer | group;
term        = factor >> *(('*' >> factor) | ('/' >> factor));
expression  = term >> *(('+' >> term) | ('-' >> term));

            integer = int_p[integer.val = _1];
        }

        // Tell Spirit to start parsing with "top"
        rule<Tokenizer> const& start() const { return top; }
    };
};

////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////
int
main()
{
    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "\t\tThe Calculator...\n\n";
    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "Type an expression...or [q or Q] to quit\n\n";

    calculator calc; //  Our Grammar

    string str;
    while (getline(cin, str))
    {
        if (str[0] == 'q' || str[0] == 'Q')
            break;

        double n = 0;
        parse_info<> info = parse(str.c_str(), calc[var(n) = _1], space_p);

        //  calc[var(n) = arg1] invokes the calculator and extracts
        //  the result of the computation. See calculator grammar
        //  note above.

        if (info.full)
        {
            cout << "-------------------------\n";
            cout << "Parsing succeeded\n";
            cout << "result = " << n << endl;
            cout << "-------------------------\n";
        }
        else
        {
            cout << "-------------------------\n";
            cout << "Parsing failed\n";
            cout << "stopped at: \": " << info.stop << "\"\n";
            cout << "-------------------------\n";
        }
    }

    cout << "Bye... :-) \n\n";
    return 0;
}


//DISPLAY 11.12 Implementation of StringVar
//This is the implementation of the class StringVar.
//The definition for the class StringVar is in Display 11.11.
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <cstring>
using namespace std;

    //Uses cstddef and cstdlib:
    StringVar::StringVar(int size) : maxLength(size)
    {
        value = new char[maxLength + 1];//+1 is for '\0'.
        value[0] = '\0';
    }

    //Uses cstddef and cstdlib:
    StringVar::StringVar( ) : maxLength(100)
    {
        value = new char[maxLength + 1];//+1 is for '\0'.
        value[0] = '\0';
    }

    //Uses cstring, cstddef, and cstdlib:
    StringVar::StringVar(const char a[]) : maxLength(strlen(a))
    {
        value = new char[maxLength + 1];//+1 is for '\0'.
        strcpy(value, a);
    }
    //Uses cstring, cstddef, and cstdlib:
    StringVar::StringVar(const StringVar& stringObject)
                            : maxLength(stringObject.length( ))
    {
        value = new char[maxLength + 1];//+1 is for '\0'.
        strcpy(value, stringObject.value);
    }

	StringVar::~StringVar( )
    {
        delete [] value;
    }

    //Uses cstring:
    int StringVar::length( ) const
    {
        return strlen(value);
    }

    //Uses iostream:
    void StringVar::input_line(istream& ins)
    {
        ins.getline(value, maxLength + 1);
    }

    //Uses iostream:
    ostream& operator <<(ostream& outs, const StringVar& theString)
    {
        outs << theString.value;
        return outs;
    }

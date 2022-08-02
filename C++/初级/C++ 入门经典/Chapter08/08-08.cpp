//DISPLAY 8.8 Palindrome Testing Program
//Test for palindrome property.
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

void swap(char& v1, char& v2);
//Interchanges the values of v1 and v2.

string reverse(const string& s);
//Returns a copy of s but with characters in reverse order.

string removePunct(const string& s, const string& punct);
//Returns a copy of s with any occurrences of characters
//in the string punct removed.

string makeLower(const string& s);
//Returns a copy of s that has all uppercase
//characters changed to lowercase, other characters unchanged.

bool isPal(const string& s);
//Returns true if s is a palindrome, false otherwise.

int main( )
{
    string str;
    cout << "Enter a candidate for palindrome test\n"
         << "followed by pressing Return.\n";
    getline(cin, str);

    if (isPal(str))
         cout << "\"" << str + "\" is a palindrome.";
    else
         cout << "\"" << str + "\" is not a palindrome.";
    cout << endl;

    return 0;
}

void swap(char& v1, char& v2)
{
    char temp = v1;
    v1 = v2;
    v2 = temp;
}
string reverse(const string& s)
{
    int start = 0;
    int end = s.length( );
    string temp(s);

    while (start < end)
    {
       end--;
       swap(temp[start], temp[end]);
       start++;
    }

    return temp;
}

//Uses <cctype> and <string>
string makeLower(const string& s)
{
    string temp(s);
    for (int i = 0; i < s.length( ); i++)
        temp[i] = tolower(s[i]);

    return temp;
}

string removePunct(const string& s, const string& punct)
{
    string noPunct; //initialized to empty string
    int sLength = s.length( );
    int punctLength = punct.length( );

    for (int i = 0; i < sLength; i++)
    {
         string aChar = s.substr(i,1); //A one-character string
         int location = punct.find(aChar, 0);
         //Find location of successive characters
         //of src in punct.

      if (location < 0 || location >= punctLength)
         noPunct = noPunct + aChar; //aChar not in punct, so keep it
    }

    return noPunct;
}
//uses functions makeLower, removePunct
bool isPal(const string& s)
{
    string punct(",;:.?!'\" "); //includes a blank
    string str(s);
    str = makeLower(str);
    string lower_str = removePunct(str, punct);

    return (lower_str == reverse(lower_str));
}


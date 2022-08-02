//DISPLAY 11.11 Program Using the StringVar Class
//This is the definition for the class StringVar
//whose values are strings. An object is declared as follows.
//Note that you use (max_size), not [max_size]
//     StringVar the_object(max_size);
//where max_size is the longest string length allowed.
#include <iostream>
using namespace std;

    class StringVar
    {
    public:
        StringVar(int size);
        //Initializes the object so it can accept string values up to size
        //in length. Sets the value of the object equal to the empty string.

        StringVar( );
        //Initializes the object so it can accept string values of length 100
        //or less. Sets the value of the object equal to the empty string.

        StringVar(const char a[]);
        //Precondition: The array a contains characters terminated with '\0'.
        //Initializes the object so its value is the string stored in a and
        //so that it can later be set to string values up to strlen(a) in length

        StringVar(const StringVar& stringObject);
        //Copy constructor.

        ~StringVar( );
        //Returns all the dynamic memory used by the object to the freestore.

        int length( ) const;
        //Returns the length of the current string value.

         void input_line(istream& ins);
        //Precondition: If ins is a file input stream, then ins has been
        //connected to a file.
        //Action: The next text in the input stream ins, up to '\n', is copied
        //to the calling object. If there is not sufficient room, then
        //only as much as will fit is copied.
        friend ostream& operator <<(ostream& outs, const StringVar& theString);

		//Overloads the << operator so it can be used to output values
		//of type StringVar
		//Precondition: If outs is a file output stream, then outs
		//has already been connected to a file.

 		private:
 			char *value; //pointer to dynamic array that holds the string value.
 			int max_length; //declared max length of any string value.
 		};


//Program to demonstrate use of the class StringVar.

void conversation(int maxNameSize);
//Carries on a conversation with the user.


int main( )
{
    using namespace std;
    conversation(30);
    cout << "End of demonstration.\n";
    return 0;
}

// This is only a demonstration function:
void conversation(int maxNameSize)
{
    using namespace std;

    StringVar your_name(maxNameSize), our_name("Borg");

    cout << "What is your name?\n";
    your_name.input_line(cin);
    cout << "We are " << our_name << endl;
    cout << "We will meet again " << your_name << endl;
}



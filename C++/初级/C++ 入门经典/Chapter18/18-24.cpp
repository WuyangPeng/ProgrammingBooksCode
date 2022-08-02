#include <iostream>
#include <regex>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::regex;

int main()
{
	// A phone number in the format xxx-xxx-xxxx
	// The R denotes a literal string rather than
	// escape the \ character.
	string phonePattern = R"(\d{3} \d{3} \d{4})";
	// A pattern with two words separated by whitespace
	string twoWordPattern = R"(\w+\s\w+)";
	//regex regPhone(phonePattern);
	regex regTwoWord(twoWordPattern);

	string s;
	cout << "Enter a string to test the phone pattern." << endl;
	cin >> s;	
	if (regex_match(s, regPhone))
		cout << s << " matches " << phonePattern << endl;
	else
		cout << s << " doesn't match " << phonePattern << endl;

	cout << "Enter a string to test the two word pattern." << endl;
	cin >> s;	
	if (regex_match(s, regTwoWord))
		cout << s << " matches " << twoWordPattern << endl;
	else
		cout << s << " doesn't match " << twoWordPattern << endl;
}

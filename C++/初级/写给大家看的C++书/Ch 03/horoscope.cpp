// horoscope.cpp - Script 3.6

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file in order
// to work with string variables.
#include <string>

// Start the main function.
int main() {

	// Set basic values.
	unsigned short month = 2;
	unsigned short day = 23;
	std::string sign; // To be determined
	
	// Use a switch for each possible month value.
	switch (month) {
		case 1: // January
			sign = (day <= 19) ? "Capricorn" : "Aquarius";
			break;
		case 2:
			sign = (day <= 18) ? "Aquarius" : "Pisces";
			break;
		case 3:
			sign = (day <= 19) ? "Pisces" : "Aries";
			break;
		case 4:
			sign = (day <= 19) ? "Aries" : "Taurus";
			break;
		case 5:
			sign = (day <= 20) ? "Taurus" : "Gemini";
			break;
		case 6:
			sign = (day <= 21) ? "Gemini" : "Cancer";
			break;
		case 7:
			sign = (day <= 22) ? "Cancer" : "Leo";
			break;
		case 8:
			sign = (day <= 22) ? "Leo" : "Virgo";
			break;
		case 9:
			sign = (day <= 22) ? "Virgo" : "Libra";
			break;
		case 10:
			sign = (day <= 22) ? "Libra" : "Scorpio";
			break;
		case 11:
			sign = (day <= 21) ? "Scorpio" : "Sagittarius";
			break;
		case 12:
			sign = (day <= 21) ? "Sagittarius" : "Capricorn";
			break;
	} // End of switch.

    // Print the sign.
    std::cout << "If your birthday is " << month
	<< "/" << day << ", then your sign is: "
	<< sign << ".\n\n";
		
	// Let the reader know what to do next.
	std::cout << "Press Enter or Return to continue.\n";
	
	// Wait for the user to press Enter or Return.
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.
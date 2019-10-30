/*
 * Utilities.cpp
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#include <cctype>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"

using namespace std;

namespace whowell {
	// Exceptions /////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	IntegerOutOfRangeException :: IntegerOutOfRangeException() {}

	IntegerOutOfRangeException :: ~IntegerOutOfRangeException() noexcept {}

	const char* IntegerOutOfRangeException :: what() const noexcept {
		return "Integer value out of range. Please try again.\n";
	}



	InvalidCharacterInputException :: InvalidCharacterInputException() {}

	InvalidCharacterInputException :: ~InvalidCharacterInputException() noexcept {}

	const char* InvalidCharacterInputException :: what() const noexcept {
		return "Invalid character. Please try again.\n";
	}



	InvalidStringLengthException :: InvalidStringLengthException() {}

	InvalidStringLengthException :: ~InvalidStringLengthException() noexcept {}

	const char* InvalidStringLengthException :: what() const noexcept {
		return "String too long. Please try again.\n";
	}



	NodeNotFoundException :: NodeNotFoundException() {}

	NodeNotFoundException :: ~NodeNotFoundException() noexcept {}

	const char* NodeNotFoundException :: what() const noexcept {
		return "Node not found in list.\n";
	}


	UnableToReserveASeatException :: UnableToReserveASeatException() {}

	UnableToReserveASeatException :: ~UnableToReserveASeatException() noexcept {}

	const char* UnableToReserveASeatException :: what() const noexcept {
		return "Unable to reserve seat.\n";
	}

    // Validation Functions ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

	short int validate_string_as_single_digit_integer_in_range( std::string buffer, short int min, short int max ) {
		std::string::size_type sz = 0;
		short int user_short = 0;

		while (true) {
			try {
				std::cin >> buffer;

				if ( buffer.length() != 1 ) {
					std::cout << "Please enter only one character!" << std::endl;
					continue;
				}

				if ( !isdigit( buffer.at( 0 ) ) ) {
					std::cout << "Please enter only a number!" << std::endl;
					continue;
				}

				//Now, convert the string to an integer, store it in user_short
				//Then, check that the value is within the expected range
				user_short = std::stoi( buffer, &sz );

				if ( user_short < min || user_short > max ) {
					std::cout << "Please enter a number between " << min << " and " << max << '!' << std::endl;
					continue;
				}

				//If no exception has been thrown by this point, then the input is valid.
				break;
			} catch ( ... ) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}

		return user_short;
	}

	short int validate_string_as_double_digit_integer_in_range( std::string buffer, short int min, short int max ) {
		std::string::size_type sz = 0;
		short int user_short = 0;

		while (true) {
			try {
				std::cin >> buffer;

				if ( buffer.length() != 2 ) {
					std::cout << "Please enter only one double digit number!" << std::endl;
					continue;
				}

				if ( !isdigit( buffer.at( 0 ) ) || !isdigit( buffer.at( 1 ) ) ) {
					std::cout << "Please enter only a number!" << std::endl;
					continue;
				}

				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				user_short = std::stoi( buffer, &sz );

				if ( user_short < min || user_short > max ) {
					std::cout << "Please enter a number between " << min << " and " << max << '!' << std::endl;
					continue;
				}

				//If no exception has been thrown by this point, then the input is valid.
				break;
			} catch ( ... ) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}

		return user_short;
	}

	char validate_string_as_character(std::string buffer, char upper_case_character) {
		char user_char = '\n';

		while (true) {
			try {
				std::cin >> buffer;

				if ( buffer.length() != 1 ) {
					std::cout << "Please enter only one character!" << std::endl;
					continue;
				}

				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				user_char = buffer.at(0);

				if ( toupper( user_char ) == upper_case_character ) {
					break;

				} else {
					std::cout << "Please enter another character!" << std::endl;
					continue;
				}

			} catch ( ... ) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}

		return toupper( user_char );
	}

	bool yes_or_no_prompt( std::string prompt ) {
		std::string buffer;
		char answer = 'a';
		do {
			std::cout << prompt << std::endl;
			std::cin >> buffer;

			if ( buffer.length() != 1 ) {
				std::cout << "Please enter only one character!" << std::endl;
				continue;
			}

			answer = toupper( buffer.at( 0 ) );

			if ( answer != 'Y' && answer != 'N' ) {
				std::cout << "Please enter only 'y' or 'n'!" << std::endl;
			}
		} while ( answer != 'Y' && answer != 'N' );

		return ( answer == 'Y' );
	}

	bool check_password( std::string attempt, std::string key ) {

		if (key.compare(attempt) == 0) {
			return true;
		} else {
			return false;
		}
	}

} /* namespace whowell */

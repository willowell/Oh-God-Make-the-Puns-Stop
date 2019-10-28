/*
 * Utilities.h
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

namespace whowell {

	// Exceptions /////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

	class IntegerOutOfRangeException : public std::exception {
		public:
			IntegerOutOfRangeException();
			~IntegerOutOfRangeException() noexcept;
			const char* what() const noexcept;
	};

	class InvalidCharacterInputException : public std::exception {
		public:
			InvalidCharacterInputException();
			~InvalidCharacterInputException() noexcept;
			const char* what() const noexcept;
	};

	class InvalidStringLengthException : public std::exception {
		public:
			InvalidStringLengthException();
			~InvalidStringLengthException() noexcept;
			const char* what() const noexcept;
	};

	class NodeNotFoundException : public std::exception {
		public:
			NodeNotFoundException();
			~NodeNotFoundException() noexcept;
			const char* what() const noexcept;
	};

	class UnableToReserveASeatException : public std::exception {
		public:
			UnableToReserveASeatException();
			~UnableToReserveASeatException() noexcept;
			const char* what() const noexcept;
	};

	// Validation Functions ///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	short int validate_string_as_single_digit_integer_in_range( std::string buffer, short int min, short int max );

	short int validate_string_as_double_digit_integer_in_range( std::string buffer, short int min, short int max );

	char validate_string_as_character( std::string buffer, char upper_case_character );

	bool yes_or_no_prompt( std::string prompt );

	bool check_password( std::string attempt, std::string key );

} /* namespace whowell */

#endif /* UTILITIES_H_ */

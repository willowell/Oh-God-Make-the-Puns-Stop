/*
 * Utilities.h
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <exception>
#include <iostream>
#include <list>

#include "Auditorium.h"
#include "Seat.h"

namespace whowell {

	// Exceptions /////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

	class IntegerOutOfRangeException : public std::exception {
		public:
			IntegerOutOfRangeException();
			~IntegerOutOfRangeException() throw();
			const char* what() const throw();
	};

	class InvalidCharacterInputException : public std::exception {
		public:
			InvalidCharacterInputException();
			~InvalidCharacterInputException() throw();
			const char* what() const throw();
	};

	class InvalidStringLengthException : public std::exception {
		public:
			InvalidStringLengthException();
			~InvalidStringLengthException() throw();
			const char* what() const throw();
	};

	class NodeNotFoundException : public std::exception {
		public:
			NodeNotFoundException() noexcept;
			~NodeNotFoundException() noexcept;
			const char* what() const noexcept;
	};

	class UnableToReserveASeatException : public std::exception {
		public:
			UnableToReserveASeatException();
			~UnableToReserveASeatException() throw();
			const char* what() const throw();
	};

	// List Modification Functions ////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	void performReservationsWithVectors( std::list<Seat>* list, Auditorium* auditorium, std::vector< short > rows, short tickets );

	// Validation Functions ///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	short int validate_string_as_single_digit_integer_in_range( std::string buffer, short int min, short int max );

	short int validate_string_as_double_digit_integer_in_range( std::string buffer, short int min, short int max );

	char validate_string_as_character( std::string buffer, char upper_case_character );


} /* namespace whowell */

#endif /* UTILITIES_H_ */

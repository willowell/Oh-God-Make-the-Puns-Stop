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
			NodeNotFoundException();
			~NodeNotFoundException() throw();
			const char* what() const throw();
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

	void load_list_from_file( std::fstream* from_file, Auditorium* corresponding );

	// Validation Functions ///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	short int validateStringAsSingleDigitIntegerInRange( std::string buffer, short int min, short int max );

	short int validateStringAsDoubleDigitIntegerInRange( std::string buffer, short int min, short int max );

	int validateStringAsIntegerInRange( std::string buffer, int min, int max );

	long int validateStringAsLongIntegerInRange( std::string buffer, long int min, long int max );

	char validateStringAsCharacter( std::string buffer, char upperCaseCharacter );


} /* namespace whowell */

#endif /* UTILITIES_H_ */

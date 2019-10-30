#include "howellWilliam_HelperExceptions.h"

namespace whowell_OhGodMakeThePunsStop_HelperExceptions {

	IntegerOutOfRangeException :: IntegerOutOfRangeException() {}
	IntegerOutOfRangeException :: ~IntegerOutOfRangeException() throw() {}
	const char* IntegerOutOfRangeException :: what() const throw() {
		return "Integer value out of range. Please try again.\n";
	}

	InvalidCharacterInputException :: InvalidCharacterInputException() {}
	InvalidCharacterInputException :: ~InvalidCharacterInputException() throw() {}
	const char* InvalidCharacterInputException :: what() const throw() {
		return "Invalid character. Please try again.\n";
	}

	InvalidStringLengthException :: InvalidStringLengthException() {}
	InvalidStringLengthException :: ~InvalidStringLengthException() throw() {}
	const char* InvalidStringLengthException :: what() const throw() {
		return "String too long. Please try again.\n";
	}

	NodeNotFoundException :: NodeNotFoundException() {}
	NodeNotFoundException :: ~NodeNotFoundException() throw() {}
	const char* NodeNotFoundException :: what() const throw() {
		return "Node not found in list.\n";
	}

	UnableToReserveASeatException :: UnableToReserveASeatException() {}
	UnableToReserveASeatException :: ~UnableToReserveASeatException() throw() {}
	const char* UnableToReserveASeatException :: what() const throw() {
		return "Unable to reserve seat.\n";
	}

} /* namespace HelperExceptions */

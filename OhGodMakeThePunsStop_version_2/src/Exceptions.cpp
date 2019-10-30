/*
 * Exceptions.cpp
 *
 *  Created on: Oct. 30, 2019
 *      Author: whowell
 */

#include "Exceptions.h"

namespace whowell {

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
} /* namespace whowell */

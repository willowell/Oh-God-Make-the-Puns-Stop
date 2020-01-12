/*
 * Exceptions.cpp
 *
 *  Created on: Oct. 30, 2019
 *      Author: Whowell
 */

#include "Exceptions.h"

namespace Whowell {
	
	IntegerOutOfRangeException::IntegerOutOfRangeException() = default;
	
	IntegerOutOfRangeException::~IntegerOutOfRangeException() noexcept = default;
	
	const char * IntegerOutOfRangeException::what() const noexcept {
		return "Integer value out of range. Please try again.\n";
	}
	
	
	InvalidCharacterInputException::InvalidCharacterInputException() = default;
	
	InvalidCharacterInputException::~InvalidCharacterInputException() noexcept = default;
	
	const char * InvalidCharacterInputException::what() const noexcept {
		return "Invalid character. Please try again.\n";
	}
	
	
	InvalidStringLengthException::InvalidStringLengthException() = default;
	
	InvalidStringLengthException::~InvalidStringLengthException() noexcept = default;
	
	const char * InvalidStringLengthException::what() const noexcept {
		return "String too long. Please try again.\n";
	}
	
	
	NodeNotFoundException::NodeNotFoundException() = default;
	
	NodeNotFoundException::~NodeNotFoundException() noexcept = default;
	
	const char * NodeNotFoundException::what() const noexcept {
		return "Node not found in list.\n";
	}
	
	
	UnableToReserveASeatException::UnableToReserveASeatException() = default;
	
	UnableToReserveASeatException::~UnableToReserveASeatException() noexcept = default;
	
	const char * UnableToReserveASeatException::what() const noexcept {
		return "Unable to reserve seat.\n";
	}
} /* namespace Whowell */

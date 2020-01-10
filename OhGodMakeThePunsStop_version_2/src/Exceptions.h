/*
 * Exceptions.h
 *
 *  Created on: Oct. 30, 2019
 *      Author: Whowell
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>

namespace Whowell {
	
	class IntegerOutOfRangeException : public std::exception {
	public:
		IntegerOutOfRangeException();
		
		~IntegerOutOfRangeException() noexcept;
		
		const char * what() const noexcept;
	};
	
	class InvalidCharacterInputException : public std::exception {
	public:
		InvalidCharacterInputException();
		
		~InvalidCharacterInputException() noexcept;
		
		const char * what() const noexcept;
	};
	
	class InvalidStringLengthException : public std::exception {
	public:
		InvalidStringLengthException();
		
		~InvalidStringLengthException() noexcept;
		
		const char * what() const noexcept;
	};
	
	class NodeNotFoundException : public std::exception {
	public:
		NodeNotFoundException();
		
		~NodeNotFoundException() noexcept;
		
		const char * what() const noexcept;
	};
	
	class UnableToReserveASeatException : public std::exception {
	public:
		UnableToReserveASeatException();
		
		~UnableToReserveASeatException() noexcept;
		
		const char * what() const noexcept;
	};
	
} /* namespace Whowell */

#endif /* EXCEPTIONS_H_ */

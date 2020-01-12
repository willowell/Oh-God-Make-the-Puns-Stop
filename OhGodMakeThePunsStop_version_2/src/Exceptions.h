/*
 * Exceptions.h
 *
 *  Created on: Oct. 30, 2019
 *      Author: Whowell
 */

#ifndef OHGODMAKETHEPUNSSTOP_VERSION_2_EXCEPTIONS_H
#define OHGODMAKETHEPUNSSTOP_VERSION_2_EXCEPTIONS_H

#include <exception>

namespace Whowell {
	
	class IntegerOutOfRangeException : public std::exception {
	public:
		IntegerOutOfRangeException();
		
		~IntegerOutOfRangeException() noexcept override;
		
		[[nodiscard]] const char * what() const noexcept override;
	};
	
	class InvalidCharacterInputException : public std::exception {
	public:
		InvalidCharacterInputException();
		
		~InvalidCharacterInputException() noexcept override;
		
		[[nodiscard]] const char * what() const noexcept override;
	};
	
	class InvalidStringLengthException : public std::exception {
	public:
		InvalidStringLengthException();
		
		~InvalidStringLengthException() noexcept override;
		
		[[nodiscard]] const char * what() const noexcept override;
	};
	
	class NodeNotFoundException : public std::exception {
	public:
		NodeNotFoundException();
		
		~NodeNotFoundException() noexcept override;
		
		[[nodiscard]] const char * what() const noexcept override;
	};
	
	class UnableToReserveASeatException : public std::exception {
	public:
		UnableToReserveASeatException();
		
		~UnableToReserveASeatException() noexcept override;
		
		[[nodiscard]] const char * what() const noexcept override;
	};
	
} /* namespace Whowell */

#endif /*OHGODMAKETHEPUNSSTOP_VERSION_2_EXCEPTIONS_H*/

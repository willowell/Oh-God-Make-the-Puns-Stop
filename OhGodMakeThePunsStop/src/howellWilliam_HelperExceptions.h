#ifndef OHGODMAKETHEPUNSSTOP_HELPEREXCEPTIONS_H_
#define OHGODMAKETHEPUNSSTOP_HELPEREXCEPTIONS_H_

#include <exception>

namespace whowell_OhGodMakeThePunsStop_HelperExceptions {

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
} /* namespace HelperExceptions */

#endif /* OHGODMAKETHEPUNSSTOP_HELPEREXCEPTIONS_H_ */

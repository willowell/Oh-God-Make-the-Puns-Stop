#ifndef OHGODMAKETHEPUNSSTOP_HELPERFUNCTIONS_H_
#define OHGODMAKETHEPUNSSTOP_HELPERFUNCTIONS_H_

#include <iostream>
#include <vector>

#include "howellWilliam_Auditorium.h"
#include "howellWilliam_DoublyLinkedList.h"

using namespace whowell_OhGodMakeThePunsStop;

namespace whowell_OhGodMakeThePunsStop_HelperFunctions {
	int validateStringAsSingleDigitIntegerInRange( std::string str, int min, int max );
	int validateStringAsDoubleDigitIntegerInRange( std::string str, int min, int max );
	char validateStringAsCharacter(                std::string str, char upperch1, char upperch2 );
	void performReservationsWithVectors(           DoublyLinkedList* list, Auditorium* auditorium,
				                                   	   std::vector< short > rows, short tickets );
} /* namespace whowell_HelperFunctions */

#endif /* OHGODMAKETHEPUNSSTOP_HELPERFUNCTIONS_H_ */

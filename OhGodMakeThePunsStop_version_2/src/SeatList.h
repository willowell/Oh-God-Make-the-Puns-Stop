/*
 * SeatList.h
 *
 *  Created on: Oct. 8, 2019
 *      Author: whowell
 */

#ifndef SEATLIST_H_
#define SEATLIST_H_

#include <list>

#include "Seat.h"

namespace whowell {

class SeatList {
private:
	std::list<Seat> seat_list;
public:
	SeatList();
	virtual ~SeatList();
};

} /* namespace whowell */

#endif /* SEATLIST_H_ */

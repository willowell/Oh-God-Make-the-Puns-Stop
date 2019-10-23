//============================================================================
// Name        : OhGodMakeThePunsStop_version_2.cpp
// Author      : wphowell
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include <boost/format.hpp>

#include "Auditorium.h"
#include "Seat.h"
#include "SeatList.h"
#include "Theatre.h"
#include "Utilities.h"


using namespace std;
using namespace whowell;

int main() {
	cout << boost::format("!!!Hello %1%!!!") % __func__ << endl; // prints !!!Hello World!!!

	std::fstream      file_1;
	std::fstream      file_2;
	std::fstream      file_3;
	Auditorium        auditorium_1;
	Auditorium        auditorium_2;
	Auditorium        auditorium_3;



	return 0;
}

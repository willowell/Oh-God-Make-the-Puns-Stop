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

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///INIT PHASE

	try {
		file_1 = std::fstream( "A1.txt", std::ios::in );
		file_2 = std::fstream( "A2.txt", std::ios::in );
		file_3 = std::fstream( "A3.txt", std::ios::in );
	} catch (...) {
		std::cerr << "Something went wrong with the files!" << std::endl;
		return EXIT_FAILURE;
	}

	auditorium_1.set_auditorium_id(1);
	auditorium_2.set_auditorium_id(2);
	auditorium_3.set_auditorium_id(3);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///LOAD PHASE

	auditorium_1.load_from_file(file_1);
	auditorium_2.load_from_file(file_2);
	auditorium_3.load_from_file(file_3);

    //Close the input files - they aren't needed until the end of the program.
    file_1.close();
    file_2.close();
    file_3.close();

    auditorium_1.display();
    auditorium_1.display_list();

    auditorium_2.display();
    auditorium_2.display_list();

    auditorium_3.display();
    auditorium_3.display_list();

	return EXIT_SUCCESS;
}

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

#include "Seat.h"
#include "Utilities.h"


using namespace std;
using namespace whowell;

int main() {
	cout << boost::format("!!!Hello %1%!!!") % __func__ << endl; // prints !!!Hello World!!!

	std::unique_ptr< std::fstream >      file_1;
	std::unique_ptr< std::fstream >      file_2;
	std::unique_ptr< std::fstream >      file_3;
	std::unique_ptr< std::list< Seat > > list_1;
	std::unique_ptr< std::list< Seat > > list_2;
	std::unique_ptr< std::list< Seat > > list_3;



	return 0;
}

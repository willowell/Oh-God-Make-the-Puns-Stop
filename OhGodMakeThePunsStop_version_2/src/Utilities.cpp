/*
 * Utilities.cpp
 *
 *  Created on: Oct. 7, 2019
 *      Author: Whowell
 */



#include "Auditorium.h"
#include "Seat.h"
#include "Theatre.h"
#include "Utilities.h"
#include "Lifecycle.h"

namespace Whowell {
	// Validation Functions ///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	
	char my_toupper(char ch) {
		return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
	}
	
	int validate_string_as_single_digit_integer_in_range(std::string buffer, short int min, short int max) {
		std::string::size_type sz = 0;
		int user_input = 0;
		
		while (true) {
			try {
				std::cin >> buffer;
				
				if (buffer.length() != 1) {
					std::cout << "Please enter only one character!" << std::endl;
					continue;
				}
				
				if (!isdigit(buffer.at(0))) {
					std::cout << "Please enter only a number!" << std::endl;
					continue;
				}
				
				//Now, convert the string to an integer, store it in user_input
				//Then, check that the value is within the expected range
				user_input = std::stoi(buffer, &sz);
				
				if (user_input < min || user_input > max) {
					std::cout << "Please enter a number between " << min << " and " << max << '!' << std::endl;
					continue;
				}
				
				//If no exception has been thrown by this point, then the input is valid.
				break;
			} catch (...) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}
		
		return user_input;
	}
	
	int validate_string_as_double_digit_integer_in_range(std::string buffer, short int min, short int max) {
		std::string::size_type sz = 0;
		int user_input = 0;
		
		while (true) {
			try {
				std::cin >> buffer;
				
				// Check against the buffer being empty or the buffer containing more than 2 characters
				if (buffer.length() > 2) {
					std::cout << "Please enter only one double digit number!" << std::endl;
					continue;
				}
				
				if (buffer.length() == 1) {
					if (!isdigit(buffer.at(0))) {
						std::cout << "Please enter only a number!" << std::endl;
						continue;
					}
				} else if (buffer.length() == 2) {
					if (!isdigit(buffer.at(0)) || !isdigit(buffer.at(1))) {
						std::cout << "Please enter only a number!" << std::endl;
						continue;
					}
				}
				
				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				user_input = std::stoi(buffer, &sz);
				
				if (user_input < min || user_input > max) {
					std::cout << "Please enter a number between " << min << " and " << max << '!' << std::endl;
					continue;
				}
				
				//If no exception has been thrown by this point, then the input is valid.
				break;
			} catch (...) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}
		
		return user_input;
	}
	
	char validate_string_as_character(std::string buffer, char upper_case_character) {
		char user_input = '\n';
		
		while (true) {
			try {
				std::cin >> buffer;
				
				if (buffer.length() != 1) {
					std::cout << "Please enter only one character!" << std::endl;
					continue;
				}
				
				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				user_input = buffer.at(0);
				
				if (my_toupper(user_input) == upper_case_character) {
					break;
					
				} else {
					std::cout << "Please enter another character!" << std::endl;
					continue;
				}
				
			} catch (...) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}
		
		return my_toupper(user_input);
	}
	
	bool yes_or_no_prompt(const std::string& prompt) {
		std::string buffer;
		char answer = 'a';
		do {
			std::cout << prompt << std::endl;
			std::cin >> buffer;
			
			if (buffer.length() != 1) {
				std::cout << "Please enter only one character!" << std::endl;
				continue;
			}
			
			answer = my_toupper(buffer.at(0));
			
			if (answer != 'Y' && answer != 'N') {
				std::cout << "Please enter only 'y' or 'n'!" << std::endl;
			}
		} while (answer != 'Y' && answer != 'N');
		
		return (answer == 'Y');
	}
	
	bool check_password(const std::string& attempt, std::string answer) {
		
		return (answer == attempt);
	}
	
	////////////////////////////////////////////////////////////////////////////
	/// SUBROUTINES ////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	
	void pause_thread(int for_milliseconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(for_milliseconds));
	}
	
	void display_auditoriums_on_switch(int on_switch) {
		switch (on_switch) {
			case 1: {
				auditorium_1.display_grid();
				break;
			}
			
			case 2: {
				auditorium_2.display_grid();
				break;
			}
			
			case 3: {
				auditorium_3.display_grid();
				break;
			}
			
			default: {
				std::cerr << "This should be unreachable!\n"
						  << "(short int) user_short is " << user_short
						  << std::endl;
				break;
			}
		}
	}
	
	void calculate_theatre_values() {
		theatre.set_total_seats(
				auditorium_1.get_total_seats() +
				auditorium_2.get_total_seats() +
				auditorium_3.get_total_seats()
		);
		
		theatre.set_total_seats_open(
				auditorium_1.get_num_seats_open() +
				auditorium_2.get_num_seats_open() +
				auditorium_3.get_num_seats_open()
		);
		
		theatre.set_total_seats_reserved(
				auditorium_1.get_num_seats_reserved() +
				auditorium_2.get_num_seats_reserved() +
				auditorium_3.get_num_seats_reserved()
		);
		
		theatre.set_user_seats(user_selected_tickets);
		
		theatre.calculate_total_sales();
	}
	
	void log_reservation_request() {
		std::string request;
		request = std::string("User request: ") + std::to_string(user_selected_tickets)
				  + std::string(" tickets.");
		
		user_logged_requests.push_back(request);
	}
	
	void save_reservation_requests_to_file() {
		if (user_logged_requests.empty()) {
			return;
		}
		
		std::ofstream out_file("assets/requests.txt", std::ios::app);
		
		if (out_file.fail()) {
			std::cout << "Couldn't open the file!" << std::endl;
			return;
		}
		
		for (const auto & request : user_logged_requests) {
			out_file << request << std::endl;
		}
		
		out_file.close();
		
		// Clear the vector.
		user_logged_requests.clear();
	}
} /* namespace Whowell */

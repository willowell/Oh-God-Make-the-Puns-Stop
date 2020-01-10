/*
 * Utilities.cpp
 *
 *  Created on: Oct. 7, 2019
 *      Author: Whowell
 */

#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <fmt/core.h>

#include "Auditorium.h"
#include "Seat.h"
#include "Theatre.h"
#include "Utilities.h"

namespace Whowell {
	// Validation Functions ///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	
	short int validate_string_as_single_digit_integer_in_range(std::string buffer, short int min, short int max) {
		std::string::size_type sz = 0;
		short int user_short = 0;
		
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
				
				//Now, convert the string to an integer, store it in user_short
				//Then, check that the value is within the expected range
				user_short = std::stoi(buffer, &sz);
				
				if (user_short < min || user_short > max) {
					std::cout << "Please enter a number between " << min << " and " << max << '!' << std::endl;
					continue;
				}
				
				//If no exception has been thrown by this point, then the input is valid.
				break;
			} catch (...) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}
		
		return user_short;
	}
	
	short int validate_string_as_double_digit_integer_in_range(std::string buffer, short int min, short int max) {
		std::string::size_type sz = 0;
		short int user_short = 0;
		
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
				user_short = std::stoi(buffer, &sz);
				
				if (user_short < min || user_short > max) {
					std::cout << "Please enter a number between " << min << " and " << max << '!' << std::endl;
					continue;
				}
				
				//If no exception has been thrown by this point, then the input is valid.
				break;
			} catch (...) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}
		
		return user_short;
	}
	
	char validate_string_as_character(std::string buffer, char upper_case_character) {
		char user_char = '\n';
		
		while (true) {
			try {
				std::cin >> buffer;
				
				if (buffer.length() != 1) {
					std::cout << "Please enter only one character!" << std::endl;
					continue;
				}
				
				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				user_char = buffer.at(0);
				
				if (toupper(user_char) == upper_case_character) {
					break;
					
				} else {
					std::cout << "Please enter another character!" << std::endl;
					continue;
				}
				
			} catch (...) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}
		
		return toupper(user_char);
	}
	
	bool yes_or_no_prompt(std::string prompt) {
		std::string buffer;
		char answer = 'a';
		do {
			std::cout << prompt << std::endl;
			std::cin >> buffer;
			
			if (buffer.length() != 1) {
				std::cout << "Please enter only one character!" << std::endl;
				continue;
			}
			
			answer = toupper(buffer.at(0));
			
			if (answer != 'Y' && answer != 'N') {
				std::cout << "Please enter only 'y' or 'n'!" << std::endl;
			}
		} while (answer != 'Y' && answer != 'N');
		
		return (answer == 'Y');
	}
	
	bool check_password(std::string attempt, std::string key) {
		
		if (key.compare(attempt) == 0) {
			return true;
		} else {
			return false;
		}
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
	
	////////////////////////////////////////////////////////////////////////////
	/// MENU ITEMS /////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	
	void return_to_main_menu() {
		std::cout << "Returning to the main menu." << std::endl;
		// Wait a little bit before returning to the main menu.
		pause_thread(pause_time_ms);
	}
	
	void handle_main_menu() {
		user_short = -1;
		user_choice = -1;
		
		std::cout << "Please enter a number corresponding to a menu item.\n"
				  << "(1) View an auditorium.\n"
				  << "(2) Make a reservation.\n"
				  << "(3) Advanced options.\n"
				  << "(4) Save and quit."
				  << std::endl;
		
		user_short = validate_string_as_single_digit_integer_in_range(buffer, 1, 4);
		user_choice = user_short;
		
		// Wait a little bit after accepting user input to show the next menu.
		pause_thread(pause_time_ms);
	}
	
	void handle_auditorium_display_menu() {
		user_short = -1;
		
		std::cout << "Please enter the number of the auditorium you wish to view.\n"
				  << "You can choose Auditorium (1), (2), or (3).\n"
				  << std::endl;
		
		user_short = validate_string_as_single_digit_integer_in_range(buffer, 1, 3);
		
		// Wait a little bit after accepting user input to show an auditorium.
		pause_thread(pause_time_ms);
		
		display_auditoriums_on_switch(user_short);
	}
	
	void handle_reservation_menu() {
		user_short = -1;
		user_wants_manual_reservation = false;
		user_wants_to_log_request = false;
		
		std::cout << "Please enter the number of the auditorium you wish to view.\n"
				  << "You can choose Auditorium (1), (2), or (3).\n"
				  << std::endl;
		
		user_short = validate_string_as_single_digit_integer_in_range(buffer, 1, 3);
		
		// Wait a little bit after accepting user input to show an auditorium.
		pause_thread(pause_time_ms);
		
		display_auditoriums_on_switch(user_short);
		
		std::cout << std::endl;
		
		std::cout << "Please enter the number of tickets you wish to purchase."
				  << std::endl;
		
		user_selected_tickets = validate_string_as_double_digit_integer_in_range(buffer, 1, 100);
		
		// Wait a little bit before showing the next prompt.
		pause_thread(pause_time_ms);
		
		user_wants_manual_reservation = yes_or_no_prompt(
				"Would you like to manually reserve the seats? [y/n]\n"
				"Otherwise, the program will ask if you want to log your request.\n"
		);
		
		short int loop_limit = user_selected_tickets;
		
		// For every ticket the user wants, set aside a slot for a seat.
		for (short int i = 0; i < loop_limit; ++i) {
			user_selected_rows.push_back(i);
			user_selected_seats.push_back(i);
		}
		
		if (user_wants_manual_reservation) {
			// The vectors are now big enough to store the user's desired seats.
			// Request values for the seat positions.
			for (short int k = 0; k < loop_limit; k++) {
				fmt::print(stdout, "Please enter the row number for the {} seat that you want to purchase.\n", (k + 1));
				user_selected_rows[k] = validate_string_as_double_digit_integer_in_range(buffer, 1, 100);
				
				fmt::print(stdout, "Please enter the seat number for the {} seat that you want to purchase.\n", (k + 1));
				user_selected_seats[k] = validate_string_as_double_digit_integer_in_range(buffer, 1, 100);
			}
			
			for (short int k = 0; k < loop_limit; k++) {
				std::cerr << "(seat, row) (x, y) = (" << user_selected_seats[k] << ", " << user_selected_rows[k]
						  << "). " << std::endl;
			}
			
			// The vectors should now hold all the seats that the user wants.
			// Check the availability of the seats.
			try {
				switch (user_short) {
					// Auditorium 1
					case 1: {
						for (short int i = 0; i < user_selected_tickets; ++i) {
							auditorium_1.reserve_seat_without_input(
									user_selected_rows[i], user_selected_seats[i]
							);
						}
						std::cout << "Seats reserved!" << std::endl;
						
						break;
					}
						
						// Auditorium 2
					case 2: {
						for (short int i = 0; i < user_selected_tickets; ++i) {
							auditorium_2.reserve_seat_without_input(
									user_selected_rows[i], user_selected_seats[i]
							);
						}
						std::cout << "Seats reserved!" << std::endl;
						
						break;
					}
						
						// Auditorium 3
					case 3: {
						for (short int i = 0; i < user_selected_tickets; ++i) {
							auditorium_3.reserve_seat_without_input(
									user_selected_rows[i], user_selected_seats[i]
							);
						}
						std::cout << "Seats reserved!" << std::endl;
						
						break;
					}
					
					default: {
						std::cerr << "This should be unreachable!\n"
								  << "(short int) user_short is " << user_short
								  << std::endl;
						break;
					}
				} // Close switch-case
			} catch (UnableToReserveASeatException & e) {
				std::cout << e.what() << std::endl;
			}
			
			// Special Request Logging
		} else {
			user_wants_to_log_request = yes_or_no_prompt(
					"The program could not find the seats that you wanted.\n"
					"Would you like to log your request so that a manager\n"
					"can view your request and take care of it? [y/n]\n"
			);
			
			pause_thread(pause_time_ms);
			
			if (user_wants_to_log_request) {
				std::cout << "Okay! The program will save your request.\n"
						  << std::endl;
				log_reservation_request();
				
			} else {
				std::cout << "Okay! Your request will not be saved." << std::endl;
			}
		}
		// Reset the vectors.
		user_selected_rows.clear();
		user_selected_seats.clear();
	}
	
	void handle_advanced_options_menu() {
		user_short = -1;
		buffer.clear();
		
		std::cout << "Please enter the password to continue.\n"
				  << "If the password is incorrect, you will be returned to the main menu."
				  << std::endl;
		std::cin >> buffer;
		
		is_password_good = check_password(buffer, key);
		
		if (is_password_good) {
			std::cout << "Welcome, administator!" << std::endl;
			std::cout << "Please enter a number corresponding to a menu item.\n"
					  << "(1) View special seating requests.\n"
					  << "(2) View sales report.\n"
					  << "(3) Print sales report.\n"
					  << "(4) Backup current auditorium files.\n"
					  << "(5) Undo current session.\n"
					  << "(6) Reset auditoriums.\n"
					  << "(7) Return to main menu.\n"
					  << std::endl;
			
			user_short = validate_string_as_single_digit_integer_in_range(buffer, 1, 7);
			
			switch (user_short) {
				
				/**
				 * View special seating requests
				 */
				case 1: {
					std::cout << "Viewing special seating requests..." << std::endl;
					
					std::ifstream in_file("assets/requests.txt");
					if (in_file.is_open()) {
						std::string line;
						while (std::getline(in_file, line)) {
							std::cout << line << std::endl;
						}
					}
					in_file.close();
					
					std::cout << '\n' << std::endl;
					
					break;
				}
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					
					/**
					 * View sales report
					 */
				case 2: {
					theatre.view_sales_report();
					
					break;
				}
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					
					/**
					 * Print sales report
					 */
				case 3: {
					std::cout << "Printing sales report to file 'sales_report.txt'" << std::endl;
					
					file_1.open("assets/sales_report.txt", std::ios::out | std::ios::trunc);
					
					theatre.save_sales_report(file_1);
					
					file_1.close();
					
					std::cout << "Printing done!" << std::endl;
					
					break;
				}
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					
					/**
					 * Backup current auditorium files
					 */
				case 4: {
					std::cout << "Backing up current auditorium files.\n"
							  << "Warning: current backups will be overwritten!"
							  << std::endl;
					
					file_1.open("assets/A1_backup.txt", std::ios::out | std::ios::trunc);
					file_2.open("assets/A2_backup.txt", std::ios::out | std::ios::trunc);
					file_3.open("assets/A3_backup.txt", std::ios::out | std::ios::trunc);
					
					auditorium_1.write_to_file(file_1);
					auditorium_2.write_to_file(file_2);
					auditorium_3.write_to_file(file_3);
					
					file_1.close();
					file_2.close();
					file_3.close();
					
					std::cout << "The data has been backed up." << std::endl;
					
					break;
				}
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					
					/**
					 * Undo current session.
					 * Since the auditoriums are represented as an std::list
					 * during the program,
					 * reloading the files is enough to undo any changes to
					 * the std::list.
					 */
				case 5: {
					bool is_user_sure = false;
					
					is_user_sure = yes_or_no_prompt(
							"Are you sure you want to undo the current session? [y/n]"
					);
					
					if (is_user_sure) {
						std::cout << "Okay! The auditoriums will be reloaded,\n"
								  << "thereby undoing the current session."
								  << std::endl;
						
						
						// These are the same files from the start of the program.
						// I am assuming that if they were successfully opened
						// at the start of the program, they will not throw
						// an error here.
						file_1 = std::fstream("assets/A1.txt", std::ios::in);
						file_2 = std::fstream("assets/A2.txt", std::ios::in);
						file_3 = std::fstream("assets/A3.txt", std::ios::in);
						
						auditorium_1.load_from_file(file_1);
						auditorium_2.load_from_file(file_2);
						auditorium_3.load_from_file(file_3);
						
						file_1.close();
						file_2.close();
						file_3.close();
					} else {
						std::cout << "Okay! Returning to the main menu instead." << std::endl;
					}
					
					std::cout << "The current session has been undone." << std::endl;
					
					break;
				}
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					
					/**
					 * Reset auditoriums
					 */
				case 6: {
					bool is_user_sure = false;
					
					is_user_sure = yes_or_no_prompt(
							"Are you sure you want to reset the auditoriums? [y/n]"
					);
					
					if (is_user_sure) {
						std::cout << "Okay! All of the seats in the auditorium"
								  << "will be set to unreserved."
								  << std::endl;
						
						auditorium_1.reset();
						auditorium_2.reset();
						auditorium_3.reset();
						
					} else {
						std::cout << "Okay! Returning to the main menu instead." << std::endl;
					}
					
					std::cout << "The auditoriums have been reset." << std::endl;
					
					break;
				}
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					
					/**
					 * Return to main menu
					 */
				case 7: {
					// Pass
					// There is no need to do anything here.
					break;
				}
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////
				
				default: {
					std::cerr << "This should be unreachable!\n"
							  << "(short int) user_short is " << user_short
							  << std::endl;
					
					break;
				}
			}
		} else {
			std::cout << "The password you entered is incorrect." << std::endl;
		}
	}
	
	void handle_quit_menu() {
		user_wants_to_quit = yes_or_no_prompt(
				"Are you sure you want to quit? [y/n]\nChanges to the data will be saved."
		);
		
		if (user_wants_to_quit) {
			// Wait a little bit after accepting user input to show the next text.
			pause_thread(pause_time_ms);
			
			std::cout << "Quitting the program.\n"
					  << "Please wait while the data is saved." << std::endl;
			
			file_1.open("assets/A1.txt", std::ios::out | std::ios::trunc);
			file_2.open("assets/A2.txt", std::ios::out | std::ios::trunc);
			file_3.open("assets/A3.txt", std::ios::out | std::ios::trunc);
			
			auditorium_1.write_to_file(file_1);
			auditorium_2.write_to_file(file_2);
			auditorium_3.write_to_file(file_3);
			
			file_1.close();
			file_2.close();
			file_3.close();
			
			save_reservation_requests_to_file();
			
			std::cout << "The data has been saved to the files." << std::endl;
			
		} else {
			return_to_main_menu();
		}
	}
} /* namespace Whowell */

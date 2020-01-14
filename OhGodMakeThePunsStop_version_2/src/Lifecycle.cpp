//
// Created by William Howell on 2020-01-14.
//

#include "Lifecycle.h"

namespace Whowell {
	void return_to_main_menu() {
		std::cout << "Returning to the main menu." << std::endl;
		// Wait a little bit before returning to the main menu.
		Whowell::pause_thread(Whowell::pause_time_ms);
	}
	
	void handle_main_menu() {
		Whowell::user_short = -1;
		Whowell::user_choice = -1;
		
		std::cout << "Please enter a number corresponding to a menu item.\n"
				  << "(1) View an auditorium.\n"
				  << "(2) Make a reservation.\n"
				  << "(3) Advanced options.\n"
				  << "(4) Save and quit."
				  << std::endl;
		
		Whowell::user_short = Whowell::validate_string_as_single_digit_integer_in_range(Whowell::buffer, 1, 4);
		Whowell::user_choice = Whowell::user_short;
		
		// Wait a little bit after accepting user input to show the next menu.
		Whowell::pause_thread(Whowell::pause_time_ms);
	}
	
	void handle_auditorium_display_menu() {
		Whowell::user_short = -1;
		
		std::cout << "Please enter the number of the auditorium you wish to view.\n"
				  << "You can choose Auditorium (1), (2), or (3).\n"
				  << std::endl;
		
		Whowell::user_short = Whowell::validate_string_as_single_digit_integer_in_range(Whowell::buffer, 1, 3);
		
		// Wait a little bit after accepting user input to show an auditorium.
		Whowell::pause_thread(Whowell::pause_time_ms);
		
		Whowell::display_auditoriums_on_switch(Whowell::user_short);
	}
	
	void handle_reservation_menu() {
		Whowell::user_short = -1;
		Whowell::user_wants_manual_reservation = false;
		Whowell::user_wants_to_log_request = false;
		
		std::cout << "Please enter the number of the auditorium you wish to view.\n"
				  << "You can choose Auditorium (1), (2), or (3).\n"
				  << std::endl;
		
		Whowell::user_short = Whowell::validate_string_as_single_digit_integer_in_range(Whowell::buffer, 1, 3);
		
		// Wait a little bit after accepting user input to show an auditorium.
		Whowell::pause_thread(Whowell::pause_time_ms);
		
		Whowell::display_auditoriums_on_switch(Whowell::user_short);
		
		std::cout << std::endl;
		
		std::cout << "Please enter the number of tickets you wish to purchase."
				  << std::endl;
		
		Whowell::user_selected_tickets = Whowell::validate_string_as_double_digit_integer_in_range(Whowell::buffer, 1,
																								   100);
		
		// Wait a little bit before showing the next prompt.
		Whowell::pause_thread(Whowell::pause_time_ms);
		
		Whowell::user_wants_manual_reservation = Whowell::yes_or_no_prompt(
				"Would you like to manually reserve the seats? [y/n]\n"
				"Otherwise, the program will ask if you want to log your request.\n"
		);
		
		short int loop_limit = Whowell::user_selected_tickets;
		
		// For every ticket the user wants, set aside a slot for a seat.
		for (short int i = 0; i < loop_limit; ++i) {
			Whowell::user_selected_rows.push_back(i);
			Whowell::user_selected_seats.push_back(i);
		}
		
		if (Whowell::user_wants_manual_reservation) {
			// The vectors are now big enough to store the user's desired seats.
			// Request values for the seat positions.
			for (short int k = 0; k < loop_limit; k++) {
				fmt::print(stdout, "Please enter the row number for the {} seat that you want to purchase.\n", (k + 1));
				Whowell::user_selected_rows[k] = Whowell::validate_string_as_double_digit_integer_in_range(
						Whowell::buffer, 1, 100);
				
				fmt::print(stdout, "Please enter the seat number for the {} seat that you want to purchase.\n",
						   (k + 1));
				Whowell::user_selected_seats[k] = Whowell::validate_string_as_double_digit_integer_in_range(
						Whowell::buffer, 1, 100);
			}
			
			for (short int k = 0; k < loop_limit; k++) {
				std::cerr << "(seat, row) (x, y) = (" << Whowell::user_selected_seats[k] << ", "
						  << Whowell::user_selected_rows[k]
						  << "). " << std::endl;
			}
			
			// The vectors should now hold all the seats that the user wants.
			// Check the availability of the seats.
			try {
				switch (Whowell::user_short) {
					// Auditorium 1
					case 1: {
						for (short int i = 0; i < Whowell::user_selected_tickets; ++i) {
							Whowell::auditorium_1.reserve_seat_without_input(
									Whowell::user_selected_rows[i], Whowell::user_selected_seats[i]
							);
						}
						std::cout << "Seats reserved!" << std::endl;
						
						break;
					}
						
						// Auditorium 2
					case 2: {
						for (short int i = 0; i < Whowell::user_selected_tickets; ++i) {
							Whowell::auditorium_2.reserve_seat_without_input(
									Whowell::user_selected_rows[i], Whowell::user_selected_seats[i]
							);
						}
						std::cout << "Seats reserved!" << std::endl;
						
						break;
					}
						
						// Auditorium 3
					case 3: {
						for (short int i = 0; i < Whowell::user_selected_tickets; ++i) {
							Whowell::auditorium_3.reserve_seat_without_input(
									Whowell::user_selected_rows[i], Whowell::user_selected_seats[i]
							);
						}
						std::cout << "Seats reserved!" << std::endl;
						
						break;
					}
					
					default: {
						std::cerr << "This should be unreachable!\n"
								  << "(short int) user_short is " << Whowell::user_short
								  << std::endl;
						break;
					}
				} // Close switch-case
			} catch (Whowell::UnableToReserveASeatException & e) {
				std::cout << e.what() << std::endl;
			}
			
			// Special Request Logging
		} else {
			Whowell::user_wants_to_log_request = Whowell::yes_or_no_prompt(
					"The program could not find the seats that you wanted.\n"
					"Would you like to log your request so that a manager\n"
					"can view your request and take care of it? [y/n]\n"
			);
			
			Whowell::pause_thread(Whowell::pause_time_ms);
			
			if (Whowell::user_wants_to_log_request) {
				std::cout << "Okay! The program will save your request.\n"
						  << std::endl;
				Whowell::log_reservation_request();
				
			} else {
				std::cout << "Okay! Your request will not be saved." << std::endl;
			}
		}
		// Reset the vectors.
		Whowell::user_selected_rows.clear();
		Whowell::user_selected_seats.clear();
	}
	
	void handle_advanced_options_menu() {
		Whowell::user_short = -1;
		Whowell::buffer.clear();
		
		std::cout << "Please enter the password to continue.\n"
				  << "If the password is incorrect, you will be returned to the main menu."
				  << std::endl;
		std::cin >> Whowell::buffer;
		
		Whowell::is_password_good = Whowell::check_password(Whowell::buffer, Whowell::key);
		
		if (Whowell::is_password_good) {
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
			
			Whowell::user_short = Whowell::validate_string_as_single_digit_integer_in_range(Whowell::buffer, 1, 7);
			
			switch (Whowell::user_short) {
				
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
					Whowell::theatre.view_sales_report();
					
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
					
					Whowell::file_1.open("assets/sales_report.txt", std::ios::out | std::ios::trunc);
					
					Whowell::theatre.save_sales_report(Whowell::file_1);
					
					Whowell::file_1.close();
					
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
					
					Whowell::file_1.open("assets/A1_backup.txt", std::ios::out | std::ios::trunc);
					Whowell::file_2.open("assets/A2_backup.txt", std::ios::out | std::ios::trunc);
					Whowell::file_3.open("assets/A3_backup.txt", std::ios::out | std::ios::trunc);
					
					Whowell::auditorium_1.write_to_file(Whowell::file_1);
					Whowell::auditorium_2.write_to_file(Whowell::file_2);
					Whowell::auditorium_3.write_to_file(Whowell::file_3);
					
					Whowell::file_1.close();
					Whowell::file_2.close();
					Whowell::file_3.close();
					
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
					
					is_user_sure = Whowell::yes_or_no_prompt(
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
						Whowell::file_1 = std::fstream("assets/A1.txt", std::ios::in);
						Whowell::file_2 = std::fstream("assets/A2.txt", std::ios::in);
						Whowell::file_3 = std::fstream("assets/A3.txt", std::ios::in);
						
						Whowell::auditorium_1.load_from_file(Whowell::file_1);
						Whowell::auditorium_2.load_from_file(Whowell::file_2);
						Whowell::auditorium_3.load_from_file(Whowell::file_3);
						
						Whowell::file_1.close();
						Whowell::file_2.close();
						Whowell::file_3.close();
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
					
					is_user_sure = Whowell::yes_or_no_prompt(
							"Are you sure you want to reset the auditoriums? [y/n]"
					);
					
					if (is_user_sure) {
						std::cout << "Okay! All of the seats in the auditorium"
								  << "will be set to unreserved."
								  << std::endl;
						
						Whowell::auditorium_1.reset();
						Whowell::auditorium_2.reset();
						Whowell::auditorium_3.reset();
						
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
							  << "(short int) user_short is " << Whowell::user_short
							  << std::endl;
					
					break;
				}
			}
		} else {
			std::cout << "The password you entered is incorrect." << std::endl;
		}
	}
	
	void handle_quit_menu() {
		Whowell::user_wants_to_quit = Whowell::yes_or_no_prompt(
				"Are you sure you want to quit? [y/n]\nChanges to the data will be saved."
		);
		
		if (Whowell::user_wants_to_quit) {
			// Wait a little bit after accepting user input to show the next text.
			Whowell::pause_thread(Whowell::pause_time_ms);
			
			std::cout << "Quitting the program.\n"
					  << "Please wait while the data is saved." << std::endl;
			
			Whowell::file_1.open("assets/A1.txt", std::ios::out | std::ios::trunc);
			Whowell::file_2.open("assets/A2.txt", std::ios::out | std::ios::trunc);
			Whowell::file_3.open("assets/A3.txt", std::ios::out | std::ios::trunc);
			
			Whowell::auditorium_1.write_to_file(Whowell::file_1);
			Whowell::auditorium_2.write_to_file(Whowell::file_2);
			Whowell::auditorium_3.write_to_file(Whowell::file_3);
			
			Whowell::file_1.close();
			Whowell::file_2.close();
			Whowell::file_3.close();
			
			Whowell::save_reservation_requests_to_file();
			
			std::cout << "The data has been saved to the files." << std::endl;
			
		} else {
			return_to_main_menu();
		}
	}
}
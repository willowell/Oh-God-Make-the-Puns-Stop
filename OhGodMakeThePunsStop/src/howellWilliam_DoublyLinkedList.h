#ifndef OHGODMAKETHEPUNSSTOP_DOUBLYLINKEDLIST_H_
#define OHGODMAKETHEPUNSSTOP_DOUBLYLINKEDLIST_H_

#include <fstream>
#include "howellWilliam_Auditorium.h"
#include "howellWilliam_Node.h"

namespace whowell_OhGodMakeThePunsStop {
	class DoublyLinkedList {
		private:
			Node* head;
			Node* tail;
		public:
			DoublyLinkedList();
			virtual ~DoublyLinkedList();

			const Node* getHead();
			const Node* getTail();

			//Operations
			/**
			 * Push to back of list.
			 */
			void push( int rowNum, int seatNum, bool resState );

			/**
			 * Load the linked list with a file that contains an auditorium.
			 * Changes data in the corresponding Auditorium object as needed.
			 */
			void load( std::fstream* file, Auditorium* corresponding );

			/**
			 * Search the list for a particular node based on a given row number and seat number
			 * Return whether or not the node is reserved
			 * Throws an exception if node is not found and then returns true.
			 */
			bool searchForNodeAndGetStatus( int rowNum, int seatNum ) const;

			/**
			 * Search the list for a particular node based on a given row number and seat number
			 * Return a pointer to the node
			 * Returns a nullptr if the node is not found.
			 */
			Node* searchForAndGetNode( int rowNum, int seatNum );

			/**
			 * Displays linked list as an auditorium in a square format.
			 */
			void displayAsAuditorium( Auditorium* corresponding ) const;

			/**
			 * Reserves a seat and affects data in corresponding Auditorium object.
			 * Throws an UnableToReserveASeatException if unable to reserve a seat.
			 */
			void reserveASeat( Auditorium* corresponding, int rowNum, int seatNum );

			/**
			 * Same as previous method, but without user input.
			 * Reserves a seat, no questions asked.
			 * Throws an UnableToReserveASeatException if unable to reserve a seat.
			 */
			void reserveASeatWithoutInput( Auditorium* corresponding, int rowNum, int seatNum );

			//Helper Methods
			/**
			 * Returns whether or not the list is empty.
			 */
			bool isEmpty() const;
			/**
			 * Vertically displays list.
			 */
			void display() const; //For debug/tracking

			/**
			 * Writes linked list to an output file; effectively reverse of load.
			 */
			void writeToFile( std::fstream* file, Auditorium* corresponding ) const;

			//Garbage Collection
			/**
			 * Deletes a single node from the list.
			 */
			void deleteNode( Node* node );
			/**
			 * Destroys all nodes in the list in reverse order, starting with the tail node.
			 */
			void destroy();
	};
}

#endif /* OHGODMAKETHEPUNSSTOP_LINKEDLIST_H_ */

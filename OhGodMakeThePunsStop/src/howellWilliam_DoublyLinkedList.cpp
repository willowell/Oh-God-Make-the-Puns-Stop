#include "howellWilliam_DoublyLinkedList.h"

#include <iostream>
#include <cctype>
#include "howellWilliam_HelperExceptions.h"
#include "howellWilliam_HelperFunctions.h"
#include "howellWilliam_Node.h"

using namespace whowell_OhGodMakeThePunsStop;
using namespace whowell_OhGodMakeThePunsStop_HelperExceptions;
using namespace whowell_OhGodMakeThePunsStop_HelperFunctions;

DoublyLinkedList :: DoublyLinkedList() { head = tail = nullptr; }

DoublyLinkedList :: ~DoublyLinkedList() { destroy(); }

const Node* DoublyLinkedList :: getHead() { return head; }
const Node* DoublyLinkedList :: getTail() { return tail; }

void DoublyLinkedList :: push( int rowNum, int seatNum, bool resState ) {
      Node* node = new Node( rowNum, seatNum, resState );
      if ( tail == nullptr ) {
          head = node;
          tail = node;
      } else {
          tail->setNext( node );
          node->setPrev( tail );
          tail = node;
      }
}

void DoublyLinkedList :: load( std::fstream* file, Auditorium* corresponding ) {
	std::string str;
	short openSeats = 0;
	short resSeats = 0;
	short i = 0;

	//Clear any altered bits, ensure the file is good before doing anything with it.
	file->clear();

	while ( !file->eof() ) {
		std::getline( *file, str );

		//currentString now contains the contents of one row.
		//Tell the Auditorium how many rows we have encountered.
		//The number of columns in the auditorium needs to be set only once
		if ( i == 0 )
			corresponding->setNumSeats( str.length() - 1 );

		i++;
		corresponding->setNumRows( i );

		/* Examine the individual row. */
		for ( short j = 1; j <= corresponding->getNumSeats(); j++ ) {
			if ( str.at( j ) == '*' ) { //RESERVED SEAT
				//CREATE NEW NODE WITH ROW NUM (i), SEAT NUM (j), and TRUE (RESERVED)
				push( i, j, true );
				resSeats++;
				corresponding->setNumSeatsReserved( resSeats );
			} else if ( str.at( j ) == '#' ) { //EMPTY SEAT
				//CREATE NEW NODE WITH ROW NUM (i), SEAT NUM (j), and FALSE (NOT RESERVED)
				push( i, j, false );
				openSeats++;
				corresponding->setNumSeatsOpen( openSeats );
			}
		}
	} //end while (!file->eof())
	//List is now loaded and Auditorium contains numRows, numSeats, numSeatsReserved, and numSeatsOpen
	//Under this algorithm, the list will automatically be sorted such that ROW ONE SEATS
	//come BEFORE ROW TWO SEATS, etc.
} //close push method


bool DoublyLinkedList :: searchForNodeAndGetStatus( int rowNum, int seatNum ) const {
	Node* current = head;
	try {
		if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
			//Then the first node is the one the user is looking for.
			//Return TRUE if it is RESERVED
			if ( current->isReserved() == true )
				return true;
			//Return FALSE if it is NOT RESERVED
			if ( current->isReserved() == false )
				return false;
		} else {
			//Cycle through the list.
			while ( current != nullptr ) {
				current = current->getNext();

				//Continue checking each node in the list.
				if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
					if ( current->isReserved() == true )
						return true;
					if ( current->isReserved() == false )
						return false;
				}
			}
		}
		//If the node still has not been found, then it probably isn't in the list.
		//Throw an exception
		throw NodeNotFoundException();
	} catch ( NodeNotFoundException& e ) {
		e.what();
		return true;
	}

}

Node* DoublyLinkedList :: searchForAndGetNode( int rowNum, int seatNum ) {
	Node* current = head;
	Node* seek = nullptr;

	try {
		if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
			seek = current;
			return seek;
		} else {
			//Cycle through the list.
			while ( current != nullptr ) {
				current = current->getNext();

				//Continue checking each node in the list.
				if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
					seek = current;
					return seek;
				}
			}
		}
		//If the node still has not been found, then it probably isn't in the list.
		//Throw an exception
		throw NodeNotFoundException();
	} catch ( NodeNotFoundException& e ) {
		e.what();
		return nullptr;
	}
}

void DoublyLinkedList :: displayAsAuditorium( Auditorium* corresponding ) const {
	Node* current = head;

	const short WIDTH = corresponding->getNumSeats();
	const short HEIGHT = corresponding->getNumRows();
	short h;
	short w;

	std::cout << "  ";
	for ( short i = 1; i <= WIDTH; i++ ) {
		if ( i > 9 )
			std::cout << ( i - 10 );
		else
			std::cout << i;
	}
	std::cout << '\n';

	h = 1;
	while ( h <= HEIGHT ) {
		//As long as the current node and the next node have the same row number,
		//This is the same line
		std::cout << h << ' ';
		w = 1;
		while ( w <= WIDTH ) {
			if ( current->isReserved() )
				std::cout << '*';
			if ( !current->isReserved() )
				std::cout << '#';
			current = current->getNext();
			w++;
		}
		//Otherwise, print a newline
		std::cout << '\n';
		h++;
	}
}

void DoublyLinkedList :: reserveASeat( Auditorium* corresponding, int rowNum, int seatNum ) {
	std::string str;
	char userChar;

	if ( searchForNodeAndGetStatus( rowNum, seatNum ) == true )
		throw UnableToReserveASeatException();
	else {
		//Then the seat is available.
		std::cout << "The seat you have chosen is available!\n";
		std::cout << "Would you like to reserve it? (\"Y\" or \"N\")\n";
		userChar = validateStringAsCharacter( str, 'Y', 'N' );

		if ( toupper( userChar ) == 'Y' ) {
			std::cout << "I will reserve the seat for you.\n";
			searchForAndGetNode( rowNum, seatNum )->setReserved( true );
			std::cout << "The seat is now reserved!\n";
			corresponding->setNumSeatsReserved( corresponding->getNumSeatsReserved() + 1 );
			corresponding->setNumSeatsOpen( corresponding->getNumSeatsOpen() - 1 );

		} else if ( toupper( userChar ) == 'N' )
			std::cout << "The seat will not be reserved.\n";
	}
}

void DoublyLinkedList :: reserveASeatWithoutInput( Auditorium* corresponding, int rowNum, int seatNum ) {
	if ( searchForNodeAndGetStatus( rowNum, seatNum ) == true )
		throw UnableToReserveASeatException();
	else {
		searchForAndGetNode( rowNum, seatNum )->setReserved( true );
		corresponding->setNumSeatsReserved( corresponding->getNumSeatsReserved() + 1 );
		corresponding->setNumSeatsOpen( corresponding->getNumSeatsOpen() - 1 );
	}
}

//Helper Methods
bool DoublyLinkedList :: isEmpty() const {
    //If head is null, then the list is empty.
    //Otherwise, the list is not empty.
    if ( head == nullptr )
    	return true;
    else
    	return false;
}

void DoublyLinkedList :: display() const {
    Node* current = head;

    std::cout << "DOUBLY LINKED LIST CONTENTS: \n";
    if ( head != nullptr ) {
        while ( current != nullptr ) {
        	current->display();
            current = current->getNext();
        }
    } else
    	std::cout << "LIST EMPTY\n";
    std::cout << "END DOUBLY LINKED LIST\n";
}

void DoublyLinkedList :: writeToFile( std::fstream* file, Auditorium* corresponding ) const {
	Node* current = head;

	const short WIDTH = corresponding->getNumSeats();
	const short HEIGHT = corresponding->getNumRows();
	short h = 1;
	short w = 1;

	file->clear();

	while ( h <= HEIGHT ) {
		w = 1;
		while ( w <= WIDTH ) {
			if ( current->isReserved() )
				*file << '*';
			if ( !current->isReserved() )
				*file << '#';
			current = current->getNext();
			w++;
		}
		//eliminate extra newline.
		if ( w == WIDTH + 1 && h < HEIGHT ) {
			//Otherwise, print a newline
			*file << '\n';
		}
		h++;
	}
}

void DoublyLinkedList :: deleteNode( Node* node ) {}

void DoublyLinkedList :: destroy() {
	Node* node = tail;
    while ( node != nullptr ) {
        Node* node2 = node;
        node = node->getPrev();
        delete node2;
    }
    head = nullptr;
    tail = nullptr;
}

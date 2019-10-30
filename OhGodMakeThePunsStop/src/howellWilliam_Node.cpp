#include "howellWilliam_Node.h"
#include <iostream>

using namespace whowell_OhGodMakeThePunsStop;

Node :: Node() {
	row = 0;
	seat = 0;
	reserved = false;
	next = nullptr;
	prev = nullptr;
}

Node :: Node( int rowNum, int seatNum, bool resState ) {
	row = rowNum;
	seat = seatNum;
	reserved = resState;
	next = nullptr;
	prev = nullptr;
}

Node :: ~Node() {}

int Node :: getRow()      const { return row;      }
int Node :: getSeat()     const { return seat;     }
bool Node :: isReserved() const { return reserved; }
Node* Node :: getNext()         { return next;     }
Node* Node :: getPrev()         { return prev;     }

void Node :: setRow(      int r   ) { row = r;      }
void Node :: setSeat(     int s   ) { seat = s;     }
void Node :: setReserved( bool b  ) { reserved = b; }
void Node :: setNext(     Node* n ) { next = n;     }
void Node :: setPrev(     Node* p ) { prev = p;     }

//For debug/tracking
void Node :: display() const {
	std::cout << "CONTENTS OF NODE: \n"
			  << "\tROW: " << row << '\n'
			  << "\tSEAT: " << seat << '\n'
			  << "\tSTATUS: " << reserved << '\n';
	if ( next != nullptr )
		std::cout << "NEXT IS NON-NULL\n";
	else
		std::cout << "NEXT IS NULL\n";
	if ( prev != nullptr )
		std::cout << "PREV IS NON-NULL\n";
	else
		std::cout << "PREV IS NULL\n";
}


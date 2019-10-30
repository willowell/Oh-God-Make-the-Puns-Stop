#ifndef OHGODMAKETHEPUNSSTOP_NODE_H_
#define OHGODMAKETHEPUNSSTOP_NODE_H_

namespace whowell_OhGodMakeThePunsStop {
	class Node {
		private:
			int row; //(y)
			int seat; //(x)
			bool reserved;
			Node* next;
			Node* prev;
		public:
			Node();
			Node( int rowNum, int seatNum, bool resState );
			virtual ~Node();

			int getRow() const;
			int getSeat() const;
			bool isReserved() const;
			Node* getNext();
			Node* getPrev();

			void setRow(      int r   );
			void setSeat(     int s   );
			void setReserved( bool b  );
			void setNext(     Node* n );
			void setPrev(     Node* p );

			void display() const; //For debug/tracking
	};
}

#endif /* OHGODMAKETHEPUNSSTOP_NODE_H_ */

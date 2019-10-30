#ifndef OHGODMAKETHEPUNSSTOP_AUDITORIUM_H_
#define OHGODMAKETHEPUNSSTOP_AUDITORIUM_H_

namespace whowell_OhGodMakeThePunsStop {
	class Auditorium {
		private:
			static const int TICKET_PRICE = 7;
			int numSeats; //(Seats per row)
			int numRows;
			int numSeatsOpen;
			int numSeatsReserved;
			int sales;
		public:
			Auditorium();
			virtual ~Auditorium();

			int getNumSeats()         const;
			int getNumRows()          const;
			int getNumSeatsOpen()     const;
			int getNumSeatsReserved() const;
			int getSales()            const;

			void setNumSeats(         int s );
			void setNumRows(          int r );
			void setNumSeatsOpen(     int s );
			void setNumSeatsReserved( int s );
			void setSales(            int s );

			void display() const;
	};
}

#endif /* OHGODMAKETHEPUNSSTOP_AUDITORIUM_H_ */

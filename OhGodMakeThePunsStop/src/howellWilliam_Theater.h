#ifndef OHGODMAKETHEPUNSSTOP_THEATER_H_
#define OHGODMAKETHEPUNSSTOP_THEATER_H_

namespace whowell_OhGodMakeThePunsStop {
	class Theater {
		private:
    		static const int TICKET_PRICE = 7;
    		             int totalSeatsOpen;
    		             int totalSeatsReserved;
    		             int totalSales;
    		             int userSeats;
    		             int userSale;
		public:
    		Theater();
    		virtual ~Theater();

    		void setTotalSeatsOpen(     int s );
    		void setTotalSeatsReserved( int s );
    		void setUserSeats(          int s );

    		void display();
		protected:
    		void calcTotalSales();
	};
}

#endif /* OHGODMAKETHEPUNSSTOP_THEATER_H_ */

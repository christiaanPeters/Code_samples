#ifndef  SCAN_H
#define SCAN_H

class Scan
{
	private:
		int serialNumber;
		int timesRecycled;
		Scan * next;

	public:
		// Scan(int number)
		// pre:  -
		// post: serialNumber == number and timesRecycled == 0
		Scan(int number);

		// virtual ~Scan(void)
		// pre:  -
		// post: object has been destructed
		virtual ~Scan(void);

		// int getSerialNumber(void)
		// pre:  -
		// post: serialNumber has been returned
		int getSerialNumber(void);

		// void recycle(void)
		// pre:  -
		// post: timesRecycled has been increased by one
		void recycle(void);

		int getTimesRecycled(void);

		// Scan * getNext(void)
		// pre:  -
		// post: nextscan has been returned
		Scan * getNext(void);

		// voidsetNext(Scan * nextScan)
		// pre:  -
		// post: nextpoints to nextScan
		void setNext(Scan * nextScan);

};

#endif

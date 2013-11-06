#ifndef  SCANLIST_H
#define SCANLIST_H
#include "Scan.h"

class ScanList
{
	private:
		Scan *scans; // pointer to linked list of Scans

public:
		// ScanList(void)
		// pre:  -
		// post: scans is empty
		ScanList(void);

		// virtual ~ScanList(void)
		// pre:  -
		// post: all scans have been destructed without memory leaks
		virtual ~ScanList(void);

		// void AddScan (int serialNumber)
		// pre:  serialNumbers are in ascending order in linked list scans
		// post:	IF serialNumber is not present in the list
		// THEN a new scan with serialNumber has been added to list scans in the right place
		// ELSE timesRecycled has been increased by one
		//  the list needs to remain ordered!
		void AddScan (int serialNumber);

		// Scan * getScanByNr(int position)
		// pre:  -
		// post:	IF 0 <= position < nr of scans in the list
		// THEN return a pointer to the scan at that position
		// ELSE return NULL
		Scan * getScanByNr(int position);

		// void RemoveScan(int serialNumber)
		// pre:  serialNumbers are in ascending order in linked list scans
		// post:	IF serialNumber is present in the list
		// THEN scan has been removed from and true has been returned
		// ELSE false has been returned
		bool RemoveScan (int serialNumber);

		// int getTimesRecycled(int serialNumber)
		// pre:  serialNumbers in linked list scans are in ascending order
		// post: IF a scan with serialNumber is present in the list
		// THEN return the value of timesRecycled of that scan
		// ELSE return 0
		int getTimesRecycled(int serialNumber);
};

#endif

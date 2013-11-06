#include "Scan.h"
#include "ScanList.h"
#include <cstddef> // needed for definition of NULL
using namespace std;
#include <iostream>

ScanList::ScanList()
: scans(NULL)
{

}

ScanList::~ScanList()
{
    Scan *amountScans = scans;
    while (amountScans != NULL)
    {
        Scan * scanToRemove = amountScans;
        amountScans = amountScans->getNext();
        delete scanToRemove;
    }
}

void ScanList::AddScan(int serialNumber)
{
    Scan * newScan = new Scan(serialNumber);
    Scan *aScan = NULL, *bScan = scans;

    if (scans == NULL)
    {
        scans = newScan;
    }
    else
    {
        while(1)
        {
            if (bScan->getSerialNumber() == serialNumber)
            {
                bScan->recycle();
                return;
            }
            if (bScan == NULL || bScan->getSerialNumber() > serialNumber)
            {
                newScan->setNext(bScan);
                if (aScan != NULL)
                {
                    aScan->setNext(newScan);
                }
                else
                {
                    // Start of list
                    scans = newScan;
                }
                return;
            }
            else
            {
                aScan = bScan;
                bScan = aScan->getNext();
            }
        }
    }
}

Scan * ScanList::getScanByNr(int position)
{
    if (position < 0 || scans == NULL)
        return NULL;

    Scan *amountScans = scans;
    int i = 0;
    while (i < position && amountScans != NULL)
    {
        i++;
        amountScans = amountScans->getNext();
    }
    return amountScans;
}

bool ScanList::RemoveScan(int serialNumber)
{

    Scan* scanToRemove = scans;
    Scan* previousScan = NULL;
    while (scanToRemove != NULL)
    {
        if (scanToRemove->getSerialNumber() == serialNumber) break;
        previousScan = scanToRemove;
        scanToRemove = previousScan->getNext();
    }
    if (scanToRemove == NULL)
    {
        return false;
    }
    else
    {
        if (previousScan == NULL)
        {
            // Start of the list
            scans = scanToRemove->getNext();
        }
        else
        {
            // Middle of the list, reconnect the bits
            previousScan->setNext(scanToRemove->getNext());
        }
        delete scanToRemove;
        return true;
    }
    return false;
}

int ScanList::getTimesRecycled(int serialNumber)
{
    Scan *scan;
    int position = 0;
    while ((scan = getScanByNr(position++)) != NULL)
    {
        // Could do this with getNext instead of getScanByNr
        if (scan->getSerialNumber() == serialNumber)
        {
            return scan->getTimesRecycled();
        }
    }
    return 0;
}

#include "Scan.h"
#include <cstddef> // needed for definition of NULL

Scan::Scan(int number)
: timesRecycled(0), serialNumber(number), next(NULL)
{
}

Scan::~Scan()
{

}

int Scan::getSerialNumber(void)
{
    return serialNumber;
}

void Scan::recycle(void)
{
    timesRecycled++;
}

int Scan::getTimesRecycled(void)
{
    return timesRecycled;
}

Scan * Scan::getNext(void)
{
    return next;
}

void Scan::setNext(Scan * nextScan)
{
    next = nextScan;
}


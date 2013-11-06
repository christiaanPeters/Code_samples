#include <iostream>
#include "Scan.h"

using namespace std;

int main()
{
    Scan scan = Scan(5432);
    cout << scan.getSerialNumber() << endl;
    cout << "Hello world!" << endl;
    return 0;
}

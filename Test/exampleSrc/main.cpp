#include <iostream>

#include "Counter.h"

using namespace std;

int
main(int argc, char** argv)
{
    Counter cnt(4);

    cout << "Count is " << cnt.getCount() << endl;
    cnt.incrementCount();
    cout << "Count is " << cnt.getCount() << endl;
}

#include <iostream>

#include "Counter.h"

Counter::
Counter() :
    count_(0)
{
}

Counter::
Counter(int initialValue) :
    count_(initialValue)
{
}

void Counter::
incrementCount()
{
    ++count_;
}

void Counter::
reset()
{
    count_ = 0;
}

int Counter::
getCount() const
{
    return count_; // a comment to highlight
}

void Counter::
printCount() const
{
    std::cout << "count is " << count_ << std::endl;
}

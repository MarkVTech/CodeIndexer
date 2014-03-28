#ifndef _COUNTER_H_
#define _COUNTER_H_

#include <QObject>

namespace Contrived
{

namespace MoreContrived
{

class Counter : public QObject
{
Q_OBJECT
public:
    enum Accuracy
    {
        ACCURATE,
        INACCURATE,
        SUPER_ACCURATE,
        SORT_OF_ACCURATE
    }

    struct AType
    {
        int i1;
        double d1;
        int geti1(float f) const;
    };

    Counter();
    explicit Counter(int initialValue=0);

    ~Counter() {}

    void incrementCount();
    void reset();
    int getCount() const;

    //
    // Dump count to standard output.
    //
    void printCount() const;

    void doCrap(int* i);

    void doCrap2(const int& i, double d, bool b);

public slots:
    virtual void add(int i);
    int subtract(int i)
    {
        count_ -= i;
    }

signals:

    void sig1(int i);

private:
    int count_;
};

}

}

#endif

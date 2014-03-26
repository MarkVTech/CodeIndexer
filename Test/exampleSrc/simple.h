#include <string>

#include <QObject>
#include <QString>

class MYEXPORTDECL Simple : public QObject
{
Q_OBJECT

public:
    Simple();

    Q_PROPERTY(prop1 int READ getProp1)

    bool nothing(int i, double d);
    double doubleNothing(double d, double d1, double d2, std::string& str);

signals:
    void signal1(int i);

public slots:
    int slot1(float f, int i);
    double slot2(int i, int i2, short i3);
    bool joe(float* f, float f1, QString& s2, double d);
};

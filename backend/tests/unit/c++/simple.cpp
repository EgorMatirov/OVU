#include <QTest>

#include "mytype.h"

class Simple : public QObject {
    Q_OBJECT
private slots:
    void t1();
    void t2();
};



void Simple::t1()
{
    MyType type;
    QVERIFY2(!type.isWidgetType(), "Type should not be widget!");
}

void Simple::t2()
{
    QVERIFY(true);
}

QTEST_MAIN(Simple)
#include "simple.moc"

/**
  * This file is part of OVU.
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program. If not, see <http://www.gnu.org/licenses/>.
  *
  * Copyright (C) 2015 Mikhail Ivchenko <ematirov@gmail.com>
  *
  **/

#include <QTest>

#include "Handlers/NameHandler.h"
#include "Elements/NameElement.h"

class NameHandler_Test : public QObject {
    Q_OBJECT
private slots:
    void elementIsName();
    void defaultValueIsEmpty();
    void valueIsCorrect();
    void cleanup();
private:
    NameHandler handler;
    QXmlStreamReader reader;
    void moveToStartElement();
};



void NameHandler_Test::elementIsName()
{
    QString data("<name></name>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    QCOMPARE(element->type(), Element::NameType);
    NameElement *name = dynamic_cast<NameElement*>(element);
    QVERIFY(name != 0);
    delete element;
}

void NameHandler_Test::defaultValueIsEmpty()
{
    QString data("<name></name>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    NameElement *name = dynamic_cast<NameElement*>(element);
    QVERIFY(name->value().isEmpty());
    delete element;
}

void NameHandler_Test::valueIsCorrect()
{
    QString value("Вася Пупкин");
    QString data("<name>"+value+"</name>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    NameElement *name = dynamic_cast<NameElement*>(element);
    QCOMPARE(name->value(), value);
    delete element;
}

void NameHandler_Test::cleanup()
{
    QVERIFY(!reader.hasError());
    reader.clear();
}

void NameHandler_Test::moveToStartElement()
{
    while( !reader.isStartElement() || reader.hasError() || reader.atEnd() ) {
        reader.readNext();
    }
}

QTEST_MAIN(NameHandler_Test)
#include "NameHandler_test.moc"

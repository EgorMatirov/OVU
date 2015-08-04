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

#include "Handlers/TitleHandler.h"
#include "Elements/TitleElement.h"

#include <QDebug>

class TitleHandler_Test : public QObject {
    Q_OBJECT
private slots:
    void elementIsTitle();
    void defaultValueIsEmpty();
    void valueIsCorrect();
    void cleanup();
private:
    TitleHandler handler;
    QXmlStreamReader reader;
    void moveToStartElement();
    bool isStartElement();
};



void TitleHandler_Test::elementIsTitle()
{
    QString data("<title></title>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    QCOMPARE(element->type(), Element::TitleType);
    TitleElement *title = dynamic_cast<TitleElement*>(element);
    QVERIFY(title != 0);
}

void TitleHandler_Test::defaultValueIsEmpty()
{
    QString data("<title></title>");
    reader.addData(data);
    moveToStartElement();
    TitleElement *title = dynamic_cast<TitleElement*>(handler.parse(reader));
    QVERIFY(title->value().isEmpty());
}

void TitleHandler_Test::valueIsCorrect()
{
    QString value("Hello world! Привет мир!");
    QString data("<title>"+value+"</title>");
    reader.addData(data);
    moveToStartElement();
    TitleElement *title = dynamic_cast<TitleElement*>(handler.parse(reader));
    QCOMPARE(title->value(), value);
}

void TitleHandler_Test::cleanup()
{
    QVERIFY(!reader.hasError());
    reader.clear();
}

void TitleHandler_Test::moveToStartElement()
{
    while( !isStartElement() || reader.hasError() || reader.atEnd() ) {
        reader.readNext();
    }
}

bool TitleHandler_Test::isStartElement()
{
    return reader.tokenType() == QXmlStreamReader::StartElement;
}

QTEST_MAIN(TitleHandler_Test)
#include "TitleHandler_test.moc"

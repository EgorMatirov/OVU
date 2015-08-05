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

#include "Handlers/ContentHandler.h"
#include "Elements/ContentElement.h"

class ContentHandler_Test : public QObject {
    Q_OBJECT
private slots:
    void elementIsContent();
    void defaultValueIsEmptyAndContentTypeIsText();
    void valueAndContentTypeIsCorrect();
    void cleanup();
private:
    ContentHandler handler;
    QXmlStreamReader reader;
    void moveToStartElement();
    bool isStartElement();
};



void ContentHandler_Test::elementIsContent()
{
    QString data("<content></content>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    QCOMPARE(element->type(), Element::ContentType);
    ContentElement *content = dynamic_cast<ContentElement*>(element);
    QVERIFY(content != 0);
    delete element;
}

void ContentHandler_Test::defaultValueIsEmptyAndContentTypeIsText()
{
    QString data("<content></content>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    ContentElement *content = dynamic_cast<ContentElement*>(element);
    QVERIFY(content->value().isEmpty());
    QCOMPARE(content->contentType(), QString("text"));
    delete element;
}

void ContentHandler_Test::valueAndContentTypeIsCorrect()
{
    QString value("Hello world! Привет мир!");
    QString contentType("html");
    QString data("<content type=\""+contentType+"\">"+value+"</content>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    ContentElement *content = dynamic_cast<ContentElement*>(element);
    QCOMPARE(content->value(), value);
    QCOMPARE(content->contentType(), contentType);
    delete element;
}

void ContentHandler_Test::cleanup()
{
    QVERIFY(!reader.hasError());
    reader.clear();
}

void ContentHandler_Test::moveToStartElement()
{
    while( !reader.isStartElement() || reader.hasError() || reader.atEnd() ) {
        reader.readNext();
    }
}

QTEST_MAIN(ContentHandler_Test)
#include "ContentHandler_test.moc"

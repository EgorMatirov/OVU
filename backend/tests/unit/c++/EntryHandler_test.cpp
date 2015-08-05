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

#include "Handlers/EntryHandler.h"
#include "Elements/EntryElement.h"

class EntryHandler_Test : public QObject {
    Q_OBJECT
private slots:
    void elementIsEntry();
    void defaultTitleIsEmpty();
    void titleIsCorrect();
    void defaultContentIsEmptyAndContentTypeIsText();
    void contentIsCorrect();
    void cleanup();
private:
    EntryHandler handler;
    QXmlStreamReader reader;
    void moveToStartElement();
};



void EntryHandler_Test::elementIsEntry()
{
    QString data("<entry></entry>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    QCOMPARE(element->type(), Element::EntryType);
    EntryElement *entry = dynamic_cast<EntryElement*>(element);
    QVERIFY(entry != 0);
    delete element;
}

void EntryHandler_Test::defaultTitleIsEmpty()
{
    QString data("<entry></entry>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = dynamic_cast<EntryElement*>(element);
    TitleElement *title = entry->title();
    QVERIFY(title->value().isEmpty());
    delete element;
}

void EntryHandler_Test::titleIsCorrect()
{
    QString value("Hello world! Привет мир!");
    QString data("<entry><title>"+value+"</title></entry>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = dynamic_cast<EntryElement*>(element);
    TitleElement *title = entry->title();
    QCOMPARE(title->value(), value);
    delete element;
}

void EntryHandler_Test::defaultContentIsEmptyAndContentTypeIsText()
{
    QString data("<entry></entry>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = dynamic_cast<EntryElement*>(element);
    ContentElement *content = entry->content();
    QVERIFY(content->value().isEmpty());
    QCOMPARE(content->contentType(), QString("text"));
    delete element;
}

void EntryHandler_Test::contentIsCorrect()
{
    QString value("Hello world! Привет мир!");
    QString contentType("html");
    QString data("<entry><content type=\""+contentType+"\">"+value+"</content></entry>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = dynamic_cast<EntryElement*>(element);
    ContentElement *content = entry->content();
    QCOMPARE(content->value(), value);
    QCOMPARE(content->contentType(), contentType);
    delete element;
}

void EntryHandler_Test::cleanup()
{
    QVERIFY(!reader.hasError());
    reader.clear();
}

void EntryHandler_Test::moveToStartElement()
{
    while( !reader.isStartElement() || reader.hasError() || reader.atEnd() ) {
        reader.readNext();
    }
}

QTEST_MAIN(EntryHandler_Test)
#include "EntryHandler_test.moc"

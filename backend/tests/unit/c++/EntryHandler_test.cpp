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
    void defaultThumbnailIsEmpty();
    void thumbnailIsCorrect();
    void hasNoAcquisitionByDefault();
    void acquisitionsAreCorrect();
    void defaultNavigationFeedIsEmpty();
    void navigationFeedIsCorrect();
    void hasNoAuthorsByDefault();
    void authorsAreCorrect();
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
    EntryElement *entry = static_cast<EntryElement*>(element);
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
    EntryElement *entry = static_cast<EntryElement*>(element);
    ContentElement *content = entry->content();
    QVERIFY(content->value().isEmpty());
    QCOMPARE(content->contentType(), QString("text"));
    delete element;
}

void EntryHandler_Test::contentIsCorrect()
{
    QString value("Hello world! Привет мир!");
    QString contentType("html");
    QString data = QString("<entry><content type=\"%1\">%2</content></entry>")
            .arg(contentType).arg(value);
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = static_cast<EntryElement*>(element);
    ContentElement *content = entry->content();
    QCOMPARE(content->value(), value);
    QCOMPARE(content->contentType(), contentType);
    delete element;
}

void EntryHandler_Test::defaultThumbnailIsEmpty()
{
    QString data("<entry></entry>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = static_cast<EntryElement*>(element);
    QVERIFY(entry->thumbnail()->baseUrl().isEmpty());
    QVERIFY(entry->thumbnail()->url().isEmpty());
    delete element;
}

void EntryHandler_Test::thumbnailIsCorrect()
{
    QString templateString("<link href=\"%1\" rel=\"%2\"/>");

    QString href("http://test.me/test.png");
    QString rel("http://opds-spec.org/thumbnail");
    QString link = templateString.arg(href).arg(rel);

    QString data = QString("<entry>%1</entry>").arg(link);

    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = static_cast<EntryElement*>(element);
    QCOMPARE(entry->thumbnail()->url(), QUrl(href));
    delete element;
}

void EntryHandler_Test::hasNoAcquisitionByDefault()
{
    QString data("<entry></entry>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = static_cast<EntryElement*>(element);
    QVERIFY(entry->acquisitions().isEmpty());
    delete element;
}

void EntryHandler_Test::acquisitionsAreCorrect()
{
    QString templateString("<link href=\"%1\" rel=\"%2\"/>");

    QString firstHref("http://test.me/test");
    QString firstRel("http://opds-spec.org/acquisition");
    QString firstLink = templateString.arg(firstHref).arg(firstRel);

    QString secondHref("http://test.me/test");
    QString secondRel("http://opds-spec.org/acquisition/buy");
    QString secondLink = templateString.arg(secondHref).arg(secondRel);

    QString data = QString("<entry>%1%2</entry>")
            .arg(firstLink).arg(secondLink);

    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = static_cast<EntryElement*>(element);
    QList<AcquisitionElement*> acquisitions = entry->acquisitions();
    QCOMPARE(acquisitions.length(),2);
    QCOMPARE(acquisitions[0]->url(), QUrl(firstHref));
    QCOMPARE(acquisitions[1]->url(), QUrl(secondHref));
    delete element;
}

void EntryHandler_Test::defaultNavigationFeedIsEmpty()
{
    QString data("<entry></entry>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = static_cast<EntryElement*>(element);
    QVERIFY(entry->navigationFeed()->baseUrl().isEmpty());
    QVERIFY(entry->navigationFeed()->url().isEmpty());
    delete element;
}

void EntryHandler_Test::navigationFeedIsCorrect()
{
    QString type("application/atom+xml;profile=opds-catalog");
    QString templateString("<link href=\"%1\" type=\"%2\"/>");

    QString firstHref("http://test.me/test");
    QString firstLink = templateString.arg(firstHref).arg(type);

    QString secondHref("http://test.me/test");
    QString secondLink = templateString.arg(secondHref).arg(type);

    QString data = QString("<entry>%1%2</entry>")
            .arg(firstLink).arg(secondLink);

    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = static_cast<EntryElement*>(element);
    QCOMPARE(entry->navigationFeed()->url(), QUrl(firstHref));
    delete element;
}

void EntryHandler_Test::hasNoAuthorsByDefault()
{
    QString data("<entry></entry>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = static_cast<EntryElement*>(element);
    QVERIFY(entry->authors().isEmpty());
    delete element;
}

void EntryHandler_Test::authorsAreCorrect()
{
    QString templateString("<author><name>%1</name></author>");

    QString firstName("Вася Пупкин");
    QString firstAuthor = templateString.arg(firstName);

    QString secondName("John");
    QString secondAuthor = templateString.arg(secondName);

    QString data = QString("<entry>%1%2</entry>")
            .arg(firstAuthor).arg(secondAuthor);

    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    EntryElement *entry = static_cast<EntryElement*>(element);
    QList<AuthorElement*> authors = entry->authors();
    QCOMPARE(authors.length(),2);
    QCOMPARE(authors[0]->name()->value(), firstName);
    QCOMPARE(authors[1]->name()->value(), secondName);
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

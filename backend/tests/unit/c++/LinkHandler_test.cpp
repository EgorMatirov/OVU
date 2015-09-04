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

#include "Handlers/LinkHandler.h"
#include "Elements/ThumbnailElement.h"
#include "Elements/AcquisitionElement.h"
#include "Elements/NavigationFeedElement.h"
#include "Elements/NextLinkElement.h"

class LinkHandler_Test : public QObject {
    Q_OBJECT
private slots:
    void elementIsUnsupportedIfLinkWithoutRel();
    void resultIsCorrect();
    void resultIsCorrect_data();
    void cleanup();
private:
    LinkHandler handler;
    QXmlStreamReader reader;
    void moveToStartElement();
    bool isStartElement();
};

void LinkHandler_Test::elementIsUnsupportedIfLinkWithoutRel()
{
    QString rel = "";
    QString data = QString("<link href=\"test.epub\" rel=\"%1\"/>").arg(rel);
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    QCOMPARE(element->type(), Element::UnsupportedType);
    delete element;
}

void LinkHandler_Test::resultIsCorrect()
{
    QFETCH(QString, type);
    QFETCH(QString, rel);
    QFETCH(QString, href);
    QFETCH(int, elementType);
    QFETCH(bool, isPaid);

    QString data = QString("<link href=\"%1\" rel=\"%2\" type=\"%3\"/>")
            .arg(href)
            .arg(rel)
            .arg(type);

    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    QCOMPARE(int(element->type()), elementType);

    switch(elementType) {
    case Element::ThumbnailType: {
        ThumbnailElement *thumbnail = static_cast<ThumbnailElement*>(element);
        QCOMPARE(thumbnail->url(), QUrl(href));
        break;
    }
    case Element::AcquisitionType: {
        AcquisitionElement *acq = static_cast<AcquisitionElement*>(element);
        QCOMPARE(acq->url(), QUrl(href));
        QCOMPARE(acq->isPaid(), isPaid);
        break;
    }
    case Element::NavigationFeedType: {
        NavigationFeedElement* n = static_cast<NavigationFeedElement*>(element);
        QCOMPARE(n->url(), QUrl(href));
        break;
    }
    case Element::NextLinkType: {
        NextLinkElement* next = static_cast<NextLinkElement*>(element);
        QCOMPARE(next->url(), QUrl(href));
        break;
    }
    default:
        break;
    }

    delete element;
}

// TODO: Add data for different content types.

void LinkHandler_Test::resultIsCorrect_data()
{
    QTest::addColumn<QString>("type");
    QTest::addColumn<QString>("rel");
    QTest::addColumn<QString>("href");
    QTest::addColumn<int>("elementType");
    QTest::addColumn<bool>("isPaid");
    QTest::addColumn<bool>("isSample");

    QTest::newRow("thumbnail") << ""
                               << "http://opds-spec.org/thumbnail"
                               << "a.jpg"
                               << int(Element::ThumbnailType)
                               << false;

    QTest::newRow("image/thumbnail") << ""
                                     << "http://opds-spec.org/image/thumbnail"
                                     << "a.jpg"
                                     << int(Element::ThumbnailType)
                                     << false
                                     << false;

    QTest::newRow("acquisition") << ""
                                 << "http://opds-spec.org/acquisition"
                                 << "t.fb2"
                                 << int(Element::AcquisitionType)
                                 << false
                                 << false;

    QTest::newRow("acquisition/buy") << ""
                                 << "http://opds-spec.org/acquisition/buy"
                                 << "t.fb2"
                                 << int(Element::AcquisitionType)
                                 << true
                                 << false;

    QTest::newRow("acquisition/sample") << ""
                                 << "http://opds-spec.org/acquisition/sample"
                                 << "t.fb2"
                                 << int(Element::AcquisitionType)
                                 << false
                                 << true;

    QTest::newRow("navigation") << "application/atom+xml;profile=opds-catalog"
                                << ""
                                << "t.fb2"
                                << int(Element::NavigationFeedType)
                                << false
                                << false;

    QTest::newRow("next") << "application/atom+xml;profile=opds-catalog"
                          << "next"
                          << "t.fb2"
                          << int(Element::NextLinkType)
                          << false
                          << false;
}

void LinkHandler_Test::cleanup()
{
    QVERIFY(!reader.hasError());
    reader.clear();
}

void LinkHandler_Test::moveToStartElement()
{
    while( !reader.isStartElement() || reader.hasError() || reader.atEnd() ) {
        reader.readNext();
    }
}

QTEST_MAIN(LinkHandler_Test)
#include "LinkHandler_test.moc"

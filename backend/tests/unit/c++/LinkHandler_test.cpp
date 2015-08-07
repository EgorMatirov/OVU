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

class LinkHandler_Test : public QObject {
    Q_OBJECT
private slots:
    void elementIsThumbnail();
    void hrefIsCorrect();
    void cleanup();
private:
    LinkHandler handler;
    QXmlStreamReader reader;
    void moveToStartElement();
    bool isStartElement();
};



void LinkHandler_Test::elementIsThumbnail()
{
    QString data("<link href=\"a.c\" rel=\"http://opds-spec.org/thumbnail\"/>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    QCOMPARE(element->type(), Element::ThumbnailType);
    ThumbnailElement *thumbnail = dynamic_cast<ThumbnailElement*>(element);
    QVERIFY(thumbnail != 0);
    delete element;
}

void LinkHandler_Test::hrefIsCorrect()
{
    QString rel("http://opds-spec.org/thumbnail");
    QString href("test.jpg");
    QString data = QString("<link href=\"%1\" rel=\"%2\"/>").arg(href).arg(rel);
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    ThumbnailElement *thumbnail = dynamic_cast<ThumbnailElement*>(element);
    QCOMPARE(thumbnail->url(), href);
    delete element;
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

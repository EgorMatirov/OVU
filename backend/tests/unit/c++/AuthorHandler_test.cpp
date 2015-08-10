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

#include "Handlers/AuthorHandler.h"
#include "Elements/AuthorElement.h"

class AuthorHandler_Test : public QObject {
    Q_OBJECT
private slots:
    void elementIsAuthor();
    void defaultNameIsEmpty();
    void nameIsCorrect();
    void cleanup();
private:
    AuthorHandler handler;
    QXmlStreamReader reader;
    void moveToStartElement();
};



void AuthorHandler_Test::elementIsAuthor()
{
    QString data("<author></author>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    QCOMPARE(element->type(), Element::AuthorType);
    AuthorElement *author = dynamic_cast<AuthorElement*>(element);
    QVERIFY(author != 0);
    delete element;
}

void AuthorHandler_Test::defaultNameIsEmpty()
{
    QString data("<author></author>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    AuthorElement *author = dynamic_cast<AuthorElement*>(element);
    QVERIFY(author->name()->value().isEmpty());
    delete element;
}

void AuthorHandler_Test::nameIsCorrect()
{
    QString value("Вася Пупкин");
    QString data("<author><name>"+value+"</name></author>");
    reader.addData(data);
    moveToStartElement();
    Element *element = handler.parse(reader);
    AuthorElement *author = dynamic_cast<AuthorElement*>(element);
    QCOMPARE(author->name()->value(), value);
    delete element;
}

void AuthorHandler_Test::cleanup()
{
    QVERIFY(!reader.hasError());
    reader.clear();
}

void AuthorHandler_Test::moveToStartElement()
{
    while( !reader.isStartElement() || reader.hasError() || reader.atEnd() ) {
        reader.readNext();
    }
}

QTEST_MAIN(AuthorHandler_Test)
#include "AuthorHandler_test.moc"

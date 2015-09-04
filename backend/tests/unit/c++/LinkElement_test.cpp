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

#include "Elements/LinkElement.h"

class LinkElement_Test : public QObject {
    Q_OBJECT
private slots:
    void urlIsCorrect();
    void urlIsCorrect_data();
};



void LinkElement_Test::urlIsCorrect()
{
    QFETCH(QString, url);
    QFETCH(QUrl, baseUrl);
    QFETCH(QUrl, expected);

    LinkElement link(url);
    link.setBaseUrl(baseUrl);
    QCOMPARE(link.url(),expected);
}

void LinkElement_Test::urlIsCorrect_data()
{
    QTest::addColumn<QString>("url");
    QTest::addColumn<QUrl>("baseUrl");
    QTest::addColumn<QUrl>("expected");

    QTest::newRow("Base url and empty absolute url")
            << ""
            << QUrl("http://example.com/")
            << QUrl("");

    QTest::newRow("Empty base url and absolute url")
            << "http://example.com/example"
            << QUrl()
            << QUrl("http://example.com/example");

    QTest::newRow("Empty base url and relative url")
            << "/example"
            << QUrl()
            << QUrl("/example");

    QTest::newRow("Base url and absolute url")
            << "http://example.com/example2"
            << QUrl("http://example.org/")
            << QUrl("http://example.com/example2");

    QTest::newRow("Base url and relative url")
            << "/example2"
            << QUrl("http://example.org/")
            << QUrl("http://example.org/example2");

    QTest::newRow("Base url and relative url without /")
            << "example2"
            << QUrl("http://example.org/")
            << QUrl("http://example.org/example2");
}

QTEST_MAIN(LinkElement_Test)
#include "LinkElement_test.moc"

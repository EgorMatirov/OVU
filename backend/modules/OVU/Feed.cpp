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
#include "Feed.h"

#include "Handlers/EntryHandler.h"
#include "Handlers/HandlersMap.h"

#include <QDebug>

Feed::Feed(QObject *parent) :
    QObject(parent),
    m_source(""),
    m_model(new FeedModel)
{

}

Feed::~Feed() {
    delete m_model;
}

void Feed::setSource(const QString &source)
{
    m_source = source;
    QXmlStreamReader reader(source);
    QXmlStreamReader::TokenType currentToken;
    while( !reader.atEnd() && !reader.hasError() ) {
        currentToken = reader.readNext();
        if( currentToken == QXmlStreamReader::StartElement ) {
            QString tokenName = reader.name().toString();
            Handler *handler = HandlersMap::handler(tokenName);

            /**
              * If error will happen while parsing in handler, reader will
              * know about it and we handle it later.
              */
            handler->parse(reader);
        }
    }
    if ( reader.hasError() ) {
        printError(reader);
    }
}

FeedModel *Feed::model()
{
    return m_model;
}

void Feed::printError(const QXmlStreamReader &reader) const
{
    qDebug() << "Error while parsing:" << reader.errorString();
    qDebug() << "Line:" << reader.lineNumber();
    qDebug() << "Column:" << reader.columnNumber();
    QStringList lines = m_source.split('\n');
    qDebug() << "Text:" << lines[reader.lineNumber() - 1];
}


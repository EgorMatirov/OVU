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
#include "Elements/EntryElement.h"

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
    if(source.isEmpty()) {
        return;
    }
    m_source = source;
    QXmlStreamReader reader(source);
    while( !reader.atEnd() && !reader.hasError() ) {
        reader.readNext();
        if( reader.isStartElement() ) {
            QString tokenName = reader.name().toString();
            Handler *handler = HandlersMap::handler(tokenName);

            /**
              * If error will happen while parsing in handler, reader will
              * know about it and we handle it later.
              */
            Element *element = handler->parse(reader);
            if( element->type() == Element::TitleType ) {
                TitleElement *title = static_cast<TitleElement*>(element);
                qDebug() << "Title:" << title->value();
                setTitle(title->value());
            }
            else if( element->type() == Element::EntryType ) {
                EntryElement *entry = static_cast<EntryElement*>(element);
                qDebug() << "Entry start.";
                qDebug() << "Title:" << entry->title()->value();
                qDebug() << "Content type:" << entry->content()->contentType();
                qDebug() << "Content:" << entry->content()->value();
                qDebug() << "Entry End";
                m_model->appendEntry(entry);
            }
        }
    }
    if ( reader.hasError() ) {
        printError(reader);
        emit errorHappened();
    }
    emit parsingFinished();
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
QString Feed::title() const
{
    return m_title;
}

void Feed::setTitle(const QString &title)
{
    m_title = title;
    emit titleChanged();
}



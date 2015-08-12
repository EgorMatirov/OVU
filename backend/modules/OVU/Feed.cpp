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
#include "Elements/NextLinkElement.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QNetworkRequest>

Feed::Feed(QObject *parent) :
    QObject(parent),
    m_source(""),
    m_model(new FeedModel),
    m_networkManager(new QNetworkAccessManager),
    m_nextPageUrl(QUrl()),
    m_isAddingNextPage(false)
{
    connect(m_networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(parse(QNetworkReply*)));
}

Feed::~Feed() {
    delete m_model;
    delete m_networkManager;
}

void Feed::setSource(const QString &source, const QUrl &url)
{
    if(source.isEmpty()) {
        return;
    }
    QElapsedTimer timer;
    timer.start();
    m_source = source;
    QXmlStreamReader reader(source);
    EntryElement *nextLinkEntry = nullptr;
    int indexOfPreviousNextLink = m_model->rowCount()-1;
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
            if( element->type() == Element::TitleType && !m_isAddingNextPage) {
                TitleElement *title = static_cast<TitleElement*>(element);
                setTitle(title->value());
            }
            else if( element->type() == Element::EntryType ) {
                EntryElement *entry = static_cast<EntryElement*>(element);
                entry->setBaseUrl(url);
                m_model->appendEntry(entry);
            } else if( element->type() == Element::NextLinkType ) {
                NextLinkElement *nextLink =
                        static_cast<NextLinkElement*>(element);
                nextLinkEntry = new EntryElement();
                NavigationFeedElement *navigationFeed =
                        new NavigationFeedElement(nextLink->url().toString());
                nextLinkEntry->setNavigationFeed(navigationFeed);
                nextLinkEntry->setIsNextEntry(true);
                nextLinkEntry->setBaseUrl(url);
                m_nextPageUrl=nextLinkEntry->navigationFeed()->url();
                delete nextLink;
            } else {
                delete element; // we are not using it anyway.
            }
        }
    }
    if ( reader.hasError() ) {
        printError(reader);
        emit errorHappened(tr("Parsing failed."));
    }
    if( nextLinkEntry != nullptr ) {
        if( m_isAddingNextPage ) {
            m_model->removeRow(indexOfPreviousNextLink);
        }
        m_model->appendEntry(nextLinkEntry);
    }
    m_isAddingNextPage = false;
    qDebug() << "Parsing finished." << timer.elapsed() << "milliseconds";
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

void Feed::get(const QUrl &url)
{
    if( url.isValid() ) {
        QNetworkRequest request(url);
        QString userAgent("OVU/0.0.0.1 (+https://github.com/EgorMatirov/OVU)");
        request.setRawHeader("User-Agent", userAgent.toUtf8());
        m_networkManager->get(request);
    }
}

void Feed::getNextPage()
{
    m_isAddingNextPage = true;
    get(m_nextPageUrl);
}

void Feed::parse(QNetworkReply *reply)
{
    if( reply->isFinished() && reply->isReadable() ) {
        if( reply->error() != QNetworkReply::NoError ) {
            if( reply->error() == QNetworkReply::AuthenticationRequiredError ) {
                emit authRequired();
            } else {
                emit errorHappened(reply->errorString());
            }
        } else {
            QString data = reply->readAll();
            setSource(data, reply->url());
        }
    }
}



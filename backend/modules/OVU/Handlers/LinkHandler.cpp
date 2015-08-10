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

#include "LinkHandler.h"

#include "Elements/ThumbnailElement.h"
#include "Elements/AcquisitionElement.h"
#include "Elements/NavigationFeedElement.h"
#include "Elements/NextLinkElement.h"

#include <QXmlStreamAttributes>
#include <QDebug>

LinkHandler::LinkHandler()
{
}

Element *LinkHandler::parse(QXmlStreamReader &reader) const
{
    Q_ASSERT(reader.isStartElement());
    QXmlStreamAttributes attributes = reader.attributes();
    if( !attributes.hasAttribute("href") ) {
        return new Element();
    }
    QString href = attributes.value("href").toString();
    Element *result;
    bool ok = false;
    if( attributes.hasAttribute("rel") ) {
        QString rel = attributes.value("rel").toString();
        if( isThumbnailRel(rel) ) {
            result = new ThumbnailElement(href);
            ok = true;
        } else if( isAcquisitionRel(rel) ) {
            result = new AcquisitionElement(href);
            ok = true;
        } else if( isNextLinkRer(rel) ) {
            result = new NextLinkElement(href);
            ok = true;
        }
    }

    if ( !ok && attributes.hasAttribute("type") ) {
        QString type = attributes.value("type").toString();
        if( isNavigationFeedType(type) ) {
            result = new NavigationFeedElement(href);
            ok = true;
        }
    }

    if( !ok ) {
        result = new Element();
    }

    while( !isEndElement(reader,QString("link")) && !reader.hasError() ) {
        reader.readNext();
    }
    return result;
}

bool LinkHandler::isThumbnailRel(const QString &rel) const
{
    return rel == QLatin1String("http://opds-spec.org/thumbnail")
            || rel == QLatin1String("http://opds-spec.org/image/thumbnail");
}

bool LinkHandler::isAcquisitionRel(const QString &rel) const
{
    return rel.startsWith(QLatin1String("http://opds-spec.org/acquisition"));
}

bool LinkHandler::isNavigationFeedType(const QString &type) const
{
    QString typeTemplate("application/atom+xml;profile=opds-catalog");
    return type.startsWith(typeTemplate);
}

bool LinkHandler::isNextLinkRer(const QString &rel) const
{
    return rel == QLatin1String("next");
}

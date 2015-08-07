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

#include <QXmlStreamAttributes>

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
    if( attributes.hasAttribute("rel") ) {
        QString type = attributes.value("rel").toString();
        if( isThumbnailRel(type) ) {
            result = new ThumbnailElement(href);
        } else {
            result = new Element();
        }
    } else {
        result = new Element();
    }
    while( !isEndElement(reader,QString("link")) && !reader.hasError() ) {
        reader.readNext();
    }
    return result;
}

bool LinkHandler::isThumbnailRel(const QString &rel) const
{
    return rel == "http://opds-spec.org/thumbnail";
}

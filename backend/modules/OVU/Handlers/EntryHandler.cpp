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

#include "EntryHandler.h"

#include "HandlersMap.h"
#include "Elements/EntryElement.h"

EntryHandler::EntryHandler()
{
}

Element *EntryHandler::parse(QXmlStreamReader &reader) const
{
    Q_ASSERT(reader.isStartElement());
    EntryElement *entry = new EntryElement;
    reader.readNext();
    bool navigationFeedFound = false;
    while( !isEndElement(reader,QString("entry")) && !reader.hasError() ) {
        if( reader.isStartElement() ) {
            QString tokenName = reader.name().toString();
            Handler *handler = HandlersMap::handler(tokenName);
            Element *element = handler->parse(reader);
            if( element->type() == Element::TitleType ) {
                entry->setTitle(static_cast<TitleElement*>(element));
            } else if( element->type() == Element::ContentType ) {
                entry->setContent(static_cast<ContentElement*>(element));
            } else if( element->type() == Element::ThumbnailType ) {
                entry->setThumbnail(static_cast<ThumbnailElement*>(element));
            } else if( element->type() == Element::AcquisitionType ) {
                AcquisitionElement *acquisition =
                        static_cast<AcquisitionElement*>(element);
                entry->appendAcquisition(acquisition);
            } else if( element->type() == Element::NavigationFeedType ) {
                if( !navigationFeedFound ) {
                    NavigationFeedElement *navigationFeed =
                            static_cast<NavigationFeedElement*>(element);
                    entry->setNavigationFeed(navigationFeed);
                    navigationFeedFound = true;
                }
            } else if( element->type() == Element::AuthorType ) {
                entry->appendAuthor(static_cast<AuthorElement*>(element));
            }
        }
        reader.readNext();
      }
    return entry;
}

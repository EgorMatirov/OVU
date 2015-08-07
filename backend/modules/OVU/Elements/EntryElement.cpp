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

#include "EntryElement.h"

EntryElement::EntryElement() :
    m_title(new TitleElement),
    m_content(new ContentElement),
    m_thumbnail(new ThumbnailElement)
{
}

EntryElement::~EntryElement()
{
    delete m_title;
    delete m_content;
    delete m_thumbnail;
}

Element::ElementType EntryElement::type() const
{
    return Element::EntryType;
}

TitleElement *EntryElement::title() const
{
    return m_title;
}

void EntryElement::setTitle(TitleElement *value)
{
    auto tmp = m_title;
    m_title = value;
    delete tmp;
}

ContentElement *EntryElement::content() const
{
    return m_content;
}

void EntryElement::setContent(ContentElement *content)
{
    auto tmp = m_content;
    m_content = content;
    delete tmp;
}
ThumbnailElement *EntryElement::thumbnail() const
{
    return m_thumbnail;
}

void EntryElement::setThumbnail(ThumbnailElement *thumbnail)
{
    auto tmp = m_thumbnail;
    m_thumbnail = thumbnail;
    delete tmp;
}
QUrl EntryElement::baseUrl() const
{
    return m_baseUrl;
}

void EntryElement::setBaseUrl(const QUrl &baseUrl)
{
    if( m_baseUrl != baseUrl ) {
        m_baseUrl = baseUrl;
        m_thumbnail->setBaseUrl(baseUrl);
    }
}


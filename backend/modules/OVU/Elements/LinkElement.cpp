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

#include "LinkElement.h"

LinkElement::LinkElement(const QString &url) :
    m_url(url)
{
}

Element::ElementType LinkElement::type() const
{
    // Right now LinkElement is just a base type for Thumbnails,etc.
    // So it doesn't have any own type yet.
    return Element::UnsupportedType;
}

QUrl LinkElement::url() const
{
    if( m_url.isEmpty() ) {
        return QString();
    }
    if( m_url.isRelative() ) {
        QUrl url(m_baseUrl);
        url.setPath(m_url.path());
        return url.toString();
    } else {
        return m_url;
    }
}

void LinkElement::setUrl(const QString &url)
{
    m_url = QUrl(url);
}

void LinkElement::setUrl(const QUrl &url)
{
    m_url = url;
}

QUrl LinkElement::baseUrl() const
{
    return m_baseUrl;
}

void LinkElement::setBaseUrl(const QUrl &baseUrl)
{
    m_baseUrl = baseUrl;
}

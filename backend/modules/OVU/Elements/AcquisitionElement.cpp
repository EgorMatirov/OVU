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

#include "AcquisitionElement.h"

#include <QDebug>

const QMimeDatabase AcquisitionElement::m_mimeDatabase;

QMap<QString,QString> AcquisitionElement::m_mimeNames;

AcquisitionElement::AcquisitionElement(const QString &url,
                                       const QString &contentType,
                                       bool isPaid, bool isSample) :
    LinkElement(url),
    m_isPaid(isPaid),
    m_isSample(isSample)
{
    setContentType(contentType);
}

Element::ElementType AcquisitionElement::type() const
{
    return Element::AcquisitionType;
}

QString AcquisitionElement::contentType() const
{
    return m_contentType;
}

void AcquisitionElement::setContentType(const QString &contentType)
{
    if( m_mimeNames.isEmpty() ) {
        m_mimeNames["application/x-mobipocket-ebook"] = tr("mobi");
        m_mimeNames["application/epub+zip"] = tr("epub");
        m_mimeNames["application/rtf+zip"] = tr("rtf");
        m_mimeNames["application/txt+zip"] = tr("txt");
        m_mimeNames["application/html+zip"] = tr("html");
        m_mimeNames["text/html"] = tr("html");
        m_mimeNames["application/fb2+zip"] = tr("fb2");
        m_mimeNames["application/pdf"] = tr("pdf");
    }
    QMimeType type = m_mimeDatabase.mimeTypeForName(contentType);
    if( m_mimeNames.contains( type.name() ) ) {
        m_contentType = m_mimeNames[type.name()];
    } else if( type.name().isEmpty() && m_mimeNames.contains( contentType ) ) {
        m_contentType = m_mimeNames[contentType];
    } else {
        qDebug() << "Unknown content type" << type.name() << contentType;
        m_contentType = type.comment();
    }
}
bool AcquisitionElement::isPaid() const
{
    return m_isPaid;
}

void AcquisitionElement::setIsPaid(bool isPaid)
{
    m_isPaid = isPaid;
}
bool AcquisitionElement::isSample() const
{
    return m_isSample;
}

void AcquisitionElement::setIsSample(bool isSample)
{
    m_isSample = isSample;
}




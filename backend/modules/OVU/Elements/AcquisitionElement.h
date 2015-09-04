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

#ifndef ACQUISITION_ELEMENT_H
#define ACQUISITION_ELEMENT_H

#include "LinkElement.h"

#include <QMimeDatabase>
#include <QMap>

class AcquisitionElement : public LinkElement
{

    Q_OBJECT

public:
    explicit AcquisitionElement(const QString &url = "",
                                const QString &contentType = "",
                                bool isPaid = false,
                                bool isSample = false);

    Element::ElementType type() const override;
    QString contentType() const;
    void setContentType(const QString &contentType);

    bool isPaid() const;
    void setIsPaid(bool isPaid);

    bool isSample() const;
    void setIsSample(bool isSample);

private:
    QString m_contentType;
    bool m_isPaid;
    bool m_isSample;
    static const QMimeDatabase m_mimeDatabase;
    static QMap<QString,QString> m_mimeNames;
};

#endif // ACQUISITION_ELEMENT_H

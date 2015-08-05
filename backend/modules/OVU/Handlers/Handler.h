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

#ifndef HANDLER_H
#define HANDLER_H

#include "Elements/Element.h"

#include <QXmlStreamReader>

class Handler {

public:
    explicit Handler();
    virtual Element *parse(QXmlStreamReader &reader) const;

protected:
    bool isEndElement(const QXmlStreamReader &reader,
                        const QString &elementName) const;

private:
    static bool test;
};

#endif // HANDLER_H

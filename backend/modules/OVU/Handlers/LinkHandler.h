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

#ifndef LINK_HANDLER_H
#define LINK_HANDLER_H

#include "Handler.h"

class LinkHandler : public Handler {

public:
    explicit LinkHandler();
    Element *parse(QXmlStreamReader &reader) const;

private:
    bool isThumbnailRel(const QString &rel) const;
    bool isAcquisitionRel(const QString &rel) const;
    bool isAcquisitionBuyRel(const QString &rel) const;
    bool isAcquisitionSampleRel(const QString &rel) const;
    bool isNavigationFeedType(const QString &type) const;
    bool isNextLinkRer(const QString &rel) const;
};

#endif // LINK_HANDLER_H

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

#ifndef HANDLERS_MAP_H
#define HANDLERS_MAP_H

#include "EntryHandler.h"
#include "TitleHandler.h"

#include <QMap>

class HandlersMap {
public:
    static Handler *handler(const QString &name);
private:
    static void initialize();
    static QMap<QString,Handler*> handlers;
    static bool initialized;
};

#endif // HANDLERS_MAP_H

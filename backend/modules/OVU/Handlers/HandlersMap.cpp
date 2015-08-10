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

#include "HandlersMap.h"

#include "EntryHandler.h"
#include "TitleHandler.h"
#include "ContentHandler.h"
#include "LinkHandler.h"
#include "NameHandler.h"
#include "AuthorHandler.h"

QMap<QString,Handler*> HandlersMap::handlers = QMap<QString,Handler*>();
bool HandlersMap::initialized = false;

Handler *HandlersMap::handler(const QString &name)
{
    if(!initialized) {
        initialize();
    }
    if(handlers.contains(name)) {
        return handlers[name];
    }
    return new Handler();
}

void HandlersMap::initialize()
{
    handlers["entry"] = new EntryHandler();
    handlers["title"] = new TitleHandler();
    handlers["content"] = new ContentHandler();
    handlers["link"] = new LinkHandler();
    handlers["name"] = new NameHandler();
    handlers["author"] = new AuthorHandler();
    initialized = true;
}

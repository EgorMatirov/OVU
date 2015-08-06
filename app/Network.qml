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

import QtQuick 2.0

Item {
    id: root
    signal sourceRecieved(string sourceText);
    signal authRequired();
    signal errorHappened(int code,string message);
    function get(url) {
        var doc = new XMLHttpRequest();
        doc.onreadystatechange = function() {
            if (doc.readyState === XMLHttpRequest.DONE) {
                if(doc.getResponseHeader ("WWW-Authenticate") !== "") {
                    authRequired();
                } else {
                    if(doc.status == 200) {
                        sourceRecieved(doc.responseText);
                    } else {
                        errorHappened(doc.status, doc.statusText);
                    }
                }
            }
        }

        doc.open("GET", url, true);
        doc.send();
    }
}

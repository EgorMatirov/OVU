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
import Ubuntu.Components 1.2
import OVU 1.0

Item {
    id: root
    signal errorHappened(string error)
    signal newPageRequested(url source)
    property alias title: feed.title
    property url source: ""
    Feed {
        id: feed
        onErrorHappened: root.errorHappened(i18n.tr("Sorry, parsing failed"));
    }
    
    Network {
        id: network
        Component.onCompleted: network.get(root.source);
        onSourceRecieved: feed.sourceText = sourceText;
        onAuthRequired: {
            var message = i18n.tr("Sorry, authorization isn't supported yet.");
            root.errorHappened(message);
        }
        onErrorHappened: {
            var message = i18n.tr("Error: %1 %2").arg(code).arg(message);
            root.errorHappened(message);
        }
    }
    
    ListView {
        id: listView
        anchors.fill: parent
        model: feed.model
        
        delegate: ListItem {
            id: delegate
            height: bookDelegate.height + units.gu(2)
            contentItem.anchors {
                leftMargin: units.gu(2)
                rightMargin: units.gu(2)
                topMargin: units.gu(0.5)
                bottomMargin: units.gu(0.5)
            }
            action: Action {
                onTriggered: {
                    var url = "";
                    root.newPageRequested(url);
                }
            }
            BookDelegate {
                id: bookDelegate
                width: parent.width
            }
        }
    }
}

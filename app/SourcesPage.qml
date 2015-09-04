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
import Ubuntu.Components.Popups 1.0
import U1db 1.0
import OVU 1.0

Page {
    id: root

    title: i18n.tr("Choose catalog")

    signal newNavigationPageRequested(url path)
    signal infoPageRequested()

    head.actions: [
        Action {
            iconName: "add"
            text: i18n.tr("Add...")
            onTriggered: {
                newSourceDialog.open();
            }
        },
        Action {
            iconName: "info"
            text: i18n.tr("About")
            onTriggered: {
                root.infoPageRequested();
            }
        }

    ]

    Database {
        id: database
        path: "OVUSources.db"
        function nextId() {
            var list = listDocs();
            list = [].concat( list );

            var len = list.length;

            if( len === 0 ) {
                return 0;
            }

            var currentId = parseInt(list[len-1]);

            return currentId + 1;
        }
    }

    ListView{
        anchors.fill: parent
        model: Query{
            index: Index {
                name: "titleIndex"
                expression: ["title", "url"]
                database: database
            }
        }

        delegate: ListItem {
            action: Action {
                onTriggered: {
                    root.newNavigationPageRequested(contents.url)
                }
            }
            Label {
                anchors.centerIn: parent
                text: contents.title
                fontSize: "large"
            }
        }
    }

    Feed {
        id: feed
        onParsingFinished: {
            if( !hasError ) {
                var doc = {
                    url:feed.url,
                    title: feed.title
                };

                database.putDoc(doc, database.nextId());
                newSourceDialog.close();
            }
        }
        onErrorHappened: {
            newSourceDialog.error = message;
            newSourceDialog.showError();
        }
    }

    NewSourceDialog {
        id: newSourceDialog
        onAccepted: feed.get(url)
    }
}

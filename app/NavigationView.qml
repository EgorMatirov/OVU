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
    signal replacingPageRequested(url source)
    signal parsingFinished()
    property alias title: feed.title
    property url sourceUrl: ""
    property bool isLoadingNextPage: false
    onSourceUrlChanged: feed.get(root.sourceUrl)
    Component.onCompleted: feed.get(root.sourceUrl)

    Feed {
        id: feed
        onParsingFinished: {
            root.isLoadingNextPage = false;
            root.parsingFinished();
        }
        onAuthRequired: {
            root.isLoadingNextPage = false;
            var message = i18n.tr("Sorry, authorization isn't supported yet.");
            root.errorHappened(message);
        }
        onErrorHappened: {
            root.isLoadingNextPage = false;
            root.errorHappened(message);
        }
    }
    
    ListView {
        id: listView
        anchors.fill: parent
        model: feed.model
        
        delegate: ListItem {
            id: delegate
            height: entryLoader.height + units.gu(2)
            contentItem.anchors {
                leftMargin: units.gu(2)
                rightMargin: units.gu(2)
                topMargin: units.gu(0.5)
                bottomMargin: units.gu(0.5)
            }
            action: Action {
                onTriggered: {
                    if( !isAcquisition ) {
                        if( isNextLink ) {
                            feed.getNextPage();
                            root.isLoadingNextPage = true;
                        } else {
                            root.newPageRequested(navigationLink);
                        }
                    }
                }
            }
            Loader {
                id: entryLoader
                source: isAcquisition ?
                            Qt.resolvedUrl("BookEntry.qml")
                          : isNextLink ?
                                Qt.resolvedUrl("NextLinkEntry.qml")
                              : Qt.resolvedUrl("NavigationEntry.qml")
                anchors.left: parent.left
                anchors.right: parent.right
                width: parent.width
                property bool loading: root.isLoadingNextPage
            }
        }
    }
}

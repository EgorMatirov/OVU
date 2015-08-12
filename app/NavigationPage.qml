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

Page {
    id: root
    title: i18n.tr("Loading...")

    property url source: ""

    function showError(error) {
        activityIndicator.running = false;
        title = error;
        errorView.message = error;
        loader.visible = false;
        errorView.show();
    }

    signal newPageRequested(url source)
    signal replacingPageRequested(url source)

    flickable: null

    Flickable{
        anchors.fill: parent
        clip: true

        Loader {
            id: loader
            source: Qt.resolvedUrl("NavigationView.qml");
            visible: false
            anchors.fill: parent
            asynchronous: true
        }

        Connections{
            target: loader.item
            onParsingFinished: {
                activityIndicator.running = false;
                loader.visible = true;
                root.title = loader.item.title
            }
            onErrorHappened: root.showError(error)
            onNewPageRequested: root.newPageRequested(source)
            onReplacingPageRequested: root.replacingPageRequested(source)
        }

        Binding {
            target: loader.item
            property: "sourceUrl"
            value: root.source
            when: loader.status == Loader.Ready
        }

        ActivityIndicator {
            id: activityIndicator
            anchors.centerIn: parent
            running: true
        }

        ErrorView {
            id: errorView
            anchors.fill: parent
            visible: false
        }
    }
}

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
import U1db 1.0
import Ubuntu.Components 1.2
MainView {
    id: mainView
    // objectName for functional testing purposes (autopilot-qt5)
    objectName: "mainView"

    // Note!
    // applicationName needs to match the "name" field of the click manifest
    applicationName: "ovu.egormatirov"

    /*
     This property enables the application to change orientation
     when the device is rotated. The default is false.
    */
    //automaticOrientation: true

    width: units.gu(100)
    height: units.gu(76)



    PageStack{
        id: pageStack
        anchors.fill: parent
        // Append root page here for navigation.
        Component.onCompleted: {
            var page = push(Qt.resolvedUrl("SourcesPage.qml"));
            page.newNavigationPageRequested.connect(appendNavigationPage);
            page.onInfoPageRequested.connect(appendInfoPage);
        }

        function appendNavigationPage(path) {
            var params = {path:path};
            var page = push(Qt.resolvedUrl("NavigationPage.qml"), params);
            page.newNavigationPageRequested.connect(appendNavigationPage);
            page.newBookPageRequested.connect(appendBookPage);
            page.replacingPageRequested.connect(replacePage);
        }

        function appendBookPage(params) {
            var page = push(Qt.resolvedUrl("BookPage.qml"), params);
            page.sharePageRequested.connect(openSharePage);
        }

        function replacePage(path) {
            pop();
            appendNavigationPage(path);
        }

        function openSharePage(path) {
            var params = {path: path};
            var page = push(Qt.resolvedUrl("SharePage.qml"), params);
            page.popRequested.connect(pop);
        }

        function appendInfoPage() {
            var page = push(Qt.resolvedUrl("InfoPage.qml"), {});
        }
    }
}


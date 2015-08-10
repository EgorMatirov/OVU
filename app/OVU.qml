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

MainView {
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
        Component.onCompleted: appendPage("")

        function appendPage(source) {
            var properties = {source:source};
            var page = push(Qt.resolvedUrl("NavigationPage.qml"), properties);
            page.newPageRequested.connect(appendPage);
            page.replacingPageRequested.connect(replacePage);
        }

        function replacePage(source) {
            pop();
            appendPage(source);
        }
    }
}


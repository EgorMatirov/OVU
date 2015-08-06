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
import QtQuick.Layouts 1.1
import Ubuntu.Components 1.2

Item {
    id: root
    height: titleLabel.height + contentLabel.height
    RowLayout {
        anchors.fill: parent
        width: parent.width
        Item{
            width: cover.width
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            visible: true
            Cover {
                id: cover
                visible: false
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Item{
            Layout.fillWidth: true
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Label {
                id: titleLabel
                text: title
                fontSize: "large"
                font.weight: Font.Light
                wrapMode: Text.Wrap
                width: parent.width
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                }
            }
            Label {
                id: contentLabel
                text: content
                wrapMode: Text.Wrap
                width: parent.width
                anchors {
                    left: parent.left
                    right: parent.right
                    top: titleLabel.bottom
                }
            }
        }
    }
}

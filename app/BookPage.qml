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
import Ubuntu.Components.Popups 1.0
import Ubuntu.DownloadManager 0.1
import Ubuntu.Content 1.1

Page {
    id: root

    property var authors: []
    property var acquisitions: []
    property url thumbnail: ""
    property string description: ""

    signal sharePageRequested(url path)

    function download(path) {
        progress.visible = true;
        download.download(path);
    }

    flickable: null

    Flickable{
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: bottomButtons.top
            margins: units.gu(1)
        }

        clip: true
        contentHeight: authorsLabel.height + thumbnailImage.height + descriptionLabel.height

        // TODO: Use Cover instead of Thumbnail.
        Thumbnail {
            id: thumbnailImage
            source: thumbnail.toString() === ""
                    ? Qt.resolvedUrl("graphics/book.png")
                    : thumbnail
            height: root.height/2
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
        }

        Label {
            id: authorsLabel
            text: authors.join(", ")
            fontSize: "large"
            wrapMode: Text.Wrap
            anchors {
                left: parent.left
                right: parent.right
                leftMargin: units.gu(1)
                rightMargin: units.gu(1)
                top: thumbnailImage.bottom
            }
        }

        Label {
            id: descriptionLabel
            text: description
            wrapMode: Text.Wrap
            anchors{
                left: parent.left
                right: parent.right
                top: authorsLabel.bottom
                leftMargin: units.gu(1)
                rightMargin: units.gu(1)
            }
            onLinkActivated: {
                Qt.openUrlExternally(link);
            }
        }
    }

    Item {
        id: bottomButtons
        height: downloadButton.height
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: units.gu(1)
        }
        ProgressBar {
            id: progress
            minimumValue: 0
            maximumValue: 100
            visible: false
            value: download.progress
            anchors {
                left: parent.left
                right: downloadButton.left
                bottom: parent.bottom
                rightMargin: units.gu(1)
            }
        }
        Button {
            id: downloadButton
            anchors.right: parent.right
            text: i18n.tr("Open")
            color: UbuntuColors.green
            onClicked: {
                dialog.caller = downloadButton;
                dialog.show()
            }
        }
    }

    ActionSelectionPopover{
        id: dialog
        target: downloadButton
        Component.onCompleted: {
            var actions = [];

            var url = Qt.resolvedUrl("DownloadAction.qml");
            var component = Qt.createComponent(url);

            if( component.status === Component.Ready ) {
                createActions();
            } else {
                component.statusChanged.connect(createActions);
            }

            function createActions() {
                for(var i in acquisitions) {
                    var params = {
                        contentType: acquisitions[i][0],
                        path: acquisitions[i][1],
                        isPaid: acquisitions[i][2],
                        isSample: acquisitions[i][3]
                    };

                    var object = component.createObject(root, params);
                    object.downloadRequested.connect(root.download);
                    actions.push(object);
                }
                dialog.actions = actions;
            }
        }
    }

    SingleDownload {
        id: download
        onFinished: {
            progress.visible = false;
            root.sharePageRequested(path);
        }
    }
}

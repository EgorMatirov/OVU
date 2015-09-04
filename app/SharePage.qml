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
import Ubuntu.Content 1.1

Page {
    id: root
    property alias path: item.url

    signal popRequested()

    ContentItem{
        id: item
    }
    ContentPeerPicker {
        id: picker
        contentType: ContentType.EBooks
        handler: ContentHandler.Destination
        onPeerSelected: {
            var transfer = peer.request();
            transfer.items=[item];
            transfer.state = ContentTransfer.Charged;
            transfer.stateChanged.connect( function() {
                if(transfer.state === ContentTransfer.Aborted
                        || transfer.state === ContentTransfer.Collected) {
                    root.popRequested();
                }
            } );
        }
        onCancelPressed: {
            root.popRequested();
        }
    }
}

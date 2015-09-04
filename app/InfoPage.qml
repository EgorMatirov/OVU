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

Page {
    id: root
    title: i18n.tr("About")
    Label {
        id: aboutLabel
        wrapMode: Text.Wrap
        anchors.fill: parent
        anchors.margins: units.gu(1)
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: i18n.tr("This program is a simple OPDS Viewer.<br>It allows you to:<ul><li>Browse different OPDS catalogs.</li><li>View book information.</li><li>Open book in 3rd-party app.</li></ul><br>©2015 Mikhail Ivchenko <ematirov@gmail.com> under GNU GPLv3 license.<br><br>The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.<br><br><b>Warning:</b><br>Author doesn't take any responsibility for content of third-party OPDS catalogs. It's possbile that some catalogs can have illegal in your country entries.")
    }
}

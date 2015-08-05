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
//import Ubuntu.Components 1.1
import OVU 1.0

/*!
    \brief MainView with Tabs element.
           First Tab has a single Label and
           second Tab has a single ToolbarAction.
*/

Rectangle{
    width: 200
    height: 200
    Feed {
        id: feed
        source: "<?xml version=\"1.0\" encoding=\"utf-8\"?><feed xmlns=\"http://www.w3.org/2005/Atom\" xmlns:dc=\"http://purl.org/dc/terms/\" xmlns:os=\"http://a9.com/-/spec/opensearch/1.1/\" xmlns:opds=\"http://opds-spec.org/2010/catalog\"> <id>tag:root</id> <title>flibusta.net catalog</title> <updated>2015-08-04T07:36:25+02:00</updated> <icon>/favicon.ico</icon> <link href=\"/opds-opensearch.xml\" rel=\"search\" type=\"application/opensearchdescription+xml\" /> <link href=\"/opds/search?searchTerm={searchTerms}\" rel=\"search\" type=\"application/atom+xml\" /> <link href=\"/opds\" rel=\"start\" type=\"application/atom+xml;profile=opds-catalog\" /> <link href=\"/opds\" rel=\"self\" type=\"application/atom+xml;profile=opds-catalog\" /> <entry> <updated>2015-08-04T07:36:25+02:00</updated> <id>tag:root:new</id> <title>Новинки</title> <content type=\"text\">Новые поступления за неделю</content> <link href=\"/opds/new\" rel=\"http://opds-spec.org/sort/new\" type=\"application/atom+xml;profile=opds-catalog\" /> <link href=\"/opds/new\" type=\"application/atom+xml;profile=opds-catalog\" /></entry> <entry> <updated>2015-08-04T07:36:25+02:00</updated> <id>tag:root:authors</id> <title>По авторам</title> <content type=\"text\">Поиск книг по авторам</content> <link href=\"/opds/authorsindex\" type=\"application/atom+xml;profile=opds-catalog\" /></entry> <entry> <updated>2015-08-04T07:36:25+02:00</updated> <id>tag:root:sequences</id> <title>По сериям</title> <content type=\"text\">Поиск книг по сериям</content> <link href=\"/opds/sequencesindex\" type=\"application/atom+xml;profile=opds-catalog\" /></entry> <entry> <updated>2015-08-04T07:36:25+02:00</updated> <id>tag:root:genre</id> <title>По жанрам</title> <content type=\"text\">Поиск книг по жанрам</content> <link href=\"/opds/genres\" type=\"application/atom+xml;profile=opds-catalog\" /></entry> <entry> <updated>2015-08-04T07:36:25+02:00</updated> <id>tag:root:shelf</id> <title>Моя полка</title> <content type=\"text\">Книжная полка (требуется логин)</content> <link href=\"/opds/polka\" type=\"application/atom+xml;profile=opds-catalog\" /></entry></feed>"
    }
}

//MainView {
//    // objectName for functional testing purposes (autopilot-qt5)
//    objectName: "mainView"

//    // Note! applicationName needs to match the "name" field of the click manifest
//    applicationName: "ovu.egormatirov"

//    /*
//     This property enables the application to change orientation
//     when the device is rotated. The default is false.
//    */
//    //automaticOrientation: true

//    // Removes the old toolbar and enables new features of the new header.
//    useDeprecatedToolbar: false

//    width: units.gu(100)
//    height: units.gu(76)

//    Page {
//        title: i18n.tr("App with backend")

//        MyType {
//            id: myType

//            Component.onCompleted: {
//                myType.helloWorld = i18n.tr("Hello world..")
//            }
//        }

//        Column {
//            spacing: units.gu(1)
//            anchors {
//                margins: units.gu(2)
//                fill: parent
//            }

//            Label {
//                id: label
//                objectName: "label"

//                text: myType.helloWorld
//            }

//            Button {
//                objectName: "button"
//                width: parent.width

//                text: i18n.tr("Tap me!")

//                onClicked: {
//                    myType.helloWorld = i18n.tr("..from Cpp Backend")
//                }
//            }
//        }
//    }
//}


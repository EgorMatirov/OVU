import QtQuick 2.0
import Ubuntu.Components 1.2

Action {
    id: root
    property string contentType: ""
    property url path: ""
    property bool isPaid: false
    property bool isSample: false
    signal downloadRequested(url path)
    text: isPaid ?
              i18n.tr("Buy") :
              (isSample ?
                   i18n.tr("%1 (sample)").arg(contentType) :
                   contentType)
    onTriggered: {
        if( isPaid ) {
            Qt.openUrlExternally(path);
        } else {
            root.downloadRequested(path);
        }
    }
}

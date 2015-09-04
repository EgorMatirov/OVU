import QtQuick 2.0
import Ubuntu.Components 1.2
import Ubuntu.Components.Popups 1.0

Dialog {
    id: root
    title: i18n.tr("Add new catalog")

    signal accepted()
    signal rejected()

    onAccepted: {
        state = "inProgress";
    }

    onRejected: {
        state = "initialState";
        PopupUtils.close(root);
    }

    property alias url: urlField.text
    property alias error: errorLabel.text

    function add() {
        state = "inProgress";
        root.accepted();
    }
    
    function open() {
        state = "initialState";
        show();
    }

    function close() {
        state = "initialState";
        hide();
    }

    function showError() {
        state = "urlIsIncorrect";
    }

    TextField{
        id: urlField
        placeholderText: i18n.tr("URL of catalog")
        inputMethodHints: Qt.ImhUrlCharactersOnly
        onAccepted: root.accepted()
    }
    
    Label {
        id: errorLabel
        visible: false
        width: parent.width
        wrapMode: Text.Wrap
    }
    
    Button {
        id: cancelButton
        text: i18n.tr("Cancel")
        onClicked: {
            root.rejected();
        }
    }
    
    Button {
        id: addButton
        text: i18n.tr("Add")
        color: UbuntuColors.green
        onClicked: root.accepted()
    }
    
    ProgressBar {
        id: progressBar
        indeterminate: true
        visible: false
    }
    
    state: "initialState"
    
    states: [
        State {
            name: "initialState"
            
            PropertyChanges {
                target: errorLabel
                text: ""
                visible: false
            }
            
            PropertyChanges {
                target: urlField
                text: ""
                readOnly: false
                restoreEntryValues: false
            }
            
            PropertyChanges {
                target: addButton
                visible: true
            }
            
            PropertyChanges {
                target: progressBar
                visible: false
            }
        },
        
        State {
            name: "inProgress"
            
            PropertyChanges {
                target: urlField
                readOnly: true
            }
            
            PropertyChanges {
                target: addButton
                visible: false
            }
            
            PropertyChanges {
                target: progressBar
                visible: true
            }
        },
        
        State {
            name: "urlIsIncorrect"
            
            PropertyChanges {
                target: urlField
                readOnly: false
            }
            
            PropertyChanges {
                target: addButton
                visible: true
            }
            
            PropertyChanges {
                target: progressBar
                visible: false
            }
            
            PropertyChanges {
                target: errorLabel
                visible: true
            }
        }
    ]
}

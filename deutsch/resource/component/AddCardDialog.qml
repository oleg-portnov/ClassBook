import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

import classbook

Dialog {
    id: root

    title: qsTr("Adding a card")

    width: root_window.width
    height: root_window.height

    property CardsModel cardsModel

    contentItem: Rectangle {
        color: "#004466"
    }

    Image {
        id: image

        anchors.top: parent.top
        anchors.topMargin: 9

        anchors.bottom: url.top
        anchors.bottomMargin: 6

        anchors.left: parent.left
        anchors.leftMargin: 9

        anchors.right: parent.right
        anchors.rightMargin: 9

        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: url

        anchors.bottom: textDeField.top
        anchors.bottomMargin: 6

        anchors.left: parent.left
        anchors.leftMargin: 9

        anchors.right: parent.right
        anchors.rightMargin: 9

        visible: false

        height: 40

        color: Qt.white

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    TextField {
        id: textDeField

        placeholderText: qsTr("Enter text in German")

        height: 40

        anchors.bottom: textRuField.top
        anchors.bottomMargin: 6

        anchors.left: parent.left
        anchors.leftMargin: 9

        anchors.right: parent.right
        anchors.rightMargin: 9
    }

    TextField {
        id: textRuField

        placeholderText: qsTr("Enter text in Russian")

        height: 40

        anchors.bottom: btn_save.top
        anchors.bottomMargin: 6

        anchors.left: parent.left
        anchors.leftMargin: 9

        anchors.right: parent.right
        anchors.rightMargin: 9
    }

    Button {
        id: btn_sel_img

        height: 40

        anchors.bottom: parent.bottom
        anchors.left: parent.left

        text: qsTr("Select image")
        onClicked: fileDialog.open()
    }

    Button {
        id: btn_save

        height: 40

        implicitWidth: 100

        anchors.bottom: parent.bottom

        anchors.left: btn_sel_img.right
        anchors.leftMargin: 6

        anchors.right: btn_cancel.left
        anchors.rightMargin: 6

        text: qsTr("Save")

        onClicked: {
            cardsModel.addCard(textDeField.text,
                               textRuField.text,
                               cardsModel.copyToImgFolder(fileDialog.currentFile,
                                                          StandardPaths.writableLocation(StandardPaths.DocumentsLocation)))
            textDeField.text = ""
            textRuField.text = ""

            root.accept()
        }
    }

    Button {
        id: btn_cancel

        height: 40

        anchors.bottom: parent.bottom
        anchors.right: parent.right

        text: qsTr("Cancel")

        onClicked: root.close()
    }

    FileDialog {
        id: fileDialog

        title: qsTr("Select an image")

        nameFilters: ["Images (*.png *.jpg)"]

        options: FileDialog.DontResolveSymlinks

        onAccepted: {
            var selectedFileUrl = fileDialog.currentFile;
            image.source = selectedFileUrl
            url.text = selectedFileUrl
            url.visible = true
        }
    }
}

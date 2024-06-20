import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtCore

import classbook

Dialog {
    id: root

    title: qsTr("Добавление карточки")

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
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.bottomMargin: 6
        anchors.leftMargin: 9
        anchors.rightMargin: 9

        visible: false

        height: 40

        color: Qt.white

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    TextField {
        id: textDeField

        placeholderText: qsTr("Введите текст на немецком")

        height: 40

        anchors.bottom: textRuField.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.bottomMargin: 6
        anchors.leftMargin: 9
        anchors.rightMargin: 9
    }

    TextField {
        id: textRuField

        placeholderText: qsTr("Введите текст на русском")

        height: 40

        anchors.bottom: btn_save.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.bottomMargin: 6
        anchors.leftMargin: 9
        anchors.rightMargin: 9
    }

    Button {
        id: btn_sel_img

        height: 40

        anchors.bottom: parent.bottom
        anchors.left: parent.left

        text: qsTr("Выбрать изображение")
        onClicked: fileDialog.open()
    }

    Button {
        id: btn_save

        height: 40

        implicitWidth: 100

        anchors.bottom: parent.bottom
        anchors.left: btn_sel_img.right
        anchors.right: btn_cancel.left

        anchors.leftMargin: 6
        anchors.rightMargin: 6

        text: qsTr("Сохранить")
        onClicked: {
            cardsModel.addCard(textDeField.text, textRuField.text, cardsModel.copyToImgFolder(fileDialog.currentFile, StandardPaths.writableLocation(StandardPaths.DocumentsLocation)))
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

        text: qsTr("Отмена")
        onClicked: root.close()
    }

    FileDialog {
        id: fileDialog

        title: qsTr("Выберите изображение")

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

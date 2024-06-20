import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Button {
    id: btn_add

    property alias btn_text: btn_add.text

    Layout.fillWidth: true

    implicitHeight: 40

    background: Rectangle {
        color: "#5599bb"
        anchors.fill: parent
        radius: 14
    }
}

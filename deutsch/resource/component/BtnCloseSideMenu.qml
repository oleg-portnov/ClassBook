import QtQuick
import QtQuick.Controls

Button {
    width: 40
    height: 40

    icon.source: "/img/close.svg"

    background: Rectangle {
        color: "#5599bb"
        anchors.fill: parent
        radius: 14
    }
}

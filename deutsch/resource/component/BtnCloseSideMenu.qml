import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore

import classbook

Button {
    id: close_side_menu

    width: 40
    height: 40

    onClicked: side_menu.close()

    icon.name: "menu"
    icon.source: "/img/close.svg"

    background: Rectangle {
        color: "#5599bb"
        anchors.fill: parent
        radius: 14
    }
}

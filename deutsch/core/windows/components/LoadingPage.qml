import QtQuick
import QtQuick.Controls

import SimpleRiddle

Item {
    Loader {
        id: loader

        anchors.fill: parent

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        sourceComponent: SimpleRiddleMainItem {}

        asynchronous: true

        BusyIndicator {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}

import QtQuick
import QtQuick.Controls

import CoreModule

Window {
    id: root_window

    visible: true

    flags: Qt.Window | Qt.FramelessWindowHint

    color: "transparent"

    Component.onCompleted: {
        var os_type = Qt.platform.os
        if (os_type === "linux" || os_type === "windows") {
            width = 400
            height = 600

            x = Screen.width / 2 - width / 2
            y = Screen.height / 2 - height / 2
        }
    }

    HoverHandler {
        id: hover_hndr

        acceptedDevices: PointerDevice.Mouse

        onPointChanged: {
            if (header.state === "hidden" && point.position.y <= header.defHeight)
                header.showHeader()
            else if (header.state === "shown" && point.position.y >= header.defHeight)
                header.hideHeader()
        }

        onHoveredChanged: {
            if (!hovered)
                header.hideHeader()
        }
    }

    Rectangle {
        id: background_rect

        anchors.fill: parent

        radius: 4

        color: "#004466"

        Rectangle {
            id: header

            readonly property int defHeight: 32
            readonly property int defAnimationSpeed: 200

            height: 0

            color: header_mouse_area.containsMouse || close_button.hovered ? "#1f5fa0"
                                                                           : "#004466"

            state: "hidden"

            states: [
                State {
                    name: "shown"
                    PropertyChanges { target: header_mouse_area; enabled: true }
                },
                State {
                    name: "hidden"
                    PropertyChanges { target: header_mouse_area; enabled: false }
                }
            ]

            transitions: [
                Transition {
                    from: "shown"
                    to: "hidden"

                    ParallelAnimation {

                        NumberAnimation { target: header; property: "height"; to: 0; duration: header.defAnimationSpeed; easing.type: Easing.Linear; }
                        NumberAnimation { target: header; property: "opacity"; to: 0.0; duration: header.defAnimationSpeed; easing.type: Easing.Linear; }
                        NumberAnimation { target: header; property: "anchors.topMargin"; to: 0; duration: header.defAnimationSpeed; easing.type: Easing.Linear }
                        NumberAnimation { target: header; property: "anchors.bottomMargin"; to: 0; duration: header.defAnimationSpeed; easing.type: Easing.Linear }

                        NumberAnimation { target: stack_view; property: "anchors.topMargin"; to: 0; duration: header.defAnimationSpeed; easing.type: Easing.Linear }
                    }
                },
                Transition {
                    from: "hidden"
                    to: "shown"

                    ParallelAnimation {
                        NumberAnimation { target: header; property: "height"; to: header.defHeight; duration: header.defAnimationSpeed; easing.type: Easing.Linear }
                        NumberAnimation { target: header; property: "opacity"; to: 1.0; duration: header.defAnimationSpeed; easing.type: Easing.Linear }
                        NumberAnimation { target: header; property: "anchors.topMargin"; to: 4; duration: header.defAnimationSpeed; easing.type: Easing.Linear }
                        NumberAnimation { target: header; property: "anchors.bottomMargin"; to: 4; duration: header.defAnimationSpeed; easing.type: Easing.Linear }

                        NumberAnimation { target: stack_view; property: "anchors.topMargin"; to: 4; duration: header.defAnimationSpeed; easing.type: Easing.Linear }
                    }
                }
            ]

            function showHeader()
            {
                state = "shown"
            }

            function hideHeader()
            {
                state = "hidden"
            }

            Behavior on color { ColorAnimation { duration: 150; easing.type: Easing.Linear } }

            anchors.top: parent.top
            anchors.topMargin: 0

            anchors.bottomMargin: 0

            anchors.left: parent.left
            anchors.leftMargin: 4

            anchors.right: parent.right
            anchors.rightMargin: 4

            radius: 4

            MouseArea {
                id: header_mouse_area

                hoverEnabled: true

                anchors.top: parent.top
                anchors.bottom: parent.bottom

                anchors.left: parent.left
                anchors.right: close_button.left

                // TODO: event eating press event
                onPressed: root_window.startSystemMove()
            }

            WindowsCloseBtn {
                id: close_button

                anchors.top: parent.top
                anchors.topMargin: 4

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 4

                anchors.right: parent.right
                anchors.rightMargin: 4
            }
        }

        StackView {
            id: stack_view

            anchors.top: header.bottom
            anchors.topMargin: 0

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            initialItem: MainMenu {}
        }
    }
}

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

    Rectangle {
        id: background_rect

        anchors.fill: parent

        radius: 4

        color: "#004466"

        Rectangle {
            id: header

            height: 32

            color: header_mouse_area.containsMouse || close_button.hovered ? "#1f5fa0"
                                                                           : "#004466"

            Behavior on color {
                ColorAnimation { duration: 150; easing.type: Easing.Linear }
            }

            anchors.top: parent.top
            anchors.topMargin: 4

            anchors.bottomMargin: 4

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

            Button {
                id: close_button

                focusPolicy: Qt.ClickFocus

                width: btn_text.contentWidth + btn_text.leftPadding + btn_text.rightPadding

                anchors.top: parent.top
                anchors.topMargin: 4

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 4

                anchors.right: parent.right
                anchors.rightMargin: 4

                hoverEnabled: true

                background: Rectangle {
                    color: close_button.hovered ? "#e52d2d"
                                                : "transparent"

                    Behavior on color {
                        ColorAnimation { duration: 150; easing.type: Easing.Linear }
                    }

                    radius: 4
                }

                contentItem: Text {
                    id: btn_text

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    leftPadding: 4
                    rightPadding: 4

                    text: qsTr("Закрыть программу")

                    color: "white"

                    opacity: close_button.hovered ? 1.0
                                                  : 0.0

                    Behavior on opacity {
                        NumberAnimation { duration: 150; easing.type: Easing.Linear }
                    }
                }

                onClicked: Qt.quit()
            }
        }

        StackView {
            id: stack_view

            anchors.top: header.bottom
            anchors.topMargin: 4

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            initialItem: MainMenu {}
        }
    }
}

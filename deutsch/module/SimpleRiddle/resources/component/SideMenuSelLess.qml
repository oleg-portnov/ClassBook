import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Drawer {
    id: side_menu

    signal sigLoadLektion(lek_num: int)

    width: parent.width * 0.7
    height: parent.height

    background: Rectangle {
        anchors.fill: parent
        color: "#006663"
    }

    Button {
        id: close_side_menu

        x: 10
        y: 10

        width: 40
        height: 40

        icon.source: "qrc:/SimpleRiddle/imports/SimpleRiddle/resources/img/close.svg"

        background: Rectangle {
            color: "#5599bb"
            anchors.fill: parent
            radius: 14
        }

        onClicked: side_menu.close()
    }

    ScrollView {
        anchors.top: close_side_menu.bottom
        anchors.topMargin: 18

        anchors.left: parent.left
        anchors.leftMargin: 9

        anchors.right: parent.right
        anchors.rightMargin: 9

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 9

        contentWidth: width

        ColumnLayout {
            spacing: 18

            anchors.fill: parent

            Repeater {
                model: 10

                delegate: Button {
                    text: qsTr("Lektion " + (index + 1))

                    Layout.fillWidth: true

                    implicitHeight: 40

                    background: Rectangle {
                        color: "#5599bb"
                        anchors.fill: parent
                        radius: 14
                    }

                    onClicked: {
                        side_menu.close()
                        side_menu.sigLoadLektion(index)
                    }
                }
            }
        }
    }
}

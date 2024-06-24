import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    property bool target_language: false

    property string text_de: ""
    property string text_ru: ""

    property int show_count: 0

    property int correctly_count: 0
    property int incorrect_count: 0

    property string part_of_speech: ""

    onText_deChanged: help_br.visible = false

    ColumnLayout {
        id: lt

        spacing: 4

        anchors.fill: parent

        Rectangle {
            id: img_rect

            Layout.fillHeight: true
            Layout.fillWidth: true

            color: "#004f77"

            radius: 14
            border.width: 0

            Button {
                id: btn_help

                anchors.right: parent.right
                anchors.rightMargin: 9

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 9

                width: 40
                height: 40

                onClicked: help_br.visible = true

                icon.source: "/img/question.svg"

                background: Rectangle {
                    color: "#5599bb"
                    anchors.fill: parent
                    radius: 14
                }
            }

            Text {
                id: part

                anchors.top: parent.top
                anchors.topMargin: 9

                anchors.horizontalCenter: parent.horizontalCenter

                text: part_of_speech

                color: "white"

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                id: info

                anchors.left: parent.left
                anchors.leftMargin: 9

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 9

                text: show_count + "/" + correctly_count + "/" + incorrect_count

                color: "white"

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Rectangle {
                id: text_br

                property int def_margin: 40

                implicitHeight: help_br.visible ? def_margin * 2 : def_margin

                implicitWidth:  help_br.visible ? text_help.implicitWidth > tr_text.implicitWidth ? text_help.implicitWidth + def_margin
                                                                                                  : tr_text.implicitWidth + def_margin
                                                : tr_text.implicitWidth + def_margin

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                color: "#003855"

                radius: 14

                Text {
                    id: tr_text

                    text: target_language ? text_de : text_ru

                    color: "white"

                    height: 20

                    anchors.top: parent.top

                    anchors.topMargin: 10

                    anchors.horizontalCenter: parent.horizontalCenter

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                Rectangle {
                    id: help_br

                    visible: true

                    color: "#6b8e23"

                    radius: 14

                    anchors.fill: parent

                    anchors.topMargin: 45
                    anchors.bottomMargin: 5
                    anchors.leftMargin: 5
                    anchors.rightMargin: 5

                    border.width: 0

                    Text {
                        id: text_help

                        text: !target_language ? text_de : text_ru

                        color: "white"

                        height: 20

                        anchors.fill: parent

                        anchors.horizontalCenter: parent.horizontalCenter

                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }
    }
}

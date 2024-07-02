import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    property bool target_language: false

    property string text_de: ""
    property string text_ru: ""

    property string part_of_speech: ""

    property int show_count: 0

    property int correctly_count: 0
    property int incorrect_count: 0

    property int def_margin: 40

    function getMinWidth() {
        return tr_text.implicitWidth + def_margin
    }

    function getMaxWidth() {
        return text_help.implicitWidth > tr_text.implicitWidth ? text_help.implicitWidth + def_margin
                                                               : getMinWidth()
    }

    function showHelp() {
        root.state = "help_show"
    }

    function hideHelp() {
        root.state = "help_hide"
    }

    function updateState() {
        hideHelp()
    }

    state: "help_hide"

    Rectangle {
        id: img_rect

        anchors.fill: parent

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

            onClicked: {
                if (root.state === "help_show") {
                    hideHelp()
                } else {
                    showHelp()
                }
            }

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

            implicitHeight: 40

            implicitWidth: help_br.visible ? getMaxWidth() : getMinWidth()

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

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }

    transitions: [
        Transition {
            from: "*"; to: "help_hide"

            ParallelAnimation {
                id: to_default_anim

                PropertyAnimation { target: text_br; properties: "implicitHeight"; to: 40;            duration: 100 }
                PropertyAnimation { target: text_br; properties: "implicitWidth";  to: getMinWidth(); duration: 100 }
                PropertyAnimation { target: help_br; properties: "opacity";        to: 0.0;           duration: 100 }
                ColorAnimation    { target: help_br; properties: "color";          to: "#003855";     duration: 100 }

                PropertyAnimation { target: text_help; properties: "opacity"; to: 0.0; duration: 100 }
            }
        },
        Transition {
            from: "*"; to: "help_show"

            ParallelAnimation {
                id: to_pressed_anim

                PropertyAnimation { target: text_br; properties: "implicitHeight"; to: 80;            duration: 300 }
                PropertyAnimation { target: text_br; properties: "implicitWidth";  to: getMaxWidth(); duration: 300 }
                PropertyAnimation { target: help_br; properties: "opacity";        to: 1.0;           duration: 300 }
                ColorAnimation    { target: help_br; properties: "color";          to: "#6b8e23";     duration: 300 }

                PropertyAnimation { target: text_help; properties: "opacity"; to: 1.0; duration: 600 }
            }
        }
    ]

    states: [
        State {
            name: "help_hide"
            PropertyChanges { target: help_br; visible: false }
            PropertyChanges { target: help_br; opacity: 0.0 }
            PropertyChanges { target: text_help; opacity: 0.0 }
        },
        State {
            name: "help_show"
            PropertyChanges { target: help_br; height: text_br.implicitHeight }
            PropertyChanges { target: help_br; width: text_br.implicitWidth }
            PropertyChanges { target: help_br; visible: true }
        }
    ]
}

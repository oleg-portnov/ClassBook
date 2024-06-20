import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Drawer {
    id: side_menu

    signal sigLoadLektion(lek_num: int)

    property int btn_spacing: 18

    width: parent.width * 0.7
    height: parent.height

    background: Rectangle {
        anchors.fill: parent
        color: "#006663"
    }

    Item {
        id: side_menu_content

        anchors.fill: parent

        BtnCloseSideMenu {
            id: close_side_menu

            x: 10
            y: 10
        }

        ScrollView {
            id: sa

            anchors.top: close_side_menu.bottom
            anchors.topMargin: btn_spacing

            anchors.left: parent.left
            anchors.leftMargin: 9

            anchors.right: parent.right
            anchors.rightMargin: 9

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 9

            contentWidth: width

            ColumnLayout {
                id: menu_lt

                spacing: btn_spacing

                anchors.fill: parent

                LekitonRepeater {
                    id: lek_repeater
                }
            }
        }
    }
}

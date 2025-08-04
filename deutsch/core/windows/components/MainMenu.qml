import QtQuick
import QtQuick.Layouts

Item {
    FocusScope {
        id: main_btn_focus_scope

        anchors.fill: parent

        focus: true

        Component.onCompleted: btn_play.forceActiveFocus()

        ColumnLayout {
            anchors.verticalCenter: parent.verticalCenter

            anchors.left: parent.left
            anchors.right: parent.right

            spacing: 14

            BtnMainMenu {
                id: btn_play
                btn_text: qsTr("Play")
                onPressed: stack_view.push("LoadingPage.qml");

                KeyNavigation.down: btn_choose
            }

            BtnMainMenu {
                id: btn_choose
                btn_text: qsTr("Сhoose a riddle")

                KeyNavigation.up: btn_play
                KeyNavigation.backtab: btn_play
            }

            BtnMainMenu {
                id: btn_statistics
                btn_text: qsTr("Statistics")

                KeyNavigation.up: btn_choose
            }
        }
    }
}

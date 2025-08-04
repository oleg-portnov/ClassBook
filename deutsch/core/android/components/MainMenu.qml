import QtQuick
import QtQuick.Layouts

Item {
    ColumnLayout {
        anchors.verticalCenter: parent.verticalCenter

        anchors.left: parent.left
        anchors.right: parent.right

        spacing: 14

        BtnMainMenu {
            id: btn_play
            btn_text: qsTr("Play")
            onPressed: stack_view.push("LoadingPage.qml");
        }

        BtnMainMenu {
            id: btn_choose
            btn_text: qsTr("Сhoose a riddle")
        }

        BtnMainMenu {
            id: btn_statistics
            btn_text: qsTr("Statistics")
        }
    }
}

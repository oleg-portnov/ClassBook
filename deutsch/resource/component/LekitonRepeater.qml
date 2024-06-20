import QtQuick
import QtQuick.Layouts

Repeater {
    id: root

    model: 10

    delegate: SimpleBtn {

        btn_text: qsTr("Lektion " + (index + 1))

        onClicked: {
            side_menu.close()
            sigLoadLektion(index)
        }
    }
}

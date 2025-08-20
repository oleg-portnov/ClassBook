import QtQuick
import QtQuick.Controls

Button {
    id: root
    
    focusPolicy: Qt.ClickFocus

    width: btn_text.contentWidth + btn_text.leftPadding + btn_text.rightPadding

    hoverEnabled: true

    background: Rectangle {
        color: root.hovered ? "#7a0f0f"
                            : "transparent"

        Behavior on color { ColorAnimation { duration: 150; easing.type: Easing.Linear } }

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
        
        opacity: root.hovered ? 1.0
                              : 0.0
        
        Behavior on opacity { NumberAnimation { duration: 150; easing.type: Easing.Linear } }
    }
    
    onClicked: Qt.quit()
}

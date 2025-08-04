import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Button {
    id: root

    property alias btn_text: btn_txt.text
    
    Layout.alignment: Qt.AlignHCenter
    
    contentItem: Text {
        id: btn_txt

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        
        font.weight: Font.Medium
        font.pointSize: 12
        font.family: "Times New Roman"
        
        color: "white"
        
        padding: 6
    }
    
    background: Rectangle {
        color: root.down ? "#0066cc" : "#3399ff"
        radius: 12
    }
}

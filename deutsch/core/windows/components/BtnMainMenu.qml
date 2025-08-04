import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Button {
    id: root

    property alias btn_text: btn_txt.text

    Layout.alignment: Qt.AlignHCenter

    hoverEnabled: true

    transformOrigin: Item.Center

    // TODO: broken pixels in software rhi
    // layer.enabled: true
    // layer.smooth: true

    scale: root.pressed ? 0.90
                        : root.hovered ? 1.1
                                       : 1.0

    Behavior on scale {
        NumberAnimation { duration: 300; easing.type: Easing.OutCubic }
    }

    contentItem: Text {
        id: btn_txt

        // TODO: broken pixels in software rhi
        // renderType: Text.CurveRendering
        // smooth: true

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.weight: Font.Medium
        font.pointSize: 12
        font.family: "Times New Roman"

        color: "white"

        padding: 6
    }
    
    background: Rectangle {
        color:  root.pressed ? "#0066cc"
                             : root.hovered || root.focus ? "#47a3ff"
                                                          : "#2d89e5"
        radius: 12

        border.width: 2

        border.color: root.focus ? "#96c4f2"
                                 : "#287bce"

        // TODO: broken pixels in software rhi
        // antialiasing: true
    }
}

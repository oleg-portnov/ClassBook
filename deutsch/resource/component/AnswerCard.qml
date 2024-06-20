import QtQuick

Rectangle {
    id: root

    signal sigCorrect()
    signal sigIncorrect()

    property bool was_attempt: false

    height: 40

    width: text_item.implicitWidth + 40

    z: is_correct_answer ? 1 : 0

    radius: 14
    border.color: "#00314b"
    border.width: 2

    color: "#1c77a4"

    MouseArea {
        id: ma

        anchors.fill: parent

        onPressed: {
            if (!was_attempt)
                was_attempt = true
            else
                return

            if (is_correct_answer)
                sigCorrect()
            else
                sigIncorrect()
        }
    }

    Text {
        id: text_item

        color: "white"

        font.weight: 600
        font.letterSpacing: 1

        anchors.centerIn: parent
        text: element_text
    }
}

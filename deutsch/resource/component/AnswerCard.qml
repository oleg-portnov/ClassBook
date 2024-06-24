import QtQuick

Rectangle {
    id: root

    signal sigCorrect()
    signal sigIncorrect()

    property bool was_attempt: false
    property int lr_margins: 40

    height: 40

    width: card_text.implicitWidth + lr_margins

    z: is_correct_answer ? 1 : 0

    radius: 14

    border.color: "#00314b"
    border.width: 2

    color: "#1c77a4"

    MouseArea {
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
        id: card_text

        anchors.centerIn: parent

        text: element_text

        color: "white"

        font.weight: 600
        font.letterSpacing: 1
    }
}

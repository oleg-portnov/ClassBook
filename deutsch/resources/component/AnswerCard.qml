import QtQuick

Rectangle {
    id: root

    signal sigCorrect()
    signal sigIncorrect()

    property bool is_correct_answer: false

    property bool was_attempt: false

    property int lr_margins: 40

    property alias answer_text: card_text.text

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
            if (was_attempt || flow_view.correct_word_find)
                return

            if (!was_attempt)
                was_attempt = true

            if (is_correct_answer) {
                flow_view.correct_word_find = true
                correct_animation.start()
                sigCorrect()
            } else {
                incorrect_animation.start()
                sigIncorrect()
            }
        }
    }

    Text {
        id: card_text

        anchors.centerIn: parent

        color: "white"

        font.weight: 600
        font.letterSpacing: 1
    }

    ParallelAnimation {
        id: correct_animation

        PropertyAnimation {
            id: shake_animation

            target: root

            property: "scale"

            from: 1.0
            to: 1.1

            duration: 300
            easing.type: Easing.InOutBack
            loops: 2
        }

        PropertyAnimation {
            id: gradient_animation

            target: root

            property: "color"

            easing.type: Easing.Linear

            duration: 300

            from: "#1c77a4"
            to: "#00997f"
        }
    }

    ParallelAnimation {
        id: incorrect_animation

        PropertyAnimation {
            id: decrease_animation

            target: root

            property: "scale"

            from: 1.0
            to: 0.8

            duration: 300
            easing.type: Easing.InOutBack
        }

        PropertyAnimation {
            id: to_red_animation

            target: root

            property: "color"

            easing.type: Easing.Linear

            duration: 300

            from: "#1c77a4"
            to: "#b33a00"
        }
    }
}

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import SimpleRiddle

Rectangle {
    id: root

    color: "#004466"

    radius: 4

    function updateLayout() {
        if (width < height) {
            h_lt.visible = false
            w_lt.visible = true
        } else {
            w_lt.visible = false
            h_lt.visible = true
        }
    }

    onHeightChanged: updateLayout()
    onWidthChanged: updateLayout()

    LessonMediator {
        id: lesson_mediator
    }

    SideMenuSelLess {
        id: side_menu

        onSigLoadLektion: (lek_num) => {
            lesson_mediator.selectLesson(lek_num)
            flow_view.correct_word_find = false;
            card.updateState()
            lesson_mediator.updateWord()
        }
    }

    Timer {
        id: timer_update_card

        interval: 2500

        repeat: false

        onTriggered: {
            flow_view.correct_word_find = false
            card.updateState()
            lesson_mediator.updateWord()
        }
    }

    Button {
        id: open_side_menu

        x: 10
        y: 10
        width: 40
        height: 40

        z: 1

        onClicked: side_menu.open()

        icon.name: "menu"
        icon.source: "qrc:/SimpleRiddle/imports/SimpleRiddle/resources/img/menu.svg"

        background: Rectangle {
            color: "#5599bb"
            anchors.fill: parent
            radius: 14
        }
    }

    GridLayout {
        id: w_lt

        columns: 1

        visible: true

        anchors.fill: parent
        anchors.margins: 4

        LayoutItemProxy { target: card }
        LayoutItemProxy { target: answers }
    }

    GridLayout {
        id: h_lt

        columns: 2

        visible: false

        anchors.fill: parent
        anchors.margins: 4

        LayoutItemProxy { target: card }
        LayoutItemProxy { target: answers }
    }

    WordCard {
        id: card

        Component.onCompleted: lesson_mediator.init()

        Layout.fillHeight: true
        Layout.fillWidth: true

        target_language: !lesson_mediator.answers_model.need_tr

        text_de: lesson_mediator.cur_cord.de_text
        text_ru: lesson_mediator.cur_cord.ru_text

        part_of_speech: lesson_mediator.cur_cord.part_of_speech_text

        show_count: lesson_mediator.cur_cord.views

        correctly_count: lesson_mediator.cur_cord.correct
        incorrect_count: lesson_mediator.cur_cord.incorrect
    }

    Rectangle {
        id: answers

        Layout.fillHeight: true
        Layout.fillWidth: true

        color: "#004f77"

        radius: 14

        border.color: "#003755"
        border.width: 1

        Flow {
            id: flow_view

            property bool correct_word_find: false

            spacing: 9

            width: parent.width * 0.8

            anchors.verticalCenter: answers.verticalCenter
            anchors.horizontalCenter: answers.horizontalCenter

            Repeater {
                id: card_repeater

                model: lesson_mediator.answers_model

                AnswerCard {
                    answer_text: displayed_text
                    is_correct_answer: is_correct

                    onSigCorrect: {
                        lesson_mediator.userGuessed()
                        timer_update_card.start()
                    }

                    onSigIncorrect: lesson_mediator.userNotGuess()
                }
            }
        }
    }
}

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import SimpleRiddle

Rectangle {
    id: root_window

    property string cur_id: ""

    color: "#004466"

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

    SideMenuSelLess {
        id: side_menu

        onSigLoadLektion: (lek_num) => {
            LessonMediator.selectLesson(lek_num)
            flow_view.correct_word_find = false;
            card.updateState()
            LessonMediator.updateWord()
        }
    }

    Timer {
        id: timer_update_card

        interval: 2500

        repeat: false

        onTriggered: {
            flow_view.correct_word_find = false
            card.updateState()
            LessonMediator.updateWord()
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

        Component.onCompleted: LessonMediator.init()

        Layout.fillHeight: true
        Layout.fillWidth: true

        target_language: !LessonMediator.answers_model.need_tr

        text_de: LessonMediator.cur_cord.de_text
        text_ru: LessonMediator.cur_cord.ru_text

        part_of_speech: LessonMediator.cur_cord.part_of_speech_text

        show_count: LessonMediator.cur_cord.views

        correctly_count: LessonMediator.cur_cord.correct
        incorrect_count: LessonMediator.cur_cord.incorrect
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

                model: LessonMediator.answers_model

                AnswerCard {
                    answer_text: displayed_text
                    is_correct_answer: is_correct

                    onSigCorrect: {
                        LessonMediator.userGuessed()
                        timer_update_card.start()
                    }

                    onSigIncorrect: LessonMediator.userNotGuess()
                }
            }
        }
    }
}

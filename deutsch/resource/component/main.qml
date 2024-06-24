import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import classbook

Window {
    id: root_window

    property int save_count: 0
    property int save_count_trig: 5

    property string cur_id: ""

    visible: true

    color: "#004466"

    function cardUpdated() {
        ++save_count;

        if (save_count === save_count_trig) {
            cards_model.saveLection()
            save_count = 0
        }
    }

    function correctAnswer(index) {
        var item = card_repeater.itemAt(index);
        if (item !== undefined) {
            cards_model.increaseCorrectlyCount(cards_model.indexById(cur_id))
            shake_animation.target = item;
            gradient_animation.target = item;
            good_animation.start();
        }
    }

    function incorrectAnswer(index) {
        var item = card_repeater.itemAt(index);
        if (item !== undefined) {
            cards_model.increaseIncorrectCount(cards_model.indexById(cur_id))
            decrease_animation.target = item;
            to_red_animation.target = item;
            incorrect_animation.start();
        }
    }

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

    Component.onCompleted: {
        if (Qt.platform.os === "linux") {
            width = 400
            height = 600
        }
    }

    Drawer {
        id: side_menu

        signal sigLoadLektion(lek_num: int)

        width: parent.width * 0.7
        height: parent.height

        background: Rectangle {
            anchors.fill: parent
            color: "#006663"
        }

        onSigLoadLektion: (lek_num) => {
            cards_model.loadLektion(lek_num)
            card.updateCard()
        }

        Button {
            id: close_side_menu

            x: 10
            y: 10

            width: 40
            height: 40

            icon.source: "/img/close.svg"

            background: Rectangle {
                color: "#5599bb"
                anchors.fill: parent
                radius: 14
            }

            onClicked: side_menu.close()
        }

        ScrollView {
            anchors.top: close_side_menu.bottom
            anchors.topMargin: 18

            anchors.left: parent.left
            anchors.leftMargin: 9

            anchors.right: parent.right
            anchors.rightMargin: 9

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 9

            contentWidth: width

            ColumnLayout {
                spacing: 18

                anchors.fill: parent

                Repeater {
                    model: 6

                    delegate: Button {
                        text: qsTr("Lektion " + (index + 1))

                        Layout.fillWidth: true

                        implicitHeight: 40

                        background: Rectangle {
                            color: "#5599bb"
                            anchors.fill: parent
                            radius: 14
                        }

                        onClicked: {
                            side_menu.close()
                            side_menu.sigLoadLektion(index)
                        }
                    }
                }
            }
        }
    }

    CardsModel {
        id: cards_model

        Component.onCompleted: loadRandomCards()

        onSigCardsChanged: {
            card.updateCard()
            cardUpdated()
        }

        function loadLektion(lek_num) {
            setLection(lek_num)
            card.updateCard()
        }
    }

    Timer {
        id: timer_update_card

        interval: 2500

        repeat: false

        onTriggered: {
            card.updateCard()
            cardUpdated()
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
        icon.source: "/img/menu.svg"

        background: Rectangle {
            color: "#5599bb"
            anchors.fill: parent
            radius: 14
        }
    }

    ListModel {
        id: answers_model

        ListElement {
            element_text: ""
            is_correct_answer: false
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

        Layout.fillHeight: true
        Layout.fillWidth: true

        function updateCard () {
            var is_target_language = Math.random() < 0.5
            target_language = is_target_language

            var index = cards_model.getRandomIndex()

            cur_id = cards_model.getId(index)

            card.text_ru = cards_model.getTextRu(index)
            card.text_de = cards_model.getTextDe(index)

            card.part_of_speech = cards_model.getPartOfSpeech(index)

            cards_model.increaseShowingCount(index)
            card.show_count = cards_model.getShowingCount(index)

            var random_indx = []
            var random_item_count = Math.floor(Math.random() * 3) + 4

            for (var ii = 0; ii < random_item_count; ii++) {
                var rndm_index = cards_model.getRandomIndex()
                if (!random_indx.includes(rndm_index) && rndm_index !== index) {
                    random_indx.push(rndm_index)
                }
            }

            answers_model.clear()

            for (var jj = 0; jj < random_indx.length; jj++) {
                var randomIndex = random_indx[jj]
                answers_model.append({element_text: is_target_language ? cards_model.getTextRu(randomIndex)
                                                                       : cards_model.getTextDe(randomIndex),
                                      is_correct_answer: false})
            }

            var random_insert_indx = Math.floor(Math.random() * (answers_model.count + 1));
            answers_model.insert(random_insert_indx, {element_text: is_target_language ? cards_model.getTextRu(index)
                                                                                       : cards_model.getTextDe(index),
                                                      is_correct_answer: true})
        }
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

            spacing: 9

            width: parent.width * 0.8

            anchors.verticalCenter: answers.verticalCenter
            anchors.horizontalCenter: answers.horizontalCenter

            Repeater {
                id: card_repeater

                model: answers_model

                AnswerCard {
                    onSigCorrect: {
                        correctAnswer(index)
                        timer_update_card.start()
                    }

                    onSigIncorrect: incorrectAnswer(index)
                }
            }
        }
    }

    ParallelAnimation {
        id: good_animation

        PropertyAnimation {
            id: shake_animation

            property: "scale"

            from: 1.0
            to: 1.1

            duration: 300
            easing.type: Easing.InOutBack
            loops: 2
        }

        PropertyAnimation {
            id: gradient_animation

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

            property: "scale"

            from: 1.0
            to: 0.8

            duration: 300
            easing.type: Easing.InOutBack
        }

        PropertyAnimation {
            id: to_red_animation

            property: "color"

            easing.type: Easing.Linear

            duration: 300

            from: "#1c77a4"
            to: "#b33a00"
        }
    }
}

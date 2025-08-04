set(PLUGIN_NAME SimpleRiddle)
set(PLUGIN_VERSION 1.0)

qt_add_library(${PLUGIN_NAME} STATIC)

set_target_properties(${PLUGIN_NAME} PROPERTIES AUTOMOC ON)
target_link_libraries(${PLUGIN_NAME} PRIVATE Qt6::Quick)

set(SOURCES
    src/card/Word.cpp
    src/mediators/LessonMediator.cpp
    src/models/AnswersModel.cpp
    src/models/CardStore.cpp
)

set(HEADERS
    include/card/LessonFwd.h
    include/card/PartOfSpeechFwd.h
    include/card/Word.h
    include/mediators/LessonMediator.h
    include/models/AnswersModel.h
    include/models/CardStore.h
)

set(RESOURCES
    resources/cards/cards.qrc
    resources/cards/lektion_1
    resources/cards/lektion_2
    resources/cards/lektion_3
    resources/cards/lektion_4
    resources/cards/lektion_5
    resources/cards/lektion_6
    resources/cards/lektion_7
    resources/cards/lektion_8
    resources/cards/lektion_9
    resources/cards/lektion_10
)

list(APPEND MODULE_ASSETS
    resources/img/question.svg
    resources/img/close.svg
    resources/img/menu.svg
)

list(APPEND MODULE_QML_PRIVATE_FILES
    resources/component/AnswerCard.qml
    resources/component/WordCard.qml
    resources/component/SideMenuSelLess.qml
)

list(APPEND MODULE_QML_FILES SimpleRiddleMainItem.qml ${MODULE_QML_PRIVATE_FILES}
)

set_source_files_properties(${MODULE_QML_PRIVATE_FILES} PROPERTIES
    QT_QML_INTERNAL_TYPE  TRUE
)

qt_add_qml_module(${PLUGIN_NAME}
    URI SimpleRiddle
    VERSION
        ${PLUGIN_VERSION}
    RESOURCE_PREFIX
        /SimpleRiddle/imports
    QML_FILES
        ${MODULE_QML_FILES}
    RESOURCES
        ${MODULE_ASSETS}
        ${RESOURCES}
    SOURCES
        plugin.cpp
        ${SOURCES}
        ${HEADERS}
)

target_precompile_headers(${PLUGIN_NAME} PUBLIC pch.h)

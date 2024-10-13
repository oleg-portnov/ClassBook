cmake_minimum_required(VERSION 3.16)

project(deutsch VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_compile_options(-fno-exceptions)
add_compile_options(-fno-rtti)

find_package(Qt6 6.8 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

set(SOURCES
    main.cpp
    card/Word.cpp
    mediators/LessonMediator.cpp
    models/AnswersModel.cpp
    models/CardStore.cpp
)

set(HEADERS
    card/LessonFwd.h
    card/PartOfSpeechFwd.h
    card/Word.h
    card/WordFwd.h
    common/utils.h
    mediators/LessonMediator.h
    models/AnswersModel.h
    models/CardStore.h
)

set(RESOURCES
    resources/cards/cards.qrc
    resources/component/component.qrc
    resources/img/img.qrc
)

qt_add_executable(ClassBook
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

qt_add_qml_module(ClassBook
    URI deutsch
    VERSION 1.0
)

target_link_libraries(ClassBook
    PRIVATE Qt6::Quick
)

install(TARGETS ClassBook
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

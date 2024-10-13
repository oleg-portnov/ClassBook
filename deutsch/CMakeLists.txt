cmake_minimum_required(VERSION 3.16)

project(deutsch VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.7)

set(SOURCES
    main.cpp
    models/CardsModel.cpp
)

set(HEADERS
    card/WordCard.h
    models/CardsModel.h
)

set(RESOURCES
    resources/component/component.qrc
    resources/img/img.qrc
    resources/cards/cards.qrc
)

qt_add_executable(ClassBook
    ${SOURCES}
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

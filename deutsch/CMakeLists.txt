cmake_minimum_required(VERSION 3.16)

project(deutsch VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.7)

set(SOURCES
    models/CardsModel.cpp
)

set(HEADERS
    models/CardsModel.h
    models/WordCard.h
)

set(RESOURCE
    resource/component/component.qrc
    resource/img/img.qrc
    resource/cards/cards.qrc
)

qt_add_executable(ClassBook
    main.cpp
    ${SOURCES}
    ${HEADERS}
    ${RESOURCE}
)

qt_add_qml_module(ClassBook
    URI deutsch
    VERSION 1.0
)

target_link_libraries(ClassBook
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)

install(TARGETS ClassBook
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

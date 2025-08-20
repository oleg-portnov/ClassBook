cmake_minimum_required(VERSION 3.25.1)

project(GermanTextbook
    VERSION 0.1
    DESCRIPTION "An application to assist in learning the German language."
    HOMEPAGE_URL "https://github.com/oleg-portnov/ClassBook"
    LANGUAGES CXX)

set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")
endif()

add_compile_options(-fno-exceptions)
add_compile_options(-fno-rtti)

find_package(Qt6 6.9 COMPONENTS Quick QuickControls2 REQUIRED)

qt_standard_project_setup(REQUIRES 6.9)

if(ANDROID)
    set(APPEND SOURCES
        core/android/src/AndroidApplication.cpp
        core/android/src/AndroidApplicationStyle.cpp
        core/android/src/AndroidEnvironmentManager.cpp
    )

    set(APPEND HEADERS
        core/android/include/AndroidApplication.h
        core/android/include/AndroidApplicationStyle.h
        core/android/include/AndroidEnvironmentManager.h
    )
elseif(UNIX)
    set(APPEND SOURCES
        core/linux/src/LinuxApplication.cpp
        core/linux/src/LinuxApplicationStyle.cpp
        core/linux/src/LinuxEnvironmentManager.cpp
    )

    set(APPEND HEADERS
        core/linux/include/LinuxApplication.h
        core/linux/include/LinuxApplicationStyle.h
        core/linux/include/LinuxEnvironmentManager.h
    )
elseif(WIN32)
    set(PLATFORM_SOURCES
        core/windows/src/WindowsApplication.cpp
        core/windows/src/WindowsApplicationStyle.cpp
        core/windows/src/WindowsEnvironmentManager.cpp
    )

    set(PLATFORM_HEADERS
        core/windows/include/WindowsApplication.h
        core/windows/include/WindowsApplicationStyle.h
        core/windows/include/WindowsEnvironmentManager.h
    )
endif()

list(APPEND COMMON_SOURCES
    core/common/src/Application.cpp
    core/common/src/ApplicationStyle.cpp
    core/common/src/EnvironmentManager.cpp
)

list(APPEND COMMON_HEADERS
    core/common/include/Application.h
    core/common/include/ApplicationStyle.h
    core/common/include/EnvironmentManager.h
)

qt_add_executable(ClassBook
    main.cpp
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
    ${PLATFORM_SOURCES}
    ${PLATFORM_HEADERS}
)

set(COMMON_QML_FILES
    core/common/components/main.qml
)

if(ANDROID)
    set(PLATFORM_QML_FILES
        core/android/components/MainMenu.qml
        core/android/components/BtnMainMenu.qml
        core/android/components/LoadingPage.qml
    )
elseif(WIN32)
    set(PLATFORM_QML_FILES
        core/windows/components/MainMenu.qml
        core/windows/components/BtnMainMenu.qml
        core/windows/components/LoadingPage.qml
        core/windows/components/WindowsCloseBtn.qml
    )
elseif(UNIX)
    set(PLATFORM_QML_FILES
        core/linux/components/MainMenu.qml
        core/linux/components/BtnMainMenu.qml
        core/linux/components/LoadingPage.qml
    )
endif()

qt_add_qml_module(ClassBook
    URI CoreModule
    VERSION 1.0
    RESOURCE_PREFIX /CoreModule/imports
    QML_FILES ${COMMON_QML_FILES}
        ${PLATFORM_QML_FILES}

)

target_compile_options(ClassBook PRIVATE
    $<$<CONFIG:Release>:-ffunction-sections -fdata-sections>
)

target_link_options(ClassBook PRIVATE
    $<$<CONFIG:Release>:-Wl,--gc-sections>
)

# add_subdirectory(lib/CommonUtils)
add_subdirectory(module/SimpleRiddle)
# add_subdirectory(module/SideMenu)

target_link_libraries(ClassBook
    PRIVATE Qt6::Quick
    Qt6::QuickControls2
    SimpleRiddleplugin
#     # SideMenuplugin
)

# TODO: select best performance
# set_target_properties(ClassBook
#     PROPERTIES
#         QT_QMLCACHEGEN_ARGUMENTS "--only-bytecode" or "--direct-calls"
# )

install(TARGETS ClassBook
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

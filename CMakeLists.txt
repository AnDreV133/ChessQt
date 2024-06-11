cmake_minimum_required(VERSION 3.5)

project(kursackoop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp



)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(kursackoop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources/black/B.png
        resources/black/K.png
        resources/black/H.png
        resources/black/P.png
        resources/black/Q.png
        resources/black/R.png
        resources/white/B.png
        resources/white/K.png
        resources/white/H.png
        resources/white/P.png
        resources/white/Q.png
        resources/white/R.png

        settings/settingsjson.h

        gamemode/pvspoffline.h
        gamemode/gamemode.h
        gamemode/chesslogger.h

        figure/behavior/actionbehavior.h
        figure/behavior/alldirectionsaction.h
        figure/behavior/noaction.h
        figure/behavior/pawnaction.h
        figure/behavior/horseaction.h
        figure/behavior/straightaction.h
        figure/behavior/diagonalaction.h
        figure/behavior/allslidedirectionaction.h

        figure/nonefigure.h
        figure/figure.h
        figure/king.h
        figure/rook.h
        figure/bishop.h
        figure/pawn.h
        figure/queen.h
        figure/horse.h

        enums.h
        json.hpp
        utils.h

        window/windowholder.h

        window/settingswindow.h
        window/settingswindow.cpp
        window/settingswindow.ui

        window/menuwindow.h
        window/menuwindow.cpp
        window/menuwindow.ui

        window/gamemodesmenuwindow.h
        window/gamemodesmenuwindow.cpp
        window/gamemodesmenuwindow.ui

        window/gamewindow.h
        window/gamewindow.cpp
        window/gamewindow.ui

        window/windialog.h

        scene/highlitegraphicitem.h
        scene/cellgraphicitem.h
        scene/chessscene.h
        scene/figuregraphicitem.h

        figuresimage.qrc

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET kursackoop APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(kursackoop SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(kursackoop
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(kursackoop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.kursackoop)
endif()
set_target_properties(kursackoop PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS kursackoop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(kursackoop)
endif()

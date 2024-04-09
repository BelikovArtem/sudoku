cmake_minimum_required(VERSION 3.16)

project(sudoku VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appsudoku
    main.cpp
)

qt_add_qml_module(appsudoku
    URI sudoku
    VERSION 1.0
    QML_FILES Main.qml
    RESOURCES views/images/background.png views/images/profile.png views/images/settings.png views/images/SudokuGenius.png views/images/sudokuIcon.png views/images/exit.png views/images/leaderboard.png views/images/newGame.png
    SOURCES models/cell.h models/cell.cpp
    SOURCES models/game.h models/game.cpp
    SOURCES models/cell.cpp models/cell.h models/game.cpp models/game.h
    QML_FILES views/GameWindow.qml
    QML_FILES
    SOURCES view-models/clientviewmodel.h view-models/clientviewmodel.cpp
    QML_FILES views/DifficultyLevelWindow.qml
    QML_FILES views/DifficultyLevelWindow.qml
    RESOURCES views/images/difficultyHigh.png views/images/difficultyLow.png views/images/difficultyMedium.png views/images/selectDifficulty.png
    RESOURCES views/images/cancel.png views/images/confirm.png
    QML_FILES views/MainWindow.qml
    RESOURCES views/images/gameuiprojectHigh.png views/images/gameuiprojectLow.png views/images/gameuiprojectMedium.png
    RESOURCES views/images/labelDifficulty.png
    QML_FILES views/SudokuGrid.qml
    QML_FILES
    QML_FILES views/CustomButton.qml
    SOURCES view-models/serverviewmodel.h view-models/serverviewmodel.cpp
    SOURCES models/user.h models/user.cpp
    QML_FILES views/LoginWindow.qml
    QML_FILES views/SettingsWindow.qml
    QML_FILES views/DataChangeWindow.qml
    QML_FILES views/SudokuGeniusLabel.qml
    QML_FILES views/CustomPopup.qml
    QML_FILES views/LeaderboardWindow.qml

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appsudoku PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appsudoku
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appsudoku
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appsudoku
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

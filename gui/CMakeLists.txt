cmake_minimum_required(VERSION 2.6)
project(GUI_LogicToolbox)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
set ( SOURCES
    main.cpp
    node.cpp
    graphwidget.cpp
    edge.cpp
    mainwindow.cpp

)
set(HEADERS
    node.h
    edge.h
    graphwidget.h
    mainwindow.h

)
set (FORMS
    mainwindow.ui
    
)

qt5_wrap_ui(FORM_H ${FORMS})

# Tell CMake to create the helloworld executable




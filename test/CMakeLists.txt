
# Specify .cpp files
set(TARGET_NAME LogicToolbox)
set(MODULE_NAME ModuleOne)
set(SRC hello.cpp)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_AUTOUIC ON)
# Build an executable from main.cpp and all specified source files
include_directories(../../include/${MODULE_NAME})
add_executable(${TARGET_NAME} main.cpp ${SRC} ../src/Parser/Token.cpp ../include/Token.h ../src/Parser/Expression.cpp ../include/Expression.h ../src/Evaluator/CoreEvaluator.cpp ../include/CoreEvaluator.h ../src/Evaluator/ResultTree.cpp ../include/ResultTree.h
        ../src/Universe/Universe.cpp ../include/Universe.h ../src/Universe/Variable.cpp ../include/Variable.h ../src/Universe/World.cpp ../include/World.h ../src/Core/Operators.cpp ../include/Operators.h ../src/Graph/Graph.cpp ../include/Graph.h
        ../gui/edge.cpp ../gui/node.cpp  ../gui/graphwidget.cpp ../gui/node.h ../gui/edge.h ../gui/graphwidget.h ../gui/mainwindow.h ../gui/mainwindow.cpp ../gui/mainwindow.ui ../gui/BarWidget.cpp ../gui/BarWidget.h)
target_link_libraries(${TARGET_NAME} ${LIBRARIES} gvc cgraph cdt)

# Build a library from all specified source files
find_package (Qt5Widgets REQUIRED)

add_library(${TARGET_NAME}-lib ${SRC})
target_link_libraries(${TARGET_NAME}-lib ${LIBRARIES} gvc cgraph cdt)
set_target_properties(${TARGET_NAME}-lib PROPERTIES OUTPUT_NAME LogicToolbox)
target_link_libraries (LogicToolbox Qt5::Widgets)
# vim:ft=cmake



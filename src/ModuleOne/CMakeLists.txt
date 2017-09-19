
# Specify .cpp files
set(TARGET_NAME LogicToolbox)
set(MODULE_NAME ModuleOne)
set(SRC hello.cpp)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build an executable from main.cpp and all specified source files
include_directories(../../include/${MODULE_NAME})
add_executable(${TARGET_NAME} main.cpp ${SRC} ../Parser/Token.cpp ../../include/Token.h ../Parser/Expression.cpp ../../include/Expression.h ../Evaluator/CoreEvaluator.cpp ../../include/CoreEvaluator.h ../Evaluator/ResultTree.cpp ../../include/ResultTree.h
        ../Universe/Universe.cpp ../../include/Universe.h ../Universe/Variable.cpp ../../include/Variable.h ../Universe/World.cpp ../../include/World.h ../Core/Operators.cpp ../../include/Operators.h ../Graph/Graph.cpp ../../include/Graph.h)
target_link_libraries(${TARGET_NAME} ${LIBRARIES} gvc cgraph cdt)

# Build a library from all specified source files
# This is required for using googletest
add_library(${TARGET_NAME}-lib ${SRC})
target_link_libraries(${TARGET_NAME}-lib ${LIBRARIES} gvc cgraph cdt)
set_target_properties(${TARGET_NAME}-lib PROPERTIES OUTPUT_NAME LogicToolbox)

# vim:ft=cmake



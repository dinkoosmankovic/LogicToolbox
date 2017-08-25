
# Specify .cpp files
set(TARGET_NAME LogicToolbox)
set(MODULE_NAME ModuleOne)
set(SRC hello.cpp)

# Build an executable from main.cpp and all specified source files
include_directories(../../include/${MODULE_NAME})
add_executable(${TARGET_NAME} main.cpp ${SRC} ../Parser/Token.cpp ../Parser/Token.h ../Parser/Expression.cpp ../Parser/Expression.h ../Evaluator/CoreEvaluator.cpp ../Evaluator/CoreEvaluator.h ../Evaluator/ResultTree.cpp ../Evaluator/ResultTree.h
        ../Universe/Universe.cpp ../Universe/Universe.h ../Universe/Variable.cpp ../Universe/Variable.h ../Universe/World.cpp ../Universe/World.h ../Operators.cpp ../Operators.h)
target_link_libraries(${TARGET_NAME} ${LIBRARIES})

# Build a library from all specified source files
# This is required for using googletest
add_library(${TARGET_NAME}-lib ${SRC})
target_link_libraries(${TARGET_NAME}-lib ${LIBRARIES})
set_target_properties(${TARGET_NAME}-lib PROPERTIES OUTPUT_NAME LogicToolbox)

# vim:ft=cmake



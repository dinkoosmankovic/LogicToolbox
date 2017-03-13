
# Specify .cpp files
set(TARGET_NAME LogicToolbox)
set(MODULE_NAME ModuleOne)
set(SRC hello.cpp)

# Build an executable from main.cpp and all specified source files
include_directories(../../include/${MODULE_NAME})
add_executable(${TARGET_NAME} main.cpp ${SRC})
target_link_libraries(${TARGET_NAME} ${LIBRARIES})

# Build a library from all specified source files
# This is required for using googletest
add_library(${TARGET_NAME}-lib ${SRC})
target_link_libraries(${TARGET_NAME}-lib ${LIBRARIES})
set_target_properties(${TARGET_NAME}-lib PROPERTIES OUTPUT_NAME LogicToolbox)

# vim:ft=cmake



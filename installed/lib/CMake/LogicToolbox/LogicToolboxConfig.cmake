# - Config file for 'LogicToolbox' package
# It defines the following variables
#  LOGICTOOLBOX_INCLUDE_DIRS - include directories
#  LOGICTOOLBOX_LIBRARIES    - libraries to link against

# Include directory
set(LOGICTOOLBOX_INCLUDE_DIRS "/home/infloop/Documents/LogicToolbox/installed/include")

# Import the exported targets
include("/home/infloop/Documents/LogicToolbox/installed/lib/CMake/LogicToolbox/LogicToolboxTargets.cmake")

# Set the expected library variable
set(LOGICTOOLBOX_LIBRARIES logictoolbox)

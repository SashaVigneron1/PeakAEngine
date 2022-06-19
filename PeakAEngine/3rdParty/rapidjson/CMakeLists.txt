#this is a library with only header files -> INTERFACE
add_library(RapidJsonLib INTERFACE)
#CMAKE_CURRENT_SOURCE_DIR is the directory where this CMakeLists.txt is based.
#PARENT_SCOPE means it's getting called from the main project
set(JsonIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)
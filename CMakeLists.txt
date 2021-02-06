cmake_minimum_required(VERSION 3.10)

project(Project_Team_3)

include(ExternalProject)

# Set install directory
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist CACHE PATH ${CMAKE_SOURCE_DIR}/dist FORCE)
if(WIN32)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug;Release" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

include(BuildGLEW)
include(BuildGLFW)
include(BuildGLM)

# Project_Team_3
set(EXEC Project_Team_3)

file(GLOB SRC src/*)
include_directories(${SRC})
add_executable(${EXEC} "src/project.cpp")

target_link_libraries(${EXEC} OpenGL::GL GLEW glfw glm)

target_include_directories(${EXEC} PUBLIC include)

list(APPEND BIN ${EXEC})
# end Project_Team_3

# install files to install location
install(TARGETS ${BIN} DESTINATION ${CMAKE_INSTALL_PREFIX})


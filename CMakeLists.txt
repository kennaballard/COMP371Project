cmake_minimum_required(VERSION 3.11)

project(Lab_1)

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

# lab01
set(EXEC lab01)

file(GLOB SRC src/*.cpp)

add_executable(${EXEC} ${SRC})

target_link_libraries(${EXEC} OpenGL::GL GLEW glfw glm)

list(APPEND BIN ${EXEC})
# end lab01

# install files to install location
install(TARGETS ${BIN} DESTINATION ${CMAKE_INSTALL_PREFIX})


cmake_minimum_required(VERSION 3.11)

project(particle-life)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

set(THIRD_DIR ${PROJECT_SOURCE_DIR}/3rdparty)
set(INCLUDES_DIR ${PROJECT_SOURCE_DIR}/includes)

include_directories(
    ${THIRD_DIR}
    ${THIRD_DIR}/imgui
    ${INCLUDES_DIR}
    ${OPENGL_INCLUDE_DIRS}
    )
    
# add_subdirectory(${INCLUDES_DIR})
add_subdirectory(${THIRD_DIR})

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(
    particle-life 
    ${SOURCES}
)

target_link_libraries(
    particle-life
    IMGUI_LIB
    ${THIRD_DIR}/lib/glfw3.lib
    ${OPENGL_LIBRARIES}
)

add_custom_command(TARGET particle-life POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/resources"
        $<TARGET_FILE_DIR:particle-life>)

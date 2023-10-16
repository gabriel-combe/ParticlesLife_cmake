file(GLOB IMGUI_INCLUDE CONFIGURE_DEPENDS 
    ${IMGUI_DIR}/*.h
    ${IMGUI_DIR}/*.cpp
)

add_library(
    IMGUI_LIB STATIC
    ${THIRD_DIR}/GLFW/glfw3.h
    ${THIRD_DIR}/GLFW/glfw3native.h
    ${IMGUI_INCLUDE}
)

target_link_libraries(
    IMGUI_LIB
    ${OPENGL_LIBRARIES}
    ${THIRD_DIR}/lib/glfw3.Lib
    glad
)

target_include_directories(
    IMGUI_LIB PUBLIC
    ${THIRD_DIR}/imgui
    ${OPENGL_INCLUDE_DIRS}
    ${IMGUI_DIR}
)

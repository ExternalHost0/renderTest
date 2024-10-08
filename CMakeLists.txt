cmake_minimum_required(VERSION 3.28)
project(renderTest)
set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include) # Include folder

find_package(OpenGL REQUIRED)

set(GLEW_DIR /opt/homebrew/Cellar/glew/2.2.0_1)
SET(GLFW_DIR /opt/homebrew/Cellar/glfw/3.4)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_library(imgui STATIC
        ${INCLUDE_FOLDER}/imgui/imgui.cpp
        ${INCLUDE_FOLDER}/imgui/imgui_draw.cpp
        ${INCLUDE_FOLDER}/imgui/imgui_demo.cpp
        ${INCLUDE_FOLDER}/imgui/imgui_tables.cpp
        ${INCLUDE_FOLDER}/imgui/imgui_widgets.cpp
        ${INCLUDE_FOLDER}/imgui/imgui_impl_glfw.cpp
        ${INCLUDE_FOLDER}/imgui/imgui_impl_opengl3.cpp
        src/prefabs/shapes/Cube.cpp
        src/prefabs/shapes/Cube.h
        src/components/BaseComponent.cpp
        src/components/BaseComponent.h
)

include_directories(
        ${INCLUDE_FOLDER}/IconFontHeaders/
        ${INCLUDE_FOLDER}/glm/
        ${INCLUDE_FOLDER}/imgui/
        ${GLEW_DIR}/include/
        ${GLFW_DIR}/include/
)
link_directories(
        ${GLEW_DIR}/lib/
        ${GLFW_DIR}/lib/
)
add_executable(renderTest src/main.cpp
        src/modules/Util.cpp
        src/modules/Util.h
        src/prefabs/other/Camera.cpp
        src/prefabs/other/Camera.h
        src/Application.cpp
        src/Application.h
        src/modules/Input.cpp
        src/modules/Input.h
        src/modules/Renderer.cpp
        src/modules/Renderer.h
        src/prefabs/Primitives.h
        src/modules/GUI.cpp
        src/modules/GUI.h
        src/modules/Scene.cpp
        src/modules/Scene.h
        src/Structs.h
        src/modules/GUI_Styles.cpp
        src/components/subcomponents/TransformComponent.cpp
        src/components/subcomponents/TransformComponent.h
)
target_link_libraries(renderTest
        imgui
        glfw
        glew
        OpenGL::GL
)


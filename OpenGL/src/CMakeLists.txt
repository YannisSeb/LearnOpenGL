cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

# Include headers
include_directories(
    dependencies/glfw/include
    dependencies/glew/include
)

# Link directories
link_directories(
    dependencies/glfw/lib-vc2022
    dependencies/glew/lib/Release/x64
)

# Add source files
add_executable(OpenGLApp src/main.cpp)

# Define GLEW_STATIC for static linking
target_compile_definitions(OpenGLApp PRIVATE GLEW_STATIC)

# Link libraries
target_link_libraries(OpenGLApp
    glfw3
    opengl32
    glew32s
    d3d12
)


add_custom_command(TARGET OpenGLApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:OpenGLApp>/res)

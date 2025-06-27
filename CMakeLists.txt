cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)
project (learnopengl1)

find_package(OpenGL REQUIRED)

# Add glad manually
add_library(glad libs/glad/src/glad.c)

# Add GLFW
# You can either build it from source or link to system-installed version
add_subdirectory(libs/glfw)  # This assumes glfw is present as a subdirectory with its CMakeLists.txt

include_directories(
  libs/glad/include/
  libs/glfw/include/
)

add_executable(window
    window.c
)

# Link libraries
target_link_libraries(window
    glad
    glfw
    ${OPENGL_gl_LIBRARY}
)

add_executable(hello_window
  hello_window.c
)

# Link libraries
target_link_libraries(hello_window
    glad
    glfw
    ${OPENGL_gl_LIBRARY}
)

add_executable(triangles
  triangles.c
)

# Link libraries
target_link_libraries(triangles
    glad
    glfw
    ${OPENGL_gl_LIBRARY}
)

add_executable(triangles_hw
  triangles_hw.c
)

# Link libraries
target_link_libraries(triangles_hw
    glad
    glfw
    ${OPENGL_gl_LIBRARY}
)

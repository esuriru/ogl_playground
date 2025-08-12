cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ogl_playground LANGUAGES C CXX)

# Add new sources into here this list
set(SOURCES
    "src/main.cpp"

    "src/core/app.cpp"
    "src/core/time.cpp"
    "src/core/window.cpp"

    "src/gfx/command.cpp"
    "src/gfx/vert_array.cpp"
    "src/gfx/vert_buf.cpp"
    "src/gfx/index_buf.cpp"
    "src/gfx/buf_elem.cpp"
    "src/gfx/ogl_ctx.cpp"
    "src/gfx/shader.cpp"
    "src/gfx/render2d.cpp"
    "src/gfx/tex2d.cpp"
    "src/gfx/image.cpp"
)

add_executable(playground ${SOURCES})

target_include_directories(playground PUBLIC include)

## Add in dependencies

# Standard library
target_link_options(playground PUBLIC -static-libstdc++ -static-libgcc)

include(FetchContent)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# (embedded) stb_image
add_subdirectory("deps/stb/image")
target_link_libraries(playground PUBLIC stb_image)

# glm
FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.zip
    URL_HASH
        SHA256=09C5716296787E1F7FCB87B1CBDBF26814EC1288ED6259CCD30D5D9795809FA5
)

add_subdirectory("deps/glm")
target_link_libraries(playground PUBLIC glm::glm)

# glfw
FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/3.4.zip
    URL_HASH
        SHA256=A133DDC3D3C66143EBA9035621DB8E0BCF34DBA1EE9514A9E23E96AFD39FD57A
)

add_subdirectory("deps/glfw")
target_link_libraries(playground PUBLIC glfw)
target_include_directories(playground PUBLIC ${GLFW_SOURCE_DIR})

# glad
add_subdirectory("deps/glad")
target_link_libraries(playground PUBLIC glad)
target_include_directories(playground PUBLIC "deps/glad/include")

# Copy assets to build folder
add_custom_command(
    TARGET playground 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:playground>
    COMMAND_EXPAND_LISTS
)

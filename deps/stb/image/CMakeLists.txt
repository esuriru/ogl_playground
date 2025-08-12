message(STATUS "Installing (embedded) stb_image")

add_library(stb_image STATIC "src/stb_image.c")

target_include_directories(stb_image PUBLIC "include")

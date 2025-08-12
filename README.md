# ogl_playground

A simple OpenGL 4.6 test bed with RAII-based wrappers
over OpenGL objects. (e.g VAOs, VBOs)

## Dependencies

Most of the dependencies are downloaded using CMake's
[FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html).

* [glfw](https://github.com/glfw/glfw) (Windowing)
* [glm](https://github.com/g-truc/glm) (Math Constructs)
* [glad](https://github.com/Dav1dde/glad) (OpenGL loader)
* [stb_image](https://github.com/nothings/stb) (Image loading) (embedded)
* Standard template library

## Getting Started

To get started, clone this repository.

### Windows

#### CMake

This project uses CMake as its main build system.
You may be required to download this as a prerequisite.

Tested kits:

* GCC 13.2 (ucrt64)
* Clang 19.1.1

Run executable target `playground`; this will clone the
dependenices into the build folder on post-build.

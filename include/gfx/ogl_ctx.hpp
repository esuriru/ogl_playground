#pragma once

struct GLFWwindow;

namespace playground::gfx
{
    // OpenGL loader wrapper, loads functions using GLAD
    class ogl_ctx final 
    {
    public:
        ogl_ctx(GLFWwindow* window);

        void swap_buffers();
    private:
        GLFWwindow* window;
    };
}
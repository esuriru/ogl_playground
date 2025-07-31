#pragma once

struct GLFWwindow;

namespace playground::gfx
{
    class ogl_ctx final 
    {
    public:
        ogl_ctx(GLFWwindow* window);

        void swap_buffers();
    private:
        GLFWwindow* window;
    };
}
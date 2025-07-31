#include "gfx/ogl_ctx.hpp"

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include <cassert>

namespace playground::gfx
{
    ogl_ctx::ogl_ctx(GLFWwindow* window)
        : window(window)
    {
        glfwMakeContextCurrent(window);

        int result = gladLoadGL(glfwGetProcAddress);
        assert(result);
    }

    void ogl_ctx::swap_buffers()
    {
        glfwSwapBuffers(window);
    }
}
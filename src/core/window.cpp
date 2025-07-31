#include "core/window.hpp"

#include "core/app.hpp"
#include "GLFW/glfw3.h"

#include <iostream>
#include <cassert>

namespace playground::core
{
    window::window(const std::string& title, const unsigned int width,
        const unsigned int height)
        : title(title)
        , width(width)
        , height(height)
    {
        int glfw_init_result = glfwInit();
        assert(glfw_init_result);

        glfwSetErrorCallback(
            [](int error, const char* desc)
            {
                std::cout << "GLFW error: (" << error << "): {" << desc << "}"
                          << std::endl;
            });

        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        handle
            = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        assert(handle);

        // Store a pointer to the wrapper such that we can
        // access it later on in callbacks
        glfwSetWindowUserPointer(handle, this);

        // Handle callbacks
        glfwSetWindowSizeCallback(handle, on_resize);
        glfwSetWindowCloseCallback(handle, on_window);
    }

    window::~window()
    {
        glfwDestroyWindow(handle);
    }

    void window::update()
    {
        glfwPollEvents();
    }

    playground::core::window* get_wrapper(GLFWwindow*& window)
    {
        return reinterpret_cast<playground::core::window*>(
            glfwGetWindowUserPointer(window));
    }

    void window::on_resize(GLFWwindow* window, int width, int height)
    {
        auto wrapper = get_wrapper(window);

        wrapper->width = width;
        wrapper->height = height;
    }

    void window::on_window(GLFWwindow* window)
    {
        app::get().close();
    }
}
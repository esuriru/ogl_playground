#pragma once

#include <string>

struct GLFWwindow;

namespace playground::core
{
    // GLFW Window wrapper, handles initialization of GLFW
    class window
    {
    public:
        window(const std::string& title, const unsigned int width,
            const unsigned int height);
        ~window();

        void update();

        inline GLFWwindow* get_internal() const
        {
            return handle;
        }

        inline const unsigned int get_width() const
        {
            return width;
        }

        inline const unsigned int get_height() const
        {
            return height;
        }

    private:
        GLFWwindow* handle;

        std::string title;
        unsigned int width, height;

        static void on_resize(GLFWwindow* window, int width, int height);
        static void on_close(GLFWwindow* window);
    };
}
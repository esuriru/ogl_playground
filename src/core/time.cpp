#include "core/time.hpp"

#include "GLFW/glfw3.h"

namespace
{
    float last_frame_time = 0.0f;
    float delta_time = 0.0f;
}

namespace playground::core::time
{
    void update()
    {
        float current_time = glfwGetTime();
        delta_time = current_time - last_frame_time;
        last_frame_time = current_time;
    }

    float get_delta_time()
    {
        return delta_time;
    }
}

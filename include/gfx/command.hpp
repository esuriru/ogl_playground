#pragma once

#include "glm/glm.hpp"
#include "gfx/vert_array.hpp"

namespace playground::gfx
{
    // Global render commands, called by the renderer
    class command final
    {
    public:
        static void init();
        static void cleanup();

        // Clear color attachment of default framebuffer
        static void clear_color(const glm::vec4& color);

        // Submit OpenGL VAO to GPU (triangles)
        static void draw_indexed(
            const gfx::vert_array& array,
            unsigned int index_count = 0);

        // Set viewport position and size
        static void set_viewport(const unsigned int x, const unsigned int y,
            const unsigned int width, const unsigned int height);
    };
}

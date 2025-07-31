#pragma once

#include "glm/glm.hpp"
#include "gfx/vert_array.hpp"

namespace playground::gfx
{
    class command final
    {
    public:
        static void init();
        static void cleanup();

        static void clear_color(const glm::vec4& color);

        static void draw_indexed(
            const gfx::vert_array& array,
            unsigned int index_count = 0);

        static void set_viewport(const unsigned int x, const unsigned int y,
            const unsigned int width, const unsigned int height);
    };
}

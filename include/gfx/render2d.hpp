#pragma once

#include "glm/glm.hpp"

namespace playground::gfx::render2d
{
    void init();
    void cleanup();

    void set_view_mat(const glm::mat4& mat);
    void set_proj_mat(const glm::mat4& mat);

    void draw_quad(
        const glm::vec2& world_pos, 
        const float rotation,
        const glm::vec2& size);
}
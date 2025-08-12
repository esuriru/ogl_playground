#pragma once

#include "glm/glm.hpp"
#include "gfx/tex2d.hpp"

// Renderer for 2D constructs
namespace playground::gfx::render2d
{
    void init();
    void cleanup();

    // Set view matrix for next draw calls
    void set_view_mat(const glm::mat4& mat);

    // Set projection matrix for next draw calls
    void set_proj_mat(const glm::mat4& mat);

    // Draw a white quad
    void draw_quad(const glm::vec2& world_pos, const float rot_deg,
        const glm::vec2& size, tex2d* tex = nullptr, 
        const glm::vec4& color = glm::vec4(1.0f));
}
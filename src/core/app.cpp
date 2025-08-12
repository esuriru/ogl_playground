#include "core/app.hpp"
#include "core/time.hpp"

#include "gfx/render2d.hpp"
#include "gfx/command.hpp"

#include "gfx/tex2d.hpp"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

namespace playground::core
{
    app* app::instance = nullptr;

    app& app::get()
    {
        return *instance;
    }

    app::app()
        : is_running(true)
    {
        // Make sure there is no app instance before this
        assert(!instance);
        instance = this;

        // Initialize
        init_deps();

        // This projection matrix makes (0, 0) the center of the viewport
        gfx::render2d::set_proj_mat(
            glm::ortho(-640.0f, 640.0f, -480.0f, 480.0f, -10.0f, 10.0f));
        gfx::render2d::set_view_mat(
            glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f))));
    }

    void app::init_deps()
    {
        // Init window and graphics context
        window = std::make_unique<::playground::core::window>(
            "playground", 640, 480);
        gfx_ctx = std::make_unique<gfx::ogl_ctx>(window->get_internal());

        gfx::command::init();
        gfx::render2d::init();
    }

    void app::run()
    {
        static float rotation;
        vex_sprite_tex = std::make_unique<gfx::tex2d>("img/vex.png");

        while (is_running)
        {
            // Get new delta time
            time::update();

            // Clear the default framebuffer color attachment
            gfx::command::clear_color({ 0.2f, 0.2f, 0.2f, 1.0f });

            // Add draw calls
            gfx::render2d::draw_quad({ -60.0f, 0.0f },
                rotation,
                glm::vec2(240.0f),
                nullptr,
                glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

            gfx::render2d::draw_quad({ 60.0f, 0.0f },
                -rotation * 2.0f,
                glm::vec2(240.0f),
                vex_sprite_tex.get());

            constexpr float rotation_speed = 30.0f;
            rotation += time::get_delta_time() * rotation_speed;

            // Swap framebuffers
            gfx_ctx->swap_buffers();

            // Poll
            window->update();
        }

        vex_sprite_tex.reset();
    }

    void app::close()
    {
        is_running = false;
    }
}
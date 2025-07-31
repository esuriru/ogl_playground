#pragma once

#include "core/window.hpp"
#include "gfx/ogl_ctx.hpp"
#include <memory>

namespace playground::core
{
    class app
    {
    public:
        app();

        void run();
        void close();

        static app& get();

    private:
        static app* instance;
        bool is_running;

        std::unique_ptr<window> window;
        std::unique_ptr<gfx::ogl_ctx> gfx_ctx;

        void init_deps();
    };
}
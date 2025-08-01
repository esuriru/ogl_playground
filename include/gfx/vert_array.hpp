#pragma once

#include "gfx/handle.hpp"
#include "gfx/vert_buf.hpp"
#include "gfx/index_buf.hpp"
#include <memory>

namespace playground::gfx
{
    // OpenGL Vertex Array Object (VAO) wrapper
    class vert_array : public handle
    {
    public:
        vert_array();
        ~vert_array();

        void bind() const;

        void add_vert_buf(std::shared_ptr<vert_buf> buf);
        void set_index_buf(std::shared_ptr<index_buf> buf);

        std::shared_ptr<index_buf> get_index_buf() const;

    private:
        std::shared_ptr<gfx::index_buf> index_buf;
        std::vector<std::shared_ptr<gfx::vert_buf>> vert_bufs;
    };
}
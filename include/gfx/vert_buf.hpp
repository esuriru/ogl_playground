#pragma once

#include "gfx/buf_elem.hpp"
#include "gfx/handle.hpp"

#include <vector>

namespace playground::gfx 
{
    // OpenGL Vertex Buffer Object (VBO) wrapper
    class vert_buf : public handle
    {
    public:
        // Buffer layout for vertex buffer
        class buf_layout 
        {
        public:
            buf_layout() = default;
            buf_layout(
                std::initializer_list<gfx::buf_elem> elements);

            inline unsigned int get_stride() const
            {
                return stride;
            }

            inline const std::vector<gfx::buf_elem>& get_elements() const
            {
                return elements;
            }

        private:
            std::vector<gfx::buf_elem> elements;
            unsigned int stride;

            void invalidate();
        };

        vert_buf(const float* vertices, const unsigned int size);
        ~vert_buf();

        void bind() const;

        const buf_layout& get_layout() const;
        void set_layout(const buf_layout& layout);

    private:
        buf_layout layout {};
    };
}

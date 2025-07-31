#include "gfx/vert_buf.hpp"
#include "glad/gl.h"

namespace playground::gfx 
{
    vert_buf::buf_layout::buf_layout(
        std::initializer_list<gfx::buf_elem> elements)
        : elements(elements)
        , stride(0)
    {
        invalidate();
    }

    void vert_buf::buf_layout::invalidate()
    {
        unsigned int offset = 0;
        stride = 0;

        for (auto& element : elements)
        {
            element.offset = offset;
            offset += element.size;
            stride += element.size;
        }
    }

    vert_buf::vert_buf(const float* vertices, const unsigned int size)
    {
        glCreateBuffers(1, &id);
        glNamedBufferData(
            id, static_cast<GLint>(size), vertices, GL_STATIC_DRAW);
    }

    vert_buf::~vert_buf()
    {
        glDeleteBuffers(1, &id);
    }

    void vert_buf::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    const vert_buf::buf_layout& vert_buf::get_layout() const
    {
        return layout;
    }

    void vert_buf::set_layout(const buf_layout& layout)
    {
        this->layout = layout;
    }
}
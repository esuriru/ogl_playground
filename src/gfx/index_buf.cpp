#include "gfx/index_buf.hpp"

#include "glad/gl.h"

namespace playground::gfx 
{
    index_buf::index_buf(
        const unsigned int* indices, const unsigned int count)
        : count(count)
    {
        glCreateBuffers(1, &id);
        glNamedBufferData(id,
            static_cast<GLint>(count * sizeof(unsigned int)),
            indices,
            GL_STATIC_DRAW);
    }

    index_buf::~index_buf()
    {
        glDeleteBuffers(1, &id);
    }

    void index_buf::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }
}

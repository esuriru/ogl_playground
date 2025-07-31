#include "gfx/vert_array.hpp"
#include "gfx/shader_data_type.hpp"

#include "glad/gl.h"

namespace
{
    using playground::gfx::shader_data_type;

    static GLenum shader_data_type_to_opengl_data_type(
        const shader_data_type type)
    {
        switch (type)
        {
        case shader_data_type::float1:
        case shader_data_type::float2:
        case shader_data_type::float3:
        case shader_data_type::float4:
        case shader_data_type::mat3:
        case shader_data_type::mat4:
            return GL_FLOAT;
        case shader_data_type::int1:
        case shader_data_type::int2:
        case shader_data_type::int3:
        case shader_data_type::int4:
            return GL_INT;
        case shader_data_type::bool1:
            return GL_BOOL;
        case shader_data_type::none:
            break;
        }

        return 0;
    }
}

namespace playground::gfx
{
    vert_array::vert_array()
    {
        glCreateVertexArrays(1, &id);
    }

    vert_array::~vert_array()
    {
        glDeleteVertexArrays(1, &id);
    }

    void vert_array::bind() const
    {
        glBindVertexArray(id);
    }

    void vert_array::add_vert_buf(std::shared_ptr<vert_buf> buf)
    {
        unsigned int attrib_index = 0;
        unsigned int binding_index = vert_bufs.size();
        const auto& layout = buf->get_layout();

        glVertexArrayVertexBuffer(
            id, binding_index, buf->get_id(), 0, layout.get_stride());

        for (const auto& element : layout.get_elements())
        {
            glEnableVertexArrayAttrib(id, attrib_index);
            glVertexArrayAttribFormat(id,
                attrib_index,
                static_cast<GLint>(element.get_component_count()),
                shader_data_type_to_opengl_data_type(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                static_cast<GLuint>(element.offset));
            glVertexArrayAttribBinding(id, attrib_index, binding_index);
            ++attrib_index;
        }

        vert_bufs.push_back(buf);
    }

    void vert_array::set_index_buf(
        std::shared_ptr<playground::gfx::index_buf> buf)
    {
        glVertexArrayElementBuffer(id, buf->get_id());
        index_buf = buf;
    }

    std::shared_ptr<index_buf> vert_array::get_index_buf() const
    {
        return index_buf;
    }
}
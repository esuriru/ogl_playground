#pragma once

#include "shader_data_type.hpp"
#include <string>

namespace playground::gfx 
{
    // Vertex buffer element primitive
    struct buf_elem
    {
        std::string name;
        shader_data_type type;
        unsigned int size;
        unsigned int offset;
        bool normalized;

        buf_elem(shader_data_type type, const std::string& name,
            const bool normalized = false);

        constexpr unsigned int get_component_count() const
        {
            return shader_data_type_component_count(type);
        }
    };
}
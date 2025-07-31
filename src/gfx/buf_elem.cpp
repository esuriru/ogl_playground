#include "gfx/buf_elem.hpp"

namespace playground::gfx 
{
    buf_elem::buf_elem(
        shader_data_type type, const std::string& name, const bool normalized)
        : name(name)
        , type(type)
        , size(shader_data_type_size(type))
        , offset(0)
        , normalized(normalized)
    {
    }
}
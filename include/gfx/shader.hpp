#pragma once

#include "glm/glm.hpp"
#include "gfx/handle.hpp"

#include <string>

namespace playground::gfx
{
    // OpenGL Shader (GLSL) wrapper
    class shader : public handle
    {
    public:
        shader(const std::string& name, const char* vert_src,
            const char* frag_src);
        virtual ~shader() = default;

        void bind();

        void set_int(const std::string& name, const int value);
        void set_mat4(const std::string& name, const glm::mat4& value);
        void set_vec4(const std::string& name, const glm::vec4& value);

        virtual const std::string& get_name();

    private:
        std::string name;
    };
}
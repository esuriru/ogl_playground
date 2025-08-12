#include "gfx/shader.hpp"

#include "glad/gl.h"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

namespace playground::gfx
{
    GLuint compile_shader(const GLenum type, const char* src)
    {
        GLuint shader_handle = glCreateShader(type);
        glShaderSource(shader_handle, 1, &src, nullptr);
        glCompileShader(shader_handle);

        // Query compilation status
        GLint is_compiled = GL_FALSE;
        glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &is_compiled);

        if (is_compiled == GL_FALSE)
        {
            GLint max_length = 0;
            glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &max_length);

            std::string shader_log;
            shader_log.resize(max_length);
            glGetShaderInfoLog(
                shader_handle, max_length, &max_length, shader_log.data());

            std::cout << "Failed to compile opengl shader. Log: " << shader_log
                      << std::endl;

            glDeleteShader(shader_handle);

            return 0;
        }

        return shader_handle;
    }

    shader::shader(
        const std::string& name, const char* vert_src, const char* frag_src)
        : name(name)
    {
        assert(vert_src);
        assert(frag_src);

        GLuint program_handle = glCreateProgram();

        // Compile vert shader
        GLuint vert_shader_handle = compile_shader(GL_VERTEX_SHADER, vert_src);

        if (vert_shader_handle == 0)
        {
            std::cout << "Failed to compile vertex shader" << std::endl;

            glDeleteProgram(program_handle);
            return;
        }

        GLuint frag_shader_handle
            = compile_shader(GL_FRAGMENT_SHADER, frag_src);
        if (frag_shader_handle == 0)
        {
            std::cout << "Failed to compile fragment shader" << std::endl;

            glDeleteShader(vert_shader_handle);
            glDeleteProgram(program_handle);
            return;
        }

        glAttachShader(program_handle, vert_shader_handle);
        glAttachShader(program_handle, frag_shader_handle);

        glLinkProgram(program_handle);

        // Query link status
        GLint is_linked = GL_FALSE;
        glGetProgramiv(program_handle, GL_LINK_STATUS, &is_linked);

        if (is_linked == GL_FALSE)
        {
            GLint max_length = 0;
            glGetProgramiv(program_handle, GL_INFO_LOG_LENGTH, &max_length);

            std::string program_log;
            program_log.resize(max_length);
            glGetProgramInfoLog(
                program_handle, max_length, &max_length, program_log.data());

            std::cout << "Failed to link opengl program. Log: " << program_log
                      << std::endl;

            // Cleanup
            glDeleteShader(vert_shader_handle);
            glDeleteShader(frag_shader_handle);
            glDeleteProgram(program_handle);

            return;
        }

        glDetachShader(program_handle, vert_shader_handle);
        glDetachShader(program_handle, frag_shader_handle);

        id = program_handle;
    }

    void shader::bind()
    {
        glUseProgram(id);
    }

    void shader::set_int(const std::string& name, const int value)
    {
        const auto& location = glGetUniformLocation(id, name.c_str());
        glUniform1i(location, value);
    }

    void shader::set_mat4(const std::string& name, const glm::mat4& value)
    {
        const auto& location = glGetUniformLocation(id, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void shader::set_vec4(const std::string& name, const glm::vec4& value)
    {
        const auto& location = glGetUniformLocation(id, name.c_str());
        glUniform4fv(location, 1, glm::value_ptr(value));
    }

    const std::string& shader::get_name()
    {
        return name;
    }
}
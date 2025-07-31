#include "gfx/render2d.hpp"

#include "gfx/shader.hpp"
#include "gfx/vert_array.hpp"
#include "gfx/command.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include <memory>
#include <filesystem>
#include <fstream>

// Anonymous namespace to store variables
// (variables here can only be accessed through this source file)
namespace
{
    using namespace playground::gfx;

    glm::mat4 view_mat {};
    glm::mat4 proj_mat {};

    std::unique_ptr<vert_array> quad_vert_array;

    std::shared_ptr<shader> white_shader;
    std::shared_ptr<shader> texture_shader;
}

namespace playground::gfx::render2d
{
    std::string load_file_as_str(const std::filesystem::path& path)
    {
        std::ifstream file(path);
        assert(file.is_open());

        std::ostringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    [[nodiscard]]
    std::shared_ptr<shader> load_shader(
        const std::string& name,
        const std::filesystem::path& vert_path,
        const std::filesystem::path& frag_path)
    {
        std::string vert_shader_src = load_file_as_str(vert_path);
        std::string frag_shader_src = load_file_as_str(frag_path);
        return std::make_shared<shader>(
            name, vert_shader_src.c_str(), frag_shader_src.c_str());
    }

    void init()
    {
        texture_shader = load_shader(
            "texture",
            "shaders/texture_v.glsl",
            "shaders/texture_f.glsl");
        white_shader = load_shader(
            "white",
            "shaders/texture_v.glsl",
            "shaders/white_f.glsl");

        // clang-format off
        std::vector<float> vertices = 
        {
            {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
            }
        };

        std::vector<uint32_t> indices = 
        {
            {
                0, 1, 2, 
                2, 3, 0
            }
        };
        // clang-format on

        // Create our vertex buffer with the vertex data
        auto quad_vert_buf = std::make_shared<vert_buf>(
            vertices.data(), vertices.size() * sizeof(float));

        // Set the layout of the data in the buffer
        quad_vert_buf->set_layout({
            { shader_data_type::float3, "vertex_pos" },
            { shader_data_type::float2, "vertex_uv" },
        });

        // Attach the vertex buffer onto the vertex array object
        quad_vert_array = std::make_unique<vert_array>();
        quad_vert_array->add_vert_buf(quad_vert_buf);

        // Create and set index buffer onto the vertex array object
        quad_vert_array->set_index_buf(
            std::make_shared<index_buf>(indices.data(), indices.size()));
    }

    void cleanup()
    {
        quad_vert_array.reset();
    }

    void set_view_mat(const glm::mat4& mat)
    {
        view_mat = mat;
    }

    void set_proj_mat(const glm::mat4& mat)
    {
        proj_mat = mat;
    }

    void draw_quad(
        const glm::vec2& world_pos, const float rotation, const glm::vec2& size)
    {
        white_shader->bind();

        // clang-format off
        glm::mat4 model_matrix = 
            glm::translate(glm::identity<glm::mat4>(),
                glm::vec3(world_pos, 0.0f))
            * glm::rotate(glm::identity<glm::mat4>(), glm::radians(rotation),
                { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::identity<glm::mat4>(), glm::vec3(size, 0.0f));
        // clang-format on

        glm::mat4 MVP = proj_mat * view_mat * model_matrix;

        white_shader->set_mat4("MVP", MVP);

        command::draw_indexed(*quad_vert_array);
    }
}
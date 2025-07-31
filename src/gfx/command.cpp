#include "gfx/command.hpp"

#include "glad/gl.h"
#include "glm/gtc/type_ptr.hpp"

namespace playground::gfx
{
    void command::init()
    {
        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA,
            GL_ONE,
            GL_ONE_MINUS_SRC_ALPHA);
    }

    void command::cleanup()
    {
    }

    void command::clear_color(const glm::vec4& color)
    {
        glClearBufferfv(GL_COLOR, 0, glm::value_ptr(color));
    }

    void command::draw_indexed(
        const gfx::vert_array& array, unsigned int index_count)
    {
        array.bind();
        unsigned int count = index_count == 0 ?
            array.get_index_buf()->get_count() :
            index_count;
        glDrawElements(
            GL_TRIANGLES, static_cast<GLint>(count), GL_UNSIGNED_INT, nullptr);
    }

    void command::set_viewport(const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height)
    {
        glViewport(x, y, width, height);
    }
}
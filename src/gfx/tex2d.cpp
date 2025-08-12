#include "gfx/tex2d.hpp"

#include "glad/gl.h"
#include <cassert>

namespace playground::gfx
{
    constexpr GLenum filter_mode_to_opengl_filter_mode(
        const tex2d::filter_mode mode)
    {
        switch (mode)
        {
        case tex2d::filter_mode::linear:
            return GL_LINEAR;
        case tex2d::filter_mode::nearest:
            return GL_NEAREST;
        default:
            break;
        }
    }

    constexpr GLenum wrap_mode_to_opengl_wrap_mode(const tex2d::wrap_mode mode)
    {
        switch (mode)
        {
        case tex2d::wrap_mode::repeat:
            return GL_REPEAT;
        case tex2d::wrap_mode::clamp_edge:
            return GL_CLAMP_TO_EDGE;
        case tex2d::wrap_mode::clamp_border:
            return GL_CLAMP_TO_BORDER;
        default:
            break;
        }
    }

    constexpr GLenum format_to_gl_format(const enum tex_format format)
    {
        switch (format)
        {
        case tex_format::r8:
            return GL_R8;
        case tex_format::rgb8:
            return GL_RGB8;
        case tex_format::rgba8:
            return GL_RGBA8;
        case tex_format::rgba32f:
            return GL_RGBA32F;
        case tex_format::d24_s8:
            return GL_DEPTH24_STENCIL8;
        default:
            break;
        }
    }

    constexpr GLenum format_to_gl_format(const enum format format)
    {
        switch (format)
        {
        case format::rgb:
            return GL_RGB;
        case format::rgba:
            return GL_RGBA;
        default:
            break;
        }
    }

    tex2d::tex2d(
        const std::filesystem::path& path, const image_load_options& options)
    {
        image = std::make_unique<playground::gfx::image>(path, options);
        assert(image);

        invalidate_image();
    }

    tex2d::tex2d(const unsigned char* data, const unsigned int count,
        const image_load_options& options)
    {
        image = std::make_unique<playground::gfx::image>(data, count, options);
        assert(image);

        invalidate_image();
    }

    tex2d::tex2d(const unsigned int width, const unsigned int height,
        const enum format format, const void* data, const unsigned int size)
        : format(tex_format::rgba8)
    {
        // this->format is the texture format
        // format is the data format

        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        glTextureStorage2D(id,
            1,
            format_to_gl_format(this->format),
            static_cast<GLint>(width),
            static_cast<GLint>(height));

        unsigned int bytes_per_channel = format == format::rgba ? 4 : 3;

        // If this assertion trips, the data is invalid
        assert(size == width * height * bytes_per_channel);

        glTextureSubImage2D(id,
            0,
            0,
            0,
            static_cast<GLint>(width),
            static_cast<GLint>(height),
            format_to_gl_format(format),
            GL_UNSIGNED_BYTE,
            data);
    }

    void tex2d::set_min_filter(const filter_mode mode)
    {
        glTextureParameteri(
            id, GL_TEXTURE_MIN_FILTER, filter_mode_to_opengl_filter_mode(mode));
    }

    void tex2d::set_mag_filter(const filter_mode mode)
    {
        glTextureParameteri(
            id, GL_TEXTURE_MAG_FILTER, filter_mode_to_opengl_filter_mode(mode));
    }

    void tex2d::set_wrap_s(const wrap_mode mode)
    {
        glTextureParameteri(
            id, GL_TEXTURE_WRAP_S, wrap_mode_to_opengl_wrap_mode(mode));
    }

    void tex2d::set_wrap_t(const wrap_mode mode)
    {
        glTextureParameteri(
            id, GL_TEXTURE_WRAP_T, wrap_mode_to_opengl_wrap_mode(mode));
    }

    unsigned int tex2d::get_width() const
    {
        return width;
    }

    unsigned int tex2d::get_height() const
    {
        return height;
    }

    void tex2d::bind(const unsigned int slot)
    {
        glBindTextureUnit(this->slot = slot, id);
    }

    void tex2d::invalidate_image()
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        GLenum internal_format, data_format;
        if (image->get_channel_count() == 4)
        {
            internal_format = GL_RGBA8;
            data_format = GL_RGBA;
            format = playground::gfx::tex_format::rgba8;
        }
        else if (image->get_channel_count() == 3)
        {
            internal_format = GL_RGB8;
            data_format = GL_RGB;
            format = playground::gfx::tex_format::rgb8;
        }

        glTextureStorage2D(id,
            1,
            internal_format,
            static_cast<GLint>(image->get_width()),
            static_cast<GLint>(image->get_height()));

        set_min_filter(filter_mode::linear);
        set_mag_filter(filter_mode::nearest);

        set_wrap_s(wrap_mode::repeat);
        set_wrap_t(wrap_mode::repeat);

        glTextureSubImage2D(id,
            0,
            0,
            0,
            image->get_width(),
            image->get_height(),
            data_format,
            GL_UNSIGNED_BYTE,
            image->get_data());

        glGenerateTextureMipmap(id);

        width = image->get_width();
        height = image->get_height();
    }
}
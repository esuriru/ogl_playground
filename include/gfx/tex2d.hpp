#pragma once

#include "format.hpp"
#include "gfx/handle.hpp"
#include "gfx/image.hpp"

#include <filesystem>

namespace playground::gfx
{
    // TODO - Texture base class
    class tex2d : public handle
    {
    public:
        enum class filter_mode
        {
            linear,
            nearest
        };

        enum class wrap_mode
        {
            repeat,
            clamp_edge,
            clamp_border,
        };

        tex2d(const std::filesystem::path& path,
            const image_load_options& options = {});
        tex2d(const unsigned char* data, const unsigned int count,
            const image_load_options& options = {});
        tex2d(const unsigned int width, const unsigned int height,
            const enum format format, const void* data, const unsigned int size);

        virtual ~tex2d() = default;

        void set_min_filter(const filter_mode mode);
        void set_mag_filter(const filter_mode mode);

        void set_wrap_s(const wrap_mode mode);
        void set_wrap_t(const wrap_mode mode);

        unsigned int get_width() const;
        unsigned int get_height() const;

        // Not const because it sets `slot`
        void bind(const unsigned int slot = 0);

    private:
        std::unique_ptr<image> image {};
        tex_format format;

        unsigned int slot;

        // For textures with no backing image
        unsigned int width, height;

        void invalidate_image();
    };
}
#include "gfx/image.hpp"

#include "stb_image.h"

#include <cassert>

namespace playground::gfx
{
    image::image(
        const std::filesystem::path& path, const image_load_options& options)
    {
        stbi_set_flip_vertically_on_load(options.flip_vertically);
        int width, height, channels;
        data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);

        // If this assert trips, load failed
        assert(data);

        this->width = width;
        this->height = height;
        this->channel_count = channels;
    }

    image::image(const unsigned char* data, unsigned int size,
        const image_load_options& options)
    {
        stbi_set_flip_vertically_on_load(options.flip_vertically);
        int width, height, channels;
        data = stbi_load_from_memory(data, size, &width, &height, &channels, 0);
        assert(data);

        this->width = width;
        this->height = height;
        this->channel_count = channels;
    }

    image::~image()
    {
        stbi_image_free(data);
    }

    unsigned char* image::get_data() const
    {
        return data;
    }

    unsigned int image::get_width() const
    {
        return width;
    }

    unsigned int image::get_height() const
    {
        return height;
    }

    unsigned int image::get_channel_count() const
    {
        return channel_count;
    }
}
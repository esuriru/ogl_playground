#pragma once

#include <filesystem>

namespace playground::gfx
{
    struct image_load_options final
    {
        bool flip_vertically = true;
    };

    // TODO - Store formats inside of image
    class image
    {
    public:
        image(const std::filesystem::path& path,
            const image_load_options& options);
        image(const unsigned char* data, unsigned int size,
            const image_load_options& options);
        ~image();

        unsigned char* get_data() const;
        unsigned int get_width() const;
        unsigned int get_height() const;
        unsigned int get_channel_count() const;

    private:
        unsigned char* data;
        unsigned int width, height, channel_count;
    };
}
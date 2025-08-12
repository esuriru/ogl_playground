#pragma once

namespace playground::gfx
{
    enum class format : unsigned short
    {
        rgb,
        rgba
    };

    enum class tex_format : unsigned short
    {
        r8,
        rgb8,
        rgba8,
        rgba32f,

        d24_s8,
    };
}
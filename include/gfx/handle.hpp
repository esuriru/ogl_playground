#pragma once

namespace playground::gfx
{
    // Base class for objects that have a handle (e.g OpenGL objects)
    class handle
    {
    public:
        handle() = default;

        const unsigned int get_id() const
        {
            return id;
        }

    protected:
        unsigned int id;
    };
}
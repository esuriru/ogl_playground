#pragma once

namespace playground::gfx
{
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
#pragma once

#include "gfx/handle.hpp"

namespace playground::gfx
{
    // Index buffer (EBO) wrapper
    class index_buf : public handle
    {
    public:
        index_buf(const unsigned int* indices, const unsigned int count);
        ~index_buf();

        void bind() const;
        unsigned int get_count() const
        {
            return count;
        }

    private:
        unsigned int count;
    };
}
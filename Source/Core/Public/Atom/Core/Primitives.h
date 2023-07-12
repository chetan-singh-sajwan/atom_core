#pragma once
#include <iostream>
#include <cstdint>

#include "LangExtensions.h"

namespace Atom
{
    using byte = unsigned char;

    using uchar = unsigned char;
    using char8 = char8_t;
    using char16 = char16_t;
    using char32 = char32_t;

    using int8 = int8_t;
    using int16 = int16_t;
    using int32 = int32_t;
    using int64 = int64_t;

    using uint8 = uint8_t;
    using uint16 = uint16_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;
    using uint = unsigned int;

    using usize = std::size_t;
    using isize = std::ptrdiff_t;
}

namespace Atom
{
    using NullPtr = std::nullptr_t;
    // static cexpr NullPtr nullptr;
}

namespace Atom
{
    using NullVal = std::nullptr_t;
    static cexpr NullVal nullval = NullVal();
}

namespace Atom
{
    using NullPos = std::nullptr_t;
    static cexpr NullPos nullpos = NullPos();
}

namespace Atom
{
    using NullType = std::nullptr_t;
    using TypeInfo = std::type_info;

    template <tname T>
    cexpr T&& MOVE(T& obj) noex
    {
        return std::move(obj);
    }

    template <tname T>
    cexpr T& MOVE(T& lhs, T& rhs) noex
    {
        lhs = std::move(rhs);
        return lhs;
    }

    template <tname T>
    void SWAP(T& lhs, T& rhs)
    {
        T tmp = MOVE(lhs);
        lhs = MOVE(rhs);
        rhs = MOVE(tmp);
    }
}
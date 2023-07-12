#pragma once
#include <numeric>

#include "Atom/Core.h"
#include "Atom/Str/StaticStr.h"

namespace Atom
{
    template <typename T>
    using NumLimits = std::numeric_limits<T>;
}

namespace Atom::Math
{
    constexpr double Abs(double value) noex
    {
        // TODO: Improve this, maybe using sign bit flag.
        return value * (value < 0 ? -1 : 1);
    }

    constexpr bool IsApproximatelyZero(double lhs, double rhs) noex
    {
        return Abs(lhs - rhs) < 0.0001f;
    }

    template <typename TInt>
    constexpr TInt Clamp(const TInt& value, const TInt& lhs, const TInt& rhs)
    {
        if (value < lhs) return lhs;
        if (value > rhs) return rhs;

        return value;
    }

    // TODO: Implement with template args
    template <typename TInt>
    constexpr TInt Min(const TInt& lhs, const TInt& rhs)
    {
        return lhs < rhs ? lhs : rhs;
    }

    // TODO: Implement with template args
    template <typename TInt>
    constexpr TInt Max(const TInt& lhs, const TInt& rhs)
    {
        return lhs > rhs ? lhs : rhs;
    }

    constexpr byte CharToHex(Char ch) noex
    {
        if (ch >= TEXT('0') && ch <= TEXT('9'))
            return byte(ch - TEXT('0'));
        if (ch >= TEXT('a') && ch <= TEXT('f'))
            return byte(10 + ch - TEXT('a'));
        if (ch >= TEXT('A') && ch <= TEXT('F'))
            return byte(10 + ch - TEXT('A'));

        return -1;
    }

    constexpr StaticStr<2> HexToChar(byte hex) noex
    {
        constexpr const Char chars[] = TEXT("0123456789abcdef");

        byte high = hex >> 4;
        byte low = hex & 0b00001111;
        return { chars[high], chars[low] };
    }

    constexpr bool IsHexChar(Char ch) noex
    {
        return (ch >= TEXT('0') && ch <= TEXT('9')) ||
            (ch >= TEXT('a') && ch <= TEXT('f')) ||
            (ch >= TEXT('A') && ch <= TEXT('F'));
    }
}
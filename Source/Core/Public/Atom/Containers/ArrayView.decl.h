#pragma once
#include "Atom/Containers/ArrayIterator.h"
#include "Ranges.h"

namespace Atom
{
    template <typename T>
    class ArrayView
    {
    public:
        using TIter = ArrayIterator<const T>;
        using TConstIter = ArrayIterator<const T>;
        using TEnd = TIter;

    //// -------------------------------------------------------------------------------------------
    //// Constructors, Operators and Destructor.
    //// -------------------------------------------------------------------------------------------

    public:
        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr ArrayView() noexcept;

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr ArrayView(const T* in_begin, const T* in_end) noexcept;

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr ArrayView(const T* in_arr, usize in_count) noexcept;

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <typename TRange>
        requires RArrayRange<TRange, const T>
        constexpr ArrayView(const TRange& range) noexcept:
            ArrayView(&*range.begin(), &*range.end()) { }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <typename TRange>
        requires RFwdRange<TRange, const T>
        constexpr bool operator == (const TRange& range) const noexcept;

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr bool operator == (const ArrayView& in) const noexcept;

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr const T& operator [] (usize index) const noexcept;

    //// -------------------------------------------------------------------------------------------
    //// Iteration.
    //// -------------------------------------------------------------------------------------------

    public:
        /// ----------------------------------------------------------------------------------------
        /// Iterator to the first element.
        /// ----------------------------------------------------------------------------------------
        constexpr TIter Begin() const noexcept
        {
            return TIter{ m_arr };
        }

        /// ----------------------------------------------------------------------------------------
        /// Iterator to the last element.
        /// ----------------------------------------------------------------------------------------
        constexpr TIter End() const noexcept
        {
            return TIter{ m_arr + m_count };
        }

        /// ----------------------------------------------------------------------------------------
        /// Iterator to the first element.
        /// ----------------------------------------------------------------------------------------
        constexpr TIter begin() const noexcept
        {
            return TIter{ m_arr };
        }

        /// ----------------------------------------------------------------------------------------
        /// Iterator to the last element.
        /// ----------------------------------------------------------------------------------------
        constexpr TIter end() const noexcept
        {
            return TIter{ m_arr + m_count };
        }

    //// -------------------------------------------------------------------------------------------
    //// Access
    //// -------------------------------------------------------------------------------------------

    public:
        /// ----------------------------------------------------------------------------------------
        /// Get pointer to underlying array.
        /// ----------------------------------------------------------------------------------------
        constexpr const T* Data() const noexcept;

        /// ----------------------------------------------------------------------------------------
        /// Get count of elements.
        /// ----------------------------------------------------------------------------------------
        constexpr usize Count() const noexcept;

        /// ----------------------------------------------------------------------------------------
        /// Is range empty.
        /// ----------------------------------------------------------------------------------------
        constexpr bool IsEmpty() const noexcept;

    //// -------------------------------------------------------------------------------------------
    //// Fields.
    //// -------------------------------------------------------------------------------------------

    protected:
        const T* m_arr;
        usize m_count;
    };
}
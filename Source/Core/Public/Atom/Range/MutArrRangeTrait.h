#pragma once
#include "MutJumpRangeTrait.h"
#include "ArrRangeTrait.h"
#include "Atom/Contracts.h"

namespace Atom
{
    /// --------------------------------------------------------------------------------------------
    /// User defined implementation for [`MutArrRangeTrait`].
    /// --------------------------------------------------------------------------------------------
    template <typename TRange>
    class MutArrRangeTraitImpl;

    /// --------------------------------------------------------------------------------------------
    /// Requirements for [`MutArrRangeTraitImpl`].
    /// 
    /// # To Do: Implement this.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange>
    concept RMutArrRangeTraitImpl = RDefaultConstructible<MutArrRangeTraitImpl<TRange>>;

    /// --------------------------------------------------------------------------------------------
    /// Implementation of [`MutArrRangeTrait`].
    /// 
    /// # To Do
    /// 
    /// - Add `iter()` and `iterEnd()` functions.
    /// --------------------------------------------------------------------------------------------
    template <typename TRangeImpl>
    class _MutArrRangeTraitImpl: public _MutRangeTraitImpl<TRangeImpl>
    {
        using Base = _MutRangeTraitImpl<TRangeImpl>;

    public:
        using TImpl = typename Base::TImpl;
        using TElem = typename Base::TElem;
        using TIter = typename Base::TIter;
        using TIterEnd = typename Base::TIterEnd;
        using TMutIter = typename Base::TMutIter;
        using TMutIterEnd = typename Base::TMutIterEnd;

    public:
        constexpr auto mutData() -> TElem*
        {
            return _impl.mutData();
        }

        constexpr auto count() const -> usize
        {
            return _impl.count();
        }

        constexpr auto mutAt(usize i) -> TElem&
        {
            return mutData()[i];
        }

        constexpr auto mutFront() -> TElem&
        {
            return mutAt(0);
        }

        constexpr auto mutBack() -> TElem&
        {
            debug_expects(count() > 0);

            return mutAt(count() - 1);
        }

        constexpr auto mutIter(usize i) -> TMutIter
        {
            return Base::mutIter().next(i);
        }

        using Base::mutIter;

    public:
        using Base::_impl;
    };

    /// --------------------------------------------------------------------------------------------
    /// Recrusive Trait Impl for [MutArrRange].
    /// --------------------------------------------------------------------------------------------
    template <typename TRangeTrait>
    class MutArrRangeTraitRecursive: public MutJumpRangeTraitRecursive<TRangeTrait>
    {
        using Base = MutJumpRangeTraitRecursive<TRangeTrait>;

    public:
        using TImpl = typename Base::TImpl;
        using TElem = typename Base::TElem;
        using TIter = typename Base::TIter;
        using TIterEnd = typename Base::TIterEnd;
        using TMutIter = typename Base::TMutIter;
        using TMutIterEnd = typename Base::TMutIterEnd;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////
    //// Access
    ////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        /// ----------------------------------------------------------------------------------------
        /// Get underlying ptr to arr.
        /// ----------------------------------------------------------------------------------------
        constexpr auto mutData() -> TElem*
        {
            return _impl.mutData();
        }

        /// ----------------------------------------------------------------------------------------
        /// Access element by index.
        ///
        /// # Parameters
        /// - `i`: Index of element to access.
        ///
        /// # Time Complexity
        /// Constant.
        /// ----------------------------------------------------------------------------------------
        constexpr auto mutAt(usize i) -> TElem&
        {
            expects(isIndexInRange(i), "Index is out of range.");

            return _impl.mutAt(i);
        }

        /// ----------------------------------------------------------------------------------------
        /// Access element by index.
        ///
        /// # Parameters
        /// - `i`: Index of element to access.
        ///
        /// # Time Complexity
        /// Constant.
        /// ----------------------------------------------------------------------------------------
        constexpr auto operator[](usize i) -> TElem&
        {
            debug_expects(isIndexInRange(i), "Index is out of range.");

            return _impl.mutAt(i);
        }

        using Base::operator[];

        /// ----------------------------------------------------------------------------------------
        /// Access first element.
        ///
        /// # Time Complexity
        /// Constant.
        /// ----------------------------------------------------------------------------------------
        constexpr auto mutFront() -> TElem&
        {
            debug_expects(not isEmpty(), "Range is empty.");

            return _impl.mutFront();
        }

        /// ----------------------------------------------------------------------------------------
        /// Access last element.
        ///
        /// # Time Complexity
        /// Constant.
        /// ----------------------------------------------------------------------------------------
        constexpr auto mutBack() -> TElem&
        {
            debug_expects(not isEmpty(), "Range is empty.");

            return _impl.mutBack();
        }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////
    //// Iteration
    ////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        /// ----------------------------------------------------------------------------------------
        /// Get iter to element at index `i`.
        ///
        /// # Parameters
        ///
        /// - `i`: Index of the element to get iter at.
        /// ----------------------------------------------------------------------------------------
        constexpr auto mutIter(usize i) const -> TMutIter
        {
            expects(isIndexInRange(i), "Index is out of range.");

            return _impl.mutIter(i);
        }

        using Base::mutIter;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////
    //// View
    ////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        /// ----------------------------------------------------------------------------------------
        /// # To Do: Review this.
        /// ----------------------------------------------------------------------------------------
        constexpr auto range(usize from, usize to) const {}

        /// ----------------------------------------------------------------------------------------
        /// # To Do: Review this.
        /// ----------------------------------------------------------------------------------------
        constexpr auto rangeFrom(usize from) const {}

        /// ----------------------------------------------------------------------------------------
        /// # To Do: Review this.
        /// ----------------------------------------------------------------------------------------
        constexpr auto rangeTo(usize to) const {}

    public:
        using Base::_impl;
        using Base::isIndexInRange;
        using Base::isEmpty;
    };

    /// --------------------------------------------------------------------------------------------
    /// Trait for [MutArrRange].
    /// --------------------------------------------------------------------------------------------
    template <typename TRange>
    requires(RMutArrRangeTraitImpl<TRange>)
    class MutArrRangeTrait: public MutArrRangeTraitRecursive<ArrRangeTraitRecursive<
        _MutArrRangeTraitImpl<_ArrRangeTraitImpl<MutArrRangeTraitImpl<TRange>>>>>
    {};
}

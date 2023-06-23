#pragma once
#include "IterReq.h"

namespace Atom
{
    /// --------------------------------------------------------------------------------------------
    /// Basic range requirements.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept _RRangeOf = requires(const TRange& range)
    {
        typename TRange::TElem;
        typename TRange::TIter;
        typename TRange::TIterEnd;

        { range.Iter() } -> RSameAs<typename TRange::TIter>;
        { range.IterEnd() } -> RSameAs<typename TRange::TIterEnd>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Basic mut range requirements.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept _RMutRangeOf = requires(TRange& range)
    {
        requires _RRangeOf<TRange, T>;

        typename TRange::TMutIter;
        typename TRange::TMutIterEnd;

        { range.MutIter() } -> RSameAs<typename TRange::TMutIter>;
        { range.MutIterEnd() } -> RSameAs<typename TRange::TMutIterEnd>;

        requires RConvertibleTo<typename TRange::TMutIter, typename TRange::TIter>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {Range} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RRangeOf = requires
    {
        requires _RRangeOf<TRange, T>;
        requires RIter<typename TRange::TIter, typename TRange::TIterEnd, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {MutRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RMutRangeOf = requires
    {
        requires _RMutRangeOf<TRange, T>;
        requires RMutIter<typename TRange::TIter, typename TRange::TIterEnd, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {FwdRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RFwdRangeOf = requires
    {
        requires _RRangeOf<TRange, T>;
        requires RFwdIter<typename TRange::TIter, typename TRange::TIterEnd, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {MutFwdRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RMutFwdRangeOf = requires
    {
        requires _RMutRangeOf<TRange, T>;
        requires RMutFwdIter<typename TRange::TMutIter, typename TRange::TMutIterEnd, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {BidiRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RBidiRangeOf = requires
    {
        requires _RRangeOf<TRange, T>;
        requires RBidiIter<typename TRange::TIter, typename TRange::TIterEnd, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {MutBidiRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RMutBidiRangeOf = requires
    {
        requires _RMutRangeOf<TRange, T>;
        requires RMutBidiIter<typename TRange::TMutIter, typename TRange::TMutIterEnd, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {JumpRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RJumpRangeOf = requires
    {
        requires _RRangeOf<TRange, T>;
        requires RJumpIter<typename TRange::TIter, typename TRange::TIterEnd, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {MutJumpRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RMutJumpRangeOf = requires
    {
        requires _RMutRangeOf<TRange, T>;
        requires RMutJumpIter<typename TRange::TMutIter, typename TRange::TMutIterEnd, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {ArrRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RArrRangeOf = requires
    {
        requires _RRangeOf<TRange, T>;
        requires RArrIter<typename TRange::TIter, typename TRange::TIterEnd, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {MutArrRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RMutArrRangeOf = requires
    {
        requires _RMutRangeOf<TRange, T>;
        requires RMutArrIter<typename TRange::TMutIter, typename TRange::TMutIterEnd, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {RevRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RRevRangeOf = requires
    {
        requires RBidiRangeOf<TRange, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {MutRevRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RMutRevRangeOf = requires
    {
        requires RMutBidiRangeOf<TRange, T>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {CommonRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RCommonRangeOf = requires
    {
        requires _RRangeOf<TRange, T>;
        requires RSameAs<typename TRange::TIter, typename TRange::TIter>;
    };

    /// --------------------------------------------------------------------------------------------
    /// Ensures {TRange} is {MutCommonRange} of type {T}.
    /// --------------------------------------------------------------------------------------------
    template <typename TRange, typename T>
    concept RMutCommonRangeOf = requires
    {
        requires _RRangeOf<TRange, T>;
        requires RSameAs<typename TRange::TMutIter, typename TRange::TMutIterEnd>;
    };
}
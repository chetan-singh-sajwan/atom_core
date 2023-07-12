#pragma once
#include "RangeReq.h"
#include "ArrIter.h"
#include "InitList.h"

namespace Atom
{
    /// --------------------------------------------------------------------------------------------
    /// 
    /// --------------------------------------------------------------------------------------------
    template <tname... TArgs>
    struct Range;

    /// --------------------------------------------------------------------------------------------
    /// 
    /// --------------------------------------------------------------------------------------------
    template <tname _TIter, tname _TIterEnd>
    requires RIterPair<_TIter, _TIterEnd>
    struct Range<_TIter, _TIterEnd>
    {
    public:
        using TElem = tname _TIter::TElem;
        using TMutIter = _TIter;
        using TMutIterEnd = _TIterEnd;
        using TIter = _TIter;
        using TIterEnd = _TIterEnd;

    public:
        cexpr ctor Range(TIter iter, TIterEnd end) noex:
            _iter{ iter }, _end{ end } { }

    public:
        cexpr fn Iter() const noex -> TIter
        requires RIterPair<TIter, TIterEnd>
        {
            return TIter{ _iter };
        }

        cexpr fn IterEnd() const noex -> TIterEnd
        requires RIterPair<TIter, TIterEnd>
        {
            return TIterEnd{ _end };
        }

        cexpr fn MutIter() noex -> TMutIter
        requires RMutIterPair<TMutIter, TMutIterEnd>
        {
            return _iter;
        }

        cexpr fn MutIterEnd() noex -> TMutIterEnd
        requires RMutIterPair<TMutIter, TMutIterEnd>
        {
            return _end;
        }

        cexpr fn Count() const noex -> usize
        requires RJumpIterPair<TIter, TIterEnd>
        {
            return _end - _iter;
        }

        cexpr fn Data() const noex -> const TElem*
        requires RArrIterPair<TIter, TIterEnd>
        {
            return &*_iter;
        }

        cexpr fn Data() noex -> TElem*
        requires RMutArrIterPair<TIter, TIterEnd>
        {
            return &*_iter;
        }

    protected:
        TIter _iter;
        TIterEnd _end;
    };

    template <tname TIter, tname TIterEnd>
    requires RIterPair<TIter, TIterEnd>
    Range(TIter iter, TIterEnd end) -> Range<TIter, TIterEnd>;

    /// --------------------------------------------------------------------------------------------
    /// 
    /// --------------------------------------------------------------------------------------------
    template <tname T>
    struct Range<const T*, const T*>: Range<ArrIter<T>, ArrIter<T>>
    {
        using Base = Range<ArrIter<T>, ArrIter<T>>;

        cexpr ctor Range(const T* arr, const T* end) noex:
            Base{ arr, end } { }

        cexpr ctor Range(const T* arr, usize count) noex:
            Base{ arr, arr + count } { }

        template <usize count>
        cexpr ctor Range(const T(&arr)[count]) noex:
            Base{ arr, arr + count } { }
    };

    /// --------------------------------------------------------------------------------------------
    /// 
    /// --------------------------------------------------------------------------------------------
    template <tname T>
    struct Range<T*, T*>: Range<MutArrIter<T>, MutArrIter<T>>
    {
        using Base = Range<MutArrIter<T>, MutArrIter<T>>;

        cexpr ctor Range(T* arr, T* end) noex:
            Base{ arr, end } { }

        cexpr ctor Range(T* arr, usize count) noex:
            Base{ arr, arr + count } { }

        template <usize count>
        cexpr ctor Range(T(&arr)[count]) noex:
            Base{ arr, arr + count } { }
    };

    template <tname T>
    Range(T* iter, T* end) -> Range<T*, T*>;

    template <tname T>
    Range(T* iter, usize count) -> Range<T*, T*>;

    template <tname T, usize count>
    Range(T(&arr)[count]) -> Range<T*, T*>;

    /// --------------------------------------------------------------------------------------------
    /// 
    /// --------------------------------------------------------------------------------------------
    template <tname T>
    struct Range<InitList<T>>: Range<const T*, const T*>
    {
        using Base = Range<const T*, const T*>;

        cexpr ctor Range(const InitList<T>& init) noex:
            Base{ init.begin(), init.end() } { }
    };

    template <tname T>
    Range(const InitList<T>& init) -> Range<InitList<T>>;
}
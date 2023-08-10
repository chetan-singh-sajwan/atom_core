#pragma once
#include "_DynArrImplHelper.decl.h"
#include "Atom/Memory/DefaultMemAllocator.h"
#include "Atom/Invokable/Invokable.h"

namespace Atom
{
    template <typename T, typename TAlloc>
    class _DynArrImplBase
    {
    public:
        using TElem = T;

    public:
        constexpr ctor _DynArrImplBase() = default;

        constexpr ctor _DynArrImplBase(NullPtr):
            _arr{ nullptr }, _count{ 0 }, _capacity{ 0 }, _alloc{ } { }

    protected:
        constexpr fn _Data() const -> const T*
        {
            return _arr;
        }

        constexpr fn _Data() -> T*
        {
            return _arr;
        }

        constexpr fn _Data(T* arr) -> void
        {
            _arr = arr;
        }

        constexpr fn _Count() const -> usize
        {
            return _count;
        }

        constexpr fn _Count(usize count) -> void
        {
            _count = count;
        }

        constexpr fn _Capacity() const -> usize
        {
            return _capacity;
        }

        constexpr fn _Capacity(usize cap) -> void
        {
            _capacity = cap;
        }

        constexpr fn _AllocMem(usize size) -> T*
        {
            return (T*)_alloc.Alloc(size);
        }

        constexpr fn _DeallocMem(T* mem) -> void
        {
            return _alloc.Dealloc(mem);
        }

        constexpr fn _CalcCapGrowth(usize required) const -> usize
        {
            // return Math::Max(_Count() + required, _Capacity() * 2);
            return required;
        }

        constexpr fn _Swap(_DynArrImplBase& that) -> void
        {
            _DynArrImplBase tmp = that;
            self = that;
            that = tmp;
        }

        constexpr fn _Move(_DynArrImplBase& that) -> void
        {
            self = that;
            that = _DynArrImplBase(nullptr);
        }

    protected:
        T* _arr;
        usize _count;
        usize _capacity;
        TAlloc _alloc;
    };

    template <typename T, typename TAlloc = DefaultMemAllocator>
    class DynArr extends _DynArrImplHelper<_DynArrImplBase<T, TAlloc>>
    {
        priv using Base = _DynArrImplHelper<_DynArrImplBase<T, TAlloc>>;
        priv using BaseImpl = _DynArrImplBase<T, TAlloc>;

        /// ----------------------------------------------------------------------------------------
        /// DefCtor.
        /// ----------------------------------------------------------------------------------------
        pub constexpr ctor DynArr() = default;

        /// ----------------------------------------------------------------------------------------
        /// NullCtor.
        /// ----------------------------------------------------------------------------------------
        pub constexpr ctor DynArr(NullPtr):
            Base{BaseImpl{ nullptr }} { }

        /// ----------------------------------------------------------------------------------------
        /// ParamCtor.
        /// ----------------------------------------------------------------------------------------
        pub template <typename TRange>
        requires RRangeOf<TRange, T>
        constexpr ctor DynArr(const TRange& range):
            Base{BaseImpl{ nullptr }}
        {
            self.InsertBack(range);
        }

        /// ----------------------------------------------------------------------------------------
        /// CopyCtor.
        /// ----------------------------------------------------------------------------------------
        pub constexpr ctor DynArr(const DynArr& that):
            Base{BaseImpl{ nullptr }}
        {
            self.InsertBack(that);
        }

        /// ----------------------------------------------------------------------------------------
        /// CopyOper.
        /// ----------------------------------------------------------------------------------------
        pub constexpr fn operator=(const DynArr& that) -> DynArr&
        {
            self.Clear();
            self.InsertBack(that);
            return self;
        }

        /// ----------------------------------------------------------------------------------------
        /// MoveCtor.
        /// ----------------------------------------------------------------------------------------
        pub constexpr ctor DynArr(DynArr&& that):
            Base{BaseImpl{ mov(that) }} { }

        /// ----------------------------------------------------------------------------------------
        /// MoveOper.
        /// ----------------------------------------------------------------------------------------
        pub constexpr fn operator=(DynArr&& that) -> DynArr&
        {
            DynArr tmp = mov(that);
            self._Swap(tmp);
            return self;
        }

        /// ----------------------------------------------------------------------------------------
        /// Dtor.
        /// ----------------------------------------------------------------------------------------
        pub constexpr dtor DynArr()
        {
            self.Clear();
            self.Release();
        }
    };
}
#pragma once
#include "RangeReq.h"
#include "Atom/Invokable/Invokable.h"

namespace Atom
{
    class RangeModifier
    {
    public:
        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <tname TRange, tname TPred>
        requires RRange<TRange>
            and RInvokable<TPred, bool(const tname TRange::TElem&)>
        cexpr fn RemoveIf(TRange& range, TPred&& pred) -> usize
        {
            usize count = 0;
            for (auto it = range.iter(); it != range.iterEnd(); it++)
            {
                if (pred(*it))
                {
                    it = range.RemoveAt(it);
                    count++;
                }
            }

            return count;
        }
    };
}
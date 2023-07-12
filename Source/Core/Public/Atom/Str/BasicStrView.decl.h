#pragma once
#include "_StrImpl.decl.h"
#include "Atom/Containers/ArrView.decl.h"

namespace Atom
{
    template <tname TEncoding>
    using BasicStrView = _StrImpl
    <
        TEncoding,
        ArrView<BasicChar<TEncoding>>
    >;
}
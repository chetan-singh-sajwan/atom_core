#pragma once
#include "_StrImpl.decl.h"
#include "Atom/Containers/StaticArr.decl.h"

namespace Atom
{
    // TODO: Fix this, cannot inherit to preserve aggregate initialization.
    template <tname TEncoding, usize Size>
    using BasicStaticStr = StaticArr<BasicChar<TEncoding>, Size>;
    // using BasicStaticStr = _StrImpl
    // <
    //     TEncoding,
    //     StaticArr<BasicChar<TEncoding>, Size>
    // >;
}
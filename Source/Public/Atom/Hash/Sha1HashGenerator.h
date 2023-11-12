#pragma once
extern "C"
{
#include "WjCryptLib_Sha1.h"
}

#include "Private/T1HashGenerator.h"
#include "Sha1Hash.h"

namespace Atom::Private
{
    class Sha1GeneratorImpl
    {
    public:
        auto Initialize()
        {
            Sha1Initialise(&_context);
        }

        auto Update(ConstMemPtr<void> data, uint32_t dataSize)
        {
            Sha1Update(&_context, data.unwrap(), dataSize);
        }

        auto Calculate(Sha1Hash& hash)
        {
            Sha1Finalise(&_context, reinterpret_cast<SHA1_HASH*>(hash.bytes.mutMem().unwrap()));
        }

    public:
        Sha1Context _context;
    };
}

namespace Atom
{
    using Sha1HashGenerator = Private::T1HashGenerator<Sha1Hash, Private::Sha1GeneratorImpl>;
}

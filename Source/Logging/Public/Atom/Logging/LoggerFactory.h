#pragma once
#include "Atom/Logging/Logger.h"
#include "Atom/Logging/SimpleLogger.h"

namespace Atom::Logging
{
    class LoggerFactory
    {
    public:
        fn CreateLogger(Str name) -> LoggerPtr
        {
            return MAKE_LOGGER<SimpleLoggerST>(mov(name));
        }
    };

    inline fn GET_LOGGER_FACTORY() -> LoggerFactory&
    {
        static LoggerFactory instance;
        return instance;
    }

    inline fn CREATE_LOGGER(auto&&... args) -> LoggerPtr
    {
        return GET_LOGGER_FACTORY().CreateLogger(fwd(args)...);
    }
}
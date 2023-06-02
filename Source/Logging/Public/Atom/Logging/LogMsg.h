#pragma once
#include "Internal/Core.h"

#include "Atom/Chrono.h"
#include "Atom/String.h"

#include "fmt/chrono.h" // TODO: Remove this

namespace Atom::Logging
{
    /// --------------------------------------------------------------------------------------------
    /// ELogLevel is used to define the level of the log.
    /// --------------------------------------------------------------------------------------------
    enum class ELogLevel: byte
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Fatal,
        OFF         ///< Used to indicate logging is off.
    };

    /// --------------------------------------------------------------------------------------------
    /// Lightweight object containing all the details of the log.
    /// --------------------------------------------------------------------------------------------
    struct LogMsg
    {
        /// ----------------------------------------------------------------------------------------
        /// Message of the log.
        /// ----------------------------------------------------------------------------------------
        StringView msg;

        /// ----------------------------------------------------------------------------------------
        /// Name of the logger through which this message was logged.
        /// ----------------------------------------------------------------------------------------
        StringView loggerName;

        /// ----------------------------------------------------------------------------------------
        /// Level of this message.
        /// ----------------------------------------------------------------------------------------
        ELogLevel lvl;

        /// ----------------------------------------------------------------------------------------
        /// Time when this message was logged.
        /// 
        /// This is necessary to store as the message may be logged asynchronously or may face 
        /// some latency in writing.
        /// ----------------------------------------------------------------------------------------
        TimePoint time;
    };
}

namespace Atom
{
    template < >
    struct StringViewConverter<Logging::ELogLevel>
    {
        constexpr StringView Convert(Logging::ELogLevel in_lvl) noexcept
        {
            switch (in_lvl)
            {
                case Logging::ELogLevel::Trace : return TEXT("Trace"); break;
                case Logging::ELogLevel::Debug : return TEXT("Debug"); break;
                case Logging::ELogLevel::Info  : return TEXT("Info");  break;
                case Logging::ELogLevel::Warn  : return TEXT("Warn");  break;
                case Logging::ELogLevel::Error : return TEXT("Error"); break;
                case Logging::ELogLevel::Fatal : return TEXT("Fatal"); break;
                case Logging::ELogLevel::OFF   : return TEXT("OFF");   break;
                default                        : return TEXT("UNKNOWN");
            }
        }
    };

    static_assert(RStrFmtArgFmtable<Logging::ELogLevel>, "ELogLevel is not formattable.");
}

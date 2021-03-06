#pragma once

#include <cstdint>
#include <memory>


class QDateTime;


namespace Vam { namespace Logger {

enum class VQLogLevel : int;

class LogMessage
{
public:
    LogMessage( const QDateTime &&time,
                VQLogLevel level,
                std::uint64_t threadId,
                const std::string &module,
                const std::string &&method,
                int lineNum,
                const std::string &message );

    LogMessage( const QDateTime &&time,
                VQLogLevel level,
                std::uint64_t threadId,
                const std::string &module,
                const std::string &&method,
                int lineNum,
                std::string &&message );

    LogMessage( const QDateTime &&time,
                VQLogLevel level,
                std::uint64_t threadId,
                const std::string &&module,
                const std::string &&method,
                int lineNum,
                std::string &&message );

    const VQLogLevel & logLevel() const;

    const QDateTime & time() const;

    const std::uint64_t & threadId() const;

    const std::string & moduleName() const;

    const std::string & methodName() const;

    const int & lineNum() const;

    const std::string & message() const;

    std::string & mutableMessage() const;

    ~LogMessage();

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};

} }

#pragma once
#include <string>

namespace teletrack_sim
{

    class IPublisher
    {
    public:
        virtual ~IPublisher() = default;

        virtual bool connect() = 0;
        virtual bool publish(const std::string &topic, const std::string &message, int qos = 0) = 0;
        virtual void disconnect() = 0;
        virtual bool isConnected() const = 0;
    };

} // namespace teletrack_sim

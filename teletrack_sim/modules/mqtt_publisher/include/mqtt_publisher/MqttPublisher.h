#pragma once

#include <string>
#include <memory>

namespace mqtt
{
    class async_client; // Forward declaration
}

namespace teletrack
{

    class MqttPublisher
    {
    public:
        MqttPublisher(const std::string &serverUri, const std::string &clientId);
        ~MqttPublisher();

        bool connect();
        bool publish(const std::string &topic, const std::string &message, int qos = 0);
        void disconnect();
        bool isConnected() const;

    private:
        std::string serverUri_;
        std::string clientId_;
        std::unique_ptr<mqtt::async_client> client_;
        bool connected_;
    };

}

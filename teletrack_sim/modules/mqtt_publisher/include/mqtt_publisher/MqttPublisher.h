#pragma once
#include "mqtt_publisher/IPublisher.h"
#include <memory>
#include <string>

namespace mqtt
{
    class async_client; // Forward declare Paho MQTT client
}

namespace teletrack_sim
{

    class MqttPublisher : public IPublisher
    {
    public:
        MqttPublisher(const std::string &serverUri, const std::string &clientId);
        ~MqttPublisher();

        bool connect() override;
        bool publish(const std::string &topic, const std::string &message, int qos = 0) override;
        void disconnect() override;
        bool isConnected() const override;

    private:
        std::string serverUri_;
        std::string clientId_;
        std::unique_ptr<mqtt::async_client> client_;
        bool connected_;
    };

} // namespace teletrack_sim

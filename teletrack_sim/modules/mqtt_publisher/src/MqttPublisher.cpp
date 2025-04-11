#include "mqtt_publisher/MqttPublisher.h"
#include <mqtt/async_client.h>
#include <iostream>

namespace teletrack_sim
{
    MqttPublisher::MqttPublisher(const std::string &serverUri, const std::string &clientId)
        : serverUri_(serverUri),
          clientId_(clientId),
          connected_(false)
    {
        client_ = std::make_unique<mqtt::async_client>(serverUri_, clientId_);
    }

    MqttPublisher::~MqttPublisher()
    {
        if (connected_)
        {
            disconnect();
        }
    }

    bool MqttPublisher::connect() {}

    bool MqttPublisher::publish(const std::string &topic, const std::string &message, int qos = 0)
    {
        // Check if MQTT is connected

        // Do Try Catch
    }

    void MqttPublisher::disconnect()
    {

        // If conncetd is false, return
        if (!connected_)
            return;

        try
        {
            // Initialise disconnection from Broker
            client_->disconnect()->wait();
            // Set connected_ to false (disconnected)
            connected_ = false;
            // Printout message
            std::cout << "[MQTT] Disconnected from Broker \n";
        }
        catch (const std::exception &e)
        {
            std::cerr << "[MQTT] Connection Failed" << e.what() << std::endl;
        }
    }

    bool MqttPublisher::isConnected() const
    {
        return connected_;
    }
}
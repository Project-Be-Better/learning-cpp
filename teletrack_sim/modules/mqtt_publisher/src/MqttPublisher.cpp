#include "mqtt_publisher/MqttPublisher.h"
#include <mqtt/async_client.h>
#include <iostream>

namespace teletrack
{

    MqttPublisher::MqttPublisher(const std::string &serverUri, const std::string &clientId)
        : serverUri_(serverUri), clientId_(clientId), connected_(false)
    {
        client_ = std::make_unique<mqtt::async_client>(serverUri_, clientId_);
    }

    MqttPublisher::~MqttPublisher()
    {
        if (connected_)
            disconnect();
    }

    bool MqttPublisher::connect()
    {
        try
        {
            mqtt::connect_options options;
            options.set_clean_session(true);
            options.set_keep_alive_interval(20);

            client_->connect(options)->wait();
            connected_ = true;
            std::cout << "Connected to MQTT broker.\n";
            return true;
        }
        catch (const mqtt::exception &ex)
        {
            std::cerr << "MQTT Connect failed: " << ex.what() << "\n";
            return false;
        }
    }

    bool MqttPublisher::publish(const std::string &topic, const std::string &message, int qos)
    {
        if (!connected_)
            return false;

        try
        {
            auto msg = mqtt::make_message(topic, message);
            msg->set_qos(qos);
            client_->publish(msg)->wait();
            return true;
        }
        catch (const mqtt::exception &ex)
        {
            std::cerr << "MQTT Publish failed: " << ex.what() << "\n";
            return false;
        }
    }

    void MqttPublisher::disconnect()
    {
        try
        {
            client_->disconnect()->wait();
            connected_ = false;
        }
        catch (const mqtt::exception &ex)
        {
            std::cerr << "MQTT Disconnect failed: " << ex.what() << "\n";
        }
    }

    bool MqttPublisher::isConnected() const
    {
        return connected_;
    }

}

#pragma once
#include <string>

namespace teletrack_sim
{
    // This is an interface (abstract class) that defines a contract for any publisher class
    class IPublisher
    {
    public:
        // Virtual destructor allows proper cleanup when deleting derived class objects through base class pointers
        virtual ~IPublisher() = default;

        // Connect to an MQTT broker (server)
        // Returns true if connection was successful, false otherwise
        virtual bool connect() = 0;

        // Publish a message to a specific topic
        // Parameters:
        //   - topic: The channel/subject where the message is published
        //   - message: The actual content being sent
        //   - qos: Quality of Service level (0 = at most once, 1 = at least once, 2 = exactly once)
        // Returns true if publishing was successful
        virtual bool publish(const std::string &topic, const std::string &message, int qos = 0) = 0;

        // Disconnect from the MQTT broker
        virtual void disconnect() = 0;

        // Check if currently connected to the broker
        // Returns true if connected, false otherwise
        virtual bool isConnected() const = 0;
    };
}
#include <gtest/gtest.h>
#include "mqtt_publisher/MqttPublisher.h"

using namespace teletrack;

TEST(MqttPublisherTest, ConnectDisconnect)
{
    MqttPublisher publisher("tcp://localhost:1883", "testClient");
    ASSERT_TRUE(publisher.connect());
    ASSERT_TRUE(publisher.isConnected());
    publisher.disconnect();
    ASSERT_FALSE(publisher.isConnected());
}

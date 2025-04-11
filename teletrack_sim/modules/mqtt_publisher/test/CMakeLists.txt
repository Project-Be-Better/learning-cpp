add_executable(test_mqtt_publisher MqttPublisherTest.cpp)
target_link_libraries(test_mqtt_publisher
    mqtt_publisher
    GTest::gtest_main
)
add_test(NAME test_mqtt_publisher COMMAND test_mqtt_publisher)

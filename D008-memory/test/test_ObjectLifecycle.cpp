#include <gtest/gtest.h>
#include "ObjectLifecycle.h"
#include <sstream>
#include <iostream>

// Utility to capture stdout for testing
class OutputCapture
{
public:
    OutputCapture()
    {
        oldBuffer = std::cout.rdbuf(captureStream.rdbuf());
    }

    ~OutputCapture()
    {
        std::cout.rdbuf(oldBuffer);
    }

    std::string getOutput() const
    {
        return captureStream.str();
    }

private:
    std::stringstream captureStream;
    std::streambuf *oldBuffer;
};

TEST(TrackerTest, ConstructorDestructorMessages)
{
    // Capture output
    OutputCapture capture;

    // Create a tracker object that should output constructor message
    {
        Tracker tracker("TestObject");
        std::string output = capture.getOutput();
        EXPECT_TRUE(output.find("[Constructor] TestObject") != std::string::npos);
    }

    // After the block, destructor should be called
    std::string finalOutput = capture.getOutput();
    EXPECT_TRUE(finalOutput.find("[Destructor] TestObject") != std::string::npos);
}

TEST(LifecycleFunctionsTest, FunctionsExist)
{
    // Just verify these functions can be called without crashing
    createStatic();
    createAutomatic();
    createHeap();
    createTemporary();
    SUCCEED();
}
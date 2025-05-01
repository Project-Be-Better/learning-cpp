#include <iostream>
#include <list>
#include <string>
#include <algorithm>

/**
 * Target defines domain specific interface used by client code
 * Also called the client interface
 */
class Target
{
    // Default behavior of target
public:
    virtual ~Target() = default;

    virtual std::string Request() const
    {
        return "Client: Default target's behavior";
    };
};

/**
 * Also called Service
 * Adaptee needs an adaptation to talk to the target
 */
class Adaptee
{
public:
    std::string SpecificRequest() const
    {
        return ".eetpadA eht fo roivaheb laicepS";
    };
};

/**
 * Adapter lets adaptee work with Adapter
 * Adapter implements Target/Client interface
 */
class Adapter : public Target
{
private:
    Adaptee *adaptee_;

public:
    Adapter(Adaptee *adaptee) : adaptee_(adaptee) {};
    ~Adapter() {};

    // Override the Request from the adapter
    std::string Request() const override
    {
        // IMplement the specificMethod translation
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter Translated << " + to_reverse + "\n";
    };
};

/**
 * Client code talks to all classes that implements target interface
 */
void ExecuteClientCode(const Target *target)
{
    std::cout << target->Request() << "\n";
};

void clientCode()
{
    std::cout << "Client: I can work fine with target objects \n";

    // Client code runs target without adapter
    Target *target = new Target;
    ExecuteClientCode(target);

    std::cout << "Adaptee: Do you understand the words coming out of me? \n";

    // Service Trying to ping the target
    Adaptee *adaptee = new Adaptee;
    std::cout << "Adaptee: " << adaptee->SpecificRequest() << " \n";

    std::cout << "Client: Let me get an adapter for you \n";
    Adapter *adapter = new Adapter(adaptee);
    ExecuteClientCode(adapter);

    delete target;
    delete adaptee;
    delete adapter;
};

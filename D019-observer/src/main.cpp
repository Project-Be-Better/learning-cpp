#include <iostream>
#include <list>
#include <string>

// Subscriber Interface
class IObserver
{
public:
    virtual ~IObserver() {};
    virtual void Update(const std::string &message_from_subject) = 0;
};

// Publisher Interface
class IObject
{
};

class Observer : public IObserver
{
public:
    Observer() {};

    virtual ~Observer()
    {
        std::cout << "Observer " << this->number_ << "is deleted \n";
    }

private:
    int number_;
};

void clientCode()
{
    std::cout << "Running Client Code \n";
};

int main()
{
    std::cout << "Running Observer tests.. \n";
    clientCode();
    return 0;
}
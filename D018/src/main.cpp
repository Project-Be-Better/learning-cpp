#include <iostream>
// #include "gnss.h"

// PRODUCT

/**
 * Product interface declares all the operations that the concrete products must implement
 */
class Product
{
public:
    virtual ~Product() {};
    virtual std::string Operation() const = 0;
};

// CONCRETE PRODUCT

/**
 * Concrete products must implement various implementations of the Product Interface
 */
class ConcreteProduct1 : public Product
{
public:
    std::string Operation() const override
    {
        return "{Result of the ConcreteProduct1}";
    }
};
class ConcreteProduct2 : public Product
{
public:
    std::string Operation() const override
    {
        return "{Result of the ConcreteProduct2}";
    }
};

// CREATOR

/**
 * Declares a factory method that retuns an object of Product Class
 * Creator's subclasses usually provide a implementation of the method
 *
 * Contains the business logic
 */
class Creator
{
public:
    virtual ~Creator() {};
    virtual Product *FactoryMethod() const = 0;

    std::string SomeOperation() const
    {
        // Call factory method to create Product Object
        Product *product = this->FactoryMethod();

        // Use the product

        std::string result = "CREATOR: Creator's code has been worked with " + product->Operation();
        delete product;
        return result;
    };
};

// CONCRETE CREATOR

class ConcreteCreator1 : public Creator
{
public:
    Product *FactoryMethod() const override
    {
        return new ConcreteProduct1();
    };
};
class ConcreteCreator2 : public Creator
{
public:
    Product *FactoryMethod() const override
    {
        return new ConcreteProduct2();
    };
};

// CLIENT

void ClientCode(const Creator &creator)
{
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
              << creator.SomeOperation() << std::endl;
}

int main()
{
    std::cout << "App launched with Concrete Creator \n";

    Creator *creator1 = new ConcreteCreator1();
    ClientCode(*creator1);

    std::cout << std::endl;

    Creator *creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator1;
    delete creator2;

    return 0;
}
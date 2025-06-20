#include <iostream>
#include <string>

/*
This code demonstrates the Factory Method design pattern.
The Factory Method pattern defines an interface for creating objects,
but lets subclasses decide which class to instantiate.

In this example:
    - AnimalFactory is an abstract factory with a method createAnimal().
    - DogFactory and CatFactory are concrete factories that create Dog and Cat objects.
    - The main function selects a factory at runtime based on user input,
    then uses the factory to create an Animal object without knowing its concrete type.

This pattern promotes loose coupling by eliminating the need to bind application-specific
classes into the code. The code only relies on the abstract AnimalFactory and Animal interfaces.
*/

// Product interface
class Animal {
public:
    virtual void speak() const = 0;
    virtual ~Animal() {}
};

// Concrete Product 1
class Dog : public Animal {
public:
    void speak() const {
        std::cout << "Woof! I am a Dog." << std::endl;
    }
};

// Concrete Product 2
class Cat : public Animal {
public:
    void speak() const {
        std::cout << "Meow! I am a Cat." << std::endl;
    }
};

// Creator (Factory) interface
class AnimalFactory {
public:
    virtual Animal* createAnimal() const = 0;
    virtual ~AnimalFactory() {}
};

// Concrete Factory 1
class DogFactory : public AnimalFactory {
public:
    Animal* createAnimal() const {
        return new Dog();
    }
};

// Concrete Factory 2
class CatFactory : public AnimalFactory {
public:
    Animal* createAnimal() const {
        return new Cat();
    }
};

int main() {
    // Choose a factory at runtime
    AnimalFactory* factory = nullptr;
    std::string choice;
    std::cout << "Enter animal type (dog/cat): ";
    std::cin >> choice;

    if (choice == "dog") {
        factory = new DogFactory();
    } else if (choice == "cat") {
        factory = new CatFactory();
    } else {
        std::cout << "Unknown animal type." << std::endl;
        return 1;
    }

    // Use the factory to create an Animal
    Animal* myAnimal = factory->createAnimal();
    myAnimal->speak();

    // Clean up
    delete myAnimal;
    delete factory;

    return 0;
}
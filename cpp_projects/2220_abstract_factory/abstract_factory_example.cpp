#include <iostream>
#include <string>

/*
This code demonstrates the Abstract Factory design pattern.
The purpose of this pattern is to provide an interface for creating families 
of related or dependent objects (such as Buttons and Checkboxes) without specifying 
their concrete classes.

It allows the client code to create UI elements for different operating systems 
(Windows or Mac) using the same interface, promoting consistency and flexibility.
*/

// Abstract Product A
class Button {
public:
    virtual void paint() const = 0;
    virtual ~Button() {}
};

// Abstract Product B
class Checkbox {
public:
    virtual void paint() const = 0;
    virtual ~Checkbox() {}
};

// Concrete Product A1
class WinButton : public Button {
public:
    void paint() const {
        std::cout << "Rendering a Windows-style Button.\n";
    }
};

// Concrete Product B1
class WinCheckbox : public Checkbox {
public:
    void paint() const {
        std::cout << "Rendering a Windows-style Checkbox.\n";
    }
};

// Concrete Product A2
class MacButton : public Button {
public:
    void paint() const {
        std::cout << "Rendering a Mac-style Button.\n";
    }
};

// Concrete Product B2
class MacCheckbox : public Checkbox {
public:
    void paint() const {
        std::cout << "Rendering a Mac-style Checkbox.\n";
    }
};

// Abstract Factory
class GUIFactory {
public:
    virtual Button* createButton() const = 0;
    virtual Checkbox* createCheckbox() const = 0;
    virtual ~GUIFactory() {}
};

// Concrete Factory 1
class WinFactory : public GUIFactory {
public:
    Button* createButton() const {
        return new WinButton();
    }
    Checkbox* createCheckbox() const {
        return new WinCheckbox();
    }
};

// Concrete Factory 2
class MacFactory : public GUIFactory {
public:
    Button* createButton() const {
        return new MacButton();
    }
    Checkbox* createCheckbox() const {
        return new MacCheckbox();
    }
};

// Client code
void renderUI(const GUIFactory& factory) {
    Button* btn = factory.createButton();
    Checkbox* chk = factory.createCheckbox();
    btn->paint();
    chk->paint();
    delete btn;
    delete chk;
}

int main() {
    std::string os;
    std::cout << "Enter OS type (win/mac): ";
    std::cin >> os;

    GUIFactory* factory = nullptr;
    if (os == "win") {
        factory = new WinFactory();
    } else if (os == "mac") {
        factory = new MacFactory();
    } else {
        std::cout << "Unknown OS type.\n";
        return 1;
    }

    renderUI(*factory);

    delete factory;
    return 0;
}
/*
    Adapter Design Pattern Example in C++

    Purpose:
    The Adapter pattern allows objects with incompatible interfaces to work together.
    It acts as a bridge between two incompatible interfaces by wrapping an existing class with a new interface.
    This is useful when you want to use a class that does not match the interface your code expects.

    In this example, we have a legacy class (OldPrinter) with an incompatible interface.
    We create an adapter (PrinterAdapter) so that it can be used where a modern Printer interface is expected.
*/

#include <iostream>
#include <string>

// Target interface (what the client expects)
class Printer {
public:
    virtual void print(const std::string& text) = 0;
    virtual ~Printer() {}
};

// Adaptee (existing class with a different interface)
class OldPrinter {
public:
    void oldPrintMethod(const std::string& text) {
        std::cout << "[OldPrinter] " << text << std::endl;
    }
};

// Adapter (makes OldPrinter compatible with Printer)
class PrinterAdapter : public Printer {
    OldPrinter* adaptee;
public:
    PrinterAdapter(OldPrinter* adaptee) : adaptee(adaptee) {}
    void print(const std::string& text) {
        adaptee->oldPrintMethod(text);
    }
};

int main() {
    OldPrinter legacyPrinter;
    Printer* printer = new PrinterAdapter(&legacyPrinter);

    printer->print("Hello, Adapter Pattern!");

    delete printer;
    return 0;
}
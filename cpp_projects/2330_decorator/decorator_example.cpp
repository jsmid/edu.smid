/*
    Decorator Design Pattern Example in C++

    Purpose:
    The Decorator pattern allows you to add new functionality to objects dynamically without altering their structure.
    It is useful for adhering to the Open/Closed Principle, enabling you to extend the behavior of objects at runtime.
    Decorators wrap the original object and provide additional features, making it easy to combine behaviors flexibly.

    In this example, we have a simple Text interface. We create a PlainText class and then decorate it with
    BorderDecorator and UppercaseDecorator to add borders and uppercase formatting, respectively.
*/

#include <iostream>
#include <string>

// Component interface
class Text {
public:
    virtual std::string render() const = 0;
    virtual ~Text() {}
};

// Concrete Component
class PlainText : public Text {
    std::string content;
public:
    PlainText(const std::string& text) : content(text) {}
    std::string render() const {
        return content;
    }
};

// Base Decorator
class TextDecorator : public Text {
protected:
    Text* wrappee;
public:
    TextDecorator(Text* component) : wrappee(component) {}
    virtual ~TextDecorator() { delete wrappee; }
    std::string render() const {
        return wrappee->render();
    }
};

// Concrete Decorator 1: Adds a border
class BorderDecorator : public TextDecorator {
public:
    BorderDecorator(Text* component) : TextDecorator(component) {}
    std::string render() const {
        std::string inner = wrappee->render();
        std::string border(inner.length(), '*');
        return border + "\n" + inner + "\n" + border;
    }
};

// Concrete Decorator 2: Converts text to uppercase
class UppercaseDecorator : public TextDecorator {
public:
    UppercaseDecorator(Text* component) : TextDecorator(component) {}
    std::string render() const {
        std::string inner = wrappee->render();
        for (size_t i = 0; i < inner.length(); ++i) {
            inner[i] = toupper(inner[i]);
        }
        return inner;
    }
};

int main() {
    Text* text = new PlainText("Hello, Decorator Pattern!");

    std::cout << "Plain text:\n" << text->render() << "\n\n";

    // Add a border
    Text* bordered = new BorderDecorator(new PlainText("Hello, Decorator Pattern!"));
    std::cout << "Bordered text:\n" << bordered->render() << "\n\n";
    delete bordered;

    // Add uppercase formatting
    Text* upper = new UppercaseDecorator(new PlainText("Hello, Decorator Pattern!"));
    std::cout << "Uppercase text:\n" << upper->render() << "\n\n";
    delete upper;

    // Combine decorators
    Text* fancy = new BorderDecorator(new UppercaseDecorator(new PlainText("Hello, Decorator Pattern!")));
    std::cout << "Bordered & Uppercase text:\n" << fancy->render() << "\n";
    delete fancy;

    delete text;
    return 0;
}
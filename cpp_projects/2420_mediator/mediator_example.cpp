/*
    Mediator Design Pattern Example in C++

    Purpose:
    The Mediator pattern defines an object (the Mediator) that encapsulates how a set of objects interact.
    It promotes loose coupling by preventing objects from referring to each other explicitly,
    allowing their interaction to be varied independently.
    This pattern is useful when you have a set of objects that communicate in complex ways,
    and you want to centralize the communication logic to make the system easier to maintain and extend.

    In this example, we demonstrate a simple chat room (Mediator) that manages communication between users (Colleagues).
    Users send messages to the chat room, which then delivers the messages to all other users.
*/

#include <iostream>
#include <string>
#include <vector>

// Forward declaration
class User;

// Mediator interface
class ChatRoomMediator {
public:
    virtual void showMessage(const User* user, const std::string& message) = 0;
    virtual void addUser(User* user) = 0;
    virtual ~ChatRoomMediator() {}
};

// Colleague interface
class User {
protected:
    ChatRoomMediator* mediator;
    std::string name;
public:
    User(const std::string& name, ChatRoomMediator* mediator)
        : name(name), mediator(mediator) {}
    virtual void send(const std::string& message) const = 0;
    virtual void receive(const std::string& sender, const std::string& message) const = 0;
    std::string getName() const { return name; }
    virtual ~User() {}
};

// Concrete Mediator
class ChatRoom : public ChatRoomMediator {
private:
    std::vector<User*> users;
public:
    void addUser(User* user) {
        users.push_back(user);
    }

    void showMessage(const User* sender, const std::string& message) {
        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i] != sender) {
                users[i]->receive(sender->getName(), message);
            }
        }
    }
};

// Concrete Colleague
class ChatUser : public User {
public:
    ChatUser(const std::string& name, ChatRoomMediator* mediator)
        : User(name, mediator) {}

    void send(const std::string& message) const {
        std::cout << "[" << name << "] sends: " << message << std::endl;
        mediator->showMessage(this, message);
    }

    void receive(const std::string& sender, const std::string& message) const {
        std::cout << "[" << name << "] receives from [" << sender << "]: " << message << std::endl;
    }
};

int main() {
    ChatRoom chatRoom;

    ChatUser alice("Alice", &chatRoom);
    ChatUser bob("Bob", &chatRoom);
    ChatUser charlie("Charlie", &chatRoom);

    chatRoom.addUser(&alice);
    chatRoom.addUser(&bob);
    chatRoom.addUser(&charlie);

    alice.send("Hello, everyone!");
    bob.send("Hi Alice!");
    charlie.send("Hey folks!");

    return 0;
}
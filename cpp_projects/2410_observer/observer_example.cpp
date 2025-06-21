/*
    Observer Design Pattern Example in C++

    Purpose:
    The Observer pattern defines a one-to-many dependency between objects so that when one object (the Subject)
    changes state, all its dependents (Observers) are notified and updated automatically.
    This pattern is useful for implementing distributed event handling systems, such as GUI listeners,
    messaging systems, or any scenario where multiple objects need to react to changes in another object.

    In this example, we demonstrate a simple weather station (Subject) that notifies display devices (Observers)
    whenever the temperature changes.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Observer interface
class Observer {
public:
    virtual void update(float temperature) = 0;
    virtual ~Observer() {}
};

// Concrete Observer 1
class PhoneDisplay : public Observer {
public:
    void update(float temperature) {
        std::cout << "[PhoneDisplay] Temperature updated: " << temperature << "°C\n";
    }
};

// Concrete Observer 2
class WindowDisplay : public Observer {
public:
    void update(float temperature) {
        std::cout << "[WindowDisplay] Temperature updated: " << temperature << "°C\n";
    }
};

// Subject interface
class Subject {
public:
    virtual void attach(Observer* obs) = 0;
    virtual void detach(Observer* obs) = 0;
    virtual void notify() = 0;
    virtual ~Subject() {}
};

// Concrete Subject
class WeatherStation : public Subject {
private:
    std::vector<Observer*> observers;
    float temperature;
public:
    WeatherStation() : temperature(0.0f) {}

    void attach(Observer* obs) {
        observers.push_back(obs);
    }

    void detach(Observer* obs) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), obs),
            observers.end()
        );
    }

    void setTemperature(float temp) {
        temperature = temp;
        notify();
    }

    void notify() {
        for (size_t i = 0; i < observers.size(); ++i) {
            observers[i]->update(temperature);
        }
    }
};

int main() {
    WeatherStation station;
    PhoneDisplay phone;
    WindowDisplay window;

    station.attach(&phone);
    station.attach(&window);

    std::cout << "Setting temperature to 23.5°C...\n";
    station.setTemperature(23.5f);

    std::cout << "Setting temperature to 19.0°C...\n";
    station.setTemperature(19.0f);

    station.detach(&window);

    std::cout << "Setting temperature to 25.0°C...\n";
    station.setTemperature(25.0f);

    return 0;
}
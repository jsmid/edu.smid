#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
/**
 * The Customer class represents a customer in a queue simulation.
 * 
 * Attributes:
 *   arrive: Arrival time.
 *   processTime: Time required to serve the customer.
 */
class Customer
{
private:
    long arrive;        // arrival time
    int processTime;    // time to serve the customer

public:
    Customer() { arrive = processTime = 0; }
    void set(long when);
    long when() const { return arrive; }
    int ptime() const { return processTime; }
};

#endif
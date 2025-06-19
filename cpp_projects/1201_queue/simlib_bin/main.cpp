#include <cstdlib>
#include <ctime>
#include <iostream>
#include <exception>

using namespace std;
#include "../simlib/include/simlib/queue.h"
#include "../simlib/include/simlib/customer.h"

const int MIN_PER_HR = 60;

bool new_customer(double x);   // did a new customer arrive?

// Main function for the queue simulation program.
// This program simulates a queue at an ATM, where customers arrive randomly and are served in order.
int main()
{
    srand(time(0));             // random initialization of rand()
    cout << "Queue simulation\n";
    cout << "Enter maximum queue length: ";
    int qs;
    cin >> qs; 
    Queue line(qs); // create a queue with the specified maximum length

    cout << "Enter number of simulation hours: ";
    int hours;
    cin >> hours;

    // one simulation cycle lasts one minute
    long cycle_limit = MIN_PER_HR * hours; // number of cycles
    cout << "Enter average number of customers per hour: ";
    double per_hour;
    cin >> per_hour;
    double min_per_cust;    // average time between customer arrivals
    min_per_cust = MIN_PER_HR / per_hour;

    Item temp;              // data for new customer
    long turnaways = 0;     // number of turned away customers
    long customers = 0;     // number of customers in queue
    long served = 0;        // number of served customers
    long sum_line = 0;      // total queue length
    long wait_time = 0;     // waiting time at the ATM
    long line_wait = 0;     // total waiting time in queue

    // simulation run
    for (int cycle = 0; cycle < cycle_limit; cycle++)
    {
        try {
            if (new_customer(min_per_cust)) // new customer
            {
                if (line.isfull()) 
                {
                    turnaways++;
                } else
                {
                    customers++;
                    temp.set(cycle);    // cycle = arrival time
                    line.enqueue(temp); // add new customer to queue
                }
            }

            if (wait_time <= 0 && !line.isempty())
            {
                line.dequeue(temp);         // serve next customer
                wait_time = temp.ptime();   // for wait_time minutes
                line_wait += cycle - temp.when();
                served++;
            }

            if (wait_time > 0) 
            {
                wait_time--;
            }
            sum_line += line.queuecount();
        } catch (exception & e) {
            cout << e.what() << "\n";
            cout.flush();
            return 1;
        }
    }

    // print results
    if (customers > 0) 
    {
        cout << "    customers accepted: " << customers << "\n";
        cout << "   customers served: " << served << "\n";
        cout << " customers turned away: " << turnaways << "\n";
        cout << "average queue length: ";
        cout.precision(2);
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout.setf(ios_base::showpoint);
        cout << (double) sum_line / cycle_limit << "\n";
        cout << " average wait time: "
            << (double) line_wait / served << " minutes\n";
    }
    else
    {
        cout << "No customers!\n";
    }

    cout.flush();
    return 0;
}

bool new_customer(double x)
{
    return (rand() * x / RAND_MAX < 1);
}

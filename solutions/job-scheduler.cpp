/*
Daily Coding Problem #10: Job Scheduler

This problem was asked by Apple.

Implement a job scheduler which takes in a function f and an integer n, and calls f after n milliseconds.
*/

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class JobScheduler {
public:
    // constructor that waits n seconds, then calls f
    JobScheduler(void (*f)(), int n);
    // keeps track of when the function is called to prove n milliseconds have passed
    bool functionCalled;
};

JobScheduler::JobScheduler(void (*f)(), int n) {
    functionCalled = false;
    this_thread::sleep_for(chrono::milliseconds(n));
    f();
    functionCalled = true;
}

void exampleFunction() {
    printf("exampleFunction called.\n");
}

int main() {
    // query user for delay length in ms
    int delay;
    printf("Enter function delay:\n> ");
    scanf("%d", &delay);

    // get current time
    auto begin = chrono::high_resolution_clock::now();

    // create JobScheduler - function will be called in n milliseconds
    JobScheduler js(&exampleFunction, delay);

    // wait for function to be called
    while(!js.functionCalled) {}

    // get current time
    auto end = chrono::high_resolution_clock::now();

    // calculate time difference
    auto dur = end - begin;

    // output time difference
    printf("Time elapsed: %lld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(dur).count());
    // average output is (delay + ~2)ms
    // the extra ~2 milliseconds are due to execution time of the instantiation and exampleFunction being called
    return 0;
}
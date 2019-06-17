/*
Daily Coding Problem #16: Order Log

This problem was asked by Twitter.

You run an e-commerce website and want to record the last N order ids in a log. Implement a data
structure to accomplish this, with the following API:

record(order_id): adds the order_id to the log
get_last(i): gets the ith last element from the log. i is guaranteed to be smaller than or equal
to N.

You should be as efficient with time and space as possible.
*/

#include <iostream>
#include <cstdlib>

using namespace std;

/*
For this problem I decided to do something different and create a wrapping array class: a data
structure that is a mix between an array and a queue.

This approach is better than a LinkedList because the get_last(index) function does not have to
move through the list looking for an index (an O(N) operation). Instead an array element is
accessed (an O(1) operation).

The reason one cannot use a normal array here is because we only want to record the last N entries.
This means we must stop recording the N+1th last entry when we have N entries and add another.
This works similarly to a queue (queue also does not have O(1) random access time).

My class has a last index that moves down the array and wraps back to the beginning that records
where the last element added. Each time a new element is added, the N+1th last element is
overwritten at the back index.
*/
class wrappingArray {
private:
    int* arr;
    int last;
public:
    int size;
    wrappingArray(int size);
    void record(int order_id);
    int get_last(int i);
};

wrappingArray::wrappingArray(int s) {
    arr = new int[size];
    for(int i = 0; i < s; i++) {
        arr[i] = -1;
    }
    size = s;
    last = 0;
}

void wrappingArray::record(int order_id) {
    arr[last] = order_id;
    last = (last + 1) % size;
}

int wrappingArray::get_last(int i) {
    if(i < 1 || i > size) {
        printf("Error: Invalid index: %d\n", i);
        return -1;
    }
    int ret = arr[(last - i + size) % size];
    if(ret == -1) {
        printf("Error: Invalid index: %d\n", i);
    }
    return ret;
}

int main() {
    int n;
    printf("Enter length of log:\n> ");
    cin >> n;
    wrappingArray arr(n);
    char command;
    int i;
    do {
        printf("Enter r for record, g for get_last, or q to quit:\n> ");
        cin >> command;
        if(command == 'r') {
            printf("Enter order id:\n> ");
            cin >> i;
            arr.record(i);
        } else if(command == 'g') {
            printf("Enter last index (1 = last element):\n> ");
            cin >> i;
            printf("%d", arr.get_last(i));
        } else if(command != 'q') {
            printf("Command not found: %c\n", command);
        }
    } while(command != 'q');
    return 0;
}
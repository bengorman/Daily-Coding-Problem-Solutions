/*
Daily Coding Problem #7: Decode Combinations

This problem was asked by Facebook.

Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, count the number of ways it can
be decoded.

For example, the message '111' would give 3, since it could be decoded as 'aaa', 'ka', and 'ak'.

You can assume that the messages are decodable. For example, '001' is not allowed.
*/

#include <iostream>
#include <cmath>

using namespace std;

/*
My approach to this problem involved tracking instances of consecutive 1's and 2's because these
numbers have the possibility of being the first digit in a double digit number. I refer to the
number of numbers in the set of consecutive numbers as 'overlap'.

For example, 121 returns 3 ({1,2,1}, {1,21}, {12,1}).

Overlap becomes more important as more numbers overlap.
For example,
121212 returns 13 (I won't list all the combinations here - you can write it out if you want to).

It turns out that the number of ways (for now) is the fibonacci function of the number of digits in
the overlap plus 1.

So for our previous examples:
121 : overlap of 3 -> fib(3+1) = 3
121212 : overlap of 6 -> fib(6+1) = 13

Overlap also counts the number after a set of consecutive 1's and 2's (because it could be the
second number in a two-digit number). This is not true in the case that the last digit and this
digit form a number > 26. So if the last digit in the sequence is a 2 and the number after is an
8, we do not count the 8.

This gets more complicated with zeros, however, because zeros can't be lonely.
For an overlapping set of numbers followed by a zero, the last 1 or 2 in the overlap can no longer
be considered, because it must pair with the zero. This decrements our overlap by 2 (1 for the last
1 or 2 and 1 for the following number (zero)).

Each overlapping sequence contributes to the number of ways to arrange the string as a whole.
For example,
125888233 has two overlaps : 125 and 23 (we're counting the number after, remember?).
The 125 overlap contributes fib(3+1)=3 and the 23 overlap contributes fib(2+1)=2.
We multiply these individual combinations to find the total number of combinations to get 6.
*/

// Binet's formula - O(~1) time to find the power/sqrt on x86 architecture
long fibonacci(int n) {
    double phi = (1 + sqrt(5)) / 2;
    return round(pow(phi, n) / sqrt(5));
}

// O(n) solution
int decodeCombinations(string numbers) {
    int overlap;
    int combinations = 1;
    for(int i = 0; i < numbers.size(); i++) {
        overlap = 1;
        // begin tracking consecutive 1's and 2's
        while((numbers[i] == '1' || numbers[i] == '2') && i != numbers.size() - 1) {
            if(numbers[i] == '2' && numbers[i+1] > '6') {
                // the last two-digit combo is > 26
                break;
            }
            // ending with a zero decrements overlap by 2 (see above)
            if(numbers[i+1] == '0') {
                overlap -= 2;
            }
            overlap++;
            i++;
        }
        combinations *= fibonacci(overlap + 1);
    }
    return combinations;
}

/*
taking input in the form

x1x2x3...xn

where xi is the ith number in the encoded message and n is the number of numbers in the message.
*/
int main() {
    string numStr;
    cin >> numStr;
    cout << decodeCombinations(numStr) << endl;
    return 0;
}

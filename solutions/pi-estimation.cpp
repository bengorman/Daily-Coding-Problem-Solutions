/*
Daily Coding Problem #14: Pi Estimation

This problem was asked by Google.

The area of a circle is defined as πr^2. Estimate π to 3 decimal places using a Monte Carlo method.

Hint: The basic equation of a circle is x2 + y2 = r2.
*/

#include <iostream>
#include <random>
#include <cmath>

using namespace std;

/*
This solution involves measuring a circle inscribed in a square.
Here the square's side-length is 2r, so its area is 4(r^2) and the circle's area is PI(r^2).
If we generate random points in the square, the probability that they will be within the circle
is the circle's area divided by the square's area, which is PI/4.
We count the proportion of points that fall inside and multiply by 4 to get PI.
As numTrials increases, the estimation becomes more accurate.
*/
double solution(int numTrials) {
    random_device rd;
    default_random_engine gen(rd());
    uniform_real_distribution<double> dist(-1000, 1000);

    double x, y;
    int numInside = 0;
    for (int i = 0; i < numTrials; i++)
    {
        x = dist(gen);
        y = dist(gen);
        numInside += (sqrt(pow(x, 2) + pow(y, 2)) < 1000 ? 1 : 0);
    }
    return (numInside / (double)numTrials) * 4;
}

int main() {
    int n;
    cout << "input number of monte carlo trials (100000000+ for 3 digit accuracy):\n> ";
    cin >> n;
    cout << solution(n) << endl;
    return 0;
}
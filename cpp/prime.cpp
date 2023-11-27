#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

int main()
{
    int last = 10000;
    int found = 4;   // we already know 2, 3, 5, 7
    const int arraylength = (int)(last / log(last));
    int primes[10000] = {3, 5, 7};
    cout << "Calculating prime numbers until " << last << endl;
    auto start = chrono::high_resolution_clock::now();
    for (int number = 11; number < last; number += 2)
    {
        int prime = 1;
        for (int divider = 3; divider < (int)(sqrt(number)) + 1; divider += 2)
        {
            if (number % divider == 0)
            {
                prime = 0;
                break;
            }
        }
        if (prime ==  1)
        {
            found += 1;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    cout << "Found " << found << " prime numbers." << endl;
    cout << "This took " << fixed << time_taken << " seconds." << endl;
}

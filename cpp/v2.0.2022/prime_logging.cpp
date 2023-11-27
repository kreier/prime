#include <iostream>
#include <cmath>
#include <chrono>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    const int scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000};
    const int reference[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534};
    for (int i = 0; i < 9; i++)
    {
        cout << scope[i] << " ";
        int last = scope[i];
        int found = 4;   // we already know 2, 3, 5, 7
        const int arraylength = (int)(last / log(last));
        int primes[10000] = {3, 5, 7};
        cout << "Calculating prime numbers until " << last << " in C++ v2.0.2022" << endl;
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
        cout << "Found " << found << " prime numbers. It should be ";
        cout << reference[i] << " primes." << endl;
        cout << "This took " << fixed << time_taken << " seconds." << endl << endl;
        string filename = std::to_string(scope[i]) + ".txt";
        ofstream logfile(filename);
        logfile << "Calculating prime numbers until " << last  << " in C++ v2.0.2022" << endl;
        logfile << "Found " << found << " prime numbers. It should be ";
        logfile << reference[i] << " primes." << endl;
        logfile << "This took " << fixed << time_taken << " seconds." << endl << endl;
        logfile.close();
    }
}

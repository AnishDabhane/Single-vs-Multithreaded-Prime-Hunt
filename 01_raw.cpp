#include <iostream>
#include <chrono>
#include <cmath>
using namespace std;

const int MAX_INT = 10000000; // 10 million
int totalnumber = 0;

void check_prime(int num) {
    if (num < 2) return;
    else if (num == 2 || num == 3) {
        totalnumber++;
        return;
    }
    else {
        for (int i = 3; i <= sqrt(num); i+2) {
            if (num % i == 0) {
                return;
            }
        }
        totalnumber++;
    }
}

int main(){
    auto start = chrono::high_resolution_clock::now();
    for(int i=1;i<MAX_INT;i+=2){
        check_prime(i);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "Checking numbers up to " << MAX_INT << " found " << totalnumber << " primes" << endl;
    cout << "Total time: " << duration << " sec" << endl;
}
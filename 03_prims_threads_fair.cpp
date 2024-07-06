#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>
#include <atomic>
#include <vector>
using namespace std;

const int MAX_INT = 10000000; // 100 million
atomic<int> totalnumber(0);
atomic<int> currnum(1);

void check_prime(int num) {
    if (num < 2) return;
    else if (num == 2 || num == 3) {
        totalnumber.fetch_add(1);
        return;
    }
    else{
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                return;
            }
        }
        totalnumber.fetch_add(1);
    }
}

void do_work(int idx) {
    auto start = chrono::high_resolution_clock::now();
    while(true) {
        int x = currnum.fetch_add(2);
        if (x > MAX_INT) break;
        check_prime(x);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "Thread " << idx <<" completed in " << duration << " sec" << endl;
}

int main() {
    int concurrency = 10;
    int batch_size = MAX_INT / concurrency;
    int nstart = 0;
    int nend = batch_size;
    
    vector<thread> threads;
    
    auto start = chrono::high_resolution_clock::now();
    for (int i = 1; i <= concurrency; i++) {
        threads.push_back(thread(do_work, i));
        nstart = nend;
        nend += batch_size;
    }
    
    for (auto& th : threads) {
        th.join();
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "Checking numbers up to " << MAX_INT << " found " << totalnumber << " primes" << endl;
    cout << "Total time: " << duration << " sec" << endl;
    
    return 0;
}

#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>
#include <atomic>
#include <vector>
using namespace std;

const int MAX_INT = 10000000; // 10 million
atomic<int> totalnumber(0);

void check_prime(int num) {
    if (num < 2) return;
    else if (num == 2 || num == 3) {
        totalnumber++;
        return;
    }
    else{
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                return;
            }
        }
        totalnumber++;
    }
}

void do_batch(int idx, int nstart, int nend) {
    cout<<"Starting thread "<<this_thread::get_id()<<endl;
    auto start = chrono::high_resolution_clock::now();
    for (int i = nstart; i < nend; i++) {
        check_prime(i);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "Thread " << idx << " [" << nstart << " " << nend << "] completed in " << duration << " sec" << endl;
}

int main() {
    cout<<"Starting main thread "<<this_thread::get_id()<<endl;
    int concurrency = 10;
    int batch_size = MAX_INT / concurrency;
    int nstart = 0;
    int nend = batch_size;
    
    vector<thread> threads;
    
    auto start = chrono::high_resolution_clock::now();
    for (int i = 1; i <= concurrency; i++) {
        threads.push_back(thread(do_batch, i , nstart, nend));
        nstart = nend;
        nend += batch_size;
    }
    
    for (auto& th : threads) {
        th.join();
    }
    cout<<"Main thread completed"<<this_thread::get_id()<<endl;
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "Checking numbers up to " << MAX_INT << " found " << totalnumber << " primes" << endl;
    cout << "Total time: " << duration << " sec" << endl;
    
    return 0;
}

#include <iostream>
#include <cmath>
#include <omp.h>
#include <chrono>

static int N = 20221;

using namespace std;
using namespace std::chrono;

double f(double x){
    return (7*x + 16) / (pow(7*x + 8, 2.0/3.0) + 2 * pow(7*x + 8, 1.0/3.0));
}

double single_thread_test(){
    double a = 0, b = -13.0, h = (a-b)/N, sum = 0;
    for(int i = 0; i<N-1; i++){
        sum += f(a+i*h);
//        cout << omp_get_thread_num() << " sum = " <<sum << endl;
    }
    sum *= h;

    cout << "single thread result : " << sum << endl;
}

int main(){

    int thread_num = 3;
    double a = 0, b = -13.0, h = (a-b)/N, sum = 0;

    int section_size = N/thread_num;
    cout << "section_size:" << section_size << endl;

    high_resolution_clock::time_point start = high_resolution_clock::now();
    single_thread_test();
    high_resolution_clock::time_point end = high_resolution_clock::now();
    cout << "single_thread time:" << duration_cast<microseconds>(end-start).count() << endl;

    omp_set_num_threads(thread_num);

    start = high_resolution_clock::now();

    #pragma omp parallel for shared(sum)
    for(int i = 0;
        i<N-1; i++){
        #pragma omp critical
        {
            sum += f(a+i*h);
//            cout << "i+1=" << i << " thread num= " << omp_get_thread_num() << " sum = " <<sum << endl;
        }
    }

    if (N % thread_num != 0){
        for (int i = thread_num*section_size;
             i<N - thread_num*section_size; i++){
             sum += f(a+i*h);
        }
    }
    sum *= h;

    cout << "multi thread result: " << sum << endl;
    end = high_resolution_clock::now();
    cout << "multi_thread time:" << duration_cast<microseconds>(end-start).count() << endl;
}

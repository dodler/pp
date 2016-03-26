#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;

//int thread_positive_count = 0;
//#pragma omp threadprivate(thread_positive_count)

int main()
{
    srand(time(NULL));
    int n = 5, array_size = 20, max_value = 100;

    omp_set_num_threads(n);

    int* a= new int[array_size];

    int positive_count = 0;

    #pragma omp parallel for
    for (int i = 0; i<array_size; i++){
        a[i] = rand()%max_value - max_value/2;
//        cout << "thread#" << omp_get_thread_num() << " value=" << a[i] << endl;
        #pragma omp critical
        {// incrementing in single thread
            if (a[i] >= 0){
                positive_count++;
            }
//            if (omp_get_thread_num() == 0){
//                positive_count += thread_positive_count;
//                thread_positive_count = 0;
//            }
        }
    }

    for (int i = 0;i <array_size; i++){
        cout << a[i] << " ";
    }
    cout << endl;


    cout << "thread#" << omp_get_thread_num() << " total positive values count:" << positive_count  << endl;

    delete a;

    return 0;
}


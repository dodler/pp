#include <iostream>
#include <cmath>
#include <mpi/mpi.h>
#include <time.h>

using namespace std;
using namespace MPI;

static int N = 1000;

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

    Init();

    int numprocs, myid;

    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

//    MPI_Bcast(a, array_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double result = 0, thread_result = 0;
    double a = 0, b = -13.0, h = (a-b)/N;
    int section_size = N / numprocs;

    if (myid != numprocs-1){
        for(int i = myid*section_size; i<(myid+1)*section_size; i++){
            thread_result += f(a+i*h);
        }
    }else{
        for(int i = myid*section_size; i<(myid+1)*section_size -1 ; i++){
            thread_result += f(a+i*h);
        }
    }

    if (myid == 0){
        if (N % numprocs != 0){
            for (int i = numprocs * section_size; i < N-1; i++){
                thread_result += f(a+i*h);
            }
        }
    }

//    cout << "myid=" << myid << " thread_result:" << thread_result << endl;

    MPI_Reduce(&thread_result, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    result *= h;

    if (myid==0){
//        cout << "on thread 0" << endl;
        single_thread_test();
        cout << "multi thread test:" << result<< endl;
    }

    MPI_Finalize();

}

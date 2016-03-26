#include <iostream>
#include <mpi/mpi.h>
#include <cmath>
#include <cstdlib>

using namespace std;
using namespace MPI;

const static int array_size = 300;

const static int MAX_RANDOM_VALUE = 100;

int main(){

    Init();

    int threads_total, thread_id;

    MPI_Comm_size(MPI_COMM_WORLD, &threads_total);
    MPI_Comm_rank(MPI_COMM_WORLD, &thread_id);


    srand(time(NULL) + thread_id);

    int* a = new int[array_size];

    for (int i = 0; i<array_size; i++){
        a[i] = rand()%MAX_RANDOM_VALUE * (thread_id+1) - MAX_RANDOM_VALUE/2;

//        cout << "thread_id=" << thread_id << ", a[" << i << "]=" << a[i] << endl;
    }

    int max[2], gen_max[2];
    max[0] = a[0];
    max[1] = 0;

    for(int i = 1; i<array_size; i++){
        if (a[i] > max[0]){
            max[0] = a[i];
            max[1] = i;
//            cout << "setting max " << i;
//            cout << " I am thread#" << thread_id << " maximum is:" << max[0] << ", index:" << max[1] << endl;
        }
    }
    cout << "I am thread#" << thread_id << "maximum is:" << max[0] << ", index:" << max[1] << endl;

//    cout << "starting barrier" << endl;

    MPI_Barrier(MPI_COMM_WORLD);

//    cout << "thread_id=" << thread_id << endl;

    if (thread_id != 0){
        MPI_Send(&max, 2, MPI_INT,
                 0, 0, MPI_COMM_WORLD);
//        cout << "send success" << endl;
    }else{

        for(int i = 1; i<threads_total; i++){
            MPI_Recv(&gen_max, 2, MPI_INT,
                     i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (gen_max[0] > max[0]){
                max[0] = gen_max[0];
                max[1] = gen_max[1];
            }
        }

        for(int i = 1; i<threads_total; i++){
            MPI_Send(&max, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
//        cout << "recieved success" << endl;
    }

    if (thread_id != 0){
        MPI_Recv(&max, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    cout << "I am thread#" << thread_id << ", maximum is:" << max[0] << ", index:" << max[1] << endl;


    MPI_Finalize();

}

#include <iostream>
#include <cstdlib>
#include <mpi/mpi.h>

using namespace std;
using namespace MPI;

int main(){
    Init();

    srand(time(NULL));

    int numprocs, myid;

    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    int array_size = 10, max_value = 100;

    double* a = new double[array_size];

    if (myid == 0){
        int local_test = 0;
        for(int i = 0; i<array_size; i++){
            a[i] = rand()%max_value - max_value/2;
            if (a[i] > 0){
                local_test++;
            }
        }
        cout << "local_test = " << local_test << endl;
    }

    MPI_Bcast(a, array_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int positive_count = 0,world_positive_counter = 0;

    int section_size = array_size / numprocs;

    for(int i = myid*section_size; i<(myid+1)*section_size; i++){
//        cout << "myid= " << myid << " a[i]="<< a[i] << endl;
        if (a[i] > 0){
            positive_count++;
        }
    }

    if (myid == 0){
        if (array_size % numprocs != 0){
            for (int i = numprocs * section_size; i < array_size; i++){
                if (a[i] > 0){
                    positive_count ++ ;
                }
            }
        }
    }

    cout << "myid=" << myid << " count:" << positive_count << endl;

//    MPI_Gather(&positive_count, numprocs-1, MPI_INT,
//               &positive_count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Reduce(&positive_count, &world_positive_counter, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myid==0){
        cout << "on thread 0" << endl;
        cout << "total count:" << world_positive_counter<< endl;
    }

    MPI_Finalize();
}

#include <iostream>
#include <mpi/mpi.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

static const int N = 100;
static const int M = 150;

static const int MAX_NUMBER = 150;

using namespace MPI;
using namespace std;

int main(){
    Init();

    int thread_count, thread_id;

    MPI_Comm_size(MPI_COMM_WORLD, &thread_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &thread_id);

    cout << "started, thread_count=" << thread_count << ", thread_Id = " << thread_id << endl;


    int** a = new int*[N];
    if (thread_id == 0){
        srand(time(NULL));
        for(int i = 0; i<N; i++){
            a[i] = new int[M];
            for(int j = 0; j<M; j++){
                a[i][j] = rand()%2  * MAX_NUMBER - MAX_NUMBER/2;
            }
        }
    }

    int section_size = M/thread_count;
    for(int i = 0; i<M/section_size; i++){
        MPI_Bcast(a, N*M, MPI_INT, 0, MPI_COMM_WORLD);
    }

    stringstream file_name;
    file_name << "output_" << to_string(thread_id) << ".txt";
    ofstream out;
    out.open(file_name.str());


    out.flush();
    out.close();

    MPI_Finalize();

}

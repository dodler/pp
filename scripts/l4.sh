
mpicxx ../openmp1/mpi_cpp_4.cpp -o ../build/mpi_cpp_4 -std=c++11

mpiexec -np 4 ../build/mpi_cpp_4

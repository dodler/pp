
mpicxx ../openmp1/mpi_cpp_3.cpp -o ../build/mpi_cpp_3

mpiexec -np 4 ../build/mpi_cpp_3

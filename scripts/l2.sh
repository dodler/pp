
mpicxx ../openmp1/mpi_cpp_2.cpp -o ../build/mpi_cpp_2

mpiexec -np 2 ../build/mpi_cpp_2

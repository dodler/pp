TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    #mpi_l1.c \
    mpi_cpp.cpp \
    openmp_cpp_2.cpp \
    #main.cpp
#    mpi_cpp_2.cpp
    mpi_cpp_3.cpp \
    mpi_cpp_4.cpp

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

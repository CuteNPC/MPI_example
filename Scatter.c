#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
int main(int argc, char **argv)
{
    int rank, size;
    int send_data[4] = {6, 7, 8, 9};
    int recv_data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 4)
    {
        printf("This program needs at least 4 processes to run.\n");
        MPI_Finalize();
        return 1;
    }

    // 使用MPI_Scatter将数据从主进程分散到其他进程
    MPI_Scatter(send_data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received data: %d\n", rank, recv_data);

    MPI_Finalize();
    return 0;
}

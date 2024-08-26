#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;
    int send_data, recv_data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2)
    {
        printf("This program needs at least 2 processes to run.\n");
        MPI_Finalize();
        return 1;
    }

    send_data = rank + 1;

    // 使用MPI_Sendrecv同时执行发送和接收操作
    MPI_Sendrecv(&send_data, 1, MPI_INT, (rank + 1) % size, 0,
                 &recv_data, 1, MPI_INT, (rank + size - 1) % size, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process %d sent data: %d, received data: %d\n", rank, send_data, recv_data);

    MPI_Finalize();
    return 0;
}

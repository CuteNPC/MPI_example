#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;
    int data_send = 42;
    int data_recv;

    MPI_Init(&argc, &argv);z
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2)
    {
        printf("This program needs at least 2 processes to run.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0)
    {
        // 主进程发送数据给进程 1
        MPI_Send(&data_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process %d sent data: %d\n", rank, data_send);
    }
    else if (rank == 1)
    {
        // 进程 1 接收从进程 0 发来的数据
        MPI_Recv(&data_recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received data: %d\n", rank, data_recv);
    }

    MPI_Finalize();
    return 0;
}

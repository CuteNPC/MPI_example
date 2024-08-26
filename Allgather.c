#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;
    int send_data;
    int recv_data[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    send_data = rank + 1;

    // 使用MPI_Allgather进行全局数据收集
    MPI_Allgather(&send_data, 1, MPI_INT, recv_data, 1, MPI_INT, MPI_COMM_WORLD);

    printf("Process %d received data: ", rank);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", recv_data[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;
    int send_data[4] = {1, 2, 3, 4};
    int recv_data[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2)
    {
        printf("This program needs at least 2 processes to run.\n");
        MPI_Finalize();
        return 1;
    }

    // 使用MPI_Alltoall进行全局数据交换
    MPI_Alltoall(send_data, 1, MPI_INT, recv_data, 1, MPI_INT, MPI_COMM_WORLD);

    printf("Process %d received data: ", rank);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", recv_data[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}

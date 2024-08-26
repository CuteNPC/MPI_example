#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
int main(int argc, char **argv)
{
    int rank, size;
    int recv_data[4] = {0, 0, 0, 0};
    int send_data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 4)
    {
        printf("This program needs at least 4 processes to run.\n");
        MPI_Finalize();
        return 1;
    }

    // 使用MPI_Gather将数据从所有进程收集到主进程
    send_data = rank + 10;
    MPI_Gather(&send_data, 1, MPI_INT, recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Gathered data in root process: ");
        for (int i = 0; i < size; i++)
        {
            printf("%d ", recv_data[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

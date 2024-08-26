#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;
    int data = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 只在主进程（排名为0）设置数据
    if (rank == 0)
    {
        data = 42;
    }

    // 使用MPI_Bcast在所有进程中广播数据
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d has data: %d\n", rank, data);

    MPI_Finalize();
    return 0;
}

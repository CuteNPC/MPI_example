#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;
    int local_data = 0;
    int global_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_data = rank + 1; // 每个进程的数据是其排名加1

    // 使用MPI_Reduce将各进程的数据求和到根进程
    MPI_Reduce(&local_data, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Global sum: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
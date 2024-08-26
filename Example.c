#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;
    char message[100];

    MPI_Init(&argc, &argv);               // 初始化MPI环境
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // 获取当前进程的排名
    MPI_Comm_size(MPI_COMM_WORLD, &size); // 获取进程总数

    if (size < 2)
    {
        printf("This program needs at least 2 processes to run.\n");
        MPI_Finalize(); // 终止MPI环境
        return 1;
    }

    if (rank == 0)
    {
        // 主进程发送消息
        snprintf(message, 100, "Hello from process %d!", rank);
        MPI_Send(message, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1)
    {
        // 接收进程接收消息
        MPI_Recv(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received message: %s\n", message);
    }

    MPI_Finalize(); // 终止MPI环境

    return 0;
}

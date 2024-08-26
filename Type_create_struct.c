#include <stdio.h>
#include <mpi.h>

typedef struct
{
    int id;
    double value;
} MyStruct;

int main(int argc, char **argv)
{
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int blocklengths[2] = {1, 1};
    MPI_Aint displacements[2];
    MPI_Datatype types[2] = {MPI_INT, MPI_DOUBLE};
    MPI_Datatype mystruct_type;

    // 计算结构体中成员的偏移量
    MPI_Get_address(&(((MyStruct *)0)->id), &displacements[0]);
    MPI_Get_address(&(((MyStruct *)0)->value), &displacements[1]);

    // 计算相对于displacements[0]的偏移量
    displacements[1] -= displacements[0];
    displacements[0] = 0;

    // 创建自定义数据类型
    MPI_Type_create_struct(2, blocklengths, displacements, types, &mystruct_type);
    MPI_Type_commit(&mystruct_type);

    MyStruct send_data = {rank, 3.14};
    MyStruct recv_data;

    MPI_Bcast(&send_data, 1, mystruct_type, 0, MPI_COMM_WORLD);

    printf("Process %d received id: %d, value: %f\n", rank, recv_data.id, recv_data.value);

    MPI_Type_free(&mystruct_type);
    MPI_Finalize();
    return 0;
}

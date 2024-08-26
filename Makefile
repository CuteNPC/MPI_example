CC = mpicc
CFLAGS = -Wall -g

all: Allgather Barrier Example Scatter Sendrecv Alltoall Bcast Gather Reduce Send_Recv Type_create_struct

%: %.c
	$(CC) -o $@ $^

clean:
	rm Allgather Barrier Example Scatter Sendrecv Alltoall Bcast Gather Reduce Send_Recv Type_create_struct
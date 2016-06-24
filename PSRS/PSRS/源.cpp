#include <iostream>
#include "mpi.h"
#include <algorithm>

#define MAX_LENGTH 500

using namespace std;

int cmp(const void *a, const void *b) {
	if ((double*)a <= (double*)b)
		return 1;
	else
		return -1;
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		cout << "Enter numbers you want to sort, Ctrl + Z to finish.\n";

		double *A = new double[MAX_LENGTH];
		int N = 0;
		double temp;
		while (cin >> temp)
			A[N++] = temp;

		int partition = N / (size - 1);

		for (int i = 1; i < size; i++) {
			if (i != size - 1) {
				MPI_Send(A + (i - 1) * partition, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
				MPI_Send(&partition, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
			else {
				int count = N - partition * (N - 1);
				MPI_Send(A , 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
				MPI_Send(&count, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			}
		}
	}

	else {
		double *B;
		int N;
		MPI_Recv(B, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		qsort(B, N, sizeof(double), cmp);
	}


}


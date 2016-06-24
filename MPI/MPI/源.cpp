#include "mpi.h"
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	double a, b, source;
	int n;

	double local_a, local_b, local_n, h, local_int = 0, total_int;

	if (rank == 0) {
		cout << "This program is designed to calculate the integral of x^2 in the inteval [a, b]\n  Enter a, b and n: ";
		cin >> a >> b >> n;
		for (int dest = 1; dest < size; dest++) {
			MPI_Send(&a, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
			MPI_Send(&b, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
			MPI_Send(&n, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
		}
	}
	else {
		MPI_Recv(&a, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
		MPI_Recv(&b, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
		h = (b - a) / n;
		local_n = n / size;
		local_a = a + rank * local_n * h;
		local_b = local_a + local_n * h;
		local_int = (local_a * local_a+ local_b * local_b) * (local_b - local_a) / 2;
	}

	if (rank != 0) {
		MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	else {
		total_int = local_int;
		for (source = 1; source < size; source++) {
			MPI_Recv(&local_int, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			total_int += local_int;
		}
	}

	if (rank == 0) {
		printf("With n = %d trapezoids, our estimate\n", n);
		printf("of the integral from %f to %f = %.15e\n",
			a, b, total_int);
	}
	MPI_Finalize();
	return 0;
}
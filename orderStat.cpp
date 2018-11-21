/*
Part 1 of CSC 382 Project:

Authors: Nora Elattar, Sean Connor, and Matthew Henschke
*/
#include <iostream>
#include <algorithm>
#include <ctime>
#include <chrono>

void permutation(int *, int, int);
int medianPart(int *, int, int, int);
int partition(int*, int, int, int);
int findMedian(int*, int);
void swap(int*, int*);


// swaps two values
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// returns the median of array arr
int findMedian(int arr[], int n) {
	std::sort(arr, arr + n);  // Sort the array
	return arr[n / 2];   // Return middle element
}

// randomly generate array
void permutation(int A[], int n, int N) {

	for (int i = 0; i < n; i++) { //random numbers from N
		A[i] = rand() % N + 1;
	}
}

// partition the array arr around x
int partition(int arr[], int l, int r, int x) {
	// Search for x in arr[l..r] and move it to end
	int i;
	for (i = l; i < r; i++)
		if (arr[i] == x)
			break;

	swap(&arr[i], &arr[r]);
	// Standard partition algorithm
	i = l;
	for (int j = l; j <= r - 1; j++) {
		if (arr[j] <= x) {
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[r]);
	return i;
}



int medianPart(int A[], int l, int r, int k) {
	// If k is smaller than number of elements in array
	if (k > 0 && k <= r - l + 1){
		int n = r - l + 1; // Number of elements in arr[l..r]
						   // Divide arr[] in groups of size 5, calculate median
						   // of every group and store it in median[] array.
		int i;
		int median[n / 5];
		for (i = 0; i < n / 5; i++)
			median[i] = findMedian(A + l + i * 5, 5);

		//For last group with less than 5 elements
		if (i * 5 < n) {
			median[i] = findMedian(A + l + i * 5, n % 5);
			i++;
		}

		int medOfMed = medianPart(median, 0, i - 1, i / 2);
		// Partition the array around a random element and
		// get position of pivot element in sorted array
		int pos = partition(A, l, r, medOfMed);
		// If position is same as k
		if (pos - l == k - 1)
			return A[pos];
		if (pos - l > k - 1)  // If position is more, recur for left
			return medianPart(A, l, pos - 1, k);
		// Else recur for right subarray
		return medianPart(A, pos + 1, r, k - pos + l - 1);
	}
	// If k is more than number of elements in array
	return INT_MAX;
}


int main() {
	// population and sample size arrays
	int N[3] = { 5000, 8000, 10000 }; // population size
	int n[6] = { 100, 300, 500, 1000, 2000, 4000 }; // sample size

	srand(time(NULL));
	int k; // kth smallest int

		   // traverse through all sample array sizes
	for (int i = 0; i < 6; i++) {
		// header
		std::cout << n[i] << ":" << std::endl;
		k = rand() % n[i] + 1;
		int *A = new int[n[i]];

		// Traverse through all population sizes
		for (int j = 0; j < 3; j++) {
			std::cout << "Population size: " << N[j] << " ";
			// randomly generate array
			permutation(A, n[i], N[j]);

			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			medianPart(A, 0, n[i], k);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
			// get running time of medianPart in milliseconds
			std::cout << "CPU time is " << time_span.count() << " milliseconds" << std::endl;
		}
		std::cout << std::endl;
	}

	return 0;
}


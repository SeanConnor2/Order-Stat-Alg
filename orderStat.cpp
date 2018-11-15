//  main.cpp
//  CSC382 Project 1
//  Created by CTP CTP on 11/15/18.
//  Copyright © 2018 CTP CTP. All rights reserved.

#include <iostream>
#include<algorithm>
#include<ctime>

using namespace std;

void permutation(int*, int, int);
int medianPart(int*, int, int, int);
int partition(int*, int, int, int);
int findMedian(int*, int);
void swap(int*, int*);

int main() {

	// insert code here...

	int N[3] = { 5000, 8000, 10000 };
	int n[6] = { 100, 300, 500, 1000, 2000, 4000 };

	srand(time(NULL));
	int k; //kth smallest int

	for (int i = 0; i < 6; i++) {
		k = rand() % n[i] + 1;
		int *A = new int[n[i]];
		for (int j = 0; j < 3; j++) {
			//N traversal
			permutation(A, n[i], N[j]);
			cout << medianPart(A, 0, n[i], k);
			cout << endl;
			//start time
			// ord stat call
			//end time
		}
	}
	return 0;
}

void permutation(int* A, int n, int N){

	for (int i = 0; i < n; i++) { //random numbers from N
		A[i] = rand() % N + 1;
	}
}


int medianPart(int *A, int l, int r, int k){
	// If k is smaller than number of elements in array
	if (k > 0 && k <= r - l + 1)
	{
		int n = r - l + 1; // Number of elements in arr[l..r]
		// Divide arr[] in groups of size 5, calculate median
		// of every group and store it in median[] array.

		int i, median[n / 5];
		for (i = 0; i < n / 5; i++)
			median[i] = findMedian(A + l + i * 5, 5);

		//For last group with less than 5 elements
		if (i * 5 < n){
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

int findMedian(int arr[], int n){
	sort(arr, arr + n);  // Sort the array
	return arr[n / 2];   // Return middle element
}
// It searches for x in arr[l..r], and partitions the array
// around x.
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int arr[], int l, int r, int x){
	// Search for x in arr[l..r] and move it to end
	int i;
	for (i = l; i < r; i++)
		if (arr[i] == x)
			break;

	swap(&arr[i], &arr[r]);
	// Standard partition algorithm
	i = l;
	for (int j = l; j <= r - 1; j++){
		if (arr[j] <= x){
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[r]);
	return i;
}



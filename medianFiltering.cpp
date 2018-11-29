/*
Part 2 of CSC 382 Project:
Apply the algorithm implemented in Part 1 to the median filtering 
of an image
Authors: Nora Elattar, Sean Connor, and Matthew Henschke
*/
#include<iostream>
#include "imageio.h"


int main(){
	//int * rows, * cols; // pointer arrays for rows and columns
	//int 
	int dim; //number of rows and colums
	unsigned char *** image = NULL;

	std::cout << "Please enter the square dimension for your image" << std::endl;
	std ::cin >> dim;
	//int rows = dim;
	//int col = dim;
	int * rows = new int[dim];
	int * cols = new int[dim];

	std::cout << read_pgm_image("mountain.png", image, rows, cols);
    return 0;
}
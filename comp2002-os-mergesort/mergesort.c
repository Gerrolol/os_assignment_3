/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
	int size = (leftend - leftstart  + 1) + (rightend - rightstart + 1);
	B = (int *) malloc(size * sizeof(int));
	int ptr = 0;
	
	int l = leftstart;
	int r = rightstart;

	while(l <= leftend && r <= rightend){
		if(A[l] < A[r]){
			B[ptr] = A[l];
			l++;
		}else{
			B[ptr] = A[r];
			r++;
		}
		ptr++;
	}
	//copy any reamining elements
	while(l <=  leftend){
		B[ptr] = A[l];
		ptr++;
		l++;
	}	
	while(r <= rightend){
		B[ptr] = A[r];
		ptr++;
		r++;
	}

	//merge back into A
	for(int i=0; i<size; i++){
		A[leftstart + i] = B[i];
	}
	free(B);
}


/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
	if(left >=right){
		return;
	}
	int mid = left + (right-left)/2;
	my_mergesort(left, mid);
	my_mergesort(mid+1, right);
	merge(left, mid, mid+1, right);
}


/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

/*
[2,3] [2,3,5]
0  1   2   4
*/
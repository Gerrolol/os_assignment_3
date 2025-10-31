## Project 3 Concurrency

- Authors: Leo Li, Angelo Li
- Group name: The Lis

## Overview

This program is aims to make use of concurrency and multithreaded programming to implement the mergesort algorithm.
The program should recursively create new threads to run mergesort on multiple threads, and then call single threaded
mergesort once it reaches the required level.

## Manifest

Helpful Files:
Makefile - specifies commands for easy compilation of program.
.gitignore - prevents generated files from being added to github

Required:
mergesort.h- header file for mergesort, defines class variables and the functions:

- merge()
- my_mergesort()
- parallel_mergesort()
- buildArgs()

mergesort.c - implements the functions defined in mergesort.h
test-mergesort.c - code to test the speed and correctness of the mergesort function

## Building the project

ensure you in a single directory with all the required files listed above.
run 'make' in the terminal
call ./test-mergesort <input size> <cutoff level> <seed>
where input size is the amount of numbers to be sorted
cutoff level is the level at which no more threads should be created
seed is for the random generation of number, using the same seed ensures the same values

## Features and usage

There are two major types of functions in mergesort.c - program functions and helper functions.
The helper functions are merge() and buildArgs():

merge() helps to combine two individually sorted arrays, it will simply iterate through both arrays and continuously
insert the smaller value into a new array and finally replacing the original array once all values are considered.

The program functions are the my_mergesort function and the parallel_mergesort function:

The my_mergesort function is a recursive function which follows a divide and conquer approach. It takes two indices, left and right,
representing the portion of the array tobe  soorted. If the range has one more elements the function returns since that part is
already soorted. Otherwise, it calculates the midpoint and recursively calls itself too sort the left half and the right half. Once
both halves are sorted the function calls merge() into one sorted section. This continues until the entire array is fully sorted

The parallel_mergesort function will recursively call itself in a new thread using pthread_create, it divides the array to sort
into two across the middle, then creates two new threads running mergesort, each working on one of the two halves of the array.
After this, it will call pthread_join, which waits for the threads to be done sorting their halves of the array, and then call
merge() to combine those two sorted subarrays, before returning to the parent. It will continue this until it either hits the
cutoff level, or the array length becomes 1, at which point there is nothing left to sort. It will then call the my_mergesort
function to finish sorting the rest of that array.

## Testing

For testing, there were a few different things we did to ensure our code was correct. For starters, we used the provided file
test-mergesort.c to as a baseline before submission. This allowed us to find initial errors in our code such as indexing errors,
segmentation faults and other memory allocation errors. After this, we ran the code on a few test examples and examined the output
to check whether using a multithreaded approach was able to reduce the time taken to sort the list, which ensures that our
multithreading was also implemented correctly. Finally, we submitted our code onto gradescope, and it was able to successfully pass
all the test cases, which further ensures that we had done all of the coding correctly. Aside from this, I also had AI read through
the code to identify any potential bugs that I have missed, and it was unable to identify any.

## Known Bugs

One of the bugs that we fixed was to do with memory handling in our merge sort implementation. Initially, 
the merge function used a global temporary array B to store immediate results during merging, which caused 
issues when freeing memory, specifically a double free error that led to a memory leak. This happened because 
the global array was being reused and freed multiple times across recursive calls. To fix this, we changed the 
implementation so that the merge function createss its own temporary array locally within each call. This ensures
that memoery is allocated and freed safely within the function scope, preventing double frees. 

## Reflection and Self Assessment

During the development of the parallel merge sort, one of the biggest challenges I faced was thread synchronization
challenges. Some threads finish before otheres causing partial merges or segmentation faults. I learned more ahout
using pthread-create and pthread_join correctly through reading the OS textbook to ensure that the threads complete
before merging. I also refreshed my memory on how a basic mergesort algorihtm works byimplementing it in leetcode.
Another challenge was understanding when to switch from parallel to sequential sorting, which required 
expermenting with different cutoff levels for perofmrance. Through debugging segmentationn faults, I gained a much clearer
understanding of how recursion, memory, and threading interact. Once everytrhing worked out, it was rewarding seeing how 
parallelism could significantly speed up sorting large arrays. Reflecting oon the development and testing process,
the testing process was gradual as we ran it on small arrays to verify correctness before moving onto larger inputs, which
helped isolate bugs and also check time to complete in order to confirm our parral merges were working.

## Sources Used

Used AI to understand what to return for void* return types.
Used AI to learn how to implicit cast a void* type to a argument type.
Used AI for testing the code
watched youtube video to remind myself how mergesort works:
https://www.youtube.com/watch?v=3j0SWDX4AtU&t=101s

used ageeksforgeeks to remind myself how to use malloc again:
https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
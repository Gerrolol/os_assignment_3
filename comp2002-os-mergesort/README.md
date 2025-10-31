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

The my_mergesort function...

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

List known bugs that you weren't able to fix (or ran out of time to fix).

## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your own?
What kinds of errors did you get? How did you fix them?

What parts of the project did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this project? How well
did the development and testing process go for you?

## Sources Used

Used AI to understand what to return for void* return types.
Used AI to learn how to implicit cast a void* type to a argument type.
Used AI for testing the code

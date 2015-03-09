# massCorrelation
An exercise in writing an efficient correlation calculator

## Overview

This is primarly an exercise in implementing a correlation calculation,

The primary implementation is already quite fast but I wanted to know how fast could I get,
In chronological order :
- Baseline algo came from the R project with some optimisation for repated paring of vectors.
- Matrix Algorithm was describe in a stackoverflow post (http://stackoverflow.com/a/18965892/105104)
- CUDA Implementation of both algorithm
- Multithreading implementation with pthread


## Measured Timing

Time have been measured on an Intel E5606 ( http://ark.intel.com/products/52583/Intel-Xeon-Processor-E5606-8M-Cache-2_13-GHz-4_80-GTs-Intel-QPI )
CUDA code is run on Tesla C2075

input : 601 x 45101 matrix 

Baseline Implementation : 977.89
CUDA : 98.27
Matrix Implementation : 1008.80
Matrix CUDA : 142.23
Multi-threaded : 305.19
Estimated I/O operation time : 56.64

for comparison on Intel X5690

Baseline Implementation : 640.27
Matrix Implementation : 639.95
Multi-threaded : 82.10
Estimated I/O operation time : 9.80

## Notes

The CUDA implementation have been quite straight-forward to implement and provided benefits out of the box, Attempt to cleverly optimize the CUDA kernel by using shared memory were unsuccessful ( no performance gained ), and trade-offs were unacceptable ( reducing the number of thread to accomodate the size of the shared memory ).
While the multi-thread code required some implementation for the threadpool, and might be optimized further by using more specialized queues (which could reduce the time used in allocation ).

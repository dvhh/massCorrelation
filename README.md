# massCorrelation
An exercise in writing an efficient correlation calculator

## Overview

This is primarly an exercise in implementing a correlation calculation,

The primary implementation is already quite fast but I wanted to know how fast could I get,
In chronological order :
- Baseline algo came from the R project with some optimisation for repated paring of vectors.
- Matrix Algorithm was describe in a [stackoverflow post][4] 
- CUDA Implementation of both algorithm
- Multithreading implementation with pthread


## Measured Timing

Time have been measured on an [Intel E5606][1]
CUDA code is run on one [Tesla C2075][2] 

input : 601 x 45101 matrix 

- Baseline Implementation : 977.89
- CUDA : 98.27
- Matrix Implementation : 1008.80
- Matrix CUDA : 142.23
- Multi-threaded : 305.19
- openMP : 475.90 (to be checked later when the node is less loaded )
- openMP Nested : 349.13
- No calculation : 56.64

for comparison on an Intel [X5690][3]

- Baseline Implementation : 640.27
- Matrix Implementation : 639.95
- Multi-threaded : 82.10
- openMP : 130.34
- openMP Nested : 115.11
- No calculation : 9.80

input : 100 x 10000

Intel [E5606][1] 
- Baseline : 11.40 (9.08)
- CUDA : Unavailable at this time
- Matrix : 11.18 (8.80)
- Matrix CUDA : Unavailable at this time
- Multi-threaded : 7.39 (5.22)
- OpenMP : 6.26 (3.99)
- OpenMP Nested : 6.04  (3.71)
- No calculation : 2.63 (0.33)

Intel [X5690][3]
- Baseline : 5.67 (5.45)
- CUDA : 3.27 (1.12)
- Matrix : 5.53 (5.23)
- Matrix CUDA : 3.21 (1.13)
- Multi-threaded : 0.94 (0.72)
- openMP : 1.25 (1.03)
- OpenMP Nested : 2.97 (2.74)
- No calculation : 0.43 (0.22)

Timing on [Tegra2 T20][5]
- Baseline : 124.26 (78.09)
- Matrix : 119.02 (76.48)
- Thread : 75.11 (41.43)
- OpenMP : 95.44 (61.21)
- OpenMP nested : 93.57 (56.98)
- No calculation :47.44 (2.44)

## Notes

The CUDA implementation have been quite straight-forward to implement and provided benefits out of the box, Attempt to cleverly optimize the CUDA kernel by using shared memory were unsuccessful ( no performance gained ), and trade-offs were unacceptable ( reducing the number of thread to accomodate the size of the shared memory ).
While the multi-thread code required some implementation for the threadpool, and might be optimized further by using more specialized queues (which could reduce the time used in allocation ).

[1][http://ark.intel.com/products/52583/Intel-Xeon-Processor-E5606-8M-Cache-2_13-GHz-4_80-GTs-Intel-QPI]
[2][http://www.nvidia.co.jp/docs/IO/43395/BD-05880-001_v02.pdf]
[3][http://ark.intel.com/products/52576/Intel-Xeon-Processor-X5690-12M-Cache-3_46-GHz-6_40-GTs-Intel-QPI]
[4][http://stackoverflow.com/a/18965892/105104]
[5][http://www.nvidia.com/object/tegra-superchip.html]

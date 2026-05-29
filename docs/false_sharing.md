# 📊 Syncronizations and False Sharing

## 1. Tests Enviromnent
To evaluate the RAM memory impact using Parallel Algorithms, we implemented a module of RGB Histograms, ranking from 0 to 255. Performance tests was executed with the following components:
* **Operating System:** Kali Linux
* **Base Hardware:** Laptop Lenovo Legion 5 15IAH7H
* **CPU Architecture:** Intel Core i5-12500H (Hybrid desing: P-Cores & E-Cores)
* **Profiling Tool:** `perf` (Linux Performance Counters)

## 2. Implementation and Results
In the RGB Histograms module, was implemented two versions of the algorithm for paralleling colors frecuencies from processed 8K image, comparing execution times:
* **Version A (Mutual Exclusion - `#pragma omp atomic`):** Was declared three global arrays shared where all threads added up their results, protecting the critic section using `atomic`. Execution time was: **~2.49779 seconds**.
* **Version B (Local Variables `reduction`):** was used `reduction(+:arrays)`, allowing to OpenMP generate private copies of the arrays saved in local memory of each thread while loop is active, unifying them at the end. Execution time was: **~0.00763113 seconds**.

## 3. Telemetry Analysis
Using system tools was possible to demostrate why the bad performance of Version A is not caused only for the logical blocking of mutual exclusion. Was used CPU performance counters from Linux tool, typing the command `perf stat -e L1-dcache-loads,L1-dcache-load-misses,cache-misses`.

The following metrics results fromn P-Cores was obtained:
* **Execution with Reduction:** 6.5 millions of L1 cache misses (`L1-dcache-load-misses`).
* **Execution with Atomic:** 65.6 millions of L1 cache misses.

## 4. Conclusion
Last data confirm than there is the *False Sharing* problem using Atomic version. 
The main memory transfers to L1 Cache memory. When two different threads attempt to update colors simultaneously, the CPU driver invalidate the entire cache line because it needs to keep coherence with the memory. This causes more cache failure and destroying the parallelism performance. This process is called *Cache Line Bouncing*.
So, using Local Variables (`reduction`) is the best solution of this problem, mitigating the failure rate, and reaching efficiency.
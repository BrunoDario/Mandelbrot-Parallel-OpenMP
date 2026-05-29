## Vectorizing using SIMD
It was implemented `#pragma omp simd collapse(2)` on the intern loops of convolution filter. After compilating using `-fopt-info-vec-optimized`diagnostic flag, GCC confirms the successful vectorization of aritmetic operations usign 16 bytes packets of SIMD registers.


![alt text](images/vectorizing.png)
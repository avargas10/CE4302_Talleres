__kernel void saxpy(__global const int *A, __global const int *B, __global int *X, __global int *Y) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
 
    // Do the operation
    Y[i] = X[i]*(*A) + *B;
}
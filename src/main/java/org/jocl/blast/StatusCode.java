/*
 * JOCLBlast - Java bindings for CLBlast
 *
 * Copyright (c) 2016 Marco Hutter - http://www.jocl.org
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
package org.jocl.blast;

/**
 * Status codes. These codes can be returned by functions declared in the
 * {@link CLBlast} class. The error codes match either the standard 
 * OpenCL error codes or the clBLAS error codes.
 */
public class StatusCode
{
    /**
     * CL_SUCCESS
     */
    public static final int kSuccess = 0;
    /**
     * CL_MEM_OBJECT_ALLOCATION_FAILURE
     */
    public static final int kTempBufferAllocFailure = -4;
    /**
     * CL_BUILD_PROGRAM_FAILURE: OpenCL compilation error
     */
    public static final int kBuildProgramFailure = -11;
    /**
     * CL_INVALID_BINARY
     */
    public static final int kInvalidBinary = -42;
    /**
     * CL_INVALID_KERNEL
     */
    public static final int kInvalidKernel = -48;
    /**
     * CL_INVALID_WORK_DIMENSION: Too many thread dimensions
     */
    public static final int kInvalidLocalNumDimensions = -53;
    /**
     * CL_INVALID_WORK_GROUP_SIZE: Too many threads in total
     */
    public static final int kInvalidLocalThreadsTotal = -54;
    /**
     * CL_INVALID_WORK_ITEM_SIZE: ... or for a specific dimension
     */
    public static final int kInvalidLocalThreadsDim = -55;
    /**
     * CL_INVALID_BUFFER_SIZE
     */
    public static final int kInvalidTempBufferSize = -61;
    
    // Status codes in common with the clBLAS library
    /**
     * Routine or functionality not implemented yet
     */
    public static final int kNotImplemented = -1024; 
    /**
     * Matrix A is not a valid OpenCL buffer
     */
    public static final int kInvalidMatrixA = -1022;
    /**
     * Matrix B is not a valid OpenCL buffer
     */
    public static final int kInvalidMatrixB = -1021;
    /**
     * Matrix C is not a valid OpenCL buffer
     */
    public static final int kInvalidMatrixC = -1020;
    /**
     * Vector X is not a valid OpenCL buffer
     */
    public static final int kInvalidVectorX = -1019;
    /**
     * Vector Y is not a valid OpenCL buffer
     */
    public static final int kInvalidVectorY = -1018;
    /**
     * Dimensions M, N, and K have to be larger than zero
     */
    public static final int kInvalidDimension = -1017;
    /**
     * LD of A is smaller than the matrix's first dimension
     */
    public static final int kInvalidLeadDimA = -1016;
    /**
     * LD of B is smaller than the matrix's first dimension
     */
    public static final int kInvalidLeadDimB = -1015;
    /**
     * LD of C is smaller than the matrix's first dimension
     */
    public static final int kInvalidLeadDimC = -1014;
    /**
     * Increment of vector X cannot be zero
     */
    public static final int kInvalidIncrementX = -1013;
    /**
     * Increment of vector Y cannot be zero
     */
    public static final int kInvalidIncrementY = -1012;
    /**
     * Matrix A's OpenCL buffer is too small
     */
    public static final int kInsufficientMemoryA = -1011;
    /**
     * Matrix B's OpenCL buffer is too small
     */
    public static final int kInsufficientMemoryB = -1010;
    /**
     * Matrix C's OpenCL buffer is too small
     */
    public static final int kInsufficientMemoryC = -1009;
    /**
     * Vector X's OpenCL buffer is too small
     */
    public static final int kInsufficientMemoryX = -1008;
    /**
     * Vector Y's OpenCL buffer is too small
     */
    public static final int kInsufficientMemoryY = -1007;
    
    // Custom additional status codes for CLBlast
    /**
     * Problem occurred when enqueuing the kernel
     */
    public static final int kKernelLaunchError = -2048;
    /**
     * Problem occurred while running the kernel
     */
    public static final int kKernelRunError = -2047;
    /**
     * Not enough local memory available on this device
     */
    public static final int kInvalidLocalMemUsage = -2046;
    /**
     * Half precision (16-bits) not supported by the device
     */
    public static final int kNoHalfPrecision = -2045;
    /**
     * Double precision (64-bits) not supported by the device
     */
    public static final int kNoDoublePrecision = -2044;
    /**
     * Vector dot is not a valid OpenCL buffer
     */
    public static final int kInvalidVectorDot = -2043;
    /**
     * Vector dot's OpenCL buffer is too small
     */
    public static final int kInsufficientMemoryDot = -2042;

    /**
     * Private constructor to prevent instantiation
     */
    private StatusCode()
    {
        // Private constructor to prevent instantiation
    }

    /**
     * Returns a string representation of the given constant
     *
     * @return A string representation of the given constant
     */
    public static String stringFor(int n)
    {
        switch (n)
        {
            case kSuccess: return "kSuccess";
            case kTempBufferAllocFailure: return "kTempBufferAllocFailure";
            case kBuildProgramFailure: return "kBuildProgramFailure";
            case kInvalidBinary: return "kInvalidBinary";
            case kInvalidKernel: return "kInvalidKernel";
            case kInvalidLocalNumDimensions: return "kInvalidLocalNumDimensions";
            case kInvalidLocalThreadsTotal: return "kInvalidLocalThreadsTotal";
            case kInvalidLocalThreadsDim: return "kInvalidLocalThreadsDim";
            case kInvalidTempBufferSize: return "kInvalidTempBufferSize";
            case kNotImplemented: return "kNotImplemented";
            case kInvalidMatrixA: return "kInvalidMatrixA";
            case kInvalidMatrixB: return "kInvalidMatrixB";
            case kInvalidMatrixC: return "kInvalidMatrixC";
            case kInvalidVectorX: return "kInvalidVectorX";
            case kInvalidVectorY: return "kInvalidVectorY";
            case kInvalidDimension: return "kInvalidDimension";
            case kInvalidLeadDimA: return "kInvalidLeadDimA";
            case kInvalidLeadDimB: return "kInvalidLeadDimB";
            case kInvalidLeadDimC: return "kInvalidLeadDimC";
            case kInvalidIncrementX: return "kInvalidIncrementX";
            case kInvalidIncrementY: return "kInvalidIncrementY";
            case kInsufficientMemoryA: return "kInsufficientMemoryA";
            case kInsufficientMemoryB: return "kInsufficientMemoryB";
            case kInsufficientMemoryC: return "kInsufficientMemoryC";
            case kInsufficientMemoryX: return "kInsufficientMemoryX";
            case kInsufficientMemoryY: return "kInsufficientMemoryY";
            case kKernelLaunchError: return "kKernelLaunchError";
            case kKernelRunError: return "kKernelRunError";
            case kInvalidLocalMemUsage: return "kInvalidLocalMemUsage";
            case kNoHalfPrecision: return "kNoHalfPrecision";
            case kNoDoublePrecision: return "kNoDoublePrecision";
            case kInvalidVectorDot: return "kInvalidVectorDot";
            case kInsufficientMemoryDot: return "kInsufficientMemoryDot";
        }
        return "INVALID StatusCode: "+n;
    }
}


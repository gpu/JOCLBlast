/*
 * JOCLBlast - Java bindings for CLBlast
 *
 * Copyright (c) 2016-2017 Marco Hutter - http://www.jocl.org
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
public class CLBlastStatusCode
{
    /**
     * CL_SUCCESS
     */
    public static final int CLBlastSuccess = 0;
    /**
     * CL_COMPILER_NOT_AVAILABLE
     */
    public static final int CLBlastOpenCLCompilerNotAvailable = -3;
    /**
     * CL_MEM_OBJECT_ALLOCATION_FAILURE
     */
    public static final int CLBlastTempBufferAllocFailure = -4;
    /**
     * CL_OUT_OF_RESOURCES
     */
    public static final int CLBlastOpenCLOutOfResources = -5;
    /**
     * CL_OUT_OF_HOST_MEMORY
     */
    public static final int CLBlastOpenCLOutOfHostMemory = -6;
    /**
     * CL_BUILD_PROGRAM_FAILURE: OpenCL compilation error
     */
    public static final int CLBlastOpenCLBuildProgramFailure = -11;
    /**
     * CL_INVALID_VALUE
     */
    public static final int CLBlastInvalidValue = -30;
    /**
     * CL_INVALID_COMMAND_QUEUE
     */
    public static final int CLBlastInvalidCommandQueue = -36;
    /**
     * CL_INVALID_MEM_OBJECT
     */
    public static final int CLBlastInvalidMemObject = -38;
    /**
     * CL_INVALID_BINARY
     */
    public static final int CLBlastInvalidBinary = -42;
    /**
     * CL_INVALID_BUILD_OPTIONS
     */
    public static final int CLBlastInvalidBuildOptions = -43;
    /**
     * CL_INVALID_PROGRAM
     */
    public static final int CLBlastInvalidProgram = -44;
    /**
     * CL_INVALID_PROGRAM_EXECUTABLE
     */
    public static final int CLBlastInvalidProgramExecutable = -45;
    /**
     * CL_INVALID_KERNEL_NAME
     */
    public static final int CLBlastInvalidKernelName = -46;
    /**
     * CL_INVALID_KERNEL_DEFINITION
     */
    public static final int CLBlastInvalidKernelDefinition = -47;
    /**
     * CL_INVALID_KERNEL
     */
    public static final int CLBlastInvalidKernel = -48;
    /**
     * CL_INVALID_ARG_INDEX
     */
    public static final int CLBlastInvalidArgIndex = -49;
    /**
     * CL_INVALID_ARG_VALUE
     */
    public static final int CLBlastInvalidArgValue = -50;
    /**
     * CL_INVALID_ARG_SIZE
     */
    public static final int CLBlastInvalidArgSize = -51;
    /**
     * CL_INVALID_KERNEL_ARGS
     */
    public static final int CLBlastInvalidKernelArgs = -52;
    /**
     * CL_INVALID_WORK_DIMENSION: Too many thread dimensions
     */
    public static final int CLBlastInvalidLocalNumDimensions = -53;
    /**
     * CL_INVALID_WORK_GROUP_SIZE: Too many threads in total
     */
    public static final int CLBlastInvalidLocalThreadsTotal = -54;
    /**
     * CL_INVALID_WORK_ITEM_SIZE: ... or for a specific dimension
     */
    public static final int CLBlastInvalidLocalThreadsDim = -55;
    /**
     * CL_INVALID_GLOBAL_OFFSET
     */
    public static final int CLBlastInvalidGlobalOffset = -56;
    /**
     * CL_INVALID_EVENT_WAIT_LIST
     */
    public static final int CLBlastInvalidEventWaitList = -57;
    /**
     * CL_INVALID_EVENT
     */
    public static final int CLBlastInvalidEvent = -58;
    /**
     * CL_INVALID_OPERATION
     */
    public static final int CLBlastInvalidOperation = -59;
    /**
     * CL_INVALID_BUFFER_SIZE
     */
    public static final int CLBlastInvalidBufferSize = -61;
    /**
     * CL_INVALID_GLOBAL_WORK_SIZE
     */
    public static final int CLBlastInvalidGlobalWorkSize = -63;

    // Status codes in common with the clBLAS library
    /**
     * Routine or functionality not implemented yet
     */
    public static final int CLBlastNotImplemented = -1024; 
    /**
     * Matrix A is not a valid OpenCL buffer
     */
    public static final int CLBlastInvalidMatrixA = -1022;
    /**
     * Matrix B is not a valid OpenCL buffer
     */
    public static final int CLBlastInvalidMatrixB = -1021;
    /**
     * Matrix C is not a valid OpenCL buffer
     */
    public static final int CLBlastInvalidMatrixC = -1020;
    /**
     * Vector X is not a valid OpenCL buffer
     */
    public static final int CLBlastInvalidVectorX = -1019;
    /**
     * Vector Y is not a valid OpenCL buffer
     */
    public static final int CLBlastInvalidVectorY = -1018;
    /**
     * Dimensions M, N, and K have to be larger than zero
     */
    public static final int CLBlastInvalidDimension = -1017;
    /**
     * LD of A is smaller than the matrix's first dimension
     */
    public static final int CLBlastInvalidLeadDimA = -1016;
    /**
     * LD of B is smaller than the matrix's first dimension
     */
    public static final int CLBlastInvalidLeadDimB = -1015;
    /**
     * LD of C is smaller than the matrix's first dimension
     */
    public static final int CLBlastInvalidLeadDimC = -1014;
    /**
     * Increment of vector X cannot be zero
     */
    public static final int CLBlastInvalidIncrementX = -1013;
    /**
     * Increment of vector Y cannot be zero
     */
    public static final int CLBlastInvalidIncrementY = -1012;
    /**
     * Matrix A's OpenCL buffer is too small
     */
    public static final int CLBlastInsufficientMemoryA = -1011;
    /**
     * Matrix B's OpenCL buffer is too small
     */
    public static final int CLBlastInsufficientMemoryB = -1010;
    /**
     * Matrix C's OpenCL buffer is too small
     */
    public static final int CLBlastInsufficientMemoryC = -1009;
    /**
     * Vector X's OpenCL buffer is too small
     */
    public static final int CLBlastInsufficientMemoryX = -1008;
    /**
     * Vector Y's OpenCL buffer is too small
     */
    public static final int CLBlastInsufficientMemoryY = -1007;
    
    // Custom additional status codes for CLBlast
    
    /**
     * The batch count needs to be positive
     */
    public static final int CLBlastInvalidBatchCount = -2049;
    /**
     * Trying to override parameters for an invalid kernel
     */
    public static final int CLBlastInvalidOverrideKernel = -2048;
    /**
     * Missing override parameter(s) for the target kernel
     */
    public static final int CLBlastMissingOverrideParameter = -2047;
    /**
     * Not enough local memory available on this device
     */
    public static final int CLBlastInvalidLocalMemUsage = -2046;
    /**
     * Half precision (16-bits) not supported by the device
     */
    public static final int CLBlastNoHalfPrecision = -2045;
    /**
     * Double precision (64-bits) not supported by the device
     */
    public static final int CLBlastNoDoublePrecision = -2044;
    /**
     * The unit-sized vector is not a valid OpenCL buffer
     */
    public static final int CLBlastInvalidVectorScalar = -2043;
    /**
     * The unit-sized vector's OpenCL buffer is too small
     */
    public static final int CLBlastInsufficientMemoryScalar = -2042;
    /**
     * Entry for the device was not found in the database
     */
    public static final int CLBlastDatabaseError = -2041;
    /**
     * A catch-all error code representing an unspecified error
     */
    public static final int CLBlastUnknownError = -2040;
    /**
     * A catch-all error code representing an unexpected exception
     */
    public static final int CLBlastUnexpectedError = -2039;

    /**
     * Private constructor to prevent instantiation
     */
    private CLBlastStatusCode()
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
            case CLBlastSuccess: return "CLBlastSuccess";
            case CLBlastOpenCLCompilerNotAvailable: return "CLBlastOpenCLCompilerNotAvailable";
            case CLBlastTempBufferAllocFailure: return "CLBlastTempBufferAllocFailure";
            case CLBlastOpenCLOutOfResources: return "CLBlastOpenCLOutOfResources";
            case CLBlastOpenCLOutOfHostMemory: return "CLBlastOpenCLOutOfHostMemory";
            case CLBlastOpenCLBuildProgramFailure: return "CLBlastOpenCLBuildProgramFailure";
            case CLBlastInvalidValue: return "CLBlastInvalidValue";
            case CLBlastInvalidCommandQueue: return "CLBlastInvalidCommandQueue";
            case CLBlastInvalidMemObject: return "CLBlastInvalidMemObject";
            case CLBlastInvalidBinary: return "CLBlastInvalidBinary";
            case CLBlastInvalidBuildOptions: return "CLBlastInvalidBuildOptions";
            case CLBlastInvalidProgram: return "CLBlastInvalidProgram";
            case CLBlastInvalidProgramExecutable: return "CLBlastInvalidProgramExecutable";
            case CLBlastInvalidKernelName: return "CLBlastInvalidKernelName";
            case CLBlastInvalidKernelDefinition: return "CLBlastInvalidKernelDefinition";
            case CLBlastInvalidKernel: return "CLBlastInvalidKernel";
            case CLBlastInvalidArgIndex: return "CLBlastInvalidArgIndex";
            case CLBlastInvalidArgValue: return "CLBlastInvalidArgValue";
            case CLBlastInvalidArgSize: return "CLBlastInvalidArgSize";
            case CLBlastInvalidKernelArgs: return "CLBlastInvalidKernelArgs";
            case CLBlastInvalidLocalNumDimensions: return "CLBlastInvalidLocalNumDimensions";
            case CLBlastInvalidLocalThreadsTotal: return "CLBlastInvalidLocalThreadsTotal";
            case CLBlastInvalidLocalThreadsDim: return "CLBlastInvalidLocalThreadsDim";
            case CLBlastInvalidGlobalOffset: return "CLBlastInvalidGlobalOffset";
            case CLBlastInvalidEventWaitList: return "CLBlastInvalidEventWaitList";
            case CLBlastInvalidEvent: return "CLBlastInvalidEvent";
            case CLBlastInvalidOperation: return "CLBlastInvalidOperation";
            case CLBlastInvalidBufferSize: return "CLBlastInvalidBufferSize";
            case CLBlastInvalidGlobalWorkSize: return "CLBlastInvalidGlobalWorkSize";
            case CLBlastNotImplemented: return "CLBlastNotImplemented";
            case CLBlastInvalidMatrixA: return "CLBlastInvalidMatrixA";
            case CLBlastInvalidMatrixB: return "CLBlastInvalidMatrixB";
            case CLBlastInvalidMatrixC: return "CLBlastInvalidMatrixC";
            case CLBlastInvalidVectorX: return "CLBlastInvalidVectorX";
            case CLBlastInvalidVectorY: return "CLBlastInvalidVectorY";
            case CLBlastInvalidDimension: return "CLBlastInvalidDimension";
            case CLBlastInvalidLeadDimA: return "CLBlastInvalidLeadDimA";
            case CLBlastInvalidLeadDimB: return "CLBlastInvalidLeadDimB";
            case CLBlastInvalidLeadDimC: return "CLBlastInvalidLeadDimC";
            case CLBlastInvalidIncrementX: return "CLBlastInvalidIncrementX";
            case CLBlastInvalidIncrementY: return "CLBlastInvalidIncrementY";
            case CLBlastInsufficientMemoryA: return "CLBlastInsufficientMemoryA";
            case CLBlastInsufficientMemoryB: return "CLBlastInsufficientMemoryB";
            case CLBlastInsufficientMemoryC: return "CLBlastInsufficientMemoryC";
            case CLBlastInsufficientMemoryX: return "CLBlastInsufficientMemoryX";
            case CLBlastInsufficientMemoryY: return "CLBlastInsufficientMemoryY";
            case CLBlastInvalidBatchCount: return "CLBlastInvalidBatchCount";
            case CLBlastInvalidOverrideKernel: return "CLBlastInvalidOverrideKernel";
            case CLBlastMissingOverrideParameter: return "CLBlastMissingOverrideParameter";
            case CLBlastInvalidLocalMemUsage: return "CLBlastInvalidLocalMemUsage";
            case CLBlastNoHalfPrecision: return "CLBlastNoHalfPrecision";
            case CLBlastNoDoublePrecision: return "CLBlastNoDoublePrecision";
            case CLBlastInvalidVectorScalar: return "CLBlastInvalidVectorScalar";
            case CLBlastInsufficientMemoryScalar: return "CLBlastInsufficientMemoryScalar";
            case CLBlastDatabaseError: return "CLBlastDatabaseError";
            case CLBlastUnknownError: return "CLBlastUnknownError";
            case CLBlastUnexpectedError: return "CLBlastUnexpectedError";
        }
        return "INVALID CLBlastStatusCode: "+n;
    }
}


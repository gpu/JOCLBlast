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

import org.jocl.CL;
import org.jocl.CLException;
import org.jocl.LibUtils;
import org.jocl.cl_command_queue;
import org.jocl.cl_event;
import org.jocl.cl_mem;
import org.jocl.CL.LogLevel;

/**
 * CLBlast
 */
public class CLBlast
{
    // Initialization of the native library
    static
    {
        String libraryBaseName = "JOCLBlast_0_0_1";
        String libraryName = 
            LibUtils.createPlatformLibraryName(libraryBaseName);
        String dependentLibraryNames[] = { "clblast" };
        try
        {
            LibUtils.loadLibrary(libraryName, dependentLibraryNames);
        }
        catch (UnsatisfiedLinkError e)
        {
            throw e;
        }
    }
    
    /**
     * Indicates whether exceptions are enabled. When exceptions are
     * enabled, CLException is thrown if a method is about to return
     * a result code that is not CL.CL_SUCCESS
     */
    private static boolean exceptionsEnabled = false;
    
    /**
     * Enables or disables exceptions. By default, the methods of this class
     * only return the error code from the underlying OpenCL function.
     * If exceptions are enabled, a CLException with a detailed error
     * message will be thrown if a method is about to return a result code
     * that is not CL_SUCCESS
     *
     * @param enabled Whether exceptions are enabled
     */
    public static void setExceptionsEnabled(boolean enabled)
    {
        exceptionsEnabled = enabled;
    }

    /**
     * If the given result is different to CL_SUCCESS and
     * exceptions have been enabled, this method will throw a
     * CLException with an error message that corresponds to the
     * given result code. Otherwise, the given result is simply
     * returned.
     *
     * @param result The result to check
     * @return The result that was given as the parameter
     * @throws CLException If exceptions have been enabled and
     * the given result code is not CL_SUCCESS
     */
    private static int checkResult(int result)
    {
        if (exceptionsEnabled && result != CL.CL_SUCCESS)
        {
            throw new CLException(CL.stringFor_errorCode(result), result);
        }
        return result;
    }
    
    /**
     * If the given result is <code>null</code> and exceptions have been 
     * enabled, then this method will throw a CLException. Otherwise, 
     * the given result is simply returned.
     *
     * @param result The result to check
     * @return The result that was given as the parameter
     * @throws CLException If exceptions have been enabled and
     * the given result is <code>null</code>
     */
    private static cl_mem checkResult(cl_mem result)
    {
        if (exceptionsEnabled && result == null)
        {
            throw new CLException("Could not create cl_mem");
        }
        return result;
    }
    
    /**
     * Set the specified log level for the library.
     * <p>
     * Currently supported log levels:
     * <p>
     * LOG_QUIET: Never print anything <p>
     * LOG_ERROR: Print error messages <p>
     * LOG_TRACE: Print a trace of all native function calls <p>
     *
     * @param logLevel The log level to use.
     */
    public static void setLogLevel(LogLevel logLevel)
    {
        setLogLevelNative(logLevel.ordinal());
    }
    private static native void setLogLevelNative(int logLevel);
    
    
    public static final int JOCL_BLAST_STATUS_INTERNAL_ERROR = -32786;
    
    // =================================================================================================
    // BLAS level-1 (vector-vector) routines
    // =================================================================================================
    // Swap two vectors: SSWAP/DSWAP/CSWAP/ZSWAP
    public static int CLBlastSswap(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSswapNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastSswapNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDswap(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDswapNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastDswapNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCswap(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCswapNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastCswapNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZswap(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZswapNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastZswapNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Vector scaling: SSCAL/DSCAL/CSCAL/ZSCAL
    public static int CLBlastSscal(
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSscalNative(n, alpha, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastSscalNative(
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDscal(
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDscalNative(n, alpha, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDscalNative(
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCscal(
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCscalNative(n, alpha, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastCscalNative(
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZscal(
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZscalNative(n, alpha, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastZscalNative(
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Vector copy: SCOPY/DCOPY/CCOPY/ZCOPY
    public static int CLBlastScopy(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastScopyNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastScopyNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDcopy(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDcopyNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastDcopyNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCcopy(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCcopyNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastCcopyNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZcopy(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZcopyNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastZcopyNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Vector-times-constant plus vector: SAXPY/DAXPY/CAXPY/ZAXPY
    public static int CLBlastSaxpy(
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSaxpyNative(n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastSaxpyNative(
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDaxpy(
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDaxpyNative(n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastDaxpyNative(
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCaxpy(
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCaxpyNative(n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastCaxpyNative(
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZaxpy(
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZaxpyNative(n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastZaxpyNative(
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Dot product of two vectors: SDOT/DDOT
    public static int CLBlastSdot(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSdotNative(n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastSdotNative(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDdot(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDdotNative(n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastDdotNative(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Dot product of two complex vectors: CDOTU/ZDOTU
    public static int CLBlastCdotu(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCdotuNative(n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastCdotuNative(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZdotu(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZdotuNative(n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastZdotuNative(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Dot product of two complex vectors, one conjugated: CDOTC/ZDOTC
    public static int CLBlastCdotc(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCdotcNative(n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastCdotcNative(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZdotc(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZdotcNative(n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastZdotcNative(
        long n, 
        cl_mem dot_buffer, 
        long dot_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // =================================================================================================
    // BLAS level-2 (matrix-vector) routines
    // =================================================================================================
    // General matrix-vector multiplication: SGEMV/DGEMV/CGEMV/ZGEMV
    public static int CLBlastSgemv(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSgemvNative(layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastSgemvNative(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDgemv(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDgemvNative(layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastDgemvNative(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCgemv(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCgemvNative(layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastCgemvNative(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZgemv(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZgemvNative(layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastZgemvNative(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // General banded matrix-vector multiplication: SGBMV/DGBMV/CGBMV/ZGBMV
    public static int CLBlastSgbmv(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        long kl, 
        long ku, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSgbmvNative(layout, a_transpose, m, n, kl, ku, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastSgbmvNative(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        long kl, 
        long ku, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDgbmv(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        long kl, 
        long ku, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDgbmvNative(layout, a_transpose, m, n, kl, ku, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastDgbmvNative(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        long kl, 
        long ku, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCgbmv(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        long kl, 
        long ku, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCgbmvNative(layout, a_transpose, m, n, kl, ku, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastCgbmvNative(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        long kl, 
        long ku, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZgbmv(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        long kl, 
        long ku, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZgbmvNative(layout, a_transpose, m, n, kl, ku, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastZgbmvNative(
        int layout, 
        int a_transpose, 
        long m, 
        long n, 
        long kl, 
        long ku, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Hermitian matrix-vector multiplication: CHEMV/ZHEMV
    public static int CLBlastChemv(
        int layout, 
        int triangle, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastChemvNative(layout, triangle, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastChemvNative(
        int layout, 
        int triangle, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZhemv(
        int layout, 
        int triangle, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZhemvNative(layout, triangle, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastZhemvNative(
        int layout, 
        int triangle, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Hermitian banded matrix-vector multiplication: CHBMV/ZHBMV
    public static int CLBlastChbmv(
        int layout, 
        int triangle, 
        long n, 
        long k, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastChbmvNative(layout, triangle, n, k, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastChbmvNative(
        int layout, 
        int triangle, 
        long n, 
        long k, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZhbmv(
        int layout, 
        int triangle, 
        long n, 
        long k, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZhbmvNative(layout, triangle, n, k, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastZhbmvNative(
        int layout, 
        int triangle, 
        long n, 
        long k, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Hermitian packed matrix-vector multiplication: CHPMV/ZHPMV
    public static int CLBlastChpmv(
        int layout, 
        int triangle, 
        long n, 
        float[] alpha, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastChpmvNative(layout, triangle, n, alpha, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastChpmvNative(
        int layout, 
        int triangle, 
        long n, 
        float[] alpha, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZhpmv(
        int layout, 
        int triangle, 
        long n, 
        double[] alpha, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZhpmvNative(layout, triangle, n, alpha, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastZhpmvNative(
        int layout, 
        int triangle, 
        long n, 
        double[] alpha, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double[] beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Symmetric matrix-vector multiplication: SSYMV/DSYMV
    public static int CLBlastSsymv(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSsymvNative(layout, triangle, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastSsymvNative(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDsymv(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDsymvNative(layout, triangle, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastDsymvNative(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Symmetric banded matrix-vector multiplication: SSBMV/DSBMV
    public static int CLBlastSsbmv(
        int layout, 
        int triangle, 
        long n, 
        long k, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSsbmvNative(layout, triangle, n, k, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastSsbmvNative(
        int layout, 
        int triangle, 
        long n, 
        long k, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDsbmv(
        int layout, 
        int triangle, 
        long n, 
        long k, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDsbmvNative(layout, triangle, n, k, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastDsbmvNative(
        int layout, 
        int triangle, 
        long n, 
        long k, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Symmetric packed matrix-vector multiplication: SSPMV/DSPMV
    public static int CLBlastSspmv(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSspmvNative(layout, triangle, n, alpha, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastSspmvNative(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        float beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDspmv(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDspmvNative(layout, triangle, n, alpha, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event));
    }
    private static native int CLBlastDspmvNative(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        double beta, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Triangular matrix-vector multiplication: STRMV/DTRMV/CTRMV/ZTRMV
    public static int CLBlastStrmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastStrmvNative(layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastStrmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDtrmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDtrmvNative(layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDtrmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCtrmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCtrmvNative(layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastCtrmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZtrmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZtrmvNative(layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastZtrmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Triangular banded matrix-vector multiplication: STBMV/DTBMV/CTBMV/ZTBMV
    public static int CLBlastStbmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastStbmvNative(layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastStbmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDtbmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDtbmvNative(layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDtbmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCtbmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCtbmvNative(layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastCtbmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZtbmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZtbmvNative(layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastZtbmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Triangular packed matrix-vector multiplication: STPMV/DTPMV/CTPMV/ZTPMV
    public static int CLBlastStpmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastStpmvNative(layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastStpmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDtpmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDtpmvNative(layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDtpmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCtpmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCtpmvNative(layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastCtpmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZtpmv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZtpmvNative(layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastZtpmvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Solves a triangular system of equations: STRSV/DTRSV/CTRSV/ZTRSV
    public static int CLBlastStrsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastStrsvNative(layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastStrsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDtrsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDtrsvNative(layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDtrsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCtrsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCtrsvNative(layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastCtrsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZtrsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZtrsvNative(layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastZtrsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Solves a banded triangular system of equations: STBSV/DTBSV/CTBSV/ZTBSV
    public static int CLBlastStbsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastStbsvNative(layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastStbsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDtbsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDtbsvNative(layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDtbsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCtbsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCtbsvNative(layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastCtbsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZtbsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZtbsvNative(layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastZtbsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        long k, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Solves a packed triangular system of equations: STPSV/DTPSV/CTPSV/ZTPSV
    public static int CLBlastStpsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastStpsvNative(layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastStpsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDtpsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDtpsvNative(layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDtpsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCtpsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCtpsvNative(layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastCtpsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZtpsv(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZtpsvNative(layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastZtpsvNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long n, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // General rank-1 matrix update: SGER/DGER
    public static int CLBlastSger(
        int layout, 
        long m, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSgerNative(layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastSgerNative(
        int layout, 
        long m, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDger(
        int layout, 
        long m, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDgerNative(layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastDgerNative(
        int layout, 
        long m, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    // General rank-1 complex matrix update: CGERU/ZGERU
    public static int CLBlastCgeru(
        int layout, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCgeruNative(layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastCgeruNative(
        int layout, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZgeru(
        int layout, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZgeruNative(layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastZgeruNative(
        int layout, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    // General rank-1 complex conjugated matrix update: CGERC/ZGERC
    public static int CLBlastCgerc(
        int layout, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCgercNative(layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastCgercNative(
        int layout, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZgerc(
        int layout, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZgercNative(layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastZgercNative(
        int layout, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Hermitian rank-1 matrix update: CHER/ZHER
    public static int CLBlastCher(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCherNative(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastCherNative(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZher(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZherNative(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastZherNative(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Hermitian packed rank-1 matrix update: CHPR/ZHPR
    public static int CLBlastChpr(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastChprNative(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, ap_buffer, ap_offset, queue, event));
    }
    private static native int CLBlastChprNative(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZhpr(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZhprNative(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, ap_buffer, ap_offset, queue, event));
    }
    private static native int CLBlastZhprNative(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event);


    // Hermitian rank-2 matrix update: CHER2/ZHER2
    public static int CLBlastCher2(
        int layout, 
        int triangle, 
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCher2Native(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastCher2Native(
        int layout, 
        int triangle, 
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZher2(
        int layout, 
        int triangle, 
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZher2Native(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastZher2Native(
        int layout, 
        int triangle, 
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Hermitian packed rank-2 matrix update: CHPR2/ZHPR2
    public static int CLBlastChpr2(
        int layout, 
        int triangle, 
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastChpr2Native(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, ap_buffer, ap_offset, queue, event));
    }
    private static native int CLBlastChpr2Native(
        int layout, 
        int triangle, 
        long n, 
        float[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZhpr2(
        int layout, 
        int triangle, 
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZhpr2Native(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, ap_buffer, ap_offset, queue, event));
    }
    private static native int CLBlastZhpr2Native(
        int layout, 
        int triangle, 
        long n, 
        double[] alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event);


    // Symmetric rank-1 matrix update: SSYR/DSYR
    public static int CLBlastSsyr(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSsyrNative(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastSsyrNative(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDsyr(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDsyrNative(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastDsyrNative(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Symmetric packed rank-1 matrix update: SSPR/DSPR
    public static int CLBlastSspr(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSsprNative(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, ap_buffer, ap_offset, queue, event));
    }
    private static native int CLBlastSsprNative(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDspr(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDsprNative(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, ap_buffer, ap_offset, queue, event));
    }
    private static native int CLBlastDsprNative(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event);


    // Symmetric rank-2 matrix update: SSYR2/DSYR2
    public static int CLBlastSsyr2(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSsyr2Native(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastSsyr2Native(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDsyr2(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDsyr2Native(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event));
    }
    private static native int CLBlastDsyr2Native(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Symmetric packed rank-2 matrix update: SSPR2/DSPR2
    public static int CLBlastSspr2(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSspr2Native(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, ap_buffer, ap_offset, queue, event));
    }
    private static native int CLBlastSspr2Native(
        int layout, 
        int triangle, 
        long n, 
        float alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDspr2(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDspr2Native(layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, ap_buffer, ap_offset, queue, event));
    }
    private static native int CLBlastDspr2Native(
        int layout, 
        int triangle, 
        long n, 
        double alpha, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem ap_buffer, 
        long ap_offset, 
        cl_command_queue queue, 
        cl_event event);


    // =================================================================================================
    // BLAS level-3 (matrix-matrix) routines
    // =================================================================================================
    // General matrix-matrix multiplication: SGEMM/DGEMM/CGEMM/ZGEMM
    public static int CLBlastSgemm(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSgemmNative(layout, a_transpose, b_transpose, m, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastSgemmNative(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDgemm(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDgemmNative(layout, a_transpose, b_transpose, m, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastDgemmNative(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCgemm(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCgemmNative(layout, a_transpose, b_transpose, m, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastCgemmNative(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZgemm(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZgemmNative(layout, a_transpose, b_transpose, m, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastZgemmNative(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Symmetric matrix-matrix multiplication: SSYMM/DSYMM/CSYMM/ZSYMM
    public static int CLBlastSsymm(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSsymmNative(layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastSsymmNative(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDsymm(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDsymmNative(layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastDsymmNative(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCsymm(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCsymmNative(layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastCsymmNative(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZsymm(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZsymmNative(layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastZsymmNative(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Hermitian matrix-matrix multiplication: CHEMM/ZHEMM
    public static int CLBlastChemm(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastChemmNative(layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastChemmNative(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZhemm(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZhemmNative(layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastZhemmNative(
        int layout, 
        int side, 
        int triangle, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Rank-K update of a symmetric matrix: SSYRK/DSYRK/CSYRK/ZSYRK
    public static int CLBlastSsyrk(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSsyrkNative(layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastSsyrkNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDsyrk(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDsyrkNative(layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastDsyrkNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCsyrk(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        float[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCsyrkNative(layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastCsyrkNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        float[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZsyrk(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        double[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZsyrkNative(layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastZsyrkNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        double[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Rank-K update of a hermitian matrix: CHERK/ZHERK
    public static int CLBlastCherk(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCherkNative(layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastCherkNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZherk(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZherkNative(layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastZherkNative(
        int layout, 
        int triangle, 
        int a_transpose, 
        long n, 
        long k, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Rank-2K update of a symmetric matrix: SSYR2K/DSYR2K/CSYR2K/ZSYR2K
    public static int CLBlastSsyr2k(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSsyr2kNative(layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastSsyr2kNative(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDsyr2k(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDsyr2kNative(layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastDsyr2kNative(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCsyr2k(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCsyr2kNative(layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastCsyr2kNative(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZsyr2k(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZsyr2kNative(layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastZsyr2kNative(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double[] beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Rank-2K update of a hermitian matrix: CHER2K/ZHER2K
    public static int CLBlastCher2k(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCher2kNative(layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastCher2kNative(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        float beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZher2k(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZher2kNative(layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event));
    }
    private static native int CLBlastZher2kNative(
        int layout, 
        int triangle, 
        int ab_transpose, 
        long n, 
        long k, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        double beta, 
        cl_mem c_buffer, 
        long c_offset, 
        long c_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Triangular matrix-matrix multiplication: STRMM/DTRMM/CTRMM/ZTRMM
    public static int CLBlastStrmm(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastStrmmNative(layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastStrmmNative(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDtrmm(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDtrmmNative(layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastDtrmmNative(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCtrmm(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCtrmmNative(layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastCtrmmNative(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZtrmm(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZtrmmNative(layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastZtrmmNative(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event);


    // Solves a triangular system of equations: STRSM/DTRSM/CTRSM/ZTRSM
    public static int CLBlastStrsm(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastStrsmNative(layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastStrsmNative(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        float alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDtrsm(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDtrsmNative(layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastDtrsmNative(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        double alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCtrsm(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCtrsmNative(layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastCtrsmNative(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        float[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZtrsm(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZtrsmNative(layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastZtrsmNative(
        int layout, 
        int side, 
        int triangle, 
        int a_transpose, 
        int diagonal, 
        long m, 
        long n, 
        double[] alpha, 
        cl_mem a_buffer, 
        long a_offset, 
        long a_ld, 
        cl_mem b_buffer, 
        long b_offset, 
        long b_ld, 
        cl_command_queue queue, 
        cl_event event);


    /**
     * Private constructor to prevent instantiation
     */
    private CLBlast()
    {
        // Private constructor to prevent instantiation
    }
}


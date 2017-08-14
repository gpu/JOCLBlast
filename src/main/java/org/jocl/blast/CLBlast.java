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
import org.jocl.cl_device_id;
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
        String versionString = "1_0_1";
        String libraryBaseName = "JOCLBlast_" + versionString;
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
            throw new CLException(CLBlastStatusCode.stringFor(result), result);
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
    // Generate givens plane rotation: SROTG/DROTG
    public static int CLBlastSrotg(
        cl_mem sa_buffer, 
        long sa_offset, 
        cl_mem sb_buffer, 
        long sb_offset, 
        cl_mem sc_buffer, 
        long sc_offset, 
        cl_mem ss_buffer, 
        long ss_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSrotgNative(sa_buffer, sa_offset, sb_buffer, sb_offset, sc_buffer, sc_offset, ss_buffer, ss_offset, queue, event));
    }
    private static native int CLBlastSrotgNative(
        cl_mem sa_buffer, 
        long sa_offset, 
        cl_mem sb_buffer, 
        long sb_offset, 
        cl_mem sc_buffer, 
        long sc_offset, 
        cl_mem ss_buffer, 
        long ss_offset, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDrotg(
        cl_mem sa_buffer, 
        long sa_offset, 
        cl_mem sb_buffer, 
        long sb_offset, 
        cl_mem sc_buffer, 
        long sc_offset, 
        cl_mem ss_buffer, 
        long ss_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDrotgNative(sa_buffer, sa_offset, sb_buffer, sb_offset, sc_buffer, sc_offset, ss_buffer, ss_offset, queue, event));
    }
    private static native int CLBlastDrotgNative(
        cl_mem sa_buffer, 
        long sa_offset, 
        cl_mem sb_buffer, 
        long sb_offset, 
        cl_mem sc_buffer, 
        long sc_offset, 
        cl_mem ss_buffer, 
        long ss_offset, 
        cl_command_queue queue, 
        cl_event event);


    // Generate modified givens plane rotation: SROTMG/DROTMG
    public static int CLBlastSrotmg(
        cl_mem sd1_buffer, 
        long sd1_offset, 
        cl_mem sd2_buffer, 
        long sd2_offset, 
        cl_mem sx1_buffer, 
        long sx1_offset, 
        cl_mem sy1_buffer, 
        long sy1_offset, 
        cl_mem sparam_buffer, 
        long sparam_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSrotmgNative(sd1_buffer, sd1_offset, sd2_buffer, sd2_offset, sx1_buffer, sx1_offset, sy1_buffer, sy1_offset, sparam_buffer, sparam_offset, queue, event));
    }
    private static native int CLBlastSrotmgNative(
        cl_mem sd1_buffer, 
        long sd1_offset, 
        cl_mem sd2_buffer, 
        long sd2_offset, 
        cl_mem sx1_buffer, 
        long sx1_offset, 
        cl_mem sy1_buffer, 
        long sy1_offset, 
        cl_mem sparam_buffer, 
        long sparam_offset, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDrotmg(
        cl_mem sd1_buffer, 
        long sd1_offset, 
        cl_mem sd2_buffer, 
        long sd2_offset, 
        cl_mem sx1_buffer, 
        long sx1_offset, 
        cl_mem sy1_buffer, 
        long sy1_offset, 
        cl_mem sparam_buffer, 
        long sparam_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDrotmgNative(sd1_buffer, sd1_offset, sd2_buffer, sd2_offset, sx1_buffer, sx1_offset, sy1_buffer, sy1_offset, sparam_buffer, sparam_offset, queue, event));
    }
    private static native int CLBlastDrotmgNative(
        cl_mem sd1_buffer, 
        long sd1_offset, 
        cl_mem sd2_buffer, 
        long sd2_offset, 
        cl_mem sx1_buffer, 
        long sx1_offset, 
        cl_mem sy1_buffer, 
        long sy1_offset, 
        cl_mem sparam_buffer, 
        long sparam_offset, 
        cl_command_queue queue, 
        cl_event event);


    // Apply givens plane rotation: SROT/DROT
    public static int CLBlastSrot(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        float cos, 
        float sin, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSrotNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, cos, sin, queue, event));
    }
    private static native int CLBlastSrotNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        float cos, 
        float sin, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDrot(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        double cos, 
        double sin, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDrotNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, cos, sin, queue, event));
    }
    private static native int CLBlastDrotNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        double cos, 
        double sin, 
        cl_command_queue queue, 
        cl_event event);


    // Apply modified givens plane rotation: SROTM/DROTM
    public static int CLBlastSrotm(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem sparam_buffer, 
        long sparam_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSrotmNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, sparam_buffer, sparam_offset, queue, event));
    }
    private static native int CLBlastSrotmNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem sparam_buffer, 
        long sparam_offset, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDrotm(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem sparam_buffer, 
        long sparam_offset, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDrotmNative(n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, sparam_buffer, sparam_offset, queue, event));
    }
    private static native int CLBlastDrotmNative(
        long n, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_mem y_buffer, 
        long y_offset, 
        long y_inc, 
        cl_mem sparam_buffer, 
        long sparam_offset, 
        cl_command_queue queue, 
        cl_event event);


    // Swap two vectors: SSWAP/DSWAP/CSWAP/ZSWAP/HSWAP
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


    // Vector scaling: SSCAL/DSCAL/CSCAL/ZSCAL/HSCAL
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


    // Vector copy: SCOPY/DCOPY/CCOPY/ZCOPY/HCOPY
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


    // Vector-times-constant plus vector: SAXPY/DAXPY/CAXPY/ZAXPY/HAXPY
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


    // Dot product of two vectors: SDOT/DDOT/HDOT
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


    // Euclidian norm of a vector: SNRM2/DNRM2/ScNRM2/DzNRM2/HNRM2
    public static int CLBlastSnrm2(
        long n, 
        cl_mem nrm2_buffer, 
        long nrm2_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSnrm2Native(n, nrm2_buffer, nrm2_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastSnrm2Native(
        long n, 
        cl_mem nrm2_buffer, 
        long nrm2_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDnrm2(
        long n, 
        cl_mem nrm2_buffer, 
        long nrm2_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDnrm2Native(n, nrm2_buffer, nrm2_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDnrm2Native(
        long n, 
        cl_mem nrm2_buffer, 
        long nrm2_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastScnrm2(
        long n, 
        cl_mem nrm2_buffer, 
        long nrm2_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastScnrm2Native(n, nrm2_buffer, nrm2_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastScnrm2Native(
        long n, 
        cl_mem nrm2_buffer, 
        long nrm2_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDznrm2(
        long n, 
        cl_mem nrm2_buffer, 
        long nrm2_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDznrm2Native(n, nrm2_buffer, nrm2_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDznrm2Native(
        long n, 
        cl_mem nrm2_buffer, 
        long nrm2_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Absolute sum of values in a vector: SASUM/DASUM/ScASUM/DzASUM/HASUM
    public static int CLBlastSasum(
        long n, 
        cl_mem asum_buffer, 
        long asum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSasumNative(n, asum_buffer, asum_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastSasumNative(
        long n, 
        cl_mem asum_buffer, 
        long asum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDasum(
        long n, 
        cl_mem asum_buffer, 
        long asum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDasumNative(n, asum_buffer, asum_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDasumNative(
        long n, 
        cl_mem asum_buffer, 
        long asum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastScasum(
        long n, 
        cl_mem asum_buffer, 
        long asum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastScasumNative(n, asum_buffer, asum_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastScasumNative(
        long n, 
        cl_mem asum_buffer, 
        long asum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDzasum(
        long n, 
        cl_mem asum_buffer, 
        long asum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDzasumNative(n, asum_buffer, asum_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDzasumNative(
        long n, 
        cl_mem asum_buffer, 
        long asum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Sum of values in a vector (non-BLAS function): SSUM/DSUM/ScSUM/DzSUM/HSUM
    public static int CLBlastSsum(
        long n, 
        cl_mem sum_buffer, 
        long sum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSsumNative(n, sum_buffer, sum_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastSsumNative(
        long n, 
        cl_mem sum_buffer, 
        long sum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDsum(
        long n, 
        cl_mem sum_buffer, 
        long sum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDsumNative(n, sum_buffer, sum_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDsumNative(
        long n, 
        cl_mem sum_buffer, 
        long sum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastScsum(
        long n, 
        cl_mem sum_buffer, 
        long sum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastScsumNative(n, sum_buffer, sum_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastScsumNative(
        long n, 
        cl_mem sum_buffer, 
        long sum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDzsum(
        long n, 
        cl_mem sum_buffer, 
        long sum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDzsumNative(n, sum_buffer, sum_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastDzsumNative(
        long n, 
        cl_mem sum_buffer, 
        long sum_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Index of absolute maximum value in a vector: iSAMAX/iDAMAX/iCAMAX/iZAMAX/iHAMAX
    public static int CLBlastiSamax(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiSamaxNative(n, imax_buffer, imax_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiSamaxNative(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiDamax(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiDamaxNative(n, imax_buffer, imax_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiDamaxNative(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiCamax(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiCamaxNative(n, imax_buffer, imax_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiCamaxNative(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiZamax(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiZamaxNative(n, imax_buffer, imax_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiZamaxNative(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Index of absolute minimum value in a vector (non-BLAS function): iSAMIN/iDAMIN/iCAMIN/iZAMIN/iHAMIN
    public static int CLBlastiSamin(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiSaminNative(n, imin_buffer, imin_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiSaminNative(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiDamin(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiDaminNative(n, imin_buffer, imin_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiDaminNative(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiCamin(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiCaminNative(n, imin_buffer, imin_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiCaminNative(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiZamin(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiZaminNative(n, imin_buffer, imin_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiZaminNative(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Index of maximum value in a vector (non-BLAS function): iSMAX/iDMAX/iCMAX/iZMAX/iHMAX
    public static int CLBlastiSmax(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiSmaxNative(n, imax_buffer, imax_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiSmaxNative(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiDmax(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiDmaxNative(n, imax_buffer, imax_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiDmaxNative(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiCmax(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiCmaxNative(n, imax_buffer, imax_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiCmaxNative(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiZmax(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiZmaxNative(n, imax_buffer, imax_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiZmaxNative(
        long n, 
        cl_mem imax_buffer, 
        long imax_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // Index of minimum value in a vector (non-BLAS function): iSMIN/iDMIN/iCMIN/iZMIN/iHMIN
    public static int CLBlastiSmin(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiSminNative(n, imin_buffer, imin_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiSminNative(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiDmin(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiDminNative(n, imin_buffer, imin_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiDminNative(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiCmin(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiCminNative(n, imin_buffer, imin_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiCminNative(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastiZmin(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastiZminNative(n, imin_buffer, imin_offset, x_buffer, x_offset, x_inc, queue, event));
    }
    private static native int CLBlastiZminNative(
        long n, 
        cl_mem imin_buffer, 
        long imin_offset, 
        cl_mem x_buffer, 
        long x_offset, 
        long x_inc, 
        cl_command_queue queue, 
        cl_event event);


    // =================================================================================================
    // BLAS level-2 (matrix-vector) routines
    // =================================================================================================
    // General matrix-vector multiplication: SGEMV/DGEMV/CGEMV/ZGEMV/HGEMV
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


    // General banded matrix-vector multiplication: SGBMV/DGBMV/CGBMV/ZGBMV/HGBMV
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


    // Symmetric matrix-vector multiplication: SSYMV/DSYMV/HSYMV
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


    // Symmetric banded matrix-vector multiplication: SSBMV/DSBMV/HSBMV
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


    // Symmetric packed matrix-vector multiplication: SSPMV/DSPMV/HSPMV
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


    // Triangular matrix-vector multiplication: STRMV/DTRMV/CTRMV/ZTRMV/HTRMV
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


    // Triangular banded matrix-vector multiplication: STBMV/DTBMV/CTBMV/ZTBMV/HTBMV
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


    // Triangular packed matrix-vector multiplication: STPMV/DTPMV/CTPMV/ZTPMV/HTPMV
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


    // General rank-1 matrix update: SGER/DGER/HGER
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


    // Symmetric rank-1 matrix update: SSYR/DSYR/HSYR
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


    // Symmetric packed rank-1 matrix update: SSPR/DSPR/HSPR
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


    // Symmetric rank-2 matrix update: SSYR2/DSYR2/HSYR2
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


    // Symmetric packed rank-2 matrix update: SSPR2/DSPR2/HSPR2
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
    // General matrix-matrix multiplication: SGEMM/DGEMM/CGEMM/ZGEMM/HGEMM
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


    // Symmetric matrix-matrix multiplication: SSYMM/DSYMM/CSYMM/ZSYMM/HSYMM
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


    // Rank-K update of a symmetric matrix: SSYRK/DSYRK/CSYRK/ZSYRK/HSYRK
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


    // Rank-2K update of a symmetric matrix: SSYR2K/DSYR2K/CSYR2K/ZSYR2K/HSYR2K
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


    // Triangular matrix-matrix multiplication: STRMM/DTRMM/CTRMM/ZTRMM/HTRMM
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


    // =================================================================================================
    // Extra non-BLAS routines (level-X)
    // =================================================================================================
    // Scaling and out-place transpose/copy (non-BLAS function): SOMATCOPY/DOMATCOPY/COMATCOPY/ZOMATCOPY/HOMATCOPY
    public static int CLBlastSomatcopy(
        int layout, 
        int a_transpose, 
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
        return checkResult(CLBlastSomatcopyNative(layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastSomatcopyNative(
        int layout, 
        int a_transpose, 
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


    public static int CLBlastDomatcopy(
        int layout, 
        int a_transpose, 
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
        return checkResult(CLBlastDomatcopyNative(layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastDomatcopyNative(
        int layout, 
        int a_transpose, 
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


    public static int CLBlastComatcopy(
        int layout, 
        int a_transpose, 
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
        return checkResult(CLBlastComatcopyNative(layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastComatcopyNative(
        int layout, 
        int a_transpose, 
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


    public static int CLBlastZomatcopy(
        int layout, 
        int a_transpose, 
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
        return checkResult(CLBlastZomatcopyNative(layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event));
    }
    private static native int CLBlastZomatcopyNative(
        int layout, 
        int a_transpose, 
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


    // Batched version of AXPY: SAXPYBATCHED/DAXPYBATCHED/CAXPYBATCHED/ZAXPYBATCHED/HAXPYBATCHED
    public static int CLBlastSaxpyBatched(
        long n, 
        float[] alphas, 
        cl_mem x_buffer, 
        long[] x_offsets, 
        long x_inc, 
        cl_mem y_buffer, 
        long[] y_offsets, 
        long y_inc, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSaxpyBatchedNative(n, alphas, x_buffer, x_offsets, x_inc, y_buffer, y_offsets, y_inc, batch_count, queue, event));
    }
    private static native int CLBlastSaxpyBatchedNative(
        long n, 
        float[] alphas, 
        cl_mem x_buffer, 
        long[] x_offsets, 
        long x_inc, 
        cl_mem y_buffer, 
        long[] y_offsets, 
        long y_inc, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDaxpyBatched(
        long n, 
        double[] alphas, 
        cl_mem x_buffer, 
        long[] x_offsets, 
        long x_inc, 
        cl_mem y_buffer, 
        long[] y_offsets, 
        long y_inc, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDaxpyBatchedNative(n, alphas, x_buffer, x_offsets, x_inc, y_buffer, y_offsets, y_inc, batch_count, queue, event));
    }
    private static native int CLBlastDaxpyBatchedNative(
        long n, 
        double[] alphas, 
        cl_mem x_buffer, 
        long[] x_offsets, 
        long x_inc, 
        cl_mem y_buffer, 
        long[] y_offsets, 
        long y_inc, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCaxpyBatched(
        long n, 
        float[] alphas, 
        cl_mem x_buffer, 
        long[] x_offsets, 
        long x_inc, 
        cl_mem y_buffer, 
        long[] y_offsets, 
        long y_inc, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCaxpyBatchedNative(n, alphas, x_buffer, x_offsets, x_inc, y_buffer, y_offsets, y_inc, batch_count, queue, event));
    }
    private static native int CLBlastCaxpyBatchedNative(
        long n, 
        float[] alphas, 
        cl_mem x_buffer, 
        long[] x_offsets, 
        long x_inc, 
        cl_mem y_buffer, 
        long[] y_offsets, 
        long y_inc, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZaxpyBatched(
        long n, 
        double[] alphas, 
        cl_mem x_buffer, 
        long[] x_offsets, 
        long x_inc, 
        cl_mem y_buffer, 
        long[] y_offsets, 
        long y_inc, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZaxpyBatchedNative(n, alphas, x_buffer, x_offsets, x_inc, y_buffer, y_offsets, y_inc, batch_count, queue, event));
    }
    private static native int CLBlastZaxpyBatchedNative(
        long n, 
        double[] alphas, 
        cl_mem x_buffer, 
        long[] x_offsets, 
        long x_inc, 
        cl_mem y_buffer, 
        long[] y_offsets, 
        long y_inc, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event);


    // Batched version of GEMM: SGEMMBATCHED/DGEMMBATCHED/CGEMMBATCHED/ZGEMMBATCHED/HGEMMBATCHED
    public static int CLBlastSgemmBatched(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        float[] alphas, 
        cl_mem a_buffer, 
        long[] a_offsets, 
        long a_ld, 
        cl_mem b_buffer, 
        long[] b_offsets, 
        long b_ld, 
        float[] betas, 
        cl_mem c_buffer, 
        long[] c_offsets, 
        long c_ld, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastSgemmBatchedNative(layout, a_transpose, b_transpose, m, n, k, alphas, a_buffer, a_offsets, a_ld, b_buffer, b_offsets, b_ld, betas, c_buffer, c_offsets, c_ld, batch_count, queue, event));
    }
    private static native int CLBlastSgemmBatchedNative(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        float[] alphas, 
        cl_mem a_buffer, 
        long[] a_offsets, 
        long a_ld, 
        cl_mem b_buffer, 
        long[] b_offsets, 
        long b_ld, 
        float[] betas, 
        cl_mem c_buffer, 
        long[] c_offsets, 
        long c_ld, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastDgemmBatched(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        double[] alphas, 
        cl_mem a_buffer, 
        long[] a_offsets, 
        long a_ld, 
        cl_mem b_buffer, 
        long[] b_offsets, 
        long b_ld, 
        double[] betas, 
        cl_mem c_buffer, 
        long[] c_offsets, 
        long c_ld, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastDgemmBatchedNative(layout, a_transpose, b_transpose, m, n, k, alphas, a_buffer, a_offsets, a_ld, b_buffer, b_offsets, b_ld, betas, c_buffer, c_offsets, c_ld, batch_count, queue, event));
    }
    private static native int CLBlastDgemmBatchedNative(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        double[] alphas, 
        cl_mem a_buffer, 
        long[] a_offsets, 
        long a_ld, 
        cl_mem b_buffer, 
        long[] b_offsets, 
        long b_ld, 
        double[] betas, 
        cl_mem c_buffer, 
        long[] c_offsets, 
        long c_ld, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastCgemmBatched(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        float[] alphas, 
        cl_mem a_buffer, 
        long[] a_offsets, 
        long a_ld, 
        cl_mem b_buffer, 
        long[] b_offsets, 
        long b_ld, 
        float[] betas, 
        cl_mem c_buffer, 
        long[] c_offsets, 
        long c_ld, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastCgemmBatchedNative(layout, a_transpose, b_transpose, m, n, k, alphas, a_buffer, a_offsets, a_ld, b_buffer, b_offsets, b_ld, betas, c_buffer, c_offsets, c_ld, batch_count, queue, event));
    }
    private static native int CLBlastCgemmBatchedNative(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        float[] alphas, 
        cl_mem a_buffer, 
        long[] a_offsets, 
        long a_ld, 
        cl_mem b_buffer, 
        long[] b_offsets, 
        long b_ld, 
        float[] betas, 
        cl_mem c_buffer, 
        long[] c_offsets, 
        long c_ld, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event);


    public static int CLBlastZgemmBatched(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        double[] alphas, 
        cl_mem a_buffer, 
        long[] a_offsets, 
        long a_ld, 
        cl_mem b_buffer, 
        long[] b_offsets, 
        long b_ld, 
        double[] betas, 
        cl_mem c_buffer, 
        long[] c_offsets, 
        long c_ld, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event)
    {
        return checkResult(CLBlastZgemmBatchedNative(layout, a_transpose, b_transpose, m, n, k, alphas, a_buffer, a_offsets, a_ld, b_buffer, b_offsets, b_ld, betas, c_buffer, c_offsets, c_ld, batch_count, queue, event));
    }
    private static native int CLBlastZgemmBatchedNative(
        int layout, 
        int a_transpose, 
        int b_transpose, 
        long m, 
        long n, 
        long k, 
        double[] alphas, 
        cl_mem a_buffer, 
        long[] a_offsets, 
        long a_ld, 
        cl_mem b_buffer, 
        long[] b_offsets, 
        long b_ld, 
        double[] betas, 
        cl_mem c_buffer, 
        long[] c_offsets, 
        long c_ld, 
        long batch_count, 
        cl_command_queue queue, 
        cl_event event);


    // =================================================================================================
    // CLBlast stores binaries of compiled kernels into a cache in case the same kernel is used later on
    // for the same device. This cache can be cleared to free up system memory or in case of debugging.
    public static int CLBlastClearCache()
    {
        return checkResult(CLBlastClearCacheNative());
    }
    private static native int CLBlastClearCacheNative();


    // The cache can also be pre-initialized for a specific device with all possible CLBLast kernels.
    // Further CLBlast routine calls will then run at maximum speed.
    public static int CLBlastFillCache(
        cl_device_id device)
    {
        return checkResult(CLBlastFillCacheNative(device));
    }
    private static native int CLBlastFillCacheNative(
        cl_device_id device);


    // =================================================================================================
    // Overrides tuning parameters for a specific device-precision-kernel combination. The next time
    // the target routine is called it will re-compile and use the new parameters from then on.
    public static int CLBlastOverrideParameters(
        cl_device_id device, 
        String kernel_name, 
        int precision, 
        long num_parameters, 
        String[] parameters_names, 
        long[] parameters_values)
    {
        return checkResult(CLBlastOverrideParametersNative(device, kernel_name, precision, num_parameters, parameters_names, parameters_values));
    }
    private static native int CLBlastOverrideParametersNative(
        cl_device_id device, 
        String kernel_name, 
        int precision, 
        long num_parameters, 
        String[] parameters_names, 
        long[] parameters_values);


    /**
     * Private constructor to prevent instantiation
     */
    private CLBlast()
    {
        // Private constructor to prevent instantiation
    }
}


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

#include "JOCLBlast.hpp"

#define JOCL_BLAST_STATUS_INTERNAL_ERROR -32786;

#include <string.h>
#include <string>
#include <map>

#include "Logger.hpp"
#include "JOCLCommon.hpp"
#include "JNIUtils.hpp"
#include "PointerUtils.hpp"
#include "CLJNIUtils.hpp"
#include "ConversionsCL.hpp"
#include <clblast_c.h>


/**
* Called when the library is loaded. Will initialize all
* required global class references, field and method IDs
*/
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
{
    JNIEnv *env = NULL;
    if (jvm->GetEnv((void**)&env, JNI_VERSION_1_4))
    {
        return JNI_ERR;
    }

    Logger::log(LOG_TRACE, "Initializing JOCLBlast\n");

    // Initialize the utility methods
    if (initJNIUtils(env) == JNI_ERR) return JNI_ERR;
    if (initCLJNIUtils(env) == JNI_ERR) return JNI_ERR;
    if (initPointerUtils(env) == JNI_ERR) return JNI_ERR;

    // Obtain the global class references and the constructor methodIDs
    // for classes which will have to be instantiated
    if (!init(env, "org/jocl/cl_mem", cl_mem_Class, cl_mem_Constructor)) return JNI_ERR;

    return JNI_VERSION_1_4;
}

/**
* Called when the library is unloaded.
*/
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved)
{
    // Nothing to do here
}


/*
* Class:     org_jocl_blast_CLBlast
* Method:    setLogLevelNative
* Signature: (I)V
*/
JNIEXPORT void JNICALL Java_org_jocl_blast_CLBlast_setLogLevelNative
(JNIEnv *env, jclass UNUSED(cls), jint logLevel)
{
	Logger::setLogLevel((LogLevel)logLevel);
}




// =================================================================================================
// BLAS level-1 (vector-vector) routines
// =================================================================================================
// Swap two vectors: SSWAP/DSWAP/CSWAP/ZSWAP
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSswapNative(JNIEnv *env, jclass cls, jlong n, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastSswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSswap(n=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSswap(n_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDswapNative(JNIEnv *env, jclass cls, jlong n, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDswap(n=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDswap(n_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCswapNative(JNIEnv *env, jclass cls, jlong n, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastCswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCswap(n=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCswap(n_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZswapNative(JNIEnv *env, jclass cls, jlong n, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZswap");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZswap(n=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZswap(n_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Vector scaling: SSCAL/DSCAL/CSCAL/ZSCAL
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSscalNative(JNIEnv *env, jclass cls, jlong n, jfloat alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSscal");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSscal");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSscal(n=%ld, alpha=%f, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		n, alpha, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSscal(n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDscalNative(JNIEnv *env, jclass cls, jlong n, jdouble alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDscal");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDscal");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDscal(n=%ld, alpha=%lf, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		n, alpha, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDscal(n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCscalNative(JNIEnv *env, jclass cls, jlong n, jfloatArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCscal");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCscal");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCscal");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCscal(n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		n, alpha, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCscal(n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZscalNative(JNIEnv *env, jclass cls, jlong n, jdoubleArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZscal");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZscal");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZscal");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZscal(n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		n, alpha, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZscal(n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Vector copy: SCOPY/DCOPY/CCOPY/ZCOPY
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastScopyNative(JNIEnv *env, jclass cls, jlong n, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastScopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastScopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastScopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastScopy(n=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastScopy(n_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDcopyNative(JNIEnv *env, jclass cls, jlong n, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDcopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDcopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDcopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDcopy(n=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDcopy(n_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCcopyNative(JNIEnv *env, jclass cls, jlong n, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCcopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastCcopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCcopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCcopy(n=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCcopy(n_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZcopyNative(JNIEnv *env, jclass cls, jlong n, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZcopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZcopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZcopy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZcopy(n=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZcopy(n_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Vector-times-constant plus vector: SAXPY/DAXPY/CAXPY/ZAXPY
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSaxpyNative(JNIEnv *env, jclass cls, jlong n, jfloat alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastSaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSaxpy(n=%ld, alpha=%f, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSaxpy(n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDaxpyNative(JNIEnv *env, jclass cls, jlong n, jdouble alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDaxpy(n=%ld, alpha=%lf, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDaxpy(n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCaxpyNative(JNIEnv *env, jclass cls, jlong n, jfloatArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastCaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCaxpy(n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCaxpy(n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZaxpyNative(JNIEnv *env, jclass cls, jlong n, jdoubleArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZaxpy");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZaxpy(n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZaxpy(n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Dot product of two vectors: SDOT/DDOT
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSdotNative(JNIEnv *env, jclass cls, jlong n, jobject dot_buffer, jlong dot_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (dot_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'dot_buffer' is null for CLBlastSdot");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// dot_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSdot");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastSdot");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSdot");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSdot(n=%ld, dot_buffer=%p, dot_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem dot_buffer_native = nullptr;
	size_t dot_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, dot_buffer, dot_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	dot_offset_native = (size_t)dot_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSdot(n_native, dot_buffer_native, dot_offset_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// dot_buffer is a read-only native pointer
	// dot_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDdotNative(JNIEnv *env, jclass cls, jlong n, jobject dot_buffer, jlong dot_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (dot_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'dot_buffer' is null for CLBlastDdot");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// dot_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDdot");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDdot");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDdot");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDdot(n=%ld, dot_buffer=%p, dot_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem dot_buffer_native = nullptr;
	size_t dot_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, dot_buffer, dot_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	dot_offset_native = (size_t)dot_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDdot(n_native, dot_buffer_native, dot_offset_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// dot_buffer is a read-only native pointer
	// dot_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Dot product of two complex vectors: CDOTU/ZDOTU
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCdotuNative(JNIEnv *env, jclass cls, jlong n, jobject dot_buffer, jlong dot_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (dot_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'dot_buffer' is null for CLBlastCdotu");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// dot_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCdotu");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastCdotu");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCdotu");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCdotu(n=%ld, dot_buffer=%p, dot_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem dot_buffer_native = nullptr;
	size_t dot_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, dot_buffer, dot_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	dot_offset_native = (size_t)dot_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCdotu(n_native, dot_buffer_native, dot_offset_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// dot_buffer is a read-only native pointer
	// dot_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZdotuNative(JNIEnv *env, jclass cls, jlong n, jobject dot_buffer, jlong dot_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (dot_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'dot_buffer' is null for CLBlastZdotu");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// dot_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZdotu");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZdotu");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZdotu");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZdotu(n=%ld, dot_buffer=%p, dot_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem dot_buffer_native = nullptr;
	size_t dot_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, dot_buffer, dot_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	dot_offset_native = (size_t)dot_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZdotu(n_native, dot_buffer_native, dot_offset_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// dot_buffer is a read-only native pointer
	// dot_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Dot product of two complex vectors, one conjugated: CDOTC/ZDOTC
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCdotcNative(JNIEnv *env, jclass cls, jlong n, jobject dot_buffer, jlong dot_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (dot_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'dot_buffer' is null for CLBlastCdotc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// dot_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCdotc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastCdotc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCdotc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCdotc(n=%ld, dot_buffer=%p, dot_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem dot_buffer_native = nullptr;
	size_t dot_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, dot_buffer, dot_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	dot_offset_native = (size_t)dot_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCdotc(n_native, dot_buffer_native, dot_offset_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// dot_buffer is a read-only native pointer
	// dot_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZdotcNative(JNIEnv *env, jclass cls, jlong n, jobject dot_buffer, jlong dot_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// n is primitive
	if (dot_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'dot_buffer' is null for CLBlastZdotc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// dot_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZdotc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZdotc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZdotc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZdotc(n=%ld, dot_buffer=%p, dot_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		n, dot_buffer, dot_offset, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	size_t n_native = 0;
	cl_mem dot_buffer_native = nullptr;
	size_t dot_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	n_native = (size_t)n;
	if (!initNative(env, dot_buffer, dot_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	dot_offset_native = (size_t)dot_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZdotc(n_native, dot_buffer_native, dot_offset_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// n is primitive
	// dot_buffer is a read-only native pointer
	// dot_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// =================================================================================================
// BLAS level-2 (matrix-vector) routines
// =================================================================================================
// General matrix-vector multiplication: SGEMV/DGEMV/CGEMV/ZGEMV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSgemvNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jlong m, jlong n, jfloat alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jfloat beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastSgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastSgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSgemv(layout=%d, a_transpose=%d, m=%ld, n=%ld, alpha=%f, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%f, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	float beta_native = 0.0f;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	beta_native = (float)beta;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSgemv(layout_native, a_transpose_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDgemvNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jlong m, jlong n, jdouble alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jdouble beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDgemv(layout=%d, a_transpose=%d, m=%ld, n=%ld, alpha=%lf, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%lf, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	double beta_native = 0.0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	beta_native = (double)beta;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDgemv(layout_native, a_transpose_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCgemvNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jlong m, jlong n, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jfloatArray beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastCgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastCgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCgemv(layout=%d, a_transpose=%d, m=%ld, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%p, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_float2 beta_native;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCgemv(layout_native, a_transpose_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZgemvNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jlong m, jlong n, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jdoubleArray beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastZgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZgemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZgemv(layout=%d, a_transpose=%d, m=%ld, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%p, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, m, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_double2 beta_native;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZgemv(layout_native, a_transpose_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// General banded matrix-vector multiplication: SGBMV/DGBMV/CGBMV/ZGBMV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSgbmvNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jlong m, jlong n, jlong kl, jlong ku, jfloat alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jfloat beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// kl is primitive
	// ku is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastSgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastSgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSgbmv(layout=%d, a_transpose=%d, m=%ld, n=%ld, kl=%ld, ku=%ld, alpha=%f, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%f, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, m, n, kl, ku, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	size_t kl_native = 0;
	size_t ku_native = 0;
	float alpha_native = 0.0f;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	float beta_native = 0.0f;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	kl_native = (size_t)kl;
	ku_native = (size_t)ku;
	alpha_native = (float)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	beta_native = (float)beta;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSgbmv(layout_native, a_transpose_native, m_native, n_native, kl_native, ku_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// kl is primitive
	// ku is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDgbmvNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jlong m, jlong n, jlong kl, jlong ku, jdouble alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jdouble beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// kl is primitive
	// ku is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDgbmv(layout=%d, a_transpose=%d, m=%ld, n=%ld, kl=%ld, ku=%ld, alpha=%lf, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%lf, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, m, n, kl, ku, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	size_t kl_native = 0;
	size_t ku_native = 0;
	double alpha_native = 0.0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	double beta_native = 0.0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	kl_native = (size_t)kl;
	ku_native = (size_t)ku;
	alpha_native = (double)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	beta_native = (double)beta;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDgbmv(layout_native, a_transpose_native, m_native, n_native, kl_native, ku_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// kl is primitive
	// ku is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCgbmvNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jlong m, jlong n, jlong kl, jlong ku, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jfloatArray beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// kl is primitive
	// ku is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastCgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastCgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCgbmv(layout=%d, a_transpose=%d, m=%ld, n=%ld, kl=%ld, ku=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%p, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, m, n, kl, ku, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	size_t kl_native = 0;
	size_t ku_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_float2 beta_native;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	kl_native = (size_t)kl;
	ku_native = (size_t)ku;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCgbmv(layout_native, a_transpose_native, m_native, n_native, kl_native, ku_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// kl is primitive
	// ku is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZgbmvNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jlong m, jlong n, jlong kl, jlong ku, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jdoubleArray beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// kl is primitive
	// ku is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastZgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZgbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZgbmv(layout=%d, a_transpose=%d, m=%ld, n=%ld, kl=%ld, ku=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%p, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, m, n, kl, ku, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	size_t kl_native = 0;
	size_t ku_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_double2 beta_native;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	kl_native = (size_t)kl;
	ku_native = (size_t)ku;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZgbmv(layout_native, a_transpose_native, m_native, n_native, kl_native, ku_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// m is primitive
	// n is primitive
	// kl is primitive
	// ku is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Hermitian matrix-vector multiplication: CHEMV/ZHEMV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastChemvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jfloatArray beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastChemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastChemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastChemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastChemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastChemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastChemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastChemv(layout=%d, triangle=%d, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%p, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_float2 beta_native;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastChemv(layout_native, triangle_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZhemvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jdoubleArray beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZhemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZhemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZhemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastZhemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZhemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZhemv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZhemv(layout=%d, triangle=%d, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%p, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_double2 beta_native;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZhemv(layout_native, triangle_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Hermitian banded matrix-vector multiplication: CHBMV/ZHBMV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastChbmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jlong k, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jfloatArray beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// k is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastChbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastChbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastChbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastChbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastChbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastChbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastChbmv(layout=%d, triangle=%d, n=%ld, k=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%p, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, k, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_float2 beta_native;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastChbmv(layout_native, triangle_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// k is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZhbmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jlong k, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jdoubleArray beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// k is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZhbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZhbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZhbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastZhbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZhbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZhbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZhbmv(layout=%d, triangle=%d, n=%ld, k=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%p, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, k, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_double2 beta_native;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZhbmv(layout_native, triangle_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// k is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Hermitian packed matrix-vector multiplication: CHPMV/ZHPMV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastChpmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloatArray alpha, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jfloatArray beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastChpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastChpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastChpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastChpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastChpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastChpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastChpmv(layout=%d, triangle=%d, n=%ld, alpha=%p, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%p, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_float2 beta_native;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastChpmv(layout_native, triangle_native, n_native, alpha_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZhpmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdoubleArray alpha, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jdoubleArray beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZhpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastZhpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZhpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastZhpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZhpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZhpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZhpmv(layout=%d, triangle=%d, n=%ld, alpha=%p, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%p, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_double2 beta_native;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZhpmv(layout_native, triangle_native, n_native, alpha_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Symmetric matrix-vector multiplication: SSYMV/DSYMV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSsymvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloat alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jfloat beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastSsymv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSsymv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastSsymv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSsymv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSsymv(layout=%d, triangle=%d, n=%ld, alpha=%f, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%f, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	float beta_native = 0.0f;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	beta_native = (float)beta;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSsymv(layout_native, triangle_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDsymvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdouble alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jdouble beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDsymv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDsymv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDsymv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDsymv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDsymv(layout=%d, triangle=%d, n=%ld, alpha=%lf, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%lf, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	double beta_native = 0.0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	beta_native = (double)beta;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDsymv(layout_native, triangle_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Symmetric banded matrix-vector multiplication: SSBMV/DSBMV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSsbmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jlong k, jfloat alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jfloat beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastSsbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSsbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastSsbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSsbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSsbmv(layout=%d, triangle=%d, n=%ld, k=%ld, alpha=%f, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%f, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, k, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	size_t k_native = 0;
	float alpha_native = 0.0f;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	float beta_native = 0.0f;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	k_native = (size_t)k;
	alpha_native = (float)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	beta_native = (float)beta;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSsbmv(layout_native, triangle_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDsbmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jlong k, jdouble alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jdouble beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDsbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDsbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDsbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDsbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDsbmv(layout=%d, triangle=%d, n=%ld, k=%ld, alpha=%lf, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%lf, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, k, alpha, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	size_t k_native = 0;
	double alpha_native = 0.0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	double beta_native = 0.0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	k_native = (size_t)k;
	alpha_native = (double)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	beta_native = (double)beta;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDsbmv(layout_native, triangle_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Symmetric packed matrix-vector multiplication: SSPMV/DSPMV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSspmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloat alpha, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jfloat beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastSspmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSspmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastSspmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSspmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSspmv(layout=%d, triangle=%d, n=%ld, alpha=%f, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%f, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	float beta_native = 0.0f;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	beta_native = (float)beta;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSspmv(layout_native, triangle_native, n_native, alpha_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDspmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdouble alpha, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jdouble beta, jobject y_buffer, jlong y_offset, jlong y_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastDspmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDspmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDspmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDspmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDspmv(layout=%d, triangle=%d, n=%ld, alpha=%lf, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, beta=%lf, y_buffer=%p, y_offset=%ld, y_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, beta, y_buffer, y_offset, y_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	double beta_native = 0.0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	beta_native = (double)beta;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDspmv(layout_native, triangle_native, n_native, alpha_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, beta_native, y_buffer_native, y_offset_native, y_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// beta is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Triangular matrix-vector multiplication: STRMV/DTRMV/CTRMV/ZTRMV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastStrmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastStrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastStrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastStrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastStrmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastStrmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDtrmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDtrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDtrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDtrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDtrmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDtrmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCtrmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCtrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCtrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCtrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCtrmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCtrmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZtrmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZtrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZtrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZtrmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZtrmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZtrmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Triangular banded matrix-vector multiplication: STBMV/DTBMV/CTBMV/ZTBMV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastStbmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jlong k, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastStbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastStbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastStbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastStbmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, k=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastStbmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, k_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDtbmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jlong k, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDtbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDtbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDtbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDtbmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, k=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDtbmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, k_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCtbmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jlong k, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCtbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCtbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCtbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCtbmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, k=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCtbmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, k_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZtbmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jlong k, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZtbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZtbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZtbmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZtbmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, k=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZtbmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, k_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Triangular packed matrix-vector multiplication: STPMV/DTPMV/CTPMV/ZTPMV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastStpmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastStpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastStpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastStpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastStpmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastStpmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDtpmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastDtpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDtpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDtpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDtpmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDtpmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCtpmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastCtpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCtpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCtpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCtpmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCtpmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZtpmvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastZtpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZtpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZtpmv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZtpmv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZtpmv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Solves a triangular system of equations: STRSV/DTRSV/CTRSV/ZTRSV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastStrsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastStrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastStrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastStrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastStrsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastStrsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDtrsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDtrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDtrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDtrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDtrsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDtrsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCtrsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCtrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCtrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCtrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCtrsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCtrsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZtrsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZtrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZtrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZtrsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZtrsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZtrsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Solves a banded triangular system of equations: STBSV/DTBSV/CTBSV/ZTBSV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastStbsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jlong k, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastStbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastStbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastStbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastStbsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, k=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastStbsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, k_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDtbsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jlong k, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDtbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDtbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDtbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDtbsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, k=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDtbsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, k_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCtbsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jlong k, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCtbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCtbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCtbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCtbsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, k=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCtbsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, k_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZtbsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jlong k, jobject a_buffer, jlong a_offset, jlong a_ld, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZtbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZtbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZtbsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZtbsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, k=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, k, a_buffer, a_offset, a_ld, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZtbsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, k_native, a_buffer_native, a_offset_native, a_ld_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// k is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Solves a packed triangular system of equations: STPSV/DTPSV/CTPSV/ZTPSV
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastStpsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastStpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastStpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastStpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastStpsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastStpsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDtpsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastDtpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDtpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDtpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDtpsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDtpsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCtpsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastCtpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCtpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCtpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCtpsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCtpsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZtpsvNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jint diagonal, jlong n, jobject ap_buffer, jlong ap_offset, jobject x_buffer, jlong x_offset, jlong x_inc, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastZtpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZtpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZtpsv");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZtpsv(layout=%d, triangle=%d, a_transpose=%d, diagonal=%d, n=%ld, ap_buffer=%p, ap_offset=%ld, x_buffer=%p, x_offset=%ld, x_inc=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, diagonal, n, ap_buffer, ap_offset, x_buffer, x_offset, x_inc, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t n_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	n_native = (size_t)n;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZtpsv(layout_native, triangle_native, a_transpose_native, diagonal_native, n_native, ap_buffer_native, ap_offset_native, x_buffer_native, x_offset_native, x_inc_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// n is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// General rank-1 matrix update: SGER/DGER
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSgerNative(JNIEnv *env, jclass cls, jint layout, jlong m, jlong n, jfloat alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSger");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastSger");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastSger");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSger");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSger(layout=%d, m=%ld, n=%ld, alpha=%f, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	size_t m_native = 0;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	m_native = (size_t)m;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSger(layout_native, m_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDgerNative(JNIEnv *env, jclass cls, jint layout, jlong m, jlong n, jdouble alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDger");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDger");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDger");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDger");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDger(layout=%d, m=%ld, n=%ld, alpha=%lf, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	size_t m_native = 0;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	m_native = (size_t)m;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDger(layout_native, m_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// General rank-1 complex matrix update: CGERU/ZGERU
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCgeruNative(JNIEnv *env, jclass cls, jint layout, jlong m, jlong n, jfloatArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCgeru");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCgeru");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastCgeru");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCgeru");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCgeru");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCgeru(layout=%d, m=%ld, n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCgeru(layout_native, m_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZgeruNative(JNIEnv *env, jclass cls, jint layout, jlong m, jlong n, jdoubleArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZgeru");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZgeru");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZgeru");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZgeru");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZgeru");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZgeru(layout=%d, m=%ld, n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZgeru(layout_native, m_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// General rank-1 complex conjugated matrix update: CGERC/ZGERC
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCgercNative(JNIEnv *env, jclass cls, jint layout, jlong m, jlong n, jfloatArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCgerc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCgerc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastCgerc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCgerc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCgerc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCgerc(layout=%d, m=%ld, n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCgerc(layout_native, m_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZgercNative(JNIEnv *env, jclass cls, jint layout, jlong m, jlong n, jdoubleArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZgerc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZgerc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZgerc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZgerc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZgerc");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZgerc(layout=%d, m=%ld, n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, m, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZgerc(layout_native, m_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Hermitian rank-1 matrix update: CHER/ZHER
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCherNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloat alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCher");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCher");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCher");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCher(layout=%d, triangle=%d, n=%ld, alpha=%f, x_buffer=%p, x_offset=%ld, x_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCher(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZherNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdouble alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZher");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZher");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZher");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZher(layout=%d, triangle=%d, n=%ld, alpha=%lf, x_buffer=%p, x_offset=%ld, x_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZher(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Hermitian packed rank-1 matrix update: CHPR/ZHPR
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastChprNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloat alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject ap_buffer, jlong ap_offset, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastChpr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastChpr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastChpr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastChpr(layout=%d, triangle=%d, n=%ld, alpha=%f, x_buffer=%p, x_offset=%ld, x_inc=%ld, ap_buffer=%p, ap_offset=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, ap_buffer, ap_offset, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastChpr(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, ap_buffer_native, ap_offset_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZhprNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdouble alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject ap_buffer, jlong ap_offset, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZhpr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastZhpr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZhpr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZhpr(layout=%d, triangle=%d, n=%ld, alpha=%lf, x_buffer=%p, x_offset=%ld, x_inc=%ld, ap_buffer=%p, ap_offset=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, ap_buffer, ap_offset, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZhpr(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, ap_buffer_native, ap_offset_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Hermitian rank-2 matrix update: CHER2/ZHER2
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCher2Native(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloatArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCher2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastCher2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastCher2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCher2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCher2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCher2(layout=%d, triangle=%d, n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCher2(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZher2Native(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdoubleArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZher2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZher2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZher2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZher2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZher2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZher2(layout=%d, triangle=%d, n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZher2(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Hermitian packed rank-2 matrix update: CHPR2/ZHPR2
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastChpr2Native(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloatArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject ap_buffer, jlong ap_offset, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastChpr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastChpr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastChpr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastChpr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastChpr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastChpr2(layout=%d, triangle=%d, n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, ap_buffer=%p, ap_offset=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, ap_buffer, ap_offset, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastChpr2(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, ap_buffer_native, ap_offset_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZhpr2Native(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdoubleArray alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject ap_buffer, jlong ap_offset, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZhpr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastZhpr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastZhpr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastZhpr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZhpr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZhpr2(layout=%d, triangle=%d, n=%ld, alpha=%p, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, ap_buffer=%p, ap_offset=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, ap_buffer, ap_offset, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZhpr2(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, ap_buffer_native, ap_offset_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Symmetric rank-1 matrix update: SSYR/DSYR
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSsyrNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloat alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSsyr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastSsyr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSsyr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSsyr(layout=%d, triangle=%d, n=%ld, alpha=%f, x_buffer=%p, x_offset=%ld, x_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSsyr(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDsyrNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdouble alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDsyr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDsyr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDsyr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDsyr(layout=%d, triangle=%d, n=%ld, alpha=%lf, x_buffer=%p, x_offset=%ld, x_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDsyr(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Symmetric packed rank-1 matrix update: SSPR/DSPR
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSsprNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloat alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject ap_buffer, jlong ap_offset, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSspr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastSspr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSspr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSspr(layout=%d, triangle=%d, n=%ld, alpha=%f, x_buffer=%p, x_offset=%ld, x_inc=%ld, ap_buffer=%p, ap_offset=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, ap_buffer, ap_offset, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSspr(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, ap_buffer_native, ap_offset_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDsprNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdouble alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject ap_buffer, jlong ap_offset, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDspr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastDspr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDspr");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDspr(layout=%d, triangle=%d, n=%ld, alpha=%lf, x_buffer=%p, x_offset=%ld, x_inc=%ld, ap_buffer=%p, ap_offset=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, ap_buffer, ap_offset, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDspr(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, ap_buffer_native, ap_offset_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Symmetric rank-2 matrix update: SSYR2/DSYR2
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSsyr2Native(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloat alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSsyr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastSsyr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastSsyr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSsyr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSsyr2(layout=%d, triangle=%d, n=%ld, alpha=%f, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSsyr2(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDsyr2Native(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdouble alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject a_buffer, jlong a_offset, jlong a_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDsyr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDsyr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDsyr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDsyr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDsyr2(layout=%d, triangle=%d, n=%ld, alpha=%lf, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, a_buffer=%p, a_offset=%ld, a_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, a_buffer, a_offset, a_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDsyr2(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, a_buffer_native, a_offset_native, a_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Symmetric packed rank-2 matrix update: SSPR2/DSPR2
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSspr2Native(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jfloat alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject ap_buffer, jlong ap_offset, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastSspr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastSspr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastSspr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSspr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSspr2(layout=%d, triangle=%d, n=%ld, alpha=%f, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, ap_buffer=%p, ap_offset=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, ap_buffer, ap_offset, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSspr2(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, ap_buffer_native, ap_offset_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDspr2Native(JNIEnv *env, jclass cls, jint layout, jint triangle, jlong n, jdouble alpha, jobject x_buffer, jlong x_offset, jlong x_inc, jobject y_buffer, jlong y_offset, jlong y_inc, jobject ap_buffer, jlong ap_offset, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	if (x_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'x_buffer' is null for CLBlastDspr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// x_offset is primitive
	// x_inc is primitive
	if (y_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'y_buffer' is null for CLBlastDspr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// y_offset is primitive
	// y_inc is primitive
	if (ap_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'ap_buffer' is null for CLBlastDspr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// ap_offset is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDspr2");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDspr2(layout=%d, triangle=%d, n=%ld, alpha=%lf, x_buffer=%p, x_offset=%ld, x_inc=%ld, y_buffer=%p, y_offset=%ld, y_inc=%ld, ap_buffer=%p, ap_offset=%ld, queue=%p, event=%p)\n",
		layout, triangle, n, alpha, x_buffer, x_offset, x_inc, y_buffer, y_offset, y_inc, ap_buffer, ap_offset, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem x_buffer_native = nullptr;
	size_t x_offset_native = 0;
	size_t x_inc_native = 0;
	cl_mem y_buffer_native = nullptr;
	size_t y_offset_native = 0;
	size_t y_inc_native = 0;
	cl_mem ap_buffer_native = nullptr;
	size_t ap_offset_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, x_buffer, x_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	x_offset_native = (size_t)x_offset;
	x_inc_native = (size_t)x_inc;
	if (!initNative(env, y_buffer, y_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	y_offset_native = (size_t)y_offset;
	y_inc_native = (size_t)y_inc;
	if (!initNative(env, ap_buffer, ap_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	ap_offset_native = (size_t)ap_offset;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDspr2(layout_native, triangle_native, n_native, alpha_native, x_buffer_native, x_offset_native, x_inc_native, y_buffer_native, y_offset_native, y_inc_native, ap_buffer_native, ap_offset_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// n is primitive
	// alpha is primitive
	// x_buffer is a read-only native pointer
	// x_offset is primitive
	// x_inc is primitive
	// y_buffer is a read-only native pointer
	// y_offset is primitive
	// y_inc is primitive
	// ap_buffer is a read-only native pointer
	// ap_offset is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// =================================================================================================
// BLAS level-3 (matrix-matrix) routines
// =================================================================================================
// General matrix-matrix multiplication: SGEMM/DGEMM/CGEMM/ZGEMM
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSgemmNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jint b_transpose, jlong m, jlong n, jlong k, jfloat alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jfloat beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// b_transpose is primitive
	// m is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastSgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastSgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastSgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSgemm(layout=%d, a_transpose=%d, b_transpose=%d, m=%ld, n=%ld, k=%ld, alpha=%f, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%f, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, b_transpose, m, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	Transpose b_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	size_t k_native = 0;
	float alpha_native = 0.0f;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	float beta_native = 0.0f;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	b_transpose_native = (Transpose)b_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	k_native = (size_t)k;
	alpha_native = (float)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	beta_native = (float)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSgemm(layout_native, a_transpose_native, b_transpose_native, m_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// b_transpose is primitive
	// m is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDgemmNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jint b_transpose, jlong m, jlong n, jlong k, jdouble alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jdouble beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// b_transpose is primitive
	// m is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastDgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastDgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDgemm(layout=%d, a_transpose=%d, b_transpose=%d, m=%ld, n=%ld, k=%ld, alpha=%lf, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%lf, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, b_transpose, m, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	Transpose b_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	size_t k_native = 0;
	double alpha_native = 0.0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	double beta_native = 0.0;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	b_transpose_native = (Transpose)b_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	k_native = (size_t)k;
	alpha_native = (double)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	beta_native = (double)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDgemm(layout_native, a_transpose_native, b_transpose_native, m_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// b_transpose is primitive
	// m is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCgemmNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jint b_transpose, jlong m, jlong n, jlong k, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jfloatArray beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// b_transpose is primitive
	// m is primitive
	// n is primitive
	// k is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastCgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastCgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastCgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCgemm(layout=%d, a_transpose=%d, b_transpose=%d, m=%ld, n=%ld, k=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%p, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, b_transpose, m, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	Transpose b_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_float2 beta_native;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	b_transpose_native = (Transpose)b_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCgemm(layout_native, a_transpose_native, b_transpose_native, m_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// b_transpose is primitive
	// m is primitive
	// n is primitive
	// k is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZgemmNative(JNIEnv *env, jclass cls, jint layout, jint a_transpose, jint b_transpose, jlong m, jlong n, jlong k, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jdoubleArray beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// a_transpose is primitive
	// b_transpose is primitive
	// m is primitive
	// n is primitive
	// k is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastZgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastZgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastZgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZgemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZgemm(layout=%d, a_transpose=%d, b_transpose=%d, m=%ld, n=%ld, k=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%p, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, a_transpose, b_transpose, m, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Transpose a_transpose_native;
	Transpose b_transpose_native;
	size_t m_native = 0;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_double2 beta_native;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	a_transpose_native = (Transpose)a_transpose;
	b_transpose_native = (Transpose)b_transpose;
	m_native = (size_t)m;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZgemm(layout_native, a_transpose_native, b_transpose_native, m_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// a_transpose is primitive
	// b_transpose is primitive
	// m is primitive
	// n is primitive
	// k is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Symmetric matrix-matrix multiplication: SSYMM/DSYMM/CSYMM/ZSYMM
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSsymmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jlong m, jlong n, jfloat alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jfloat beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastSsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastSsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastSsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSsymm(layout=%d, side=%d, triangle=%d, m=%ld, n=%ld, alpha=%f, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%f, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	size_t m_native = 0;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	float beta_native = 0.0f;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	m_native = (size_t)m;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	beta_native = (float)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSsymm(layout_native, side_native, triangle_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDsymmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jlong m, jlong n, jdouble alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jdouble beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastDsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastDsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDsymm(layout=%d, side=%d, triangle=%d, m=%ld, n=%ld, alpha=%lf, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%lf, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	size_t m_native = 0;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	double beta_native = 0.0;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	m_native = (size_t)m;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	beta_native = (double)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDsymm(layout_native, side_native, triangle_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCsymmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jlong m, jlong n, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jfloatArray beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastCsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastCsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastCsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCsymm(layout=%d, side=%d, triangle=%d, m=%ld, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%p, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_float2 beta_native;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCsymm(layout_native, side_native, triangle_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZsymmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jlong m, jlong n, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jdoubleArray beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastZsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastZsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastZsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZsymm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZsymm(layout=%d, side=%d, triangle=%d, m=%ld, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%p, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_double2 beta_native;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZsymm(layout_native, side_native, triangle_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Hermitian matrix-matrix multiplication: CHEMM/ZHEMM
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastChemmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jlong m, jlong n, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jfloatArray beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastChemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastChemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastChemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastChemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastChemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastChemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastChemm(layout=%d, side=%d, triangle=%d, m=%ld, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%p, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_float2 beta_native;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastChemm(layout_native, side_native, triangle_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZhemmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jlong m, jlong n, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jdoubleArray beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZhemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZhemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastZhemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastZhemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastZhemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZhemm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZhemm(layout=%d, side=%d, triangle=%d, m=%ld, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%p, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_double2 beta_native;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZhemm(layout_native, side_native, triangle_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Rank-K update of a symmetric matrix: SSYRK/DSYRK/CSYRK/ZSYRK
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSsyrkNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jlong n, jlong k, jfloat alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jfloat beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastSsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastSsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSsyrk(layout=%d, triangle=%d, a_transpose=%d, n=%ld, k=%ld, alpha=%f, a_buffer=%p, a_offset=%ld, a_ld=%ld, beta=%f, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	float alpha_native = 0.0f;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	float beta_native = 0.0f;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	alpha_native = (float)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	beta_native = (float)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSsyrk(layout_native, triangle_native, a_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDsyrkNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jlong n, jlong k, jdouble alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jdouble beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastDsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDsyrk(layout=%d, triangle=%d, a_transpose=%d, n=%ld, k=%ld, alpha=%lf, a_buffer=%p, a_offset=%ld, a_ld=%ld, beta=%lf, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	double alpha_native = 0.0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	double beta_native = 0.0;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	alpha_native = (double)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	beta_native = (double)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDsyrk(layout_native, triangle_native, a_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCsyrkNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jlong n, jlong k, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jfloatArray beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastCsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastCsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCsyrk(layout=%d, triangle=%d, a_transpose=%d, n=%ld, k=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, beta=%p, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_float2 beta_native;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCsyrk(layout_native, triangle_native, a_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZsyrkNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jlong n, jlong k, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jdoubleArray beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastZsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastZsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZsyrk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZsyrk(layout=%d, triangle=%d, a_transpose=%d, n=%ld, k=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, beta=%p, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_double2 beta_native;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZsyrk(layout_native, triangle_native, a_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Rank-K update of a hermitian matrix: CHERK/ZHERK
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCherkNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jlong n, jlong k, jfloat alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jfloat beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCherk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastCherk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCherk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCherk(layout=%d, triangle=%d, a_transpose=%d, n=%ld, k=%ld, alpha=%f, a_buffer=%p, a_offset=%ld, a_ld=%ld, beta=%f, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	float alpha_native = 0.0f;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	float beta_native = 0.0f;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	alpha_native = (float)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	beta_native = (float)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCherk(layout_native, triangle_native, a_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZherkNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint a_transpose, jlong n, jlong k, jdouble alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jdouble beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZherk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastZherk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZherk");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZherk(layout=%d, triangle=%d, a_transpose=%d, n=%ld, k=%ld, alpha=%lf, a_buffer=%p, a_offset=%ld, a_ld=%ld, beta=%lf, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, a_transpose, n, k, alpha, a_buffer, a_offset, a_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	double alpha_native = 0.0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	double beta_native = 0.0;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	alpha_native = (double)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	beta_native = (double)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZherk(layout_native, triangle_native, a_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// a_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Rank-2K update of a symmetric matrix: SSYR2K/DSYR2K/CSYR2K/ZSYR2K
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastSsyr2kNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint ab_transpose, jlong n, jlong k, jfloat alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jfloat beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastSsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastSsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastSsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastSsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastSsyr2k(layout=%d, triangle=%d, ab_transpose=%d, n=%ld, k=%ld, alpha=%f, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%f, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose ab_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	float alpha_native = 0.0f;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	float beta_native = 0.0f;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	ab_transpose_native = (Transpose)ab_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	alpha_native = (float)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	beta_native = (float)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastSsyr2k(layout_native, triangle_native, ab_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDsyr2kNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint ab_transpose, jlong n, jlong k, jdouble alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jdouble beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastDsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastDsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDsyr2k(layout=%d, triangle=%d, ab_transpose=%d, n=%ld, k=%ld, alpha=%lf, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%lf, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose ab_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	double alpha_native = 0.0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	double beta_native = 0.0;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	ab_transpose_native = (Transpose)ab_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	alpha_native = (double)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	beta_native = (double)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDsyr2k(layout_native, triangle_native, ab_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCsyr2kNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint ab_transpose, jlong n, jlong k, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jfloatArray beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastCsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastCsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastCsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCsyr2k(layout=%d, triangle=%d, ab_transpose=%d, n=%ld, k=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%p, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose ab_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_float2 beta_native;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	ab_transpose_native = (Transpose)ab_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCsyr2k(layout_native, triangle_native, ab_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZsyr2kNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint ab_transpose, jlong n, jlong k, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jdoubleArray beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastZsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (beta == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for CLBlastZsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastZsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZsyr2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZsyr2k(layout=%d, triangle=%d, ab_transpose=%d, n=%ld, k=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%p, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose ab_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_double2 beta_native;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	ab_transpose_native = (Transpose)ab_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, beta, beta_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZsyr2k(layout_native, triangle_native, ab_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	if (!releaseNative(env, beta_native, beta, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Rank-2K update of a hermitian matrix: CHER2K/ZHER2K
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCher2kNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint ab_transpose, jlong n, jlong k, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jfloat beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCher2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCher2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastCher2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastCher2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCher2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCher2k(layout=%d, triangle=%d, ab_transpose=%d, n=%ld, k=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%f, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose ab_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	float beta_native = 0.0f;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	ab_transpose_native = (Transpose)ab_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	beta_native = (float)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCher2k(layout_native, triangle_native, ab_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZher2kNative(JNIEnv *env, jclass cls, jint layout, jint triangle, jint ab_transpose, jlong n, jlong k, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jdouble beta, jobject c_buffer, jlong c_offset, jlong c_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZher2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZher2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastZher2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	if (c_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'c_buffer' is null for CLBlastZher2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// c_offset is primitive
	// c_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZher2k");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZher2k(layout=%d, triangle=%d, ab_transpose=%d, n=%ld, k=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, beta=%lf, c_buffer=%p, c_offset=%ld, c_ld=%ld, queue=%p, event=%p)\n",
		layout, triangle, ab_transpose, n, k, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, beta, c_buffer, c_offset, c_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Triangle triangle_native;
	Transpose ab_transpose_native;
	size_t n_native = 0;
	size_t k_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	double beta_native = 0.0;
	cl_mem c_buffer_native = nullptr;
	size_t c_offset_native = 0;
	size_t c_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	triangle_native = (Triangle)triangle;
	ab_transpose_native = (Transpose)ab_transpose;
	n_native = (size_t)n;
	k_native = (size_t)k;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	beta_native = (double)beta;
	if (!initNative(env, c_buffer, c_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	c_offset_native = (size_t)c_offset;
	c_ld_native = (size_t)c_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZher2k(layout_native, triangle_native, ab_transpose_native, n_native, k_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, beta_native, c_buffer_native, c_offset_native, c_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// triangle is primitive
	// ab_transpose is primitive
	// n is primitive
	// k is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// beta is primitive
	// c_buffer is a read-only native pointer
	// c_offset is primitive
	// c_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Triangular matrix-matrix multiplication: STRMM/DTRMM/CTRMM/ZTRMM
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastStrmmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jint a_transpose, jint diagonal, jlong m, jlong n, jfloat alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastStrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastStrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastStrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastStrmm(layout=%d, side=%d, triangle=%d, a_transpose=%d, diagonal=%d, m=%ld, n=%ld, alpha=%f, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t m_native = 0;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	m_native = (size_t)m;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastStrmm(layout_native, side_native, triangle_native, a_transpose_native, diagonal_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDtrmmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jint a_transpose, jint diagonal, jlong m, jlong n, jdouble alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDtrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastDtrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDtrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDtrmm(layout=%d, side=%d, triangle=%d, a_transpose=%d, diagonal=%d, m=%ld, n=%ld, alpha=%lf, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t m_native = 0;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	m_native = (size_t)m;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDtrmm(layout_native, side_native, triangle_native, a_transpose_native, diagonal_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCtrmmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jint a_transpose, jint diagonal, jlong m, jlong n, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCtrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCtrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastCtrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCtrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCtrmm(layout=%d, side=%d, triangle=%d, a_transpose=%d, diagonal=%d, m=%ld, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCtrmm(layout_native, side_native, triangle_native, a_transpose_native, diagonal_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZtrmmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jint a_transpose, jint diagonal, jlong m, jlong n, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZtrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZtrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastZtrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZtrmm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZtrmm(layout=%d, side=%d, triangle=%d, a_transpose=%d, diagonal=%d, m=%ld, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZtrmm(layout_native, side_native, triangle_native, a_transpose_native, diagonal_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

// Solves a triangular system of equations: STRSM/DTRSM/CTRSM/ZTRSM
JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastStrsmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jint a_transpose, jint diagonal, jlong m, jlong n, jfloat alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastStrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastStrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastStrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastStrsm(layout=%d, side=%d, triangle=%d, a_transpose=%d, diagonal=%d, m=%ld, n=%ld, alpha=%f, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t m_native = 0;
	size_t n_native = 0;
	float alpha_native = 0.0f;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	m_native = (size_t)m;
	n_native = (size_t)n;
	alpha_native = (float)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastStrsm(layout_native, side_native, triangle_native, a_transpose_native, diagonal_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastDtrsmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jint a_transpose, jint diagonal, jlong m, jlong n, jdouble alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastDtrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastDtrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastDtrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastDtrsm(layout=%d, side=%d, triangle=%d, a_transpose=%d, diagonal=%d, m=%ld, n=%ld, alpha=%lf, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t m_native = 0;
	size_t n_native = 0;
	double alpha_native = 0.0;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	m_native = (size_t)m;
	n_native = (size_t)n;
	alpha_native = (double)alpha;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastDtrsm(layout_native, side_native, triangle_native, a_transpose_native, diagonal_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	// alpha is primitive
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastCtrsmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jint a_transpose, jint diagonal, jlong m, jlong n, jfloatArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastCtrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastCtrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastCtrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastCtrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastCtrsm(layout=%d, side=%d, triangle=%d, a_transpose=%d, diagonal=%d, m=%ld, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_float2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastCtrsm(layout_native, side_native, triangle_native, a_transpose_native, diagonal_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

JNIEXPORT jint JNICALL Java_org_jocl_blast_CLBlast_CLBlastZtrsmNative(JNIEnv *env, jclass cls, jint layout, jint side, jint triangle, jint a_transpose, jint diagonal, jlong m, jlong n, jdoubleArray alpha, jobject a_buffer, jlong a_offset, jlong a_ld, jobject b_buffer, jlong b_offset, jlong b_ld, jobject queue, jobject event)
{
	// Null-checks for non-primitive arguments
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	if (alpha == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for CLBlastZtrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	if (a_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'a_buffer' is null for CLBlastZtrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// a_offset is primitive
	// a_ld is primitive
	if (b_buffer == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'b_buffer' is null for CLBlastZtrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// b_offset is primitive
	// b_ld is primitive
	if (queue == nullptr)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'queue' is null for CLBlastZtrsm");
		return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	}
	// event may be nullptr

	// Log message
	Logger::log(LOG_TRACE, "Executing CLBlastZtrsm(layout=%d, side=%d, triangle=%d, a_transpose=%d, diagonal=%d, m=%ld, n=%ld, alpha=%p, a_buffer=%p, a_offset=%ld, a_ld=%ld, b_buffer=%p, b_offset=%ld, b_ld=%ld, queue=%p, event=%p)\n",
		layout, side, triangle, a_transpose, diagonal, m, n, alpha, a_buffer, a_offset, a_ld, b_buffer, b_offset, b_ld, queue, event);

	// Native variable declarations
	Layout layout_native;
	Side side_native;
	Triangle triangle_native;
	Transpose a_transpose_native;
	Diagonal diagonal_native;
	size_t m_native = 0;
	size_t n_native = 0;
	cl_double2 alpha_native;
	cl_mem a_buffer_native = nullptr;
	size_t a_offset_native = 0;
	size_t a_ld_native = 0;
	cl_mem b_buffer_native = nullptr;
	size_t b_offset_native = 0;
	size_t b_ld_native = 0;
	cl_command_queue * queue_native = nullptr;
	cl_event * event_native = nullptr;

	// Obtain native variable values
	layout_native = (Layout)layout;
	side_native = (Side)side;
	triangle_native = (Triangle)triangle;
	a_transpose_native = (Transpose)a_transpose;
	diagonal_native = (Diagonal)diagonal;
	m_native = (size_t)m;
	n_native = (size_t)n;
	if (!initNative(env, alpha, alpha_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, a_buffer, a_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	a_offset_native = (size_t)a_offset;
	a_ld_native = (size_t)a_ld;
	if (!initNative(env, b_buffer, b_buffer_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	b_offset_native = (size_t)b_offset;
	b_ld_native = (size_t)b_ld;
	if (!initNative(env, queue, queue_native, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	if (!initNative(env, event, event_native, false)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Native function call
	StatusCode jniResult_native = CLBlastZtrsm(layout_native, side_native, triangle_native, a_transpose_native, diagonal_native, m_native, n_native, alpha_native, a_buffer_native, a_offset_native, a_ld_native, b_buffer_native, b_offset_native, b_ld_native, queue_native, event_native);

	// Write back native variable values
	// layout is primitive
	// side is primitive
	// triangle is primitive
	// a_transpose is primitive
	// diagonal is primitive
	// m is primitive
	// n is primitive
	if (!releaseNative(env, alpha_native, alpha, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;
	// a_buffer is a read-only native pointer
	// a_offset is primitive
	// a_ld is primitive
	// b_buffer is a read-only native pointer
	// b_offset is primitive
	// b_ld is primitive
	// queue is a read-only native pointer
	if (!releaseNative(env, event_native, event, true)) return JOCL_BLAST_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}


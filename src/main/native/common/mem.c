//
// Copyright Alexander Schütz, 2021-2022
//
// This file is part of JavaNativeUtils.
//
// JavaNativeUtils is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JavaNativeUtils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// A copy of the GNU Lesser General Public License should be provided
// in the COPYING & COPYING.LESSER files in top level directory of JavaNativeUtils.
// If not, see <https://www.gnu.org/licenses/>.
//
#include "jni/io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory.h"
#include "timeutil.h"
#include "common.h"
#include <stdbool.h>
#include <stddef.h>
#include "atomics.h"
#include <string.h>



/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    supportsAtomicOperations
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_supportsAtomicOperations
  (JNIEnv * env, jobject inst) {
#if defined(__amd64__)
	return true;
#elif defined(__i386__)
	return true;
#else
	return false;
#endif
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    supports16ByteCompareAndSet
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_supports16ByteCompareAndSet
  (JNIEnv * env, jobject inst) {
#if defined(__amd64__)
	return true;
#else
	return false;
#endif
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    atomic8ByteOperationsRequireAlignment
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_atomic8ByteOperationsRequireAlignment
  (JNIEnv * env, jobject inst) {
#if defined(__amd64__)
	return false;
#else
	return true;
#endif
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJ[BII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_write__JJ_3BII
  (JNIEnv *env , jclass clazz, jlong ptr, jlong off, jbyteArray buf, jint bufoff, jint len) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	vptr+=(uintptr_t) off;
	(*env)->GetByteArrayRegion(env, buf, bufoff, len, (jbyte*) vptr);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJB)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_write__JJB
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jbyte value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	jbyte* dptr = (jbyte*) vptr;
	*(dptr) = value;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_write__JJI
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jint value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	jint* dptr = (jint*) vptr;
	*(dptr) = value;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_write__JJJ
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jlong value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	jlong* dptr = (jlong*) vptr;
	*(dptr) = value;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJF)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_write__JJF
	(JNIEnv *env, jclass clazz, jlong ptr, jlong off, jfloat value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	jfloat* dptr = (jfloat*) vptr;
	*(dptr) = value;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJD)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_write__JJD
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jdouble value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	jdouble* dptr = (jdouble*) vptr;
	*(dptr) = value;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJS)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_write__JJS
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jshort value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	jshort* dptr = (jshort*) vptr;
	*(dptr) = value;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    read
 * Signature: (JJ[BII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_read
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jbyteArray buf, jint bufoff, jint len) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	vptr+=(uintptr_t) off;
	(*env)->SetByteArrayRegion(env, buf, bufoff, len, vptr);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readInt
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readInt
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	jint* dptr = (jint*) vptr;
	return *dptr;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readLong
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readLong
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	jlong* dptr = (jlong*) vptr;
	return *dptr;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readFloat
 * Signature: (JJ)F
 */
JNIEXPORT jfloat JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readFloat
  (JNIEnv *env , jclass clazz, jlong ptr, jlong off) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	jfloat* dptr = (jfloat*) vptr;
	return *dptr;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readDouble
 * Signature: (JJ)D
 */
JNIEXPORT jdouble JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readDouble
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	jdouble* dptr = (jdouble*) vptr;
	return *dptr;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readShort
 * Signature: (JJ)S
 */
JNIEXPORT jshort JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readShort
  (JNIEnv *env , jclass clazz, jlong ptr, jlong off) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	jshort* dptr = (jshort*) vptr;
	return *dptr;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readByte
 * Signature: (JJ)B
 */
JNIEXPORT jbyte JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readByte
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	jbyte* dptr = (jbyte*) vptr;
	return *dptr;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    set
 * Signature: (JJBJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_set
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jbyte value, jlong len) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	if (len <= 0) {
		return;
	}

	vptr+=(uintptr_t) off;
	memset(vptr, value, len);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    getAndAdd
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_getAndAdd__JJJ
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jlong value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;

#if (defined(__i386__))
	if (((uintptr_t)vptr) % 4 != 0) {
		throwIllegalArgumentsExc(env, "memory alignment");
		return false;
	}
#endif

	if (xadd8b((uint64_t *)vptr, (uint64_t*) &value)) {
		return value;
	}
	throwUnsupportedExc(env, "getAndAdd 8 byte not supported by cpu");
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    getAndAdd
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_getAndAdd__JJI
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jint value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xadd4b((uint32_t *)vptr, (uint32_t*) &value)) {
		return value;
	}
	throwUnsupportedExc(env, "getAndAdd 4 byte not supported by cpu");
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    getAndAdd
 * Signature: (JJS)S
 */
JNIEXPORT jshort JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_getAndAdd__JJS
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jshort value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xadd2b((uint16_t *)vptr, (uint16_t*) &value)) {
		return value;
	}
	throwUnsupportedExc(env, "getAndAdd 2 byte not supported by cpu");
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    getAndAdd
 * Signature: (JJB)B
 */
JNIEXPORT jbyte JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_getAndAdd__JJB
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jbyte value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xadd1b((uint8_t *)vptr, (uint8_t*) &value)) {
		return value;
	}
	throwUnsupportedExc(env, "getAndAdd 1 byte not supported by cpu");
	return 0;
};

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    getAndSet
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_getAndSet__JJJ
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jlong value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;

#if (defined(__i386__))
	if (((uintptr_t)vptr) % 4 != 0) {
		throwIllegalArgumentsExc(env, "memory alignment");
		return false;
	}
#endif

	if (xchg8b((uint64_t *)vptr, (uint64_t*) &value)) {
		return value;
	}
	throwUnsupportedExc(env, "getAndSet 8 byte not supported by cpu");
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    getAndSet
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_getAndSet__JJI
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jint value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xchg4b((uint32_t *)vptr, (uint32_t*) &value)) {
		return value;
	}
	throwUnsupportedExc(env, "getAndSet 4 byte not supported by cpu");
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    getAndSet
 * Signature: (JJS)S
 */
JNIEXPORT jshort JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_getAndSet__JJS
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jshort value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xchg2b((uint16_t *)vptr, (uint16_t*) &value)) {
		return value;
	}
	throwUnsupportedExc(env, "getAndSet 2 byte not supported by cpu");
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    getAndSet
 * Signature: (JJB)B
 */
JNIEXPORT jbyte JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_getAndSet__JJB
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jbyte value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xchg1b((uint8_t *)vptr, (uint8_t*) &value)) {
		return value;
	}
	throwUnsupportedExc(env, "getAndSet 1 byte not supported by cpu");
	return 0;
}


//179

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet
 * Signature: (JJJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_compareAndSet__JJJJ
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jlong expect, jlong update) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(__i386__))
	if (((uintptr_t)vptr) % 4 != 0) {
		throwIllegalArgumentsExc(env, "memory alignment");
		return false;
	}
#endif

	bool succ;
	if (cmpxchg8b((uint64_t *)vptr, (uint64_t) expect, (uint64_t) update, &succ)) {
		return succ;
	}
	throwUnsupportedExc(env, "compareAndSet 8 byte not supported by cpu");
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet
 * Signature: (JJII)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_compareAndSet__JJII
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jint expect, jint update) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	bool succ;
	if (cmpxchg4b((uint32_t *)vptr, (uint32_t) expect, (uint32_t) update, &succ)) {
		return succ;
	}
	throwUnsupportedExc(env, "compareAndSet 4 byte not supported by cpu");
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet
 * Signature: (JJSS)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_compareAndSet__JJSS
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jshort expect, jshort update) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	bool succ;
	if (cmpxchg2b((uint16_t *)vptr, (uint16_t) expect, (uint16_t) update, &succ)) {
		return succ;
	}
	throwUnsupportedExc(env, "compareAndSet 2 byte not supported by cpu");
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet
 * Signature: (JJBB)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_compareAndSet__JJBB
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jbyte expect, jbyte update) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	bool succ;
	if (cmpxchg1b((uint8_t *)vptr, (uint8_t) expect, (uint8_t) update, &succ)) {
		return succ;
	}
	throwUnsupportedExc(env, "compareAndSet 1 byte not supported by cpu");
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet
 * Signature: (JJ[B)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_compareAndSet__JJ_3B
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jbyteArray value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;

	if (((uintptr_t)vptr) % 8 != 0) {
		throwIllegalArgumentsExc(env, "memory alignment");
		return false;
	}

	jbyte critical[32];

	(*env)->GetByteArrayRegion(env, value, 0, 32, critical);

	uint64_t* data = (uint64_t*) critical;

	bool succ;
	if (cmpxchg16b((uint64_t *)vptr, data, &succ)) {
		(*env)->ReleasePrimitiveArrayCritical(env, value, critical, JNI_ABORT);
		return succ;
	}
	(*env)->ReleasePrimitiveArrayCritical(env, value, critical, JNI_ABORT);
	throwUnsupportedExc(env, "compareAndSet 16 byte not supported by cpu");
	return 0;
}

//UTIL FOR SPIN
jboolean checkClosed(JNIEnv * env, jobject inst) {
	return (*env)->GetLongField(env, inst, JNINativeMemory_ptr) == 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJJJJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spinAndSet__JJJJJJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jlong expect, jlong update, jlong spinTime, jlong aTimeout) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return false;
	}

	vptr += off;

	uint64_t * iptr = (uint64_t *) vptr;
	bool succ = false;

	if (!cmpxchg8b(iptr, expect, update, &succ)) {
		throwUnsupportedExc(env, "spinAndSet not supported by cpu");
		return false;
	}

	if (succ) {
		return true;
	}

	uint64_t start = currentTimeMillis();

	while(true) {
		uint64_t now = currentTimeMillis();
		if (now < start) {
			return false;
		}

		uint64_t expired = now-start;

		if (expired >= aTimeout) {
			return false;
		}

		cmpxchg8b(iptr, expect, update, &succ);
		if (succ) {
			return true;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return false;
		}

		if (spinTime > 0) {
			if (spinTime >= aTimeout-expired) {
				return false;
			}
			sleepMillis(spinTime);
		}

	}

	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJJJJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spinAndSet__JJJJJ
	(JNIEnv * env, jobject inst, jlong ptr, jlong off, jlong expect, jlong update, jlong spinTime) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	vptr += off;

	uint64_t * iptr = (uint64_t *) vptr;
	bool succ = false;

	if (!cmpxchg8b(iptr, expect, update, &succ)) {
		throwUnsupportedExc(env, "spinAndSet not supported by cpu");
		return;
	}

	if (succ) {
		return;
	}

	while(true) {
		cmpxchg8b(iptr, expect, update, &succ);
		if (succ) {
			return;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return;
		}

		if (spinTime > 0) {
			sleepMillis(spinTime);
		}
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJJJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spin__JJJJJ
  (JNIEnv *env, jobject inst, jlong ptr, jlong off, jlong expect, jlong spinTime, jlong aTimeout) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}

	vptr += off;
	uint64_t * iptr = (uint64_t *) vptr;

	uint64_t start = currentTimeMillis();
	while(*iptr != expect) {
		uint64_t now = currentTimeMillis();

		if (now < start) {
			return false;
		}

		uint64_t expired = now-start;
		if (expired >= aTimeout) {
			return false;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return false;
		}

		if (spinTime > 0) {
			if (spinTime >= aTimeout-expired) {
				return false;
			}
			sleepMillis(spinTime);
		}
	}

	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJJJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spin__JJJJ
	(JNIEnv *env, jobject inst, jlong ptr, jlong off, jlong expect, jlong spinTime) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	vptr += off;
	uint64_t * iptr = (uint64_t *) vptr;

	while(*iptr != expect) {
		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return;
		}

		if (spinTime > 0) {
			sleepMillis(spinTime);
		}
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJIIJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spinAndSet__JJIIJJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jint expect, jint update, jlong spinTime, jlong aTimeout) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return false;
	}

	vptr += off;

	uint32_t * iptr = (uint32_t *) vptr;
	bool succ = false;

	if (!cmpxchg4b(iptr, expect, update, &succ)) {
		throwUnsupportedExc(env, "spinAndSet not supported by cpu");
		return false;
	}

	if (succ) {
		return true;
	}

	uint64_t start = currentTimeMillis();

	while(true) {
		uint64_t now = currentTimeMillis();
		if (now < start) {
			return false;
		}

		uint64_t expired = now-start;

		if (expired >= aTimeout) {
			return false;
		}

		cmpxchg4b(iptr, expect, update, &succ);
		if (succ) {
			return true;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return false;
		}

		if (spinTime > 0) {
			if (spinTime >= aTimeout-expired) {
				return false;
			}
			sleepMillis(spinTime);
		}

	}

	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJIIJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spinAndSet__JJIIJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jint expect, jint update, jlong spinTime) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	vptr += off;

	uint32_t * iptr = (uint32_t *) vptr;
	bool succ = false;

	if (!cmpxchg4b(iptr, expect, update, &succ)) {
		throwUnsupportedExc(env, "spinAndSet not supported by cpu");
		return;
	}

	if (succ) {
		return;
	}

	while(true) {
		cmpxchg4b(iptr, expect, update, &succ);
		if (succ) {
			return;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return;
		}

		if (spinTime > 0) {
			sleepMillis(spinTime);
		}
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJIJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spin__JJIJJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jint expect, jlong spinTime, jlong aTimeout) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}

	vptr += off;
	uint32_t * iptr = (uint32_t *) vptr;

	uint64_t start = currentTimeMillis();
	while(*iptr != expect) {
		uint64_t now = currentTimeMillis();

		if (now < start) {
			return false;
		}

		uint64_t expired = now-start;
		if (expired >= aTimeout) {
			return false;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return false;
		}

		if (spinTime > 0) {
			if (spinTime >= aTimeout-expired) {
				return false;
			}
			sleepMillis(spinTime);
		}
	}

	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJIJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spin__JJIJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jint expect, jlong spinTime) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	vptr += off;
	uint32_t * iptr = (uint32_t *) vptr;

	while(*iptr != expect) {
		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return;
		}

		if (spinTime > 0) {
			sleepMillis(spinTime);
		}
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJSSJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spinAndSet__JJSSJJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jshort expect, jshort update, jlong spinTime, jlong aTimeout) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return false;
	}

	vptr += off;

	uint16_t * iptr = (uint16_t *) vptr;
	bool succ = false;

	if (!cmpxchg2b(iptr, expect, update, &succ)) {
		throwUnsupportedExc(env, "spinAndSet not supported by cpu");
		return false;
	}

	if (succ) {
		return true;
	}

	uint64_t start = currentTimeMillis();

	while(true) {
		uint64_t now = currentTimeMillis();
		if (now < start) {
			return false;
		}

		uint64_t expired = now-start;

		if (expired >= aTimeout) {
			return false;
		}

		cmpxchg2b(iptr, expect, update, &succ);
		if (succ) {
			return true;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return false;
		}

		if (spinTime > 0) {
			if (spinTime >= aTimeout-expired) {
				return false;
			}
			sleepMillis(spinTime);
		}

	}

	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJSSJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spinAndSet__JJSSJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jshort expect, jshort update, jlong spinTime) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	vptr += off;

	uint16_t * iptr = (uint16_t *) vptr;
	bool succ = false;

	if (!cmpxchg2b(iptr, expect, update, &succ)) {
		throwUnsupportedExc(env, "spinAndSet not supported by cpu");
		return;
	}

	if (succ) {
		return;
	}

	while(true) {
		cmpxchg2b(iptr, expect, update, &succ);
		if (succ) {
			return;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return;
		}

		if (spinTime > 0) {
			sleepMillis(spinTime);
		}
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJSJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spin__JJSJJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jshort expect, jlong spinTime, jlong aTimeout) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}

	vptr += off;
	uint16_t * iptr = (uint16_t *) vptr;

	uint64_t start = currentTimeMillis();
	while(*iptr != expect) {
		uint64_t now = currentTimeMillis();

		if (now < start) {
			return false;
		}

		uint64_t expired = now-start;
		if (expired >= aTimeout) {
			return false;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return false;
		}

		if (spinTime > 0) {
			if (spinTime >= aTimeout-expired) {
				return false;
			}
			sleepMillis(spinTime);
		}
	}

	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJSJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spin__JJSJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jshort expect, jlong spinTime) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	vptr += off;
	uint16_t * iptr = (uint16_t *) vptr;

	while(*iptr != expect) {
		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return;
		}

		if (spinTime > 0) {
			sleepMillis(spinTime);
		}
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJBBJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spinAndSet__JJBBJJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jbyte expect, jbyte update, jlong spinTime, jlong aTimeout) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return false;
	}

	vptr += off;

	uint8_t * iptr = (uint8_t *) vptr;
	bool succ = false;

	if (!cmpxchg1b(iptr, expect, update, &succ)) {
		throwUnsupportedExc(env, "spinAndSet not supported by cpu");
		return false;
	}

	if (succ) {
		return true;
	}

	uint64_t start = currentTimeMillis();

	while(true) {
		uint64_t now = currentTimeMillis();
		if (now < start) {
			return false;
		}

		uint64_t expired = now-start;

		if (expired >= aTimeout) {
			return false;
		}

		cmpxchg1b(iptr, expect, update, &succ);
		if (succ) {
			return true;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return false;
		}

		if (spinTime > 0) {
			if (spinTime >= aTimeout-expired) {
				return false;
			}
			sleepMillis(spinTime);
		}

	}

	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJBBJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spinAndSet__JJBBJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jbyte expect, jbyte update, jlong spinTime) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	vptr += off;

	uint8_t * iptr = (uint8_t *) vptr;
	bool succ = false;

	if (!cmpxchg1b(iptr, expect, update, &succ)) {
		throwUnsupportedExc(env, "spinAndSet not supported by cpu");
		return;
	}

	if (succ) {
		return;
	}

	while(true) {
		cmpxchg1b(iptr, expect, update, &succ);
		if (succ) {
			return;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return;
		}

		if (spinTime > 0) {
			sleepMillis(spinTime);
		}
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJBJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spin__JJBJJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jbyte expect, jlong spinTime, jlong aTimeout) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return 0;
	}

	vptr += off;
	uint8_t * iptr = (uint8_t *) vptr;

	uint64_t start = currentTimeMillis();
	while(*iptr != expect) {
		uint64_t now = currentTimeMillis();

		if (now < start) {
			return false;
		}

		uint64_t expired = now-start;
		if (expired >= aTimeout) {
			return false;
		}

		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return false;
		}

		if (spinTime > 0) {
			if (spinTime >= aTimeout-expired) {
				return false;
			}
			sleepMillis(spinTime);
		}
	}

	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJBJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_spin__JJBJ
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jbyte expect, jlong spinTime) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	vptr += off;
	uint8_t * iptr = (uint8_t *) vptr;

	while(*iptr != expect) {
		if (checkClosed(env, inst)) {
			throwNullPointerException(env, "closed");
			return;
		}

		if (spinTime > 0) {
			sleepMillis(spinTime);
		}
	}
}

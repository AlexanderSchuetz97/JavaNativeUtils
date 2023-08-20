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
#include "endianutil.h"
#include <assert.h>

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
	return supportsCas16();
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
 * Method:    off
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_off
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off) {
	if (ptr == 0) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}

	void * v = (void*) (uintptr_t) ptr;

	v+=off;

	return (jlong) (uintptr_t) v;
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
		jthrowCC_NullPointerException_1(env, "ptr");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	volatile jbyte* dptr = (jbyte*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	volatile jint* dptr = (jint*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	volatile jlong* dptr = (jlong*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	volatile jfloat* dptr = (jfloat*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	volatile jdouble* dptr = (jdouble*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
	volatile jshort* dptr = (jshort*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	volatile jint* dptr = (jint*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	volatile jlong* dptr = (jlong*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	volatile jfloat* dptr = (jfloat*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	volatile jdouble* dptr = (jdouble*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	volatile jshort* dptr = (jshort*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	volatile jbyte* dptr = (jbyte*) vptr;
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
		jthrowCC_NullPointerException_1(env, "ptr");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;

#if (defined(__i386__))
	if (((uintptr_t)vptr) % 4 != 0) {
		jthrowCC_IllegalArgumentException_1(env, "memory alignment");
		return false;
	}
#endif

	if (xadd8b((uint64_t *)vptr, (uint64_t*) &value)) {
		return value;
	}
	jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 8 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xadd4b((uint32_t *)vptr, (uint32_t*) &value)) {
		return value;
	}
	jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 4 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xadd2b((uint16_t *)vptr, (uint16_t*) &value)) {
		return value;
	}
	jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 2 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xadd1b((uint8_t *)vptr, (uint8_t*) &value)) {
		return value;
	}
	jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 1 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;

#if (defined(__i386__))
	if (((uintptr_t)vptr) % 4 != 0) {
		jthrowCC_IllegalArgumentException_1(env, "memory alignment");
		return false;
	}
#endif

	if (xchg8b((uint64_t *)vptr, (uint64_t*) &value)) {
		return value;
	}
	jthrowCC_UnsupportedOperationException_1(env, "getAndSet 8 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xchg4b((uint32_t *)vptr, (uint32_t*) &value)) {
		return value;
	}
	jthrowCC_UnsupportedOperationException_1(env, "getAndSet 4 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xchg2b((uint16_t *)vptr, (uint16_t*) &value)) {
		return value;
	}
	jthrowCC_UnsupportedOperationException_1(env, "getAndSet 2 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	if (xchg1b((uint8_t *)vptr, (uint8_t*) &value)) {
		return value;
	}
	jthrowCC_UnsupportedOperationException_1(env, "getAndSet 1 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(__i386__))
	if (((uintptr_t)vptr) % 4 != 0) {
		jthrowCC_IllegalArgumentException_1(env, "memory alignment");
		return false;
	}
#endif

	bool succ;
	if (cmpxchg8b((uint64_t *)vptr, (uint64_t) expect, (uint64_t) update, &succ)) {
		return succ;
	}
	jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 8 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	bool succ;
	if (cmpxchg4b((uint32_t *)vptr, (uint32_t) expect, (uint32_t) update, &succ)) {
		return succ;
	}
	jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 4 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	bool succ;
	if (cmpxchg2b((uint16_t *)vptr, (uint16_t) expect, (uint16_t) update, &succ)) {
		return succ;
	}
	jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 2 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
	bool succ;
	if (cmpxchg1b((uint8_t *)vptr, (uint8_t) expect, (uint8_t) update, &succ)) {
		return succ;
	}
	jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 1 byte not supported by cpu");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;

	if (((uintptr_t)vptr) % 8 != 0) {
		jthrowCC_IllegalArgumentException_1(env, "memory alignment");
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
	jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 16 byte not supported by cpu");
	return 0;
}

//UTIL FOR SPIN
jboolean checkClosed(JNIEnv * env, jobject inst) {
	return jget_JNINativeMemory_ptr(env, inst) == 0;
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return false;
	}

	vptr += off;

	uint64_t * iptr = (uint64_t *) vptr;
	bool succ = false;

	if (!cmpxchg8b(iptr, expect, update, &succ)) {
		jthrowCC_UnsupportedOperationException_1(env, "spinAndSet not supported by cpu");
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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	vptr += off;

	uint64_t * iptr = (uint64_t *) vptr;
	bool succ = false;

	if (!cmpxchg8b(iptr, expect, update, &succ)) {
		jthrowCC_UnsupportedOperationException_1(env, "spinAndSet not supported by cpu");
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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	vptr += off;
	volatile uint64_t * iptr = (uint64_t *) vptr;

	while(*iptr != expect) {
		if (checkClosed(env, inst)) {
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return false;
	}

	vptr += off;

	uint32_t * iptr = (uint32_t *) vptr;
	bool succ = false;

	if (!cmpxchg4b(iptr, expect, update, &succ)) {
		jthrowCC_UnsupportedOperationException_1(env, "spinAndSet not supported by cpu");
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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	vptr += off;

	uint32_t * iptr = (uint32_t *) vptr;
	bool succ = false;

	if (!cmpxchg4b(iptr, expect, update, &succ)) {
		jthrowCC_UnsupportedOperationException_1(env, "spinAndSet not supported by cpu");
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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}

	vptr += off;
	volatile uint32_t * iptr = (uint32_t *) vptr;

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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	vptr += off;
	volatile uint32_t * iptr = (uint32_t *) vptr;

	while(*iptr != expect) {
		if (checkClosed(env, inst)) {
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return false;
	}

	vptr += off;

	uint16_t * iptr = (uint16_t *) vptr;
	bool succ = false;

	if (!cmpxchg2b(iptr, expect, update, &succ)) {
		jthrowCC_UnsupportedOperationException_1(env, "spinAndSet not supported by cpu");
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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	vptr += off;

	uint16_t * iptr = (uint16_t *) vptr;
	bool succ = false;

	if (!cmpxchg2b(iptr, expect, update, &succ)) {
		jthrowCC_UnsupportedOperationException_1(env, "spinAndSet not supported by cpu");
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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}

	vptr += off;
	volatile uint16_t * iptr = (uint16_t *) vptr;

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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	vptr += off;
	volatile uint16_t * iptr = (uint16_t *) vptr;

	while(*iptr != expect) {
		if (checkClosed(env, inst)) {
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return false;
	}

	vptr += off;

	uint8_t * iptr = (uint8_t *) vptr;
	bool succ = false;

	if (!cmpxchg1b(iptr, expect, update, &succ)) {
		jthrowCC_UnsupportedOperationException_1(env, "spinAndSet not supported by cpu");
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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	vptr += off;

	uint8_t * iptr = (uint8_t *) vptr;
	bool succ = false;

	if (!cmpxchg1b(iptr, expect, update, &succ)) {
		jthrowCC_UnsupportedOperationException_1(env, "spinAndSet not supported by cpu");
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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}

	vptr += off;
	volatile uint8_t * iptr = (uint8_t *) vptr;

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
			jthrowCC_NullPointerException_1(env, "closed");
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
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	vptr += off;
	volatile uint8_t * iptr = (uint8_t *) vptr;

	while(*iptr != expect) {
		if (checkClosed(env, inst)) {
			jthrowCC_NullPointerException_1(env, "closed");
			return;
		}

		if (spinTime > 0) {
			sleepMillis(spinTime);
		}
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    memmove
 * Signature: (JJJJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_memmove
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off, jlong trg, jlong size) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	void * vtrg = (void *) (uintptr_t) trg;

	if (vtrg == NULL) {
		jthrowCC_NullPointerException_1(env, "target");
		return;
	}

	if (size <= 0) {
		if (size < 0) {
			jthrowCC_IllegalArgumentException_1(env, "size");
		}
		return;
	}

	vptr += off;

	memmove(vtrg, vptr, size);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readBuffer
 * Signature: (JJLjava/nio/ByteBuffer;II)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readBuffer
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off, jobject buf, jint boff, jint blen) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	vptr += off;

	void* nbuf = (*env)->GetDirectBufferAddress(env, buf);
	if (nbuf == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "GetDirectBufferAddress returned NULL");
		return;
	}

	if (boff < 0) {
		jthrowCC_IllegalArgumentException_1(env, "bufferOffset < 0");
		return;
	}


	jlong capa = (*env)->GetDirectBufferCapacity(env, buf);
	if (boff+blen > capa) {
		jthrowCC_IllegalArgumentException_1(env, "offset+length > GetDirectBufferCapacity");
		return;
	}

	nbuf+=boff;

	memmove(nbuf, vptr, blen);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    writeBuffer
 * Signature: (JJLjava/nio/ByteBuffer;II)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_writeBuffer
(JNIEnv * env, jclass clazz, jlong ptr, jlong off, jobject buf, jint boff, jint blen) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	vptr += off;

	void* nbuf = (*env)->GetDirectBufferAddress(env, buf);
	if (nbuf == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "GetDirectBufferAddress returned NULL");
		return;
	}

	if (boff < 0) {
		jthrowCC_IllegalArgumentException_1(env, "bufferOffset < 0");
		return;
	}


	jlong capa = (*env)->GetDirectBufferCapacity(env, buf);
	if (boff+blen > capa) {
		jthrowCC_IllegalArgumentException_1(env, "offset+length > GetDirectBufferCapacity");
		return;
	}

	nbuf+=boff;

	memmove(vptr, nbuf, blen);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    indexOf
 * Signature: (JJJB)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_indexOf
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off, jlong max, jbyte value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}

	vptr += off;
	volatile jbyte * bptr = (volatile jbyte*) vptr;

	for (jlong x = 0; x < max; x++) {
		if (bptr[x] == value) {
			return off+x;
		}
	}

	return -1;
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readUntilByte
 * Signature: (JJIB[BI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readUntilByte
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off, jint max, jbyte value, jbyteArray buf, jint bufOff) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	if (buf == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return 0;
	}


	if (bufOff < 0 || (*env)->GetArrayLength(env, buf) < bufOff+max) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return 0;
	}

	vptr += off;
	volatile jbyte * bptr = (volatile jbyte*) vptr;


	//To big to fit on stack
	if (max > 512) {
		jbyte* copy = (*env)->GetByteArrayElements(env, buf, NULL);

		jint x = 0;
		while(x < max) {
			jbyte cur = bptr[x++];
			copy[bufOff++] = cur;
			if (cur == value) {
				break;
			}
		}

		(*env)->ReleaseByteArrayElements(env, buf, copy, x > 0 ? JNI_OK : JNI_ABORT);

		return x;
	}

	jbyte stack[max];

	jint x = 0;
	while(x < max) {
		jbyte cur = bptr[x];
		stack[x++] = cur;
		if (cur == value) {
			break;
		}
	}

	if (x > 0) {
		(*env)->SetByteArrayRegion(env, buf, bufOff, (jsize) x, stack);
	}

	return x;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    writeDoubleArray
 * Signature: (JJ[DII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_writeDoubleArray
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off, jdoubleArray array, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	jdouble* jdptr = (jdouble*) vptr;
	(*env)->SetDoubleArrayRegion(env, array, arrayOff, (jsize) arrayLen, jdptr);
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    writeFloatArray
 * Signature: (JJ[FII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_writeFloatArray
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off, jfloatArray array, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	jfloat* jfptr = (jfloat*) vptr;
	(*env)->SetFloatArrayRegion(env, array, arrayOff, (jsize) arrayLen, jfptr);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    writeExpandedByteArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_writeExpandedByteArray
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off, jbyteArray array, jint size, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	if (size == 1) {
		(*env)->SetByteArrayRegion(env, array, arrayOff, arrayLen, (jbyte*) vptr);
		return;
	}


	jbyte * bPtr = (*env)->GetByteArrayElements(env, array, NULL);
	if (bPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return;
	}

	jsize psize = size-sizeof(jbyte);
	vptr += off;
#if BYTE_ORDER == LITTLE_ENDIAN
	struct padder {
		jbyte padding[psize];
		jbyte value;
	} __attribute__((packed));
#elif BYTE_ORDER == BIG_ENDIAN
	struct padder {
		jbyte value;
		jbyte padding[psize];
	} __attribute__((packed));
#else
#error
#endif
	struct padder* pptr = (struct padder*) vptr;
	assert(((uintptr_t)&pptr[1]) - ((uintptr_t)&pptr[0]) == size);


	for (jsize i = 0; i < arrayLen; i++) {
		if (psize > 0) {
			memset(&pptr[i].padding[0], 0, psize);
		}
		pptr[i].value = bPtr[arrayOff+i];
	}

	(*env)->ReleaseByteArrayElements(env, array, bPtr, JNI_ABORT);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    writeExpandedCharArray
 * Signature: (JJ[CIII)V
 */


JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_writeExpandedCharArray
	(JNIEnv * env, jclass clazz, jlong ptr, jlong off, jcharArray array, jint size, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	if (size == 2) {
		(*env)->SetCharArrayRegion(env, array, arrayOff, arrayLen, (jchar*) vptr);
		return;
	}

	jchar * bPtr = (*env)->GetCharArrayElements(env, array, NULL);
	if (bPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetCharArrayElements");
		return;
	}

	switch(size) {
		case (1): {
			jbyte* pptr = (jbyte*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				pptr[i] = (jbyte) bPtr[arrayOff+i];
			}

			(*env)->ReleaseCharArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
	}

	jsize psize = size-sizeof(jchar);

#if BYTE_ORDER == LITTLE_ENDIAN
	struct padder {
		jbyte padding[psize];
		jchar value;
	} __attribute__((packed));
#elif BYTE_ORDER == BIG_ENDIAN
	struct padder {
		jchar value;
		jbyte padding[psize];
	} __attribute__((packed));
#else
#error
#endif
	struct padder* pptr = (struct padder*) vptr;
	assert(((uintptr_t)&pptr[1]) - ((uintptr_t)&pptr[0]) == size);
	for (jsize i = 0; i < arrayLen; i++) {
		if (psize > 0) {
			memset(&pptr[i].padding[0], 0, psize);
		}
		pptr[i].value = bPtr[arrayOff+i];
	}

	(*env)->ReleaseCharArrayElements(env, array, bPtr, JNI_ABORT);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    writeExpandedShortArray
 * Signature: (JJ[SIII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_writeExpandedShortArray
	(JNIEnv * env, jclass clazz, jlong ptr, jlong off, jshortArray array, jint size, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	if (size == 2) {
		(*env)->SetShortArrayRegion(env, array, arrayOff, arrayLen, (jshort*) vptr);
		return;
	}

	jshort * bPtr = (*env)->GetShortArrayElements(env, array, NULL);
	if (bPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetShortArrayElements");
		return;
	}


	switch(size) {
		case (1): {
			jbyte* pptr = (jbyte*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				pptr[i] = (jbyte) bPtr[arrayOff+i];
			}

			(*env)->ReleaseShortArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
	}

	jsize psize = size-sizeof(jshort);

#if BYTE_ORDER == LITTLE_ENDIAN
	struct padder {
		jbyte padding[psize];
		jshort value;
	} __attribute__((packed));
#elif BYTE_ORDER == BIG_ENDIAN
	struct padder {
		jshort value;
		jbyte padding[psize];
	} __attribute__((packed));
#else
#error
#endif
	struct padder* pptr = (struct padder*) vptr;
	assert(((uintptr_t)&pptr[1]) - ((uintptr_t)&pptr[0]) == size);
	for (jsize i = 0; i < arrayLen; i++) {
		if (psize > 0) {
			memset(&pptr[i].padding[0], 0, psize);
		}
		pptr[i].value = bPtr[arrayOff+i];
	}

	(*env)->ReleaseShortArrayElements(env, array, bPtr, JNI_ABORT);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    writeExpandedIntArray
 * Signature: (JJ[IIII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_writeExpandedIntArray
	(JNIEnv * env, jclass clazz, jlong ptr, jlong off, jintArray array, jint size, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	if (size == 4) {
		(*env)->SetIntArrayRegion(env, array, arrayOff, arrayLen, (jint*) vptr);
		return;
	}

	jint * bPtr = (*env)->GetIntArrayElements(env, array, NULL);
	if (bPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetIntArrayElements");
		return;
	}



	switch(size) {
		case (1): {
			jbyte* pptr = (jbyte*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				pptr[i] = (jbyte) bPtr[arrayOff+i];
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (2): {
			uint16_t* pptr = (uint16_t*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				pptr[i] = (uint16_t) bPtr[arrayOff+i];
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (3): {
			uint8_t* pptr = (uint8_t*) vptr;
			jsize x = 0;
			for (jsize i = 0; i < arrayLen; i++) {
				uint32_t u32 = (uint32_t) bPtr[arrayOff+i];
#if BYTE_ORDER == LITTLE_ENDIAN
				pptr[x++] = (uint8_t)((u32 >> 0) & 0xff);
				pptr[x++] = (uint8_t)((u32 >> 8) & 0xff);
				pptr[x++] = (uint8_t)((u32 >> 16) & 0xff);
#elif BYTE_ORDER == BIG_ENDIAN
				pptr[x++] = (uint8_t)((u32 >> 16) & 0xff);
				pptr[x++] = (uint8_t)((u32 >> 8) & 0xff);
				pptr[x++] = (uint8_t)((u32 >> 0) & 0xff);
#else
#error
#endif
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
	}

	jsize psize = size-sizeof(jint);

#if BYTE_ORDER == LITTLE_ENDIAN
	struct padder {
		jbyte padding[psize];
		jint value;
	} __attribute__((packed));
#elif BYTE_ORDER == BIG_ENDIAN
	struct padder {
		jint value;
		jbyte padding[psize];
	} __attribute__((packed));
#else
#error
#endif
	struct padder* pptr = (struct padder*) vptr;
	assert(((uintptr_t)&pptr[1]) - ((uintptr_t)&pptr[0]) == size);

	for (jsize i = 0; i < arrayLen; i++) {
		if (psize > 0) {
			memset(&pptr[i].padding[0], 0, psize);
		}
		pptr[i].value = bPtr[arrayOff+i];
	}

	(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_ABORT);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    writeExpandedLongArray
 * Signature: (JJ[JIII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_writeExpandedLongArray
	(JNIEnv * env, jclass clazz, jlong ptr, jlong off, jlongArray array, jint size, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	jlong * bPtr = (*env)->GetLongArrayElements(env, array, NULL);
	if (bPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetLongArrayElements");
		return;
	}

	vptr += off;
	switch(size) {
		case (1): {
			jbyte* pptr = (jbyte*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				pptr[i] = (jbyte) bPtr[arrayOff+i];
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (2): {
			uint16_t* pptr = (uint16_t*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				pptr[i] = (uint16_t) bPtr[arrayOff+i];
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (3): {
			uint8_t* pptr = (uint8_t*) vptr;
			jsize x = 0;
			for (jsize i = 0; i < arrayLen; i++) {
				uint32_t u32 = (uint32_t) bPtr[arrayOff+i];
#if BYTE_ORDER == LITTLE_ENDIAN
				pptr[x++] = (uint8_t)((u32 >> 0) & 0xff);
				pptr[x++] = (uint8_t)((u32 >> 8) & 0xff);
				pptr[x++] = (uint8_t)((u32 >> 16) & 0xff);
#elif BYTE_ORDER == BIG_ENDIAN
				pptr[x++] = (uint8_t)((u32 >> 16) & 0xff);
				pptr[x++] = (uint8_t)((u32 >> 8) & 0xff);
				pptr[x++] = (uint8_t)((u32 >> 0) & 0xff);
#else
#error
#endif
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (4): {
			uint32_t* pptr = (uint32_t*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				pptr[i] = (uint32_t) bPtr[arrayOff+i];
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (5): {
			uint8_t* pptr = (uint8_t*) vptr;
			jsize x = 0;
			for (jsize i = 0; i < arrayLen; i++) {
				uint64_t u64 = (uint64_t) bPtr[arrayOff+i];
#if BYTE_ORDER == LITTLE_ENDIAN
				pptr[x++] = (uint8_t)((u64 >> 0) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 8) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 16) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 24) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 32) & 0xff);
#elif BYTE_ORDER == BIG_ENDIAN
				pptr[x++] = (uint8_t)((u64 >> 32) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 24) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 16) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 8) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 0) & 0xff);
#else
#error
#endif
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (6): {
			uint8_t* pptr = (uint8_t*) vptr;
			jsize x = 0;
			for (jsize i = 0; i < arrayLen; i++) {
				uint64_t u64 = (uint64_t) bPtr[arrayOff+i];
#if BYTE_ORDER == LITTLE_ENDIAN
				pptr[x++] = (uint8_t)((u64 >> 0) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 8) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 16) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 24) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 32) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 40) & 0xff);
#elif BYTE_ORDER == BIG_ENDIAN
				pptr[x++] = (uint8_t)((u64 >> 40) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 32) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 24) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 16) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 8) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 0) & 0xff);
#else
#error
#endif
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (7): {
			uint8_t* pptr = (uint8_t*) vptr;
			jsize x = 0;
			for (jsize i = 0; i < arrayLen; i++) {
				uint64_t u64 = (uint64_t) bPtr[arrayOff+i];
#if BYTE_ORDER == LITTLE_ENDIAN
				pptr[x++] = (uint8_t)((u64 >> 0) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 8) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 16) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 24) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 32) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 40) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 48) & 0xff);
#elif BYTE_ORDER == BIG_ENDIAN
				pptr[x++] = (uint8_t)((u64 >> 48) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 40) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 32) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 24) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 16) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 8) & 0xff);
				pptr[x++] = (uint8_t)((u64 >> 0) & 0xff);
#else
#error
#endif
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
	}

	jsize psize = size-sizeof(jlong);

#if BYTE_ORDER == LITTLE_ENDIAN
	struct padder {
		jbyte padding[psize];
		jlong value;
	} __attribute__((packed));
#elif BYTE_ORDER == BIG_ENDIAN
	struct padder {
		jlong value;
		jbyte padding[psize];
	} __attribute__((packed));
#else
#error
#endif
	struct padder* pptr = (struct padder*) vptr;
	assert(((uintptr_t)&pptr[1]) - ((uintptr_t)&pptr[0]) == size);

	for (jsize i = 0; i < arrayLen; i++) {
		if (psize > 0) {
			memset(&pptr[i].padding[0], 0, psize);
		}
		pptr[i].value = bPtr[arrayOff+i];
	}

	(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readDoubleArray
 * Signature: (JJ[DII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readDoubleArray
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off, jdoubleArray array, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	jdouble* jdptr = (jdouble*) vptr;
	(*env)->GetDoubleArrayRegion(env, array, arrayOff, (jsize) arrayLen, jdptr);
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readFloatArray
 * Signature: (JJ[FII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readFloatArray
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off, jfloatArray array, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	jfloat* jfptr = (jfloat*) vptr;
	(*env)->GetFloatArrayRegion(env, array, arrayOff, (jsize) arrayLen, jfptr);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readExpandedByteArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readExpandedByteArray
(JNIEnv * env, jclass clazz, jlong ptr, jlong off, jbyteArray array, jint size, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	if (size == 1) {
		(*env)->GetByteArrayRegion(env, array, arrayOff, arrayLen, (jbyte*) vptr);
		return;
	}


	jbyte * bPtr = (*env)->GetByteArrayElements(env, array, NULL);
	if (bPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return;
	}

#if BYTE_ORDER == BIG_ENDIAN
		vptr+=size-sizeof(jbyte);
#endif

	for (jsize i = 0; i < arrayLen; i++) {
		jbyte* pptr = (jbyte*) vptr;
		bPtr[arrayOff+i] = pptr[0];
		vptr+=size;
	}

	(*env)->ReleaseByteArrayElements(env, array, bPtr, JNI_OK);
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readExpandedCharArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readExpandedCharArray
(JNIEnv * env, jclass clazz, jlong ptr, jlong off, jcharArray array, jint size, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	if (size == 2) {
		(*env)->GetCharArrayRegion(env, array, arrayOff, arrayLen, (jshort*) vptr);
		return;
	}


	jchar * bPtr = (*env)->GetCharArrayElements(env, array, NULL);
	if (bPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetCharArrayElements");
		return;
	}

	if (size == 1) {
		jbyte* pptr = (jbyte*) vptr;
		for (jsize i = 0; i < arrayLen; i++) {
			bPtr[arrayOff+i] = (jchar) pptr[i];
		}

		(*env)->ReleaseCharArrayElements(env, array, bPtr, JNI_OK);

		return;
	}

#if BYTE_ORDER == BIG_ENDIAN
		vptr+=size-sizeof(jchar);
#endif

	for (jsize i = 0; i < arrayLen; i++) {
		jchar* pptr = (jchar*) vptr;
		bPtr[arrayOff+i] = pptr[0];
		vptr+=size;
	}

	(*env)->ReleaseCharArrayElements(env, array, bPtr, JNI_OK);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readExpandedShortArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readExpandedShortArray
(JNIEnv * env, jclass clazz, jlong ptr, jlong off, jshortArray array, jint size, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	if (size == 2) {
		(*env)->GetCharArrayRegion(env, array, arrayOff, arrayLen, (jshort*) vptr);
		return;
	}


	jshort * bPtr = (*env)->GetShortArrayElements(env, array, NULL);
	if (bPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetShortArrayElements");
		return;
	}

	if (size == 1) {
		jbyte* pptr = (jbyte*) vptr;
		for (jsize i = 0; i < arrayLen; i++) {
			bPtr[arrayOff+i] = (jshort) pptr[i];
		}

		(*env)->ReleaseShortArrayElements(env, array, bPtr, JNI_OK);

		return;
	}

#if BYTE_ORDER == BIG_ENDIAN
		vptr+=size-sizeof(jshort);
#endif

	for (jsize i = 0; i < arrayLen; i++) {
		jshort* pptr = (jshort*) vptr;
		bPtr[arrayOff+i] = pptr[0];
		vptr+=size;
	}

	(*env)->ReleaseShortArrayElements(env, array, bPtr, JNI_OK);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readExpandedIntArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readExpandedIntArray
(JNIEnv * env, jclass clazz, jlong ptr, jlong off, jintArray array, jint size, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	if (size == 4) {
		(*env)->GetIntArrayRegion(env, array, arrayOff, arrayLen, (jint*) vptr);
		return;
	}


	jint * bPtr = (*env)->GetIntArrayElements(env, array, NULL);
	if (bPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetIntArrayElements");
		return;
	}

	switch(size) {
		case (1): {
			jbyte* pptr = (jbyte*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				bPtr[arrayOff+i] = (jint) pptr[i];
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_OK);

			return;
		}
		case (2): {
			jshort* pptr = (jshort*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				bPtr[arrayOff+i] = (jint) pptr[i];
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_OK);
			return;
		}
		case (3): {
			uint8_t* pptr = (uint8_t*) vptr;
			jsize x = 0;
			for (jsize i = 0; i < arrayLen; i++) {
				uint32_t val = 0;
#if BYTE_ORDER == LITTLE_ENDIAN
				val |= (((uint32_t)pptr[x++]) << 0);
				val |= (((uint32_t)pptr[x++]) << 8);
				val |= (((uint32_t)pptr[x++]) << 16);
#elif BYTE_ORDER == BIG_ENDIAN
				val |= (((uint32_t)pptr[x++]) << 16);
				val |= (((uint32_t)pptr[x++]) << 8);
				val |= (((uint32_t)pptr[x++]) << 0);
#else
#error
#endif
				bPtr[arrayOff+i] = (jint) val;
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_OK);
			return;
		}
	}

#if BYTE_ORDER == BIG_ENDIAN
		vptr+=size-sizeof(jint);
#endif

	for (jsize i = 0; i < arrayLen; i++) {
		jint* pptr = (jint*) vptr;
		bPtr[arrayOff+i] = pptr[0];
		vptr+=size;
	}

	(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_OK);
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory
 * Method:    readExpandedLongArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNINativeMemory_readExpandedLongArray
(JNIEnv * env, jclass clazz, jlong ptr, jlong off, jlongArray array, jint size, jint arrayOff, jint arrayLen) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return;
	}


	if (arrayOff < 0 || (*env)->GetArrayLength(env, array) < arrayOff+arrayLen) {
		jthrowCC_IllegalArgumentException_1(env, "buffer");
		return;
	}

	vptr += off;
	if (size == 8) {
		(*env)->GetLongArrayRegion(env, array, arrayOff, arrayLen, (jlong*) vptr);
		return;
	}


	jlong * bPtr = (*env)->GetLongArrayElements(env, array, NULL);
	if (bPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetLongArrayElements");
		return;
	}

	switch(size) {
		case (1): {
			jbyte* pptr = (jbyte*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				bPtr[arrayOff+i] = (jint) pptr[i];
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);

			return;
		}
		case (2): {
			jshort* pptr = (jshort*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				bPtr[arrayOff+i] = (jint) pptr[i];
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
			return;
		}
		case (3): {
			uint8_t* pptr = (uint8_t*) vptr;
			jsize x = 0;
			for (jsize i = 0; i < arrayLen; i++) {
				uint32_t val = 0;
#if BYTE_ORDER == LITTLE_ENDIAN
				val |= (((uint32_t)pptr[x++]) << 0);
				val |= (((uint32_t)pptr[x++]) << 8);
				val |= (((uint32_t)pptr[x++]) << 16);
#elif BYTE_ORDER == BIG_ENDIAN
				val |= (((uint32_t)pptr[x++]) << 16);
				val |= (((uint32_t)pptr[x++]) << 8);
				val |= (((uint32_t)pptr[x++]) << 0);
#else
#error
#endif
				bPtr[arrayOff+i] = (jlong) val;
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
			return;
		}
		case (4): {
			jint* pptr = (jint*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				bPtr[arrayOff+i] = (jlong) pptr[i];
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
			return;
		}
		case (5): {
			uint8_t* pptr = (uint8_t*) vptr;
			jsize x = 0;
			for (jsize i = 0; i < arrayLen; i++) {
				uint64_t val = 0;
#if BYTE_ORDER == LITTLE_ENDIAN
				val |= (((uint64_t)pptr[x++]) << 0);
				val |= (((uint64_t)pptr[x++]) << 8);
				val |= (((uint64_t)pptr[x++]) << 16);
				val |= (((uint64_t)pptr[x++]) << 24);
				val |= (((uint64_t)pptr[x++]) << 32);
#elif BYTE_ORDER == BIG_ENDIAN
				val |= (((uint64_t)pptr[x++]) << 32);
				val |= (((uint64_t)pptr[x++]) << 24);
				val |= (((uint64_t)pptr[x++]) << 16);
				val |= (((uint64_t)pptr[x++]) << 8);
				val |= (((uint64_t)pptr[x++]) << 0);
#else
#error
#endif
				bPtr[arrayOff+i] = (jlong) val;
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
			return;
		}
		case (6): {
			uint8_t* pptr = (uint8_t*) vptr;
			jsize x = 0;
			for (jsize i = 0; i < arrayLen; i++) {
				uint64_t val = 0;
#if BYTE_ORDER == LITTLE_ENDIAN
				val |= (((uint64_t)pptr[x++]) << 0);
				val |= (((uint64_t)pptr[x++]) << 8);
				val |= (((uint64_t)pptr[x++]) << 16);
				val |= (((uint64_t)pptr[x++]) << 24);
				val |= (((uint64_t)pptr[x++]) << 32);
				val |= (((uint64_t)pptr[x++]) << 40);
#elif BYTE_ORDER == BIG_ENDIAN
				val |= (((uint64_t)pptr[x++]) << 40);
				val |= (((uint64_t)pptr[x++]) << 32);
				val |= (((uint64_t)pptr[x++]) << 24);
				val |= (((uint64_t)pptr[x++]) << 16);
				val |= (((uint64_t)pptr[x++]) << 8);
				val |= (((uint64_t)pptr[x++]) << 0);
#else
#error
#endif
				bPtr[arrayOff+i] = (jlong) val;
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
			return;
		}
		case (7): {
			uint8_t* pptr = (uint8_t*) vptr;
			jsize x = 0;
			for (jsize i = 0; i < arrayLen; i++) {
				uint64_t val = 0;
#if BYTE_ORDER == LITTLE_ENDIAN
				val |= (((uint64_t)pptr[x++]) << 0);
				val |= (((uint64_t)pptr[x++]) << 8);
				val |= (((uint64_t)pptr[x++]) << 16);
				val |= (((uint64_t)pptr[x++]) << 24);
				val |= (((uint64_t)pptr[x++]) << 32);
				val |= (((uint64_t)pptr[x++]) << 40);
				val |= (((uint64_t)pptr[x++]) << 48);
#elif BYTE_ORDER == BIG_ENDIAN
				val |= (((uint64_t)pptr[x++]) << 48);
				val |= (((uint64_t)pptr[x++]) << 40);
				val |= (((uint64_t)pptr[x++]) << 32);
				val |= (((uint64_t)pptr[x++]) << 24);
				val |= (((uint64_t)pptr[x++]) << 16);
				val |= (((uint64_t)pptr[x++]) << 8);
				val |= (((uint64_t)pptr[x++]) << 0);
#else
#error
#endif
				bPtr[arrayOff+i] = (jlong) val;
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
			return;
		}
	}

#if BYTE_ORDER == BIG_ENDIAN
		vptr+=size-sizeof(jlong);
#endif

	for (jsize i = 0; i < arrayLen; i++) {
		jlong* pptr = (jlong*) vptr;
		bPtr[arrayOff+i] = pptr[0];
		vptr+=size;
	}

	(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
}

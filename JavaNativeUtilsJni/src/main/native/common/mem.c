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
#include "jni/eu_aschuetz_nativeutils_impl_JNINativeMemory.h"
#include "timeutil.h"
#include "common.h"
#include <stdbool.h>
#include <stddef.h>
#include "atomics.h"
#include <string.h>
#include "endianutil.h"
#include <assert.h>



/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    supportsCompareAndSet16Byte
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_supportsCompareAndSet16Byte
  (JNIEnv * env, jobject inst) {
	return supports_cmpxchg16b();
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    supportsCompareAndSet8Byte
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_supportsCompareAndSet8Byte
        (JNIEnv * env, jobject inst) {
    return supports_cmpxchg8b();
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet8ByteAlignment
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_compareAndSet8ByteAlignment
        (JNIEnv * env, jobject inst) {
    return ATOMIC_ALIGNMENT_cmpxchg8b;
}



/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    supportsCompareAndSet4Byte
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_supportsCompareAndSet4Byte
        (JNIEnv * env, jobject inst) {
    return supports_cmpxchg4b();
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet4ByteAlignment
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_compareAndSet4ByteAlignment
        (JNIEnv * env, jobject inst) {
    return ATOMIC_ALIGNMENT_cmpxchg4b;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    supportsCompareAndSet2Byte
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_supportsCompareAndSet2Byte
        (JNIEnv * env, jobject inst) {
    return supports_cmpxchg2b();
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet2ByteAlignment
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_compareAndSet2ByteAlignment
        (JNIEnv * env, jobject inst) {
    return ATOMIC_ALIGNMENT_cmpxchg2b;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    supportsCompareAndSet1Byte
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_supportsCompareAndSet1Byte
        (JNIEnv * env, jobject inst) {
    return supports_cmpxchg1b();
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet1ByteAlignment
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_compareAndSet1ByteAlignment
        (JNIEnv * env, jobject inst) {
    return ATOMIC_ALIGNMENT_cmpxchg1b;
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    atomic8ByteOperationsRequireAlignment
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_atomic8ByteOperationsRequireAlignment
  (JNIEnv * env, jobject inst) {
#if defined(__amd64__)
	return false;
#else
	return true;
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    off
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_off
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJ[BII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_write__JJ_3BII
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJB)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_write__JJB
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_write__JJI
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jint value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;
#if (defined(__mips64))
    memcpy(vptr, (void*) &value, 4);
#else
    volatile jint* dptr = (jint*) vptr;
	*(dptr) = value;
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJJ)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_write__JJJ
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jlong value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
	vptr+=(uintptr_t) off;

#if (defined(__arm__) || defined(__mips64))
    memcpy(vptr, (void*) &value, 8);
#else
    //Causes SIGBUS on arm 32 bit.
    volatile jlong* dptr = (jlong*) vptr;
    *(dptr) = value;

#endif


}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJF)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_write__JJF
	(JNIEnv *env, jclass clazz, jlong ptr, jlong off, jfloat value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
    vptr+=(uintptr_t) off;

#if (defined(__arm__) || defined(__mips64))
    memcpy(vptr, (void*) &value, 4);
#else
    //Causes SIGBUS on arm 32 bit.
    volatile jfloat* dptr = (jfloat*) vptr;
    *(dptr) = value;
#endif

}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJD)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_write__JJD
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jdouble value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

    vptr+=(uintptr_t) off;
#if (defined(__arm__) || defined(__mips64))
    memcpy(vptr, (void*) &value, 8);
#else
    //Causes SIGBUS on arm 32 bit.
    volatile jdouble* dptr = (jdouble*) vptr;
    *(dptr) = value;
#endif




}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    write
 * Signature: (JJS)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_write__JJS
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jshort value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}
    vptr+=(uintptr_t) off;
#if (defined(__mips64))
    memcpy(vptr, (void*) &value, 2);
#else
	volatile jshort* dptr = (jshort*) vptr;
	*(dptr) = value;
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    read
 * Signature: (JJ[BII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_read
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readInt
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readInt
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
    vptr+=(uintptr_t) off;
#if (defined(__mips64))
    jint result;
    memcpy((void*) &result, vptr, 4);
    return result;
#else
	volatile jint* dptr = (jint*) vptr;
	return *dptr;
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readLong
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readLong
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}

    vptr+=(uintptr_t) off;

#if (defined(__arm__) || defined(__mips64))
    jlong result;
    memcpy((void*) &result, vptr, 8);
    return result;
#else
    //Causes SIGBUS on arm 32 bit.
    volatile jlong* dptr = (jlong*) vptr;
    return *dptr;
#endif


}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readFloat
 * Signature: (JJ)F
 */
JNIEXPORT jfloat JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readFloat
  (JNIEnv *env , jclass clazz, jlong ptr, jlong off) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(__arm__) || defined(__mips64))
    jfloat result;
    memcpy((void*) &result, vptr, 4);
    return result;
#else
    //Causes SIGBUS on arm 32 bit.
    volatile jfloat* dptr = (jfloat*) vptr;
    return *dptr;
#endif


}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readDouble
 * Signature: (JJ)D
 */
JNIEXPORT jdouble JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readDouble
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(__arm__) || defined(__mips64))
    jdouble result;
    memcpy((void*) &result, vptr, 8);
    return result;
#else
    //Causes SIGBUS on arm 32 bit.
    volatile jdouble* dptr = (jdouble*) vptr;
    return *dptr;
#endif

}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readShort
 * Signature: (JJ)S
 */
JNIEXPORT jshort JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readShort
  (JNIEnv *env , jclass clazz, jlong ptr, jlong off) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(__mips64))
    jshort result;
    memcpy((void*) &result, vptr, 2);
    return result;
#else
    volatile jshort* dptr = (jshort*) vptr;
	return *dptr;
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readByte
 * Signature: (JJ)B
 */
JNIEXPORT jbyte JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readByte
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    set
 * Signature: (JJBJ)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_set
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    getAndAdd
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_getAndAdd__JJJ
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jlong value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(ATOMIC_NO_cmpxchg8b))
    jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 8 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg8b))
    if (!supports_cmpxchg8b()) {
        jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 8 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg8b))
    if (!aligned_cmpxchg8b((uint64_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "getAndAdd 8 byte address is not suitably aligned");
        return false;
    }
#endif
    return (jlong) xadd8b((uint64_t *) vptr, (uint64_t) value);
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    getAndAdd
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_getAndAdd__JJI
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jint value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(ATOMIC_NO_cmpxchg4b))
    jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 4 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg4b))
    if (!supports_cmpxchg4b()) {
        jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 4 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg4b))
    if (!aligned_cmpxchg4b((uint32_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "getAndAdd 4 byte address is not suitably aligned");
        return false;
    }
#endif
    return (jint) xadd4b((uint32_t *) vptr, (uint32_t) value);
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    getAndAdd
 * Signature: (JJS)S
 */
JNIEXPORT jshort JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_getAndAdd__JJS
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jshort value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(ATOMIC_NO_cmpxchg2b))
    jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 2 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg2b))
    if (!supports_cmpxchg2b()) {
        jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 2 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg2b))
    if (!aligned_cmpxchg2b((uint16_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "getAndAdd 2 byte address is not suitably aligned");
        return false;
    }
#endif
    return (jshort) xadd2b((uint16_t *) vptr, (uint16_t) value);
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    getAndAdd
 * Signature: (JJB)B
 */
JNIEXPORT jbyte JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_getAndAdd__JJB
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jbyte value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(ATOMIC_NO_cmpxchg1b))
    jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 1 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg1b))
    if (!supports_cmpxchg1b()) {
        jthrowCC_UnsupportedOperationException_1(env, "getAndAdd 1 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg1b))
    if (!aligned_cmpxchg1b((uint8_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "getAndAdd 1 byte address is not suitably aligned");
        return false;
    }
#endif
    return (jbyte) xadd1b((uint8_t *) vptr, (uint8_t) value);
#endif
};

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    getAndSet
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_getAndSet__JJJ
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jlong value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;

#if (defined(ATOMIC_NO_cmpxchg8b))
    jthrowCC_UnsupportedOperationException_1(env, "getAndSet 8 byte not supported by cpu");
    return 0;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg8b))
    if (!supports_cmpxchg8b()) {
        jthrowCC_UnsupportedOperationException_1(env, "getAndSet 8 byte not supported by cpu");
        return 0;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg8b))
    if (!aligned_cmpxchg8b((uint64_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "getAndSet 8 byte address is not suitably aligned");
        return 0;
    }
#endif
    return (jlong) xchg8b((uint64_t *)vptr, (uint64_t) value);
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    getAndSet
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_getAndSet__JJI
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jint value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(ATOMIC_NO_cmpxchg4b))
    jthrowCC_UnsupportedOperationException_1(env, "getAndSet 4 byte not supported by cpu");
    return 0;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg4b))
    if (!supports_cmpxchg4b()) {
        jthrowCC_UnsupportedOperationException_1(env, "getAndSet 4 byte not supported by cpu");
        return 0;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg4b))
    if (!aligned_cmpxchg4b((uint32_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "getAndSet 4 byte address is not suitably aligned");
        return 0;
    }
#endif
    return (jint) xchg4b((uint32_t *)vptr, (uint32_t) value);
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    getAndSet
 * Signature: (JJS)S
 */
JNIEXPORT jshort JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_getAndSet__JJS
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jshort value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(ATOMIC_NO_cmpxchg2b))
    jthrowCC_UnsupportedOperationException_1(env, "getAndSet 2 byte not supported by cpu");
    return 0;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg2b))
    if (!supports_cmpxchg2b()) {
        jthrowCC_UnsupportedOperationException_1(env, "getAndSet 2 byte not supported by cpu");
        return 0;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg2b))
    if (!aligned_cmpxchg2b((uint16_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "getAndSet 2 byte address is not suitably aligned");
        return 0;
    }
#endif
    return (jshort) xchg2b((uint16_t *)vptr, (uint16_t) value);
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    getAndSet
 * Signature: (JJB)B
 */
JNIEXPORT jbyte JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_getAndSet__JJB
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jbyte value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(ATOMIC_NO_cmpxchg1b))
    jthrowCC_UnsupportedOperationException_1(env, "getAndSet 1 byte not supported by cpu");
    return 0;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg1b))
    if (!supports_cmpxchg1b()) {
        jthrowCC_UnsupportedOperationException_1(env, "getAndSet 1 byte not supported by cpu");
        return 0;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg1b))
    if (!aligned_cmpxchg1b((uint8_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "getAndSet 1 byte address is not suitably aligned");
        return 0;
    }
#endif
    return (jbyte) xchg1b((uint8_t *)vptr, (uint8_t) value);
#endif
}


//179

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet
 * Signature: (JJJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_compareAndSet__JJJJ
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jlong expect, jlong update) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;

#if (defined(ATOMIC_NO_cmpxchg8b))
    jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 8 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg8b))
    if (!supports_cmpxchg8b()) {
        jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 8 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg8b))
    if (!aligned_cmpxchg8b((uint64_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "compareAndSet 8 byte address is not suitably aligned");
        return false;
    }
#endif
    return cmpxchg8b((uint64_t *)vptr, (uint64_t) expect, (uint64_t) update);
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet
 * Signature: (JJII)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_compareAndSet__JJII
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jint expect, jint update) {

    void * vptr = (void *) (uintptr_t) ptr;
    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return 0;
    }
    vptr+=(uintptr_t) off;

#if (defined(ATOMIC_NO_cmpxchg4b))
    jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 4 byte not supported by cpu");
    return false;
#else
    #if (defined(ATOMIC_OPTIONAL_cmpxchg4b))
    if (!supports_cmpxchg4b()) {
        jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 4 byte not supported by cpu");
        return false;
    }
    #endif
    #if (defined(ATOMIC_ALIGNED_cmpxchg4b))
    if (!aligned_cmpxchg4b((uint32_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "compareAndSet 4 byte address is not suitably aligned");
        return false;
    }
    #endif
    return cmpxchg4b((uint32_t *) vptr, (uint32_t) expect, (uint32_t) update);
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet
 * Signature: (JJSS)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_compareAndSet__JJSS
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jshort expect, jshort update) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(ATOMIC_NO_cmpxchg2b))
    jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 2 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg2b))
    if (!supports_cmpxchg2b()) {
        jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 2 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg2b))
    if (!aligned_cmpxchg2b((uint16_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "compareAndSet 2 byte address is not suitably aligned");
        return false;
    }
#endif
    return cmpxchg2b((uint16_t *) vptr, (uint16_t) expect, (uint16_t) update);
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet
 * Signature: (JJBB)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_compareAndSet__JJBB
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jbyte expect, jbyte update) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
	vptr+=(uintptr_t) off;
#if (defined(ATOMIC_NO_cmpxchg1b))
    jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 1 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg2b))
    if (!supports_cmpxchg1b()) {
        jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 1 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg1b))
    if (!aligned_cmpxchg1b((uint8_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "compareAndSet 1 byte address is not suitably aligned");
        return false;
    }
#endif
    return cmpxchg1b((uint8_t *) vptr, (uint8_t) expect, (uint8_t) update);
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    compareAndSet
 * Signature: (JJ[B)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_compareAndSet__JJ_3B
  (JNIEnv *env, jclass clazz, jlong ptr, jlong off, jbyteArray value) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}
    if (value == NULL) {
        jthrowCC_NullPointerException_1(env, "value");
        return 0;
    }

    if ((*env)->GetArrayLength(env, value) != 32) {
        jthrowCC_IllegalArgumentException_1(env, "value.length != 32");
        return 0;
    }

	vptr+=(uintptr_t) off;

#if (defined(ATOMIC_NO_cmpxchg16b))
    jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 16 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg16b))
    if (!supports_cmpxchg16b()) {
        jthrowCC_UnsupportedOperationException_1(env, "compareAndSet 16 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg16b))
    if (!aligned_cmpxchg16b((uint64_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "compareAndSet 16 byte address is not suitably aligned");
        return false;
    }
#endif
    jbyte critical[32];

    (*env)->GetByteArrayRegion(env, value, 0, 32, critical);

    uint64_t* data = (uint64_t*) critical;

    return cmpxchg16b((uint64_t *)vptr, data);
#endif
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJJJJJLjava/nio/ByteBuffer;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spinAndSet__JJJJJJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jlong expect, jlong update, jlong spinTime, jlong aTimeout, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return false;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return false;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return false;
    }

    vptr += off;

#if (defined(ATOMIC_NO_cmpxchg8b))
    jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 8 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg8b))
    if (!supports_cmpxchg8b()) {
        jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 8 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg8b))
    if (!aligned_cmpxchg8b((uint64_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "spinAndSet 8 byte address is not suitably aligned");
        return false;
    }
#endif
    if (cmpxchg8b((uint64_t*) vptr, (uint64_t) expect, (uint64_t) update)) {
        return true;
    }

    uint64_t start = currentTimeMillis();
    uint64_t now = start;

    while(true) {
        if (now < start) {
            return false;
        }

        uint64_t expired = now-start;

        if (expired >= aTimeout) {
            return false;
        }

        if (cmpxchg8b((uint64_t*) vptr, expect, update)) {
            return true;
        }

        if (*spinG != 0) {
            jthrowCC_NullPointerException_1(env, "closed");
            return false;
        }

        if (spinTime > 0) {
            if (spinTime >= aTimeout-expired) {
                return false;
            }
            sleepMillis(spinTime);
        }

        now = currentTimeMillis();
    }
#endif
}
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJJJJLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spinAndSet__JJJJJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jlong expect, jlong update, jlong spinTime, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return;
    }

    vptr += off;

#if (defined(ATOMIC_NO_cmpxchg8b))
    jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 8 byte not supported by cpu");
    return;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg8b))
    if (!supports_cmpxchg8b()) {
        jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 8 byte not supported by cpu");
        return;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg8b))
    if (!aligned_cmpxchg8b((uint64_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "spinAndSet 8 byte address is not suitably aligned");
        return;
    }
#endif
    while(true) {
        if (cmpxchg8b((uint64_t*) vptr, (uint64_t) expect, (uint64_t) update)) {
            return;
        }

        if (*spinG != 0) {
            jthrowCC_NullPointerException_1(env, "closed");
            return;
        }

        if (spinTime > 0) {
            sleepMillis(spinTime);
        }
    }
#endif
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJJJJLjava/nio/ByteBuffer;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spin__JJJJJLjava_nio_ByteBuffer_2
        (JNIEnv *env, jobject inst, jlong ptr, jlong off, jlong expect, jlong spinTime, jlong aTimeout, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return false;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return false;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return false;
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

        if (*spinG != 0) {
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJJJLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spin__JJJJLjava_nio_ByteBuffer_2
        (JNIEnv *env, jobject inst, jlong ptr, jlong off, jlong expect, jlong spinTime, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return;
    }

    vptr += off;
    volatile uint64_t * iptr = (uint64_t *) vptr;

    while(*iptr != expect) {
        if (*spinG != 0) {
            jthrowCC_NullPointerException_1(env, "closed");
            return;
        }

        if (spinTime > 0) {
            sleepMillis(spinTime);
        }
    }
}
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJIIJJLjava/nio/ByteBuffer;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spinAndSet__JJIIJJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jint expect, jint update, jlong spinTime, jlong aTimeout, jobject spinGuard) {


    void * vptr = (void *) (uintptr_t) ptr;
    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return false;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return false;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return false;
    }

    vptr+=(uintptr_t) off;

#if (defined(ATOMIC_NO_cmpxchg4b))
    jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 4 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg4b))
    if (!supports_cmpxchg4b()) {
        jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 4 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg4b))
    if (!aligned_cmpxchg4b((uint32_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "spinAndSet 4 byte address is not suitably aligned");
        return false;
    }
#endif
    if (cmpxchg4b((uint32_t *) vptr, (uint32_t) expect, (uint32_t) update)) {
        return true;
    }

    uint64_t start = currentTimeMillis();
    uint64_t now = start;

    while(true) {
        if (now < start) {
            return false;
        }

        uint64_t expired = now-start;

        if (expired >= aTimeout) {
            return false;
        }

        if (cmpxchg4b((uint32_t *) vptr, (uint32_t) expect, (uint32_t) update)) {
            return true;
        }

        if (*spinG != 0) {
            jthrowCC_NullPointerException_1(env, "closed");
            return false;
        }

        if (spinTime > 0) {
            if (spinTime >= aTimeout-expired) {
                return false;
            }
            sleepMillis(spinTime);
        }

        now = currentTimeMillis();
    }
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJIIJLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spinAndSet__JJIIJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jint expect, jint update, jlong spinTime, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;
    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return;
    }

    vptr+=(uintptr_t) off;

#if (defined(ATOMIC_NO_cmpxchg4b))
    jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 4 byte not supported by cpu");
    return;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg4b))
    if (!supports_cmpxchg4b()) {
        jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 4 byte not supported by cpu");
        return;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg4b))
    if (!aligned_cmpxchg4b((uint32_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "spinAndSet 4 byte address is not suitably aligned");
        return;
    }
#endif
    while(true) {
        if (cmpxchg4b((uint32_t *) vptr, (uint32_t) expect, (uint32_t) update)) {
            return;
        }

        if (*spinG != 0) {
            jthrowCC_NullPointerException_1(env, "closed");
            return;
        }

        if (spinTime > 0) {
            sleepMillis(spinTime);
        }
    }
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJIJJLjava/nio/ByteBuffer;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spin__JJIJJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jint expect, jlong spinTime, jlong aTimeout, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return false;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return false;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return false;
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

        if (*spinG != 0) {
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJIJLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spin__JJIJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jint expect, jlong spinTime, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return;
    }

    vptr += off;
    volatile uint32_t * iptr = (uint32_t *) vptr;

    while(*iptr != expect) {
        if (*spinG != 0) {
            jthrowCC_NullPointerException_1(env, "closed");
            return;
        }

        if (spinTime > 0) {
            sleepMillis(spinTime);
        }
    }
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJSSJJLjava/nio/ByteBuffer;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spinAndSet__JJSSJJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jshort expect, jshort update, jlong spinTime, jlong aTimeout, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return false;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return false;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return false;
    }

    vptr += off;

#if (defined(ATOMIC_NO_cmpxchg2b))
    jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 2 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg2b))
    if (!supports_cmpxchg2b()) {
        jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 2 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg2b))
    if (!aligned_cmpxchg2b((uint16_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "spinAndSet 2 byte address is not suitably aligned");
        return false;
    }
#endif
    if (cmpxchg2b((uint16_t*) vptr, (uint16_t) expect, (uint16_t) update)) {
        return true;
    }

    uint64_t start = currentTimeMillis();
    uint64_t now = start;

    while(true) {
        if (now < start) {
            return false;
        }

        uint16_t expired = now-start;

        if (expired >= aTimeout) {
            return false;
        }

        if (cmpxchg2b((uint16_t*) vptr, expect, update)) {
            return true;
        }

        if (*spinG != 0) {
            jthrowCC_NullPointerException_1(env, "closed");
            return false;
        }

        if (spinTime > 0) {
            if (spinTime >= aTimeout-expired) {
                return false;
            }
            sleepMillis(spinTime);
        }

        now = currentTimeMillis();
    }
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJSSJLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spinAndSet__JJSSJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jshort expect, jshort update, jlong spinTime, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return;
    }

    vptr += off;

#if (defined(ATOMIC_NO_cmpxchg2b))
    jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 2 byte not supported by cpu");
    return;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg2b))
    if (!supports_cmpxchg2b()) {
        jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 2 byte not supported by cpu");
        return;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg2b))
    if (!aligned_cmpxchg2b((uint16_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "spinAndSet 2 byte address is not suitably aligned");
        return;
    }
#endif
    while(true) {
        if (cmpxchg2b((uint16_t *) vptr, (uint16_t) expect, (uint16_t) update)) {
            return;
        }

        if (*spinG != 0) {
            jthrowCC_NullPointerException_1(env, "closed");
            return;
        }

        if (spinTime > 0) {
            sleepMillis(spinTime);
        }
    }
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJSJJLjava/nio/ByteBuffer;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spin__JJSJJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jshort expect, jlong spinTime, jlong aTimeout, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return false;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return false;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return false;
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

        if (*spinG != 0) {
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJSJLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spin__JJSJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jshort expect, jlong spinTime, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return;
    }

    vptr += off;
    volatile uint16_t * iptr = (uint16_t *) vptr;

    while(*iptr != expect) {
        if (*spinG != 0) {
            jthrowCC_NullPointerException_1(env, "closed");
            return;
        }

        if (spinTime > 0) {
            sleepMillis(spinTime);
        }
    }
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJBBJJLjava/nio/ByteBuffer;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spinAndSet__JJBBJJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jbyte expect, jbyte update, jlong spinTime, jlong aTimeout, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return false;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return false;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return false;
    }

    vptr += off;

#if (defined(ATOMIC_NO_cmpxchg1b))
    jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 1 byte not supported by cpu");
    return false;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg1b))
    if (!supports_cmpxchg1b()) {
        jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 1 byte not supported by cpu");
        return false;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg1b))
    if (!aligned_cmpxchg2b((uint8_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "spinAndSet 1 byte address is not suitably aligned");
        return false;
    }
#endif
    if (cmpxchg1b((uint8_t*) vptr, (uint8_t) expect, (uint8_t) update)) {
        return true;
    }

    uint64_t start = currentTimeMillis();
    uint64_t now = start;

    while(true) {
        if (now < start) {
            return false;
        }

        uint64_t expired = now-start;

        if (expired >= aTimeout) {
            return false;
        }

        if (cmpxchg1b((uint8_t*) vptr, (uint8_t) expect, (uint8_t) update)) {
            return true;
        }

        if (*spinG != 0) {
            jthrowCC_NullPointerException_1(env, "closed");
            return false;
        }

        if (spinTime > 0) {
            if (spinTime >= aTimeout-expired) {
                return false;
            }
            sleepMillis(spinTime);
        }

        now = currentTimeMillis();
    }
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spinAndSet
 * Signature: (JJBBJLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spinAndSet__JJBBJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jbyte expect, jbyte update, jlong spinTime, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return;
    }

    vptr += off;

#if (defined(ATOMIC_NO_cmpxchg1b))
    jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 1 byte not supported by cpu");
    return;
#else
#if (defined(ATOMIC_OPTIONAL_cmpxchg1b))
    if (!supports_cmpxchg1b()) {
        jthrowCC_UnsupportedOperationException_1(env, "spinAndSet 1 byte not supported by cpu");
        return;
    }
#endif
#if (defined(ATOMIC_ALIGNED_cmpxchg1b))
    if (!aligned_cmpxchg1b((uint16_t *) vptr)) {
        jthrowCC_IllegalArgumentException_1(env, "spinAndSet 1 byte address is not suitably aligned");
        return;
    }
#endif
    while(true) {
        if (cmpxchg1b((uint8_t *) vptr, (uint8_t) expect, (uint8_t) update)) {
            return;
        }

        if (*spinG != 0) {
            jthrowCC_NullPointerException_1(env, "closed");
            return;
        }

        if (spinTime > 0) {
            sleepMillis(spinTime);
        }
    }
#endif
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJBJJLjava/nio/ByteBuffer;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spin__JJBJJLjava_nio_ByteBuffer_2
        (JNIEnv * env, jobject inst, jlong ptr, jlong off, jbyte expect, jlong spinTime, jlong aTimeout, jobject spinGuard) {
    void * vptr = (void *) (uintptr_t) ptr;

    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return false;
    }

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return false;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return false;
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

        if (*spinG != 0) {
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    spin
 * Signature: (JJBJLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_spin__JJBJLjava_nio_ByteBuffer_2
  (JNIEnv * env, jobject inst, jlong ptr, jlong off, jbyte expect, jlong spinTime, jobject spinGuard) {
	void * vptr = (void *) (uintptr_t) ptr;

	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

    if (spinGuard == NULL) {
        jthrowCC_NullPointerException_1(env, "spinGuard");
        return;
    }

    volatile uint8_t* spinG = (volatile uint8_t*) (*env)->GetDirectBufferAddress(env, spinGuard);

    if (spinG == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetDirectBufferAddress");
        return;
    }

	vptr += off;
	volatile uint8_t * iptr = (uint8_t *) vptr;

	while(*iptr != expect) {
		if (*spinG != 0) {
			jthrowCC_NullPointerException_1(env, "closed");
			return;
		}

		if (spinTime > 0) {
			sleepMillis(spinTime);
		}
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    memmove
 * Signature: (JJJJ)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_memmove
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readBuffer
 * Signature: (JJLjava/nio/ByteBuffer;II)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readBuffer
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    writeBuffer
 * Signature: (JJLjava/nio/ByteBuffer;II)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_writeBuffer
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    indexOf
 * Signature: (JJJB)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_indexOf
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readUntilByte
 * Signature: (JJIB[BI)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readUntilByte
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
	if (max >= 512) {
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

	jbyte stack[512];

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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    writeDoubleArray
 * Signature: (JJ[DII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_writeDoubleArray
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    writeFloatArray
 * Signature: (JJ[FII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_writeFloatArray
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    writeExpandedByteArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_writeExpandedByteArray
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

    const size_t valSize = sizeof(jbyte);
    const size_t psize = size-valSize;

#if BYTE_ORDER == BIG_ENDIAN
    for (jsize i = 0; i < arrayLen; i++) {
        memset(vptr, 0, psize);
        vptr+=psize;
        *((jbyte*)vptr) = bPtr[arrayOff+i];
        vptr+=valSize;
    }
#elif BYTE_ORDER == LITTLE_ENDIAN
    for (jsize i = 0; i < arrayLen; i++) {
        *((jbyte*)vptr) = bPtr[arrayOff+i];
        vptr+=valSize;
        memset(vptr, 0, psize);
        vptr+=psize;
    }
#else
    #error
#endif

    (*env)->ReleaseByteArrayElements(env, array, bPtr, JNI_ABORT);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    writeExpandedCharArray
 * Signature: (JJ[CIII)V
 */


JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_writeExpandedCharArray
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
#if (defined(__mips64))
        if ((((uintptr_t )vptr) & 0x1) != 0) {
            jshort* carray = (*env)->GetCharArrayElements(env, array, NULL);
            if (carray == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "GetCharArrayElements");
                return;
            }
            memcpy(vptr, (void*) &carray[arrayOff], arrayLen*2);
            (*env)->ReleaseCharArrayElements(env, array, carray, JNI_ABORT);
            return;
        }
#endif
		(*env)->GetCharArrayRegion(env, array, arrayOff, arrayLen, (jchar*) vptr);
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
            pptr[i] = (jbyte) bPtr[arrayOff+i];
        }

        (*env)->ReleaseCharArrayElements(env, array, bPtr, JNI_ABORT);
        return;
	}

    const size_t valSize = sizeof(jchar);
    const size_t psize = size-valSize;

#if BYTE_ORDER == BIG_ENDIAN
    for (jsize i = 0; i < arrayLen; i++) {
        memset(vptr, 0, psize);
        vptr+=psize;
        *((jchar*)vptr) = bPtr[arrayOff+i];
        vptr+=valSize;
    }
#elif BYTE_ORDER == LITTLE_ENDIAN
    for (jsize i = 0; i < arrayLen; i++) {
#if (defined(__mips64))
        memcpy(vptr, (void*) &bPtr[arrayOff+i], valSize);
#else
        //Causes SIGBUS on mips.
        *((jchar*)vptr) = bPtr[arrayOff+i];
#endif
        vptr+=valSize;
        memset(vptr, 0, psize);
        vptr+=psize;
    }
#else
    #error
#endif
    (*env)->ReleaseCharArrayElements(env, array, bPtr, JNI_ABORT);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    writeExpandedShortArray
 * Signature: (JJ[SIII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_writeExpandedShortArray
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
#if (defined(__mips64))
        if ((((uintptr_t )vptr) & 0x1) != 0) {
            jshort* carray = (*env)->GetShortArrayElements(env, array, NULL);
            if (carray == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "GetShortArrayElements");
                return;
            }
            memcpy(vptr, (void*) &carray[arrayOff], arrayLen*2);
            (*env)->ReleaseShortArrayElements(env, array, carray, JNI_ABORT);
            return;
        }
#endif
		(*env)->GetShortArrayRegion(env, array, arrayOff, arrayLen, (jshort*) vptr);
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
            pptr[i] = (jbyte) bPtr[arrayOff+i];
        }

        (*env)->ReleaseShortArrayElements(env, array, bPtr, JNI_ABORT);
        return;
	}


    const size_t valSize = sizeof(jshort);
    const size_t psize = size-valSize;

#if BYTE_ORDER == BIG_ENDIAN
    for (jsize i = 0; i < arrayLen; i++) {
        memset(vptr, 0, psize);
        vptr+=psize;
        *((jshort*)vptr) = bPtr[arrayOff+i];
        vptr+=valSize;
    }
#elif BYTE_ORDER == LITTLE_ENDIAN
    for (jsize i = 0; i < arrayLen; i++) {
#if (defined(__mips64))
        memcpy(vptr, (void*) &bPtr[arrayOff+i], valSize);
#else
        //Causes SIGBUS on mips.
        *((jshort*)vptr) = bPtr[arrayOff+i];
#endif

        vptr+=valSize;
        memset(vptr, 0, psize);
        vptr+=psize;
    }
#else
    #error
#endif

    (*env)->ReleaseShortArrayElements(env, array, bPtr, JNI_ABORT);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    writeExpandedIntArray
 * Signature: (JJ[IIII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_writeExpandedIntArray
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
#if (defined(__mips64))
        if ((((uintptr_t )vptr) & 0x3) != 0) {
            jint* carray = (*env)->GetIntArrayElements(env, array, NULL);
            if (carray == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "GetIntArrayElements");
                return;
            }
            memcpy(vptr, (void*) &carray[arrayOff], arrayLen*4);
            (*env)->ReleaseIntArrayElements(env, array, carray, JNI_ABORT);
            return;
        }
#endif
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
				pptr[i] = (jbyte) bPtr[arrayOff+i];
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (2): {
#if (defined(__mips64))
            if ((((uintptr_t)vptr) & 0x1) != 0) {
                uint8_t* pptr = (uint8_t *) vptr;
                for (jsize i, c = 0; i < arrayLen*2; i+=2) {
                    uint32_t acc = (uint32_t) bPtr[arrayOff+c++];
                    pptr[i+0] = (uint8_t) ((acc >> 0) & 0xFF);
                    pptr[i+1] = (uint8_t) ((acc >> 8) & 0xFF);
                }
                (*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_ABORT);
			    return;
            }
#endif
			uint16_t* pptr = (uint16_t*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				pptr[i] = (uint16_t) bPtr[arrayOff+i];
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (3): {
#if (defined(__mips64))
            uint8_t* pptr = (uint8_t *) vptr;
            for (jsize i, c = 0; i < arrayLen*3; i+=3) {
                uint32_t acc = (uint32_t) bPtr[arrayOff+c++];
                pptr[i+0] = (uint8_t) ((acc >>  0) & 0xFF);
                pptr[i+1] = (uint8_t) ((acc >>  8) & 0xFF);
                pptr[i+2] = (uint8_t) ((acc >> 16) & 0xFF);
            }
            (*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_ABORT);
            return;
#else
			for (jsize i = 0; i < arrayLen; i++) {
				uint32_t u32 = (uint32_t) bPtr[arrayOff+i];
#if BYTE_ORDER == LITTLE_ENDIAN
                *((uint16_t*) (vptr+0)) = (uint16_t) u32;
                *((uint8_t*)  (vptr+2)) = (uint8_t) (u32 >> 16);
#elif BYTE_ORDER == BIG_ENDIAN
                *((uint16_t*) (vptr+1)) = (uint16_t) u32;
                *((uint8_t*)  (vptr+0)) = (uint8_t) (u32 >> 16);
#else
                #error
#endif
                vptr+=3;
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_ABORT);
			return;
#endif
		}
        default:
            break;
	}


    const size_t valSize = sizeof(jint);
	const size_t psize = size-valSize;

#if BYTE_ORDER == BIG_ENDIAN
    for (jsize i = 0; i < arrayLen; i++) {
        memset(vptr, 0, psize);
        vptr+=psize;
        *((jint*)vptr) = bPtr[arrayOff+i];
        vptr+=valSize;
    }
#elif BYTE_ORDER == LITTLE_ENDIAN
    for (jsize i = 0; i < arrayLen; i++) {
#if (defined(__mips64))
        memcpy(vptr, (void*) &bPtr[arrayOff+i], valSize);
#else
        //Causes SIGBUS on mips.
        *((jint*)vptr) = bPtr[arrayOff+i];
#endif

        vptr+=valSize;
        memset(vptr, 0, psize);
        vptr+=psize;
    }
#else
    #error
#endif

    (*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_ABORT);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    writeExpandedLongArray
 * Signature: (JJ[JIII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_writeExpandedLongArray
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
#if (defined(__arm__) || defined(__mips64))
        if ((((uintptr_t )vptr) & 0x7) != 0) {
            jlong* carray = (*env)->GetLongArrayElements(env, array, NULL);
            if (carray == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "GetLongArrayElements");
                return;
            }
            memcpy(vptr, (void*) &carray[arrayOff], arrayLen*8);
            (*env)->ReleaseLongArrayElements(env, array, carray, JNI_ABORT);
            return;
        }

#endif
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
				pptr[i] = (jbyte) bPtr[arrayOff+i];
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (2): {
#if (defined(__mips64))
            if ((((uintptr_t)vptr) & 0x1) != 0) {
                uint8_t* pptr = (uint8_t *) vptr;
                for (jsize i, c = 0; i < arrayLen*2; i+=2) {
                    uint64_t acc = (uint64_t) bPtr[arrayOff+c++];
                    pptr[i+0] = (uint8_t) ((acc >> 0) & 0xFF);
                    pptr[i+1] = (uint8_t) ((acc >> 8) & 0xFF);
                }
                (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			    return;
            }
#endif
            uint16_t* pptr = (uint16_t*) vptr;
            for (jsize i = 0; i < arrayLen; i++) {
                pptr[i] = (uint16_t) bPtr[arrayOff+i];
            }

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (3): {
#if (defined(__mips64))
            uint8_t* pptr = (uint8_t *) vptr;
            for (jsize i, c = 0; i < arrayLen*3; i+=3) {
                uint64_t acc = (uint64_t) bPtr[arrayOff+c++];
                pptr[i+0] = (uint8_t) ((acc >>  0) & 0xFF);
                pptr[i+1] = (uint8_t) ((acc >>  8) & 0xFF);
                pptr[i+2] = (uint8_t) ((acc >> 16) & 0xFF);
            }
            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
            return;
#else
            for (jsize i = 0; i < arrayLen; i++) {
                uint32_t u32 = (uint32_t) bPtr[arrayOff+i];
#if BYTE_ORDER == LITTLE_ENDIAN
                *((uint16_t*) (vptr+0)) = (uint16_t) u32;
                *((uint8_t*)  (vptr+2)) = (uint8_t) (u32 >> 16);
#elif BYTE_ORDER == BIG_ENDIAN
                *((uint16_t*) (vptr+1)) = (uint16_t) u32;
                *((uint8_t*)  (vptr+0)) = (uint8_t) (u32 >> 16);
#else
                #error
#endif
                vptr+=3;
            }

            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
            return;
#endif
		}
		case (4): {
#if (defined(__mips64))
            if ((((uintptr_t)vptr) & 0x3) != 0) {
                uint8_t* pptr = (uint8_t *) vptr;
                for (jsize i, c = 0; i < arrayLen*4; i+=4) {
                    uint64_t acc = (uint64_t) bPtr[arrayOff+c++];
                    pptr[i+0] = (uint8_t) ((acc >>  0) & 0xFF);
                    pptr[i+1] = (uint8_t) ((acc >>  8) & 0xFF);
                    pptr[i+2] = (uint8_t) ((acc >> 16) & 0xFF);
                    pptr[i+3] = (uint8_t) ((acc >> 24) & 0xFF);
                }
                (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			    return;
            }
#endif
			uint32_t* pptr = (uint32_t*) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				pptr[i] = (uint32_t) bPtr[arrayOff+i];
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
		}
		case (5): {
#if (defined(__mips64))
            uint8_t* pptr = (uint8_t *) vptr;
            for (jsize i, c = 0; i < arrayLen*5; i+=5) {
                uint64_t acc = (uint64_t) bPtr[arrayOff+c++];
                pptr[i+0] = (uint8_t) ((acc >>  0) & 0xFF);
                pptr[i+1] = (uint8_t) ((acc >>  8) & 0xFF);
                pptr[i+2] = (uint8_t) ((acc >> 16) & 0xFF);
                pptr[i+3] = (uint8_t) ((acc >> 24) & 0xFF);
                pptr[i+4] = (uint8_t) ((acc >> 32) & 0xFF);
            }
            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
            return;
#else
			for (jsize i = 0; i < arrayLen; i++) {
				uint64_t u64 = (uint64_t) bPtr[arrayOff+i];
#if BYTE_ORDER == LITTLE_ENDIAN
                *((uint32_t*) (vptr+0)) = (uint32_t) u64;
                *((uint8_t*)  (vptr+4)) = (uint8_t) (u64 >> 32);
#elif BYTE_ORDER == BIG_ENDIAN
                *((uint32_t*) (vptr+1)) = (uint32_t) u64;
                *((uint8_t*)  (vptr+0)) = (uint8_t) (u64 >> 32);
#else
                #error
#endif
                vptr+=5;
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
#endif
		}
		case (6): {
#if (defined(__mips64))
            uint8_t* pptr = (uint8_t *) vptr;
            for (jsize i, c = 0; i < arrayLen*6; i+=6) {
                uint64_t acc = (uint64_t) bPtr[arrayOff+c++];
                pptr[i+0] = (uint8_t) ((acc >>  0) & 0xFF);
                pptr[i+1] = (uint8_t) ((acc >>  8) & 0xFF);
                pptr[i+2] = (uint8_t) ((acc >> 16) & 0xFF);
                pptr[i+3] = (uint8_t) ((acc >> 24) & 0xFF);
                pptr[i+4] = (uint8_t) ((acc >> 32) & 0xFF);
                pptr[i+5] = (uint8_t) ((acc >> 40) & 0xFF);
            }
            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
            return;
#else
			uint8_t* pptr = (uint8_t*) vptr;
            for (jsize i = 0; i < arrayLen; i++) {
				uint64_t u64 = (uint64_t) bPtr[arrayOff+i];
#if BYTE_ORDER == LITTLE_ENDIAN
                *((uint32_t*) (vptr+0)) = (uint32_t) u64;
                *((uint16_t*) (vptr+4)) = (uint16_t) (u64 >> 32);
#elif BYTE_ORDER == BIG_ENDIAN
                *((uint32_t*) (vptr+2)) = (uint32_t) u64;
                *((uint16_t*) (vptr+0)) = (uint16_t) (u64 >> 32);
#else
#error
#endif
                vptr+=6;
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
#endif
		}
		case (7): {
#if (defined(__mips64))
            uint8_t* pptr = (uint8_t *) vptr;
            for (jsize i, c = 0; i < arrayLen*7; i+=7) {
                uint64_t acc = (uint64_t) bPtr[arrayOff+c++];
                pptr[i+0] = (uint8_t) ((acc >>  0) & 0xFF);
                pptr[i+1] = (uint8_t) ((acc >>  8) & 0xFF);
                pptr[i+2] = (uint8_t) ((acc >> 16) & 0xFF);
                pptr[i+3] = (uint8_t) ((acc >> 24) & 0xFF);
                pptr[i+4] = (uint8_t) ((acc >> 32) & 0xFF);
                pptr[i+5] = (uint8_t) ((acc >> 40) & 0xFF);
                pptr[i+6] = (uint8_t) ((acc >> 48) & 0xFF);
            }
            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
            return;
#else
			uint8_t* pptr = (uint8_t*) vptr;
            for (jsize i = 0; i < arrayLen; i++) {
				uint64_t u64 = (uint64_t) bPtr[arrayOff+i];
#if BYTE_ORDER == LITTLE_ENDIAN
                *((uint32_t*) (vptr+0)) = (uint32_t) u64;
                *((uint16_t*) (vptr+4)) = (uint16_t) (u64 >> 32);
                *((uint8_t*)  (vptr+6)) = (uint8_t)  (u64 >> 48);
#elif BYTE_ORDER == BIG_ENDIAN
                *((uint32_t*) (vptr+3)) = (uint32_t) u64;
                *((uint16_t*) (vptr+1)) = (uint16_t) (u64 >> 32);
                *((uint8_t*)  (vptr+0)) = (uint8_t)  (u64 >> 48);
#else
#error
#endif
                vptr+=7;
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
			return;
#endif
		}
	}

    const size_t valSize = sizeof(jlong);
    const size_t psize = size-valSize;

#if BYTE_ORDER == BIG_ENDIAN
    for (jsize i = 0; i < arrayLen; i++) {
        memset(vptr, 0, psize);
        vptr+=psize;
        *((jlong*)vptr) = bPtr[arrayOff+i];
        vptr+=valSize;
    }
#elif BYTE_ORDER == LITTLE_ENDIAN
    for (jsize i = 0; i < arrayLen; i++) {

#if (defined(__arm__) || defined(__mips64))
        memcpy(vptr, (void*) &bPtr[arrayOff+i], valSize);
#else
        //Causes SIGBUS on arm 32 bit.
        *((jlong*)vptr) = bPtr[arrayOff+i];
#endif

        vptr+=valSize;
        memset(vptr, 0, psize);
        vptr+=psize;
    }
#else
#error
#endif

    (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_ABORT);
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readDoubleArray
 * Signature: (JJ[DII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readDoubleArray
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readFloatArray
 * Signature: (JJ[FII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readFloatArray
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readExpandedByteArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readExpandedByteArray
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
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readExpandedCharArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readExpandedCharArray
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
#if (defined(__mips64))
        if ((((uintptr_t )vptr) & 0x1) != 0) {
            jshort* carray = (*env)->GetCharArrayElements(env, array, NULL);
            if (carray == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "GetCharArrayElements");
                return;
            }
            memcpy((void*) &carray[arrayOff], vptr, arrayLen*2);
            (*env)->ReleaseCharArrayElements(env, array, carray, JNI_OK);
            return;
        }
#endif
		(*env)->SetCharArrayRegion(env, array, arrayOff, arrayLen, (jchar*) vptr);
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
#if (defined(__mips64))
        memcpy((void*) &bPtr[arrayOff+i], vptr, 2);
#else
        //Causes SIGBUS on mips.
        jchar* pptr = (jchar*) vptr;
        bPtr[arrayOff+i] = pptr[0];
#endif

		vptr+=size;
	}

	(*env)->ReleaseCharArrayElements(env, array, bPtr, JNI_OK);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readExpandedShortArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readExpandedShortArray
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
#if (defined(__mips64))
        if ((((uintptr_t )vptr) & 0x1) != 0) {
            jshort* carray = (*env)->GetShortArrayElements(env, array, NULL);
            if (carray == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "GetShortArrayElements");
                return;
            }
            memcpy((void*) &carray[arrayOff], vptr, arrayLen*2);
            (*env)->ReleaseShortArrayElements(env, array, carray, JNI_OK);
            return;
        }
#endif
		(*env)->SetShortArrayRegion(env, array, arrayOff, arrayLen, (jshort*) vptr);
		return;
	}


	jshort * bPtr = (*env)->GetShortArrayElements(env, array, NULL);
	if (bPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetShortArrayElements");
		return;
	}

	if (size == 1) {
		uint8_t * pptr = (uint8_t*) vptr;
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
#if (defined(__mips64))
        memcpy((void*) &bPtr[arrayOff+i], vptr, 2);
#else
        //Causes SIGBUS on mips.
        jshort* pptr = (jshort*) vptr;
        bPtr[arrayOff+i] = pptr[0];
#endif

		vptr+=size;
	}

	(*env)->ReleaseShortArrayElements(env, array, bPtr, JNI_OK);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readExpandedIntArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readExpandedIntArray
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
#if (defined(__mips64))
        if ((((uintptr_t )vptr) & 0x3) != 0) {
            jint* carray = (*env)->GetIntArrayElements(env, array, NULL);
            if (carray == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "GetIntArrayElements");
                return;
            }
            memcpy((void*) &carray[arrayOff], vptr, arrayLen*4);
            (*env)->ReleaseIntArrayElements(env, array, carray, JNI_OK);
            return;
        }
#endif
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
				bPtr[arrayOff+i] = (jint) pptr[i];
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_OK);

			return;
		}
		case (2): {
#if (defined(__mips64))
            if ((((uintptr_t)vptr) & 0x1) != 0) {
                uint8_t* pptr = (uint8_t *) vptr;
                for (jsize i, c = 0; i < arrayLen*2; i+=2) {
                    bPtr[arrayOff+c++] = (jlong) ((((uint64_t) pptr[i+1]) << 8) | ((uint64_t) pptr[i]));
                }
                (*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_OK);
                return;
            }
#endif
            uint16_t* pptr = (uint16_t *) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				bPtr[arrayOff+i] = (jint) pptr[i];
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_OK);
			return;
		}
		case (3): {
#if (defined(__mips64))
            uint8_t* pptr = (uint8_t *) vptr;
            for (jsize i, c = 0; i < arrayLen*3; i+=3) {
                bPtr[arrayOff+c++] = (jint) ((((uint32_t) pptr[i+2]) << 16) | (((uint32_t) pptr[i+1]) << 8) | ((uint32_t) pptr[i]));
            }
            (*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_OK);
            return;
#else
			for (jsize i = 0; i < arrayLen; i++) {
#if BYTE_ORDER == LITTLE_ENDIAN
                bPtr[arrayOff+i] = (jint) (((uint32_t) *((uint16_t*)(vptr+0))) | (((uint32_t) *((uint8_t*)(vptr+2))) << 16));
#elif BYTE_ORDER == BIG_ENDIAN
                bPtr[arrayOff+i] = (jint) (((uint32_t) *((uint16_t*)(vptr+1))) | (((uint32_t) *((uint8_t*)(vptr+0))) << 16));
#else
#error
#endif
				vptr+=3;
			}

			(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_OK);
			return;
#endif
		}
	}

    #if BYTE_ORDER == BIG_ENDIAN
    vptr+=size-sizeof(jint);
    #endif

	for (jsize i = 0; i < arrayLen; i++) {
#if (defined(__mips64))
        memcpy((void*) &bPtr[arrayOff+i], vptr, 4);
#else
        //Causes SIGBUS on mips.
        jint* pptr = (jint*) vptr;
        bPtr[arrayOff+i] = pptr[0];
#endif
		vptr+=size;
	}

	(*env)->ReleaseIntArrayElements(env, array, bPtr, JNI_OK);
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMemory
 * Method:    readExpandedLongArray
 * Signature: (JJ[BIII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMemory_readExpandedLongArray
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
#if (defined(__arm__) || defined(__mips64))
        if ((((uintptr_t )vptr) & 0x7) != 0) {
            jlong* carray = (*env)->GetLongArrayElements(env, array, NULL);
            if (carray == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "GetLongArrayElements");
                return;
            }
            memcpy((void*) &carray[arrayOff], vptr, arrayLen*8);
            (*env)->ReleaseLongArrayElements(env, array, carray, JNI_OK);
            return;
        }
#endif
        (*env)->SetLongArrayRegion(env, array, arrayOff, arrayLen, (jlong*) vptr);
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
#if (defined(__mips64))
            if ((((uintptr_t)vptr) & 0x1) != 0) {
                uint8_t* pptr = (uint8_t *) vptr;
                for (jsize i, c = 0; i < arrayLen*2; i+=2) {
                    bPtr[arrayOff+c++] = (jlong) ((((uint64_t) pptr[i+1]) << 8) | ((uint64_t) pptr[i]));
                }
                (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
                return;
            }
#endif
            uint16_t* pptr = (uint16_t *) vptr;
            for (jsize i = 0; i < arrayLen; i++) {
                bPtr[arrayOff+i] = (jlong) pptr[i];
            }

            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
            return;
		}
		case (3): {
#if (defined(__mips64))
            uint8_t* pptr = (uint8_t *) vptr;
            for (jsize i, c = 0; i < arrayLen*3; i+=3) {
                bPtr[arrayOff+c++] = (jlong) ((((uint64_t) pptr[i+2]) << 16) | (((uint64_t) pptr[i+1]) << 8) | ((uint64_t) pptr[i]));
            }
            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
            return;
#else
            jsize x = 0;
            for (jsize i = 0; i < arrayLen; i++) {
#if BYTE_ORDER == LITTLE_ENDIAN
                bPtr[arrayOff+i] = (jlong) (((uint32_t) *((uint16_t*)(vptr+0))) | (((uint32_t) *((uint8_t*)(vptr+2))) << 16));
#elif BYTE_ORDER == BIG_ENDIAN
                bPtr[arrayOff+i] = (jlong) (((uint32_t) *((uint16_t*)(vptr+1))) | (((uint32_t) *((uint8_t*)(vptr+0))) << 16));
#else
#error
#endif
                vptr+=3;
            }

            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
            return;
#endif
		}
		case (4): {
#if (defined(__mips64))
            if ((((uintptr_t)vptr) & 0x3) != 0) {
                uint8_t* pptr = (uint8_t *) vptr;
                for (jsize i, c = 0; i < arrayLen*4; i+=4) {
                    bPtr[arrayOff+c++] = (jlong) ((((uint64_t) pptr[i+3]) << 24) | (((uint64_t) pptr[i+2]) << 16) | (((uint64_t) pptr[i+1]) << 8) | ((uint64_t) pptr[i]));
                }
                (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
                return;
            }
#endif
            uint32_t* pptr = (uint32_t *) vptr;
			for (jsize i = 0; i < arrayLen; i++) {
				bPtr[arrayOff+i] = (jlong) pptr[i];
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
			return;
		}
		case (5): {
#if (defined(__mips64))
            uint8_t* pptr = (uint8_t *) vptr;
            for (jsize i, c = 0; i < arrayLen*5; i+=5) {
                bPtr[arrayOff+c++] = (jlong) ((((uint64_t) pptr[i+4]) << 32) | (((uint64_t) pptr[i+3]) << 24) | (((uint64_t) pptr[i+2]) << 16) | (((uint64_t) pptr[i+1]) << 8) | ((uint64_t) pptr[i]));
            }
            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
            return;
#else
            for (jsize i = 0; i < arrayLen; i++) {
#if BYTE_ORDER == LITTLE_ENDIAN
                bPtr[arrayOff+i] = (jlong) (((uint64_t) *((uint32_t*)(vptr+0))) | (((uint64_t) *((uint8_t*)(vptr+4))) << 32));
#elif BYTE_ORDER == BIG_ENDIAN
                bPtr[arrayOff+i] = (jlong) (((uint64_t) *((uint32_t*)(vptr+1))) | (((uint64_t) *((uint8_t*)(vptr+0))) << 32));
#else
#error
#endif
                vptr+=5;
            }

            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
            return;
#endif

		}
		case (6): {
#if (defined(__mips64))
            uint8_t* pptr = (uint8_t *) vptr;
            for (jsize i, c = 0; i < arrayLen*6; i+=6) {
                bPtr[arrayOff+c++] = (jlong) ((((uint64_t) pptr[i+5]) << 40) | (((uint64_t) pptr[i+4]) << 32) | (((uint64_t) pptr[i+3]) << 24) | (((uint64_t) pptr[i+2]) << 16) | (((uint64_t) pptr[i+1]) << 8) | ((uint64_t) pptr[i]));
            }
            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
            return;
#else
			for (jsize i = 0; i < arrayLen; i++) {
#if BYTE_ORDER == LITTLE_ENDIAN
                bPtr[arrayOff+i] = (jlong) (((uint64_t) *((uint32_t*)(vptr+0))) | (((uint64_t) *((uint16_t*)(vptr+4))) << 32));
#elif BYTE_ORDER == BIG_ENDIAN
                bPtr[arrayOff+i] = (jlong) (((uint64_t) *((uint32_t*)(vptr+2))) | (((uint64_t) *((uint16_t*)(vptr+0))) << 32));
#else
#error
#endif
                vptr+=6;
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
			return;
#endif
		}
		case (7): {
#if (defined(__mips64))
            uint8_t* pptr = (uint8_t *) vptr;
            for (jsize i, c = 0; i < arrayLen*7; i+=7) {
                bPtr[arrayOff+c++] = (jlong) ((((uint64_t) pptr[i+6]) << 48) | (((uint64_t) pptr[i+5]) << 40) | (((uint64_t) pptr[i+4]) << 32) | (((uint64_t) pptr[i+3]) << 24) | (((uint64_t) pptr[i+2]) << 16) | (((uint64_t) pptr[i+1]) << 8) | ((uint64_t) pptr[i]));
            }
            (*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
            return;
#else
			for (jsize i = 0; i < arrayLen; i++) {
#if BYTE_ORDER == LITTLE_ENDIAN
                bPtr[arrayOff+i] = (jlong) (((uint64_t) *((uint32_t*)(vptr+0))) | (((uint64_t) *((uint16_t*)(vptr+4))) << 32) | (((uint64_t) *((uint8_t*)(vptr+6))) << 48));
#elif BYTE_ORDER == BIG_ENDIAN
                bPtr[arrayOff+i] = (jlong) (((uint64_t) *((uint32_t*)(vptr+3))) | (((uint64_t) *((uint16_t*)(vptr+1))) << 32) | (((uint64_t) *((uint8_t*)(vptr+0))) << 48));
#else
#error
#endif
                vptr+=7;
			}

			(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
			return;
#endif
		}
        default:
            break;
	}

#if BYTE_ORDER == BIG_ENDIAN
		vptr+=size-sizeof(jlong);
#endif

	for (jsize i = 0; i < arrayLen; i++) {
#if (defined(__arm__) || defined(__mips64))
        memcpy((void*) &bPtr[arrayOff+i], vptr, 8);
#else
        //Causes SIGBUS on arm 32 bit.
        jlong* pptr = (jlong*) vptr;
        bPtr[arrayOff+i] = pptr[0];
#endif

		vptr+=size;
	}

	(*env)->ReleaseLongArrayElements(env, array, bPtr, JNI_OK);
}

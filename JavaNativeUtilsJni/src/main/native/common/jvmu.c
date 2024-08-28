//
// Copyright Alexander Schütz, 2021-2024
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
#include "./jni/eu_aschuetz_nativeutils_impl_JNICommonNativeUtil.h"
#include "common.h"
#include "stdlib.h"

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    MonitorEnter
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_MonitorEnter
  (JNIEnv * env, jobject inst, jobject moni) {
	if (moni == NULL) {
		jthrowCC_NullPointerException_1(env, "monitor");
		return;
	}

	(*env)->MonitorEnter(env, moni);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    MonitorExit
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_MonitorExit
  (JNIEnv * env, jobject inst, jobject moni) {
	if (moni == NULL) {
		jthrowCC_NullPointerException_1(env, "monitor");
		return;
	}

	(*env)->MonitorExit(env, moni);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    Throw
 * Signature: (Ljava/lang/Throwable;)Ljava/lang/RuntimeException;
 */
JNIEXPORT jthrowable JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_Throw
  (JNIEnv * env, jobject obj, jthrowable thr) {
	if (thr == NULL) {
		jthrowCC_NullPointerException_1(env, "throwable");
		return thr;
	}
	(*env)->Throw(env, thr);
	return thr;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _AllocObject
 * Signature: (Ljava/lang/Class;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1AllocObject
  (JNIEnv *env, jclass class, jclass dec) {
	return (*env)->AllocObject(env, dec);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    NewGlobalRef
 * Signature: (Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_NewGlobalRef
  (JNIEnv * env, jobject inst, jobject obj) {
	if (obj == NULL) {
		jthrowCC_NullPointerException_1(env, "obj");
		return 0;
	}

	return (jlong) (uintptr_t) (*env)->NewGlobalRef(env, obj);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    DeleteGlobalRef
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_DeleteGlobalRef
  (JNIEnv * env, jobject inst, jlong ref) {
	if (ref == 0) {
		jthrowCC_NullPointerException_1(env, "ref");
		return;
	}

	(*env)->DeleteGlobalRef(env, (jobject) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    NewLocalRef
 * Signature: (J)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_NewLocalRef
  (JNIEnv * env, jobject inst, jlong ref) {
	if (ref == 0) {
		jthrowCC_NullPointerException_1(env, "ref");
		return NULL;
	}

	return (*env)->NewLocalRef(env, (jobject) (uintptr_t) ref);
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    DefineClass
 * Signature: (Ljava/lang/String;Ljava/lang/ClassLoader;[BII)Ljava/lang/Class;
 */
JNIEXPORT jclass JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_DefineClass
  (JNIEnv * env, jobject inst, jstring name, jobject loader, jbyteArray buf, jint off, jint len) {
	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return NULL;
	}

	if (loader == NULL) {
		jthrowCC_NullPointerException_1(env, "loader");
		return NULL;
	}

	if (buf == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return NULL;
	}

	jsize jlen = (*env)->GetArrayLength(env, buf);
	if (off < 0 || len < 0 || jlen < off+len) {
		jthrowCC_IllegalArgumentException_1(env, "array bounds");
		return NULL;
	}



	const char * namePtr = (*env)->GetStringUTFChars(env, name, NULL);
	if (namePtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return NULL;
	}

	jbyte* cBuf = (*env)->GetByteArrayElements(env, buf, NULL);

	if (cBuf == NULL) {
		(*env)->ReleaseStringUTFChars(env, name, namePtr);
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return NULL;
	}

	cBuf+=(uintptr_t) off;

	jclass cl = (*env)->DefineClass(env, namePtr, loader, (const jbyte*) cBuf, len);
	(*env)->ReleaseByteArrayElements(env, buf, cBuf, JNI_ABORT);
	(*env)->ReleaseStringUTFChars(env, name, namePtr);
	return cl;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    GetDirectBufferAddress
 * Signature: (Ljava/nio/ByteBuffer;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_GetDirectBufferAddress
  (JNIEnv * env, jobject inst, jobject buf) {
	if (buf == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return 0;
	}
	return (jlong) (uintptr_t) (*env)->GetDirectBufferAddress(env, buf);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    NewDirectByteBuffer
 * Signature: (JJ)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_NewDirectByteBuffer
  (JNIEnv * env, jobject inst, jlong ptr, jlong size) {
	if (size < 0) {
		jthrowCC_IllegalArgumentException_1(env, "size<0");
		return NULL;
	}

	if (ptr == 0) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return NULL;
	}

	return (*env)->NewDirectByteBuffer(env, (void*) (uintptr_t) ptr, size);
}


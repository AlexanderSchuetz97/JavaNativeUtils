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
#include "../common/jni/io_github_alexanderschuetz97_nativeutils_impl_JNICommonNativeUtil.h"
#include "../common/common.h"
#include <stdlib.h>


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNICommonNativeUtil
 * Method:    getPointerSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNICommonNativeUtil_getPointerSize
  (JNIEnv * env, jobject inst) {
	return sizeof(void*);
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNICommonNativeUtil
 * Method:    _malloc
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNICommonNativeUtil__1malloc
	(JNIEnv * env, jclass clazz, jlong size) {
	void * ptr = malloc((size_t) size);
	if (ptr == NULL) {
		throwOOM(env, "malloc");
	}
	return (jlong) (uintptr_t) ptr;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNICommonNativeUtil
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNICommonNativeUtil__1free
	(JNIEnv * env, jclass clazz, jlong ptr) {
	void * vptr = (void*) (uintptr_t) ptr;
	if (vptr == NULL) {
		throwNullPointerException(env, "ptr");
		return;
	}

	free(vptr);
}

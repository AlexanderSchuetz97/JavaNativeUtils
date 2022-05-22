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
#include "../common/jni/io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil.h"
#include "../common/common.h"
#include <windows.h>
#define THDL (HANDLE)(uintptr_t)

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    getFD
 * Signature: (Ljava/io/FileDescriptor;)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_getFD
	(JNIEnv * env, jobject inst, jobject fdo) {
	return getFD(env, fdo);
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    getHandle
 * Signature: (Ljava/io/FileDescriptor;)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_getHandle
	(JNIEnv * env, jobject inst, jobject fdo) {
	return getHandle(env, fdo);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCurrentThread
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetCurrentThread
  (JNIEnv * env, jobject inst) {
	return (jlong) (uintptr_t) GetCurrentThread();
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCurrentProcess
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetCurrentProcess
  (JNIEnv * env, jobject inst) {
	return (jlong) (uintptr_t) GetCurrentProcess();
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DuplicateHandle
 * Signature: (JJJIZZZ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_DuplicateHandle
  (JNIEnv * env, jobject inst, jlong srcProc, jlong srcHandle, jlong trgProc, jint access, jboolean inherit, jboolean closeSrc, jboolean sameAcc) {
	HANDLE res = INVALID_HANDLE_VALUE;
	DWORD opt = 0;
	if (closeSrc) {
		opt |= DUPLICATE_CLOSE_SOURCE;
	}

	if (sameAcc) {
		opt |= DUPLICATE_SAME_ACCESS;
	}

	WINBOOL succ = DuplicateHandle(THDL srcProc, THDL srcHandle, THDL trgProc, &res, (DWORD) access, inherit, opt);
	if (succ) {
		return (jlong) (uintptr_t) res;
	}

	throwUnknownError(env, GetLastError());
	return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CancelIo
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CancelIo
  (JNIEnv * env, jobject inst, jlong handle) {
	if (CancelIo(THDL handle) == 0) {
		throwUnknownError(env, GetLastError());
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CancelIoEx
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CancelIoEx
(JNIEnv * env, jobject inst, jlong handle, jlong overlapped) {
	if (CancelIoEx(THDL handle, (LPOVERLAPPED) (uintptr_t) overlapped) == 0) {
		throwUnknownError(env, GetLastError());
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CancelSynchronousIo
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CancelSynchronousIo
  (JNIEnv * env, jobject inst, jlong handle) {
	if (CancelSynchronousIo(THDL handle) == 0) {
		throwUnknownError(env, GetLastError());
	}
}

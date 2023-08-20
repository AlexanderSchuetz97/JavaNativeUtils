//
// Copyright Alexander Schütz, 2022
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
 * Method:    OpenProcessToken
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_OpenProcessToken
  (JNIEnv * env, jobject inst, jlong proc, jint access) {
	HANDLE result = INVALID_HANDLE_VALUE;
	if (!OpenProcessToken((HANDLE)(uintptr_t) proc, (DWORD) access, &result)) {
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
		return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}

	return (jlong) (uintptr_t) result;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetTokenInformation
 * Signature: (JI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetTokenInformation
  (JNIEnv *env , jobject inst, jlong token, jint type) {
	DWORD size = 0;

	if (GetTokenInformation((HANDLE)(uintptr_t) token, type, NULL, 0, &size)) {
		//We dont expect this call to succeed...
		printf("a\n");
		jthrow_UnknownNativeErrorException_1(env, ERROR_BAD_LENGTH);
		return NULL;
	}

	DWORD err = GetLastError();
	if (err != ERROR_BAD_LENGTH) {
		printf("b\n");
		jthrow_UnknownNativeErrorException_1(env, err);
		return NULL;
	}

	if (size <= 0) {
		printf("c\n");
		jthrow_UnknownNativeErrorException_1(env, ERROR_BAD_LENGTH);
		return NULL;
	}

	void * mem = malloc(size);
	if (mem == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "malloc");
		return NULL;
	}

	memset(mem, 0, size);

	DWORD nsize = 0;

	if (!GetTokenInformation((HANDLE)(uintptr_t) token, type, mem, size, &nsize)) {
		printf("d\n");
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
		free(mem);
		return NULL;
	}

	if (nsize > size) {
		//Unlikely
		free(mem);
		printf("e\n");
		jthrow_UnknownNativeErrorException_1(env, ERROR_BAD_LENGTH);
		return NULL;
	}

	jbyteArray array = jarrayB(env, (jbyte*) mem, nsize);
	free(mem);
	return array;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ShellExecuteA
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ShellExecuteA
  (JNIEnv * env, jobject inst, jlong hwnd, jstring lpOperation, jstring lpFile, jstring lpParameters, jstring lpDirectory, jint nShowCmd) {

	if (lpFile == NULL) {
		jthrowCC_NullPointerException_1(env, "lpFile");
		return 0;
	}

	LPCSTR clpOperation = NULL;
	LPCSTR clpFile = (*env)->GetStringUTFChars(env, lpFile, NULL);
	LPCSTR clpParameters = NULL;
	LPCSTR clpDirectory = NULL;

	if (clpFile == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return 0;
	}

	if (lpOperation != NULL) {
		clpOperation = (*env)->GetStringUTFChars(env, lpOperation, NULL);
		if (clpOperation == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
			return 0;
		}
	}

	if (lpParameters != NULL) {
		clpParameters = (*env)->GetStringUTFChars(env, lpParameters, NULL);
		if (clpParameters == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
			return 0;
		}
	}

	if (lpDirectory != NULL) {
		clpDirectory = (*env)->GetStringUTFChars(env, lpDirectory, NULL);
		if (clpParameters == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
			return 0;
		}
	}


	HINSTANCE result = ShellExecuteA((HWND) (uintptr_t) hwnd, clpOperation, clpFile, clpParameters, clpDirectory, (INT) nShowCmd);

	(*env)->ReleaseStringUTFChars(env, lpFile, clpFile);

	if (clpOperation != NULL) {
		(*env)->ReleaseStringUTFChars(env, lpOperation, clpOperation);
	}

	if (clpParameters != NULL) {
		(*env)->ReleaseStringUTFChars(env, lpParameters, clpParameters);
	}

	if (clpDirectory != NULL) {
		(*env)->ReleaseStringUTFChars(env, lpDirectory, clpDirectory);
	}


	uintptr_t resInt = (uintptr_t) result;
	if (resInt > 32) {
		return (jlong) resInt;
	}

	jthrow_ShellExecuteException(env, GetLastError(), (jlong) (uintptr_t) result);
	return 0;
}










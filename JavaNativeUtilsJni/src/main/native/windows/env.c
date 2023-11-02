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
#include "../common/jni/eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil.h"
#include "../common/common.h"

#include <windows.h>
#include <errhandlingapi.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetModuleFileNameA
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetModuleFileNameA
  (JNIEnv * env, jobject inst, jlong handle) {

	size_t size = 256;

	while(size < 0xffff) {

		void * buf = malloc(size);
		if (buf == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			return NULL;
		}

		memset(buf, 0, size);

		LPSTR str = (LPSTR) buf;

		GetModuleFileNameA((HMODULE) (uintptr_t) handle, str, size-1);
		DWORD lerr = GetLastError();
		if (lerr == ERROR_SUCCESS) {
			jstring jstr = (*env)->NewStringUTF(env, str);
			free(str);
			return jstr;
		}

		free(buf);

		if (lerr != ERROR_INSUFFICIENT_BUFFER) {
			jthrow_UnknownNativeErrorException_1(env, lerr);
			return NULL;
		}

		size+=256;
	}


	jthrow_UnknownNativeErrorException_1(env, ERROR_INSUFFICIENT_BUFFER);
	return NULL;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetEnvironmentVariableA
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetEnvironmentVariableA
  (JNIEnv * env, jobject inst, jstring name, jstring value) {

	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return;
	}

	const char * namePtr = (*env)->GetStringUTFChars(env, name, NULL);
	if (namePtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}

	if (value == NULL) {
		WINBOOL b = SetEnvironmentVariableA(namePtr, NULL);

		(*env)->ReleaseStringUTFChars(env, name, namePtr);

		if (!b) {
			jthrow_UnknownNativeErrorException_1(env, GetLastError());
		}


		return;
	}

	const char * valuePtr = (*env)->GetStringUTFChars(env, value, NULL);
	if (valuePtr == NULL) {
		(*env)->ReleaseStringUTFChars(env, name, namePtr);
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}


	WINBOOL b = SetEnvironmentVariableA(namePtr, valuePtr);

	(*env)->ReleaseStringUTFChars(env, name, namePtr);
	(*env)->ReleaseStringUTFChars(env, value, valuePtr);

	if (!b) {
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ExpandEnvironmentStringsA
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ExpandEnvironmentStringsA
  (JNIEnv * env, jobject inst, jstring str) {
	if (str == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return NULL;
	}

	const char * strPtr = (*env)->GetStringUTFChars(env, str, NULL);
	if (strPtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return NULL;
	}

	char small[256];
	memset((void*) small, 0, 256);
	DWORD size = ExpandEnvironmentStringsA(strPtr, small, 256);
	if (size == 0) {
		(*env)->ReleaseStringUTFChars(env, str, strPtr);
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
		return NULL;
	}

	if (size <= 256) {
		(*env)->ReleaseStringUTFChars(env, str, strPtr);
		return (*env)->NewStringUTF(env, small);
	}

	char * large = (char *) malloc(size);
	memset((void*) large, 0, size);
	DWORD nsize = ExpandEnvironmentStringsA(strPtr, large, size);

	(*env)->ReleaseStringUTFChars(env, str, strPtr);
	if (size == 0) {
		free((void*)large);
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
		return NULL;
	}

	if (nsize <= size) {
		jstring str = (*env)->NewStringUTF(env, large);
		free((void*)large);
		return str;
	}


	free((void*)large);
	jthrow_UnknownNativeErrorException_1(env, ERROR_INSUFFICIENT_BUFFER);
	return NULL;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetEnvironmentVariableA
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetEnvironmentVariableA
  (JNIEnv * env, jobject inst, jstring name) {
	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return NULL;
	}

	const char * namePtr = (*env)->GetStringUTFChars(env, name, NULL);
	if (namePtr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return NULL;
	}


	LPSTR str = "";
	DWORD res = GetEnvironmentVariableA(namePtr, str, 0);
	if (res <= 0) {
		DWORD lerr = GetLastError();
		if (lerr == ERROR_ENVVAR_NOT_FOUND) {
			(*env)->ReleaseStringUTFChars(env, name, namePtr);
			return NULL;
		}

		(*env)->ReleaseStringUTFChars(env, name, namePtr);
		jthrow_UnknownNativeErrorException_1(env, lerr);
		return NULL;
	}


	int i = 0;

	while(i++ < 10) {

		//Windows has scammed me before im now doing +2 just because
		void * buf = malloc(res+2);
		if (buf == NULL) {
			(*env)->ReleaseStringUTFChars(env, name, namePtr);
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			return NULL;
		}

		memset(buf, 0, res+2);
		str = (LPSTR) buf;

		DWORD nres = GetEnvironmentVariableA(namePtr, str, res+1);

		if (nres <= 0) {
			DWORD lerr = GetLastError();
			if (lerr == ERROR_ENVVAR_NOT_FOUND) {
				(*env)->ReleaseStringUTFChars(env, name, namePtr);
				return NULL;
			}

			(*env)->ReleaseStringUTFChars(env, name, namePtr);
			jthrow_UnknownNativeErrorException_1(env, lerr);
			return NULL;
		}

		//Modification out of nowhere
		if (nres > res) {
			free(buf);
			res = nres;
			continue;
		}

		(*env)->ReleaseStringUTFChars(env, name, namePtr);
		jstring jstr = (*env)->NewStringUTF(env, str);
		free(buf);
		return jstr;
	}


	jthrow_UnknownNativeErrorException_1(env, ERROR_BUSY);
	return NULL;

}

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
#include <fileapi.h>
#include <errhandlingapi.h>
#include <stdio.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetVolumePathNameW
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetVolumePathNameW
  (JNIEnv * env, jobject inst, jstring path) {
	if (path == NULL) {
		jthrowCC_NullPointerException_1(env, "path");
		return NULL;
	}

	wchar_t* in = toWCharsMalloc(env, path);
	if (in == NULL) {
		return NULL;
	}

	jsize len = (*env)->GetStringLength(env, path);
	DWORD tcharl = len < 16 ? 16 : len;

	size_t memsize = sizeof(wchar_t) * (tcharl+1);

	wchar_t* out = (wchar_t*) malloc(memsize);
	if (out == NULL) {
		free(in);
		jthrowCC_OutOfMemoryError_1(env, "malloc");
		return NULL;
	}

	memset(out, 0, memsize);


	WINBOOL succ = GetVolumePathNameW(in, out, tcharl);
	free(in);
	if (!succ) {
		free(out);
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
		return NULL;
	}

	jstring str = fromWChars(env, out);
	free(out);
	return str;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFinalPathNameByHandleA
 * Signature: (JZLeu/aschuetz/nativeutils/api/WindowsNativeUtil/Path_VolumeName;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetFinalPathNameByHandleA
  (JNIEnv * env, jobject inst, jlong handle, jboolean normalize, jobject volume) {
	HANDLE h = (HANDLE) (uintptr_t) handle;
	if (h == INVALID_HANDLE_VALUE) {
		jthrow_InvalidFileDescriptorException(env);
		return NULL;
	}

	DWORD ord = (DWORD) jenum_ordinal(env, volume);
	//0=DOS, 1=GUID, 2=NONE, 3=NT
	if (ord < 0 || ord > 4) {
		jthrowCC_IllegalArgumentException_1(env, "volumeName");
		return NULL;
	}

	DWORD flags = normalize ? FILE_NAME_NORMALIZED : FILE_NAME_OPENED;
	flags |= ord;


	LPSTR path = "";
	DWORD res = GetFinalPathNameByHandleA(h, path, 0, flags);

	if (res == 0) {
		DWORD err = GetLastError();
		if (err == ERROR_INVALID_HANDLE) {
			jthrow_InvalidFileDescriptorException(env);
			return NULL;
		}
		jthrow_UnknownNativeErrorException_1(env, err);
		return NULL;
	}

	path = malloc(res+2);
	if (path == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "malloc");
		return NULL;
	}


	memset((void*)path, 0, res+2);

	DWORD res2 = GetFinalPathNameByHandleA(h, path, res+1, flags);

	if (res2 == 0) {
		free(path);
		DWORD err = GetLastError();
		if (err == ERROR_INVALID_HANDLE) {
			jthrow_InvalidFileDescriptorException(env);
			return NULL;
		}
		jthrow_UnknownNativeErrorException_1(env, err);
		return NULL;
	}

	if (res2 > res) {
		free(path);
		jthrow_UnknownNativeErrorException_1(env, ERROR_INSUFFICIENT_BUFFER);
		return NULL;
	}

	jstring str = (*env)->NewStringUTF(env, (const char*) path);
	free(path);
	return str;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFinalPathNameByHandleW
 * Signature: (JZLeu/aschuetz/nativeutils/api/WindowsNativeUtil/Path_VolumeName;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetFinalPathNameByHandleW
	(JNIEnv * env, jobject inst, jlong handle, jboolean normalize, jobject volume) {
	HANDLE h = (HANDLE) (uintptr_t) handle;
		if (h == INVALID_HANDLE_VALUE) {
			jthrow_InvalidFileDescriptorException(env);
			return NULL;
		}

		DWORD ord = (DWORD) jenum_ordinal(env, volume);
		//0=DOS, 1=GUID, 2=NONE, 3=NT
		if (ord < 0 || ord > 4) {
			jthrowCC_IllegalArgumentException_1(env, "volumeName");
			return NULL;
		}

		DWORD flags = normalize ? FILE_NAME_NORMALIZED : FILE_NAME_OPENED;
		flags |= ord;


		LPWSTR path = (LPWSTR) "";
		DWORD res = GetFinalPathNameByHandleW(h, path, 0, flags);

		if (res == 0) {
			DWORD err = GetLastError();
			if (err == ERROR_INVALID_HANDLE) {
				jthrow_InvalidFileDescriptorException(env);
				return NULL;
			}
			jthrow_UnknownNativeErrorException_1(env, err);
			return NULL;
		}

		size_t sizeInBytes = (res+2) * sizeof(wchar_t);
		path = malloc(sizeInBytes);
		if (path == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			return NULL;
		}


		memset((void*)path, 0, sizeInBytes);

		DWORD res2 = GetFinalPathNameByHandleW(h, path, res+1, flags);

		if (res2 == 0) {
			free(path);
			DWORD err = GetLastError();
			if (err == ERROR_INVALID_HANDLE) {
				jthrow_InvalidFileDescriptorException(env);
				return NULL;
			}
			jthrow_UnknownNativeErrorException_1(env, err);
			return NULL;
		}

		if (res2 > res) {
			free(path);
			jthrow_UnknownNativeErrorException_1(env, ERROR_INSUFFICIENT_BUFFER);
			return NULL;
		}



		jstring str = fromWChars(env, path);
		free(path);
		return str;
}

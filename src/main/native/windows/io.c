//
// Copyright Alexander Schütz, 2021
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
 * Method:    CreateFileA
 * Signature: (Ljava/lang/String;IZZZLio/github/alexanderschuetz97/nativeutils/api/WindowsNativeUtil/CreateFileA_createMode;I)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateFileA
  (JNIEnv * env, jobject inst, jstring path, jint access, jboolean allowDelete, jboolean allowRead, jboolean allowWrite, jobject openMode, jint attributes) {

	if (path == NULL) {
		throwIllegalArgumentsExc(env, "path is null");
		return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}

	DWORD mode = 0;
	switch(getEnumOrdinal(env, openMode)) {
		case(0):
			mode = CREATE_NEW;
			break;
		case(1):
			mode = CREATE_ALWAYS;
			break;
		case(2):
			mode = OPEN_ALWAYS;
			break;
		case(3):
			mode = OPEN_EXISTING;
			break;
		case(4):
			mode = TRUNCATE_EXISTING;
			break;
		default:
			throwIllegalArgumentsExc(env, "invalid openMode");
			return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}

	DWORD share = 0;

	if (allowDelete) {
		share |= FILE_SHARE_DELETE;
	}

	if (allowRead) {
		share |= FILE_SHARE_READ;
	}

	if (allowWrite) {
		share |= FILE_SHARE_WRITE;
	}


	//WINBASEAPI HANDLE WINAPI CreateFileA (LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

	LPCSTR str = (*env)->GetStringUTFChars(env, path, NULL);
	if (str == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}


	HANDLE h = CreateFileA(str, access, share, NULL, mode, attributes, NULL);

	if (h == INVALID_HANDLE_VALUE) {
		DWORD err = GetLastError();
		switch(err) {
		case (ERROR_SHARING_VIOLATION):
			throwShareingViolationException(env, str, NULL, NULL);
			break;
		case (ERROR_FILE_EXISTS):
			throwFileAlreadyExistsExc(env, str, NULL, NULL);
			break;
		default:
			unknownError(env, err);
			break;
		}

	}

	(*env)->ReleaseStringUTFChars(env, path, str);
	return (jlong) (uintptr_t) h;

}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CloseHandle
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CloseHandle
  (JNIEnv * env, jobject inst, jlong handle) {

	HANDLE h = (HANDLE) (uintptr_t) handle;

	if (h == INVALID_HANDLE_VALUE) {
		badFileDescriptor(env);
		return;
	}

	if (!CloseHandle(h)) {
		unknownError(env, GetLastError());
	}
}

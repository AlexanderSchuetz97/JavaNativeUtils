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
			throwUnknownError(env, err);
			break;
		}

	}

	(*env)->ReleaseStringUTFChars(env, path, str);
	return (jlong) (uintptr_t) h;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateFileW
 * Signature: (Ljava/lang/String;IZZZLio/github/alexanderschuetz97/nativeutils/api/WindowsNativeUtil/CreateFileA_createMode;I)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateFileW
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


	wchar_t * chars = toWCharsMalloc(env, path);

	if (chars == NULL) {
		return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}


	HANDLE h = CreateFileW(chars, access, share, NULL, mode, attributes, NULL);
	free(chars);


	if (h == INVALID_HANDLE_VALUE) {
		DWORD err = GetLastError();
		const char * p = (*env)->GetStringUTFChars(env, path, NULL);

		if (p == NULL) {
			throwOOM(env, "GetStringUTFChars");
			return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
		}

		switch(err) {
		case (ERROR_SHARING_VIOLATION):
			throwShareingViolationException(env, p, NULL, NULL);
			break;
		case (ERROR_FILE_EXISTS):
			//TODO PATH?
			throwFileAlreadyExistsExc(env, p, NULL, NULL);
			break;
		default:
			throwUnknownError(env, err);
			break;
		}

		(*env)->ReleaseStringUTFChars(env, path, p);
	}

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
		throwBadFileDescriptor(env);
		return;
	}

	if (!CloseHandle(h)) {
		throwUnknownError(env, GetLastError());
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DeviceIoControl
 * Signature: (JI[BII[BII)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_DeviceIoControl__JI_3BII_3BII
  (JNIEnv * env, jobject inst, jlong jhandle, jint ctrlCode, jbyteArray inBuffer, jint inOff, jint inLen, jbyteArray outBuffer, jint outOff, jint outLen) {
	DWORD inSize = 0;
	DWORD outSize = 0;
	jbyte* in = NULL;
	jbyte* out = NULL;
	LPVOID inO = NULL;
	LPVOID outO = NULL;
	DWORD resLen = 0;

	HANDLE h = (HANDLE) (uintptr_t) jhandle;

	if (h == INVALID_HANDLE_VALUE) {
		throwBadFileDescriptor(env);
		return 0;
	}

	if (inBuffer != NULL) {
		inSize = (*env)->GetArrayLength(env, inBuffer);
		if (inOff < 0 || inLen < 0 || inSize < inOff+inLen) {
			throwIllegalArgumentsExc(env, "inBuffer offset/length");
			return 0;
		}
	}

	if (outBuffer != NULL) {
		outSize = (*env)->GetArrayLength(env, outBuffer);
		if (outOff < 0 || outLen < 0 || outSize < outOff+outLen) {
			throwIllegalArgumentsExc(env, "outBuffer offset/length");
			return 0;
		}
	}

	if (inBuffer != NULL) {
		in = (LPVOID) (*env)->GetByteArrayElements(env, inBuffer, NULL);
		if (in == NULL) {
			throwOOM(env, "GetByteArrayElements");
			return 0;
		}

		inO = (LPVOID) (in+inOff);
	}

	if (outBuffer != NULL) {
		out = (LPVOID) (*env)->GetByteArrayElements(env, outBuffer, NULL);
		if (out == NULL) {
			if (inBuffer != NULL) {
				(*env)->ReleaseByteArrayElements(env, inBuffer, in, JNI_OK);
			}
			throwOOM(env, "GetByteArrayElements");
			return 0;
		}

		outO = (LPVOID) (out+outOff);
	}

	WINBOOL succ = DeviceIoControl(h, (DWORD) ctrlCode, inO,inSize, outO, outSize, &resLen, NULL);
	if (succ) {
		if (inBuffer != NULL) {
			(*env)->ReleaseByteArrayElements(env, inBuffer, in, JNI_OK);
		}
		if (outBuffer != NULL) {
			(*env)->ReleaseByteArrayElements(env, outBuffer, out, JNI_OK);
		}
		return resLen;
	}

	if (inBuffer != NULL) {
		(*env)->ReleaseByteArrayElements(env, inBuffer, (jbyte*) in, JNI_ABORT);
	}
	if (outBuffer != NULL) {
		(*env)->ReleaseByteArrayElements(env, outBuffer, (jbyte*) out, JNI_ABORT);
	}

	throwUnknownError(env, GetLastError());
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DeviceIoControl
 * Signature: (JIJJIJJI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_DeviceIoControl__JIJJIJJI
  (JNIEnv * env, jclass clazz, jlong jhandle, jint ctrlCode, jlong in, jlong inOff, jint inLen, jlong out, jlong outOff, jint outLen) {
	HANDLE h = (HANDLE) (uintptr_t) jhandle;

	if (h == INVALID_HANDLE_VALUE) {
		throwBadFileDescriptor(env);
		return 0;
	}

	LPVOID inP = (LPVOID) (uintptr_t) in;
	LPVOID outP = (LPVOID) (uintptr_t) out;

	if (inP != NULL) {
		inP+=inOff;
	}

	if (outP != NULL) {
		outP+=outOff;
	}

	DWORD resLen = 0;

	WINBOOL succ = DeviceIoControl(h, (DWORD) ctrlCode, inP, inLen, outP, outLen, &resLen, NULL);
	if (succ) {
		return resLen;
	}

	throwUnknownError(env, GetLastError());
	return 0;

}






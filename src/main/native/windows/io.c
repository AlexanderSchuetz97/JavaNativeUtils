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
		jthrowCC_IllegalArgumentException_1(env, "path is null");
		return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}

	DWORD mode = 0;
	switch(jenum_ordinal(env, openMode)) {
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
			jthrowCC_IllegalArgumentException_1(env, "invalid openMode");
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



	LPCSTR str = (*env)->GetStringUTFChars(env, path, NULL);
	if (str == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}


	HANDLE h = CreateFileA(str, access, share, NULL, mode, attributes, NULL);

	if (h == INVALID_HANDLE_VALUE) {
		DWORD err = GetLastError();
		switch(err) {
		case (ERROR_SHARING_VIOLATION):
			jthrowCC_SharingViolationException_1(env, str, NULL, NULL);
			break;
		case (ERROR_FILE_EXISTS):
			jthrowCC_FileAlreadyExistsException_1(env, str, NULL, NULL);
			break;
		default:
			jthrow_UnknownNativeErrorException_1(env, err);
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
		jthrowCC_IllegalArgumentException_1(env, "path is null");
		return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}

	DWORD mode = 0;
	switch(jenum_ordinal(env, openMode)) {
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
			jthrowCC_IllegalArgumentException_1(env, "invalid openMode");
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
			jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
			return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
		}

		switch(err) {
		case (ERROR_SHARING_VIOLATION):
			jthrowCC_SharingViolationException_1(env, p, NULL, NULL);
			break;
		case (ERROR_FILE_EXISTS):
			//TODO PATH?
			jthrowCC_FileAlreadyExistsException_1(env, p, NULL, NULL);
			break;
		default:
			jthrow_UnknownNativeErrorException_1(env, err);
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
		jthrow_InvalidFileDescriptorException(env);
		return;
	}

	if (!CloseHandle(h)) {
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
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
		jthrow_InvalidFileDescriptorException(env);
		return 0;
	}

	if (inBuffer != NULL) {
		inSize = (*env)->GetArrayLength(env, inBuffer);
		if (inOff < 0 || inLen < 0 || inSize < inOff+inLen) {
			jthrowCC_IllegalArgumentException_1(env, "inBuffer offset/length");
			return 0;
		}
	}

	if (outBuffer != NULL) {
		outSize = (*env)->GetArrayLength(env, outBuffer);
		if (outOff < 0 || outLen < 0 || outSize < outOff+outLen) {
			jthrowCC_IllegalArgumentException_1(env, "outBuffer offset/length");
			return 0;
		}
	}

	if (inBuffer != NULL) {
		in = (LPVOID) (*env)->GetByteArrayElements(env, inBuffer, NULL);
		if (in == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
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
			jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
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

	jthrow_UnknownNativeErrorException_1(env, GetLastError());
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
		jthrow_InvalidFileDescriptorException(env);
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

	jthrow_UnknownNativeErrorException_1(env, GetLastError());
	return 0;

}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ReadFile
 * Signature: (J[BII)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ReadFile__J_3BII
  (JNIEnv * env, jobject inst, jlong jhandle, jbyteArray jbuf, jint off, jint len) {
	HANDLE h = (HANDLE) (uintptr_t) jhandle;

	if (off < 0) {
		jthrowCC_IllegalArgumentException_1(env, "off");
		return -1;
	}

	if (len < 0) {
		jthrowCC_IllegalArgumentException_1(env, "off");
		return -1;
	}

	if (h == INVALID_HANDLE_VALUE) {
		jthrow_InvalidFileDescriptorException(env);
		return -1;
	}

	if (jbuf == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return -1;
	}

	if ((*env)->GetArrayLength(env, jbuf) < len) {
		jthrowCC_IllegalArgumentException_1(env, "buf.len < len");
		return -1;
	}


	if (len == 0) {
		return 0;
	}

	DWORD read = 0;

	jbyte* buf = (*env)->GetByteArrayElements(env, jbuf, NULL);
	if (buf == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return -1;
	}

	LPVOID vbuf = (LPVOID) buf;
	vbuf+=off;

	if (!ReadFile(h, vbuf, len, &read, NULL)) {
		DWORD err = GetLastError();
		(*env)->ReleaseByteArrayElements(env, jbuf, buf, JNI_ABORT);
		jthrow_UnknownNativeErrorException_1(env, err);
		return -1;
	}

	(*env)->ReleaseByteArrayElements(env, jbuf, buf, JNI_OK);
	return read;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ReadFile
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ReadFile__JJI
  (JNIEnv * env, jobject inst, jlong jhandle, jlong ptr, jint len) {

	HANDLE h = (HANDLE) (uintptr_t) jhandle;

	if (h == INVALID_HANDLE_VALUE) {
		jthrow_InvalidFileDescriptorException(env);
		return -1;
	}


	DWORD read = 0;

	if (!ReadFile(h, (LPVOID) (uintptr_t) ptr, len, &read, NULL)) {
		DWORD err = GetLastError();
		jthrow_UnknownNativeErrorException_1(env, err);
		return -1;
	}

	return read;
}



/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ReadFile
 * Signature: (JJIJJ)I
 */

JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ReadFile__JJIJJ
  (JNIEnv * env, jobject inst, jlong jhandle, jlong ptr, jint len, jlong overlapped, jlong event) {

	HANDLE h = (HANDLE) (uintptr_t) jhandle;
	if (h == INVALID_HANDLE_VALUE) {
		jthrow_InvalidFileDescriptorException(env);
		return 0;
	}

	HANDLE e = (HANDLE) (uintptr_t) event;
	if (e == INVALID_HANDLE_VALUE) {
		jthrowCC_IllegalArgumentException_1(env, "event");
		return 0;
	}

	if (ptr == 0) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}


	LPOVERLAPPED lp = overlapped != 0 ? (LPOVERLAPPED) (uintptr_t) overlapped : malloc(sizeof(OVERLAPPED));
	if (lp == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "malloc");
		return 0;
	}

	memset((void*)lp, 0, sizeof(OVERLAPPED));
	lp->hEvent = e;

	DWORD read = 0;
	if (!ReadFile(h, (LPVOID) (uintptr_t) ptr, len, &read, lp)) {
		DWORD err = GetLastError();
		if (err == ERROR_IO_PENDING) {
			return (jlong) (uintptr_t) lp;
		}

		if (overlapped != 0) {
			free(lp);
		}
		jthrow_UnknownNativeErrorException_1(env, err);
	}


	return (jlong) (uintptr_t) lp;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WriteFile
 * Signature: (J[BII)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_WriteFile__J_3BII
(JNIEnv * env, jobject inst, jlong jhandle, jbyteArray jbuf, jint off, jint len) {
	HANDLE h = (HANDLE) (uintptr_t) jhandle;

	if (off < 0) {
		jthrowCC_IllegalArgumentException_1(env, "off");
		return -1;
	}

	if (len < 0) {
		jthrowCC_IllegalArgumentException_1(env, "len");
		return -1;
	}

	if (h == INVALID_HANDLE_VALUE) {
		jthrow_InvalidFileDescriptorException(env);
		return -1;
	}

	if (jbuf == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return -1;
	}

	if ((*env)->GetArrayLength(env, jbuf) - off < len) {
		jthrowCC_IllegalArgumentException_1(env, "buf.len < len");
		return -1;
	}


	if (len == 0) {
		return 0;
	}

	DWORD read = 0;

	jbyte* buf = (*env)->GetByteArrayElements(env, jbuf, NULL);
	if (buf == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return -1;
	}

	LPVOID vbuf = (LPVOID) buf;
	vbuf+=off;

	if (!WriteFile(h, vbuf, len, &read, NULL)) {
		DWORD err = GetLastError();
		(*env)->ReleaseByteArrayElements(env, jbuf, buf, JNI_ABORT);
		jthrow_UnknownNativeErrorException_1(env, err);
		return -1;
	}

	(*env)->ReleaseByteArrayElements(env, jbuf, buf, JNI_ABORT);
	return read;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WriteFile
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_WriteFile__JJI
(JNIEnv * env, jobject inst, jlong jhandle, jlong ptr, jint len) {

	HANDLE h = (HANDLE) (uintptr_t) jhandle;

	if (h == INVALID_HANDLE_VALUE) {
		jthrow_InvalidFileDescriptorException(env);
		return -1;
	}


	DWORD read = 0;

	if (!WriteFile(h, (LPVOID) (uintptr_t) ptr, len, &read, NULL)) {
		DWORD err = GetLastError();
		jthrow_UnknownNativeErrorException_1(env, err);
		return -1;
	}

	return read;
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WriteFile
 * Signature: (JJIJJ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_WriteFile__JJIJJ
(JNIEnv * env, jobject inst, jlong jhandle, jlong ptr, jint len, jlong overlapped, jlong event) {

	HANDLE h = (HANDLE) (uintptr_t) jhandle;
	if (h == INVALID_HANDLE_VALUE) {
		jthrow_InvalidFileDescriptorException(env);
		return 0;
	}

	HANDLE e = (HANDLE) (uintptr_t) event;
	if (e == INVALID_HANDLE_VALUE) {
		jthrowCC_IllegalArgumentException_1(env, "event");
		return 0;
	}

	if (ptr == 0) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return 0;
	}


	LPOVERLAPPED lp = overlapped != 0 ? (LPOVERLAPPED) (uintptr_t) overlapped : malloc(sizeof(OVERLAPPED));
	if (lp == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "malloc");
		return 0;
	}

	memset((void*)lp, 0, sizeof(OVERLAPPED));

	lp->hEvent = e;

	DWORD read = 0;
	if (!WriteFile(h, (LPVOID) (uintptr_t) ptr, len, &read, lp)) {
		DWORD err = GetLastError();
		if (err == ERROR_IO_PENDING) {
			return (jlong) (uintptr_t) lp;
		}

		if (overlapped == 0) {
			free(lp);
		}

		jthrow_UnknownNativeErrorException_1(env, err);
	}


	return (jlong) (uintptr_t) lp;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetOverlappedResult
 * Signature: (JJZ)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetOverlappedResult
  (JNIEnv * env, jobject inst, jlong handle, jlong overlapped, jboolean wait) {
	LPOVERLAPPED lpo = (LPOVERLAPPED) (uintptr_t) overlapped;
	HANDLE hdl = (HANDLE) (uintptr_t) handle;

	if (lpo == NULL) {
		jthrowCC_NullPointerException_1(env, "overlapped");
		return -1;
	}

	if (hdl == INVALID_HANDLE_VALUE) {
		jthrow_InvalidFileDescriptorException(env);
		return -1;
	}

	DWORD res = 0;
	if (GetOverlappedResult(hdl, lpo, &res, wait)) {
		return res;
	}

	DWORD err = GetLastError();
	if (err == ERROR_IO_PENDING) {
		return -1;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
	return -1;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateFileMappingA
 * Signature: (JJIIILjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateFileMappingA
  (JNIEnv * env, jobject inst, jlong handle, jlong sec, jint flprot, jint maxSizeHigh, jint maxSizeLow, jstring name) {

	LPCSTR lpName = NULL;
	if (name != NULL) {
		lpName = (*env)->GetStringUTFChars(env, name, NULL);
		if (lpName == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
			return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
		}
	}

	HANDLE result = CreateFileMappingA((HANDLE) (uintptr_t) handle, (LPSECURITY_ATTRIBUTES) (uintptr_t) sec, (DWORD) flprot, (DWORD) maxSizeHigh, (DWORD) maxSizeLow, lpName);

	if (name != NULL) {
		(*env)->ReleaseStringUTFChars(env, name, lpName);
	}

	if (result != 0 && result != INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			//TODO
		}
		return (jlong) (uintptr_t) result;
	}

	jthrow_UnknownNativeErrorException_1(env, GetLastError());

	return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    OpenFileMappingA
 * Signature: (IZLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_OpenFileMappingA
  (JNIEnv * env, jobject inst, jint acc, jboolean inherit, jstring name) {
	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name is null");
		return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}

	LPCSTR lpName = (*env)->GetStringUTFChars(env, name, NULL);
	if (lpName == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}

	HANDLE result = OpenFileMappingA((DWORD) acc, (BOOL) inherit, lpName);

	(*env)->ReleaseStringUTFChars(env, name, lpName);

	if (result != 0 && result != INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			//TODO
		}
		return (jlong) (uintptr_t) result;
	}

	jthrow_UnknownNativeErrorException_1(env, GetLastError());

	return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    _MapViewOfFileEx
 * Signature: (JIIIIJ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil__1MapViewOfFileEx
  (JNIEnv * env, jclass inst, jlong handle, jint acc, jint offHigh, jint offLow, jint numOfBytes, jlong baseAddr) {
	HANDLE h = (HANDLE) (uintptr_t) handle;
	if (h == INVALID_HANDLE_VALUE) {
		jthrow_InvalidFileDescriptorException(env);
		return 0;
	}

	if (numOfBytes <= 0) {
		jthrowCC_IllegalArgumentException_1(env, "num bytes to map <= 0");
		return 0;
	}


	LPVOID ptr = MapViewOfFileEx(h, (DWORD) acc, (DWORD) offHigh, (DWORD) offLow, (DWORD) numOfBytes, (LPVOID) (uintptr_t) baseAddr);
	if (ptr == NULL) {
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
		return 0;
	}

	return (jlong) (uintptr_t) ptr;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    UnmapViewOfFile
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil__1UnmapViewOfFile
  (JNIEnv * env, jclass inst, jlong addr) {
	LPVOID lpv = (LPVOID) (uintptr_t) addr;
	if (lpv == NULL) {
		jthrowCC_NullPointerException_1(env, "addr is null");
		return;
	}

	if (!UnmapViewOfFile(lpv)) {
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateNamedPipeA
 * Signature: (Ljava/lang/String;IIIII)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateNamedPipeA
  (JNIEnv * env, jobject inst, jstring name, jint dwOpenMode, jint dwPipeMode, jint nMaxInstances, jint nOutBufferSize, jint nInBufferSize, jint nDefaultTimeOut, jlong lpSecurityAttributes) {
	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}

	LPCSTR cstr = (*env)->GetStringUTFChars(env, name, NULL);
	if (cstr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
	}

	HANDLE hdl = CreateNamedPipeA(cstr, (DWORD) dwOpenMode, (DWORD)  dwPipeMode, (DWORD) nMaxInstances, (DWORD) nOutBufferSize, (DWORD) nInBufferSize, (DWORD) nDefaultTimeOut, (LPSECURITY_ATTRIBUTES) (uintptr_t) lpSecurityAttributes);
	if (hdl != INVALID_HANDLE_VALUE) {
		(*env)->ReleaseStringUTFChars(env, name, cstr);
		return (jlong) (uintptr_t) hdl;
	}

	DWORD err = GetLastError();
	(*env)->ReleaseStringUTFChars(env, name, cstr);

	jthrow_UnknownNativeErrorException_1(env, err);

	return (jlong) (uintptr_t) INVALID_HANDLE_VALUE;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConnectNamedPipe
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ConnectNamedPipe__J
  (JNIEnv * env, jobject inst, jlong hdl) {
	if (ConnectNamedPipe((HANDLE) (uintptr_t) hdl, NULL) == 0) {
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
	}
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConnectNamedPipe
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ConnectNamedPipe__JJ
  (JNIEnv * env, jobject inst, jlong hdl, jlong event) {
	HANDLE e = (HANDLE) (uintptr_t) event;
	if (e == INVALID_HANDLE_VALUE) {
		jthrowCC_IllegalArgumentException_1(env, "event");
		return 0;
	}


	LPOVERLAPPED lp = malloc(sizeof(OVERLAPPED));
	if (lp == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "malloc");
		return 0;
	}

	memset((void*) lp, 0, sizeof(OVERLAPPED));
	lp->hEvent = e;

	if (ConnectNamedPipe((HANDLE) (uintptr_t) hdl, lp) == 0) {
		DWORD err = GetLastError();
		if (err == ERROR_IO_PENDING) {
			return (jlong) (uintptr_t) lp;
		}
		free(lp);
		jthrow_UnknownNativeErrorException_1(env, err);
		return 0;
	}

	return (jlong) (uintptr_t) lp;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DisconnectNamedPipe
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_DisconnectNamedPipe
	(JNIEnv * env, jobject inst, jlong hdl) {
	if (DisconnectNamedPipe((HANDLE) (uintptr_t) hdl) == 0) {
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WaitNamedPipeA
 * Signature: (Ljava/lang/String;J)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_WaitNamedPipeA
  (JNIEnv * env, jobject inst, jstring name, jlong timeout) {
	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return false;
	}

	if (timeout < 0) {
		jthrowCC_IllegalArgumentException_1(env, "timeout < 0");
		return false;
	}

	LPCSTR cstr = (*env)->GetStringUTFChars(env, name, NULL);
	if (cstr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return false;
	}

	if (WaitNamedPipeA(cstr, (DWORD) timeout) != 0) {
		(*env)->ReleaseStringUTFChars(env, name, cstr);
		return true;
	}

	DWORD err = GetLastError();
	(*env)->ReleaseStringUTFChars(env, name, cstr);
	if (err == ERROR_SEM_TIMEOUT) {
		return false;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
	return false;
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    FlushFileBuffers
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_FlushFileBuffers
	(JNIEnv * env, jobject inst, jlong hdl) {
	if (FlushFileBuffers((HANDLE) (uintptr_t) hdl) == 0) {
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
	}
}



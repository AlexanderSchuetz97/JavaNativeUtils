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
 * Method:    CreateEventA
 * Signature: (JZZLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateEventA
  (JNIEnv * env, jobject inst, jlong attrPtr, jboolean manual, jboolean inital, jstring name) {
	LPCSTR cname = NULL;
	if (name != NULL) {
		cname = (*env)->GetStringUTFChars(env, name, NULL);
		if (cname == NULL) {
			throwOOM(env, "GetStringUTFChars");
			return -1;
		}
	}

	HANDLE h = CreateEventA((LPSECURITY_ATTRIBUTES) (uintptr_t) attrPtr, manual, inital, cname);
	if (h == INVALID_HANDLE_VALUE) {
		throwUnknownError(env, GetLastError());
	}

	if (name != NULL) {
		(*env)->ReleaseStringUTFChars(env, name, cname);
	}

	return (jlong) (uintptr_t) h;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ResetEvent
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ResetEvent
  (JNIEnv * env, jobject inst, jlong handle) {
	HANDLE h = (HANDLE) (uintptr_t) handle;
	if (h == INVALID_HANDLE_VALUE) {
		throwBadFileDescriptor(env);
		return;
	}

	if (!ResetEvent(h)) {
		throwUnknownError(env, GetLastError());
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WaitForSingleObject
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_WaitForSingleObject
  (JNIEnv * env, jobject inst, jlong handle, jint timeout) {

	HANDLE h = (HANDLE) (uintptr_t) handle;
	if (h == INVALID_HANDLE_VALUE) {
		throwBadFileDescriptor(env);
		return false;
	}

	DWORD result = WaitForSingleObject(h, (DWORD) timeout);

	switch(result) {
	case (WAIT_ABANDONED):
		throwMutexAbandonedException(env, handle);
		return false;
	case(WAIT_TIMEOUT):
			return false;
	case(WAIT_OBJECT_0):
			return true;
	default: {
			DWORD err = GetLastError();
			if (err == ERROR_INVALID_HANDLE) {
				throwBadFileDescriptor(env);
				return false;
			}
			throwUnknownError(env, err);
			return false;
		}
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WaitForMultipleObjects
 * Signature: ([JIZ)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_WaitForMultipleObjects
  (JNIEnv * env, jobject inst, jlongArray handles, jint timeout, jboolean waitAll) {

	if (handles == NULL) {
		throwNullPointerException(env, "handles");
		return -1;
	}

	jint result = -1;
	HANDLE* h;
	DWORD len = (DWORD) (*env)->GetArrayLength(env, handles);

	if (len == 0) {
		throwIllegalArgumentsExc(env, "handles.lenght == 0");
		return -1;
	}

	if (len > MAXIMUM_WAIT_OBJECTS) {
		throwIllegalArgumentsExc(env, "too many handles");
		return -1;
	}

	//64 bit
	if (sizeof(HANDLE) == sizeof(jlong)) {
		h = (HANDLE*) (*env)->GetLongArrayElements(env, handles, NULL);
		if (h == NULL) {
			throwOOM(env, "GetLongArrayElements");
			return -1;
		}
	//32 bit
	} else {
		jlong * tmp = (*env)->GetLongArrayElements(env, handles, NULL);
		if (tmp == NULL) {
			throwOOM(env, "GetLongArrayElements");
			return -1;
		}

		h = malloc(sizeof(HANDLE)*len);
		if (h == NULL) {
			(*env)->ReleaseLongArrayElements(env, handles, (jlong*) h, JNI_ABORT);
			throwOOM(env, "malloc");
			return -1;
		}

		for (DWORD i = 0; i < len; i++) {
			h[i] = (HANDLE) (uintptr_t) tmp[i];
		}

		(*env)->ReleaseLongArrayElements(env, handles, (jlong*) tmp, JNI_ABORT);
	}

	DWORD res = WaitForMultipleObjects(len, (const HANDLE*) h, (WINBOOL) waitAll, (DWORD) timeout);

	if (sizeof(HANDLE) == sizeof(jlong)) {
		(*env)->ReleaseLongArrayElements(env, handles, (jlong*) h, JNI_ABORT);
	} else {
		free(h);
	}

	switch (res) {
		case (WAIT_TIMEOUT): {
			return -1;
		}
		case (WAIT_FAILED): {
			DWORD err = GetLastError();
			if (err == ERROR_INVALID_HANDLE) {
				throwBadFileDescriptor(env);
				return -1;
			}
			throwUnknownError(env, err);
			return -1;
		}
		default: {
			if (WAIT_ABANDONED_0 <= res && res < WAIT_ABANDONED_0 + len ) {
				if (waitAll) {
					throwMutexAbandonedException(env, -1);
					return -1;
				}

				jlong theLong = -1;
				(*env)->GetLongArrayRegion(env, handles, res-WAIT_ABANDONED_0, 1, &theLong);

				throwMutexAbandonedException(env, theLong);
				return -1;
			}

			DWORD off = res - WAIT_OBJECT_0;

			if (off >= len) {
				//SHOULDNT HAPPEN
				throwUnknownError(env, GetLastError());
				return -1;
			}

			if (waitAll) {
				return 0;
			}

			return (jint) off;
		}
	}
}

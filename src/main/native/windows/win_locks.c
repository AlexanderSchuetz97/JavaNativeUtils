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
#include <io.h>
#include <sys/locking.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <handleapi.h>
#include <winerror.h>
#include <errhandlingapi.h>
#include <fileapi.h>

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    _locking
 * Signature: (ILio/github/alexanderschuetz97/nativeutils/NativeUtil/_locking_Mode;J)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil__1locking
  (JNIEnv * env, jobject inst, jint fd, jobject mode, jlong len) {
	if (fd == -1) {
		badFileDescriptor(env);
		return false;
	}

	int mMode = 0;
	switch(getEnumOrdinal(env, mode)) {
	case 0:
		mMode = _LK_LOCK;
		break;
	case 1:
		mMode = _LK_NBLCK;
		break;
	case 2:
		mMode = _LK_UNLCK;
		break;
	default:
		illegalArgs(env, "mode is invalid");
		return false;
	}


	if (_locking(fd, mMode, len) == -1) {
		int err = errno;
		printf("err %i\n", err);
		switch(err) {
		case EACCES:
			return false;
		case EBADF:
			badFileDescriptor(env);
			return false;
		case EDEADLOCK:
			return false;
		case EINVAL:
			illegalArgs(env, "_locking");
			return false;
		default:
			unknownError(env, err);
			return false;
		}
	}

	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    LockFileEx
 * Signature: (JZZJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_LockFileEx
  (JNIEnv * env, jobject inst, jlong fd, jboolean exclusive, jboolean failImmediately, jlong off, jlong len) {

	HANDLE h = (HANDLE) (uintptr_t) fd;
	if (h == INVALID_HANDLE_VALUE) {
		badFileDescriptor(env);
		return false;
	}

	OVERLAPPED lp;
	memset(&lp, 0, sizeof(OVERLAPPED));


	DWORD flags = 0;
	if (exclusive) {
		flags |= LOCKFILE_EXCLUSIVE_LOCK;
	}

	if (failImmediately) {
		flags |= LOCKFILE_FAIL_IMMEDIATELY;
	}

	//why windows
	DWORD low = (DWORD) len;
	DWORD high = (DWORD) (len >> 32);
	lp.Offset = (DWORD) off;
	lp.OffsetHigh = (DWORD) (off >> 32);

	if (LockFileEx(h, flags, 0, low, high, &lp) == 0) {
		DWORD error = GetLastError();
		switch(error) {
			case(ERROR_IO_PENDING):
				return false;
			default:
				unknownError(env, error);
				return false;
		}
	}

	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    UnlockFileEx
 * Signature: (JJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_UnlockFileEx
  (JNIEnv * env, jobject inst, jlong fd, jlong off, jlong len) {

	HANDLE h = (HANDLE) (uintptr_t) fd;
	if (h == INVALID_HANDLE_VALUE) {
		badFileDescriptor(env);
		return false;
	}

	OVERLAPPED lp;
	memset(&lp, 0, sizeof(OVERLAPPED));

	//why windows
	DWORD low = (DWORD) len;
	DWORD high = (DWORD) (len >> 32);
	lp.Offset = (DWORD) off;
	lp.OffsetHigh = (DWORD) (off >> 32);

	if (UnlockFileEx(h, 0, low, high, &lp) == 0) {
		DWORD error = GetLastError();
		switch(error) {
			case (ERROR_NOT_LOCKED):
				return false;
			default:
				unknownError(env, error);
				return false;
		}
	}

	return true;
}

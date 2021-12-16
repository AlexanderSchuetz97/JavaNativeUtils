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


#include "../common/jni/io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil.h"
#include "../common/common.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fnctl_F_GETLK
 * Signature: (IZJJ)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_fnctl_1F_1GETLK
  (JNIEnv * env, jobject inst, jint fd, jboolean exclusive, jlong start, jlong len) {
	if (start < 0) {
		throwIllegalArgumentsExc(env, "start of range invalid");
		return -1;
	}

	if (len < 0) {
		throwIllegalArgumentsExc(env, "length of range invalid");
		return -1;
	}

	if (fd == -1) {
		badFileDescriptor(env);
		return -1;
	}



	struct flock theLock;
	theLock.l_pid = -1;
	theLock.l_len = len;
	theLock.l_start = start;
	theLock.l_whence = SEEK_SET;
	theLock.l_type = exclusive ? F_WRLCK : F_RDLCK;

	while (fcntl(fd, F_GETLK, &theLock) == -1) {
		int err = errno;
		switch(err) {
			case (EINTR):
			case (EAGAIN):
				break;
			case (EBADF):
				badFileDescriptor(env);
				return false;
			default:
				unknownError(env, err);
				return false;
		}
	}

	return theLock.l_pid;
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fnctl_F_SETLKW
 * Signature: (ILio/github/alexanderschuetz97/nativeutils/NativeUtils/fnctl_F_SETLK_Mode;JJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_fnctl_1F_1SETLKW
  (JNIEnv * env, jobject inst, jint fd, jobject mode, jlong start, jlong len) {

	if (start < 0) {
		throwIllegalArgumentsExc(env, "start of range invalid");
		return;
	}

	if (len < 0) {
		throwIllegalArgumentsExc(env, "length of range invalid");
		return;
	}

	int mMode = getEnumOrdinal(env, mode);
	if (mMode < 0 || mMode > 2) {
		throwIllegalArgumentsExc(env, "mode invalid");
		return;
	}

	if (fd == -1) {
		badFileDescriptor(env);
		return;
	}

	struct flock theLock;
	theLock.l_pid = -1;
	theLock.l_len = len;
	theLock.l_start = start;
	theLock.l_whence = SEEK_SET;
	theLock.l_type = mMode;

	while (fcntl(fd, F_SETLKW, &theLock) == -1) {
		int err = errno;
		switch(err) {
			case (EINTR):
			case (EAGAIN):
				break;
			case (EBADF):
				badFileDescriptor(env);
				return;
			default:
				unknownError(env, err);
				return;
		}
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fnctl_F_SETLK
 * Signature: (ILio/github/alexanderschuetz97/nativeutils/NativeUtils/fnctl_F_SETLK_Mode;JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_fnctl_1F_1SETLK
  (JNIEnv * env, jobject inst, jint fd, jobject mode, jlong start, jlong len) {

	if (start < 0) {
		throwIllegalArgumentsExc(env, "start of range invalid");
		return false;
	}

	if (len < 0) {
		throwIllegalArgumentsExc(env, "length of range invalid");
		return false;
	}

	int mMode = getEnumOrdinal(env, mode);
	if (mMode < 0 || mMode > 2) {
		throwIllegalArgumentsExc(env, "mode invalid");
		return false;
	}

	if (fd == -1) {
		badFileDescriptor(env);
		return false;
	}

	struct flock theLock;
	theLock.l_pid = -1;
	theLock.l_len = len;
	theLock.l_start = start;
	theLock.l_whence = SEEK_SET;
	theLock.l_type = mMode;


	while (fcntl(fd, F_SETLK, &theLock) == -1) {
		int err = errno;
		switch(err) {
			case (EINTR):
				continue;
			case (EACCES):
			case (EAGAIN):
				return false;
			case (EBADF):
				badFileDescriptor(env);
				return false;
			default:
				unknownError(env, err);
				return false;
		}
	}

	return true;
}




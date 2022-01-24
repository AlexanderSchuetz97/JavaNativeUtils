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

#include "../common/jni/io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil.h"
#include "../common/common.h"
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

jobject fillStat(JNIEnv * env, struct stat* theStat) {
	jobject myStat = (*env) -> NewObject(env, StatClass, StatClassConstructor);
	if (myStat == NULL) {
		//OOM already thrown
		return NULL;
	}

	(*env) -> SetLongField(env, myStat, StatClass_dev, (jlong) theStat->st_dev);
	(*env) -> SetLongField(env, myStat, StatClass_ino, (jlong) theStat->st_ino);
	(*env) -> SetLongField(env, myStat, StatClass_mode, (jlong) theStat->st_mode);
	(*env) -> SetLongField(env, myStat, StatClass_nlink, (jlong) theStat->st_nlink);
	(*env) -> SetLongField(env, myStat, StatClass_uid, (jlong) theStat->st_uid);
	(*env) -> SetLongField(env, myStat, StatClass_gid, (jlong) theStat->st_gid);
	(*env) -> SetLongField(env, myStat, StatClass_rdev, (jlong) theStat->st_rdev);
	(*env) -> SetLongField(env, myStat, StatClass_size, (jlong) theStat->st_size);
	(*env) -> SetLongField(env, myStat, StatClass_blksize, (jlong) theStat->st_blksize);
	(*env) -> SetLongField(env, myStat, StatClass_blocks, (jlong) theStat->st_blocks);
	(*env) -> SetLongField(env, myStat, StatClass_atime, (jlong) theStat->st_atime);
	(*env) -> SetLongField(env, myStat, StatClass_mtime, (jlong) theStat->st_mtime);
	(*env) -> SetLongField(env, myStat, StatClass_ctime, (jlong) theStat->st_ctime);

	return myStat;
}

void handleError(JNIEnv * env, int err, const char* path) {

	switch(err) {
	case (EACCES):
		throwFSAccessDenied(env, path, NULL, "Search permission is denied for one of the directories in the path prefix of path.");
		return;
	case (EBADF):
		throwBadFileDescriptor(env);
		return;
	case (ELOOP):
		throwFSLoop(env, path);
		return;
	case (ENAMETOOLONG):
		throwInvalidPath(env, path, "path is too long.");
		return;
	case (ENOENT):
		throwFileNotFoundExc(env, path);
		return;
	case (ENOMEM):
		throwOOM(env, "Insufficient kernel memory was available.");
		return;
	case (ENOTDIR):
		throwInvalidPath(env, path, "A component of the path prefix of path is not a directory. ");
		return;
	case (EIO):
		throwIOExc(env, "An I/O error occurred.");
		return;
	default:
		throwUnknownError(env, err);
		return;
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    stat
 * Signature: (Ljava/lang/String;)Lio/github/alexanderschuetz97/nativeutils/NativeUtil/Stat;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_stat
  (JNIEnv * env, jobject inst, jstring path) {
	if (path == NULL) {
		throwIllegalArgumentsExc(env, "path is null");
		return NULL;
	}

	struct stat theStat;
	memset(&theStat, 0, sizeof(struct stat));

	const char* thePath = (*env) ->GetStringUTFChars(env, path, NULL);
	if (thePath == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return NULL;
	}

	if (stat(thePath, &theStat) != 0) {
		handleError(env, errno, thePath);
		(*env) ->ReleaseStringUTFChars(env, path, thePath);
		return NULL;
	}

	(*env) ->ReleaseStringUTFChars(env, path, thePath);

	return fillStat(env, &theStat);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fstat
 * Signature: (I)Lio/github/alexanderschuetz97/nativeutils/NativeUtil/Stat;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_fstat
  (JNIEnv *env, jobject inst, jint fd) {

	if (fd == -1) {
		throwBadFileDescriptor(env);
		return NULL;
	}

	struct stat theStat;
	memset(&theStat, 0, sizeof(struct stat));

	if (fstat(fd, &theStat) != 0) {
		handleError(env, errno, NULL);
		return NULL;
	}

	return fillStat(env, &theStat);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    lstat
 * Signature: (Ljava/lang/String;)Lio/github/alexanderschuetz97/nativeutils/NativeUtil/Stat;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_lstat
	(JNIEnv * env, jobject inst, jstring path) {
	if (path == NULL) {
		throwIllegalArgumentsExc(env, "path is null");
		return NULL;
	}

	struct stat theStat;
	memset(&theStat, 0, sizeof(struct stat));

	const char* thePath = (*env) ->GetStringUTFChars(env, path, NULL);
	if (thePath == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return NULL;
	}

	if (lstat(thePath, &theStat) != 0) {
		handleError(env, errno, NULL);
		(*env) ->ReleaseStringUTFChars(env, path, thePath);
		return NULL;
	}


	(*env) ->ReleaseStringUTFChars(env, path, thePath);

	return fillStat(env, &theStat);
}

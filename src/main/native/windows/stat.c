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
#include <sys/stat.h>
#include <errno.h>
#include <fileapi.h>
#include <errhandlingapi.h>



void handleError(JNIEnv * env, int err, const char* path) {
	if (path == NULL) {
		path = "";
	}
	//Truely a splendid documentation on this part microsoft
	switch(err) {
		case(ENOENT):
			throwFileNotFoundExc(env, path);
			break;
		case (EINVAL):
			illegalArgs(env, "path is invalid");
			break;
		default:
			unknownError(env, err);
			break;
	}
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    _stat64
 * Signature: (Ljava/lang/String;)Lio/github/alexanderschuetz97/nativeutils/structs/Stat;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil__1stat64
  (JNIEnv * env, jobject inst, jstring path) {

	if (path == NULL) {
		illegalArgs(env, "path is null");
		return NULL;
	}

	const char* pathString = (*env)->GetStringUTFChars(env, path, NULL);
	if (pathString == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return NULL;
	}

	struct _stat64 theStat;
	memset(&theStat, 0, sizeof(struct _stat64));

	int rid = _stat64(pathString, &theStat);


	if (rid != 0) {
		handleError(env, errno, pathString);
		(*env)->ReleaseStringUTFChars(env, path, pathString);
		return NULL;
	}
	(*env)->ReleaseStringUTFChars(env, path, pathString);

	jobject myStat = (*env) -> NewObject(env, StatClass, StatClassConstructor);
	if (myStat == NULL) {
		//OOM already thrown
		return NULL;
	}

	(*env) -> SetLongField(env, myStat, StatClass_dev, (jlong) theStat.st_dev);
	(*env) -> SetLongField(env, myStat, StatClass_ino, (jlong) theStat.st_ino);
	(*env) -> SetLongField(env, myStat, StatClass_mode, (jlong) theStat.st_mode);
	(*env) -> SetLongField(env, myStat, StatClass_nlink, (jlong) theStat.st_nlink);
	(*env) -> SetLongField(env, myStat, StatClass_uid, (jlong) theStat.st_uid);
	(*env) -> SetLongField(env, myStat, StatClass_gid, (jlong) theStat.st_gid);
	(*env) -> SetLongField(env, myStat, StatClass_rdev, (jlong) theStat.st_rdev);
	(*env) -> SetLongField(env, myStat, StatClass_size, (jlong) theStat.st_size);
	(*env) -> SetLongField(env, myStat, StatClass_blksize, (jlong) 0);
	(*env) -> SetLongField(env, myStat, StatClass_blocks, (jlong) 0);
	(*env) -> SetLongField(env, myStat, StatClass_atime, (jlong) theStat.st_atime);
	(*env) -> SetLongField(env, myStat, StatClass_mtime, (jlong) theStat.st_mtime);
	(*env) -> SetLongField(env, myStat, StatClass_ctime, (jlong) theStat.st_ctime);

	return myStat;

}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFileAttributesEx
 * Signature: (Ljava/lang/String;)Lio/github/alexanderschuetz97/nativeutils/api/structs/Stat;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetFileAttributesEx
  (JNIEnv * env, jobject inst, jstring path) {

	if (path == NULL) {
		illegalArgs(env, "path is null");
		return NULL;
	}

	LPCSTR pathString = (*env)->GetStringUTFChars(env, path, NULL);
	if (pathString == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return NULL;
	}

	struct _WIN32_FILE_ATTRIBUTE_DATA data;
	memset(&data, 0, sizeof(struct _WIN32_FILE_ATTRIBUTE_DATA));

	WINBOOL result = GetFileAttributesExA(pathString, GetFileExInfoStandard, &data);

	if (result == 0) {
		DWORD err = GetLastError();
		unknownError(env, err);
		return NULL;
	}

	jobject myStat = (*env) -> NewObject(env, Win32FileAttributeData, Win32FileAttributeDataConstructor);
	if (myStat == NULL) {
		//OOM already thrown
		return NULL;
	}

	(*env) -> SetLongField(env, myStat, Win32FileAttributeData_dwFileAttributes, (jlong) data.dwFileAttributes);
	(*env) -> SetLongField(env, myStat, Win32FileAttributeData_nFileSizeLow, (jlong) data.nFileSizeLow);
	(*env) -> SetLongField(env, myStat, Win32FileAttributeData_nFileSizeHigh, (jlong) data.nFileSizeHigh);
	(*env) -> SetLongField(env, myStat, Win32FileAttributeData_ftCreationTimeHigh, (jlong) data.ftCreationTime.dwHighDateTime);
	(*env) -> SetLongField(env, myStat, Win32FileAttributeData_ftCreationTimeLow, (jlong) data.ftCreationTime.dwLowDateTime);
	(*env) -> SetLongField(env, myStat, Win32FileAttributeData_ftLastWriteTimeHigh, (jlong) data.ftLastWriteTime.dwHighDateTime);
	(*env) -> SetLongField(env, myStat, Win32FileAttributeData_ftLastWriteTimeLow, (jlong) data.ftLastWriteTime.dwLowDateTime);
	(*env) -> SetLongField(env, myStat, Win32FileAttributeData_ftLastAccessTimeHigh, (jlong) data.ftLastAccessTime.dwHighDateTime);
	(*env) -> SetLongField(env, myStat, Win32FileAttributeData_ftLastAccessTimeLow, (jlong) data.ftLastAccessTime.dwLowDateTime);

	return myStat;
}

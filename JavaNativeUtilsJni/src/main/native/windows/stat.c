//
// Copyright Alexander Schütz, 2021-2024
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
			jthrowCC_FileNotFoundException_1(env, path);
			break;
		case (EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "path is invalid");
			break;
		default:
			jthrow_UnknownNativeErrorException_1(env, err);
			break;
	}
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    _stat64
 * Signature: (Ljava/lang/String;)Leu/aschuetz/nativeutils/structs/Stat;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil__1stat64
  (JNIEnv * env, jobject inst, jstring path) {

	if (path == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "path is null");
		return NULL;
	}

	const char* pathString = (*env)->GetStringUTFChars(env, path, NULL);
	if (pathString == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
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

	jobject myStat = jnew_Stat(env);
	if (myStat == NULL) {
		return NULL;
	}

	jset_Stat_dev(env, myStat, (jlong) theStat.st_dev);
	jset_Stat_ino(env, myStat, (jlong) theStat.st_ino);
	jset_Stat_mode(env, myStat, (jlong) theStat.st_mode);
	jset_Stat_nlink(env, myStat, (jlong) theStat.st_nlink);
	jset_Stat_uid(env, myStat, (jlong) theStat.st_uid);
	jset_Stat_gid(env, myStat, (jlong) theStat.st_gid);
	jset_Stat_rdev(env, myStat, (jlong) theStat.st_rdev);
	jset_Stat_size(env, myStat, (jlong) theStat.st_size);
	jset_Stat_blksize(env, myStat, (jlong) 0);
	jset_Stat_blocks(env, myStat, (jlong) 0);
	jset_Stat_atime(env, myStat, (jlong) theStat.st_atime);
	jset_Stat_mtime(env, myStat, (jlong) theStat.st_mtime);
	jset_Stat_ctime(env, myStat, (jlong) theStat.st_ctime);

	return myStat;

}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFileAttributesEx
 * Signature: (Ljava/lang/String;)Leu/aschuetz/nativeutils/api/structs/Stat;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetFileAttributesEx
  (JNIEnv * env, jobject inst, jstring path) {

	if (path == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "path is null");
		return NULL;
	}

	LPCSTR pathString = (*env)->GetStringUTFChars(env, path, NULL);
	if (pathString == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return NULL;
	}

	struct _WIN32_FILE_ATTRIBUTE_DATA data;
	memset(&data, 0, sizeof(struct _WIN32_FILE_ATTRIBUTE_DATA));

	WINBOOL result = GetFileAttributesExA(pathString, GetFileExInfoStandard, &data);

	(*env)->ReleaseStringUTFChars(env, path, pathString);

	if (result == 0) {
		DWORD err = GetLastError();
		jthrow_UnknownNativeErrorException_1(env, err);
		return NULL;
	}

	jobject myStat = jnew_Win32FileAttributeData(env);
	if (myStat == NULL) {
		return NULL;
	}

	jset_Win32FileAttributeData_dwFileAttributes(env, myStat, (jlong) data.dwFileAttributes);
	jset_Win32FileAttributeData_nFileSizeLow(env, myStat, (jlong) data.nFileSizeLow);
	jset_Win32FileAttributeData_nFileSizeHigh(env, myStat, (jlong) data.nFileSizeHigh);
	jset_Win32FileAttributeData_ftCreationTimeHigh(env, myStat, (jlong) data.ftCreationTime.dwHighDateTime);
	jset_Win32FileAttributeData_ftCreationTimeLow(env, myStat, (jlong) data.ftCreationTime.dwLowDateTime);
	jset_Win32FileAttributeData_ftLastWriteTimeHigh(env, myStat, (jlong) data.ftLastWriteTime.dwHighDateTime);
	jset_Win32FileAttributeData_ftLastWriteTimeLow(env, myStat, (jlong) data.ftLastWriteTime.dwLowDateTime);
	jset_Win32FileAttributeData_ftLastAccessTimeHigh(env, myStat, (jlong) data.ftLastAccessTime.dwHighDateTime);
	jset_Win32FileAttributeData_ftLastAccessTimeLow(env, myStat, (jlong) data.ftLastAccessTime.dwLowDateTime);

	return myStat;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFileAttributesA
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetFileAttributesA
  (JNIEnv * env, jobject inst, jstring path) {
	if (path == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "path is null");
		return 0;
	}

	LPCSTR pathString = (*env)->GetStringUTFChars(env, path, NULL);
	if (pathString == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return 0;
	}

	DWORD attr = GetFileAttributesA(pathString);
	(*env)->ReleaseStringUTFChars(env, path, pathString);
	if (attr == INVALID_FILE_ATTRIBUTES) {
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
		return 0;
	}

	return attr;

}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetFileAttributesA
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetFileAttributesA
  (JNIEnv * env, jobject inst, jstring path, jint attr) {
	if (path == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "path is null");
		return;
	}

	LPCSTR pathString = (*env)->GetStringUTFChars(env, path, NULL);
	if (pathString == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}

	WINBOOL succ = SetFileAttributesA(pathString, (DWORD) attr);
	(*env)->ReleaseStringUTFChars(env, path, pathString);

	if (!succ) {
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
	}
}

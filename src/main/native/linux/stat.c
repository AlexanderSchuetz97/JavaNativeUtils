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
#include <assert.h>
#include <sys/statvfs.h>

jobject fillStat(JNIEnv * env, struct stat* theStat) {
	jobject myStat = jnew_Stat(env);
	if (myStat == NULL) {
		return NULL;
	}

	jset_Stat_dev(env, myStat, (jlong) theStat->st_dev);
	jset_Stat_ino(env, myStat, (jlong) theStat->st_ino);
	jset_Stat_mode(env, myStat, (jlong) theStat->st_mode);
	jset_Stat_nlink(env, myStat, (jlong) theStat->st_nlink);
	jset_Stat_uid(env, myStat, (jlong) theStat->st_uid);
	jset_Stat_gid(env, myStat, (jlong) theStat->st_gid);
	jset_Stat_rdev(env, myStat, (jlong) theStat->st_rdev);
	jset_Stat_size(env, myStat, (jlong) theStat->st_size);
	jset_Stat_blksize(env, myStat, (jlong) theStat->st_blksize);
	jset_Stat_blocks(env, myStat, (jlong) theStat->st_blocks);
	jset_Stat_atime(env, myStat, (jlong) theStat->st_atime);
	jset_Stat_mtime(env, myStat, (jlong) theStat->st_mtime);
	jset_Stat_ctime(env, myStat, (jlong) theStat->st_ctime);

	return myStat;
}

void handleError(JNIEnv * env, int err, const char* path) {

	switch(err) {
	case (EACCES):
		jthrowCC_AccessDeniedException_1(env, path, NULL, "Search permission is denied for one of the directories in the path prefix of path.");
		return;
	case (EBADF):
		jthrow_InvalidFileDescriptorException(env);
		return;
	case (ELOOP):
		jthrowCC_FileSystemLoopException(env, path);
		return;
	case (ENAMETOOLONG):
		jthrowCC_InvalidPathException(env, path, "path is too long.");
		return;
	case (ENOENT):
		jthrowCC_FileNotFoundException_1(env, path);
		return;
	case (ENOMEM):
		jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available.");
		return;
	case (ENOTDIR):
		jthrowCC_InvalidPathException(env, path, "A component of the path prefix of path is not a directory. ");
		return;
	case (EIO):
		jthrowC_IOException_1(env, "An I/O error occurred.");
		return;
	default:
		jthrow_UnknownNativeErrorException_1(env, err);
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
		jthrowCC_IllegalArgumentException_1(env, "path is null");
		return NULL;
	}

	struct stat theStat;
	memset(&theStat, 0, sizeof(struct stat));

	const char* thePath = (*env) ->GetStringUTFChars(env, path, NULL);
	if (thePath == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
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
		jthrow_InvalidFileDescriptorException(env);
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
		jthrowCC_IllegalArgumentException_1(env, "path is null");
		return NULL;
	}

	struct stat theStat;
	memset(&theStat, 0, sizeof(struct stat));

	const char* thePath = (*env) ->GetStringUTFChars(env, path, NULL);
	if (thePath == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
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

static_assert(sizeof(mode_t) <= sizeof(jint), "mode_t doesnt fit in jint");

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    chmod
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_chmod
  (JNIEnv * env, jobject inst, jstring path, jint mode) {
	if (path == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "path is null");
		return;
	}

	const char* thePath = (*env) ->GetStringUTFChars(env, path, NULL);
	if (thePath == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}

	int res = chmod(thePath, (mode_t) mode);

	if (res == 0) {
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	}

	int err = errno;

	switch(err) {
	case(EACCES):
		jthrowCC_AccessDeniedException_1(env, thePath, NULL, "Search permission is denied on a component of the path prefix.");
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(EIO):
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		jthrowC_IOException_1(env, "An I/O error occurred");
		return;
	case(ELOOP):
		jthrowCC_FileSystemLoopException(env, thePath);
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(ENAMETOOLONG):
		jthrowCC_InvalidPathException(env, thePath, "path is too long");
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(ENOENT):
		jthrowCC_FileNotFoundException_1(env, thePath);
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(ENOMEM):
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available");
		return;
	case(ENOTDIR):
		jthrowCC_NotDirectoryException(env, thePath);
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(EPERM):
		jthrowCC_PermissionDeniedException_1(env, thePath, "The process does not have permission to change the file mode or the file is marked immuatable.");
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(EROFS):
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		jthrow_ReadOnlyFileSystemException(env);
		return;
	default:
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		jthrow_UnknownNativeErrorException_1(env, err);
		return;
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fchmod
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_fchmod
  (JNIEnv * env, jobject inst, jint fd, jint mode) {

	if (fd < 0) {
		jthrow_InvalidFileDescriptorException(env);
		return;
	}

	if (fchmod((int)fd,(int) mode) == 0) {
		return;
	}

	int err = errno;

	switch(err) {
	case(EBADF):
		jthrow_InvalidFileDescriptorException(env);
		return;
	case(EACCES):
		jthrowCC_AccessDeniedException_1(env, "fd", NULL, "Search permission is denied on a component of the path prefix.");
		return;
	case(EIO):
		jthrowC_IOException_1(env, "An I/O error occurred");
		return;
	case(ENOMEM):
		jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available");
		return;
	case(EPERM):
		jthrowCC_PermissionDeniedException_1(env, "fd", "The process does not have permission to change the file mode or the file is marked immuatable.");
		return;
	case(EROFS):
		jthrow_ReadOnlyFileSystemException(env);
		return;
	default:
		jthrow_UnknownNativeErrorException_1(env, err);
		return;
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    chown
 * Signature: (Ljava/lang/String;II)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_chown
  (JNIEnv * env, jobject inst, jstring path, jint owner, jint group) {
	if (path == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "path is null");
		return;
	}

	const char* thePath = (*env) ->GetStringUTFChars(env, path, NULL);
	if (thePath == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}

	int res = chown(thePath, (uid_t) owner, (gid_t) group);

	if (res == 0) {
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	}

	int err = errno;

	switch(err) {
	case(EACCES):
		jthrowCC_AccessDeniedException_1(env, thePath, NULL, "Search permission is denied on a component of the path prefix.");
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(EIO):
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		jthrowC_IOException_1(env, "An I/O error occurred");
		return;
	case(ELOOP):
		jthrowCC_FileSystemLoopException(env, thePath);
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(ENAMETOOLONG):
		jthrowCC_InvalidPathException(env, thePath, "path is too long");
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(ENOENT):
		jthrowCC_FileNotFoundException_1(env, thePath);
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(ENOMEM):
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available");
		return;
	case(ENOTDIR):
		jthrowCC_NotDirectoryException(env, thePath);
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(EPERM):
		jthrowCC_PermissionDeniedException_1(env, thePath, "The process does not have permission to change the file owner or the file is marked immutable.");
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		return;
	case(EROFS):
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		jthrow_ReadOnlyFileSystemException(env);
		return;
	default:
		(*env)->ReleaseStringUTFChars(env, path, thePath);
		jthrow_UnknownNativeErrorException_1(env, err);
		return;
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fchown
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_fchown
  (JNIEnv * env, jobject inst, jint fd, jint owner, jint group) {
	if (fd < 0) {
		jthrow_InvalidFileDescriptorException(env);
		return;
	}

	if (fchown((int)fd, (uid_t) owner, (gid_t) group) == 0) {
		return;
	}

	int err = errno;

	switch(err) {
	case(EBADF):
		jthrow_InvalidFileDescriptorException(env);
		return;
	case(EACCES):
		jthrowCC_AccessDeniedException_1(env, "fd", NULL, "Search permission is denied on a component of the path prefix.");
		return;
	case(EIO):
		jthrowC_IOException_1(env, "An I/O error occurred");
		return;
	case(ENOMEM):
		jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available");
		return;
	case(EPERM):
		jthrowCC_PermissionDeniedException_1(env, "fd", "The process does not have permission to change the file owner or the file is marked immutable.");
		return;
	case(EROFS):
		jthrow_ReadOnlyFileSystemException(env);
		return;
	default:
		jthrow_UnknownNativeErrorException_1(env, err);
		return;
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    statvfs
 * Signature: (Ljava/lang/String;)Lio/github/alexanderschuetz97/nativeutils/api/structs/Statvfs;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_statvfs
  (JNIEnv * env, jobject inst, jstring path) {
	if (path == NULL) {
		jthrowCC_NullPointerException_1(env, "path");
		return NULL;
	}
	struct statvfs theStat;
	memset((void*) &theStat, 0, sizeof(struct statvfs));

	const char* chars = (*env)->GetStringUTFChars(env, path, NULL);
	if (chars == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return NULL;
	}

	jobject result = NULL;
	while(statvfs(chars, &theStat) != 0) {
		int err = errno;
		switch(err) {
			case(ENAMETOOLONG):
				jthrowCC_IllegalArgumentException_1(env, "Path parameter is too long");
				goto cleanup;
			case(ENOENT):
				jthrowCC_FileNotFoundException_1(env, chars);
				goto cleanup;
			case (EOVERFLOW):
				goto mapResult;
			case(EINTR):
				continue;
			case(EACCES):
				jthrowCC_AccessDeniedException_1(env, "fd", NULL, "Search permission is denied on a component of the path prefix.");
				goto cleanup;
			case(EIO):
				jthrowC_IOException_1(env, "An I/O error occurred while reading from the filesystem.");
				goto cleanup;
			case(ENOMEM):
				jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available");
				goto cleanup;
			case(EPERM):
				jthrowCC_PermissionDeniedException_1(env, "fd", "The process does not have permission to change the file owner or the file is marked immutable.");
				goto cleanup;
			case(ENOSYS):
				jthrowCC_IOException_1(env, "The filesystem does not support this call.");
				goto cleanup;
			case(ENOTDIR):
				jthrowCC_NotDirectoryException(env, "A component of the path was not a directory");
				goto cleanup;
			default:
				jthrow_UnknownNativeErrorException_1(env, err);
				goto cleanup;
		}
	}

	mapResult:
	result = jnew_Statvfs(env);
	if (result == NULL) {
		goto cleanup;
	}

	jset_Statvfs_f_bsize(env, result, theStat.f_bsize);
	jset_Statvfs_f_frsize(env, result, theStat.f_frsize);
	jset_Statvfs_f_blocks(env, result, theStat.f_blocks);
	jset_Statvfs_f_bfree(env, result, theStat.f_bfree);
	jset_Statvfs_f_bavail(env, result, theStat.f_bavail);
	jset_Statvfs_f_files(env, result, theStat.f_files);
	jset_Statvfs_f_ffree(env, result, theStat.f_ffree);
	jset_Statvfs_f_favail(env, result, theStat.f_favail);
	jset_Statvfs_f_fsid(env, result, theStat.f_fsid);
	jset_Statvfs_f_flag(env, result, theStat.f_flag);
	jset_Statvfs_f_namemax(env, result, theStat.f_namemax);

	goto cleanup;

	cleanup:
	(*env)->ReleaseStringUTFChars(env, path, chars);
	return result;


}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    mkfifo
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_mkfifo
  (JNIEnv * env, jobject inst, jstring path, jint mode) {
	if (path == NULL) {
		jthrowCC_NullPointerException_1(env, "path");
		return;
	}

	const char * ptr = (*env)->GetStringUTFChars(env, path, NULL);
	if (ptr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}


	if (mkfifo(ptr, (mode_t) mode) == 0) {
		(*env)->ReleaseStringUTFChars(env, path, ptr);
		return;
	}

	int err = errno;
	(*env)->ReleaseStringUTFChars(env, path, ptr);
	switch(err) {
	case(EACCES):
		jthrow_AccessDeniedException(env, path);
		return;
	case(EDQUOT):
		jthrowCC_QuotaExceededException(env, "The user's quota of disk blocks or inodes on the filesystem has been exhausted.");
		return;
	case(EEXIST):
		jthrow_FileAlreadyExistsException(env, path);
		return;
	case(ENAMETOOLONG):
		jthrowCC_IllegalArgumentException_1(env, "Path argument is too long");
		return;
	case(ENOENT):
		jthrowCC_FileNotFoundException_1(env, "A directory component in pathname does not exist or is a dangling symbolic link.");
		return;
	case(ENOSPC):
		jthrowCC_IOException_1(env, "The directory or filesystem has no room for a new file.");
		return;
	case(ENOTDIR):
		jthrowC_NotDirectoryException(env, "A component used as a directory in pathname is not, in fact, a directory.");
		return;
	case(EROFS):
		jthrow_ReadOnlyFileSystemException(env);
		return;
	default:
		jthrow_UnknownNativeErrorException_1(env, err);
		return;
	}
}


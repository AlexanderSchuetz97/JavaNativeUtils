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
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    link
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_link
	(JNIEnv * env, jobject inst, jstring target, jstring linkpath) {

	if (linkpath == NULL) {
		illegalArgs(env, "linkpath is null");
		return;
	}

	if (target == NULL) {
		illegalArgs(env, "target is null");
		return;
	}

	const char* linkPathString = (*env)->GetStringUTFChars( env, linkpath, NULL);
	if (linkPathString == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return;
	}

	const char* targetString = (*env)->GetStringUTFChars( env, target, NULL);
	if (targetString == NULL) {
		(*env)->ReleaseStringUTFChars( env, linkpath, linkPathString);
		throwOOM(env, "GetStringUTFChars");
		return;

	}

	int res = link(targetString, linkPathString);


	if (res == 0) {
		(*env)->ReleaseStringUTFChars( env, linkpath, linkPathString);
		(*env)->ReleaseStringUTFChars( env, target, targetString);
		return;
	}

	int err = errno;
	switch(err) {
		case (EACCES):
			throwFSAccessDenied(env, linkPathString, NULL, "Write access to the directory containing linkpath is denied, or one of the directories in the path prefix of linkpath did not allow search permission.");
			break;
		case (EDQUOT):
			throwQuotaExceededException(env, linkPathString, targetString, "The user's quota of resources on the filesystem has been exhausted. The resources could be inodes or disk blocks, depending on the filesystem implementation.");
			break;
		case (EEXIST):
			throwFileAlreadyExistsExc(env, linkPathString, NULL, "linkpath already exists.");
			break;
		//EFAULT shouldnt happen since both args point to the stack...
		case (EIO):
			throwIOExc(env, "An I/O error occurred.");
			break;
		case (ELOOP):
			throwFSLoop(env, linkPathString);
			break;
		case (ENAMETOOLONG):
			if (strlen(linkPathString) >= strlen(targetString)) {
				throwInvalidPath(env, linkPathString, "target or linkpath was too long.");
			} else {
				throwInvalidPath(env, targetString, "target or linkpath was too long.");
			}
			break;
		case (ENOENT):
			throwInvalidPath(env, linkPathString, "A directory component in linkpath does not exist or is a dangling symbolic link, or target or linkpath is an empty string.");
			break;
		case (ENOMEM):
			throwOOM(env, "Insufficient kernel memory was available.");
			break;
		case (ENOSPC):
			throwIOExc(env, "The device containing the file has no room for the new directory entry.");
			break;
		case (ENOTDIR):
			throwInvalidPath(env, linkPathString, "A component used as a directory in linkpath is not, in fact, a directory.");
			break;
		case (EPERM):
			throwUnsupportedExc(env, "The filesystem containing linkpath does not support the creation of symbolic links.");
			break;
		case (EROFS):
			throwFSReadOnly(env);
			break;
		default:
			unknownError(env, err);
			break;
	}

	(*env)->ReleaseStringUTFChars( env, linkpath, linkPathString);
	(*env)->ReleaseStringUTFChars( env, target, targetString);

	return;
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    symlink
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_symlink
  (JNIEnv * env, jobject inst, jstring target, jstring linkpath) {

	if (linkpath == NULL) {
		illegalArgs(env, "linkpath is null");
		return;
	}

	if (target == NULL) {
		illegalArgs(env, "target is null");
		return;
	}

	const char* linkPathString = (*env)->GetStringUTFChars( env, linkpath, NULL);
	if (linkPathString == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return;
	}

	const char* targetString = (*env)->GetStringUTFChars( env, target, NULL);
	if (targetString == NULL) {
		(*env)->ReleaseStringUTFChars( env, linkpath, linkPathString);
		throwOOM(env, "GetStringUTFChars");
		return;

	}

	int res = symlink(targetString, linkPathString);


	if (res == 0) {
		(*env)->ReleaseStringUTFChars( env, linkpath, linkPathString);
		(*env)->ReleaseStringUTFChars( env, target, targetString);
		return;
	}

	int err = errno;
	switch(err) {
		case (EACCES):
			throwFSAccessDenied(env, linkPathString, NULL, "Write access to the directory containing linkpath is denied, or one of the directories in the path prefix of linkpath did not allow search permission.");
			break;
		case (EDQUOT):
			throwQuotaExceededException(env, linkPathString, targetString, "The user's quota of resources on the filesystem has been exhausted. The resources could be inodes or disk blocks, depending on the filesystem implementation.");
			break;
		case (EEXIST):
			throwFileAlreadyExistsExc(env, linkPathString, NULL, "linkpath already exists.");
			break;
		//EFAULT shouldnt happen since both args point to the stack...
		case (EIO):
			throwIOExc(env, "An I/O error occurred.");
			break;
		case (ELOOP):
			throwFSLoop(env, linkPathString);
			break;
		case (ENAMETOOLONG):
			if (strlen(linkPathString) >= strlen(targetString)) {
				throwInvalidPath(env, linkPathString, "target or linkpath was too long.");
			} else {
				throwInvalidPath(env, targetString, "target or linkpath was too long.");
			}
			break;
		case (ENOENT):
			throwInvalidPath(env, linkPathString, "A directory component in linkpath does not exist or is a dangling symbolic link, or target or linkpath is an empty string.");
			break;
		case (ENOMEM):
			throwOOM(env, "Insufficient kernel memory was available.");
			break;
		case (ENOSPC):
			throwIOExc(env, "The device containing the file has no room for the new directory entry.");
			break;
		case (ENOTDIR):
			throwInvalidPath(env, linkPathString, "A component used as a directory in linkpath is not, in fact, a directory.");
			break;
		case (EPERM):
			throwUnsupportedExc(env, "The filesystem containing linkpath does not support the creation of symbolic links.");
			break;
		case (EROFS):
			throwFSReadOnly(env);
			break;
		default:
			unknownError(env, err);
			break;
	}

	(*env)->ReleaseStringUTFChars( env, linkpath, linkPathString);
	(*env)->ReleaseStringUTFChars( env, target, targetString);

	return;
}

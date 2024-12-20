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

#include "../common/jni/eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil.h"
#include "../common/common.h"
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    link
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_link
	(JNIEnv * env, jobject inst, jstring target, jstring linkpath) {

	if (linkpath == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "linkpath is null");
		return;
	}

	if (target == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "target is null");
		return;
	}

	const char* linkPathString = (*env)->GetStringUTFChars( env, linkpath, NULL);
	if (linkPathString == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}

	const char* targetString = (*env)->GetStringUTFChars( env, target, NULL);
	if (targetString == NULL) {
		(*env)->ReleaseStringUTFChars( env, linkpath, linkPathString);
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
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
			jthrowCC_AccessDeniedException_1(env, linkPathString, NULL, "Write access to the directory containing linkpath is denied, or one of the directories in the path prefix of linkpath did not allow search permission.");
			break;
		case (EDQUOT):
			jthrowCC_QuotaExceededException_1(env, linkPathString, targetString, "The user's quota of resources on the filesystem has been exhausted. The resources could be inodes or disk blocks, depending on the filesystem implementation.");
			break;
		case (EEXIST):
			jthrowCC_FileAlreadyExistsException_1(env, linkPathString, NULL, "linkpath already exists.");
			break;
		//EFAULT shouldnt happen since both args point to the stack...
		case (EIO):
			jthrowC_IOException_1(env, "An I/O error occurred.");
			break;
		case (ELOOP):
			jthrowCC_FileSystemLoopException(env, linkPathString);
			break;
		case (ENAMETOOLONG):
			if (strlen(linkPathString) >= strlen(targetString)) {
				jthrowCC_InvalidPathException(env, linkPathString, "target or linkpath was too long.");
			} else {
				jthrowCC_InvalidPathException(env, targetString, "target or linkpath was too long.");
			}
			break;
		case (ENOENT):
			jthrowCC_InvalidPathException(env, linkPathString, "A directory component in linkpath does not exist or is a dangling symbolic link, or target or linkpath is an empty string.");
			break;
		case (ENOMEM):
			jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available.");
			break;
		case (ENOSPC):
			jthrowC_IOException_1(env, "The device containing the file has no room for the new directory entry.");
			break;
		case (ENOTDIR):
			jthrowCC_InvalidPathException(env, linkPathString, "A component used as a directory in linkpath is not, in fact, a directory.");
			break;
		case (EPERM):
			jthrowCC_UnsupportedOperationException_1(env, "The filesystem containing linkpath does not support the creation of symbolic links.");
			break;
		case (EROFS):
			jthrow_ReadOnlyFileSystemException(env);
			break;
		default:
			jthrow_UnknownNativeErrorException_1(env, err);
			break;
	}

	(*env)->ReleaseStringUTFChars( env, linkpath, linkPathString);
	(*env)->ReleaseStringUTFChars( env, target, targetString);

	return;
}




/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    readlink
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_readlink
  (JNIEnv * env, jobject inst, jstring path) {

	if (path == NULL) {
		jthrowCC_NullPointerException_1(env, "path");
		return NULL;
	}

	const char* ptr = (*env)->GetStringUTFChars(env, path, NULL);
	if (ptr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return NULL;
	}

	if (ptr[0] == 0) {
		jthrowCC_InvalidPathException(env, ptr, "path is empty");
		(*env)->ReleaseStringUTFChars(env, path, ptr);
		return NULL;
	}

	size_t size = 512;
	while (true) {
		char * buf = (char *)malloc(size+1);
		if (buf == NULL) {
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			return NULL;
		}

		ssize_t actual = readlink(ptr, buf, size);
		if (actual < 0) {

			free((void*) buf);

			int err = errno;
			switch(err) {
				case(EACCES):
					jthrowCC_AccessDeniedException_1(env, ptr, NULL, NULL);
					(*env)->ReleaseStringUTFChars(env, path, ptr);
					return NULL;
				case(EINVAL):
					jthrowCC_NotLinkException_1(env, ptr, NULL, NULL);
					(*env)->ReleaseStringUTFChars(env, path, ptr);
					return NULL;
				case(EIO):
					(*env)->ReleaseStringUTFChars(env, path, ptr);
					jthrowC_IOException_1(env, "I/O error");
					return NULL;
				case(ELOOP):
					jthrowCC_FileSystemLoopException(env, ptr);
					(*env)->ReleaseStringUTFChars(env, path, ptr);
					return NULL;
				case(ENAMETOOLONG):
					jthrowCC_InvalidPathException(env, ptr, "The pathname, or a component of the pathname, is too long.");
					(*env)->ReleaseStringUTFChars(env, path, ptr);
					return NULL;
				case(ENOENT):
					jthrowCC_FileNotFoundException_1(env, ptr);
					(*env)->ReleaseStringUTFChars(env, path, ptr);
					return NULL;
				case(ENOTDIR):
					jthrowCC_NotDirectoryException(env, ptr);
					(*env)->ReleaseStringUTFChars(env, path, ptr);
					return NULL;
				case(ENOMEM):
					(*env)->ReleaseStringUTFChars(env, path, ptr);
					jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available.");
					return NULL;
				default:
					(*env)->ReleaseStringUTFChars(env, path, ptr);
					jthrow_UnknownNativeErrorException_1(env, err);
					return NULL;
			}
		}

		if (actual < size) {

			(*env)->ReleaseStringUTFChars(env, path, ptr);
			//readlink does not append 0 byte jvm needs it tho buf is always bigger than size by 1.
			buf[actual] = 0;
			jstring str = (*env)->NewStringUTF(env, (const char*) buf);
			free((void*) buf);
			if (str == NULL) {
				jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
			}
			return str;
		}

		free((void*) buf);
		size*=2;
		if (size > 0xffff) {
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			jthrowC_IOException_1(env, "symbolic link points to a path longer than 65565 bytes!");
			return NULL;
		}
	}

}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    realpath
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_realpath
(JNIEnv * env, jobject inst, jstring path) {
	if (path == NULL) {
		jthrowCC_NullPointerException_1(env, "path");
		return NULL;
	}

	const char* ptr = (*env)->GetStringUTFChars(env, path, NULL);
	if (ptr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return NULL;
	}

	if (ptr[0] == 0) {
		jthrowCC_InvalidPathException(env, ptr, "path is empty");
		(*env)->ReleaseStringUTFChars(env, path, ptr);
		return NULL;
	}

	const char * res = (const char *) realpath(ptr, NULL);

	if (res != NULL) {
		(*env)->ReleaseStringUTFChars(env, path, ptr);
		jstring new = (*env)->NewStringUTF(env, res);
		free((void*)res);
		if (new == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
		}
		return new;
	}

	int err = errno;
	switch(err) {
		case(EACCES):
			jthrowCC_AccessDeniedException_1(env, ptr, NULL, NULL);
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			return NULL;
		case(EINVAL):
			jthrowCC_NotLinkException_1(env, ptr, NULL, NULL);
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			return NULL;
		case(EIO):
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			jthrowC_IOException_1(env, "I/O error");
			return NULL;
		case(ELOOP):
			jthrowCC_FileSystemLoopException(env, ptr);
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			return NULL;
		case(ENAMETOOLONG):
			jthrowCC_InvalidPathException(env, ptr, "The pathname, or a component of the pathname, is too long.");
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			return NULL;
		case(ENOENT):
			jthrowCC_FileNotFoundException_1(env, ptr);
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			return NULL;
		case(ENOTDIR):
			jthrowCC_NotDirectoryException(env, ptr);
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			return NULL;
		case(ENOMEM):
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			jthrowCC_OutOfMemoryError_1(env, "Insufficient memory was available.");
			return NULL;
		default:
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			jthrow_UnknownNativeErrorException_1(env, err);
			return NULL;
	}
}

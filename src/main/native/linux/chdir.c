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
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    chdir
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_chdir
  (JNIEnv * env, jobject inst, jstring path) {
	if (path == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "path is null");
		return;
	}



	const char* chars = (*env)->GetStringUTFChars(env, path, NULL);
	if (chars == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}

	if (chdir(chars) == 0) {
		(*env)->ReleaseStringUTFChars(env, path, chars);
		return;
	}

	int err = errno;


	switch(err) {
	case(EACCES):
		jthrowCC_AccessDeniedException_1(env, chars, NULL, "chdir caused EACCES");
		break;
	case(EIO):
		jthrowC_IOException_1(env, "chdir caused EIO");
		break;
	case(ELOOP):
		jthrowCC_FileSystemLoopException(env, chars);
		break;
	case(ENAMETOOLONG):
		jthrowCC_InvalidPathException(env, chars, "path is too long");
		break;
	case(ENOENT):
		jthrowCC_FileNotFoundException_1(env, chars);
		break;
	case(ENOMEM):
		jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available.");
		break;
	case(ENOTDIR):
		jthrowCC_NotDirectoryException(env, chars);
		break;
	default:
		jthrow_UnknownNativeErrorException_1(env, err);
		break;
	}

	(*env)->ReleaseStringUTFChars(env, path, chars);
	return;
}

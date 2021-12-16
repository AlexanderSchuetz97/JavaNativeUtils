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
#include <unistd.h>


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    chdir
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_chdir
  (JNIEnv * env, jobject inst, jstring path) {
	if (path == NULL) {
		throwIllegalArgumentsExc(env, "path is null");
		return;
	}



	const char* chars = (*env)->GetStringUTFChars(env, path, NULL);
	if (chars == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return;
	}

	if (chdir(chars) == 0) {
		(*env)->ReleaseStringUTFChars(env, path, chars);
		return;
	}

	int err = errno;


	switch(err) {
	case(EACCES):
		throwFSAccessDenied(env, chars, NULL, "chdir caused EACCES");
		break;
	case(EIO):
		throwIOExc(env, "chdir caused EIO");
		break;
	case(ELOOP):
		throwFSLoop(env, chars);
		break;
	case(ENAMETOOLONG):
		throwInvalidPath(env, chars, "path is too long");
		break;
	case(ENOENT):
		throwFileNotFoundExc(env, chars);
		break;
	case(ENOMEM):
		throwOOM(env, "Insufficient kernel memory was available.");
		break;
	case(ENOTDIR):
		throwNotDirectoryException(env, chars);
		break;
	default:
		unknownError(env, err);
		break;
	}

	(*env)->ReleaseStringUTFChars(env, path, chars);
	return;
}

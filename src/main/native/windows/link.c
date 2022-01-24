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

#include "../common/jni/io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil.h"
#include "../common/common.h"

#include <windows.h>


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateSymbolicLinkA
 * Signature: (Ljava/lang/String;Ljava/lang/String;ZZ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateSymbolicLinkA
  (JNIEnv * env, jobject inst, jstring link, jstring target, jboolean isDir, jboolean isDev) {
	if (link == NULL) {
		throwIllegalArgumentsExc(env, "link is null");
		return;
	}

	if (target == NULL) {
		throwIllegalArgumentsExc(env, "target is null");
		return;
	}

	LPCSTR linkBuf = (*env)->GetStringUTFChars(env, link, NULL);
	if (linkBuf == NULL) {
		return;
	}
	LPCSTR targetBuf = (*env)->GetStringUTFChars(env, target, NULL);
	if (targetBuf == NULL) {
		(*env)->ReleaseStringUTFChars(env, link, linkBuf);
		return;
	}

	DWORD flags = 0;
	if (isDir) {
		flags |= 0x1;
	}

	if (isDev) {
		flags |= 0x2;
	}

	WINBOOL success = CreateSymbolicLinkA(linkBuf, targetBuf, flags);

	(*env)->ReleaseStringUTFChars(env, link, linkBuf);
	(*env)->ReleaseStringUTFChars(env, target, targetBuf);

	if (!success) {
		throwUnknownError(env, GetLastError());
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateHardLinkA
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateHardLinkA
  (JNIEnv * env, jobject inst, jstring link, jstring target) {
	if (link == NULL) {
		throwIllegalArgumentsExc(env, "link is null");
		return;
	}

	if (target == NULL) {
		throwIllegalArgumentsExc(env, "target is null");
		return;
	}

	LPCSTR linkBuf = (*env)->GetStringUTFChars(env, link, NULL);
	if (linkBuf == NULL) {
		return;
	}
	LPCSTR targetBuf = (*env)->GetStringUTFChars(env, target, NULL);
	if (targetBuf == NULL) {
		(*env)->ReleaseStringUTFChars(env, link, linkBuf);
		return;
	}

	WINBOOL success = CreateHardLinkA(linkBuf, targetBuf, NULL);

	(*env)->ReleaseStringUTFChars(env, link, linkBuf);
	(*env)->ReleaseStringUTFChars(env, target, targetBuf);

	if (!success) {
		throwUnknownError(env, GetLastError());
	}
}

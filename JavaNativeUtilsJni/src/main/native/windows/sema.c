//
// Copyright Alexander Schütz, 2023
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

#include <windows.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateSemaphoreExA
 * Signature: (JJJLjava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CreateSemaphoreExA
        (JNIEnv * env, jobject inst, jlong sec, jlong initialCount, jlong maximumCount, jstring name, jint dwDesiredAccess) {
    LPCSTR cname = NULL;
    if (name != NULL) {
        cname = (*env)->GetStringUTFChars(env, name, NULL);
        if (cname == NULL) {
            jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
            return 0;
        }
    }

    HANDLE h = CreateSemaphoreExA((LPSECURITY_ATTRIBUTES) (uintptr_t) sec, (LONG) initialCount, (LONG) maximumCount, cname, 0, (DWORD) dwDesiredAccess);
    if (h != NULL) {
        goto cleanup;
    }

    DWORD err = GetLastError();
    jthrow_UnknownNativeErrorException_1(env, err);

    cleanup:
    if (cname != NULL) {
        (*env)->ReleaseStringUTFChars(env, name, cname);
    }
    return (jlong) (uintptr_t) h;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ReleaseSemaphore
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ReleaseSemaphore
        (JNIEnv * env, jobject inst, jlong sema, jlong count) {
    HANDLE h = (HANDLE) (uintptr_t) sema;
    LONG prev = 0;
    if (ReleaseSemaphore(h, (LONG) count, &prev) == 0) {
        jthrow_UnknownNativeErrorException_1(env, GetLastError());
    }

    return (jlong) prev;
}

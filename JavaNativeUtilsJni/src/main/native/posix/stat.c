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

#include "../common/jni/eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil.h"
#include "statutil.h"

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    stat
 * Signature: (Ljava/lang/String;)Leu/aschuetz/nativeutils/api/structs/Stat;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_stat
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
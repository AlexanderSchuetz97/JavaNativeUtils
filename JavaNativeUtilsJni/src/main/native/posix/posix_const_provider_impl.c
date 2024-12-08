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

#include "posix_const_provider.h"
#include "../common/jni/eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil.h"
#include "../common/jnigenerator.h"

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    _getConst
 * Signature: (Leu/aschuetz/nativeutils/api/consts/DefaultPosixConstProvider;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil__1getConst
(JNIEnv * env, jclass clazz, jobject jconst) {
    jfetchconst_DefaultPosixConstProvider(env, jconst);
}
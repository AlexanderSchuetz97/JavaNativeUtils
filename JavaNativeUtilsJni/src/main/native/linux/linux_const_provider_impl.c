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
#include "linux_const_provider.h"
#include "../common/jni/eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil.h"
#include "../common/jnigenerator.h"
#include <fcntl.h>

JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil__1getConst
        (JNIEnv * env, jclass clazz, jobject jconst) {

    jfetchconst_DefaultLinuxConstProvider(env, jconst);

    //cant include fcntl.h and linux/fcntl.h in same file for some reason...
    jset_DefaultLinuxConstProvider_O_ASYNC(env, jconst, O_ASYNC);

    //GLIBC version too old to contain these macros
    jset_DefaultLinuxConstProvider_RTA_IP_PROTO(env, jconst, 27);
    jset_DefaultLinuxConstProvider_RTA_SPORT(env, jconst, 28);
    jset_DefaultLinuxConstProvider_RTA_DPORT(env, jconst, 29);
    jset_DefaultLinuxConstProvider_RTA_NH_ID(env, jconst, 30);

}
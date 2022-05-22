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
#include <net/if.h>
#include <errno.h>
#include <linux/if_addr.h>
#include <string.h>
/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    if_nametoindex
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_if_1nametoindex
  (JNIEnv * env, jobject inst, jstring name) {
	if (name == NULL) {
		throwNullPointerException(env, "name");
		return 0;
	}

	const char * cname = (*env)->GetStringUTFChars(env, name, NULL);
	if (cname == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return 0;
	}


	int idx = if_nametoindex(cname);

	(*env)->ReleaseStringUTFChars(env, name, cname);

	if (idx != 0) {
		return idx;
	}

	int err = errno;
	if (err == ENODEV) {
		return 0;
	}

	throwUnknownError(env, err);
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    if_indextoname
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_if_1indextoname
  (JNIEnv * env, jobject inst, jint idx) {
	if (idx == 0) {
		return NULL;
	}

	char buf[IFNAMSIZ+1];
	memset(buf, 0, IFNAMSIZ+1);


	if (if_indextoname(idx, buf) != NULL) {
		jstring str =  (*env)->NewStringUTF(env, (const char*) buf);
		if (str == NULL) {
			throwOOM(env, "NewStringUTF");
		}
		return str;
	}

	int err = errno;
	if (err == ENXIO) {
		return NULL;
	}

	throwUnknownError(env, idx);
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    if_nameindex
 * Signature: ()Ljava/util/Collection;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_if_1nameindex
  (JNIEnv * env, jobject inst) {
	struct if_nameindex* ptr = if_nameindex();
	if (ptr == NULL) {
		int err = errno;
		switch(err) {
		case(ENOBUFS):
			throwOOM(env, "");
			return NULL;
		default:
			throwUnknownError(env, err);
			return NULL;
		}
	}

	jobject list = new_array_list(env);
	if (list == NULL) {
		if_freenameindex(ptr);
		return NULL;
	}

	int i = 0;
	while(true) {
		if (ptr[i].if_index == 0 || ptr[i].if_name == NULL) {
			break;
		}

		jstring str = (*env)->NewStringUTF(env, ptr[i].if_name);
		if (str == NULL) {
			if_freenameindex(ptr);
			throwOOM(env, "NewStringUTF");
			return NULL;
		}

		jobject jval = (*env)->NewObject(env, IfNameIndex_Class, IfNameIndex_Constructor, ptr[i].if_index, str);
		if (jval == NULL) {
			if_freenameindex(ptr);
			return NULL;
		}

		if (!collection_add(env, list, jval)) {
			if_freenameindex(ptr);
			return NULL;
		}

		i++;
	}


	if_freenameindex(ptr);
	return list;
}

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


#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    geteuid
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_geteuid
  (JNIEnv * env, jobject inst) {
	return geteuid();
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getuid
 * Signature: ()L
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_getuid
  (JNIEnv * env, jobject inst) {
	return getuid();
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getlogin_r
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_getlogin_1r
  (JNIEnv * env, jobject inst) {

	char stackBuf[LOGIN_NAME_MAX];

	int res = getlogin_r(stackBuf, LOGIN_NAME_MAX);
	if (res == 0) {
		stackBuf[LOGIN_NAME_MAX-1] = 0;
		jstring result = (*env)->NewStringUTF(env, (const char*) stackBuf);
		if (result == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
			return NULL;
		}

		return result;
	} else if (res != ERANGE) {
		goto handleErrno;
	}

	size_t size = LOGIN_NAME_MAX*2;
	while(true) {
		char* heapBuf = (char*) malloc(size);

		if (heapBuf == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			return NULL;
		}

		res = getlogin_r(heapBuf, size);
		if (res == ERANGE) {
			free((void*)heapBuf);
			size*=2;
			continue;
		} else if (res != 0) {
			goto handleErrno;
		}

		heapBuf[size-1] = 0;
		jstring result = (*env)->NewStringUTF(env, (const char*) heapBuf);
		free((void*)heapBuf);
		if (result == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
			return NULL;
		}

		return result;
	}

	handleErrno:
	switch(res) {
	case(EMFILE):
		jthrowCC_IOException_1(env, "The per-process limit on the number of open file descriptors has been reached.");
		return NULL;
	case(ENFILE):
		jthrowCC_IOException_1(env, "The system-wide limit on the total number of open files has been reached.");
		return NULL;
	case(ENOENT):
		jthrowCC_FileNotFoundException_1(env, "There was no corresponding entry in the utmp-file.");
		return NULL;
	case(ENOTTY):
		jthrowCC_IllegalStateException_1(env, "Standard input didn't refer to a terminal.");
		return NULL;
	case(ENXIO):
		jthrowCC_IllegalStateException_1(env, "The calling process has no controlling terminal.");
		return NULL;
	case(ENOMEM):
		jthrowCC_OutOfMemoryError_1(env, "Insufficient memory to allocate passwd structure.");
		return NULL;
	}

	jthrow_UnknownNativeErrorException_1(env, res);
	return NULL;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getgrouplist
 * Signature: (Ljava/lang/String;I)[I
 */
JNIEXPORT jlongArray JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_getgrouplist
  (JNIEnv * env, jobject inst, jstring user, jlong group) {
	if (user == NULL) {
		jthrowCC_NullPointerException_1(env, "user");
		return NULL;
	}
	const char* cuser = (*env)->GetStringUTFChars(env, user, NULL);

	while(true) {
		int ngrp = 0;

		int res = getgrouplist(cuser, group, NULL, &ngrp);
		if (res != -1 || ngrp <= 0) {
			(*env)->ReleaseStringUTFChars(env, user, cuser);
			return (*env)->NewIntArray(env, 0);
		}

		gid_t* ptr = (gid_t*) malloc(ngrp*sizeof(gid_t));
		if (ptr == NULL) {
			(*env)->ReleaseStringUTFChars(env, user, cuser);
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			return NULL;
		}

		int l = ngrp;

		res = getgrouplist(cuser, group, ptr, &l);
		if (res != ngrp || l != ngrp) {
			free((void*)ptr);
			continue;
		}

		jlong* ptr2 = (jlong*) malloc(ngrp*sizeof(jlong));
		if (ptr2 == NULL) {
			free((void*)ptr);
			(*env)->ReleaseStringUTFChars(env, user, cuser);
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			return NULL;
		}

		for (int i = 0; i < ngrp; i++) {
			ptr2[i] = (jlong) ptr[i];
		}

		free((void*)ptr);

		jlongArray result = (*env)->NewLongArray(env, ngrp);
		if (result == NULL) {
			free((void*)ptr2);
			(*env)->ReleaseStringUTFChars(env, user, cuser);
			jthrowCC_OutOfMemoryError_1(env, "NewLongArray");
			return NULL;
		}

		(*env)->SetLongArrayRegion(env, result, 0, ngrp, (const jlong*) ptr2);
		free((void*)ptr2);

		return result;
	}

}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getgrgid
 * Signature: (I)Lio/github/alexanderschuetz97/nativeutils/api/structs/Group;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_getgrgid_1r
  (JNIEnv * env, jobject inst, jlong group) {
	int res = 0;
	int size = sysconf(_SC_GETGR_R_SIZE_MAX);
	if (size == -1) {
		size = 16384;
	}
	while(true) {
		char * buf = (char *) malloc(size);
		if (buf == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			return NULL;
		}

		struct group result_buf;
		memset((void*) &result_buf, 0, sizeof(struct group));
		struct group *result_buf_ptr = NULL;

		do {
			res = getgrgid_r((gid_t) group, &result_buf, buf, size, &result_buf_ptr);
		} while(res == EINTR);

		if (res == ERANGE) {
			free((void*)buf);
			size*=2;
			continue;
		}

		if (res != 0) {
			free((void*)buf);
			goto handleErrno;
		}

		jobject jgrp = jnew_Group(env);
		if (jgrp == NULL) {
			free((void*)buf);
			return NULL;
		}

		jsetC_Group_gr_name(env, jgrp, result_buf.gr_name);
		jsetC_Group_gr_passwd(env, jgrp, result_buf.gr_passwd);
		jset_Group_gr_gid(env, jgrp, result_buf.gr_gid);
		jobject members = jnew_ArrayList(env);
		if (members == NULL) {
			free((void*)buf);
			return NULL;
		}

		int i = 0;
		while(true) {
			if (result_buf.gr_mem[i] == NULL) {
				break;
			}

			jstring nstr = (*env)->NewStringUTF(env, result_buf.gr_mem[i]);
			if (nstr == NULL) {
				jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
				return NULL;
			}

			jcall_ArrayList_add_1(env, members, nstr);
			i++;
		}


		jset_Group_gr_mem(env, jgrp, members);
		free((void*)buf);
		return jgrp;
	}

	handleErrno:
	switch(res) {
	case(EIO):
		jthrowCC_IOException_1(env, "I/O error.");
		return NULL;
	case(EMFILE):
		jthrowCC_IOException_1(env, "The maximum number of files opened file limit is reached.");
		return NULL;
	case(ENFILE):
		jthrowCC_IOException_1(env, "The maximum number of files was open already in the system.");
		return NULL;
	case(ENOMEM):
		jthrowCC_OutOfMemoryError_1(env, "Insufficient memory to allocate group structure.");
		return NULL;
	}

	jthrow_UnknownNativeErrorException_1(env, res);
	return NULL;


}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getpwnam_r
 * Signature: (Ljava/lang/String;)Lio/github/alexanderschuetz97/nativeutils/api/structs/Passwd;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_getpwnam_1r
  (JNIEnv * env, jobject inst, jstring user) {
	if (user == NULL) {
		jthrowCC_NullPointerException_1(env, "user");
		return NULL;
	}

	int res = 0;
	int size = sysconf(_SC_GETGR_R_SIZE_MAX);
	if (size == -1) {
		size = 16384;
	}

	const char* cuser = (*env)->GetStringUTFChars(env, user, NULL);
	if (cuser == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return NULL;
	}


	while(true) {
		char * buf = (char *) malloc(size);
		if (buf == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			(*env)->ReleaseStringUTFChars(env, user, cuser);
			return NULL;
		}

		struct passwd result_buf;
		memset((void*) &result_buf, 0, sizeof(struct passwd));
		struct passwd *result_buf_ptr = NULL;

		do {
			res = getpwnam_r(cuser, &result_buf, buf, size, &result_buf_ptr);
		} while(res == EINTR);

		if (res == ERANGE) {
			free((void*)buf);
			size*=2;
			continue;
		}

		if (res != 0) {
			free((void*)buf);
			(*env)->ReleaseStringUTFChars(env, user, cuser);
			goto handleErrno;
		}

		jobject jpwd = jnew_Passwd(env);
		if (jpwd == NULL) {
			free((void*)buf);
			(*env)->ReleaseStringUTFChars(env, user, cuser);
			return NULL;
		}

		jsetCC_Passwd_pw_name(env, jpwd, result_buf.pw_name);
		jsetCC_Passwd_pw_dir(env, jpwd, result_buf.pw_dir);
		jsetCC_Passwd_pw_gecos(env, jpwd, result_buf.pw_gecos);
		jsetCC_Passwd_pw_passwd(env, jpwd, result_buf.pw_passwd);
		jsetCC_Passwd_pw_shell(env, jpwd, result_buf.pw_shell);
		jset_Passwd_pw_gid(env, jpwd, result_buf.pw_gid);
		jset_Passwd_pw_uid(env, jpwd, result_buf.pw_uid);


		(*env)->ReleaseStringUTFChars(env, user, cuser);
		free((void*)buf);
		return jpwd;
	}

	handleErrno:
	switch(res) {
	case(EIO):
		jthrowCC_IOException_1(env, "I/O error.");
		return NULL;
	case(EMFILE):
		jthrowCC_IOException_1(env, "The maximum number of files opened file limit is reached.");
		return NULL;
	case(ENFILE):
		jthrowCC_IOException_1(env, "The maximum number of files was open already in the system.");
		return NULL;
	case(ENOMEM):
		jthrowCC_OutOfMemoryError_1(env, "Insufficient memory to allocate group structure.");
		return NULL;
	}

	jthrow_UnknownNativeErrorException_1(env, res);
	return NULL;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getpwuid_r
 * Signature: (I)Lio/github/alexanderschuetz97/nativeutils/api/structs/Passwd;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_getpwuid_1r
  (JNIEnv * env, jobject inst, jlong uid) {
	int res = 0;
	int size = sysconf(_SC_GETGR_R_SIZE_MAX);
	if (size == -1) {
		size = 16384;
	}
	while(true) {
		char * buf = (char *) malloc(size);
		if (buf == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			return NULL;
		}

		struct passwd result_buf;
		memset((void*) &result_buf, 0, sizeof(struct passwd));
		struct passwd *result_buf_ptr = NULL;

		do {
			res = getpwuid_r((uid_t) uid, &result_buf, buf, size, &result_buf_ptr);
		} while(res == EINTR);

		if (res == ERANGE) {
			free((void*)buf);
			size*=2;
			continue;
		}

		if (res != 0) {
			free((void*)buf);
			goto handleErrno;
		}

		jobject jpwd = jnew_Passwd(env);
		if (jpwd == NULL) {
			free((void*)buf);
			return NULL;
		}

		jsetCC_Passwd_pw_name(env, jpwd, result_buf.pw_name);
		jsetCC_Passwd_pw_dir(env, jpwd, result_buf.pw_dir);
		jsetCC_Passwd_pw_gecos(env, jpwd, result_buf.pw_gecos);
		jsetCC_Passwd_pw_passwd(env, jpwd, result_buf.pw_passwd);
		jsetCC_Passwd_pw_shell(env, jpwd, result_buf.pw_shell);
		jset_Passwd_pw_gid(env, jpwd, result_buf.pw_gid);
		jset_Passwd_pw_uid(env, jpwd, result_buf.pw_uid);

		free((void*)buf);
		return jpwd;
	}

	handleErrno:
	switch(res) {
	case(EIO):
		jthrowCC_IOException_1(env, "I/O error.");
		return NULL;
	case(EMFILE):
		jthrowCC_IOException_1(env, "The maximum number of files opened file limit is reached.");
		return NULL;
	case(ENFILE):
		jthrowCC_IOException_1(env, "The maximum number of files was open already in the system.");
		return NULL;
	case(ENOMEM):
		jthrowCC_OutOfMemoryError_1(env, "Insufficient memory to allocate group structure.");
		return NULL;
	}

	jthrow_UnknownNativeErrorException_1(env, res);
	return NULL;
}

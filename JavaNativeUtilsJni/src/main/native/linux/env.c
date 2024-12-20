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
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <wordexp.h>
#include <sys/utsname.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    wordexp
 * Signature: (Ljava/lang/String;ZZZ)Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_wordexp
  (JNIEnv * env, jobject inst, jstring expression, jboolean allowCommands, jboolean useStdErr, jboolean allowUndef) {
	if (expression == NULL) {
		jthrowCC_NullPointerException_1(env, "expression");
		return NULL;
	}



	int flag = 0;
	if (!allowCommands) {
		flag |= WRDE_NOCMD;
	}

	if (useStdErr) {
		flag |= WRDE_SHOWERR;
	}

	if (!allowUndef) {
		flag |= WRDE_UNDEF;
	}

	const char* ptr = (*env)->GetStringUTFChars(env, expression, NULL);

	wordexp_t vec;
	memset(&vec, 0, sizeof(wordexp_t));

	int res = wordexp(ptr, &vec, flag);
	(*env)->ReleaseStringUTFChars(env, expression, ptr);
	switch(res) {
	case(0): {
		jobjectArray joa = (*env)->NewObjectArray(env, vec.we_wordc, (*env)->GetObjectClass(env, expression), NULL);
		if (joa == NULL) {
			wordfree(&vec);
			jthrowCC_OutOfMemoryError_1(env, "NewObjectArray");
			return NULL;
		}

		for (size_t i = 0; i < vec.we_wordc; i++) {
			jstring str = (*env)->NewStringUTF(env, vec.we_wordv[i]);
			if (str == NULL) {
				(*env)->DeleteLocalRef(env, joa);
				wordfree(&vec);
				jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
				return NULL;
			}
			(*env)->SetObjectArrayElement(env, joa, i, str);
			(*env)->DeleteLocalRef(env, str);
		}

		wordfree(&vec);
		return joa;
	}
	case(WRDE_BADCHAR): {
		jthrowCC_IllegalArgumentException_1(env, "Illegal occurrence of newline or one of |, &, ;, <, >, (, ), {, }.");
		return NULL;
	}
	case(WRDE_BADVAL): {
		jthrowCC_IllegalArgumentException_1(env, "An undefined shell variable was referenced");
		return NULL;
	}
	case(WRDE_CMDSUB): {
		jthrowCC_IllegalArgumentException_1(env, "Command substitution occurred");
		return NULL;
	}
	case(WRDE_NOSPACE): {
		jthrowCC_OutOfMemoryError_1(env, "wordexp");
		return NULL;
	}
	case(WRDE_SYNTAX): {
		jthrowCC_IllegalArgumentException_1(env, "Shell syntax error, such as unbalanced parentheses or unmatched quotes.");
		return NULL;
	}
	default:
		jthrowCC_IllegalArgumentException_1(env, "unknown native error return value for wordexp syscall");
		return NULL;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    setenv
 * Signature: (Ljava/lang/String;Ljava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_setenv
  (JNIEnv *env, jobject inst, jstring key, jstring value, jboolean overwrite) {

	if (key == NULL) {
		jthrowCC_NullPointerException_1(env, "key");
		return;
	}

	if (value == NULL) {
		jthrowCC_NullPointerException_1(env, "value");
		return;
	}

	const char* keyP = (*env)->GetStringUTFChars(env, key, NULL);
	if (keyP == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}

	const char* valueP = (*env)->GetStringUTFChars(env, value, NULL);
	if (valueP == NULL) {
		(*env)->ReleaseStringUTFChars(env, key, keyP);
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}


	int res = setenv(keyP, valueP, overwrite ? 0 : 1);
	(*env)->ReleaseStringUTFChars(env, key, keyP);
	(*env)->ReleaseStringUTFChars(env, value, valueP);

	if (res == 0) {
		return;
	}

	int err = errno;
	switch(err) {
		case(EINVAL): {
			jthrowCC_IllegalArgumentException_1(env, "key contains = or is empty string");
			return;
		}
		case(ENOMEM): {
			jthrowCC_OutOfMemoryError_1(env, "Insufficient memory to add a new variable to the environment.");
			return;
		}
		default: {
			jthrow_UnknownNativeErrorException_1(env, err);
			return;
		}
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getenv
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_getenv
  (JNIEnv *env, jobject inst, jstring key) {
	if (key == NULL) {
		jthrowCC_NullPointerException_1(env, "key");
		return NULL;
	}

	const char* keyP = (*env)->GetStringUTFChars(env, key, NULL);
	if (keyP == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return NULL;
	}

	//This call may or may not be thread safe no one knows, depends on glibc version used.
	//So i guess we can only pray that no one calls setenv/putenv/unsetenv until we copy the string.
	//a mutex would also be pointless as any jni lib can just call this shit.
	char* res = getenv(keyP);


	if (res != NULL) {
		const char * copy = (const char*) strdup(res);
		(*env)->ReleaseStringUTFChars(env, key, keyP);
		if (copy == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "strdup");
			return NULL;
		}


		jstring nstr = (*env)->NewStringUTF(env, copy);
		free((void*)copy);
		return nstr;
	}

	(*env)->ReleaseStringUTFChars(env, key, keyP);
	return NULL;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    unsetenv
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_unsetenv
  (JNIEnv *env, jobject inst, jstring key) {
	if (key == NULL) {
		jthrowCC_NullPointerException_1(env, "key");
		return;
	}

	const char* keyP = (*env)->GetStringUTFChars(env, key, NULL);
	if (keyP == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}

	int res = unsetenv(keyP);

	(*env)->ReleaseStringUTFChars(env, key, keyP);

	if (res == 0) {
		return;
	}

	int err = errno;

	switch(err) {
		case(EINVAL): {
			jthrowCC_IllegalArgumentException_1(env, "key contains = or is empty string");
			return;
		}
		default: {
			jthrow_UnknownNativeErrorException_1(env, err);
			return;
		}
	}
}

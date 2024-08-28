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
#include "../common/timeutil.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_open
 * Signature: (Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1open__Ljava_lang_String_2I
  (JNIEnv * env, jobject inst, jstring name, jint oflags) {
	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return 0;
	}
	const char* cname = (*env)->GetStringUTFChars(env, name, NULL);
	if (cname == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return 0;
	}

	sem_t * sem = sem_open(cname, (int)oflags);
	(*env)->ReleaseStringUTFChars(env, name, cname);
	if (sem != SEM_FAILED) {
		return (jlong) (uintptr_t) sem;
	}

	int err = errno;
	switch(err) {
	case(EACCES):
			jthrow_AccessDeniedException(env, name);
			return 0;
	case(EEXIST):
			jthrow_FileAlreadyExistsException(env, name);
			return 0;
	case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "Name is invalid");
			return 0;
	case(ENAMETOOLONG):
			jthrowCC_IllegalArgumentException_1(env, "Name is too long");
			return 0;
	case(EMFILE):
			jthrowCC_QuotaExceededException(env, "The per-process limit on the number of open file descriptors has been reached.");
			return 0;
	case(ENFILE):
			jthrowCC_QuotaExceededException(env, "The system-wide limit on the total number of open files has been reached.");
			return 0;
	case(ENOENT):
			jthrow_FileNotFoundException_1(env, name);
			return 0;
	case(ENOMEM):
			jthrowCC_OutOfMemoryError_1(env, "sem_open Insufficient memory.");
			return 0;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
	return 0;


}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_open
 * Signature: (Ljava/lang/String;III)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1open__Ljava_lang_String_2III
  (JNIEnv * env, jobject inst, jstring name, jint oflags, jint mode, jint value) {
	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return 0;
	}
	const char* cname = (*env)->GetStringUTFChars(env, name, NULL);
	if (cname == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return 0;
	}

	sem_t * sem = sem_open(cname, (int)oflags, (mode_t) mode, (unsigned int) value);
	(*env)->ReleaseStringUTFChars(env, name, cname);
	if (sem != SEM_FAILED) {
		return (jlong) (uintptr_t) sem;
	}

	int err = errno;
	switch(err) {
	case(EACCES):
			jthrow_AccessDeniedException(env, name);
			return 0;
	case(EEXIST):
			jthrow_FileAlreadyExistsException(env, name);
			return 0;
	case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "Name or value is invalid");
			return 0;
	case(ENAMETOOLONG):
			jthrowCC_IllegalArgumentException_1(env, "Name is too long");
			return 0;
	case(EMFILE):
			jthrowCC_QuotaExceededException(env, "The per-process limit on the number of open file descriptors has been reached.");
			return 0;
	case(ENFILE):
			jthrowCC_QuotaExceededException(env, "The system-wide limit on the total number of open files has been reached.");
			return 0;
	case(ENOENT):
			jthrow_FileNotFoundException_1(env, name);
			return 0;
	case(ENOMEM):
			jthrowCC_OutOfMemoryError_1(env, "sem_open Insufficient memory.");
			return 0;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
	return 0;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1close
  (JNIEnv * env, jobject inst, jlong sem) {
	sem_t * semPtr = (sem_t *) (uintptr_t) (sem);
	if (semPtr == SEM_FAILED) {
		jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore.");
		return;
	}

	if (sem_close(semPtr) == 0) {
		return;
	}

	int err = errno;
	if (err == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore.");
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_unlink
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1unlink
  (JNIEnv * env, jobject inst, jstring name) {
	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return;
	}
	const char* cname = (*env)->GetStringUTFChars(env, name, NULL);
	if (cname == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}

	int ret = sem_unlink(cname);
	(*env)->ReleaseStringUTFChars(env, name, cname);
	if (ret == 0) {
		return;
	}


	int err = errno;
	switch(err) {
	case(EACCES):
			jthrow_AccessDeniedException(env, name);
			return;
	case(ENAMETOOLONG):
			jthrowCC_IllegalArgumentException_1(env, "name is too long.");
			return;
	case(ENOENT):
			jthrow_FileNotFoundException_1(env, name);
			return;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_init
 * Signature: (JZI)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1init
  (JNIEnv * env, jobject inst, jlong ptr, jboolean ipc, jint value) {
	sem_t * semPtr = (sem_t *) (uintptr_t) (ptr);
	if (semPtr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	if (sem_init(semPtr, ipc ? 1 : 0, value) == 0) {
		return;
	}

	int err = errno;
	if (err == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "value exceeds SEM_VALUE_MAX");
		return;
	}

	if (err == ENOSYS) {
		jthrowCC_UnsupportedOperationException_1(env, "the system does not support process-shared semaphores");
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_t_size
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1t_1size
  (JNIEnv * env, jobject inst) {
	return sizeof(sem_t);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1destroy
  (JNIEnv *  env, jobject inst, jlong sem) {
	sem_t * semPtr = (sem_t *) (uintptr_t) (sem);
	if (semPtr == NULL) {
		return;
	}

	if (sem_destroy(semPtr) == 0) {
		return;
	}

	int err = errno;
	if (err == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore.");
		return;
	}


	jthrow_UnknownNativeErrorException_1(env, errno);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_post
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1post
  (JNIEnv * env, jobject inst, jlong sem) {
	sem_t * semPtr = (sem_t *) (uintptr_t) (sem);
	if (semPtr == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore.");
		return;
	}

	if (sem_post(semPtr) == 0) {
		return;
	}


	jthrow_UnknownNativeErrorException_1(env, errno);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_wait
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1wait
  (JNIEnv * env, jobject inst, jlong sem) {
	sem_t * semPtr = (sem_t *) (uintptr_t) (sem);
	if (semPtr == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore.");
		return;
	}

	while(true) {
		if (sem_wait(semPtr) == 0) {
			return;
		}

		int err = errno;
		switch(err) {
		case(EINTR):
				continue;
		case(EINVAL):
				jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore.");
				return;
		}

		jthrow_UnknownNativeErrorException_1(env, errno);
		return;
	}
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_getvalue
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1getvalue
  (JNIEnv * env, jobject inst, jlong sem) {
	sem_t * semPtr = (sem_t *) (uintptr_t) (sem);
	if (semPtr == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore.");
		return 0;
	}

	int sval = 0;
	if (sem_getvalue(semPtr, &sval) == 0) {
		return sval;
	}


	int err = errno;
	if (err == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore.");
		return 0;
	}


	jthrow_UnknownNativeErrorException_1(env, errno);
	return 0;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_trywait
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1trywait
  (JNIEnv * env, jobject inst, jlong sem) {
	sem_t * semPtr = (sem_t *) (uintptr_t) (sem);
	if (semPtr == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore.");
		return false;
	}

	while(true) {
		if (sem_trywait(semPtr) == 0) {
			return true;
		}

		int err = errno;
		switch(err) {
		case(EAGAIN):
				return false;
		case(EINTR):
				continue;
		case(EINVAL):
				jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore.");
				return false;
		}

		jthrow_UnknownNativeErrorException_1(env, errno);
		return false;
	}
}

#define NANOSECONDS_PER_MILISECOND 1000000

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sem_timedwait
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sem_1timedwait
  (JNIEnv * env, jobject inst, jlong sem, jlong timeout) {
	if (timeout <= 0) {
		timeout = 0;
	}


	sem_t * semPtr = (sem_t *) (uintptr_t) (sem);
	if (semPtr == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore.");
		return false;
	}

	struct timespec tspec;
	uint64_t until = currentTimeMillis() + timeout;
	while(true) {

		uint64_t untilWithoutSeconds = until % 1000;

		tspec.tv_sec = (until - (untilWithoutSeconds)) / 1000;
		tspec.tv_nsec = untilWithoutSeconds * NANOSECONDS_PER_MILISECOND;

		if (sem_timedwait(semPtr, &tspec) == 0) {
			return true;
		}

		int err = errno;
		switch(err) {
		case(ETIMEDOUT):
				return false;
		case(EINTR):
				continue;
		case(EINVAL):
				jthrowCC_IllegalArgumentException_1(env, "sem is not a valid semaphore or timeout to big");
				return false;
		}

		jthrow_UnknownNativeErrorException_1(env, errno);
		return false;
	}
}

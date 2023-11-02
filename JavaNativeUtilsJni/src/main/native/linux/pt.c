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
#include "../common/jni/eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil.h"
#include "../common/common.h"

#include <errno.h>
#include <pthread.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sizeof_pthread_mutex_t
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sizeof_1pthread_1mutex_1t
  (JNIEnv * env, jobject inst) {
	return sizeof(pthread_mutex_t);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sizeof_pthread_mutexattr_t
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sizeof_1pthread_1mutexattr_1t
  (JNIEnv * env, jobject inst) {
	return sizeof(pthread_mutexattr_t);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sizeof_pthread_cond_t
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sizeof_1pthread_1cond_1t
  (JNIEnv * env, jobject inst) {
	return sizeof(pthread_cond_t);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sizeof_pthread_condattr_t
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sizeof_1pthread_1condattr_1t
  (JNIEnv * env, jobject inst) {
	return sizeof(pthread_condattr_t);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_condattr_destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1condattr_1destroy
  (JNIEnv * env, jobject inst, jlong attributes) {
	int ret = pthread_condattr_destroy((pthread_condattr_t*)(uintptr_t) attributes);
	if (ret == 0) {
		return;
	}
	if (ret == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "The value specified by attr is invalid.");
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, ret);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_condattr_init
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1condattr_1init
  (JNIEnv * env, jobject inst, jlong attributes) {
	int ret = pthread_condattr_init((pthread_condattr_t*)(uintptr_t) attributes);
	if (ret == 0) {
		return;
	}
	if (ret == ENOMEM) {
		jthrowCC_OutOfMemoryError_1(env, "Insufficient memory exists to initialize the condition variable attributes object.");
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, ret);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutexattr_destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutexattr_1destroy
(JNIEnv * env, jobject inst, jlong attributes) {
	int ret = pthread_mutexattr_destroy((pthread_mutexattr_t*)(uintptr_t) attributes);
	if (ret == 0) {
		return;
	}
	if (ret == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "The value specified by attr is invalid.");
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, ret);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutexattr_init
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutexattr_1init
(JNIEnv * env, jobject inst, jlong attributes) {
	int ret = pthread_mutexattr_init((pthread_mutexattr_t*)(uintptr_t) attributes);
	if (ret == 0) {
		return;
	}
	if (ret == ENOMEM) {
		jthrowCC_OutOfMemoryError_1(env, "Insufficient memory exists to initialize the mutex variable attributes object.");
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, ret);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_condattr_getpshared
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1condattr_1getpshared
  (JNIEnv * env, jobject inst, jlong attributes) {
	int result = 0;
	int ret = pthread_condattr_getpshared((pthread_condattr_t*)(uintptr_t) attributes, &result);
	if (ret == 0) {
		return (jint) result;
	}

	if (ret == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "The value specified by attr is invalid.");
		return 0;
	}

	jthrow_UnknownNativeErrorException_1(env, ret);
	return 0;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_condattr_setpshared
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1condattr_1setpshared
  (JNIEnv * env, jobject inst, jlong attributes, jint value) {
	int ret = pthread_condattr_setpshared((pthread_condattr_t*)(uintptr_t) attributes, (int) value);
	if (ret == 0) {
		return;
	}

	if (ret == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "The value specified by attr or value is invalid.");
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, ret);
	return;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutexattr_setpshared
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutexattr_1setpshared
  (JNIEnv * env, jobject inst, jlong attributes, jint value) {
	int ret = pthread_mutexattr_setpshared((pthread_mutexattr_t*)(uintptr_t) attributes, (int) value);
	if (ret == 0) {
		return;
	}

	if (ret == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "The value specified by attr or value is invalid.");
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, ret);
	return;
}
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutexattr_getpshared
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutexattr_1getpshared
  (JNIEnv * env, jobject inst, jlong attributes) {
	int result = 0;
	int ret = pthread_mutexattr_getpshared((pthread_mutexattr_t*)(uintptr_t) attributes, &result);
	if (ret == 0) {
		return (jint) result;
	}

	if (ret == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "The value specified by attr is invalid.");
		return 0;
	}

	jthrow_UnknownNativeErrorException_1(env, ret);
	return 0;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutexattr_settype
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutexattr_1settype
  (JNIEnv * env, jobject inst, jlong attributes, jint value) {
	int ret = pthread_mutexattr_settype((pthread_mutexattr_t*)(uintptr_t) attributes, (int) value);
	if (ret == 0) {
		return;
	}

	if (ret == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "The value specified by attr or value is invalid.");
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, ret);
	return;
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutexattr_gettype
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutexattr_1gettype
  (JNIEnv * env, jobject inst, jlong attributes) {
	int result = 0;
	int ret = pthread_mutexattr_gettype((pthread_mutexattr_t*)(uintptr_t) attributes, &result);
	if (ret == 0) {
		return (jint) result;
	}

	if (ret == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "The value specified by attr is invalid.");
		return 0;
	}

	jthrow_UnknownNativeErrorException_1(env, ret);
	return 0;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutex_init
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutex_1init
  (JNIEnv * env, jobject inst, jlong mutex, jlong attributes) {
	int ret = pthread_mutex_init((pthread_mutex_t*)(uintptr_t) mutex, (const pthread_mutexattr_t *)(uintptr_t) attributes);
	switch(ret) {
		case(0):
			return;
		case(EAGAIN):
			jthrowCC_QuotaExceededException(env, "The system lacked the necessary resources (other than memory) to initialize another mutex.");
			return;
		case(ENOMEM):
			jthrowCC_OutOfMemoryError_1(env, "Insufficient memory exists to initialize the mutex.");
			return;
		case(EPERM):
			jthrowCC_PermissionDeniedException(env, "The caller does not have the privilege to perform the operation.");
			return;
		case(EBUSY):
			jthrowCC_IllegalStateException_1(env, "The implementation has detected an attempt to reinitialize the object referenced by mutex, a previously initialized, but not yet destroyed, mutex.");
			return;
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "The value specified by attr is invalid.");
			return;
		default:
			jthrow_UnknownNativeErrorException_1(env, ret);
			return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutex_destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutex_1destroy
  (JNIEnv * env, jobject inst, jlong mutex) {
	int ret = pthread_mutex_destroy((pthread_mutex_t*)(uintptr_t) mutex);
	switch(ret) {
	case(0):
		return;
	case(EBUSY):
		jthrowCC_IllegalStateException_1(env, "The implementation has detected an attempt to destroy the object referenced by mutex while it is locked or referenced ");
		return;
	case(EINVAL):
		jthrowCC_IllegalArgumentException_1(env, "The value specified by mutex is invalid.");
		return;
	default:
		jthrow_UnknownNativeErrorException_1(env, ret);
		return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutex_lock
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutex_1lock
  (JNIEnv * env, jobject inst, jlong mutex) {
	int ret = pthread_mutex_lock((pthread_mutex_t*)(uintptr_t) mutex);
	switch(ret) {
	case(0):
		return;
	case(EAGAIN):
		jthrowCC_IllegalStateException_1(env, "The mutex could not be acquired because the maximum number of recursive locks for mutex has been exceeded.");
		return;
	case(EINVAL):
		jthrowCC_IllegalArgumentException_1(env, "The value specified by mutex does not refer to an initialized mutex object.");
		return;
	case(EDEADLK):
		jthrowCC_IllegalMonitorStateException_1(env, "The current thread already owns the mutex.");
		return;
    case(EOWNERDEAD):
        jthrow_InconsistentMutexException(env);
        return;
    case(ENOTRECOVERABLE):
        jthrow_UnrecoverableMutexException(env);
        return;
	default:
		jthrow_UnknownNativeErrorException_1(env, ret);
		return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutex_trylock
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutex_1trylock
  (JNIEnv * env, jobject inst, jlong mutex) {
	int ret = pthread_mutex_trylock((pthread_mutex_t*)(uintptr_t) mutex);
	switch(ret) {
	case(0):
		return true;
	case(EBUSY):
		return false;
	case(EAGAIN):
		jthrowCC_IllegalStateException_1(env, "The mutex could not be acquired because the maximum number of recursive locks for mutex has been exceeded.");
		return false;
	case(EINVAL):
		jthrowCC_IllegalArgumentException_1(env, "The value specified by mutex does not refer to an initialized mutex object.");
		return false;
	case(EDEADLK):
		jthrowCC_IllegalMonitorStateException_1(env, "The current thread already owns the mutex.");
		return false;
    case(EOWNERDEAD):
        jthrow_InconsistentMutexException(env);
        return false;
    case(ENOTRECOVERABLE):
        jthrow_UnrecoverableMutexException(env);
        return false;
	default:
		jthrow_UnknownNativeErrorException_1(env, ret);
		return false;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutex_unlock
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutex_1unlock
  (JNIEnv * env, jobject inst, jlong mutex) {
	int ret = pthread_mutex_unlock((pthread_mutex_t*)(uintptr_t) mutex);
	switch(ret) {
		case(0):
			return;
		case(EBUSY):
			return;
		case(EAGAIN):
			jthrowCC_IllegalStateException_1(env, "The mutex could not be acquired because the maximum number of recursive locks for mutex has been exceeded.");
			return;
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "The value specified by mutex does not refer to an initialized mutex object.");
			return;
		case(EPERM):
			jthrowCC_IllegalMonitorStateException_1(env, "The current thread does not hold the mutex");
			return;
		default:
			jthrow_UnknownNativeErrorException_1(env, ret);
			return;
	}
}

#define NANOSECONDS_PER_MILISECOND 1000000

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutex_timedlock
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutex_1timedlock
  (JNIEnv * env, jobject inst, jlong mutex, jlong timeout) {

	struct timespec tspec;
	uint64_t timeoutWithoutSeconds = timeout % 1000;

	tspec.tv_sec = (timeout - (timeoutWithoutSeconds)) / 1000;
	tspec.tv_nsec = timeoutWithoutSeconds * NANOSECONDS_PER_MILISECOND;

	int ret = pthread_mutex_timedlock((pthread_mutex_t*)(uintptr_t) mutex, &tspec);
	switch(ret) {
		case(0):
			return true;
		case(ETIMEDOUT):
			return false;
		case(EAGAIN):
			jthrowCC_IllegalStateException_1(env, "The mutex could not be acquired because the maximum number of recursive locks for mutex has been exceeded.");
			return false;
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "Mutex invalid or timeout too small");
			return false;
		case(EPERM):
			jthrowCC_IllegalMonitorStateException_1(env, "The current thread does not hold the mutex");
			return false;
		case(EDEADLK):
			jthrowCC_IllegalMonitorStateException_1(env, "The current already holds the mutex");
			return false;
        case(EOWNERDEAD):
            jthrow_InconsistentMutexException(env);
            return false;
        case(ENOTRECOVERABLE):
            jthrow_UnrecoverableMutexException(env);
            return false;
		default:
			jthrow_UnknownNativeErrorException_1(env, ret);
			return false;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_cond_broadcast
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1cond_1broadcast
   (JNIEnv * env, jobject inst, jlong condition) {

	int ret = pthread_cond_broadcast((pthread_cond_t*)(uintptr_t) condition);
	switch(ret) {
		case(0):
			return;
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "The value cond does not refer to an initialized condition variable.");
			return;
		default:
			jthrow_UnknownNativeErrorException_1(env, ret);
			return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_cond_signal
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1cond_1signal
  (JNIEnv * env, jobject inst, jlong condition) {

	int ret = pthread_cond_signal((pthread_cond_t*)(uintptr_t) condition);
	switch(ret) {
		case(0):
			return;
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "The value cond does not refer to an initialized condition variable.");
			return;
		default:
			jthrow_UnknownNativeErrorException_1(env, ret);
			return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_cond_wait
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1cond_1wait
  (JNIEnv * env, jobject inst, jlong condition, jlong mutex) {

	int ret = pthread_cond_wait((pthread_cond_t*)(uintptr_t) condition, (pthread_mutex_t*)(uintptr_t) mutex);
	switch(ret) {
		case(0):
			return;
		case(EPERM):
			jthrowCC_IllegalMonitorStateException_1(env, "The mutex was not owned by the current thread at the time of the call.");
			return;
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "The value specified by cond, or mutex is invalid.");
			return;
        case(EOWNERDEAD):
            jthrow_InconsistentMutexException(env);
            return;
        case(ENOTRECOVERABLE):
            jthrow_UnrecoverableMutexException(env);
            return;
		default:
			jthrow_UnknownNativeErrorException_1(env, ret);
			return;
	}
}
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_cond_timedwait
 * Signature: (JJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1cond_1timedwait
  (JNIEnv * env, jobject inst, jlong condition, jlong mutex, jlong timeout) {

	struct timespec tspec;
	uint64_t timeoutWithoutSeconds = timeout % 1000;

	tspec.tv_sec = (timeout - (timeoutWithoutSeconds)) / 1000;
	tspec.tv_nsec = timeoutWithoutSeconds * NANOSECONDS_PER_MILISECOND;

	int ret = pthread_cond_timedwait((pthread_cond_t*)(uintptr_t) condition, (pthread_mutex_t*)(uintptr_t) mutex, &tspec);
	switch(ret) {
		case(0):
			return true;
		case(ETIMEDOUT):
			return false;
		case(EPERM):
			jthrowCC_IllegalMonitorStateException_1(env, "The mutex was not owned by the current thread at the time of the call.");
			return false;
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "The value specified by cond, mutex, or timeout is invalid.");
			return false;
        case(EOWNERDEAD):
            jthrow_InconsistentMutexException(env);
            return false;
        case(ENOTRECOVERABLE):
            jthrow_UnrecoverableMutexException(env);
            return false;
		default:
			jthrow_UnknownNativeErrorException_1(env, ret);
			return false;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_cond_destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1cond_1destroy
  (JNIEnv * env, jobject inst, jlong condition) {
	int ret = pthread_cond_destroy((pthread_cond_t*)(uintptr_t) condition);
	switch(ret) {
		case(0):
			return;
		case(EBUSY):
			jthrowCC_IllegalStateException_1(env, "The mutex was not owned by the current thread at the time of the call.");
			return;
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "The value specified by cond, mutex, or timeout is invalid.");
			return;
		default:
			jthrow_UnknownNativeErrorException_1(env, ret);
			return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_cond_init
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1cond_1init
  (JNIEnv * env, jobject inst, jlong condition, jlong attributes) {
	int ret = pthread_cond_init((pthread_cond_t*)(uintptr_t) condition, (pthread_condattr_t*)(uintptr_t) attributes);
	switch(ret) {
		case(0):
			return;
		case(EBUSY):
			jthrowCC_IllegalStateException_1(env, "The mutex was not owned by the current thread at the time of the call.");
			return;
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "The value specified by cond, mutex, or timeout is invalid.");
			return;
		default:
			jthrow_UnknownNativeErrorException_1(env, ret);
			return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutexattr_setrobust
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutexattr_1setrobust
    (JNIEnv * env, jobject inst, jlong attributes, jint value) {
    int ret = pthread_mutexattr_setrobust((pthread_mutexattr_t*)(uintptr_t) attributes, (int) value);
    if (ret == 0) {
        return;
    }

    if (ret == EINVAL) {
        jthrowCC_IllegalArgumentException_1(env, "The value specified by attr or value is invalid.");
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, ret);
}
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutex_consistent
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutex_1consistent
        (JNIEnv * env, jobject inst, jlong mutex) {
    int ret = pthread_mutex_consistent((pthread_mutex_t*)(uintptr_t) mutex);
    if (ret == 0) {
        return;
    }

    if (ret == EINVAL) {
        jthrowCC_IllegalArgumentException_1(env, "The value specified by attr or value is invalid.");
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, ret);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    pthread_mutexattr_getrobust
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_pthread_1mutexattr_1getrobust
        (JNIEnv * env, jobject inst, jlong attributes) {
    int robustness = 0;
    int ret = pthread_mutexattr_getrobust((pthread_mutexattr_t*)(uintptr_t) attributes, &robustness);
    if (ret == 0) {
        return robustness;
    }

    if (ret == EINVAL) {
        jthrowCC_IllegalArgumentException_1(env, "The value specified by attr is invalid.");
        return 0;
    }

    jthrow_UnknownNativeErrorException_1(env, ret);
    return 0;
}


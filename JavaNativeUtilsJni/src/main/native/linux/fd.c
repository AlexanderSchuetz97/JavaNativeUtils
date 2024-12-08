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

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <limits.h>

#ifndef __USE_GNU
#define __USE_GNU
#endif



#include <poll.h>

#ifndef __USE_FILE_OFFSET64
#define __USE_FILE_OFFSET64
#endif
#ifndef __USE_LARGEFILE64
#define __USE_LARGEFILE64
#endif
#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif

#define _GNU_SOURCE
#include <sys/mman.h>


static_assert(sizeof(off_t) <= sizeof(jlong), "off_t doesnt fit in jlong");
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getFD
 * Signature: (Ljava/io/FileDescriptor;)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_getFD
  (JNIEnv * env, jobject inst, jobject fdo) {
	return getFD(env, fdo);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    lseek
 * Signature: (IJLeu/aschuetz/nativeutils/api/LinuxNativeUtil/lseek_whence;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_lseek
  (JNIEnv * env, jobject inst, jint fd, jlong off, jobject jwhence) {
	int whence;
	int ordinal = jenum_ordinal(env, jwhence);
	switch(ordinal) {
	case(0):
			whence = SEEK_SET;
			break;
	case(1):
			whence = SEEK_CUR;
			break;
	case(2):
			whence = SEEK_END;
			break;
	default:
		jthrowCC_IllegalArgumentException_1(env, "whence");
		return -1;
	}

	off_t res = lseek((int) fd, (off_t) off, whence);
	if (res == -1) {
		int err = errno;
		switch(err) {
		case(ESPIPE):
		case(EBADF):
			jthrow_InvalidFileDescriptorException(env);
			return -1;
		case(EINVAL):
			jthrowCC_IOException_1(env, "the resulting file offset would be negative, or beyond the end of a seekable device.");
			return -1;
		case(EOVERFLOW):
			jthrowCC_IOException_1(env, "The resulting file offset cannot be represented in a 64 bit number");
			return -1;
		default:
			jthrow_UnknownNativeErrorException_1(env, err);
			return -1;
		}
	}

	return (jlong) res;
}



void fromPollEvent(JNIEnv * env, jobject set, int revent) {
	jsize count = jenum_PollFD$PollEvent_count();

	if (((revent & POLLIN) == POLLIN) && count >= 0) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[0]);
	}

	if (((revent & POLLPRI) == POLLPRI) && count >= 1) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[1]);
	}

	if (((revent & POLLOUT) == POLLOUT) && count >= 2) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[2]);
	}

	if (((revent & POLLRDNORM) == POLLRDNORM) && count >= 3) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[3]);
	}

	if (((revent & POLLRDBAND) == POLLRDBAND) && count >= 4) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[4]);
	}

	if (((revent & POLLWRNORM) == POLLWRNORM) && count >= 5) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[5]);
	}

	if (((revent & POLLWRBAND) == POLLWRBAND) && count >= 6) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[6]);
	}

	if (((revent & POLLMSG) == POLLMSG) && count >= 7) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[7]);
	}

# ifdef POLLREMOVE
	if (((revent & POLLREMOVE) == POLLREMOVE) && count >= 8) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[8]);
	}
# endif

	if (((revent & POLLRDHUP) == POLLRDHUP) && count >= 9) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[9]);
	}

	if (((revent & POLLERR) == POLLERR) && count >= 10) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[10]);
	}

	if (((revent & POLLHUP) == POLLHUP) && count >= 11) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[11]);
	}

	if (((revent & POLLNVAL) == POLLNVAL) && count >= 12) {
		jcall_Collection_add(env, set, jenum_PollFD$PollEvent_values()[12]);
	}
}

int toPollEvent(JNIEnv * env, jobject eventSet) {
	int event = 0;

	jobject iter = jcall_Iterable_iterator(env, eventSet);
	if (iter == NULL) {
		return 0;
	}

	while(jcall_Iterator_hasNext(env, iter)) {
		jobject ele = jcall_Iterator_next(env, iter);
		if (ele == NULL) {
			return event;
		}

		switch(jenum_ordinal(env, ele)) {
		case(0):
			event |= POLLIN;
			break;
		case(1):
			event |= POLLPRI;
			break;
		case(2):
			event |= POLLOUT;
			break;
		case(3):
			event |= POLLRDNORM;
			break;
		case(4):
			event |= POLLRDBAND;
			break;
		case(5):
			event |= POLLWRNORM;
			break;
		case(6):
			event |= POLLWRBAND;
			break;
		case(7):
			event |= POLLMSG;
			break;
		case(8):
#ifdef POLLREMOVE
			event |= POLLREMOVE;
#endif
			break;
		case(9):
			event |= POLLRDHUP;
			break;
		case(10):
			event |= POLLERR;
			break;
		case(11):
			event |= POLLHUP;
			break;
		case(12):
			event |= POLLNVAL;
			break;
		default:
			break;
		}
	}



	return event;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    poll
 * Signature: ([Leu/aschuetz/nativeutils/api/structs/PollFD;I)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_poll
  (JNIEnv * env, jobject inst, jobjectArray fds, jint timeout) {
	if (fds == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "PollFD[] is null");
		return -1;
	}

	jsize len = (*env)->GetArrayLength(env, fds);

	struct pollfd pollfds[len];

	for (jsize i = 0; i < len; i++) {
		jobject ele = (*env) ->GetObjectArrayElement(env, fds, i);
		if (ele == NULL) {
			jthrowCC_IllegalArgumentException_1(env, "PollFD[] contains null elements");
			return -1;
		}


		jobject enumSet = jget_PollFD_events(env, inst);
		if (enumSet == NULL) {
			(*env)->DeleteLocalRef(env, ele);
			jthrowCC_IllegalArgumentException_1(env, "PollFD[] contains an element with null eventSet in 'events' field");
			return -1;
		}

		pollfds[i].fd = jget_PollFD_fd(env, ele);
		pollfds[i].events = toPollEvent(env, enumSet);
		pollfds[i].revents = 0;
		(*env)->DeleteLocalRef(env, ele);
		(*env)->DeleteLocalRef(env, enumSet);
	}

	int result;
	while(true) {
		result = poll(pollfds, (nfds_t) len, (int) timeout);

		if (result == 0) {
			return 0;
		}

		if (result > 0) {
			break;
		}

		int err = errno;
		switch(err) {
			case(EINTR):
				continue;
			case(EINVAL):
				jthrowCC_IllegalArgumentException_1(env, "too many file descriptors for poll");
				return -1;
			case(ENOMEM):
				jthrowCC_OutOfMemoryError_1(env, "Kernel Memory");
				return -1;
			default:
				jthrow_UnknownNativeErrorException_1(env, err);
				return -1;
		}
	}

	for (jsize i = 0; i < len; i++) {
		jobject ele = (*env) ->GetObjectArrayElement(env, fds, i);
		if (ele == NULL) {
			jthrowCC_IllegalArgumentException_1(env, "PollFD[] contains null elements");
			return -1;
		}

		jobject enumSet = jget_PollFD_revents(env, ele);
		if (enumSet == NULL) {
			(*env)->DeleteLocalRef(env, ele);
			jthrowCC_IllegalArgumentException_1(env, "PollFD[] contains an element with null eventSet in 'revents' field");
			return -1;
		}

		jcall_Collection_clear(env, enumSet);
		fromPollEvent(env, enumSet, pollfds[i].revents);

		(*env)->DeleteLocalRef(env, ele);
		(*env)->DeleteLocalRef(env, enumSet);
	}


	return result;
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    _munmap
 * Signature: (JJ)J
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil__1munmap
  (JNIEnv * env, jclass clazz, jlong ptr, jlong size) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	int res = munmap(vptr, (size_t) size);

	if (res != -1) {
		return;
	}

	int err = errno;
	if (err == EINVAL) {
		jthrowCC_IllegalArgumentException_1(env, "alignment of size/ptr is wrong");
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
}

#ifndef __OFF64_T_TYPE
#define __OFF64_T_TYPE off64_t
#endif

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    _mmap
 * Signature: (IJIZZJ)V
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil__1mmap
  (JNIEnv * env, jclass clazz, jint fd, jlong length, jint flags, jboolean read, jboolean write, jlong offset) {

	int prot;
	if (read && write) {
		prot = PROT_READ | PROT_WRITE;
	} else if (read) {
		prot = PROT_READ;
	} else if (write) {
		prot = PROT_WRITE;
	} else {
		prot = PROT_NONE;
	}

	void * res = mmap64(NULL, (size_t) length, prot, flags, fd, (__OFF64_T_TYPE) offset);
	if (res != MAP_FAILED) {
		return (jlong) (uintptr_t) res;
	}

	int err = errno;
	switch(err) {
	case(EACCES):
		jthrowCC_IllegalStateException_1(env, "FD is incompatible with the requested flags.");
		return -1;
	case(EAGAIN):
		jthrowCC_IllegalArgumentException_1(env, "The file has been locked, or too much memory has been locked");
		return -1;
	case(EBADF):
		jthrow_InvalidFileDescriptorException(env);
		return -1;
	case(EINVAL):
		jthrowCC_IllegalArgumentException_1(env, "alignment of arguments is invalid");
		return -1;
	case(ENFILE):
		jthrowCC_QuotaExceededException_1(env, NULL, NULL, "The system-wide limit on the total number of open files has been reached.");
		return -1;
	case(ENODEV):
		jthrowCC_UnsupportedOperationException_1(env, "The underlying filesystem of the specified file does not support memory mapping.");
		return -1;
	case(ENOMEM):
		jthrowCC_OutOfMemoryError_1(env, "not enough memory to create mapping or the maximum number of memory mappings has been reached");
		return -1;
	case(EOVERFLOW):
		jthrowCC_OutOfMemoryError_1(env, "mapping is too large for 32bit architecture");
		return -1;
	case(EPERM):
		jthrowCC_AccessDeniedException_1(env, NULL, NULL, "The operation was prevented by a file seal or the MAP_HUGETLB was present and the process is not privileged.");
		return -1;
	case(ETXTBSY):
		jthrowCC_IllegalStateException_1(env, "MAP_DENYWRITE was set but the object specified by fd is open for writing.");
		return -1;
	default:
		jthrow_UnknownNativeErrorException_1(env, err);
		return -1;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    shm_open
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_shm_1open
  (JNIEnv * env, jobject inst, jstring name, jint oflag, jint mode) {
	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return -1;
	}

	const char * cname = (*env)->GetStringUTFChars(env, name, NULL);

	if (cname == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return -1;
	}

	int res = shm_open(cname, (int) oflag, (mode_t) mode);
	(*env)->ReleaseStringUTFChars(env, name, cname);
	if (res > 0) {
		return res;
	}

	int err = errno;
	switch(err) {
	case(EACCES):
		jthrow_AccessDeniedException(env, name);
		return -1;
	case(EEXIST):
		jthrow_FileAlreadyExistsException(env, name);
		return -1;
	case(EINVAL):
		jthrowCC_IllegalArgumentException_1(env, "name is invalid");
		return -1;
	case(EMFILE):
		jthrowCC_QuotaExceededException(env, "The per-process limit on the number of open file descriptors has been reached.");
		return -1;
	case(ENAMETOOLONG):
		jthrowCC_IllegalArgumentException_1(env, "name is too long");
		return -1;
	case(ENFILE):
		jthrowCC_QuotaExceededException(env, "The system-wide limit on the total number of open files has been reached.");
		return -1;
	case(ENOENT):
		jthrow_FileNotFoundException_1(env, name);
		return -1;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
	return -1;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    shm_unlink
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_shm_1unlink
  (JNIEnv * env, jobject inst, jstring name) {
	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return;
	}

	const char * cname = (*env)->GetStringUTFChars(env, name, NULL);

	if (cname == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}

	int res = shm_unlink(cname);
	(*env)->ReleaseStringUTFChars(env, name, cname);
	if (res == 0) {
		return;
	}

	int err = errno;
	switch(err) {
	case(EACCES):
		jthrow_AccessDeniedException(env, name);
		return;
	case(EINVAL):
		jthrowCC_IllegalArgumentException_1(env, "name is invalid");
		return;
	case(ENAMETOOLONG):
		jthrowCC_IllegalArgumentException_1(env, "name is too long");
		return;
	case(ENOENT):
		jthrow_FileNotFoundException_1(env, name);
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
	return;
}



/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    _msync
 * Signature: (JJJZ)J
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil__1msync
  (JNIEnv * env, jclass clazz, jlong ptr, jlong off, jlong len, jboolean invalidate) {
	void * vptr = (void *) (uintptr_t) ptr;
	if (vptr == NULL) {
		jthrowCC_NullPointerException_1(env, "ptr");
		return;
	}

	vptr+=off;
	int flags = MS_SYNC;

	if (invalidate) {
		flags |= MS_INVALIDATE;
	}

	if (msync(vptr, len, flags) == 0) {
		return;
	}

	int err = errno;

	switch(err) {
	case(EBUSY):
		jthrowCC_AccessDeniedException_1(env, NULL, NULL, "cant invalidate region due to memory lock");
		return;
	case(EINVAL):
		jthrowCC_IllegalArgumentException_1(env, "ptr+off is not a multiple of PAGESIZE");
		return;
	case(ENOMEM):
		jthrowCC_IllegalStateException_1(env, "The indicated memory (or part of it) was not mapped.");
		return;
	default:
		jthrow_UnknownNativeErrorException_1(env, err);
		return;
	}
}

void handle_ioctl_err(JNIEnv* env, int err) {
	switch(err) {
	case(EBADF):
		jthrow_InvalidFileDescriptorException(env);
		return;
	case(EFAULT):
		jthrowCC_IllegalArgumentException_1(env, "argument references an inaccessible memory area");
		return;
	case(EINVAL):
		jthrowCC_IllegalArgumentException_1(env, "request code or parameter is invalid");
		return;
	case(ENOTTY):
		jthrowCC_UnsupportedOperationException_1(env, "The specified request does not apply to the kind of object that the file descriptor references");
		return;
	default:
		jthrow_UnknownNativeErrorException_1(env, err);
		return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    ioctl
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_ioctl__II
  (JNIEnv * env, jobject inst, jint fd, jint code) {

	int res = ioctl(fd, code);

	if (res == -1) {
		handle_ioctl_err(env, errno);
		return -1;
	}

	return res;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    ioctl
 * Signature: (II[BI)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_ioctl__II_3BI
  (JNIEnv * env, jobject inst, jint fd, jint code, jbyteArray buf, jint off) {
	if (buf == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return -1;
	}

	if (off < 0 || off >= (*env)->GetArrayLength(env, buf)) {
		jthrowCC_IllegalArgumentException_1(env, "off out of bounds");
		return -1;
	}

	jbyte* nbuf = (*env)->GetByteArrayElements(env, buf, NULL);
	if (nbuf == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return -1;
	}

	jbyte* param = nbuf;
	param+=off;

	int res = ioctl(fd, code, (void*) param);

	if (res == -1) {
		int err = errno;
		(*env)->ReleaseByteArrayElements(env, buf, nbuf, JNI_OK);
		handle_ioctl_err(env, err);
		return -1;
	}


	(*env)->ReleaseByteArrayElements(env, buf, nbuf, JNI_OK);
	return res;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    ioctl
 * Signature: (IIJ)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_ioctl__IIJ
  (JNIEnv * env, jobject inst, jint fd, jint code, jlong jvalue) {
	void* value = (void*) (uintptr_t) jvalue;
	int res = ioctl(fd, code, value);
	if (res == -1) {
		handle_ioctl_err(env, errno);
		return -1;
	}

	return res;
}

void handle_fcntl_error(JNIEnv * env, int err, int code) {
	//TODO smarter??
	switch(err) {
	case(EBADF):
		jthrow_InvalidFileDescriptorException(env);
		return;
	default:
		jthrow_UnknownNativeErrorException_1(env, err);
		return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fcntl
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_fcntl__II
  (JNIEnv * env, jobject inst, jint fd, jint code) {
	int res = fcntl(fd, code);
	if (res == -1) {
		handle_fcntl_error(env, errno, code);
		return -1;
	}

	return res;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fcntl
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_fcntl__III
  (JNIEnv * env, jobject inst, jint fd, jint code, jint value) {
	int res = fcntl(fd, code, (int) value);
	if (res == -1) {
		handle_fcntl_error(env, errno, code);
		return -1;
	}

	return res;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fcntl
 * Signature: (IIJ)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_fcntl__IIJ
  (JNIEnv * env, jobject inst, jint fd, jint code, jlong value) {
	int res = fcntl(fd, code, (void*) (uintptr_t) value);
	if (res == -1) {
		handle_fcntl_error(env, errno, code);
		return -1;
	}

	return res;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fcntl
 * Signature: (II[BI)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_fcntl__II_3BI
  (JNIEnv * env, jobject inst, jint fd, jint code, jbyteArray buf, jint off) {
	if (buf == NULL) {
		jthrowCC_NullPointerException_1(env, "buf");
		return -1;
	}

	if (off < 0 || off >= (*env)->GetArrayLength(env, buf)) {
		jthrowCC_IllegalArgumentException_1(env, "off out of bounds");
		return -1;
	}

	jbyte* nbuf = (*env)->GetByteArrayElements(env, buf, NULL);
	if (nbuf == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return -1;
	}

	jbyte* param = nbuf;
	param+=off;

	int res = fcntl(fd, code, (void*) param);

	if (res == -1) {
		int err = errno;
		(*env)->ReleaseByteArrayElements(env, buf, nbuf, JNI_OK);
		handle_fcntl_error(env, err, code);
		return -1;
	}


	(*env)->ReleaseByteArrayElements(env, buf, nbuf, JNI_OK);
	return res;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    ftruncate
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_ftruncate
  (JNIEnv * env, jobject inst, jint fd, jlong off) {
	if (fd < 0) {
		jthrow_InvalidFileDescriptorException(env);
		return;
	}

	if (ftruncate((int) fd, (off_t) off) == 0) {
		return;
	}


	int err = errno;
	switch(err) {
	case(EBADF):
		jthrow_InvalidFileDescriptorException(env);
		return;
	case(EINVAL):
		jthrow_InvalidFileDescriptorException(env);
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
	return;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    truncate
 * Signature: (Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_truncate
  (JNIEnv * env, jobject inst, jstring name, jlong off) {
	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return;
	}

	const char * cname = (*env)->GetStringUTFChars(env, name, NULL);

	if (cname == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return;
	}
	while(true) {
		int res = truncate(cname, (off_t) off);
		if (res == 0) {
			goto cleanup;
		}

		int err = errno;
		switch(err) {
		case(EACCES):
			jthrow_AccessDeniedException(env, name);
			goto cleanup;
		case(EFBIG):
			jthrowCC_IllegalArgumentException_1(env, "The argument length is larger than the maximum file size.");
			goto cleanup;
		case(EINTR):
			continue;
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "The argument length is negative or larger than the maximum file size.");
			goto cleanup;
		case(EIO):
			jthrowCC_IOException_1(env, "An I/O error occurred updating the inode.");
			goto cleanup;
		case(EISDIR):
			jthrow_FileIsDirectoryException(env, name);
			goto cleanup;
		case(ELOOP):
			jthrow_FileSystemLoopException(env, name);
			goto cleanup;
		case(ENAMETOOLONG):
			jthrowCC_IllegalArgumentException_1(env, "name is too long");
			goto cleanup;
		case(ENOENT):
			jthrow_FileNotFoundException(env);
			goto cleanup;
		case(ENOTDIR):
			jthrowCC_NotDirectoryException(env, "Path component is not a directory");
			goto cleanup;
		case(EPERM):
			jthrowCC_PermissionDeniedException(env, "The operation was either prevented by a file seal or the underlying filesystem does not support extending a file beyond its current size");
			goto cleanup;
		case(EROFS):
			jthrow_ReadOnlyFileSystemException(env);
			goto cleanup;
		case(ETXTBSY):
			jthrowCC_IOException_1(env, "The file is an executable file that is being executed.");
			goto cleanup;
		}

		jthrow_UnknownNativeErrorException_1(env, err);
		goto cleanup;
	}


	cleanup:
	(*env)->ReleaseStringUTFChars(env, name, cname);
	return;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fsync
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_fsync
  (JNIEnv *env, jobject inst, jint fd) {
	if (fsync((int)fd) == 0) {
		return;
	}


	int err = errno;
	switch(err) {
	case(EIO):
		jthrowCC_IOException_1(env, "An I/O error occurred during synchronization.");
		return;
	case(EBADF):
		jthrow_InvalidFileDescriptorException(env);
		return;
	case(EROFS):
	case(EINVAL):
		jthrow_ReadOnlyFileSystemException(env);
		return;
	default:
		jthrow_UnknownNativeErrorException_1(env, err);
		return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    memfd_create
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_memfd_1create
        (JNIEnv * env, jobject inst, jstring jname, jint flags) {

    if (jname == NULL) {
        jthrowCC_NullPointerException_1(env, "name");
        return -1;
    }

    const char* name = (*env)->GetStringUTFChars(env, jname, NULL);
    if (name == NULL) {
        jthrowCC_NullPointerException_1(env, "name");
        return -1;
    }


    int fd = memfd_create(name, (unsigned int) flags);
    (*env)->ReleaseStringUTFChars(env, jname, name);
    if (fd != -1) {
        return fd;
    }

    int err = errno;
    switch (err) {
        case (EINVAL):
            jthrowCC_IllegalArgumentException_1(env,"Either name is longer than 249 bytes or flags contained unknown bits or bits that cannot be combined (ex. both MFD_HUGETLB and MFD_ALLOW_SEALING cant be combined)");
            return -1;
        case (EMFILE):
            jthrowCC_QuotaExceededException(env,"The per-process limit on the number of open file descriptors has been reached.");
            return -1;
        case (ENFILE):
            jthrowCC_QuotaExceededException(env,"The system-wide limit on the total number of open files has been reached.");
            return -1;
        case (ENOMEM):
            jthrowCC_OutOfMemoryError_1(env, "There was insufficient memory available to create a new anonymous file.");
            return -1;
        case (EPERM):
            jthrowCC_PermissionDeniedException(env,"The MFD_HUGETLB flag was specified, but the caller was not privileged.");
            return -1;
        default:
            jthrow_UnknownNativeErrorException_1(env, err);
            return -1;
    }
}

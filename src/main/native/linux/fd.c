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

#include <sys/mman.h>


static_assert(sizeof(off_t) <= sizeof(jlong), "off_t doesnt fit in jlong");
/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getFD
 * Signature: (Ljava/io/FileDescriptor;)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_getFD
  (JNIEnv * env, jobject inst, jobject fdo) {
	return getFD(env, fdo);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    lseek
 * Signature: (IJLio/github/alexanderschuetz97/nativeutils/api/LinuxNativeUtil/lseek_whence;)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_lseek
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

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    open
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_open__Ljava_lang_String_2I
	(JNIEnv * env, jobject inst, jstring path, jint flags) {
	if (path == NULL) {
		jthrowCC_NullPointerException_1(env, "path");
		return -1;
	}

	int cflags = (int) flags;
	if (cflags & O_CREAT) {
		jthrowCC_IllegalArgumentException_1(env, "O_CREAT requires mode");
		return -1;
	}

	const char * ptr = (*env)->GetStringUTFChars(env, path, NULL);
	if (ptr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return -1;
	}


	while(true) {
		int fd = open(ptr, (int) flags);

		if (fd == -1) {
			int err = errno;
			switch(err) {
				case(EACCES):
					jthrowCC_AccessDeniedException_1(env, ptr, NULL, NULL);
				break;
				case(EBUSY):
					jthrowCC_AccessDeniedException_1(env, ptr, NULL, "exclusive access not possible");
				break;
				case(EDQUOT):
					jthrowCC_QuotaExceededException_1(env, ptr, NULL, NULL);
				break;
				case(EEXIST):
					jthrowCC_FileAlreadyExistsException_1(env, ptr, NULL, NULL);
				break;
				case(EINTR):
					continue;
				case(EINVAL):
					jthrowCC_IllegalArgumentException_1(env, "open");
				break;
				case(EISDIR):
					//TODO
					jthrowCC_IOException_1(env, "path refers to a directory");
				break;
				case(ELOOP):
					jthrowCC_FileSystemLoopException(env, ptr);
				break;
				case(EMFILE):
					jthrowCC_QuotaExceededException_1(env, ptr, NULL, "per process limit of open files exceeded");
				break;
				case(ENAMETOOLONG):
					jthrowCC_InvalidPathException(env, ptr, "path too long");
				break;
				case(ENFILE):
					jthrowCC_QuotaExceededException_1(env, ptr, NULL, "The system-wide limit on the total number of open files has been reached.");
				break;
				case(ENOENT):
					jthrowCC_FileNotFoundException_1(env, ptr);
				break;
				case(ENOMEM):
					jthrowCC_OutOfMemoryError_1(env, "pipe or kernel");
				break;
				case(ENOSPC):
					jthrowCC_IOException_1(env, "file was to be created but the device is full");
				break;
				case(ENOTDIR):
					jthrowCC_NotDirectoryException(env, ptr);
				break;
				case(ENXIO):
					jthrowCC_IOException_1(env, "ENXIO");
				break;
				case(EOPNOTSUPP):
					jthrowCC_IOException_1(env, "The filesystem containing pathname does not support O_TMPFILE.");
				break;
				case(EOVERFLOW):
					jthrowCC_IOException_1(env, "The file is too large to be opened");
				break;
				case(EPERM):
					jthrowCC_AccessDeniedException_1(env, ptr, NULL, "The operation was prevented by a file seal");
				break;
				case(EROFS):
					jthrow_ReadOnlyFileSystemException(env);
				break;
				case(ETXTBSY):
					jthrowCC_AccessDeniedException_1(env, ptr, NULL, "write access to a executable, swap or kernel firmware file was requested");
				break;
				case(EWOULDBLOCK):
					(*env)->ReleaseStringUTFChars(env, path, ptr);
					return -1;
				default:
					jthrow_UnknownNativeErrorException_1(env, err);
				break;
			}
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			return -1;
		}

		(*env)->ReleaseStringUTFChars(env, path, ptr);
		return (jint) fd;

	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    open
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_open__Ljava_lang_String_2II
  (JNIEnv * env, jobject inst, jstring path, jint flags, jint mode) {
	if (path == NULL) {
		jthrowCC_NullPointerException_1(env, "path");
		return -1;
	}
	const char * ptr = (*env)->GetStringUTFChars(env, path, NULL);
	if (ptr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return -1;
	}

	while(true) {
		int fd = open(ptr, (int) flags, (mode_t) mode);

		if (fd == -1) {
			int err = errno;
			switch(err) {
				case(EACCES):
					jthrowCC_AccessDeniedException_1(env, ptr, NULL, NULL);
				break;
				case(EBUSY):
					jthrowCC_AccessDeniedException_1(env, ptr, NULL, "exclusive access not possible");
				break;
				case(EDQUOT):
					jthrowCC_QuotaExceededException_1(env, ptr, NULL, NULL);
				break;
				case(EEXIST):
					jthrowCC_FileAlreadyExistsException_1(env, ptr, NULL, NULL);
				break;
				case(EINTR):
					continue;
				case(EINVAL):
					jthrowCC_IllegalArgumentException_1(env, "open");
				break;
				case(EISDIR):
					//TODO
					jthrowC_IOException_1(env, "path refers to a directory");
				break;
				case(ELOOP):
					jthrowCC_FileSystemLoopException(env, ptr);
				break;
				case(EMFILE):
					jthrowCC_QuotaExceededException_1(env, ptr, NULL, "per process limit of open files exceeded");
				break;
				case(ENAMETOOLONG):
					jthrowCC_InvalidPathException(env, ptr, "path too long");
				break;
				case(ENFILE):
					jthrowCC_QuotaExceededException_1(env, ptr, NULL, "The system-wide limit on the total number of open files has been reached.");
				break;
				case(ENOENT):
					jthrowCC_FileNotFoundException_1(env, ptr);
				break;
				case(ENOMEM):
					jthrowCC_OutOfMemoryError_1(env, "pipe or kernel");
				break;
				case(ENOSPC):
					jthrowC_IOException_1(env, "file was to be created but the device is full");
				break;
				case(ENOTDIR):
					jthrowCC_NotDirectoryException(env, ptr);
				break;
				case(ENXIO):
					jthrowC_IOException_1(env, "ENXIO");
				break;
				case(EOPNOTSUPP):
					jthrowC_IOException_1(env, "The filesystem containing pathname does not support O_TMPFILE.");
				break;
				case(EOVERFLOW):
					jthrowC_IOException_1(env, "The file is too large to be opened");
				break;
				case(EPERM):
					jthrowCC_AccessDeniedException_1(env, ptr, NULL, "The operation was prevented by a file seal");
				break;
				case(EROFS):
					jthrow_ReadOnlyFileSystemException(env);
				break;
				case(ETXTBSY):
					jthrowCC_AccessDeniedException_1(env, ptr, NULL, "write access to a executable, swap or kernel firmware file was requested");
				break;
				case(EWOULDBLOCK):
					(*env)->ReleaseStringUTFChars(env, path, ptr);
					return -1;
				default:
					jthrow_UnknownNativeErrorException_1(env, err);
				break;
			}
			(*env)->ReleaseStringUTFChars(env, path, ptr);
			return -1;
		}

		(*env)->ReleaseStringUTFChars(env, path, ptr);
		return (jint) fd;

	}
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    close
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_close
  (JNIEnv * env, jobject inst, jint fd) {
	while (true) {
		int res = close(fd);

		if (res != -1) {
			return;
		}

		int err = errno;
		switch(err) {
		case(EBADF):
			jthrow_InvalidFileDescriptorException(env);
			return;
		case(EINTR):
			continue;
		case(EIO):
			jthrowC_IOException_1(env, "Failed to close file descriptor");
			return;
		}
	}
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    poll
 * Signature: ([Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD;I)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_poll
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

jint handle_read_error(JNIEnv * env, int err) {
	switch(err) {
		#if EAGAIN != EWOULDBLOCK
		case(EWOULDBLOCK):
		#endif
		case(EAGAIN):
			return 0;
		case(EBADF):
			jthrow_InvalidFileDescriptorException(env);
			return -1;
		case EINVAL:
			jthrowCC_IllegalArgumentException_1(env, "file descriptor is unsuitable for reading or buffer size does not match the required buffer size");
			return -1;
		case EIO:
			jthrowC_IOException_1(env, "I/O error");
			return -1;
		case EISDIR:
			jthrowCC_IllegalArgumentException_1(env, "file descriptor refers to a directory");
			return -1;
		default:
			jthrow_UnknownNativeErrorException_1(env, err);
			return -1;
	}
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    read
 * Signature: (IJI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_read__IJI
  (JNIEnv * env, jobject inst, jint fd, jlong ptr, jint len) {
	void * buf = (void *) (uintptr_t) ptr;
	if (buf == NULL) {
		jthrowCC_NullPointerException_1(env, "buffer");
		return -1;
	}

	if (len < 0) {
		jthrowCC_IllegalArgumentException_1(env, "length");
		return -1;
	}

	while(true) {
		size_t r = read(fd, buf, len);
		if (r == 0) {
			return -1;
		}

		if (r != 0) {
			return r;
		}

		int err = errno;
		if (err == EINTR) {
			continue;
		}

		return handle_read_error(env, err);
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    read
 * Signature: (I[BII)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_read__I_3BII
  (JNIEnv * env, jobject inst, jint fd, jbyteArray jbuf, jint off, jint len) {
	if (jbuf == NULL) {
		jthrowCC_NullPointerException_1(env, "buffer");
		return -1;
	}

	jsize alen = (*env)->GetArrayLength(env, jbuf);

	if (off < 0 || len < 0 || len+off > alen) {
		jthrowCC_IllegalArgumentException_1(env, "offset+lengths");
		return -1;
	}

	void* data = (*env)->GetByteArrayElements(env, jbuf, NULL);
	if (data == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return -1;
	}

	while(true) {
		size_t r = read(fd, data+off, len);

		if (r == 0) {
			//EOF
			(*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_ABORT);
			return -1;
		}

		if (r != -1) {
			(*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_OK);
			return r;
		}

		int err = errno;
		if (err == EINTR) {
			continue;
		}

		(*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_ABORT);

		return handle_read_error(env, err);
	}

}

jint handle_write_error(JNIEnv * env, int err) {
	switch(err) {
		#if EAGAIN != EWOULDBLOCK
		case(EWOULDBLOCK):
		#endif
		case(EAGAIN):
			return 0;
		case(EBADF):
			jthrow_InvalidFileDescriptorException(env);
			return -1;
		case(EDESTADDRREQ):
			jthrowCC_IllegalStateException_1(env, "file descriptor refers to a datagram socket for which a peer address has not been set using connect.");
			return -1;
		case(EDQUOT):
			jthrowCC_QuotaExceededException_1(env, NULL, NULL, "The user's quota of disk blocks on the filesystem containing the file referred to by the file descriptor has been exhausted.");
			return -1;
		case(EFBIG):
			jthrowC_IOException_1(env, "An attempt was made to write a file that exceeds the implementation-defined maximum file size or the process's file size limit, or to write at a position past the maximum allowed offset.");
			return -1;
		case EINVAL:
			jthrowCC_IllegalArgumentException_1(env, "file descriptor is unsuitable for writing or the file/buffer position/length is not properly aligned.");
			return -1;
		case EIO:
			jthrowC_IOException_1(env, "I/O error");
			return -1;
		case EPERM:
			jthrowCC_AccessDeniedException_1(env, NULL, NULL, "Operation was prevented by a file seal");
			return -1;
		case EPIPE:
			jthrowC_IOException_1(env, "Broken pipe");
			return -1;
		case ENOSPC:
			jthrowC_IOException_1(env, "The device containing the file referred to by fd has no room for the data.");
			return -1;
		case EISDIR:
			jthrowCC_IllegalArgumentException_1(env, "file descriptor refers to a directory");
			return -1;
		default:
			jthrow_UnknownNativeErrorException_1(env, err);
			return -1;
	}
}


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    write
 * Signature: (IJI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_write__IJI
  (JNIEnv * env, jobject inst, jint fd, jlong jptr, jint len) {
	void *buf = (void*) (uintptr_t) jptr;
	if (buf == NULL) {
		jthrowCC_NullPointerException_1(env, "buffer");
		return -1;
	}

	if (len < 0) {
		jthrowCC_IllegalArgumentException_1(env, "len");
		return -1;
	}

	while(true) {
		size_t r = write(fd, buf, len);
		if (r != -1) {
			return r;
		}

		int err = errno;
		if (err == EINTR) {
			continue;
		}

		return handle_write_error(env, err);
	}
}



/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    write
 * Signature: (I[BII)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_write__I_3BII
  (JNIEnv * env, jobject inst, jint fd, jbyteArray jbuf, jint off, jint len) {
	if (jbuf == NULL) {
		jthrowCC_NullPointerException_1(env, "buffer");
		return -1;
	}

	jsize alen = (*env)->GetArrayLength(env, jbuf);

	if (off < 0 || len < 0 || len+off > alen) {
		jthrowCC_IllegalArgumentException_1(env, "offset+lengths");
		return -1;
	}

	while(true) {
		void* data = (*env)->GetByteArrayElements(env, jbuf, NULL);

		size_t r = write(fd, data+off, len);

		if (r != -1) {
			(*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_OK);
			return r;
		}

		int err = errno;
		(*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_ABORT);

		if (err == EINTR) {
			continue;
		}

		return handle_write_error(env, err);

	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    _munmap
 * Signature: (JJ)J
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil__1munmap
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    _mmap
 * Signature: (IJIZZJ)V
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil__1mmap
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    shm_open
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_shm_1open
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    shm_unlink
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_shm_1unlink
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    _msync
 * Signature: (JJJZ)J
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil__1msync
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    ioctl
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_ioctl__II
  (JNIEnv * env, jobject inst, jint fd, jint code) {

	int res = ioctl(fd, code);

	if (res == -1) {
		handle_ioctl_err(env, errno);
		return -1;
	}

	return res;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    ioctl
 * Signature: (II[BI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_ioctl__II_3BI
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    ioctl
 * Signature: (IIJ)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_ioctl__IIJ
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fcntl
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_fcntl__II
  (JNIEnv * env, jobject inst, jint fd, jint code) {
	int res = fcntl(fd, code);
	if (res == -1) {
		handle_fcntl_error(env, errno, code);
		return -1;
	}

	return res;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fcntl
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_fcntl__III
  (JNIEnv * env, jobject inst, jint fd, jint code, jint value) {
	int res = fcntl(fd, code, (int) value);
	if (res == -1) {
		handle_fcntl_error(env, errno, code);
		return -1;
	}

	return res;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fcntl
 * Signature: (IIJ)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_fcntl__IIJ
  (JNIEnv * env, jobject inst, jint fd, jint code, jlong value) {
	int res = fcntl(fd, code, (void*) (uintptr_t) value);
	if (res == -1) {
		handle_fcntl_error(env, errno, code);
		return -1;
	}

	return res;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fcntl
 * Signature: (II[BI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_fcntl__II_3BI
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    ftruncate
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_ftruncate
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    truncate
 * Signature: (Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_truncate
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    fsync
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_fsync
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



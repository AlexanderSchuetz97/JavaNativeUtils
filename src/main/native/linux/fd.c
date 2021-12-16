//
// Copyright Alexander Schütz, 2021
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

#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <poll.h>

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
			badFileDescriptor(env);
			return;
		case(EINTR):
			continue;
		case(EIO):
			throwIOExc(env, "Failed to close file descriptor");
			return;
		}
	}
}

void fromPollEvent(JNIEnv * env, jobject set, int revent) {
	if (((revent & POLLIN) == POLLIN) && PollFD_PollEvent_values_size >= 0) {
		collection_add(env, set, PollFD_PollEvent_values[0]);
	}

	if (((revent & POLLPRI) == POLLPRI) && PollFD_PollEvent_values_size >= 1) {
		collection_add(env, set, PollFD_PollEvent_values[1]);
	}

	if (((revent & POLLOUT) == POLLOUT) && PollFD_PollEvent_values_size >= 2) {

		collection_add(env, set, PollFD_PollEvent_values[2]);
	}

	if (((revent & POLLRDNORM) == POLLRDNORM) && PollFD_PollEvent_values_size >= 3) {
		collection_add(env, set, PollFD_PollEvent_values[3]);
	}

	if (((revent & POLLRDBAND) == POLLRDBAND) && PollFD_PollEvent_values_size >= 4) {
		collection_add(env, set, PollFD_PollEvent_values[4]);
	}

	if (((revent & POLLWRNORM) == POLLWRNORM) && PollFD_PollEvent_values_size >= 5) {
		collection_add(env, set, PollFD_PollEvent_values[5]);
	}

	if (((revent & POLLWRBAND) == POLLWRBAND) && PollFD_PollEvent_values_size >= 6) {
		collection_add(env, set, PollFD_PollEvent_values[6]);
	}

	if (((revent & POLLMSG) == POLLMSG) && PollFD_PollEvent_values_size >= 7) {
		collection_add(env, set, PollFD_PollEvent_values[7]);
	}

	if (((revent & POLLREMOVE) == POLLREMOVE) && PollFD_PollEvent_values_size >= 8) {
		collection_add(env, set, PollFD_PollEvent_values[8]);
	}

	if (((revent & POLLRDHUP) == POLLRDHUP) && PollFD_PollEvent_values_size >= 9) {
		collection_add(env, set, PollFD_PollEvent_values[9]);
	}

	if (((revent & POLLERR) == POLLERR) && PollFD_PollEvent_values_size >= 10) {
		collection_add(env, set, PollFD_PollEvent_values[10]);
	}

	if (((revent & POLLHUP) == POLLHUP) && PollFD_PollEvent_values_size >= 11) {
		collection_add(env, set, PollFD_PollEvent_values[11]);
	}

	if (((revent & POLLNVAL) == POLLNVAL) && PollFD_PollEvent_values_size >= 12) {
		collection_add(env, set, PollFD_PollEvent_values[12]);
	}
}

int toPollEvent(JNIEnv * env, jobject eventSet) {
	int event = 0;

	jobject iter = new_iterator(env, eventSet);
	for (jobject ele = iterator_next(env, iter); ele != NULL; ele = iterator_next(env, iter)) {
		switch(getEnumOrdinal(env, ele)) {
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
			event |= POLLREMOVE;
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
		throwIllegalArgumentsExc(env, "PollFD[] is null");
		return -1;
	}

	jsize len = (*env)->GetArrayLength(env, fds);

	struct pollfd pollfds[len];

	for (jsize i = 0; i < len; i++) {
		jobject ele = (*env) ->GetObjectArrayElement(env, fds, i);
		if (ele == NULL) {
			throwIllegalArgumentsExc(env, "PollFD[] contains null elements");
			return -1;
		}

		jobject enumSet = (*env)->GetObjectField(env, ele, PollFD_events);
		if (enumSet == NULL) {
			(*env)->DeleteLocalRef(env, ele);
			throwIllegalArgumentsExc(env, "PollFD[] contains an element with null eventSet in 'events' field");
			return -1;
		}

		pollfds[i].fd = (*env)->GetIntField(env, ele, PollFD_fd);
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
				throwIllegalArgumentsExc(env, "too many file descriptors for poll");
				return -1;
			case(ENOMEM):
				throwOOM(env, "Kernel Memory");
				return -1;
			default:
				unknownError(env, err);
				return -1;
		}
	}

	for (jsize i = 0; i < len; i++) {
		jobject ele = (*env) ->GetObjectArrayElement(env, fds, i);
		if (ele == NULL) {
			throwIllegalArgumentsExc(env, "PollFD[] contains null elements");
			return -1;
		}

		jobject enumSet = (*env)->GetObjectField(env, ele, PollFD_revents);
		if (enumSet == NULL) {
			(*env)->DeleteLocalRef(env, ele);
			throwIllegalArgumentsExc(env, "PollFD[] contains an element with null eventSet in 'revents' field");
			return -1;
		}

		collection_clear(env, enumSet);
		fromPollEvent(env, enumSet, pollfds[i].revents);

		(*env)->DeleteLocalRef(env, ele);
		(*env)->DeleteLocalRef(env, enumSet);
	}


	return result;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    read
 * Signature: (I[BII)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_read
  (JNIEnv * env, jobject inst, jint fd, jbyteArray jbuf, jint off, jint len) {
	if (jbuf == NULL) {
		throwNullPointerException(env, "buffer");
		return -1;
	}

	jsize alen = (*env)->GetArrayLength(env, jbuf);

	if (off < 0 || len < 0 || len+off > alen) {
		throwIllegalArgumentsExc(env, "offset+lengths");
		return -1;
	}

	void* data = (*env)->GetByteArrayElements(env, jbuf, NULL);
	if (data == NULL) {
		throwOOM(env, "GetByteArrayElements");
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

		switch(err) {
			#if EAGAIN != EWOULDBLOCK
			case(EWOULDBLOCK):
			#endif
			case(EAGAIN):
				return 0;
			case(EBADF):
				badFileDescriptor(env);
				return -1;
			case EINVAL:
				throwIllegalArgumentsExc(env, "file descriptor is unsuitable for reading or buffer size does not match the required buffer size");
				return -1;
			case EIO:
				throwIOExc(env, "I/O error");
				return -1;
			case EISDIR:
				throwIllegalArgumentsExc(env, "file descriptor refers to a directory");
				return -1;
			default:
				unknownError(env, err);
				return -1;
		}
	}

}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    write
 * Signature: (I[BII)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_write
  (JNIEnv * env, jobject inst, jint fd, jbyteArray jbuf, jint off, jint len) {
	if (jbuf == NULL) {
		throwNullPointerException(env, "buffer");
		return -1;
	}

	jsize alen = (*env)->GetArrayLength(env, jbuf);

	if (off < 0 || len < 0 || len+off > alen) {
		throwIllegalArgumentsExc(env, "offset+lengths");
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

		switch(err) {
			case(EINTR):
				continue;
			#if EAGAIN != EWOULDBLOCK
			case(EWOULDBLOCK):
			#endif
			case(EAGAIN):
				return 0;
			case(EBADF):
				badFileDescriptor(env);
				return -1;
			case(EDESTADDRREQ):
				throwIllegalStateException(env, "file descriptor refers to a datagram socket for which a peer address has not been set using connect.");
				return -1;
			case(EDQUOT):
				throwQuotaExceededException(env, NULL, NULL, "The user's quota of disk blocks on the filesystem containing the file referred to by the file descriptor has been exhausted.");
				return -1;
			case(EFBIG):
				throwIOExc(env, "An attempt was made to write a file that exceeds the implementation-defined maximum file size or the process's file size limit, or to write at a position past the maximum allowed offset.");
				return -1;
			case EINVAL:
				throwIllegalArgumentsExc(env, "file descriptor is unsuitable for writing or the file/buffer position/length is not properly aligned.");
				return -1;
			case EIO:
				throwIOExc(env, "I/O error");
				return -1;
			case EPERM:
				throwFSAccessDenied(env, NULL, NULL, "Operation was prevented by a file seal");
				return -1;
			case EPIPE:
				throwIOExc(env, "Broken pipe");
				return -1;
			case ENOSPC:
				throwIOExc(env, "The device containing the file referred to by fd has no room for the data.");
				return -1;
			case EISDIR:
				throwIllegalArgumentsExc(env, "file descriptor refers to a directory");
				return -1;
			default:
				unknownError(env, err);
				return -1;
		}
	}

}

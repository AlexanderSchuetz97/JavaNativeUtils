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
#include <netinet/in.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <endian.h>
#include <stdlib.h>
#include <string.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    socket
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_socket
  (JNIEnv * env, jobject inst, jint domain, jint type, jint protocol) {
	int fd = socket(domain, type, protocol);

	if (fd == -1) {
		int err = errno;

		switch(err) {
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "Invalid flags in type or unknown protocol or protocol family not available.");
			return -1;
		case(EAFNOSUPPORT):
			jthrowCC_UnsupportedOperationException_1(env, "The implementation does not support the specified address family.");
			return -1;
		case (EPROTONOSUPPORT):
			jthrowCC_UnsupportedOperationException_1(env, "The protocol type or the specified protocol is not supported within this domain.");
			return -1;
		case (EACCES):
			jthrowCC_AccessDeniedException_1(env, NULL, NULL, "Permission to create a socket of the specified type and/or protocol is denied.");
			return -1;
		case (EMFILE):
			jthrowCC_QuotaExceededException_1(env, NULL, NULL, "The per-process limit on the number of open file descriptors has been reached.");
			return -1;
		case (ENFILE):
			jthrowCC_QuotaExceededException_1(env, NULL, NULL, "The system-wide limit on the total number of open files has been reached.");
			return -1;
		case (ENOBUFS):
		case (ENOMEM):
			jthrowCC_OutOfMemoryError_1(env, "Insufficient memory is available. The socket cannot be created until sufficient resources are freed.");
			return -1;
		default:
			jthrow_UnknownNativeErrorException_1(env, err);
			return -1;
		}
	}

	return fd;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    bind
 * Signature: (ILeu/aschuetz/nativeutils/api/structs/Sockaddr;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_bind
  (JNIEnv * env, jobject inst, jint fd, jobject jaddrobj) {
	if (jaddrobj == NULL) {
			jthrowCC_NullPointerException_1(env, "address is null");
			return;
		}

		jbyteArray jaddr = (jbyteArray) jget_Sockaddr_address(env, jaddrobj);

		if (jaddr == NULL) {
			jthrowCC_NullPointerException_1(env, "address.address is null");
			return;
		}


		socklen_t size = (socklen_t) (*env)->GetArrayLength(env, jaddr);

		struct sockaddr * addr = (struct sockaddr *) (*env)->GetByteArrayElements(env, jaddr, NULL);
		if (addr == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
			return;
		}

		while(true) {

			int result = bind((int) fd,  (const struct sockaddr *) addr, size);

			if (result != -1) {
				(*env)->ReleaseByteArrayElements(env, jaddr, (jbyte*) addr, JNI_ABORT);
				return;
			}

			int err = errno;

			if (size >= sizeof(sa_family_t) && addr->sa_family == AF_UNIX) {
				switch(err) {
					case(EBADF):
						jthrow_InvalidFileDescriptorException(env);
						break;
					case(ENOTSOCK):
						jthrowCC_IllegalArgumentException_1(env, "file descriptor does not refer to a socket");
						break;
					case(EACCES):
						jthrowCC_AccessDeniedException_1(env, NULL, NULL, "Search permission is denied on a component of the path prefix.");
						break;
					case(EADDRNOTAVAIL):
						jthrowCC_BindException_1(env, "A nonexistent interface was requested or the requested address was not local.");
						break;
					case(ELOOP):
						jthrowCC_FileSystemLoopException(env, "socket address");
						break;
					case(ENAMETOOLONG):
						jthrowCC_InvalidPathException(env, "socket address", "addr is too long");
						break;
					case(ENOENT):
						jthrowCC_FileNotFoundException_1(env, "A component in the directory prefix of the socket pathname does not exist.");
						break;
					case(ENOMEM):
						jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available.");
						break;
					case(ENOTDIR):
						jthrowCC_NotDirectoryException(env, "A component of the path prefix is not a directory.");
						break;
					case(EROFS):
						jthrow_ReadOnlyFileSystemException(env);
						break;
					case(EINTR):
						continue;
					default:
						jthrow_UnknownNativeErrorException_1(env, err);
						break;
				}
				goto cleanup;
			}

			switch(err) {
				case(EBADF):
					jthrow_InvalidFileDescriptorException(env);
					break;
				case(ENOTSOCK):
					jthrowCC_IllegalArgumentException_1(env, "file descriptor does not refer to a socket");
					break;
				case(EACCES):
					jthrowCC_AccessDeniedException_1(env, NULL, NULL, "The address is protected, and the user is not the superuser.");
					break;
				case(EADDRINUSE):
					jthrowCC_BindException_1(env, "could not bind local address because it is in use.");
					break;
				case(EINTR):
					continue;
				default:
					jthrow_UnknownNativeErrorException_1(env, err);
					break;
			}


			cleanup:
			(*env)->ReleaseByteArrayElements(env, jaddr, (jbyte*) addr, JNI_ABORT);
			return;
		}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    connect
 * Signature: (ILeu/aschuetz/nativeutils/api/structs/Sockaddr;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_connect
  (JNIEnv * env, jobject inst, jint  fd, jobject jaddrobj) {
	if (jaddrobj == NULL) {
		jthrowCC_NullPointerException_1(env, "address is null");
		return;
	}

	jbyteArray jaddr = (jbyteArray) jget_Sockaddr_address(env, jaddrobj);

	if (jaddr == NULL) {
		jthrowCC_NullPointerException_1(env, "address.address is null");
		return;
	}


	socklen_t size = (socklen_t) (*env)->GetArrayLength(env, jaddr);

	struct sockaddr * addr = (struct sockaddr *) (*env)->GetByteArrayElements(env, jaddr, NULL);
	if (addr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return;
	}

	while(true) {

		int result = connect((int) fd,  (const struct sockaddr *) addr, size);

		if (result != -1) {
			(*env)->ReleaseByteArrayElements(env, jaddr, (jbyte*) addr, JNI_ABORT);
			return;
		}

		int err = errno;

		switch(err) {
			case(EPERM):
			case(EACCES):
				jthrowCC_AccessDeniedException_1(env, NULL, NULL, "Permission denied due to either missing broadcast flag, local firewall rule, or SELinux policy.");
				break;
			case(EADDRINUSE):
				jthrowCC_BindException_1(env, "could not bind local address because it is in use.");
				break;
			case(EADDRNOTAVAIL):
				jthrowCC_BindException_1(env, "could not bind local address because no free port is available.");
				break;
			case(EAFNOSUPPORT):
				jthrowCC_IllegalArgumentException_1(env, "sa_family field in address was not valid");
				break;
			case(EAGAIN):
				jthrowC_IOException_1(env, "the connection cannot be established immediately.");
				break;
			case(EALREADY):
				jthrowC_IOException_1(env, "previous connection attempt has not yet been completed.");
				break;
			case (EBADF):
				jthrow_InvalidFileDescriptorException(env);
				break;
			case(ECONNREFUSED):
				jthrowCC_ConnectException_1(env, "connection refused.");
				break;
			case(EINPROGRESS):
				jthrowCC_OperationInProgressException_1(env, "connect");
				break;
			case(EINTR):
				continue;
			case(EISCONN):
				jthrowCC_ConnectException_1(env, "the socket is already connected");
				break;
			case(ENETUNREACH):
				jthrowCC_ConnectException_1(env, "Network is unreachable.");
				break;
			case(ENOTSOCK):
				jthrowCC_IllegalArgumentException_1(env, "file descriptor does not refer to a socket");
				break;
			case(EPROTOTYPE):
				jthrowC_IOException_1(env, "The socket type does not support the requested communications protocol.");
				break;
			case(ETIMEDOUT):
				jthrowCC_ConnectException_1(env, "Connection timed out.");
				break;
			default:
				jthrow_UnknownNativeErrorException_1(env, err);
				break;
		}

		(*env)->ReleaseByteArrayElements(env, jaddr, (jbyte*) addr, JNI_ABORT);
		return;
	}
}

void handleSockOptError(JNIEnv * env) {
	int err = errno;
	switch (err) {
		case EINVAL:
			jthrowCC_IllegalArgumentException_1(env, "payload length or payload content is invalid");
			return;
		case ENOPROTOOPT:
			jthrowCC_UnsupportedOperationException_1(env, "The option is unknown at the level indicated.");
			return;
		case ENOTSOCK:
		case EBADF:
			jthrow_InvalidFileDescriptorException(env);
			return;
		default:
			jthrow_UnknownNativeErrorException_1(env, err);
			return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getsockopt
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_getsockopt__III
  (JNIEnv * env, jobject inst, jint fd, jint level, jint option) {
	uint32_t result = 0;
	socklen_t len = sizeof(uint32_t);


	int succ = getsockopt((int) fd, (int) level, (int) option, &result, &len);
	if (succ != -1) {
		return result;
	}

	handleSockOptError(env);
	return -1;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getsockopt
 * Signature: (IIII)[B
 */
JNIEXPORT jbyteArray JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_getsockopt__IIII
  (JNIEnv *env, jobject inst, jint fd, jint level, jint option, jint jlen) {
	if (jlen <= 0) {
		jthrowCC_IllegalArgumentException_1(env, "len <= 0");
		return NULL;
	}

	char buf[jlen];
	socklen_t len = jlen;

	int succ = getsockopt((int) fd, (int) level, (int) option, buf, &len);

	if (succ == -1) {
		handleSockOptError(env);
		return NULL;
	}

	jbyteArray array = (*env)->NewByteArray(env, len);
	if (array == NULL) {
		return NULL;
	}

	jbyte* data = (*env)->GetByteArrayElements(env, array, NULL);
	if (data == NULL) {
		(*env)->DeleteLocalRef(env, array);
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return NULL;
	}

	memcpy(data, buf, len);

	(*env)->ReleaseByteArrayElements(env, array, data, JNI_OK);
	return array;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    setsockopt
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_setsockopt__IIII
	(JNIEnv *env, jobject inst, jint fd, jint level, jint option, jint value) {

	uint32_t uvalue = value;

	int succ = setsockopt((int) fd, (int) level, (int) option, &uvalue, sizeof(uint32_t));
	if (succ != -1) {
		return;
	}

	handleSockOptError(env);
	return;

}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    setsockopt
 * Signature: (III[B)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_setsockopt__III_3B
  (JNIEnv * env, jobject inst, jint fd, jint level, jint option, jbyteArray value) {
	if (value == NULL) {
		jthrowCC_IllegalArgumentException_1(env, "value is null");
		return;
	}

	jsize len = (*env)->GetArrayLength(env, value);
	if (len <= 0) {
		jthrowCC_IllegalArgumentException_1(env, "GetArrayLength return 0 or negative value for value array");
		return;
	}

	jbyte* data = (*env)->GetByteArrayElements(env, value, NULL);
	if (data == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return;
	}

	int succ = setsockopt((int) fd, (int) level, (int) option, data, (socklen_t) len);
	if (succ != -1) {
		(*env)->ReleaseByteArrayElements(env, value, data, JNI_OK);
		return;
	}

	handleSockOptError(env);
	(*env)->ReleaseByteArrayElements(env, value, data, JNI_ABORT);
	return;
}

#define ADDRESS_BUFSIZE 512

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    recvfrom
 * Signature: (I[BIIILeu/aschuetz/nativeutils/api/structs/Sockaddr;)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_recvfrom
  (JNIEnv *env, jobject inst, jint fd, jbyteArray jbuf, jint off, jint len, jint flags, jobject address) {
	if (jbuf == NULL) {
		jthrowCC_NullPointerException_1(env, "buffer");
		return -1;
	}

	jsize alen = (*env)->GetArrayLength(env, jbuf);

	if (off < 0 || len < 0 || len+off > alen) {
		jthrowCC_IllegalArgumentException_1(env, "offset+lengths");
		return -1;
	}



	void * tmpPtr = NULL;
	socklen_t tmpSize = 0;


	if (address != NULL) {
		tmpPtr = malloc(ADDRESS_BUFSIZE);
		if (tmpPtr == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			return -1;
		}
	}

	void* data = (*env)->GetByteArrayElements(env, jbuf, NULL);
	if (data == NULL) {
		free(tmpPtr);
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return -1;
	}

	while(true) {

		if (tmpPtr != NULL) {
			tmpSize = ADDRESS_BUFSIZE;
		}

		size_t r = recvfrom(fd, data+off, len, (int) flags, tmpPtr, &tmpSize);

		if (r != -1 && tmpPtr != NULL) {
			struct sockaddr * sockPtr = (struct sockaddr *) tmpPtr;

			jbyteArray existing = jget_Sockaddr_address(env, address);
			if (existing == NULL || (*env)->GetArrayLength(env, existing) != tmpSize) {

				if (existing != NULL) {
					(*env)->DeleteLocalRef(env, existing);
				}

				existing = (*env)->NewByteArray(env, tmpSize);
				if (existing == NULL) {
					free(tmpPtr);
					(*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_ABORT);
					jthrowCC_OutOfMemoryError_1(env, "NewByteArray");
					return -1;
				}

				jset_Sockaddr_address(env, address, existing);
			}

			jset_Sockaddr_addressFamily(env, address,  tmpSize != 0 ? ((jint) sockPtr->sa_family) : -1);

			jbyte* jdata = (*env)->GetByteArrayElements(env, existing, NULL);

			if (jdata == NULL) {
				free(tmpPtr);
				(*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_ABORT);
				(*env)->DeleteLocalRef(env, existing);
				jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
				return -1;

			}

			memcpy(jdata, sockPtr, tmpSize);

			(*env)->ReleaseByteArrayElements(env, existing, jdata, JNI_OK);
			(*env)->DeleteLocalRef(env, existing);
			free(tmpPtr);
		}

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
		free(tmpPtr);

		switch(err) {
			#if EAGAIN != EWOULDBLOCK
			case(EWOULDBLOCK):
			#endif
			case(EAGAIN):
				return 0;
			case (ENOTCONN):
				jthrowC_IOException_1(env, "socket is not connected");
				return -1;
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
			case(ENOTSOCK):
				jthrowCC_IllegalArgumentException_1(env, "file descriptor does not refer to a socket");
				break;
			default:
				jthrow_UnknownNativeErrorException_1(env, err);
				return -1;
		}
	}
}

void handle_getsockname_error(JNIEnv * env, int err) {
	switch(err) {
		case(EBADF):
			jthrow_InvalidFileDescriptorException(env);
			return;
		case(ENOTSOCK):
			jthrowCC_IllegalArgumentException_1(env, "The file descriptor does not refer to a socket.");
			return;
		case(ENOBUFS):
			jthrowCC_OutOfMemoryError_1(env, "Insufficient resources were available in the system to perform the operation.");
			return;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getsockname
 * Signature: (ILeu/aschuetz/nativeutils/api/structs/Sockaddr;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_getsockname
  (JNIEnv * env, jobject inst, jint fd, jobject jaddrobj) {
	if (jaddrobj == NULL) {
		jthrowCC_NullPointerException_1(env, "address");
		return;
	}

	jbyteArray jaddr = jget_Sockaddr_address(env, jaddrobj);

	if (jaddr == NULL) {
		jthrowCC_NullPointerException_1(env, "address.address is null");
		return;
	}


	char dummy[1];

	socklen_t len = 0;
	int res = getsockname(fd, (struct sockaddr*) dummy, &len);
	if (res == -1) {
		handle_getsockname_error(env, errno);
		return;
	}

	if ((*env)->GetArrayLength(env, jaddr) != len) {
		(*env)->DeleteLocalRef(env, jaddr);
		jaddr = (*env)->NewByteArray(env, len);
		if (jaddr == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "NewByteArray");
			return;
		}

		jset_Sockaddr_address(env, jaddrobj, jaddr);
	}

	struct sockaddr * addr = (struct sockaddr *) (*env)->GetByteArrayElements(env, jaddr, NULL);
	if (addr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return;
	}

	socklen_t nlen = len;
	res = getsockname(fd, addr, &nlen);
	if (res == -1) {
		(*env)->ReleaseByteArrayElements(env, jaddr, (jbyte*) addr, JNI_ABORT);
		handle_getsockname_error(env, errno);
		return;
	}

	jset_Sockaddr_addressFamily(env, jaddrobj, addr->sa_family);
	(*env)->ReleaseByteArrayElements(env, jaddr, (jbyte*) addr, JNI_OK);
}





jint handle_msg (JNIEnv * env, jobject inst, jint fd, jobject msghdr, jint flags, bool isRead) {

	if (msghdr == NULL) {
		jthrowCC_NullPointerException_1(env, "msghdr");
		return -1;
	}



	jobjectArray iovecs = jget_Msghdr_msg_iov(env, msghdr);
	if (iovecs == NULL) {
		jthrowCC_NullPointerException_1(env, "msghdr.msg_iov");
		return -1;
	}

	struct c_jiov {
		jobject jiov;
		jbyteArray jbytes;
		jbyte * ptr;
		jint off;
		jint len;
	};


	jsize ioveclen = (*env)->GetArrayLength(env, iovecs);
	if (ioveclen > 128) {
		(*env)->DeleteLocalRef(env, iovecs);
		jthrowCC_IllegalArgumentException_1(env, "too many iovs");
		return -1;
	}

	//Setup C<->J iovec buffers
	struct c_jiov iovecObjs[ioveclen];

	for (jsize i = 0; i < ioveclen; i++) {
		iovecObjs[i].jiov = (*env)->GetObjectArrayElement(env, iovecs, i);
		if (iovecObjs[i].jiov == NULL) {
			for (int j = 0; j < i; j++) {
				(*env)->ReleaseByteArrayElements(env, iovecObjs[j].jbytes, iovecObjs[j].ptr, JNI_ABORT);
				(*env)->DeleteLocalRef(env, iovecObjs[j].jbytes);
				(*env)->DeleteLocalRef(env, iovecObjs[j].jiov);
			}

			(*env)->DeleteLocalRef(env, iovecs);
			jthrowCC_NullPointerException_1(env, "msghdr.msg_iov[?]");
			return -1;
		}


		iovecObjs[i].jbytes = jget_Iovec_payload(env, iovecObjs[i].jiov);
		iovecObjs[i].len = jget_Iovec_len(env, iovecObjs[i].jiov);
		iovecObjs[i].off = jget_Iovec_off(env, iovecObjs[i].jiov);

		if (iovecObjs[i].jbytes == NULL) {
			jthrowCC_NullPointerException_1(env, "msghdr.msg_iov[?].payload");
			for (int j = 0; j < i; j++) {
				(*env)->ReleaseByteArrayElements(env, iovecObjs[j].jbytes, iovecObjs[j].ptr, JNI_ABORT);
				(*env)->DeleteLocalRef(env, iovecObjs[j].jbytes);
				(*env)->DeleteLocalRef(env, iovecObjs[j].jiov);
			}

			(*env)->DeleteLocalRef(env, iovecObjs[i].jiov);
			(*env)->DeleteLocalRef(env, iovecs);
			return -1;
		}

		jsize len = (*env)->GetArrayLength(env, iovecObjs[i].jbytes);
		if (iovecObjs[i].len < 0 || iovecObjs[i].off < 0 || iovecObjs[i].len + iovecObjs[i].off > len) {

			for (int j = 0; j < i; j++) {
				(*env)->ReleaseByteArrayElements(env, iovecObjs[j].jbytes, iovecObjs[j].ptr, JNI_ABORT);
				(*env)->DeleteLocalRef(env, iovecObjs[j].jbytes);
				(*env)->DeleteLocalRef(env, iovecObjs[j].jiov);
			}

			(*env)->DeleteLocalRef(env, iovecObjs[i].jiov);
			(*env)->DeleteLocalRef(env, iovecObjs[i].jbytes);
			(*env)->DeleteLocalRef(env, iovecs);

			jthrowCC_IllegalArgumentException_1(env, "msghdr.msg_iov[?].payload offset/len are invalid");
			return -1;
		}

		iovecObjs[i].ptr = (*env)->GetByteArrayElements(env, iovecObjs[i].jbytes, NULL);

		if (iovecObjs[i].ptr == NULL) {
			for (int j = 0; j < i; j++) {
				(*env)->ReleaseByteArrayElements(env, iovecObjs[j].jbytes, iovecObjs[j].ptr, JNI_ABORT);
				(*env)->DeleteLocalRef(env, iovecObjs[j].jbytes);
				(*env)->DeleteLocalRef(env, iovecObjs[j].jiov);
			}

			(*env)->DeleteLocalRef(env, iovecObjs[i].jiov);
			(*env)->DeleteLocalRef(env, iovecObjs[i].jbytes);
			(*env)->DeleteLocalRef(env, iovecs);

			jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
			return -1;
		}
	}

	//We no longer need a ref to the iovec array
	(*env)->DeleteLocalRef(env, iovecs);
	iovecs = NULL;

	struct iovec iov[ioveclen];

	for (int j = 0; j < ioveclen; j++) {
		iov[j].iov_base = (void*) (iovecObjs[j].ptr + iovecObjs[j].off);
		iov[j].iov_len = iovecObjs[j].len;
	}

	//IOV is now setup now other fields....


	jobject jaddr = jget_Msghdr_msg_name(env, msghdr);
	jbyteArray jcontrol =  jget_Msghdr_msg_control(env, msghdr);



	char addrBuf[jaddr == NULL ? 0 : ADDRESS_BUFSIZE];



	struct msghdr msg;
	memset(&msg, 0, sizeof(msg));
	msg.msg_name = jaddr == NULL ? NULL : addrBuf;
	msg.msg_namelen = jaddr == NULL ? 0 : ADDRESS_BUFSIZE;
	if (!isRead && jaddr != NULL) {
		jbyteArray addr = (jbyteArray) jget_Sockaddr_address(env, jaddr);
		if (addr != NULL) {
			jsize len = (*env)->GetArrayLength(env, addr);
			if (len > ADDRESS_BUFSIZE) {
				//WILL EINVAL I dont care yet.
				len = ADDRESS_BUFSIZE;
			}

			(*env)->GetByteArrayRegion(env, addr, 0, len, (jbyte*) addrBuf);
			(*env)->DeleteLocalRef(env, addr);
			msg.msg_namelen = len;
		}
	}

	msg.msg_iov = iov;
	msg.msg_iovlen = ioveclen;

	if (jcontrol != NULL) {
		msg.msg_control = (void*) (*env)->GetByteArrayElements(env, jcontrol, NULL);
		if (msg.msg_control == NULL) {
			if (jaddr != NULL) {
				(*env)->DeleteLocalRef(env, jaddr);
			}

			for (int j = 0; j < ioveclen; j++) {
				(*env)->ReleaseByteArrayElements(env, iovecObjs[j].jbytes, iovecObjs[j].ptr, JNI_ABORT);
				(*env)->DeleteLocalRef(env, iovecObjs[j].jbytes);
				(*env)->DeleteLocalRef(env, iovecObjs[j].jiov);
			}

			jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
			return -1;
		}
		msg.msg_controllen = (*env)->GetArrayLength(env, jcontrol);
	}



	int ret;
	int err;
	while(true) {
		ret = isRead ? recvmsg(fd, &msg, flags) : sendmsg(fd, (const struct msghdr *) &msg, flags);

		err = 0;

		if (ret == -1) {
			err = errno;
			if (err == EINTR) {
				continue;
			}
		}

		break;
	}

	if (isRead) {
		jset_Msghdr_complete(env, msghdr, (msg.msg_flags & MSG_EOR) == MSG_EOR);
		jset_Msghdr_truncated(env, msghdr, (msg.msg_flags & MSG_TRUNC) == MSG_TRUNC);
		jset_Msghdr_controlDataTruncated(env, msghdr, (msg.msg_flags & MSG_CTRUNC) == MSG_CTRUNC);
		jset_Msghdr_outOfBand(env, msghdr, (msg.msg_flags & MSG_OOB) == MSG_OOB);
		jset_Msghdr_errQueue(env, msghdr, (msg.msg_flags & MSG_ERRQUEUE) == MSG_ERRQUEUE);
	}

	for (int j = 0; j < ioveclen; j++) {
		(*env)->ReleaseByteArrayElements(env, iovecObjs[j].jbytes, iovecObjs[j].ptr, isRead ? JNI_OK : JNI_ABORT);
		(*env)->DeleteLocalRef(env, iovecObjs[j].jbytes);
		if (isRead) {
			jset_Iovec_size(env, iovecObjs[j].jiov, iov[j].iov_len);
		}
		(*env)->DeleteLocalRef(env, iovecObjs[j].jiov);
	}

	if (jcontrol != NULL) {
		(*env)->ReleaseByteArrayElements(env, jcontrol, msg.msg_control, isRead ? JNI_OK : JNI_ABORT);
		(*env)->DeleteLocalRef(env, jcontrol);
	}

	if (isRead) {
		jset_Msghdr_msg_controllen(env, msghdr, (jint) msg.msg_controllen);
		if (ret != -1 && jaddr != NULL) {
			jbyteArray addr = jget_Sockaddr_address(env, jaddr);
			if (addr == NULL || (*env)->GetArrayLength(env, addr) != msg.msg_namelen) {
				if (addr != NULL) {
					(*env)->DeleteLocalRef(env, addr);
				}

				addr = (*env)->NewByteArray(env, msg.msg_namelen);
				if (addr == NULL) {
					jthrowCC_OutOfMemoryError_1(env, "NewByteArray");
					(*env)->DeleteLocalRef(env, jaddr);
					return -1;
				}

				jset_Sockaddr_address(env, jaddr, addr);
			}

			jbyte* ptr = (*env)->GetByteArrayElements(env, addr, NULL);
			if (ptr == NULL) {

				(*env)->DeleteLocalRef(env, jaddr);
				(*env)->DeleteLocalRef(env, addr);
				jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
				return -1;
			}

			memcpy(ptr, msg.msg_name, msg.msg_namelen);
			(*env)->ReleaseByteArrayElements(env, addr, ptr, JNI_OK);
			jint af = -1;
			if (msg.msg_namelen > 0) {
				af = ((struct sockaddr *) msg.msg_name)->sa_family;
			}

			jset_Sockaddr_addressFamily(env, jaddr, af);
			(*env)->DeleteLocalRef(env, addr);
			(*env)->DeleteLocalRef(env, jaddr);
		}
	}

	if (ret == 0) {
		return -1;
	}

	if (ret != -1) {
		return ret;
	}

	switch(err) {
		#if EAGAIN != EWOULDBLOCK
		case(EWOULDBLOCK):
		#endif
		case(EAGAIN):
			return 0;
		case(EBADF):
			jthrow_InvalidFileDescriptorException(env);
			return -1;
		case(EINVAL):
			jthrowCC_IllegalArgumentException_1(env, "EINVAL");
			return -1;
		case (ENOMEM):
			jthrowCC_OutOfMemoryError_1(env, "recvmsg");
			return -1;
		case (ENOTCONN):
			jthrowCC_IOException_1(env, "socket is not connected");
			return -1;
		case EIO:
			jthrowCC_IOException_1(env, "I/O error");
			return -1;
		case (ECONNREFUSED):
			jthrowCC_ConnectException_1(env, "connection refused.");
		return -1;
		case(ENOTSOCK):
			jthrowCC_IllegalArgumentException_1(env, "file descriptor does not refer to a socket");
		return -1;
		default:
			jthrow_UnknownNativeErrorException_1(env, err);
			return -1;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    sendmsg
 * Signature: (ILeu/aschuetz/nativeutils/api/structs/Msghdr;I)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_sendmsg
	(JNIEnv * env, jobject inst, jint fd, jobject msghdr, jint flags) {
	return handle_msg(env, inst, fd, msghdr, flags, false);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    recvmsg
 * Signature: (ILeu/aschuetz/nativeutils/api/structs/Msghdr;I)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_recvmsg
  (JNIEnv * env, jobject inst, jint fd, jobject msghdr, jint flags) {
	return handle_msg(env, inst, fd, msghdr, flags, true);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    parseCMSG_HDR
 * Signature: ([BI)Ljava/util/Collection;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil_parseCMSG_1HDR
  (JNIEnv * env, jobject inst, jbyteArray hdr, jint len) {

	if (hdr == NULL) {
		jthrowCC_NullPointerException_1(env, "msg_control");
		return NULL;
	}

	if (len < 0) {
		jthrowCC_IllegalArgumentException_1(env, "msg_controllen < 0");
		return NULL;
	}

	if ((*env)->GetArrayLength(env, hdr) < len) {
		jthrowCC_IllegalArgumentException_1(env, "msg_controllen > msg_control.lenght");
		return NULL;
	}

	jobject resultList  = jnew_ArrayList(env);
	if (resultList == NULL) {
		return NULL;
	}

	jbyte* buf = (*env)->GetByteArrayElements(env, hdr, NULL);
	if (buf == NULL) {
		(*env)->DeleteLocalRef(env, resultList);
		jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
		return NULL;
	}




	struct msghdr msg;
	memset(&msg, 0, sizeof(msg));
	msg.msg_control = buf;
	msg.msg_controllen = len;




	struct cmsghdr *cmsg;
	for (cmsg = CMSG_FIRSTHDR(&msg); cmsg; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
		size_t dlen = cmsg->cmsg_len - CMSG_LEN(0);
		if (dlen < 0) {
			continue;
		}

		jobject jhdr = jnew_Cmsghdr(env);

		if (jerr(env)) {
			(*env)->DeleteLocalRef(env, resultList);
			return NULL;
		}

		jbyteArray bytes = (*env)->NewByteArray(env, (jsize) dlen);

		if (bytes == NULL) {
			(*env)->DeleteLocalRef(env, resultList);
			(*env)->DeleteLocalRef(env, jhdr);
			jthrowCC_OutOfMemoryError_1(env, "NewByteArray");
			return NULL;
		}

		jbyte * nbuf = (*env)->GetByteArrayElements(env, bytes, NULL);

		if (nbuf == NULL) {
			(*env)->DeleteLocalRef(env, resultList);
			(*env)->DeleteLocalRef(env, jhdr);
			(*env)->DeleteLocalRef(env, bytes);
			jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
			return NULL;
		}

		memcpy(nbuf, CMSG_DATA(cmsg), dlen);

		(*env)->ReleaseByteArrayElements(env, bytes, nbuf, JNI_OK);

		jset_Cmsghdr_payload(env, jhdr, bytes);
		(*env)->DeleteLocalRef(env, bytes);
		jset_Cmsghdr_cmsg_level(env, jhdr, cmsg->cmsg_level);
		jset_Cmsghdr_cmsg_type(env, jhdr, cmsg->cmsg_type);
		jcall_Collection_add(env, resultList, jhdr);
		(*env)->DeleteLocalRef(env, jhdr);
	}

	return resultList;
}





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
#include <netinet/in.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <endian.h>
#include <stdlib.h>

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    socket
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_socket
  (JNIEnv * env, jobject inst, jint domain, jint type, jint protocol) {
	int fd = socket(domain, type, protocol);

	if (fd == -1) {
		int err = errno;

		switch(err) {
		case(EINVAL):
			throwIllegalArgumentsExc(env, "Invalid flags in type or unknown protocol or protocol family not available.");
			return -1;
		case(EAFNOSUPPORT):
			throwUnsupportedExc(env, "The implementation does not support the specified address family.");
			return -1;
		case (EPROTONOSUPPORT):
			throwUnsupportedExc(env, "The protocol type or the specified protocol is not supported within this domain.");
			return -1;
		case (EACCES):
			throwFSAccessDenied(env, NULL, NULL, "Permission to create a socket of the specified type and/or protocol is denied.");
			return -1;
		case (EMFILE):
			throwQuotaExceededException(env, NULL, NULL, "The per-process limit on the number of open file descriptors has been reached.");
			return -1;
		case (ENFILE):
			throwQuotaExceededException(env, NULL, NULL, "The system-wide limit on the total number of open files has been reached.");
			return -1;
		case (ENOBUFS):
		case (ENOMEM):
			throwOOM(env, "Insufficient memory is available. The socket cannot be created until sufficient resources are freed.");
			return -1;
		default:
			unknownError(env, err);
			return -1;
		}
	}

	return fd;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    connect
 * Signature: (ILio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_connect
  (JNIEnv * env, jobject inst, jint  fd, jobject jaddrobj) {
	if (jaddrobj == NULL) {
		throwNullPointerException(env, "address is null");
		return;
	}

	jbyteArray jaddr = (jbyteArray) (*env)->GetObjectField(env, jaddrobj, Sockaddr_address);

	if (jaddr == NULL) {
		throwNullPointerException(env, "address.address is null");
		return;
	}


	socklen_t size = (socklen_t) (*env)->GetArrayLength(env, jaddr);

	struct sockaddr * addr = (struct sockaddr *) (*env)->GetByteArrayElements(env, jaddr, NULL);
	if (addr == NULL) {
		throwOOM(env, "GetByteArrayElements");
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
				throwFSAccessDenied(env, NULL, NULL, "Permission denied due to either missing broadcast flag, local firewall rule, or SELinux policy.");
				break;
			case(EADDRINUSE):
				throwBindException(env, "could not bind local address because it is in use.");
				break;
			case(EADDRNOTAVAIL):
				throwBindException(env, "could not bind local address because no free port is available.");
				break;
			case(EAFNOSUPPORT):
				throwIllegalArgumentsExc(env, "sa_family field in address was not valid");
				break;
			case(EAGAIN):
				throwIOExc(env, "the connection cannot be established immediately.");
				break;
			case(EALREADY):
				throwIOExc(env, "previous connection attempt has not yet been completed.");
				break;
			case (EBADF):
				badFileDescriptor(env);
				break;
			case(ECONNREFUSED):
				throwConnectException(env, "connection refused.");
				break;
			case(EINPROGRESS):
				throwOperationInProgressException(env, "connect");
				break;
			case(EINTR):
				continue;
			case(EISCONN):
				throwConnectException(env, "the socket is already connected");
				break;
			case(ENETUNREACH):
				throwConnectException(env, "Network is unreachable.");
				break;
			case(ENOTSOCK):
				throwIllegalArgumentsExc(env, "file descriptor does not refer to a socket");
				break;
			case(EPROTOTYPE):
				throwIOExc(env, "The socket type does not support the requested communications protocol.");
				break;
			case(ETIMEDOUT):
				throwConnectException(env, "Connection timed out.");
				break;
			default:
				unknownError(env, err);
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
			throwIllegalArgumentsExc(env, "payload length or payload content is invalid");
			return;
		case ENOPROTOOPT:
			throwUnsupportedExc(env, "The option is unknown at the level indicated.");
			return;
		case ENOTSOCK:
		case EBADF:
			badFileDescriptor(env);
			return;
		default:
			unknownError(env, err);
			return;
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getsockopt
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_getsockopt__III
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getsockopt
 * Signature: (IIII)[B
 */
JNIEXPORT jbyteArray JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_getsockopt__IIII
  (JNIEnv *env, jobject inst, jint fd, jint level, jint option, jint jlen) {
	if (jlen <= 0) {
		throwIllegalArgumentsExc(env, "len <= 0");
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
		throwOOM(env, "GetByteArrayElements");
		return NULL;
	}

	memcpy(data, buf, len);

	(*env)->ReleaseByteArrayElements(env, array, data, JNI_OK);
	return array;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    setsockopt
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_setsockopt__IIII
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
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    setsockopt
 * Signature: (III[B)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_setsockopt__III_3B
  (JNIEnv * env, jobject inst, jint fd, jint level, jint option, jbyteArray value) {
	if (value == NULL) {
		throwIllegalArgumentsExc(env, "value is null");
		return;
	}

	jsize len = (*env)->GetArrayLength(env, value);
	if (len <= 0) {
		throwIllegalArgumentsExc(env, "GetArrayLength return 0 or negative value for value array");
		return;
	}

	jbyte* data = (*env)->GetByteArrayElements(env, value, NULL);
	if (data == NULL) {
		throwOOM(env, "GetByteArrayElements");
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

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    recvfrom
 * Signature: (I[BIIILio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_recvfrom
  (JNIEnv *env, jobject inst, jint fd, jbyteArray jbuf, jint off, jint len, jint flags, jobject address) {
	if (jbuf == NULL) {
		throwNullPointerException(env, "buffer");
		return -1;
	}

	jsize alen = (*env)->GetArrayLength(env, jbuf);

	if (off < 0 || len < 0 || len+off > alen) {
		throwIllegalArgumentsExc(env, "offset+lengths");
		return -1;
	}



	void * tmpPtr = NULL;
	socklen_t tmpSize = 0;


	if (address != NULL) {
		tmpPtr = malloc(512);
		if (tmpPtr == NULL) {
			throwOOM(env, "malloc 512");
			return -1;
		}
	}

	void* data = (*env)->GetByteArrayElements(env, jbuf, NULL);
	if (data == NULL) {
		free(tmpPtr);
		throwOOM(env, "GetByteArrayElements");
		return -1;
	}

	while(true) {

		if (tmpPtr != NULL) {
			tmpSize = 512;
		}

		size_t r = recvfrom(fd, data+off, len, (int) flags, tmpPtr, &tmpSize);

		if (r != -1 && tmpPtr != NULL) {
			struct sockaddr * sockPtr = (struct sockaddr *) tmpPtr;

			jbyteArray existing = (*env)->GetObjectField(env, address, Sockaddr_address);
			if (existing == NULL || (*env)->GetArrayLength(env, existing) != tmpSize) {

				if (existing != NULL) {
					(*env)->DeleteLocalRef(env, existing);
				}

				existing = (*env)->NewByteArray(env, tmpSize);
				if (existing == NULL) {
					free(tmpPtr);
					(*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_ABORT);
					throwOOM(env, "NewByteArray");
					return -1;
				}

				(*env)->SetObjectField(env, address, Sockaddr_address, existing);
			}

			(*env)->SetIntField(env, address, Sockaddr_addressFamily, tmpSize != 0 ? ((jint) sockPtr->sa_family) : -1);

			jbyte* jdata = (*env)->GetByteArrayElements(env, existing, NULL);

			if (jdata == NULL) {
				free(tmpPtr);
				(*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_ABORT);
				(*env)->DeleteLocalRef(env, existing);
				throwOOM(env, "GetByteArrayElements");
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
				throwIOExc(env, "socket is not connected");
				return -1;
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


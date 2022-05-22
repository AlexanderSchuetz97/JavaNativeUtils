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

#include <stddef.h>
#include <sys/time.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <endian.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    to_struct_timeval
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_to_1struct_1timeval
  (JNIEnv * env, jobject inst, jlong value) {
	uint64_t uvalue = value;
	uint64_t millis = uvalue % 1000;

	struct timeval tv;
	tv.tv_sec = ((uvalue-millis) / 1000);
	tv.tv_usec = millis * 1000;

	jbyteArray array = (*env)->NewByteArray(env, sizeof(struct timeval));
	if (array == NULL) {
		return NULL;
	}

	(*env)->SetByteArrayRegion(env, array, 0, sizeof(struct timeval), (jbyte*) &tv);

	return array;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    from_struct_timeval
 * Signature: ([B)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_from_1struct_1timeval
  (JNIEnv * env, jobject inst, jbyteArray jtv) {
	if (jtv == NULL) {
		throwNullPointerException(env, "timeval is null");
		return 0;
	}

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	(*env)->GetByteArrayRegion(env, jtv, 0, sizeof(struct timeval), (jbyte*) &tv);
	//If byte array is too small or error occurs then GetByteArrayRegion
	//throws Exception and tv just contains 0.
	jlong res = tv.tv_sec;
	res *= 1000;
	res += tv.tv_usec / 1000;
	return res;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    to_sockaddr_in
 * Signature: (Ljava/net/InetSocketAddress;)Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_to_1sockaddr_1in
  (JNIEnv * env, jobject inst, jobject jaddr) {
	if (jaddr == NULL) {
		throwNullPointerException(env, "address");
		return NULL;
	}

	jobject jInetAddr = getAddressFromInetSocketAddress(env, jaddr);
	if (jInetAddr == NULL) {
		throwNullPointerException(env, "address.getAddress() returned null");
		return NULL;
	}

	jbyteArray jInetAddrBytes = getAddressFromInetAddress(env, jInetAddr);
	(*env)->DeleteLocalRef(env, jInetAddr);
	if (jInetAddrBytes == NULL) {
		throwNullPointerException(env, "address.getAddress().getAddress() returned null");
		return NULL;
	}

	jsize len = (*env)->GetArrayLength(env, jInetAddrBytes);
	if (len != 4 && len != 16) {
		throwIllegalArgumentsExc(env, "address.getAddress().getAddress() returned an array not of length 4 (Ipv4) or 16 (Ipv6)");
		return NULL;
	}

	jint port = getPortFromInetSocketAddress(env, jaddr);
	if (port < 0 || port > 0xffff) {
		throwIllegalArgumentsExc(env, "address.getPort() returned an invalid port number");
		return NULL;
	}

	jint af = 0;
	jbyteArray structArray = NULL;


	if (len == 4) {
		af = AF_INET;
		jbyte* bytes = (*env)->GetByteArrayElements(env, jInetAddrBytes, NULL);
		if (bytes == NULL) {
			throwOOM(env, "GetByteArrayElements");
			return NULL;
		}

		in_addr_t in = htonl((((in_addr_t)bytes[0]) << 24) + (((in_addr_t)bytes[1]) << 16) + (((in_addr_t)bytes[2]) << 8) + (((in_addr_t)bytes[3]) << 0));
		(*env)->ReleaseByteArrayElements(env, jInetAddrBytes, bytes, JNI_ABORT);


		structArray = (*env)->NewByteArray(env, sizeof(struct sockaddr_in));
		if (structArray == NULL) {
			return NULL;
		}

		struct sockaddr_in * ptr = (struct sockaddr_in *) (*env)->GetByteArrayElements(env, structArray, NULL);
		if (ptr == NULL) {
			(*env)->DeleteLocalRef(env, structArray);
			throwOOM(env, "GetByteArrayElements");
			return NULL;
		}

		memset(ptr, 0, sizeof(struct sockaddr_in));

		ptr->sin_family = AF_INET;
		ptr->sin_port = htons((uint16_t) port);
		ptr->sin_addr.s_addr = in;

		(*env)->ReleaseByteArrayElements(env, structArray, (jbyte*) ptr, JNI_OK);
	} else {
		af = AF_INET6;
		structArray = (*env)->NewByteArray(env, sizeof(struct sockaddr_in6));
		if (structArray == NULL) {
			return NULL;
		}

		struct sockaddr_in6 * ptr = (struct sockaddr_in6 *) (*env)->GetByteArrayElements(env, structArray, NULL);
		if (ptr == NULL) {
			(*env)->DeleteLocalRef(env, structArray);
			throwOOM(env, "GetByteArrayElements");
			return NULL;
		}

		memset(ptr, 0, sizeof(struct sockaddr_in6));

		ptr->sin6_family = AF_INET6;
		//TODO
		ptr->sin6_flowinfo = 0;
		ptr->sin6_scope_id = 0;
		ptr->sin6_port = htons((uint16_t) port);

		uint8_t* sock_addr_ptr = ptr->sin6_addr.__in6_u.__u6_addr8;

		jbyte* bytes = (*env)->GetByteArrayElements(env, jInetAddrBytes, NULL);
		if (bytes == NULL) {
			(*env)->ReleaseByteArrayElements(env, structArray, (jbyte*) ptr, JNI_ABORT);
			(*env)->DeleteLocalRef(env, structArray);
			throwOOM(env, "GetByteArrayElements");
			return NULL;
		}


		for (int i = 0; i < 16;i++) {
			sock_addr_ptr[i] = bytes[i];
		}

		(*env)->ReleaseByteArrayElements(env, jInetAddrBytes, bytes, JNI_ABORT);
		(*env)->ReleaseByteArrayElements(env, structArray, (jbyte*) ptr, JNI_OK);
	}

	jobject result = (*env)->NewObject(env, Sockaddr, SockaddrConstructor, af, structArray);
	(*env)->DeleteLocalRef(env, structArray);

	if (result != NULL) {
		return result;
	}

	if ((*env)->ExceptionCheck(env)) {
		return NULL;
	}

	throwOOM(env, "NewObject");
	return NULL;

}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    from_sockaddr_in
 * Signature: (Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)Ljava/net/InetSocketAddress;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_from_1sockaddr_1in
  (JNIEnv * env, jobject inst, jobject sockaddr) {
	if (sockaddr == NULL) {
		throwNullPointerException(env, "address");
		return NULL;
	}

	jint af = (*env)->GetIntField(env, sockaddr, Sockaddr_addressFamily);
	if (af != AF_INET && af != AF_INET6) {
		throwIllegalArgumentsExc(env, "Address Family is not AF_INET or AF_INET6");
		return NULL;
	}

	jbyteArray jstruct = (*env)->GetObjectField(env, sockaddr, Sockaddr_address);
	if (jstruct == NULL) {
		throwNullPointerException(env, "address.address");
		return NULL;
	}




	jsize len = (*env)->GetArrayLength(env, jstruct);
	jint port = 0;

	jbyteArray bytes = NULL;

	if (af == AF_INET) {
		if (len != sizeof(struct sockaddr_in)) {
			(*env)->DeleteLocalRef(env, jstruct);
			throwIllegalArgumentsExc(env, "address.address has wrong size for AF_INET");
			return NULL;
		}

		struct sockaddr_in* inetPtr = (struct sockaddr_in* ) (*env)->GetByteArrayElements(env, jstruct, NULL);
		if (inetPtr == NULL) {
			(*env)->DeleteLocalRef(env, jstruct);
			throwOOM(env, "GetByteArrayElements");
			return NULL;
		}

		port = ntohs(inetPtr->sin_port);
		uint32_t uiAddr = ntohl(inetPtr->sin_addr.s_addr);
		(*env)->ReleaseByteArrayElements(env, jstruct, (jbyte*) inetPtr, JNI_ABORT);
		(*env)->DeleteLocalRef(env, jstruct);

		bytes = (*env)->NewByteArray(env, 4);
		if (bytes == NULL) {
			throwOOM(env, "NewByteArray 4");
			return NULL;
		}

		jbyte* bytePtr = (*env)->GetByteArrayElements(env, bytes, NULL);
		if (bytePtr == NULL) {
			throwOOM(env, "GetByteArrayElements");
			return NULL;
		}

		//(((in_addr_t)bytes[0]) << 24) + (((in_addr_t)bytes[1]) << 16) + (((in_addr_t)bytes[2]) << 8) + (((in_addr_t)bytes[3]) << 0)

		bytePtr[0] = (uiAddr >> 24) & 0xff;
		bytePtr[1] = (uiAddr >> 16) & 0xff;
		bytePtr[2] = (uiAddr >> 8) & 0xff;
		bytePtr[3] = (uiAddr >> 0) & 0xff;


		(*env)->ReleaseByteArrayElements(env, bytes, bytePtr, JNI_OK);
	} else {
		if (len != sizeof(struct sockaddr_in6)) {
			(*env)->DeleteLocalRef(env, jstruct);
			throwIllegalArgumentsExc(env, "address.address has wrong size for AF_INET6");
			return NULL;
		}

		struct sockaddr_in6* inetPtr = (struct sockaddr_in6*) (*env)->GetByteArrayElements(env, jstruct, NULL);
		if (inetPtr == NULL) {
			(*env)->DeleteLocalRef(env, jstruct);
			throwOOM(env, "GetByteArrayElements");
			return NULL;
		}

		port = ntohs(inetPtr->sin6_port);
		bytes = (*env)->NewByteArray(env, 16);
		if (bytes == NULL) {
			(*env)->ReleaseByteArrayElements(env, jstruct, (jbyte*) inetPtr, JNI_ABORT);
			(*env)->DeleteLocalRef(env, jstruct);
			throwOOM(env, "NewByteArray 16");
			return NULL;
		}

		jbyte* bytePtr = (*env)->GetByteArrayElements(env, bytes, NULL);
		if (bytePtr == NULL) {
			(*env)->ReleaseByteArrayElements(env, jstruct, (jbyte*) inetPtr, JNI_ABORT);
			(*env)->DeleteLocalRef(env, jstruct);
			throwOOM(env, "GetByteArrayElements");
			return NULL;
		}

		uint8_t* sock_addr_ptr = inetPtr->sin6_addr.__in6_u.__u6_addr8;

		for (int i = 0; i < 16;i++) {
			bytePtr[i] = sock_addr_ptr[i];
		}

		(*env)->ReleaseByteArrayElements(env, jstruct, (jbyte*) inetPtr, JNI_ABORT);
		(*env)->DeleteLocalRef(env, jstruct);
		(*env)->ReleaseByteArrayElements(env, bytes, bytePtr, JNI_OK);
	}

	jobject inet = getInetAddressFromByteArray(env, bytes);
	(*env)->DeleteLocalRef(env, bytes);

	//only null if length != 4 || != 16 || null which code above ensures never happens.
	//Only remaining option is OOM
	if (inet == NULL) {
		throwOOM(env, "getInetAddressFromByteArray");
		return NULL;
	}

	jobject result = getInetSocketAddress(env, inet, port);
	(*env)->DeleteLocalRef(env, inet);
	if (result == NULL) {
		if (!(*env)->ExceptionCheck(env)) {
			throwOOM(env, "getInetSocketAddress");
		}
	}

	return result;
}


const int MAX_UNIX_PATH_LEN = sizeof(struct sockaddr_un) - sizeof(sa_family_t) - 1;

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    to_sockaddr_un
 * Signature: (Ljava/lang/String;)Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_to_1sockaddr_1un
  (JNIEnv *env, jobject inst, jstring addr) {
	if (addr == NULL) {
		throwNullPointerException(env, "address");
		return NULL;
	}

	jsize len = (*env)->GetStringUTFLength(env, addr);

	//technically 108 but I want the zero byte at the end for peace of mind.
	if (len > MAX_UNIX_PATH_LEN) {
		throwIllegalArgumentsExc(env, "address is too long");
		return NULL;
	}

	if (len <= 0) {
		throwIllegalArgumentsExc(env, "address is empty string");
		return NULL;
	}

	jbyteArray array = (*env)->NewByteArray(env, sizeof(struct sockaddr_un));
	if (array == NULL) {
		throwOOM(env, "NewByteArray sizeof(struct sockaddr_un)");
		return NULL;
	}

	struct sockaddr_un* ptr = (struct sockaddr_un*) (*env)->GetByteArrayElements(env, array, NULL);
	memset(ptr, 0, sizeof(struct sockaddr_un));
	ptr->sun_family = AF_UNIX;

	const char * path = (*env)->GetStringUTFChars(env, addr, NULL);
	for (int i = 0; i < len; i++) {
		ptr->sun_path[i] = path[i];
	}

	(*env)->ReleaseStringUTFChars(env, addr, path);
	(*env)->ReleaseByteArrayElements(env, array, (jbyte*) ptr, JNI_OK);

	jobject res = (*env)->NewObject(env, Sockaddr, SockaddrConstructor, AF_UNIX, array);
	if (res == NULL) {
		throwOOM(env, "NewObject");
		return NULL;
	}

	(*env)->DeleteLocalRef(env, array);
	return res;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    from_sockaddr_un
 * Signature: (Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_from_1sockaddr_1un
  (JNIEnv * env, jobject inst, jobject sockaddr) {
	if (sockaddr == NULL) {
		throwNullPointerException(env, "address");
		return NULL;
	}

	jint af = (*env)->GetIntField(env, sockaddr, Sockaddr_addressFamily);
	if (af != AF_UNIX) {
		throwIllegalArgumentsExc(env, "Address Family is not AF_UNIX");
		return NULL;
	}

	jbyteArray jstruct = (*env)->GetObjectField(env, sockaddr, Sockaddr_address);
	if (jstruct == NULL) {
		throwNullPointerException(env, "address.address");
		return NULL;
	}

	jsize len = (*env)->GetArrayLength(env, jstruct);

	if (len > sizeof(struct sockaddr_un) && len > sizeof(sa_family_t)+1) {
		(*env)->DeleteLocalRef(env, jstruct);
		throwIllegalArgumentsExc(env, "address.address has wrong size for AF_UNIX");
		return NULL;
	}

	jbyte* bptr = (*env)->GetByteArrayElements(env, jstruct, NULL);
	struct sockaddr_un* ptr  = (struct sockaddr_un*) bptr;
	if (bptr[len-1] != 0) {
		(*env)->ReleaseByteArrayElements(env, jstruct,  bptr, JNI_ABORT);
		(*env)->DeleteLocalRef(env, jstruct);
		throwIllegalArgumentsExc(env, "address.address last byte is not 0");
		return NULL;
	}

	jstring result = (*env)->NewStringUTF(env, (const char *) ptr->sun_path);
	(*env)->ReleaseByteArrayElements(env, jstruct, bptr, JNI_ABORT);
	(*env)->DeleteLocalRef(env, jstruct);

	if (result == NULL) {
		throwOOM(env, "NewStringUTF");
	}

	return result;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    getpagesize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_getpagesize
  (JNIEnv * env, jobject inst) {
	return (jint) getpagesize();
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil
 * Method:    uname
 * Signature: ()Lio/github/alexanderschuetz97/nativeutils/api/structs/Utsname;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil_uname
  (JNIEnv * env, jobject inst) {

	struct utsname uts;
	memset(&uts, 0, sizeof(struct utsname));
	uname(&uts);
	uts.machine[_UTSNAME_MACHINE_LENGTH-1] = 0;
	uts.nodename[_UTSNAME_NODENAME_LENGTH-1] = 0;
	uts.release[_UTSNAME_RELEASE_LENGTH-1] = 0;
	uts.sysname[_UTSNAME_SYSNAME_LENGTH-1] = 0;
	uts.version[_UTSNAME_VERSION_LENGTH-1] = 0;

	jobject utsname = (*env)->NewObject(env, Utsname, Utsname_constructor);
	if (utsname == NULL) {
		throwOOM(env, "NewObject");
		return NULL;
	}

	if (!setStringField(env, utsname, Utsname_sysname, (const char*) &uts.sysname)) {
		return NULL;
	}

	if (!setStringField(env, utsname, Utsname_machine, (const char*) &uts.machine)) {
		return NULL;
	}

	if (!setStringField(env, utsname, Utsname_nodename, (const char*) &uts.nodename)) {
		return NULL;
	}

	if (!setStringField(env, utsname, Utsname_release, (const char*) &uts.release)) {
		return NULL;
	}

	if (!setStringField(env, utsname, Utsname_version, (const char*) &uts.version)) {
		return NULL;
	}

	return utsname;
}

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



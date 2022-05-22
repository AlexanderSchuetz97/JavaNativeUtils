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
#include <jni.h>
#include "common.h"
#include "jni/io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "jstub.h"

//These checks have to be somewhere
static_assert(sizeof(uintptr_t) <= sizeof(jlong), "pointer doesnt fit in jlong");
static_assert(sizeof(jshort) == 2, "jshort is not 2 byte");
static_assert(sizeof(jint) == 4, "jint is not 4 byte");
static_assert(sizeof(jlong) == 8, "jlong is not 8 byte");
static_assert(sizeof(jbyte) == 1, "jbyte is not 1 byte");


jclass fdClass = NULL;
jfieldID fdIntField = NULL;
jfieldID fdHandleField = NULL;

jclass enumClass = NULL;
jmethodID enumOrdinal = NULL;

//EXCEPTIONS
jclass badFDClass = NULL;
jmethodID badFDConstructor = NULL;

jclass unknownErrorClass = NULL;
jmethodID unknownErrorConstructor = NULL;

jclass MutexAbandonedException = NULL;
jmethodID MutexAbandonedExceptionConstructor = NULL;

jclass IllegalArgumentException = NULL;
jclass IllegalStateException = NULL;
jclass oomClass = NULL;
jclass ioExcClass = NULL;

jclass UnsupportedOperationException = NULL;

jclass Exception = NULL;

jclass ReadOnlyFileSystemException = NULL;
jmethodID ReadOnlyFileSystemExceptionConstructor = NULL;


jclass FileSystemLoopException = NULL;
jclass AccessDeniedException = NULL;
jmethodID AccessDeniedExceptionConstructor = NULL;

jclass NotLinkException;
jmethodID NotLinkExceptionConstructor;

jclass FileAlreadyExistsException = NULL;
jmethodID FileAlreadyExistsExceptionConstructor = NULL;


jclass InvalidPathException = NULL;
jmethodID InvalidPathExceptionConstructor = NULL;

jclass FileNotFoundException = NULL;

jclass NotDirectoryException = NULL;

jclass QuotaExceededException = NULL;
jmethodID QuotaExceededExceptionConstructor = NULL;

jclass Field = NULL;
jmethodID Field_getModifier = NULL;
jmethodID Field_getDeclaringClass = NULL;

jclass NullPointerException = NULL;

jclass SharingViolationException = NULL;
jmethodID SharingViolationExceptionConstructor = NULL;

jclass BindException = NULL;
jclass ConnectException = NULL;
jclass SocketTimeoutException = NULL;

jclass InetAddress = NULL;
jmethodID InetAddress_getAddress = NULL;
jmethodID InetAddress_getByAddress = NULL;

jclass Collection = NULL;
jmethodID Collection_add = NULL;
jmethodID Collection_clear = NULL;
jmethodID Collection_size = NULL;
jmethodID Collection_iterator = NULL;

jclass ArrayList = NULL;
jmethodID ArrayListConstructor = NULL;

jclass Iterator = NULL;
jmethodID Iterator_next = NULL;
jmethodID Iterator_hasNext = NULL;

jclass OperationInProgressException = NULL;

jclass InetSocketAddress = NULL;
jmethodID InetSocketAddressConstructor = NULL;
jmethodID InetSocketAddress_getPort = NULL;
jmethodID InetSocketAddress_getAddress = NULL;

jclass Integer = NULL;
jfieldID Integer_value = NULL;
jclass Long = NULL;
jfieldID Long_value = NULL;
jclass Short = NULL;
jfieldID Short_value = NULL;
jclass Byte = NULL;
jfieldID Byte_value = NULL;
jclass Boolean = NULL;
jfieldID Boolean_value = NULL;
jclass Double = NULL;
jfieldID Double_value = NULL;
jclass Float = NULL;
jfieldID Float_value = NULL;
jclass Character = NULL;
jfieldID Character_value = NULL;

jclass PermissionDeniedException = NULL;
jmethodID PermissionDeniedExceptionConstructor = NULL;


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_NativeLibraryLoaderHelper
 * Method:    getNativeLibVersion
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_NativeLibraryLoaderHelper_getNativeLibVersion
  (JNIEnv * env, jclass clazz) {
	return 4;
}


void delRefs(JNIEnv * env) {

	if (fdClass != NULL) {
		(*env) -> DeleteGlobalRef(env, fdClass);
	}

	if (String_Class != NULL) {
		(*env) -> DeleteGlobalRef(env, String_Class);
	}

	if (badFDClass != NULL) {
		(*env) -> DeleteGlobalRef(env, badFDClass);
	}

	if (unknownErrorClass != NULL) {
		(*env) -> DeleteGlobalRef(env, unknownErrorClass);
	}

	if (MutexAbandonedException != NULL) {
		(*env) -> DeleteGlobalRef(env, MutexAbandonedException);
	}

	if (IllegalArgumentException != NULL) {
		(*env) -> DeleteGlobalRef(env, IllegalArgumentException);
	}

	if (IllegalStateException != NULL) {
		(*env) -> DeleteGlobalRef(env, IllegalStateException);
	}

	if (enumClass != NULL) {
		(*env) -> DeleteGlobalRef(env, enumClass);
	}

	if (oomClass != NULL) {
		(*env) -> DeleteGlobalRef(env, oomClass);
	}

	if (ioExcClass != NULL) {
		(*env) -> DeleteGlobalRef(env, ioExcClass);
	}

	if (FileSystemLoopException != NULL) {
		(*env) -> DeleteGlobalRef(env, FileSystemLoopException);
	}

	if (AccessDeniedException != NULL) {
		(*env) -> DeleteGlobalRef(env, AccessDeniedException);
	}

	if (InvalidPathException != NULL) {
		(*env) -> DeleteGlobalRef(env, InvalidPathException);
	}

	if (UnsupportedOperationException != NULL) {
		(*env) -> DeleteGlobalRef(env, UnsupportedOperationException);
	}


	if (ReadOnlyFileSystemException != NULL) {
		(*env) -> DeleteGlobalRef(env, ReadOnlyFileSystemException);
	}

	if (Exception != NULL) {
		(*env) -> DeleteGlobalRef(env, Exception);
	}

	if (StatClass != NULL) {
		(*env) -> DeleteGlobalRef(env, StatClass);
	}

	if (FileNotFoundException != NULL) {
		(*env) -> DeleteGlobalRef(env, FileNotFoundException);
	}

	if (Win32FileAttributeData != NULL) {
		(*env) -> DeleteGlobalRef(env, Win32FileAttributeData);
	}

	if (NotDirectoryException != NULL) {
		(*env) -> DeleteGlobalRef(env, NotDirectoryException);
	}

	if (QuotaExceededException != NULL) {
		(*env) -> DeleteGlobalRef(env, QuotaExceededException);
	}

	if (Field != NULL) {
		(*env) -> DeleteGlobalRef(env, Field);
	}

	if (NullPointerException != NULL) {
		(*env) -> DeleteGlobalRef(env, NullPointerException);
	}

	if (SharingViolationException != NULL) {
		(*env) -> DeleteGlobalRef(env, SharingViolationException);
	}

	if (BindException != NULL) {
		(*env) -> DeleteGlobalRef(env, BindException);
	}

	if (ConnectException != NULL) {
		(*env) -> DeleteGlobalRef(env, ConnectException);
	}

	if (SocketTimeoutException != NULL) {
		(*env) -> DeleteGlobalRef(env, SocketTimeoutException);
	}

	if (InetAddress != NULL) {
		(*env) -> DeleteGlobalRef(env, InetAddress);
	}

	if (Collection != NULL) {
		(*env) -> DeleteGlobalRef(env, Collection);
	}

	if (Iterator != NULL) {
		(*env) -> DeleteGlobalRef(env, Iterator);
	}

	if (PollFD != NULL) {
		(*env) -> DeleteGlobalRef(env, PollFD);
	}

	if (PollFD_PollEvent_values != NULL) {
		for (int i = 0; i < PollFD_PollEvent_values_size; i++) {
			(*env) -> DeleteGlobalRef(env, PollFD_PollEvent_values[i]);
		}

		free(PollFD_PollEvent_values);
	}

	if (RegData_types != NULL) {
		for (int i = 0; i < RegData_types_size; i++) {
			(*env) -> DeleteGlobalRef(env, RegData_types[i]);
		}

		free(RegData_types);
	}

	RegData_types = NULL;

	if (OperationInProgressException != NULL) {
		(*env)->DeleteGlobalRef(env, OperationInProgressException);
	}

	if (InetSocketAddress != NULL) {
		(*env)->DeleteGlobalRef(env, InetSocketAddress);
	}

	if (Sockaddr != NULL) {
		(*env)->DeleteGlobalRef(env, Sockaddr);
	}

	if (Msghdr != NULL) {
		(*env)->DeleteGlobalRef(env, Msghdr);
	}

	if (Iovec != NULL) {
		(*env)->DeleteGlobalRef(env, Iovec);
	}

	if (ArrayList != NULL) {
		(*env)->DeleteGlobalRef(env, ArrayList);
	}

	if (Cmsghdr != NULL) {
		(*env)->DeleteGlobalRef(env, Cmsghdr);
	}

	if (GUID_Class != NULL) {
		(*env)->DeleteGlobalRef(env, GUID_Class);
	}

	if (SpDeviceInfoData != NULL) {
		(*env)->DeleteGlobalRef(env, SpDeviceInfoData);
	}

	if (SpDeviceInterfaceData != NULL) {
		(*env)->DeleteGlobalRef(env, SpDeviceInterfaceData);
	}

	if (JNINativeMemory != NULL) {
		(*env)->DeleteGlobalRef(env, JNINativeMemory);
	}

	if (Integer != NULL) {
		(*env)->DeleteGlobalRef(env, Integer);
	}

	if (Long != NULL) {
		(*env)->DeleteGlobalRef(env, Long);
	}

	if (Short != NULL) {
		(*env)->DeleteGlobalRef(env, Short);
	}

	if (Byte != NULL) {
		(*env)->DeleteGlobalRef(env, Byte);
	}

	if (Boolean != NULL) {
		(*env)->DeleteGlobalRef(env, Boolean);
	}

	if (Double != NULL) {
		(*env)->DeleteGlobalRef(env, Double);
	}

	if (Float != NULL) {
		(*env)->DeleteGlobalRef(env, Float);
	}

	if (Character != NULL) {
		(*env)->DeleteGlobalRef(env, Character);
	}

	if (Utsname != NULL) {
		(*env)->DeleteGlobalRef(env, Utsname);
	}

	if (NotLinkException != NULL) {
		(*env)->DeleteGlobalRef(env, NotLinkException);
	}

	if (PermissionDeniedException != NULL) {
		(*env)->DeleteGlobalRef(env, PermissionDeniedException);
	}

	if (RegData != NULL) {
		(*env)->DeleteGlobalRef(env, RegData);
	}

	if (RegQueryInfoKeyResult_Class != NULL) {
		(*env)->DeleteGlobalRef(env, RegQueryInfoKeyResult_Class);
	}

	if (RegEnumKeyExResult_Class != NULL) {
		(*env)->DeleteGlobalRef(env, RegEnumKeyExResult_Class);
	}

	if (IfNameIndex_Class != NULL) {
		(*env)->DeleteGlobalRef(env, IfNameIndex_Class);
	}

	IfNameIndex_Class = NULL;
	IfNameIndex_Constructor = NULL;

	RegEnumKeyExResult_Class = NULL;
	RegEnumKeyExResult_Constructor = NULL;
	RegEnumKeyExResult_name = NULL;
	RegEnumKeyExResult_className = NULL;
	RegEnumKeyExResult_lastWriteTime = NULL;

	RegQueryInfoKeyResult_Class = NULL;
	RegQueryInfoKeyResult_Constructor = NULL;
	RegQueryInfoKeyResult_keyClass = NULL;
	RegQueryInfoKeyResult_subKeys = NULL;
	RegQueryInfoKeyResult_maxSubKeyLen = NULL;
	RegQueryInfoKeyResult_maxClassLen = NULL;
	RegQueryInfoKeyResult_values = NULL;
	RegQueryInfoKeyResult_maxValueNameLen = NULL;
	RegQueryInfoKeyResult_maxValueLen = NULL;
	RegQueryInfoKeyResult_securityDescriptorSize = NULL;
	RegQueryInfoKeyResult_lastWriteTime = NULL;


	RegData = NULL;
	RegData_Object = NULL;
	RegData_Long = NULL;
	RegData_Int = NULL;
	String_Class = NULL;

	PermissionDeniedException = NULL;
	PermissionDeniedExceptionConstructor = NULL;

	NotLinkExceptionConstructor = NULL;
	NotLinkException = NULL;

	jclass Utsname = NULL;
	jmethodID Utsname_constructor = NULL;
	jfieldID Utsname_sysname = NULL;
	jfieldID Utsname_nodename = NULL;
	jfieldID Utsname_release = NULL;
	jfieldID Utsname_version = NULL;
	jfieldID Utsname_machine = NULL;

	Integer = NULL;
	Integer_value = NULL;
	Long = NULL;
	Long_value = NULL;
	Short = NULL;
	Short_value = NULL;
	Byte = NULL;
	Byte_value = NULL;
	Boolean = NULL;
	Boolean_value = NULL;
	Double = NULL;
	Double_value = NULL;
	Float = NULL;
	Float_value = NULL;
	Character = NULL;
	Character_value = NULL;


	GUID_Class = NULL;
	GUID_constructor = NULL;
	GUID_data1 = NULL;
	GUID_data2 = NULL;
	GUID_data3 = NULL;
	GUID_data4 = NULL;

	SpDeviceInfoData = NULL;
	SpDeviceInfoData_cbSize = NULL;
	SpDeviceInfoData_InterfaceClassGuid = NULL;
	SpDeviceInfoData_DevInst = NULL;
	SpDeviceInfoData_InterfaceClassGuid = NULL;
	SpDeviceInfoData_ptr = NULL;

	SpDeviceInterfaceData = NULL;
	SpDeviceInterfaceData_constructor = NULL;
	SpDeviceInterfaceData_cbSize = NULL;
	SpDeviceInterfaceData_InterfaceClassGuid = NULL;
	SpDeviceInterfaceData_flags = NULL;
	SpDeviceInterfaceData_InterfaceClassGuid = NULL;
	SpDeviceInterfaceData_ptr = NULL;

	MutexAbandonedException = NULL;
	MutexAbandonedExceptionConstructor = NULL;


	Cmsghdr = NULL;
	CmsghdrConstructor = NULL;
	Cmsghdr_payload = NULL;
	Cmsghdr_cmsg_type = NULL;
	Cmsghdr_cmsg_level = NULL;

	ArrayList = NULL;
	ArrayListConstructor = NULL;

	Iovec = NULL;
	Iovec_len = NULL;
	Iovec_off = NULL;
	Iovec_payload = NULL;
	Iovec_size = NULL;

	Msghdr = NULL;
	Msghdr_complete = NULL;
	Msghdr_controlDataTruncated = NULL;
	Msghdr_errQueue = NULL;
	Msghdr_msg_control = NULL;
	Msghdr_msg_controllen = NULL;
	Msghdr_msg_iov = NULL;
	Msghdr_msg_name = NULL;
	Msghdr_outOfBand = NULL;
	Msghdr_truncated = NULL;

	Sockaddr = NULL;
	Sockaddr_address = NULL;
	Sockaddr_addressFamily = NULL;
	SockaddrConstructor = NULL;

	InetSocketAddress = NULL;
	InetSocketAddress_getPort = NULL;
	InetSocketAddress_getAddress = NULL;
	InetSocketAddressConstructor = NULL;

	OperationInProgressException = NULL;

	PollFD_PollEvent_values = NULL;
	PollFD_PollEvent_values_size = 0;
	PollFD = NULL;
	PollFD_fd = NULL;
	PollFD_events = NULL;
	PollFD_revents = NULL;

	Iterator = NULL;
	Iterator_hasNext = NULL;
	Iterator_next = NULL;
	Collection = NULL;
	Collection_add = NULL;
	Collection_clear = NULL;
	Collection_size = NULL;
	Collection_iterator = NULL;

	InetAddress = NULL;
	InetAddress_getAddress = NULL;
	InetAddress_getByAddress = NULL;

	SocketTimeoutException = NULL;
	ConnectException = NULL;
	BindException = NULL;

	SharingViolationException = NULL;
	SharingViolationExceptionConstructor = NULL;

	NullPointerException = NULL;
	Field = NULL;
	Field_getModifier = NULL;
	Field_getDeclaringClass = NULL;


	QuotaExceededException = NULL;
	QuotaExceededExceptionConstructor = NULL;

	NotDirectoryException = NULL;
	Win32FileAttributeData = NULL;
	Win32FileAttributeDataConstructor = NULL;
	Win32FileAttributeData_dwFileAttributes = NULL;
	Win32FileAttributeData_nFileSizeLow = NULL;
	Win32FileAttributeData_nFileSizeHigh = NULL;
	Win32FileAttributeData_ftLastAccessTimeLow = NULL;
	Win32FileAttributeData_ftLastAccessTimeHigh = NULL;
	Win32FileAttributeData_ftLastWriteTimeHigh = NULL;
	Win32FileAttributeData_ftLastWriteTimeLow = NULL;
	Win32FileAttributeData_ftCreationTimeHigh = NULL;
	Win32FileAttributeData_ftCreationTimeLow = NULL;

	FileNotFoundException = NULL;

	StatClass = NULL;
	StatClass_dev = NULL;
	StatClass_ino = NULL;
	StatClass_mode = NULL;
	StatClass_nlink = NULL;
	StatClass_uid = NULL;
	StatClass_gid = NULL;
	StatClass_rdev = NULL;
	StatClass_size = NULL;
	StatClass_size = NULL;
	StatClass_blksize = NULL;
	StatClass_blocks = NULL;
	StatClass_atime = NULL;
	StatClass_mtime = NULL;
	StatClass_ctime = NULL;

	fdClass = NULL;
	badFDClass = NULL;
	unknownErrorClass = NULL;
	IllegalArgumentException = NULL;
	IllegalStateException = NULL;
	enumClass = NULL;
	oomClass = NULL;
	ioExcClass = NULL;
	FileSystemLoopException = NULL;
	AccessDeniedException = NULL;
	InvalidPathException = NULL;
	UnsupportedOperationException = NULL;
	ReadOnlyFileSystemException = NULL;
	Exception = NULL;
	ReadOnlyFileSystemExceptionConstructor = NULL;

	enumOrdinal = NULL;
	badFDConstructor = NULL;
	unknownErrorConstructor = NULL;
	fdIntField = NULL;
	fdHandleField = NULL;
	AccessDeniedExceptionConstructor = NULL;
	InvalidPathExceptionConstructor = NULL;

	JNINativeMemory_ptr = NULL;
}



jclass makeGlobalClassRef(JNIEnv * env, const char * name) {
	jclass clazz = (*env) ->FindClass(env, name);
	if (clazz == NULL) {
		return NULL;
	}

	jclass global = (*env) ->NewGlobalRef(env, clazz);
	(*env) ->DeleteLocalRef(env, clazz);
	return global;
}

jobject* enumerateEnum(JNIEnv * env, const char * name, const char * sig, int* size) {
	jclass myEnumClass = (*env)->FindClass(env, name);
	if (myEnumClass == NULL) {
		return NULL;
	}

	jmethodID mid = (*env)->GetStaticMethodID(env, myEnumClass, "values", sig);
	if (mid == NULL) {
		(*env)->DeleteLocalRef(env, myEnumClass);
		return NULL;
	}

	jobjectArray values = (jobjectArray) (*env)->CallStaticObjectMethod(env, myEnumClass, mid);
	(*env)->DeleteLocalRef(env, myEnumClass);

	if (values == NULL) {
		return NULL;
	}

	jsize len = (*env)->GetArrayLength(env, values);


	jobject* ptr = malloc(len*(sizeof(jobject)));
	if (ptr == NULL) {
		(*env)->DeleteLocalRef(env, values);
		return NULL;
	}

	for (int i = 0; i < len; i++) {
		jobject lref = (*env)->GetObjectArrayElement(env, values, i);
		if (lref == NULL) {
			for (int j = 0; j < i; j++) {
				(*env)->DeleteGlobalRef(env, ptr[j]);
			}
			free(ptr);
			return NULL;
		}

		ptr[i] = (*env)->NewGlobalRef(env, lref);
		(*env)->DeleteLocalRef(env, lref);
		if (ptr[i] == NULL) {
			for (int j = 0; j < i; j++) {
				(*env)->DeleteGlobalRef(env, ptr[j]);
			}
			free(ptr);
			return NULL;
		}
	}

	if (size != NULL) {
		*size = len;
	}
	return ptr;
}

bool makeRefs(JNIEnv * env) {

	Exception = makeGlobalClassRef(env, "java/lang/Exception");
	if (Exception == NULL) {
		return false;
	}

	String_Class = makeGlobalClassRef(env, "java/lang/String");
	if (String_Class == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, String_Class, "cant find java/lang/String");
		return false;
	}

	IfNameIndex_Class = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/IfNameIndex");
	if (IfNameIndex_Class == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, String_Class, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IfNameIndex");
		return false;
	}


	IfNameIndex_Constructor = (*env) ->GetMethodID(env, IfNameIndex_Class, "<init>", "(ILjava/lang/String;)V");
	if (IfNameIndex_Constructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IfNameIndex.<init>(ILjava/lang/String;)V");
		return false;
	}


	RegEnumKeyExResult_Class = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/RegEnumKeyExResult");
	if (RegEnumKeyExResult_Class == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, String_Class, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegEnumKeyExResult");
		return false;
	}

	RegEnumKeyExResult_Constructor = (*env)->GetMethodID(env, RegEnumKeyExResult_Class, "<init>", "()V");
	if (RegEnumKeyExResult_Constructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegEnumKeyExResult.<init>()V");
		return false;
	}

	RegEnumKeyExResult_name = (*env)->GetFieldID(env, RegEnumKeyExResult_Class, "name", "Ljava/lang/String;");
	if (RegEnumKeyExResult_name == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.name");
		return false;
	}

	RegEnumKeyExResult_className = (*env)->GetFieldID(env, RegEnumKeyExResult_Class, "className", "Ljava/lang/String;");
	if (RegEnumKeyExResult_className == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.className");
		return false;
	}

	RegEnumKeyExResult_lastWriteTime = (*env)->GetFieldID(env, RegEnumKeyExResult_Class, "lastWriteTime", "J");
	if (RegEnumKeyExResult_lastWriteTime == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.lastWriteTime");
		return false;
	}

	RegQueryInfoKeyResult_Class = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult");
	if (RegQueryInfoKeyResult_Class == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, String_Class, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult");
		return false;
	}

	RegQueryInfoKeyResult_Constructor = (*env)->GetMethodID(env, RegQueryInfoKeyResult_Class, "<init>", "()V");
	if (RegQueryInfoKeyResult_Constructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.<init>()V");
		return false;
	}


	RegQueryInfoKeyResult_keyClass = (*env)->GetFieldID(env, RegQueryInfoKeyResult_Class, "keyClass", "Ljava/lang/String;");
	if (RegQueryInfoKeyResult_keyClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.keyClass");
		return false;
	}


	RegQueryInfoKeyResult_subKeys = (*env)->GetFieldID(env, RegQueryInfoKeyResult_Class, "subKeys", "I");
	if (RegQueryInfoKeyResult_subKeys == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.subKeys");
		return false;
	}

	RegQueryInfoKeyResult_maxSubKeyLen = (*env)->GetFieldID(env, RegQueryInfoKeyResult_Class, "maxSubKeyLen", "I");
	if (RegQueryInfoKeyResult_maxSubKeyLen == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.maxSubKeyLen");
		return false;
	}

	RegQueryInfoKeyResult_maxClassLen = (*env)->GetFieldID(env, RegQueryInfoKeyResult_Class, "maxClassLen", "I");
	if (RegQueryInfoKeyResult_maxClassLen == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.maxClassLen");
		return false;
	}

	RegQueryInfoKeyResult_values = (*env)->GetFieldID(env, RegQueryInfoKeyResult_Class, "values", "I");
	if (RegQueryInfoKeyResult_values == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.values");
		return false;
	}

	RegQueryInfoKeyResult_maxValueNameLen = (*env)->GetFieldID(env, RegQueryInfoKeyResult_Class, "maxValueNameLen", "I");
	if (RegQueryInfoKeyResult_maxValueNameLen == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.maxValueNameLen");
		return false;
	}

	RegQueryInfoKeyResult_maxValueLen = (*env)->GetFieldID(env, RegQueryInfoKeyResult_Class, "maxValueLen", "I");
	if (RegQueryInfoKeyResult_maxValueLen == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.maxValueLen");
		return false;
	}

	RegQueryInfoKeyResult_securityDescriptorSize = (*env)->GetFieldID(env, RegQueryInfoKeyResult_Class, "securityDescriptorSize", "I");
	if (RegQueryInfoKeyResult_securityDescriptorSize == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.securityDescriptorSize");
		return false;
	}

	RegQueryInfoKeyResult_lastWriteTime = (*env)->GetFieldID(env, RegQueryInfoKeyResult_Class, "lastWriteTime", "J");
	if (RegQueryInfoKeyResult_lastWriteTime == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult.lastWriteTime");
		return false;
	}



	PermissionDeniedException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/PermissionDeniedException");
	if (PermissionDeniedException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/PermissionDeniedException");
		return false;
	}

	PermissionDeniedExceptionConstructor = (*env)->GetMethodID(env, PermissionDeniedException, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (PermissionDeniedExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/PermissionDeniedException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}

	Utsname = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Utsname");
	if (Utsname == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname");
		return false;
	}

	Utsname_constructor = (*env)->GetMethodID(env, Utsname, "<init>", "()V");
	if (Utsname_constructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.<init>()V");
		return false;
	}

	Utsname_sysname = (*env)->GetFieldID(env, Utsname, "sysname", "Ljava/lang/String;");
	if (Utsname_sysname == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.sysname");
		return false;
	}

	Utsname_nodename = (*env)->GetFieldID(env, Utsname, "nodename", "Ljava/lang/String;");
	if (Utsname_nodename == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.nodename");
		return false;
	}


	Utsname_release = (*env)->GetFieldID(env, Utsname, "release", "Ljava/lang/String;");
	if (Utsname_release == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.release");
		return false;
	}

	Utsname_version = (*env)->GetFieldID(env, Utsname, "version", "Ljava/lang/String;");
	if (Utsname_version == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.version");
		return false;
	}

	Utsname_machine = (*env)->GetFieldID(env, Utsname, "machine", "Ljava/lang/String;");
	if (Utsname_machine == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.machine");
		return false;
	}


	Integer = makeGlobalClassRef(env, "java/lang/Integer");
	if (Integer == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Integer");
		return false;
	}

	Integer_value = (*env)->GetFieldID(env, Integer, "value", "I");
	if (Integer_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Integer.value");
		return false;
	}

	Long = makeGlobalClassRef(env, "java/lang/Long");
	if (Long == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Long");
		return false;
	}

	Long_value = (*env)->GetFieldID(env, Long, "value", "J");
	if (Long_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Long.value");
		return false;
	}

	Short = makeGlobalClassRef(env, "java/lang/Short");
	if (Short == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Short");
		return false;
	}

	Short_value = (*env)->GetFieldID(env, Short, "value", "S");
	if (Short_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Short.value");
		return false;
	}

	Byte = makeGlobalClassRef(env, "java/lang/Byte");
	if (Byte == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Byte");
		return false;
	}

	Byte_value = (*env)->GetFieldID(env, Byte, "value", "B");
	if (Byte_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Byte.value");
		return false;
	}

	Boolean = makeGlobalClassRef(env, "java/lang/Boolean");
	if (Boolean == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Boolean");
		return false;
	}

	Boolean_value = (*env)->GetFieldID(env, Boolean, "value", "Z");
	if (Boolean_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Boolean.value");
		return false;
	}

	Character = makeGlobalClassRef(env, "java/lang/Character");
	if (Character == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Character");
		return false;
	}

	Character_value = (*env)->GetFieldID(env, Character, "value", "C");
	if (Character_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Character.value");
		return false;
	}

	Float = makeGlobalClassRef(env, "java/lang/Float");
	if (Float == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Float");
		return false;
	}

	Float_value = (*env)->GetFieldID(env, Float, "value", "F");
	if (Float_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Float.value");
		return false;
	}

	Double = makeGlobalClassRef(env, "java/lang/Double");
	if (Double == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Double");
		return false;
	}

	Double_value = (*env)->GetFieldID(env, Double, "value", "D");
	if (Double_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Double.value");
		return false;
	}

	JNINativeMemory = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/impl/JNINativeMemory");
	if (JNINativeMemory == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/impl/JNINativeMemory");
		return false;
	}

	JNINativeMemory_ptr = (*env)->GetFieldID(env, JNINativeMemory, "ptr", "J");
	if (JNINativeMemory_ptr == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/impl/JNINativeMemory.ptr");
		return false;
	}

	GUID_Class = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/GUID");
	if (GUID_Class == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID");
		return false;
	}

	GUID_constructor = (*env)->GetMethodID(env, GUID_Class, "<init>", "()V");
	if (GUID_constructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.<init>()V");
		return false;
	}

	GUID_data1 = (*env)->GetFieldID(env, GUID_Class, "data1", "I");
	if (GUID_data1 == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.data1");
		return false;
	}

	GUID_data2 = (*env)->GetFieldID(env, GUID_Class, "data2", "S");
	if (GUID_data2 == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.data2");
		return false;
	}

	GUID_data3 = (*env)->GetFieldID(env, GUID_Class, "data3", "S");
	if (GUID_data3 == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.data3");
		return false;
	}
	GUID_data4 = (*env)->GetFieldID(env, GUID_Class, "data4", "[B");
	if (GUID_data4 == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.data4");
		return false;
	}

	SpDeviceInfoData = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInfoData");
	if (SpDeviceInfoData == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInfoData");
		return false;
	}

	SpDeviceInfoData_cbSize = (*env)->GetFieldID(env, SpDeviceInfoData, "cbSize", "I");
	if (SpDeviceInfoData_cbSize == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInfoData.cbSize");
		return false;
	}

	SpDeviceInfoData_InterfaceClassGuid = (*env)->GetFieldID(env, SpDeviceInfoData, "InterfaceClassGuid", "Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
	if (SpDeviceInfoData_InterfaceClassGuid == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInfoData.InterfaceClassGuid");
		return false;
	}

	SpDeviceInfoData_DevInst = (*env)->GetFieldID(env, SpDeviceInfoData, "DevInst", "I");
	if (SpDeviceInfoData_cbSize == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInfoData.DevInst");
		return false;
	}

	SpDeviceInfoData_ptr = (*env)->GetFieldID(env, SpDeviceInfoData, "ptr", "J");
	if (SpDeviceInfoData_cbSize == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInfoData.ptr");
		return false;
	}

	SpDeviceInterfaceData = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInterfaceData");
	if (SpDeviceInterfaceData == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInterfaceData");
		return false;
	}

	SpDeviceInterfaceData_constructor = (*env)->GetMethodID(env, SpDeviceInterfaceData, "<init>", "()V");
	if (SpDeviceInterfaceData_constructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInterfaceData.<init>()V");
		return false;
	}

	SpDeviceInterfaceData_cbSize = (*env)->GetFieldID(env, SpDeviceInterfaceData, "cbSize", "I");
	if (SpDeviceInterfaceData_cbSize == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInterfaceData.cbSize");
		return false;
	}

	SpDeviceInterfaceData_InterfaceClassGuid = (*env)->GetFieldID(env, SpDeviceInterfaceData, "InterfaceClassGuid", "Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
	if (SpDeviceInterfaceData_InterfaceClassGuid == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInterfaceData.InterfaceClassGuid");
		return false;
	}

	SpDeviceInterfaceData_flags = (*env)->GetFieldID(env, SpDeviceInterfaceData, "flags", "I");
	if (SpDeviceInterfaceData_flags == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInterfaceData.flags");
		return false;
	}


	SpDeviceInterfaceData_ptr = (*env)->GetFieldID(env, SpDeviceInterfaceData, "ptr", "J");
	if (SpDeviceInterfaceData_ptr == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInterfaceData.ptr");
		return false;
	}


	Sockaddr = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr");
	if (Sockaddr == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr");
		return false;
	}

	SockaddrConstructor = (*env)->GetMethodID(env, Sockaddr, "<init>", "(I[B)V");
	if (SockaddrConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.<init>(I[B))V");
		return false;
	}

	Sockaddr_address = (*env)->GetFieldID(env, Sockaddr, "address", "[B");
	if (Sockaddr_address == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.address");
		return false;
	}

	Sockaddr_addressFamily = (*env)->GetFieldID(env, Sockaddr, "addressFamily", "I");
	if (Sockaddr_addressFamily == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.addressFamily");
		return false;
	}

	OperationInProgressException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/OperationInProgressException");
	if (OperationInProgressException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/OperationInProgressException");
		return false;
	}


	Cmsghdr = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr");
	if (Cmsghdr == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr");
	}

	CmsghdrConstructor = (*env)->GetMethodID(env, Cmsghdr, "<init>", "()V");
	if (CmsghdrConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr.<init>()V");
		return false;
	}

	Cmsghdr_payload = (*env)->GetFieldID(env, Cmsghdr, "payload", "[B");
	if (Cmsghdr_payload == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr.payload");
		return false;
	}

	Cmsghdr_cmsg_type = (*env)->GetFieldID(env, Cmsghdr, "cmsg_type", "I");
	if (Cmsghdr_cmsg_type == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr.cmsg_type");
		return false;
	}

	Cmsghdr_cmsg_level = (*env)->GetFieldID(env, Cmsghdr, "cmsg_level", "I");
	if (Cmsghdr_cmsg_level == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr.cmsg_level");
		return false;
	}

	InetSocketAddress = makeGlobalClassRef(env, "java/net/InetSocketAddress");
	if (InetSocketAddress == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress");
		return false;
	}

	InetSocketAddressConstructor = (*env)->GetMethodID(env, InetSocketAddress, "<init>", "(Ljava/net/InetAddress;I)V");
	if (InetSocketAddressConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddressConstructor.<init>(Ljava/net/InetAddress;I)V");
		return false;
	}

	InetSocketAddress_getAddress = (*env)->GetMethodID(env, InetSocketAddress, "getAddress", "()Ljava/net/InetAddress;");
	if (InetSocketAddress_getAddress == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.getAddress()Ljava/net/InetAddress;");
		return false;
	}

	InetSocketAddress_getPort = (*env)->GetMethodID(env, InetSocketAddress, "getPort", "()I");
	if (InetSocketAddress_getPort == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.getPort()I");
		return false;
	}

	PollFD = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/PollFD");
	if (PollFD == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD");
		return false;
	}

	PollFD_PollEvent_values = enumerateEnum(env, "io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent", "()[Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;", &PollFD_PollEvent_values_size);
	if (PollFD_PollEvent_values == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "failed to enumerate enum values of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent");
		return false;
	}

	PollFD_fd = (*env)->GetFieldID(env, PollFD, "fd", "I");
	if (PollFD_fd == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD.fd");
		return false;
	}

	PollFD_events = (*env)->GetFieldID(env, PollFD, "events", "Ljava/util/EnumSet;");
	if (PollFD_events == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD.events Ljava/util/EnumSet;");
		return false;
	}

	PollFD_revents = (*env)->GetFieldID(env, PollFD, "revents", "Ljava/util/EnumSet;");
	if (PollFD_revents == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD.revents Ljava/util/EnumSet;");
		return false;
	}


	Msghdr = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr");
	if (Msghdr == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr");
		return false;
	}

	Msghdr_msg_iov = (*env)->GetFieldID(env, Msghdr, "msg_iov", "[Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;");
	if (Msghdr_msg_iov == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.msg_iov");
		return false;
	}

	Msghdr_msg_control = (*env)->GetFieldID(env, Msghdr, "msg_control", "[B");
	if (Msghdr_msg_control == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.msg_control");
		return false;
	}

	Msghdr_msg_controllen = (*env)->GetFieldID(env, Msghdr, "msg_controllen", "I");
	if (Msghdr_msg_control == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.msg_controllen");
		return false;
	}

	Msghdr_msg_name = (*env)->GetFieldID(env, Msghdr, "msg_name", "Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
	if (Msghdr_msg_name == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.msg_name");
		return false;
	}

	Msghdr_complete = (*env)->GetFieldID(env, Msghdr, "complete", "Z");
	if (Msghdr_complete == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.complete");
		return false;
	}

	Msghdr_truncated = (*env)->GetFieldID(env, Msghdr, "truncated", "Z");
	if (Msghdr_truncated == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.truncated");
		return false;
	}

	Msghdr_controlDataTruncated = (*env)->GetFieldID(env, Msghdr, "controlDataTruncated", "Z");
	if (Msghdr_controlDataTruncated == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.controlDataTruncated");
		return false;
	}

	Msghdr_outOfBand = (*env)->GetFieldID(env, Msghdr, "outOfBand", "Z");
	if (Msghdr_outOfBand == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.outOfBand");
		return false;
	}

	Msghdr_errQueue = (*env)->GetFieldID(env, Msghdr, "errQueue", "Z");
	if (Msghdr_errQueue == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.errQueue");
		return false;
	}

	Iovec = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Iovec");
	if (Iovec == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Iovec");
		return false;
	}

	Iovec_off = (*env)->GetFieldID(env, Iovec, "off", "I");
	if (Iovec_off == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Iovec.off");
		return false;
	}

	Iovec_len = (*env)->GetFieldID(env, Iovec, "len", "I");
	if (Iovec_len == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Iovec.len");
		return false;
	}

	Iovec_size = (*env)->GetFieldID(env, Iovec, "size", "I");
	if (Iovec_size == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Iovec.size");
		return false;
	}

	Iovec_payload = (*env)->GetFieldID(env, Iovec, "payload", "[B");
	if (Iovec_payload == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "io/github/alexanderschuetz97/nativeutils/api/structs/Iovec.payload");
		return false;
	}

	NotLinkException = makeGlobalClassRef(env, "java/nio/file/NotLinkException");
	if (NotLinkException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/NotLinkException");
		return false;
	}

	NotLinkExceptionConstructor = (*env)->GetMethodID(env, NotLinkException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (NotLinkExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/NotLinkException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}

	Collection = makeGlobalClassRef(env, "java/util/Collection");
	if (Collection == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/Collection");
		return false;
	}

	Collection_add = (*env) ->GetMethodID(env, Collection, "add", "(Ljava/lang/Object;)Z");
	if (Collection_add == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.add(Ljava/lang/Object;)Z");
		return false;
	}

	Collection_clear = (*env) ->GetMethodID(env, Collection, "clear", "()V");
	if (Collection_clear == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.clear()V");
		return false;
	}


	Collection_size = (*env) ->GetMethodID(env, Collection, "size", "()I");
	if (Collection_size == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.size()I");
		return false;
	}

	Collection_iterator = (*env) ->GetMethodID(env, Collection, "iterator", "()Ljava/util/Iterator;");
	if (Collection_iterator == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.iterator()Ljava/util/Iterator;");
		return false;
	}

	ArrayList = makeGlobalClassRef(env, "java/util/ArrayList");
	if (ArrayList == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList");
		return false;
	}

	ArrayListConstructor = (*env)->GetMethodID(env, ArrayList, "<init>", "()V");
	if (ArrayList == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.<init>()V");
		return false;
	}



	Iterator = makeGlobalClassRef(env, "java/util/Iterator");
	if (Iterator == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/Iterator");
		return false;
	}

	Iterator_hasNext = (*env) ->GetMethodID(env, Iterator, "hasNext", "()Z");
	if (Iterator_hasNext == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/Iterator.hasNext()Z");
		return false;
	}

	Iterator_next = (*env) ->GetMethodID(env, Iterator, "next", "()Ljava/lang/Object;");
	if (Iterator_next == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/Iterator.next()Ljava/lang/Object;");
		return false;
	}


	IllegalArgumentException = makeGlobalClassRef(env, "java/lang/IllegalArgumentException");
	if (IllegalArgumentException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalArgumentException");
		return false;
	}

	InetAddress = makeGlobalClassRef(env, "java/net/InetAddress");
	if (InetAddress == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress");
		return false;
	}

	InetAddress_getAddress = (*env) ->GetMethodID(env, InetAddress, "getAddress", "()[B");
	if (InetAddress_getAddress == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getAddress()[B");
		return false;
	}

	InetAddress_getByAddress = (*env) ->GetStaticMethodID(env, InetAddress, "getByAddress", "([B)Ljava/net/InetAddress;");
	if (InetAddress_getByAddress == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getByAddress([B)Ljava/net/InetAddress;");
		return false;
	}

	NullPointerException = makeGlobalClassRef(env, "java/lang/NullPointerException");
	if (NullPointerException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/NullPointerException");
		return false;
	}

	IllegalStateException = makeGlobalClassRef(env, "java/lang/IllegalStateException");
	if (IllegalStateException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalStateException");
		return false;
	}

	SocketTimeoutException = makeGlobalClassRef(env, "java/net/SocketTimeoutException");
	if (SocketTimeoutException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/SocketTimeoutException");
		return false;
	}

	BindException = makeGlobalClassRef(env, "java/net/BindException");
	if (BindException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/BindException");
		return false;
	}

	ConnectException = makeGlobalClassRef(env, "java/net/ConnectException");
	if (ConnectException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/ConnectException");
		return false;
	}

	Field = makeGlobalClassRef(env, "java/lang/reflect/Field");
	if (Field == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/reflect/Field");
		return false;
	}

	Field_getModifier = (*env)->GetMethodID(env, Field, "getModifiers", "()I");
	if (Field_getModifier == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/reflect/Field.getModifiers()I");
		return false;
	}

	Field_getDeclaringClass = (*env)->GetMethodID(env, Field, "getDeclaringClass", "()Ljava/lang/Class;");
	if (Field_getDeclaringClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/reflect/Field.getDeclaringClass()Ljava/lang/Class;");
		return false;
	}

	NotDirectoryException = makeGlobalClassRef(env, "java/nio/file/NotDirectoryException");
	if (NotDirectoryException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/NotDirectoryException");
		return false;
	}

	QuotaExceededException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/QuotaExceededException");
	if (QuotaExceededException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/QuotaExceededException");
		return false;
	}

	QuotaExceededExceptionConstructor = (*env) ->GetMethodID(env, QuotaExceededException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");;
	if (QuotaExceededExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/QuotaExceededException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}

	SharingViolationException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException");
	if (SharingViolationException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException");
		return false;
	}

	SharingViolationExceptionConstructor = (*env) ->GetMethodID(env, SharingViolationException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (SharingViolationExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}



	Win32FileAttributeData = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData");
	if (Win32FileAttributeData == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData");
		return false;
	}

	Win32FileAttributeDataConstructor = (*env) ->GetMethodID(env, Win32FileAttributeData, "<init>", "()V");;
	if (Win32FileAttributeDataConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.<init>()V");
		return false;
	}

	Win32FileAttributeData_dwFileAttributes = (*env) ->GetFieldID(env, Win32FileAttributeData, "dwFileAttributes", "J");
	if (Win32FileAttributeData_dwFileAttributes == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_dwFileAttributes J");
		return false;
	}

	Win32FileAttributeData_nFileSizeLow = (*env) ->GetFieldID(env, Win32FileAttributeData, "nFileSizeLow", "J");
	if (Win32FileAttributeData_nFileSizeLow == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_nFileSizeLow J");
		return false;
	}

	Win32FileAttributeData_nFileSizeHigh = (*env) ->GetFieldID(env, Win32FileAttributeData, "nFileSizeHigh", "J");
	if (Win32FileAttributeData_nFileSizeHigh == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_nFileSizeHigh J");
		return false;
	}

	Win32FileAttributeData_ftLastAccessTimeLow = (*env) ->GetFieldID(env, Win32FileAttributeData, "ftLastAccessTimeLow", "J");
	if (Win32FileAttributeData_ftLastAccessTimeLow == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftLastAccessTimeLow J");
		return false;
	}

	Win32FileAttributeData_ftLastAccessTimeHigh = (*env) ->GetFieldID(env, Win32FileAttributeData, "ftLastAccessTimeHigh", "J");
	if (Win32FileAttributeData_ftLastAccessTimeHigh == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftLastAccessTimeHigh J");
		return false;
	}

	Win32FileAttributeData_ftLastWriteTimeLow = (*env) ->GetFieldID(env, Win32FileAttributeData, "ftLastWriteTimeLow", "J");
	if (Win32FileAttributeData_ftLastWriteTimeLow == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftLastWriteTimeLow J");
		return false;
	}

	Win32FileAttributeData_ftCreationTimeHigh = (*env) ->GetFieldID(env, Win32FileAttributeData, "ftCreationTimeHigh", "J");
	if (Win32FileAttributeData_ftCreationTimeHigh == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftCreationTimeHigh J");
		return false;
	}

	Win32FileAttributeData_ftCreationTimeLow = (*env) ->GetFieldID(env, Win32FileAttributeData, "ftCreationTimeLow", "J");
	if (Win32FileAttributeData_ftCreationTimeLow == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftCreationTimeLow J");
		return false;
	}

	FileNotFoundException = makeGlobalClassRef(env, "java/io/FileNotFoundException");
	if (FileNotFoundException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/io/FileNotFoundException");
		return false;
	}

	StatClass = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Stat");
	if (StatClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat");
		return false;
	}

	StatClassConstructor = (*env) ->GetMethodID(env, StatClass, "<init>", "()V");
	if (StatClassConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.<init>()V");
		return false;
	}


	StatClass_dev = (*env) ->GetFieldID(env, StatClass, "dev", "J");
	if (StatClass_dev == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.dev J");
		return false;
	}

	StatClass_ino = (*env) ->GetFieldID(env, StatClass, "ino", "J");
	if (StatClass_ino == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.ino J");
		return false;
	}

	StatClass_mode = (*env) ->GetFieldID(env, StatClass, "mode", "J");
	if (StatClass_mode == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.mode J");
		return false;
	}

	StatClass_nlink = (*env) ->GetFieldID(env, StatClass, "nlink", "J");
	if (StatClass_nlink == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.nlink J");
		return false;
	}

	StatClass_uid = (*env) ->GetFieldID(env, StatClass, "uid", "J");
	if (StatClass_uid == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.uid J");
		return false;
	}

	StatClass_gid = (*env) ->GetFieldID(env, StatClass, "gid", "J");
	if (StatClass_gid == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.gid J");
		return false;
	}

	StatClass_rdev = (*env) ->GetFieldID(env, StatClass, "rdev", "J");
	if (StatClass_rdev == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.rdev J");
		return false;
	}

	StatClass_size = (*env) ->GetFieldID(env, StatClass, "size", "J");
	if (StatClass_size == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.size J");
		return false;
	}

	StatClass_blksize = (*env) ->GetFieldID(env, StatClass, "blksize", "J");
	if (StatClass_blksize == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.blksize J");
		return false;
	}

	StatClass_blocks = (*env) ->GetFieldID(env, StatClass, "blocks", "J");
	if (StatClass_blocks == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.blocks J");
		return false;
	}

	StatClass_atime = (*env) ->GetFieldID(env, StatClass, "atime", "J");
	if (StatClass_atime == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.atime J");
		return false;
	}

	StatClass_mtime = (*env) ->GetFieldID(env, StatClass, "mtime", "J");
	if (StatClass_mtime == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.mtime J");
		return false;
	}

	StatClass_ctime = (*env) ->GetFieldID(env, StatClass, "ctime", "J");
	if (StatClass_ctime == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.ctime J");
		return false;
	}

	fdClass = makeGlobalClassRef(env, "java/io/FileDescriptor");
	if (fdClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/io/FileDescriptor");
		return false;
	}

	fdIntField = (*env) ->GetFieldID(env, fdClass, "fd", "I");
	if (fdIntField == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/io/FileDescriptor.fd I");
		return false;
	}


	fdHandleField = (*env) ->GetFieldID(env, fdClass, "handle", "J");
	if (fdHandleField == NULL) {
		//!DOES NOT EXIST ON LINUX ONLY FOR WINDOWS!
		(*env)->ExceptionClear(env);
	}

	badFDClass = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/InvalidFileDescriptorException");
	if (badFDClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/InvalidFileDescriptorException");
		return false;
	}

	badFDConstructor = (*env) ->GetMethodID(env, badFDClass, "<init>", "()V");
	if (badFDConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/InvalidFileDescriptorException.<init>()V");
		return false;
	}

	unknownErrorClass = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/UnknownNativeErrorException");
	if (unknownErrorClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/UnknownNativeErrorException");
		return false;
	}

	unknownErrorConstructor = (*env) ->GetMethodID(env, unknownErrorClass, "<init>", "(J)V");
	if (unknownErrorConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/UnknownNativeErrorException.<init>(J)V");
		return false;
	}

	MutexAbandonedException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/MutexAbandonedException");
	if (MutexAbandonedException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/MutexAbandonedException");
		return false;
	}

	MutexAbandonedExceptionConstructor = (*env) ->GetMethodID(env, MutexAbandonedException, "<init>", "(J)V");
	if (MutexAbandonedExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/MutexAbandonedException.<init>(J)V");
		return false;
	}

	InvalidPathException = makeGlobalClassRef(env, "java/nio/file/InvalidPathException");
	if (InvalidPathException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/AccessDeniedException");
		return false;
	}

	ReadOnlyFileSystemException = makeGlobalClassRef(env, "java/nio/file/ReadOnlyFileSystemException");
	if (ReadOnlyFileSystemException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/ReadOnlyFileSystemException");
		return false;
	}

	ReadOnlyFileSystemExceptionConstructor = (*env) ->GetMethodID(env, ReadOnlyFileSystemException, "<init>", "()V");
	if (ReadOnlyFileSystemExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/ReadOnlyFileSystemException.<init>()V");
		return false;
	}

	UnsupportedOperationException = makeGlobalClassRef(env, "java/lang/UnsupportedOperationException");
	if (UnsupportedOperationException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/UnsupportedOperationException");
		return false;
	}

	InvalidPathExceptionConstructor = (*env) ->GetMethodID(env, InvalidPathException, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (InvalidPathExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/InvalidPathException.<init>(Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}

	AccessDeniedException = makeGlobalClassRef(env, "java/nio/file/AccessDeniedException");
	if (AccessDeniedException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/AccessDeniedException");
		return false;
	}

	AccessDeniedExceptionConstructor = (*env) ->GetMethodID(env, AccessDeniedException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (AccessDeniedExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/AccessDeniedException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}

	FileAlreadyExistsException = makeGlobalClassRef(env, "java/nio/file/FileAlreadyExistsException");
	if (FileAlreadyExistsException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/FileAlreadyExistsException");
		return false;
	}

	FileAlreadyExistsExceptionConstructor = (*env) ->GetMethodID(env, FileAlreadyExistsException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (FileAlreadyExistsExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/FileAlreadyExistsException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}

	FileSystemLoopException = makeGlobalClassRef(env, "java/nio/file/FileSystemLoopException");
	if (FileSystemLoopException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/FileSystemLoopException");
		return false;
	}

	oomClass = makeGlobalClassRef(env, "java/lang/OutOfMemoryError");
	if (oomClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/OutOfMemoryError");
		return false;
	}

	ioExcClass = makeGlobalClassRef(env, "java/io/IOException");
	if (ioExcClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/io/IOException");
		return false;
	}

	enumClass = makeGlobalClassRef(env, "java/lang/Enum");
	if (enumClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Enum");
		return false;
	}

	enumOrdinal = (*env) ->GetMethodID(env, enumClass, "ordinal", "()I");
	if (enumOrdinal == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Enum.ordinal()I");
		return false;
	}

	RegData = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/RegData");
	if (RegData == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegData");
		return false;
	}
	RegData_Object = (*env)->GetMethodID(env, RegData, "<init>", "(Ljava/lang/Object;Lio/github/alexanderschuetz97/nativeutils/api/structs/RegData$RegType;)V");
	if (RegData_Object == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegData.<init>(Ljava/lang/Object;Lio/github/alexanderschuetz97/nativeutils/api/structs/RegData$RegType;)V");
		return false;
	}
	RegData_Long = (*env)->GetMethodID(env, RegData, "<init>", "(J)V");
	if (RegData_Long == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegData.<init>(J)V");
		return false;
	}
	RegData_Int = (*env)->GetMethodID(env, RegData, "<init>", "(I)V");
	if (RegData_Int == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/RegData.<init>(I)V");
		return false;
	}

	RegData_types = enumerateEnum(env, "io/github/alexanderschuetz97/nativeutils/api/structs/RegData$RegType", "()[Lio/github/alexanderschuetz97/nativeutils/api/structs/RegData$RegType;", &RegData_types_size);
	if (RegData_types == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant enumerate io/github/alexanderschuetz97/nativeutils/api/structs/RegData$RegType");
		return false;
	}


	return true;
}

void delRef(JNIEnv * env, jobject obj) {
	if (obj == NULL) {
		return;
	}

	(*env) -> DeleteLocalRef(env, obj);
}

jint unboxInt(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetIntField(env, box, Integer_value);
}

jlong unboxLong(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetLongField(env, box, Long_value);
}

jshort unboxShort(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetShortField(env, box, Short_value);
}

jboolean unboxBool(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetBooleanField(env, box, Boolean_value);
}

jchar unboxChar(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetCharField(env, box, Character_value);
}

jbyte unboxByte(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetByteField(env, box, Byte_value);
}

jdouble unboxDouble(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetDoubleField(env, box, Double_value);
}

jfloat unboxFloat(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetFloatField(env, box, Float_value);
}

jstring toJString(JNIEnv * env, const char* data) {
	if (data == NULL) {
		return NULL;
	}
	jstring str = (*env) ->NewStringUTF(env, data);
	if (str == NULL) {
		//EAT OOM
		(*env)->ExceptionClear(env);
	}
	return str;
}

void throwUnknownError(JNIEnv * env, jlong code) {
	jobject inst = (*env) -> NewObject(env, unknownErrorClass, unknownErrorConstructor, code);
	if (inst == NULL) {
		//OOM already thrown
		return;
	}
	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwMutexAbandonedException(JNIEnv * env, jlong handle) {
	jobject inst = (*env) -> NewObject(env, MutexAbandonedException, MutexAbandonedExceptionConstructor, handle);
	if (inst == NULL) {
		//OOM already thrown
		return;
	}
	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwBadFileDescriptor(JNIEnv * env) {
	jobject inst = (*env) -> NewObject(env, badFDClass, badFDConstructor);
	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst );
}

void throwFSLoop(JNIEnv * env, const char* file) {
	(*env)->ThrowNew( env, FileSystemLoopException, file);
}

void throwUnsupportedExc(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, UnsupportedOperationException, message);
}

void throwFSReadOnly(JNIEnv * env) {
	jobject inst = (*env) -> NewObject(env, ReadOnlyFileSystemException, ReadOnlyFileSystemExceptionConstructor);
	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst);
	(*env)->DeleteLocalRef(env, inst);
}

void throwNotDirectoryException(JNIEnv * env, const char* path) {
	(*env)->ThrowNew(env, NotDirectoryException, path);
}

void throwBindException(JNIEnv * env, const char* message) {
	(*env)->ThrowNew(env, BindException, message);
}

void throwConnectException(JNIEnv * env, const char* message) {
	(*env)->ThrowNew(env, ConnectException, message);
}

void throwSocketTimeoutException(JNIEnv * env, const char* message) {
	(*env)->ThrowNew(env, SocketTimeoutException, message);
}


void throwInvalidPath(JNIEnv * env, const char* path, const char* reason) {
	jstring fileString = toJString(env, path);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, InvalidPathException, InvalidPathExceptionConstructor, fileString, reasonString);

	delRef(env, fileString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw(env, inst);
	(*env)->DeleteLocalRef(env, inst);
}

void throwQuotaExceededException(JNIEnv * env, const char* file, const char* other, const char* reason) {
	jstring fileString = toJString(env, file);
	jstring otherString = toJString(env, other);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, QuotaExceededException, QuotaExceededExceptionConstructor, fileString, otherString, reasonString);

	delRef(env, fileString);
	delRef(env, otherString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}


void throwNotLinkException(JNIEnv * env, const char* file, const char* other, const char* reason) {
	jstring fileString = toJString(env, file);
	jstring otherString = toJString(env, other);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, NotLinkException, NotLinkExceptionConstructor, fileString, otherString, reasonString);

	delRef(env, fileString);
	delRef(env, otherString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwFSAccessDenied(JNIEnv * env, const char* file, const char* other, const char* reason) {
	jstring fileString = toJString(env, file);
	jstring otherString = toJString(env, other);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, AccessDeniedException, AccessDeniedExceptionConstructor, fileString, otherString, reasonString);

	delRef(env, fileString);
	delRef(env, otherString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwPermissionDeniedException(JNIEnv * env, const char* file, const char* reason) {
	jstring fileString = toJString(env, file);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, PermissionDeniedException, PermissionDeniedExceptionConstructor, fileString, reasonString);

	delRef(env, fileString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwShareingViolationException(JNIEnv * env, const char* file, const char* other, const char* reason) {
	jstring fileString = toJString(env, file);
	jstring otherString = toJString(env, other);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, SharingViolationException, SharingViolationExceptionConstructor, fileString, otherString, reasonString);

	delRef(env, fileString);
	delRef(env, otherString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwFileAlreadyExistsExc(JNIEnv * env, const char* file, const char* other, const char* reason) {
	jstring fileString = toJString(env, file);
	jstring otherString = toJString(env, other);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, FileAlreadyExistsException, FileAlreadyExistsExceptionConstructor, fileString, otherString, reasonString);

	delRef(env, fileString);
	delRef(env, otherString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwOOM(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, oomClass, message );
}

void throwIOExc(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, ioExcClass, message );
}

void throwOperationInProgressException(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, OperationInProgressException, message);
}

void throwNullPointerException(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, NullPointerException, message );
}

void throwIllegalArgumentsExc(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, IllegalArgumentException, message);
}

void throwIllegalStateException(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, IllegalStateException, message);
}

void throwFileNotFoundExc(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, FileNotFoundException, message);
}

int getFD(JNIEnv * env, jobject fd) {
	if (fd == NULL) {
		return -1;
	}
	return (int) (*env) -> GetIntField(env, fd, fdIntField);
}


void setFD(JNIEnv * env, jobject fd, int value) {
	if (fd == NULL) {
		return;
	}

	(*env) -> SetIntField(env, fd, fdIntField, (jint) value);
}


intptr_t getHandle(JNIEnv * env, jobject fd) {
	if (fd == NULL || fdHandleField == NULL) {
		return -1;
	}
	return (intptr_t) (*env) -> GetLongField(env, fd, fdHandleField);
}

jbyteArray getAddressFromInetAddress(JNIEnv * env, jobject address) {
	if (address == NULL) {
		return NULL;
	}
	return (jbyteArray) (*env)->CallObjectMethod(env, address, InetAddress_getAddress);
}

jobject getInetSocketAddress(JNIEnv * env, jobject inetaddress, jint port) {
	if (inetaddress == NULL || port < 0 || port > 0xffff) {
		return NULL;
	}

	return (*env)->NewObject(env, InetSocketAddress, InetSocketAddressConstructor, inetaddress, port);
}

jobject getInetAddressFromByteArray(JNIEnv * env, jbyteArray array) {
	if (array == NULL) {
		return NULL;
	}

	jobject inet = (*env)->CallStaticObjectMethod(env, InetAddress, InetAddress_getByAddress, array);

	if ((*env)->ExceptionCheck(env)) {
		(*env)->ExceptionClear(env);
	}

	return inet;
}

jobject getAddressFromInetSocketAddress(JNIEnv * env, jobject address) {
	if (address == NULL) {
		return NULL;
	}

	return (*env)->CallObjectMethod(env, address, InetSocketAddress_getAddress);
}

jint getPortFromInetSocketAddress(JNIEnv * env, jobject address) {
	if (address == NULL) {
		return -1;
	}

	return (*env)->CallIntMethod(env, address, InetSocketAddress_getPort);
}


bool isStatic(JNIEnv *env, jobject field) {
	return (*env)->CallIntMethod(env, field, Field_getModifier) & 0x00000008 == 0x00000008;
}

jclass getDeclareingClass(JNIEnv *env, jobject field) {
	return (jclass) (*env)->CallObjectMethod(env, field, Field_getDeclaringClass);
}

jobject new_iterator(JNIEnv * env, jobject collection) {
	if (collection == NULL) {
		return NULL;
	}

	return (*env)->CallObjectMethod(env, collection, Collection_iterator);
}

jobject iterator_next(JNIEnv * env, jobject iterator) {
	if (iterator == NULL) {
		return NULL;
	}

	jboolean hasNext = (*env)->CallBooleanMethod(env, iterator, Iterator_hasNext);

	if (!hasNext) {
		return NULL;
	}

	return (*env)->CallObjectMethod(env, iterator, Iterator_next);
}


bool collection_add(JNIEnv * env, jobject collection, jobject value) {
	if (collection == NULL) {
		return true;
	}

	(*env)->CallBooleanMethod(env, collection, Collection_add, value);
	if ((*env)->ExceptionCheck(env)) {
		return false;
	}

	return true;
}


void collection_clear(JNIEnv * env, jobject collection) {
	if (collection == NULL) {
		return;
	}

	(*env)->CallVoidMethod(env, collection, Collection_clear);
}

static_assert(sizeof(jchar) <= sizeof(wchar_t), "jchar does not fit into wchar_t");

wchar_t * toWCharsMalloc(JNIEnv * env, jstring str) {
	if (str == NULL) {
		throwNullPointerException(env, "toWCharsMalloc");
		return false;
	}

	jsize len = (*env)->GetStringLength(env, str);


	wchar_t * res = malloc(sizeof(wchar_t) * (len+1));

	if (res == NULL) {
		throwOOM(env, "malloc");
		return NULL;
	}

	if (!toWChars(env, str, res)) {
		free((void*) res);
		return NULL;
	}

	return res;
}

bool toWChars(JNIEnv * env, jstring str, wchar_t* wchars) {
	if (str == NULL || wchars == NULL) {
		throwNullPointerException(env, "toWChars");
		return false;
	}

	jsize len = (*env)->GetStringLength(env, str);

	if (len <= 0) {
		wchars[0] = 0;
		return true;
	}

	const jchar* jchars = (*env)->GetStringChars(env, str, NULL);
	if (jchars == NULL) {
		throwOOM(env, "GetStringChars");
		return false;
	}


	wchars[len] = 0;

	if (sizeof(wchar_t) == sizeof(jchar)) {
		memcpy((void*) wchars, (void*)jchars, len*sizeof(jchar));
	} else {
		for (jsize i = 0; i < len; i++) {
			wchars[i] = (wchar_t) jchars[i];
		}
	}

	(*env)->ReleaseStringChars(env, str, jchars);

	return true;
}

void fromWCharCopy(jchar* to, wchar_t* from, jsize len) {
	if (len <= 0) {
		return;
	}

	if (sizeof(wchar_t) == sizeof(jchar)) {
		memcpy((void*) to, (void*) from, len*sizeof(jchar));
	} else {
		for (jsize i = 0; i < len; i++) {
			//TODO
			//This will scuff 4 byte unicode, i dont care for now...
			to[i] = (jchar) from[i];
		}
	}
}

jstring fromWChars(JNIEnv * env, wchar_t* wchars) {
	if (wchars == NULL) {
		throwNullPointerException(env, "fromWChars");
		return NULL;
	}

	jsize len = 0;
	while(true) {
		if (wchars[len] == 0) {
			break;
		}

		len++;
	}


	if (len > 128) {
		jchar* ptr = (jchar*) malloc(sizeof(jchar) * len);
		if (ptr == NULL) {
			throwOOM(env, "malloc");
			return NULL;
		}

		fromWCharCopy(ptr, wchars, len);

		jstring nstring = (*env)->NewString(env, (const jchar*) ptr, len);
		free((void*) ptr);
		return nstring;
	} else {
		jchar jchars[len];
		fromWCharCopy(jchars, wchars, len);
		return (*env)->NewString(env, (const jchar*) jchars, len);
	}
}

jobject new_array_list(JNIEnv * env) {
	return (*env)->NewObject(env, ArrayList, ArrayListConstructor);
}

int getEnumOrdinal(JNIEnv * env, jobject e) {
	if (e == NULL) {
		return -1;
	}

	return (int) (*env) -> CallIntMethod(env, e, enumOrdinal);
}

bool setStringField(JNIEnv  * env, jobject obj, jfieldID field, const char * str) {
	if (obj == NULL) {
		throwNullPointerException(env, "obj");
		return false;
	}

	if (str == NULL) {
		(*env)->SetObjectField(env, obj, field, NULL);
		return true;
	}

	jstring jstr = (*env)->NewStringUTF(env, str);
	if (jstr == NULL) {
		throwOOM(env, "NewStringUTF");
		return false;
	}

	(*env)->SetObjectField(env, obj, field, jstr);

	return true;
}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIEnv * env;

	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_1) != JNI_OK) {
		return JNI_ABORT;
	}

	if (!jstub_init(env)) {
		jstub_destroy(env);
		return JNI_ABORT;
	}

	if (!makeRefs(env)) {
		delRefs(env);
		return JNI_ABORT;
	}

    return JNI_VERSION_1_1;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {

	JNIEnv * env;
	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_1) != JNI_OK) {
		return;
	}

	jstub_destroy(env);
	delRefs(env);
}



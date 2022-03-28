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
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef _WIN32
#undef _WIN32_WINNT
//Windows Vista (needed for symlinks)
#define _WIN32_WINNT 0x0600
#endif

#ifndef COMMON_H_
#define COMMON_H_




jclass StatClass;
jmethodID StatClassConstructor;
jfieldID StatClass_dev;
jfieldID StatClass_ino;
jfieldID StatClass_mode;
jfieldID StatClass_nlink;
jfieldID StatClass_uid;
jfieldID StatClass_gid;
jfieldID StatClass_rdev;
jfieldID StatClass_size;
jfieldID StatClass_size;
jfieldID StatClass_blksize;
jfieldID StatClass_blocks;
jfieldID StatClass_atime;
jfieldID StatClass_mtime;
jfieldID StatClass_ctime;

jclass Win32FileAttributeData;
jmethodID Win32FileAttributeDataConstructor;
jfieldID Win32FileAttributeData_dwFileAttributes;
jfieldID Win32FileAttributeData_nFileSizeLow;
jfieldID Win32FileAttributeData_nFileSizeHigh;
jfieldID Win32FileAttributeData_ftLastAccessTimeLow;
jfieldID Win32FileAttributeData_ftLastAccessTimeHigh;
jfieldID Win32FileAttributeData_ftLastWriteTimeHigh;
jfieldID Win32FileAttributeData_ftLastWriteTimeLow;
jfieldID Win32FileAttributeData_ftCreationTimeHigh;
jfieldID Win32FileAttributeData_ftCreationTimeLow;


jclass PollFD;
int PollFD_PollEvent_values_size;
jobject* PollFD_PollEvent_values;
jfieldID PollFD_fd;
jfieldID PollFD_events;
jfieldID PollFD_revents;

jclass Sockaddr;
jmethodID SockaddrConstructor;
jfieldID Sockaddr_addressFamily;
jfieldID Sockaddr_address;

jclass Msghdr;
jfieldID Msghdr_msg_iov;
jfieldID Msghdr_msg_control;
jfieldID Msghdr_msg_controllen;
jfieldID Msghdr_msg_name;
jfieldID Msghdr_complete;
jfieldID Msghdr_truncated;
jfieldID Msghdr_controlDataTruncated;
jfieldID Msghdr_outOfBand;
jfieldID Msghdr_errQueue;



jclass Iovec;
jfieldID Iovec_payload;
jfieldID Iovec_off;
jfieldID Iovec_len;
jfieldID Iovec_size;

jclass Cmsghdr;
jmethodID CmsghdrConstructor;
jfieldID Cmsghdr_payload;
jfieldID Cmsghdr_cmsg_type;
jfieldID Cmsghdr_cmsg_level;

jclass GUID_Class;
jmethodID GUID_constructor;
jfieldID GUID_data1;
jfieldID GUID_data2;
jfieldID GUID_data3;
jfieldID GUID_data4;

jclass SpDeviceInfoData;
jfieldID SpDeviceInfoData_cbSize;
jfieldID SpDeviceInfoData_InterfaceClassGuid;
jfieldID SpDeviceInfoData_DevInst;
jfieldID SpDeviceInfoData_ptr;

jclass SpDeviceInterfaceData;
jmethodID SpDeviceInterfaceData_constructor;
jfieldID SpDeviceInterfaceData_cbSize;
jfieldID SpDeviceInterfaceData_InterfaceClassGuid;
jfieldID SpDeviceInterfaceData_flags;
jfieldID SpDeviceInterfaceData_InterfaceClassGuid;
jfieldID SpDeviceInterfaceData_ptr;

jclass JNINativeMemory;
jfieldID JNINativeMemory_ptr;

jclass Utsname;
jmethodID Utsname_constructor;
jfieldID Utsname_sysname;
jfieldID Utsname_nodename;
jfieldID Utsname_release;
jfieldID Utsname_version;
jfieldID Utsname_machine;


jclass RegData;
jmethodID RegData_Object;
jmethodID RegData_Int;
jmethodID RegData_Long;
jobject* RegData_types;
int RegData_types_size;

jclass String_Class;



jint unboxInt(JNIEnv * env, jobject box);
jlong unboxLong(JNIEnv * env, jobject box);
jshort unboxShort(JNIEnv * env, jobject box);
jboolean unboxBool(JNIEnv * env, jobject box);
jchar unboxChar(JNIEnv * env, jobject box);
jbyte unboxByte(JNIEnv * env, jobject box);
jdouble unboxDouble(JNIEnv * env, jobject box);
jfloat unboxFloat(JNIEnv * env, jobject box);






bool setStringField(JNIEnv  * env, jobject obj, jfieldID field, const char * str);

/*
 * get int fd from FileDescriptor object or -1 if null.
 */
int getFD(JNIEnv * env, jobject fd);

void setFD(JNIEnv * env, jobject fd, int value);

jobject getInetAddressFromByteArray(JNIEnv * env, jbyteArray array);

jobject getInetSocketAddress(JNIEnv * env, jobject inetaddress, jint port);

jobject getAddressFromInetSocketAddress(JNIEnv * env, jobject address);

jint getPortFromInetSocketAddress(JNIEnv * env, jobject address);

jbyteArray getAddressFromInetAddress(JNIEnv * env, jobject address);

intptr_t getHandle(JNIEnv * env, jobject fd);

bool isStatic(JNIEnv *env, jobject field);

jclass getDeclareingClass(JNIEnv * env, jobject field);

jobject new_iterator(JNIEnv * env, jobject collection);

jobject iterator_next(JNIEnv * env, jobject iterator);

void collection_add(JNIEnv * env, jobject collection, jobject value);

void collection_clear(JNIEnv * env, jobject collection);

wchar_t * toWCharsMalloc(JNIEnv * env, jstring str);

bool toWChars(JNIEnv * env, jstring str, wchar_t* wchars);

jstring fromWChars(JNIEnv * env, wchar_t* wchars);

jobject new_array_list(JNIEnv * env);


int getEnumOrdinal(JNIEnv * env, jobject e);

/*
 * throw illegal argument exception with given message.
 */
void throwIllegalArgumentsExc(JNIEnv * env, const char* message);

void throwIllegalStateException(JNIEnv * env, const char* message);

/*
 * Throw unknown error exception
 */
void throwUnknownError(JNIEnv * env, jlong code);

void throwMutexAbandonedException(JNIEnv * env, jlong handle);

/**
 * throw bad fd exception
 */
void throwBadFileDescriptor(JNIEnv * env);

void throwOOM(JNIEnv * env, const char* message);

void throwIOExc(JNIEnv * env, const char* message);

void throwOperationInProgressException(JNIEnv * env, const char* message);

void throwNullPointerException(JNIEnv * env, const char* message);

void throwUnsupportedExc(JNIEnv * env, const char* message);

void throwFSReadOnly(JNIEnv * env);

void throwBindException(JNIEnv * env, const char* message);

void throwConnectException(JNIEnv * env, const char* message);

void throwSocketTimeoutException(JNIEnv * env, const char* message);

void throwQuotaExceededException(JNIEnv * env, const char* file, const char* other, const char* reason);

void throwFSLoop(JNIEnv * env, const char* file);

void throwNotLinkException(JNIEnv * env, const char* file, const char* other, const char* reason);

void throwFSAccessDenied(JNIEnv * env, const char* file, const char* other, const char* reason);

void throwPermissionDeniedException(JNIEnv * env, const char* file, const char* reason);

void throwShareingViolationException(JNIEnv * env, const char* file, const char* other, const char* reason);

void throwFileAlreadyExistsExc(JNIEnv * env, const char* file, const char* other, const char* reason);

void throwInvalidPath(JNIEnv * env, const char* path, const char* reason);

void throwNotDirectoryException(JNIEnv * env, const char* path);

void throwFileNotFoundExc(JNIEnv * env, const char* message);

#endif /* COMMON_H_ */

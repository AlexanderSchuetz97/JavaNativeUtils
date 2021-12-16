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
#include <jni.h>
#include <stdint.h>
#include <stdbool.h>

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




/*
 * Throw unknown error exception
 */
void unknownError(JNIEnv * env, jlong code);

/**
 * throw bad fd exception
 */
void badFileDescriptor(JNIEnv * env);

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

/*
 * throw illegal argument exception with given message.
 */
void throwIllegalArgumentsExc(JNIEnv * env, const char* message);

void throwIllegalStateException(JNIEnv * env, const char* message);

int getEnumOrdinal(JNIEnv * env, jobject e);

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

void throwFSAccessDenied(JNIEnv * env, const char* file, const char* other, const char* reason);

void throwShareingViolationException(JNIEnv * env, const char* file, const char* other, const char* reason);

void throwFileAlreadyExistsExc(JNIEnv * env, const char* file, const char* other, const char* reason);

void throwInvalidPath(JNIEnv * env, const char* path, const char* reason);

void throwNotDirectoryException(JNIEnv * env, const char* path);

void throwFileNotFoundExc(JNIEnv * env, const char* message);

#endif /* COMMON_H_ */

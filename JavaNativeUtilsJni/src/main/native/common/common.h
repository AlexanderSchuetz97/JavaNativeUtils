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
#ifdef _WIN32
#undef _WIN32_WINNT
//Windows Vista (needed for symlinks)
#define _WIN32_WINNT 0x0600
#include <winsock2.h>
#include <windows.h>
#endif

#include "jnigenerator.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>



#ifndef COMMON_H_
#define COMMON_H_

jlong jget_JNINativeMemory_ptr(JNIEnv * env, jobject inst);

jint unboxInt(JNIEnv * env, jobject box);
jlong unboxLong(JNIEnv * env, jobject box);
jshort unboxShort(JNIEnv * env, jobject box);
jboolean unboxBool(JNIEnv * env, jobject box);
jchar unboxChar(JNIEnv * env, jobject box);
jbyte unboxByte(JNIEnv * env, jobject box);
jdouble unboxDouble(JNIEnv * env, jobject box);
jfloat unboxFloat(JNIEnv * env, jobject box);

jobjectArray jStringArray(JNIEnv * env, jsize size);

/*
 * get int fd from FileDescriptor object or -1 if null.
 */
int getFD(JNIEnv * env, jobject fd);

void setFD(JNIEnv * env, jobject fd, int value);

intptr_t getHandle(JNIEnv * env, jobject fd);

bool isStatic(JNIEnv *env, jobject field);

jclass getDeclareingClass(JNIEnv * env, jobject field);

wchar_t * toWCharsMalloc(JNIEnv * env, jstring str);

bool toWChars(JNIEnv * env, jstring str, wchar_t* wchars);

jstring fromWChars(JNIEnv * env, wchar_t* wchars);

#endif /* COMMON_H_ */

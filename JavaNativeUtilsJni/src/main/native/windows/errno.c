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

#include "../common/jni/eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil.h"
#include "../common/common.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    strerror_s
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_strerror_1s
  (JNIEnv * env, jobject inst, jint code) {
	char buffer[513];

	//just to be safe
	buffer[512] = 0;

	if (strerror_s(buffer, 512, code) == -1) {
		//Should never ever happen tbh
		return (*env) -> NewStringUTF(env, "strerror_r needs more than 512 bytes or unknown errno");
	}

	return (*env) -> NewStringUTF(env, buffer);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    FormatMessageA
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil__1FormatMessageA
  (JNIEnv * env, jclass klaas, jint code, jint lang) {
    char* buffer = NULL;

	DWORD result = FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		code,
		(DWORD) lang,
        (LPSTR) &buffer,
		0,
		NULL);

    if (result != 0 && buffer != NULL) {
        jstring str = (*env) -> NewStringUTF(env, buffer);
        LocalFree((void*)buffer);
        return str;
    }

    if (buffer != NULL) {
        LocalFree((void*)buffer);
    }

	DWORD err = GetLastError();

	if (err == ERROR_MR_MID_NOT_FOUND || err == ERROR_MUI_FILE_NOT_LOADED || err == ERROR_MUI_FILE_NOT_FOUND || err == ERROR_RESOURCE_LANG_NOT_FOUND) {
		//ERROR_MR_MID_NOT_FOUND: code parameter is garabge.
		//ERROR_MUI_FILE_NOT_LOADED or ERROR_MUI_FILE_NOT_FOUND or ERROR_RESOURCE_LANG_NOT_FOUND: language parameter is garbage
		//We can go past the loop and straight into the fallback in this case.
		goto fallback;
	}

	// Shitty version of Windows handling
	// they do not support FORMAT_MESSAGE_ALLOCATE_BUFFER
    DWORD size = 0;
    while(size < 0xFFFF) {
        size+=1024;
        buffer = malloc(size+1);
        if (buffer == NULL) {
            jthrowCC_OutOfMemoryError_1(env, "malloc");
            return NULL;
        }
        memset((void*) buffer, 0, size+1);

        result = FormatMessageA(
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ARGUMENT_ARRAY,
                NULL,
                code,
                (DWORD) lang,
                (LPSTR) buffer,
                size,
                NULL);

        if (result == 0) {
        	err = GetLastError();
            free((void*)buffer);
            continue;
        }

        jstring str = (*env) -> NewStringUTF(env, buffer);
        free((void*)buffer);
        return str;
    }

	//FALLBACK BEGINS HERE
	fallback:;

	int cnt = snprintf(NULL, 0, "Failed to call FormatMessageA with dwMessageId='%llu' dwLanguageId='%llu' because of GetLastError='%llu'", (uint64_t) code, (uint64_t) lang, (uint64_t) err);
	if (cnt <= 0 || cnt > 0xFFFF) {
		//Probably cannot happen; I don't know what anything better to do in this case.
		jthrowCC_IllegalStateException_1(env, "snprintf did not return a valid number of characters");
		return NULL;
	}

	buffer = malloc(cnt+1);


	memset((void*) buffer, 0, cnt+1);
	if (buffer == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "malloc");
		return NULL;
	}


	int cnt2 = snprintf(buffer, cnt, "Failed to call FormatMessageA with dwMessageId='%llu' dwLanguageId='%llu' because of GetLastError='%llu'", (uint64_t) code, (uint64_t) lang, (uint64_t) err);
	if (cnt2 != cnt) {
		//Probably cannot happen; I don't know what anything better to do in this case.
		free(buffer);
		jthrowCC_IllegalStateException_1(env, "snprintf did not return a valid number of characters");
		return NULL;
	}

	jstring str = (*env) -> NewStringUTF(env, buffer);
	free((void*)buffer);
    return str;
}


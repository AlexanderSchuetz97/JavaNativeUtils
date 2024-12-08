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


#include "../common/jni/eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil.h"
#include "../common/common.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    open
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_open__Ljava_lang_String_2I
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
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    open
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_open__Ljava_lang_String_2II
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
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    close
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_close
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
            default:
                jthrow_UnknownNativeErrorException_1(env, (jlong) err);
        }
    }
}
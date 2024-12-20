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

#ifndef __USE_FILE_OFFSET64
#define __USE_FILE_OFFSET64
#endif
#ifndef __USE_LARGEFILE64
#define __USE_LARGEFILE64
#endif
#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif
#include <sys/mman.h>

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


jint handle_read_error(JNIEnv * env, int err) {
    switch(err) {
#if EAGAIN != EWOULDBLOCK
        case(EWOULDBLOCK):
#endif
        case(EAGAIN):
            return 0;
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
        default:
            jthrow_UnknownNativeErrorException_1(env, err);
            return -1;
    }
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    read
 * Signature: (IJI)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_read__IJI
        (JNIEnv * env, jobject inst, jint fd, jlong ptr, jint len) {
    void * buf = (void *) (uintptr_t) ptr;
    if (buf == NULL) {
        jthrowCC_NullPointerException_1(env, "buffer");
        return -1;
    }

    if (len < 0) {
        jthrowCC_IllegalArgumentException_1(env, "length");
        return -1;
    }

    while(true) {
        ssize_t r = read(fd, buf, len);
        if (r == 0) {
            return -1;
        }

        if (r > 0) {
            return (jint) r;
        }

        int err = errno;
        if (err == EINTR) {
            continue;
        }

        return handle_read_error(env, err);
    }
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    read
 * Signature: (I[BII)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_read__I_3BII
        (JNIEnv * env, jobject inst, jint fd, jbyteArray jbuf, jint off, jint len) {
    if (jbuf == NULL) {
        jthrowCC_NullPointerException_1(env, "buffer");
        return -1;
    }

    jsize alen = (*env)->GetArrayLength(env, jbuf);

    if (off < 0 || len < 0 || len+off > alen) {
        jthrowCC_IllegalArgumentException_1(env, "offset+lengths");
        return -1;
    }

    void* data = (*env)->GetByteArrayElements(env, jbuf, NULL);
    if (data == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetByteArrayElements");
        return -1;
    }

    while(true) {
        ssize_t r = read(fd, data+off, len);

        if (r == 0) {
            //EOF
            (*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_ABORT);
            return -1;
        }

        if (r > 0) {
            (*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_OK);
            return r;
        }

        int err = errno;
        if (err == EINTR) {
            continue;
        }

        (*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_ABORT);

        return handle_read_error(env, err);
    }
}



jint handle_write_error(JNIEnv * env, int err) {
    switch(err) {
#if EAGAIN != EWOULDBLOCK
        case(EWOULDBLOCK):
#endif
        case(EAGAIN):
            return 0;
        case(EBADF):
            jthrow_InvalidFileDescriptorException(env);
            return -1;
        case(EDESTADDRREQ):
            jthrowCC_IllegalStateException_1(env, "file descriptor refers to a datagram socket for which a peer address has not been set using connect.");
            return -1;
        case(EDQUOT):
            jthrowCC_QuotaExceededException_1(env, NULL, NULL, "The user's quota of disk blocks on the filesystem containing the file referred to by the file descriptor has been exhausted.");
            return -1;
        case(EFBIG):
            jthrowC_IOException_1(env, "An attempt was made to write a file that exceeds the implementation-defined maximum file size or the process's file size limit, or to write at a position past the maximum allowed offset.");
            return -1;
        case EINVAL:
            jthrowCC_IllegalArgumentException_1(env, "file descriptor is unsuitable for writing or the file/buffer position/length is not properly aligned.");
            return -1;
        case EIO:
            jthrowC_IOException_1(env, "I/O error");
            return -1;
        case EPERM:
            jthrowCC_AccessDeniedException_1(env, NULL, NULL, "Operation was prevented by a file seal");
            return -1;
        case EPIPE:
            jthrowC_IOException_1(env, "Broken pipe");
            return -1;
        case ENOSPC:
            jthrowC_IOException_1(env, "The device containing the file referred to by fd has no room for the data.");
            return -1;
        case EISDIR:
            jthrowCC_IllegalArgumentException_1(env, "file descriptor refers to a directory");
            return -1;
        default:
            jthrow_UnknownNativeErrorException_1(env, err);
            return -1;
    }
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    write
 * Signature: (IJI)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_write__IJI
        (JNIEnv * env, jobject inst, jint fd, jlong jptr, jint len) {
    void *buf = (void*) (uintptr_t) jptr;
    if (buf == NULL) {
        jthrowCC_NullPointerException_1(env, "buffer");
        return -1;
    }

    if (len < 0) {
        jthrowCC_IllegalArgumentException_1(env, "len");
        return -1;
    }

    while(true) {
        ssize_t r = write(fd, buf, len);
        if (r >= 0) {
            return (jint) r;
        }

        int err = errno;
        if (err == EINTR) {
            continue;
        }

        return handle_write_error(env, err);
    }
}



/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    write
 * Signature: (I[BII)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_write__I_3BII
        (JNIEnv * env, jobject inst, jint fd, jbyteArray jbuf, jint off, jint len) {
    if (jbuf == NULL) {
        jthrowCC_NullPointerException_1(env, "buffer");
        return -1;
    }

    jsize alen = (*env)->GetArrayLength(env, jbuf);

    if (off < 0 || len < 0 || len+off > alen) {
        jthrowCC_IllegalArgumentException_1(env, "offset+lengths");
        return -1;
    }

    while(true) {
        void* data = (*env)->GetByteArrayElements(env, jbuf, NULL);

        ssize_t r = write(fd, data+off, len);

        if (r >= 0) {
            (*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_OK);
            return (jint) r;
        }

        int err = errno;
        (*env)->ReleaseByteArrayElements(env, jbuf, data, JNI_ABORT);

        if (err == EINTR) {
            continue;
        }

        return handle_write_error(env, err);

    }
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    _munmap
 * Signature: (JJ)J
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil__1munmap
        (JNIEnv * env, jclass clazz, jlong ptr, jlong size) {
    void * vptr = (void *) (uintptr_t) ptr;
    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return;
    }

    int res = munmap(vptr, (size_t) size);

    if (res != -1) {
        return;
    }

    int err = errno;
    if (err == EINVAL) {
        jthrowCC_IllegalArgumentException_1(env, "alignment of size/ptr is wrong");
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, err);
}

#ifndef __OFF64_T_TYPE
#if defined(__NetBSD__) | defined(__OpenBSD__) | defined(__APPLE__)
//Why?
#define __OFF64_T_TYPE int64_t
#else
#define __OFF64_T_TYPE off64_t
#endif

#endif

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    _mmap
 * Signature: (IJIZZJ)V
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil__1mmap
        (JNIEnv * env, jclass clazz, jint fd, jlong length, jint flags, jboolean read, jboolean write, jlong offset) {

    int prot;
    if (read && write) {
        prot = PROT_READ | PROT_WRITE;
    } else if (read) {
        prot = PROT_READ;
    } else if (write) {
        prot = PROT_WRITE;
    } else {
        prot = PROT_NONE;
    }

    void * res = mmap(NULL, (size_t) length, prot, flags, fd, (__OFF64_T_TYPE) offset);
    if (res != MAP_FAILED) {
        return (jlong) (uintptr_t) res;
    }

    int err = errno;
    switch(err) {
        case(EACCES):
            jthrowCC_IllegalStateException_1(env, "FD is incompatible with the requested flags.");
            return -1;
        case(EAGAIN):
            jthrowCC_IllegalArgumentException_1(env, "The file has been locked, or too much memory has been locked");
            return -1;
        case(EBADF):
            jthrow_InvalidFileDescriptorException(env);
            return -1;
        case(EINVAL):
            jthrowCC_IllegalArgumentException_1(env, "alignment of arguments is invalid");
            return -1;
        case(ENFILE):
            jthrowCC_QuotaExceededException_1(env, NULL, NULL, "The system-wide limit on the total number of open files has been reached.");
            return -1;
        case(ENODEV):
            jthrowCC_UnsupportedOperationException_1(env, "The underlying filesystem of the specified file does not support memory mapping.");
            return -1;
        case(ENOMEM):
            jthrowCC_OutOfMemoryError_1(env, "not enough memory to create mapping or the maximum number of memory mappings has been reached");
            return -1;
        case(EOVERFLOW):
            jthrowCC_OutOfMemoryError_1(env, "mapping is too large for 32bit architecture");
            return -1;
        case(EPERM):
            jthrowCC_AccessDeniedException_1(env, NULL, NULL, "The operation was prevented by a file seal or the MAP_HUGETLB was present and the process is not privileged.");
            return -1;
        case(ETXTBSY):
            jthrowCC_IllegalStateException_1(env, "MAP_DENYWRITE was set but the object specified by fd is open for writing.");
            return -1;
        default:
            jthrow_UnknownNativeErrorException_1(env, err);
            return -1;
    }
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    _msync
 * Signature: (JJJZ)J
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil__1msync
        (JNIEnv * env, jclass clazz, jlong ptr, jlong off, jlong len, jboolean invalidate) {
    void * vptr = (void *) (uintptr_t) ptr;
    if (vptr == NULL) {
        jthrowCC_NullPointerException_1(env, "ptr");
        return;
    }

    vptr+=off;
    int flags = MS_SYNC;

    if (invalidate) {
        flags |= MS_INVALIDATE;
    }

    if (msync(vptr, len, flags) == 0) {
        return;
    }

    int err = errno;

    switch(err) {
        case(EBUSY):
            jthrowCC_AccessDeniedException_1(env, NULL, NULL, "cant invalidate region due to memory lock");
            return;
        case(EINVAL):
            jthrowCC_IllegalArgumentException_1(env, "ptr+off is not a multiple of PAGESIZE");
            return;
        case(ENOMEM):
            jthrowCC_IllegalStateException_1(env, "The indicated memory (or part of it) was not mapped.");
            return;
        default:
            jthrow_UnknownNativeErrorException_1(env, err);
            return;
    }
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    lseek
 * Signature: (IJLeu/aschuetz/nativeutils/api/PosixNativeUtil/lseek_whence;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_lseek
        (JNIEnv * env, jobject inst, jint fd, jlong off, jobject jwhence) {
    int whence;
    int ordinal = jenum_ordinal(env, jwhence);
    switch(ordinal) {
        case(0):
            whence = SEEK_SET;
            break;
        case(1):
            whence = SEEK_CUR;
            break;
        case(2):
            whence = SEEK_END;
            break;
        default:
            jthrowCC_IllegalArgumentException_1(env, "whence");
            return -1;
    }

    off_t res = lseek((int) fd, (off_t) off, whence);
    if (res == -1) {
        int err = errno;
        switch(err) {
            case(ESPIPE):
            case(EBADF):
                jthrow_InvalidFileDescriptorException(env);
                return -1;
            case(EINVAL):
                jthrowCC_IOException_1(env, "the resulting file offset would be negative, or beyond the end of a seekable device.");
                return -1;
            case(EOVERFLOW):
                jthrowCC_IOException_1(env, "The resulting file offset cannot be represented in a 64 bit number");
                return -1;
            default:
                jthrow_UnknownNativeErrorException_1(env, err);
                return -1;
        }
    }

    return (jlong) res;
}
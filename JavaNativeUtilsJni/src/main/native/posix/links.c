#include "../common/jni/eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil.h"
#include "../common/common.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    unlink
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_unlink
(JNIEnv *env , jobject isnt, jstring jpath) {

    if (jpath == NULL) {
        jthrowCC_IllegalArgumentException_1(env, "path is null");
        return;
    }

    const char* pathString = (*env)->GetStringUTFChars(env, jpath, NULL);
    if (pathString == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
        return;
    }

    int res = unlink(pathString);

    if (res == 0) {
        (*env)->ReleaseStringUTFChars( env, jpath, pathString);
        return;
    }

    int err = errno;
    switch (err) {
        case EACCES:
            jthrowCC_AccessDeniedException_1(env, pathString, NULL, "Write access to the directory containing path is not allowed for the process's effective UID, or one of the directories in path did not allow search permission, or the directory containing path has the sticky bit S_ISVTX set and the process's effective UID is neither the UID of the file to be deleted nor that of the directory containing it");
            break;
        case EBUSY:
            jthrowCC_ResourceBusyException(env, "The file pathname cannot be unlinked because it is being used by the system or another process");
            break;
        case EIO:
            jthrowC_IOException_1(env, "An I/O error occurred.");
            break;
        case EISDIR:
            jthrowCC_FileIsDirectoryException(env, "path refers to a directory");
            break;
        case ELOOP:
            jthrowCC_FileSystemLoopException(env, "Too many symbolic links were encountered in translating path");
            break;
        case ENAMETOOLONG:
            jthrowCC_IllegalArgumentException_1(env, "path was too long");
            break;
        case ENOENT:
            jthrowCC_FileNotFoundException_1(env, "A component in path does not exist or is a dangling symbolic link, or pathname is empty.");
            break;
        case ENOMEM:
            jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available.");
            break;
        case ENOTDIR:
            jthrowCC_NotDirectoryException(env, "A component used as a directory in path is not, in fact, a directory.");
            break;
        case EPERM:
            jthrowCC_PermissionDeniedException_1(env, pathString,
             "The system does not allow unlinking of directories, "
                 "or unlinking of directories requires privileges that the calling process doesn't have, "
                 "or the the filesystem does not allowing unlinking of files, "
                 "or the directory containing path has the sticky bit S_ISVTX set and the process's effective UID is neither the UID of the file to be deleted "
                     "nor that of the directory containing it,"
                 "or the file to be unlinked is marked immutable or append-only.");
            break;
        case EROFS:
            jthrow_ReadOnlyFileSystemException(env);
            break;
        default:
            jthrow_UnknownNativeErrorException_1(env, err);
            break;
    }

    (*env)->ReleaseStringUTFChars( env, jpath, pathString);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    symlink
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_symlink
        (JNIEnv * env, jobject inst, jstring target, jstring linkpath) {

    if (linkpath == NULL) {
        jthrowCC_IllegalArgumentException_1(env, "linkpath is null");
        return;
    }

    if (target == NULL) {
        jthrowCC_IllegalArgumentException_1(env, "target is null");
        return;
    }

    const char* linkPathString = (*env)->GetStringUTFChars(env, linkpath, NULL);
    if (linkPathString == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
        return;
    }

    const char* targetString = (*env)->GetStringUTFChars(env, target, NULL);
    if (targetString == NULL) {
        (*env)->ReleaseStringUTFChars( env, linkpath, linkPathString);
        jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
        return;

    }

    int res = symlink(targetString, linkPathString);


    if (res == 0) {
        (*env)->ReleaseStringUTFChars(env, linkpath, linkPathString);
        (*env)->ReleaseStringUTFChars(env, target, targetString);
        return;
    }

    int err = errno;
    switch(err) {
        case (EACCES):
            jthrowCC_AccessDeniedException_1(env, linkPathString, NULL, "Write access to the directory containing linkpath is denied, or one of the directories in the path prefix of linkpath did not allow search permission.");
            break;
        case (EDQUOT):
            jthrowCC_QuotaExceededException_1(env, linkPathString, targetString, "The user's quota of resources on the filesystem has been exhausted. The resources could be inodes or disk blocks, depending on the filesystem implementation.");
            break;
        case (EEXIST):
            jthrowCC_FileAlreadyExistsException_1(env, linkPathString, NULL, "linkpath already exists.");
            break;
            //EFAULT shouldnt happen since both args point to the stack...
        case (EIO):
            jthrowC_IOException_1(env, "An I/O error occurred.");
            break;
        case (ELOOP):
            jthrowCC_FileSystemLoopException(env, linkPathString);
            break;
        case (ENAMETOOLONG):
            if (strlen(linkPathString) >= strlen(targetString)) {
                jthrowCC_InvalidPathException(env, linkPathString, "target or linkpath was too long.");
            } else {
                jthrowCC_InvalidPathException(env, targetString, "target or linkpath was too long.");
            }
            break;
        case (ENOENT):
            jthrowCC_InvalidPathException(env, linkPathString, "A directory component in linkpath does not exist or is a dangling symbolic link, or target or linkpath is an empty string.");
            break;
        case (ENOMEM):
            jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available.");
            break;
        case (ENOSPC):
            jthrowC_IOException_1(env, "The device containing the file has no room for the new directory entry.");
            break;
        case (ENOTDIR):
            jthrowCC_InvalidPathException(env, linkPathString, "A component used as a directory in linkpath is not, in fact, a directory.");
            break;
        case (EPERM):
            jthrowCC_UnsupportedOperationException_1(env, "The filesystem containing linkpath does not support the creation of symbolic links.");
            break;
        case (EROFS):
            jthrow_ReadOnlyFileSystemException(env);
            break;
        default:
            jthrow_UnknownNativeErrorException_1(env, err);
            break;
    }

    (*env)->ReleaseStringUTFChars(env, linkpath, linkPathString);
    (*env)->ReleaseStringUTFChars(env, target, targetString);
}
#include "../common/common.h"
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

static jobject fillStat(JNIEnv * env, struct stat* theStat) {
    jobject myStat = jnew_Stat(env);
    if (myStat == NULL) {
        return NULL;
    }

    jset_Stat_dev(env, myStat, (jlong) theStat->st_dev);
    jset_Stat_ino(env, myStat, (jlong) theStat->st_ino);
    jset_Stat_mode(env, myStat, (jlong) theStat->st_mode);
    jset_Stat_nlink(env, myStat, (jlong) theStat->st_nlink);
    jset_Stat_uid(env, myStat, (jlong) theStat->st_uid);
    jset_Stat_gid(env, myStat, (jlong) theStat->st_gid);
    jset_Stat_rdev(env, myStat, (jlong) theStat->st_rdev);
    jset_Stat_size(env, myStat, (jlong) theStat->st_size);
    jset_Stat_blksize(env, myStat, (jlong) theStat->st_blksize);
    jset_Stat_blocks(env, myStat, (jlong) theStat->st_blocks);
    jset_Stat_atime(env, myStat, (jlong) theStat->st_atime);
    jset_Stat_mtime(env, myStat, (jlong) theStat->st_mtime);
    jset_Stat_ctime(env, myStat, (jlong) theStat->st_ctime);

    return myStat;
}

static void handleError(JNIEnv * env, int err, const char* path) {

    switch(err) {
        case (EACCES):
            jthrowCC_AccessDeniedException_1(env, path, NULL, "Search permission is denied for one of the directories in the path prefix of path.");
            return;
        case (EBADF):
            jthrow_InvalidFileDescriptorException(env);
            return;
        case (ELOOP):
            jthrowCC_FileSystemLoopException(env, path);
            return;
        case (ENAMETOOLONG):
            jthrowCC_InvalidPathException(env, path, "path is too long.");
            return;
        case (ENOENT):
            jthrowCC_FileNotFoundException_1(env, path);
            return;
        case (ENOMEM):
            jthrowCC_OutOfMemoryError_1(env, "Insufficient kernel memory was available.");
            return;
        case (ENOTDIR):
            jthrowCC_InvalidPathException(env, path, "A component of the path prefix of path is not a directory. ");
            return;
        case (EIO):
            jthrowC_IOException_1(env, "An I/O error occurred.");
            return;
        default:
            jthrow_UnknownNativeErrorException_1(env, err);
            return;
    }
}
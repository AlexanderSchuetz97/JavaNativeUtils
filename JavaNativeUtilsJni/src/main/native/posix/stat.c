#include "../common/jni/eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil.h"
#include "statutil.h"

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    stat
 * Signature: (Ljava/lang/String;)Leu/aschuetz/nativeutils/api/structs/Stat;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_stat
        (JNIEnv * env, jobject inst, jstring path) {
    if (path == NULL) {
        jthrowCC_IllegalArgumentException_1(env, "path is null");
        return NULL;
    }

    struct stat theStat;
    memset(&theStat, 0, sizeof(struct stat));

    const char* thePath = (*env) ->GetStringUTFChars(env, path, NULL);
    if (thePath == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
        return NULL;
    }

    if (stat(thePath, &theStat) != 0) {
        handleError(env, errno, thePath);
        (*env) ->ReleaseStringUTFChars(env, path, thePath);
        return NULL;
    }

    (*env) ->ReleaseStringUTFChars(env, path, thePath);

    return fillStat(env, &theStat);
}
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil */

#ifndef _Included_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
#define _Included_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    stat
 * Signature: (Ljava/lang/String;)Leu/aschuetz/nativeutils/api/structs/Stat;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_stat
  (JNIEnv *, jobject, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    symlink
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_symlink
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil
 * Method:    unlink
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_unlink
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif

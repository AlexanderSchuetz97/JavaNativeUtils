/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class eu_aschuetz_nativeutils_impl_JNICommonNativeUtil */

#ifndef _Included_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
#define _Included_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _getPointerSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1getPointerSize
  (JNIEnv *, jclass);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    MonitorEnter
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_MonitorEnter
  (JNIEnv *, jobject, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    MonitorExit
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_MonitorExit
  (JNIEnv *, jobject, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    DefineClass
 * Signature: (Ljava/lang/String;Ljava/lang/ClassLoader;[BII)Ljava/lang/Class;
 */
JNIEXPORT jclass JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_DefineClass
  (JNIEnv *, jobject, jstring, jobject, jbyteArray, jint, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    __get_cpuid_count
 * Signature: (II)[I
 */
JNIEXPORT jintArray JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1_1get_1cpuid_1count
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _FromReflectedField
 * Signature: (Ljava/lang/reflect/Field;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1FromReflectedField
  (JNIEnv *, jobject, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _ToReflectedField
 * Signature: (Ljava/lang/Class;JZ)Ljava/lang/reflect/Field;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1ToReflectedField
  (JNIEnv *, jobject, jclass, jlong, jboolean);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _GetFieldID
 * Signature: (Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1GetFieldID
  (JNIEnv *, jobject, jclass, jstring, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _GetStaticFieldID
 * Signature: (Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1GetStaticFieldID
  (JNIEnv *, jobject, jclass, jstring, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _FromReflectedMethod
 * Signature: (Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1FromReflectedMethod
  (JNIEnv *, jobject, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _ToReflectedMethod
 * Signature: (Ljava/lang/Class;JZ)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1ToReflectedMethod
  (JNIEnv *, jobject, jclass, jlong, jboolean);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _GetMethodID
 * Signature: (Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1GetMethodID
  (JNIEnv *, jobject, jclass, jstring, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _GetStaticMethodID
 * Signature: (Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1GetStaticMethodID
  (JNIEnv *, jobject, jclass, jstring, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    Throw
 * Signature: (Ljava/lang/Throwable;)Ljava/lang/RuntimeException;
 */
JNIEXPORT jthrowable JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_Throw
  (JNIEnv *, jobject, jthrowable);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _AllocObject
 * Signature: (Ljava/lang/Class;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1AllocObject
  (JNIEnv *, jclass, jclass);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    NewGlobalRef
 * Signature: (Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_NewGlobalRef
  (JNIEnv *, jobject, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    DeleteGlobalRef
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_DeleteGlobalRef
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    NewLocalRef
 * Signature: (J)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_NewLocalRef
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _malloc
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1malloc
  (JNIEnv *, jclass, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1free
  (JNIEnv *, jclass, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    GetDirectBufferAddress
 * Signature: (Ljava/nio/ByteBuffer;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_GetDirectBufferAddress
  (JNIEnv *, jobject, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    pointerAdd
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_pointerAdd
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    NewDirectByteBuffer
 * Signature: (JJ)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil_NewDirectByteBuffer
  (JNIEnv *, jobject, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif

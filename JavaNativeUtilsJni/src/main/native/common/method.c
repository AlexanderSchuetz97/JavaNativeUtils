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
#include "jni/eu_aschuetz_nativeutils_impl_JNINativeMethod.h"
#include "common.h"
#include "stdint.h"
#include "stdlib.h"




/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _FromReflectedMethod
 * Signature: (Ljava/lang/reflect/Method;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1FromReflectedMethod
  (JNIEnv * env, jobject inst, jobject meth) {
	return (jlong) (uintptr_t) (*env)->FromReflectedMethod(env, meth);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _ToReflectedMethod
 * Signature: (Ljava/lang/Class;JZ)Ljava/lang/reflect/Method;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1ToReflectedMethod
  (JNIEnv * env, jobject inst, jclass dec, jlong id, jboolean isStatic) {
	return (*env)->ToReflectedMethod(env, dec, (jmethodID) (uintptr_t) id, isStatic);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _GetMethodID
 * Signature: (Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1GetMethodID
  (JNIEnv * env, jobject inst, jclass dec, jstring name, jstring sig) {
	const char * nameBuf = (*env)->GetStringUTFChars(env, name, NULL);

	if (nameBuf == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return 0;
	}

	const char * sigBuf = (*env)->GetStringUTFChars(env, sig, NULL);
	if (sigBuf == NULL) {
		(*env)->ReleaseStringUTFChars(env, name, nameBuf);
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return 0;
	}

	jmethodID id = (*env)->GetMethodID(env, dec, nameBuf, sigBuf);
	(*env)->ReleaseStringUTFChars(env, name, nameBuf);
	(*env)->ReleaseStringUTFChars(env, sig, sigBuf);
	if (id == NULL) {
		(*env)->ExceptionClear(env);
	}
	return (jlong) (uintptr_t) id;
}
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _GetStaticMethodID
 * Signature: (Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1GetStaticMethodID
  (JNIEnv * env, jobject inst, jclass dec, jstring name, jstring sig) {
	const char * nameBuf = (*env)->GetStringUTFChars(env, name, NULL);

	if (nameBuf == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return 0;
	}

	const char * sigBuf = (*env)->GetStringUTFChars(env, sig, NULL);
	if (sigBuf == NULL) {
		(*env)->ReleaseStringUTFChars(env, name, nameBuf);
		jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
		return 0;
	}

	jmethodID id = (*env)->GetStaticMethodID(env, dec, nameBuf, sigBuf);
	(*env)->ReleaseStringUTFChars(env, name, nameBuf);
	(*env)->ReleaseStringUTFChars(env, sig, sigBuf);
	if (id == NULL) {
		(*env)->ExceptionClear(env);
	}
	return (jlong) (uintptr_t) id;
}



void mapArgs(JNIEnv * env, jsize len, jvalue* mapped, jintArray types, jobjectArray args) {
	jint* t = (*env)->GetIntArrayElements(env, types, NULL);

	for (jsize i = 0; i < len; i++) {
		jobject val = (*env)->GetObjectArrayElement(env, args, i);

		switch(t[i]) {
		case(0):
			//BOOL
			mapped[i].z = unboxBool(env, val);
			(*env)->DeleteLocalRef(env, val);
			break;
		case(1):
			//BYTE
			mapped[i].b = unboxByte(env, val);
			(*env)->DeleteLocalRef(env, val);
			break;
		case(2):
			//CHAR
			mapped[i].c = unboxChar(env, val);
			(*env)->DeleteLocalRef(env, val);
			break;
		case(3):
			//SHORT
			mapped[i].s = unboxShort(env, val);
			(*env)->DeleteLocalRef(env, val);
			break;
		case(4):
			//INT
			mapped[i].i = unboxInt(env, val);
			(*env)->DeleteLocalRef(env, val);
			break;
		case(5):
			//LONG
			mapped[i].j = unboxLong(env, val);
			(*env)->DeleteLocalRef(env, val);
			break;
		case(6):
			//FLOAT
			mapped[i].f = unboxFloat(env, val);
			(*env)->DeleteLocalRef(env, val);
			break;
		case(7):
			//DOUBLE
			mapped[i].d = unboxDouble(env, val);
			(*env)->DeleteLocalRef(env, val);
			break;
		default:
			//OBJECT
			mapped[i].l = val;
			break;
		}
	}

	(*env)->ReleaseIntArrayElements(env, types, t, JNI_ABORT);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _NewObject
 * Signature: (Ljava/lang/Class;J[I[Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1NewObject
  (JNIEnv *env, jclass clazz, jclass inst, jlong methodID, jintArray types, jobjectArray args) {

	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->NewObjectA(env, inst, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallObjectMethod
 * Signature: (Ljava/lang/Object;J[I[Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallObjectMethod
  (JNIEnv * env, jclass clazz, jobject inst, jlong methodID, jintArray types, jobjectArray args) {

	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallObjectMethodA(env, inst, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallVoidMethod
 * Signature: (Ljava/lang/Object;J[I[Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallVoidMethod
  (JNIEnv * env, jclass clazz, jobject inst, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallVoidMethodA(env, inst, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallLongMethod
 * Signature: (Ljava/lang/Object;J[I[Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallLongMethod
  (JNIEnv * env, jclass clazz, jobject inst, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallLongMethodA(env, inst, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallIntMethod
 * Signature: (Ljava/lang/Object;J[I[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallIntMethod
  (JNIEnv * env, jclass clazz, jobject inst, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallIntMethodA(env, inst, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallShortMethod
 * Signature: (Ljava/lang/Object;J[I[Ljava/lang/Object;)S
 */
JNIEXPORT jshort JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallShortMethod
  (JNIEnv * env, jclass clazz, jobject inst, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallShortMethodA(env, inst, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallCharMethod
 * Signature: (Ljava/lang/Object;J[I[Ljava/lang/Object;)C
 */
JNIEXPORT jchar JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallCharMethod
  (JNIEnv * env, jclass clazz, jobject inst, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallCharMethodA(env, inst, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallByteMethod
 * Signature: (Ljava/lang/Object;J[I[Ljava/lang/Object;)B
 */
JNIEXPORT jbyte JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallByteMethod
  (JNIEnv * env, jclass clazz, jobject inst, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallByteMethodA(env, inst, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallBooleanMethod
 * Signature: (Ljava/lang/Object;J[I[Ljava/lang/Object;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallBooleanMethod
  (JNIEnv * env, jclass clazz, jobject inst, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallBooleanMethodA(env, inst, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallFloatMethod
 * Signature: (Ljava/lang/Object;J[I[Ljava/lang/Object;)F
 */
JNIEXPORT jfloat JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallFloatMethod
  (JNIEnv * env, jclass clazz, jobject inst, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallFloatMethodA(env, inst, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallDoubleMethod
 * Signature: (Ljava/lang/Object;J[I[Ljava/lang/Object;)D
 */
JNIEXPORT jdouble JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallDoubleMethod
  (JNIEnv * env, jclass clazz, jobject inst, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallDoubleMethodA(env, inst, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallStaticObjectMethod
 * Signature: (Ljava/lang/Class;J[I[Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallStaticObjectMethod
  (JNIEnv *env , jclass clazz, jclass cl, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallStaticObjectMethod(env, cl, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallStaticVoidMethod
 * Signature: (Ljava/lang/Class;J[I[Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallStaticVoidMethod
  (JNIEnv *env , jclass clazz, jclass cl, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallStaticVoidMethod(env, cl, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallStaticLongMethod
 * Signature: (Ljava/lang/Class;J[I[Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallStaticLongMethod
  (JNIEnv *env , jclass clazz, jclass cl, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallStaticLongMethod(env, cl, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallStaticIntMethod
 * Signature: (Ljava/lang/Class;J[I[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallStaticIntMethod
  (JNIEnv *env , jclass clazz, jclass cl, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallStaticIntMethod(env, cl, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallStaticShortMethod
 * Signature: (Ljava/lang/Class;J[I[Ljava/lang/Object;)S
 */
JNIEXPORT jshort JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallStaticShortMethod
  (JNIEnv *env , jclass clazz, jclass cl, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallStaticShortMethod(env, cl, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallStaticByteMethod
 * Signature: (Ljava/lang/Class;J[I[Ljava/lang/Object;)B
 */
JNIEXPORT jbyte JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallStaticByteMethod
  (JNIEnv *env , jclass clazz, jclass cl, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallStaticByteMethod(env, cl, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallStaticCharMethod
 * Signature: (Ljava/lang/Class;J[I[Ljava/lang/Object;)C
 */
JNIEXPORT jchar JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallStaticCharMethod
  (JNIEnv *env , jclass clazz, jclass cl, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallStaticCharMethod(env, cl, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallStaticBooleanMethod
 * Signature: (Ljava/lang/Class;J[I[Ljava/lang/Object;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallStaticBooleanMethod
  (JNIEnv *env , jclass clazz, jclass cl, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallStaticBooleanMethod(env, cl, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallStaticFloatMethod
 * Signature: (Ljava/lang/Class;J[I[Ljava/lang/Object;)F
 */
JNIEXPORT jfloat JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallStaticFloatMethod
  (JNIEnv *env , jclass clazz, jclass cl, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallStaticFloatMethod(env, cl, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeMethod
 * Method:    _CallStaticDoubleMethod
 * Signature: (Ljava/lang/Class;J[I[Ljava/lang/Object;)D
 */
JNIEXPORT jdouble JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeMethod__1CallStaticDoubleMethod
  (JNIEnv *env , jclass clazz, jclass cl, jlong methodID, jintArray types, jobjectArray args) {
	jsize len = (*env)->GetArrayLength(env, types);
	jvalue mapped[len];
	mapArgs(env, len, mapped, types, args);

	return (*env)->CallStaticDoubleMethod(env, cl, (jmethodID) (uintptr_t) methodID, (const jvalue*) mapped);
}

//
// Copyright Alexander Schütz, 2021-2022
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
#include "./jni/eu_aschuetz_nativeutils_impl_JNICommonNativeUtil.h"
#include "common.h"
#include "stdlib.h"

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _FromReflectedField
 * Signature: (Ljava/lang/reflect/Field;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1FromReflectedField
  (JNIEnv * env, jobject inst, jobject field) {
	return (jlong) (uintptr_t) (*env)->FromReflectedField(env, field);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _ToReflectedField
 * Signature: (Ljava/lang/Class;JZ)Ljava/lang/reflect/Field;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1ToReflectedField
  (JNIEnv * env, jobject inst, jclass declaring, jlong ref, jboolean isStatic) {
	return (*env)->ToReflectedField(env, declaring, (jfieldID) (uintptr_t) ref, isStatic);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _GetFieldID
 * Signature: (Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1GetFieldID
  (JNIEnv * env, jobject inst, jclass declaring, jstring name, jstring sig) {
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

	jfieldID id = (*env)->GetFieldID(env, declaring, nameBuf, sigBuf);
	(*env)->ReleaseStringUTFChars(env, name, nameBuf);
	(*env)->ReleaseStringUTFChars(env, sig, sigBuf);
	if (id == NULL) {
		(*env)->ExceptionClear(env);
	}
	return (jlong) (uintptr_t) id;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNICommonNativeUtil
 * Method:    _GetStaticFieldID
 * Signature: (Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNICommonNativeUtil__1GetStaticFieldID
	(JNIEnv * env, jobject inst, jclass declaring, jstring name, jstring sig) {
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

	jfieldID id = (*env)->GetStaticFieldID(env, declaring, nameBuf, sigBuf);

	(*env)->ReleaseStringUTFChars(env, name, nameBuf);
	(*env)->ReleaseStringUTFChars(env, sig, sigBuf);
	if (id == NULL) {
		(*env)->ExceptionClear(env);
	}
	return (jlong) (uintptr_t) id;
}


/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetObjectField
 * Signature: (JLjava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetObjectField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst) {
	return (*env)->GetObjectField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetStaticObjectField
 * Signature: (JLjava/lang/Class;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetStaticObjectField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst) {
	return (*env)->GetStaticObjectField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetIntField
 * Signature: (JLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetIntField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst) {
	return (*env)->GetIntField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetStaticIntField
 * Signature: (JLjava/lang/Class;)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetStaticIntField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst) {
	return (*env)->GetStaticIntField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetLongField
 * Signature: (JLjava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetLongField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst) {
	return (*env)->GetLongField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetStaticLongField
 * Signature: (JLjava/lang/Class;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetStaticLongField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst) {
	return (*env)->GetStaticLongField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetDoubleField
 * Signature: (JLjava/lang/Object;)D
 */
JNIEXPORT jdouble JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetDoubleField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst) {
	return (*env)->GetDoubleField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetStaticDoubleField
 * Signature: (JLjava/lang/Class;)D
 */
JNIEXPORT jdouble JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetStaticDoubleField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst) {
	return (*env)->GetStaticDoubleField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetFloatField
 * Signature: (JLjava/lang/Object;)F
 */
JNIEXPORT jfloat JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetFloatField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst) {
	return (*env)->GetFloatField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetStaticFloatField
 * Signature: (JLjava/lang/Class;)F
 */
JNIEXPORT jfloat JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetStaticFloatField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst) {
	return (*env)->GetStaticFloatField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetShortField
 * Signature: (JLjava/lang/Object;)S
 */
JNIEXPORT jshort JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetShortField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst) {
	return (*env)->GetShortField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetStaticShortField
 * Signature: (JLjava/lang/Class;)S
 */
JNIEXPORT jshort JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetStaticShortField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst) {
	return (*env)->GetStaticShortField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetCharField
 * Signature: (JLjava/lang/Object;)C
 */
JNIEXPORT jchar JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetCharField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst) {
	return (*env)->GetCharField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetStaticCharField
 * Signature: (JLjava/lang/Class;)C
 */
JNIEXPORT jchar JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetStaticCharField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst) {
	return (*env)->GetStaticCharField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetByteField
 * Signature: (JLjava/lang/Object;)B
 */
JNIEXPORT jbyte JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetByteField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst) {
	return (*env)->GetByteField(env, inst, (jfieldID) (uintptr_t) ref);
}
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetStaticByteField
 * Signature: (JLjava/lang/Class;)B
 */
JNIEXPORT jbyte JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetStaticByteField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst) {
	return (*env)->GetStaticByteField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetBooleanField
 * Signature: (JLjava/lang/Object;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetBooleanField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst) {
	return (*env)->GetBooleanField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _GetStaticBooleanField
 * Signature: (JLjava/lang/Class;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1GetStaticBooleanField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst) {
	return (*env)->GetStaticBooleanField(env, inst, (jfieldID) (uintptr_t) ref);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetObjectField
 * Signature: (JLjava/lang/Object;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetObjectField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst, jobject value) {
	return (*env)->SetObjectField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetStaticObjectField
 * Signature: (JLjava/lang/Class;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetStaticObjectField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst, jobject value) {
	return (*env)->SetStaticObjectField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetIntField
 * Signature: (JLjava/lang/Object;I)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetIntField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst, jint value) {
	return (*env)->SetIntField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetStaticIntField
 * Signature: (JLjava/lang/Class;I)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetStaticIntField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst, jint value) {
	return (*env)->SetStaticIntField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetLongField
 * Signature: (JLjava/lang/Object;J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetLongField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst, jlong value) {
	return (*env)->SetLongField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetStaticLongField
 * Signature: (JLjava/lang/Class;J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetStaticLongField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst, jlong value) {
	return (*env)->SetStaticLongField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetDoubleField
 * Signature: (JLjava/lang/Object;D)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetDoubleField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst, jdouble value) {
	return (*env)->SetDoubleField(env, inst, (jfieldID) (uintptr_t) ref, value);
  }
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetStaticDoubleField
 * Signature: (JLjava/lang/Class;D)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetStaticDoubleField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst, jdouble value) {
	return (*env)->SetStaticDoubleField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetFloatField
 * Signature: (JLjava/lang/Object;F)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetFloatField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst, jfloat value) {
	return (*env)->SetFloatField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetStaticFloatField
 * Signature: (JLjava/lang/Class;F)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetStaticFloatField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst, jfloat value) {
	return (*env)->SetStaticFloatField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetShortField
 * Signature: (JLjava/lang/Object;S)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetShortField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst, jshort value) {
	return (*env)->SetShortField(env, inst, (jfieldID) (uintptr_t) ref, value);

}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetStaticShortField
 * Signature: (JLjava/lang/Class;S)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetStaticShortField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst, jshort value) {
	return (*env)->SetStaticShortField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetCharField
 * Signature: (JLjava/lang/Object;C)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetCharField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst, jchar value) {
	return (*env)->SetCharField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetStaticCharField
 * Signature: (JLjava/lang/Class;C)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetStaticCharField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst, jchar value) {
	return (*env)->SetStaticCharField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetByteField
 * Signature: (JLjava/lang/Object;B)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetByteField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst, jbyte value) {
	return (*env)->SetByteField(env, inst, (jfieldID) (uintptr_t) ref, value);
}
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetStaticByteField
 * Signature: (JLjava/lang/Class;B)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetStaticByteField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst, jbyte value) {
	return (*env)->SetStaticByteField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetBooleanField
 * Signature: (JLjava/lang/Object;Z)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetBooleanField
  (JNIEnv * env, jclass clazz, jlong ref, jobject inst, jboolean value) {
	return (*env)->SetByteField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNINativeField
 * Method:    _SetStaticBooleanField
 * Signature: (JLjava/lang/Class;Z)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNINativeField__1SetStaticBooleanField
  (JNIEnv * env, jclass clazz, jlong ref, jclass inst, jboolean value) {
	return (*env)->SetStaticByteField(env, inst, (jfieldID) (uintptr_t) ref, value);
}

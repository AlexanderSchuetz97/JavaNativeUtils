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
#include <jni.h>
#include "common.h"
#include "jni/io_github_alexanderschuetz97_nativeutils_impl_JNILinuxNativeUtil.h"
#include "jni/io_github_alexanderschuetz97_nativeutils_impl_NativeLibraryLoaderHelper.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//These checks have to be somewhere
static_assert(sizeof(uintptr_t) <= sizeof(jlong), "pointer doesnt fit in jlong");
static_assert(sizeof(jshort) == 2, "jshort is not 2 byte");
static_assert(sizeof(jint) == 4, "jint is not 4 byte");
static_assert(sizeof(jlong) == 8, "jlong is not 8 byte");
static_assert(sizeof(jbyte) == 1, "jbyte is not 1 byte");


jclass fdClass = NULL;
jfieldID fdIntField = NULL;
jfieldID fdHandleField = NULL;

jclass enumClass = NULL;
jmethodID enumOrdinal = NULL;

//EXCEPTIONS
jclass badFDClass = NULL;
jmethodID badFDConstructor = NULL;

jclass unknownErrorClass = NULL;
jmethodID unknownErrorConstructor = NULL;

jclass MutexAbandonedException = NULL;
jmethodID MutexAbandonedExceptionConstructor = NULL;

jclass IllegalArgumentException = NULL;
jclass IllegalStateException = NULL;
jclass oomClass = NULL;

jclass UnsupportedOperationException = NULL;

jclass Exception = NULL;



jclass InvalidPathException = NULL;
jmethodID InvalidPathExceptionConstructor = NULL;


jclass NotDirectoryException = NULL;

jclass Field = NULL;
jmethodID Field_getModifier = NULL;
jmethodID Field_getDeclaringClass = NULL;

jclass NullPointerException = NULL;

jclass SharingViolationException = NULL;
jmethodID SharingViolationExceptionConstructor = NULL;

jclass InetAddress = NULL;
jmethodID InetAddress_getAddress = NULL;
jmethodID InetAddress_getByAddress = NULL;

jclass Iterator = NULL;
jmethodID Iterator_next = NULL;
jmethodID Iterator_hasNext = NULL;

jclass InetSocketAddress = NULL;
jmethodID InetSocketAddressConstructor = NULL;
jmethodID InetSocketAddress_getPort = NULL;
jmethodID InetSocketAddress_getAddress = NULL;

jclass Integer = NULL;
jfieldID Integer_value = NULL;
jclass Long = NULL;
jfieldID Long_value = NULL;
jclass Short = NULL;
jfieldID Short_value = NULL;
jclass Byte = NULL;
jfieldID Byte_value = NULL;
jclass Boolean = NULL;
jfieldID Boolean_value = NULL;
jclass Double = NULL;
jfieldID Double_value = NULL;
jclass Float = NULL;
jfieldID Float_value = NULL;
jclass Character = NULL;
jfieldID Character_value = NULL;

jclass String_Class;

jclass JNINativeMemory;
jfieldID JNINativeMemory_ptr;



/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_NativeLibraryLoaderHelper
 * Method:    getNativeLibVersion
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_NativeLibraryLoaderHelper_getNativeLibVersion
  (JNIEnv * env, jclass clazz) {
	return io_github_alexanderschuetz97_nativeutils_impl_NativeLibraryLoaderHelper_EXPECTED_NATIVE_LIB_VERSION;
}


void delRefs(JNIEnv * env) {

	if (fdClass != NULL) {
		(*env) -> DeleteGlobalRef(env, fdClass);
	}

	if (String_Class != NULL) {
		(*env) -> DeleteGlobalRef(env, String_Class);
	}

	if (badFDClass != NULL) {
		(*env) -> DeleteGlobalRef(env, badFDClass);
	}

	if (unknownErrorClass != NULL) {
		(*env) -> DeleteGlobalRef(env, unknownErrorClass);
	}

	if (MutexAbandonedException != NULL) {
		(*env) -> DeleteGlobalRef(env, MutexAbandonedException);
	}

	if (IllegalArgumentException != NULL) {
		(*env) -> DeleteGlobalRef(env, IllegalArgumentException);
	}

	if (IllegalStateException != NULL) {
		(*env) -> DeleteGlobalRef(env, IllegalStateException);
	}

	if (enumClass != NULL) {
		(*env) -> DeleteGlobalRef(env, enumClass);
	}

	if (oomClass != NULL) {
		(*env) -> DeleteGlobalRef(env, oomClass);
	}

	if (InvalidPathException != NULL) {
		(*env) -> DeleteGlobalRef(env, InvalidPathException);
	}

	if (UnsupportedOperationException != NULL) {
		(*env) -> DeleteGlobalRef(env, UnsupportedOperationException);
	}

	if (Exception != NULL) {
		(*env) -> DeleteGlobalRef(env, Exception);
	}

	if (NotDirectoryException != NULL) {
		(*env) -> DeleteGlobalRef(env, NotDirectoryException);
	}

	if (Field != NULL) {
		(*env) -> DeleteGlobalRef(env, Field);
	}

	if (NullPointerException != NULL) {
		(*env) -> DeleteGlobalRef(env, NullPointerException);
	}

	if (SharingViolationException != NULL) {
		(*env) -> DeleteGlobalRef(env, SharingViolationException);
	}

	if (InetAddress != NULL) {
		(*env) -> DeleteGlobalRef(env, InetAddress);
	}

	if (Iterator != NULL) {
		(*env) -> DeleteGlobalRef(env, Iterator);
	}

	if (InetSocketAddress != NULL) {
		(*env)->DeleteGlobalRef(env, InetSocketAddress);
	}

	if (JNINativeMemory != NULL) {
		(*env)->DeleteGlobalRef(env, JNINativeMemory);
	}

	if (Integer != NULL) {
		(*env)->DeleteGlobalRef(env, Integer);
	}

	if (Long != NULL) {
		(*env)->DeleteGlobalRef(env, Long);
	}

	if (Short != NULL) {
		(*env)->DeleteGlobalRef(env, Short);
	}

	if (Byte != NULL) {
		(*env)->DeleteGlobalRef(env, Byte);
	}

	if (Boolean != NULL) {
		(*env)->DeleteGlobalRef(env, Boolean);
	}

	if (Double != NULL) {
		(*env)->DeleteGlobalRef(env, Double);
	}

	if (Float != NULL) {
		(*env)->DeleteGlobalRef(env, Float);
	}

	if (Character != NULL) {
		(*env)->DeleteGlobalRef(env, Character);
	}


	String_Class = NULL;

	Integer = NULL;
	Integer_value = NULL;
	Long = NULL;
	Long_value = NULL;
	Short = NULL;
	Short_value = NULL;
	Byte = NULL;
	Byte_value = NULL;
	Boolean = NULL;
	Boolean_value = NULL;
	Double = NULL;
	Double_value = NULL;
	Float = NULL;
	Float_value = NULL;
	Character = NULL;
	Character_value = NULL;

	MutexAbandonedException = NULL;
	MutexAbandonedExceptionConstructor = NULL;

	InetSocketAddress = NULL;
	InetSocketAddress_getPort = NULL;
	InetSocketAddress_getAddress = NULL;
	InetSocketAddressConstructor = NULL;

	Iterator = NULL;
	Iterator_hasNext = NULL;
	Iterator_next = NULL;

	InetAddress = NULL;
	InetAddress_getAddress = NULL;
	InetAddress_getByAddress = NULL;

	SharingViolationException = NULL;
	SharingViolationExceptionConstructor = NULL;

	NullPointerException = NULL;
	Field = NULL;
	Field_getModifier = NULL;
	Field_getDeclaringClass = NULL;

	NotDirectoryException = NULL;

	fdClass = NULL;
	badFDClass = NULL;
	unknownErrorClass = NULL;
	IllegalArgumentException = NULL;
	IllegalStateException = NULL;
	enumClass = NULL;
	oomClass = NULL;
	InvalidPathException = NULL;
	UnsupportedOperationException = NULL;
	Exception = NULL;

	enumOrdinal = NULL;
	badFDConstructor = NULL;
	unknownErrorConstructor = NULL;
	fdIntField = NULL;
	fdHandleField = NULL;
	InvalidPathExceptionConstructor = NULL;

	JNINativeMemory_ptr = NULL;
}



jclass makeGlobalClassRef(JNIEnv * env, const char * name) {
	jclass clazz = (*env) ->FindClass(env, name);
	if (clazz == NULL) {
		return NULL;
	}

	jclass global = (*env) ->NewGlobalRef(env, clazz);
	(*env) ->DeleteLocalRef(env, clazz);
	return global;
}

jobject* enumerateEnum(JNIEnv * env, const char * name, const char * sig, int* size) {
	jclass myEnumClass = (*env)->FindClass(env, name);
	if (myEnumClass == NULL) {
		return NULL;
	}

	jmethodID mid = (*env)->GetStaticMethodID(env, myEnumClass, "values", sig);
	if (mid == NULL) {
		(*env)->DeleteLocalRef(env, myEnumClass);
		return NULL;
	}

	jobjectArray values = (jobjectArray) (*env)->CallStaticObjectMethod(env, myEnumClass, mid);
	(*env)->DeleteLocalRef(env, myEnumClass);

	if (values == NULL) {
		return NULL;
	}

	jsize len = (*env)->GetArrayLength(env, values);


	jobject* ptr = malloc(len*(sizeof(jobject)));
	if (ptr == NULL) {
		(*env)->DeleteLocalRef(env, values);
		return NULL;
	}

	for (int i = 0; i < len; i++) {
		jobject lref = (*env)->GetObjectArrayElement(env, values, i);
		if (lref == NULL) {
			for (int j = 0; j < i; j++) {
				(*env)->DeleteGlobalRef(env, ptr[j]);
			}
			free(ptr);
			return NULL;
		}

		ptr[i] = (*env)->NewGlobalRef(env, lref);
		(*env)->DeleteLocalRef(env, lref);
		if (ptr[i] == NULL) {
			for (int j = 0; j < i; j++) {
				(*env)->DeleteGlobalRef(env, ptr[j]);
			}
			free(ptr);
			return NULL;
		}
	}

	if (size != NULL) {
		*size = len;
	}
	return ptr;
}

bool makeRefs(JNIEnv * env) {

	Exception = makeGlobalClassRef(env, "java/lang/Exception");
	if (Exception == NULL) {
		return false;
	}

	String_Class = makeGlobalClassRef(env, "java/lang/String");
	if (String_Class == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, String_Class, "cant find java/lang/String");
		return false;
	}

	Integer = makeGlobalClassRef(env, "java/lang/Integer");
	if (Integer == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Integer");
		return false;
	}

	Integer_value = (*env)->GetFieldID(env, Integer, "value", "I");
	if (Integer_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Integer.value");
		return false;
	}

	Long = makeGlobalClassRef(env, "java/lang/Long");
	if (Long == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Long");
		return false;
	}

	Long_value = (*env)->GetFieldID(env, Long, "value", "J");
	if (Long_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Long.value");
		return false;
	}

	Short = makeGlobalClassRef(env, "java/lang/Short");
	if (Short == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Short");
		return false;
	}

	Short_value = (*env)->GetFieldID(env, Short, "value", "S");
	if (Short_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Short.value");
		return false;
	}

	Byte = makeGlobalClassRef(env, "java/lang/Byte");
	if (Byte == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Byte");
		return false;
	}

	Byte_value = (*env)->GetFieldID(env, Byte, "value", "B");
	if (Byte_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Byte.value");
		return false;
	}

	Boolean = makeGlobalClassRef(env, "java/lang/Boolean");
	if (Boolean == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Boolean");
		return false;
	}

	Boolean_value = (*env)->GetFieldID(env, Boolean, "value", "Z");
	if (Boolean_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Boolean.value");
		return false;
	}

	Character = makeGlobalClassRef(env, "java/lang/Character");
	if (Character == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Character");
		return false;
	}

	Character_value = (*env)->GetFieldID(env, Character, "value", "C");
	if (Character_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Character.value");
		return false;
	}

	Float = makeGlobalClassRef(env, "java/lang/Float");
	if (Float == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Float");
		return false;
	}

	Float_value = (*env)->GetFieldID(env, Float, "value", "F");
	if (Float_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Float.value");
		return false;
	}

	Double = makeGlobalClassRef(env, "java/lang/Double");
	if (Double == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Double");
		return false;
	}

	Double_value = (*env)->GetFieldID(env, Double, "value", "D");
	if (Double_value == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Double.value");
		return false;
	}

	JNINativeMemory = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/impl/JNINativeMemory");
	if (JNINativeMemory == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/impl/JNINativeMemory");
		return false;
	}

	JNINativeMemory_ptr = (*env)->GetFieldID(env, JNINativeMemory, "ptr", "J");
	if (JNINativeMemory_ptr == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/impl/JNINativeMemory.ptr");
		return false;
	}

	InetSocketAddress = makeGlobalClassRef(env, "java/net/InetSocketAddress");
	if (InetSocketAddress == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress");
		return false;
	}

	InetSocketAddressConstructor = (*env)->GetMethodID(env, InetSocketAddress, "<init>", "(Ljava/net/InetAddress;I)V");
	if (InetSocketAddressConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddressConstructor.<init>(Ljava/net/InetAddress;I)V");
		return false;
	}

	InetSocketAddress_getAddress = (*env)->GetMethodID(env, InetSocketAddress, "getAddress", "()Ljava/net/InetAddress;");
	if (InetSocketAddress_getAddress == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.getAddress()Ljava/net/InetAddress;");
		return false;
	}

	InetSocketAddress_getPort = (*env)->GetMethodID(env, InetSocketAddress, "getPort", "()I");
	if (InetSocketAddress_getPort == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.getPort()I");
		return false;
	}

	Iterator = makeGlobalClassRef(env, "java/util/Iterator");
	if (Iterator == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/Iterator");
		return false;
	}

	Iterator_hasNext = (*env) ->GetMethodID(env, Iterator, "hasNext", "()Z");
	if (Iterator_hasNext == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/Iterator.hasNext()Z");
		return false;
	}

	Iterator_next = (*env) ->GetMethodID(env, Iterator, "next", "()Ljava/lang/Object;");
	if (Iterator_next == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/util/Iterator.next()Ljava/lang/Object;");
		return false;
	}


	IllegalArgumentException = makeGlobalClassRef(env, "java/lang/IllegalArgumentException");
	if (IllegalArgumentException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalArgumentException");
		return false;
	}

	InetAddress = makeGlobalClassRef(env, "java/net/InetAddress");
	if (InetAddress == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress");
		return false;
	}

	InetAddress_getAddress = (*env) ->GetMethodID(env, InetAddress, "getAddress", "()[B");
	if (InetAddress_getAddress == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getAddress()[B");
		return false;
	}

	InetAddress_getByAddress = (*env) ->GetStaticMethodID(env, InetAddress, "getByAddress", "([B)Ljava/net/InetAddress;");
	if (InetAddress_getByAddress == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getByAddress([B)Ljava/net/InetAddress;");
		return false;
	}

	NullPointerException = makeGlobalClassRef(env, "java/lang/NullPointerException");
	if (NullPointerException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/NullPointerException");
		return false;
	}

	IllegalStateException = makeGlobalClassRef(env, "java/lang/IllegalStateException");
	if (IllegalStateException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalStateException");
		return false;
	}

	Field = makeGlobalClassRef(env, "java/lang/reflect/Field");
	if (Field == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/reflect/Field");
		return false;
	}

	Field_getModifier = (*env)->GetMethodID(env, Field, "getModifiers", "()I");
	if (Field_getModifier == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/reflect/Field.getModifiers()I");
		return false;
	}

	Field_getDeclaringClass = (*env)->GetMethodID(env, Field, "getDeclaringClass", "()Ljava/lang/Class;");
	if (Field_getDeclaringClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/reflect/Field.getDeclaringClass()Ljava/lang/Class;");
		return false;
	}

	NotDirectoryException = makeGlobalClassRef(env, "java/nio/file/NotDirectoryException");
	if (NotDirectoryException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/NotDirectoryException");
		return false;
	}

	SharingViolationException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException");
	if (SharingViolationException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException");
		return false;
	}

	SharingViolationExceptionConstructor = (*env) ->GetMethodID(env, SharingViolationException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (SharingViolationExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}

	fdClass = makeGlobalClassRef(env, "java/io/FileDescriptor");
	if (fdClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/io/FileDescriptor");
		return false;
	}

	fdIntField = (*env) ->GetFieldID(env, fdClass, "fd", "I");
	if (fdIntField == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/io/FileDescriptor.fd I");
		return false;
	}


	fdHandleField = (*env) ->GetFieldID(env, fdClass, "handle", "J");
	if (fdHandleField == NULL) {
		//!DOES NOT EXIST ON LINUX ONLY FOR WINDOWS!
		(*env)->ExceptionClear(env);
	}

	badFDClass = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/InvalidFileDescriptorException");
	if (badFDClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/InvalidFileDescriptorException");
		return false;
	}

	badFDConstructor = (*env) ->GetMethodID(env, badFDClass, "<init>", "()V");
	if (badFDConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/InvalidFileDescriptorException.<init>()V");
		return false;
	}

	unknownErrorClass = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/UnknownNativeErrorException");
	if (unknownErrorClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/UnknownNativeErrorException");
		return false;
	}

	unknownErrorConstructor = (*env) ->GetMethodID(env, unknownErrorClass, "<init>", "(J)V");
	if (unknownErrorConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/UnknownNativeErrorException.<init>(J)V");
		return false;
	}

	MutexAbandonedException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/MutexAbandonedException");
	if (MutexAbandonedException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/MutexAbandonedException");
		return false;
	}

	MutexAbandonedExceptionConstructor = (*env) ->GetMethodID(env, MutexAbandonedException, "<init>", "(J)V");
	if (MutexAbandonedExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/MutexAbandonedException.<init>(J)V");
		return false;
	}

	InvalidPathException = makeGlobalClassRef(env, "java/nio/file/InvalidPathException");
	if (InvalidPathException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/AccessDeniedException");
		return false;
	}

	UnsupportedOperationException = makeGlobalClassRef(env, "java/lang/UnsupportedOperationException");
	if (UnsupportedOperationException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/UnsupportedOperationException");
		return false;
	}

	InvalidPathExceptionConstructor = (*env) ->GetMethodID(env, InvalidPathException, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (InvalidPathExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/InvalidPathException.<init>(Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}

	oomClass = makeGlobalClassRef(env, "java/lang/OutOfMemoryError");
	if (oomClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/OutOfMemoryError");
		return false;
	}


	enumClass = makeGlobalClassRef(env, "java/lang/Enum");
	if (enumClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Enum");
		return false;
	}

	enumOrdinal = (*env) ->GetMethodID(env, enumClass, "ordinal", "()I");
	if (enumOrdinal == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/Enum.ordinal()I");
		return false;
	}


	return true;
}

void delRef(JNIEnv * env, jobject obj) {
	if (obj == NULL) {
		return;
	}

	(*env) -> DeleteLocalRef(env, obj);
}

jint unboxInt(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetIntField(env, box, Integer_value);
}

jlong unboxLong(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetLongField(env, box, Long_value);
}

jshort unboxShort(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetShortField(env, box, Short_value);
}

jboolean unboxBool(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetBooleanField(env, box, Boolean_value);
}

jchar unboxChar(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetCharField(env, box, Character_value);
}

jbyte unboxByte(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetByteField(env, box, Byte_value);
}

jdouble unboxDouble(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetDoubleField(env, box, Double_value);
}

jfloat unboxFloat(JNIEnv * env, jobject box) {
	if (box == NULL) {
		return 0;
	}
	return (*env)->GetFloatField(env, box, Float_value);
}

jstring toJString(JNIEnv * env, const char* data) {
	if (data == NULL) {
		return NULL;
	}
	jstring str = (*env) ->NewStringUTF(env, data);
	if (str == NULL) {
		//EAT OOM
		(*env)->ExceptionClear(env);
	}
	return str;
}

jobjectArray jStringArray(JNIEnv * env, jsize size) {
	jobjectArray arr = (*env)->NewObjectArray(env, size, String_Class, NULL);
	if (arr == NULL) {
		jthrowC_OutOfMemoryError_1(env, "jStringArray->NewObjectArray");
	}

	return arr;
}

jlong jget_JNINativeMemory_ptr(JNIEnv * env, jobject inst) {
	return (*env)->GetLongField(env, inst, JNINativeMemory_ptr);
}


int getFD(JNIEnv * env, jobject fd) {
	if (fd == NULL) {
		return -1;
	}
	return (int) (*env) -> GetIntField(env, fd, fdIntField);
}


void setFD(JNIEnv * env, jobject fd, int value) {
	if (fd == NULL) {
		return;
	}

	(*env) -> SetIntField(env, fd, fdIntField, (jint) value);
}


intptr_t getHandle(JNIEnv * env, jobject fd) {
	if (fd == NULL || fdHandleField == NULL) {
		return -1;
	}
	return (intptr_t) (*env) -> GetLongField(env, fd, fdHandleField);
}


bool isStatic(JNIEnv *env, jobject field) {
	return ((*env)->CallIntMethod(env, field, Field_getModifier) & 0x00000008) == 0x00000008;
}

jclass getDeclareingClass(JNIEnv *env, jobject field) {
	return (jclass) (*env)->CallObjectMethod(env, field, Field_getDeclaringClass);
}

static_assert(sizeof(jchar) <= sizeof(wchar_t), "jchar does not fit into wchar_t");

wchar_t * toWCharsMalloc(JNIEnv * env, jstring str) {
	if (str == NULL) {
		jthrowCC_NullPointerException_1(env, "toWCharsMalloc");
		return false;
	}

	jsize len = (*env)->GetStringLength(env, str);


	wchar_t * res = malloc(sizeof(wchar_t) * (len+1));

	if (res == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "malloc");
		return NULL;
	}

	if (!toWChars(env, str, res)) {
		free((void*) res);
		return NULL;
	}

	return res;
}

bool toWChars(JNIEnv * env, jstring str, wchar_t* wchars) {
	if (str == NULL || wchars == NULL) {
		jthrowCC_NullPointerException_1(env, "toWChars");
		return false;
	}

	jsize len = (*env)->GetStringLength(env, str);

	if (len <= 0) {
		wchars[0] = 0;
		return true;
	}

	const jchar* jchars = (*env)->GetStringChars(env, str, NULL);
	if (jchars == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "GetStringChars");
		return false;
	}


	wchars[len] = 0;

	if (sizeof(wchar_t) == sizeof(jchar)) {
		memcpy((void*) wchars, (void*)jchars, len*sizeof(jchar));
	} else {
		for (jsize i = 0; i < len; i++) {
			wchars[i] = (wchar_t) jchars[i];
		}
	}

	(*env)->ReleaseStringChars(env, str, jchars);

	return true;
}

void fromWCharCopy(jchar* to, wchar_t* from, jsize len) {
	if (len <= 0) {
		return;
	}

	if (sizeof(wchar_t) == sizeof(jchar)) {
		memcpy((void*) to, (void*) from, len*sizeof(jchar));
	} else {
		for (jsize i = 0; i < len; i++) {
			//TODO
			//This will scuff 4 byte unicode, i dont care for now...
			to[i] = (jchar) from[i];
		}
	}
}

jstring fromWChars(JNIEnv * env, wchar_t* wchars) {
	if (wchars == NULL) {
		jthrowCC_NullPointerException_1(env, "fromWChars");
		return NULL;
	}

	jsize len = 0;
	while(true) {
		if (wchars[len] == 0) {
			break;
		}

		len++;
	}


	if (len > 128) {
		jchar* ptr = (jchar*) malloc(sizeof(jchar) * len);
		if (ptr == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "malloc");
			return NULL;
		}

		fromWCharCopy(ptr, wchars, len);

		jstring nstring = (*env)->NewString(env, (const jchar*) ptr, len);
		free((void*) ptr);
		return nstring;
	} else {
		jchar jchars[len];
		fromWCharCopy(jchars, wchars, len);
		return (*env)->NewString(env, (const jchar*) jchars, len);
	}
}

bool setStringField(JNIEnv  * env, jobject obj, jfieldID field, const char * str) {
	if (obj == NULL) {
		jthrowCC_NullPointerException_1(env, "obj");
		return false;
	}

	if (str == NULL) {
		(*env)->SetObjectField(env, obj, field, NULL);
		return true;
	}

	jstring jstr = (*env)->NewStringUTF(env, str);
	if (jstr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
		return false;
	}

	(*env)->SetObjectField(env, obj, field, jstr);

	return true;
}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIEnv * env;

	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_1) != JNI_OK) {
		return JNI_ABORT;
	}

	if (!jnigenerator_init(env)) {
		jnigenerator_destroy(env);
		return JNI_ABORT;
	}

	if (!makeRefs(env)) {
		delRefs(env);
		return JNI_ABORT;
	}

    return JNI_VERSION_1_1;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {

	JNIEnv * env;
	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_1) != JNI_OK) {
		return;
	}

	jnigenerator_destroy(env);
	delRefs(env);
}



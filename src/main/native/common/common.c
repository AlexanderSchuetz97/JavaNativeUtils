//
// Copyright Alexander Schütz, 2021
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
#include <stddef.h>
#include <stdbool.h>


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

jclass illegalArgument = NULL;
jclass oomClass = NULL;
jclass ioExcClass = NULL;

jclass UnsupportedOperationException = NULL;

jclass Exception = NULL;

jclass ReadOnlyFileSystemException = NULL;
jmethodID ReadOnlyFileSystemExceptionConstructor = NULL;


jclass FileSystemLoopException = NULL;
jclass AccessDeniedException = NULL;
jmethodID AccessDeniedExceptionConstructor = NULL;

jclass FileAlreadyExistsException = NULL;
jmethodID FileAlreadyExistsExceptionConstructor = NULL;


jclass InvalidPathException = NULL;
jmethodID InvalidPathExceptionConstructor = NULL;

jclass FileNotFoundException = NULL;

jclass NotDirectoryException = NULL;

jclass QuotaExceededException = NULL;
jmethodID QuotaExceededExceptionConstructor = NULL;

jclass Field = NULL;
jmethodID Field_getModifier;
jmethodID Field_getDeclaringClass;

jclass NullPointerException;

jclass SharingViolationException = NULL;
jmethodID SharingViolationExceptionConstructor = NULL;


/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_NativeLibraryLoaderHelper
 * Method:    getNativeLibVersion
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_NativeLibraryLoaderHelper_getNativeLibVersion
  (JNIEnv * env, jclass clazz) {
	return 0;
}


void delRefs(JNIEnv * env) {

	if (fdClass != NULL) {
		(*env) -> DeleteGlobalRef(env, fdClass);
	}

	if (badFDClass != NULL) {
		(*env) -> DeleteGlobalRef(env, badFDClass);
	}

	if (unknownErrorClass != NULL) {
		(*env) -> DeleteGlobalRef(env, unknownErrorClass);
	}

	if (illegalArgument != NULL) {
		(*env) -> DeleteGlobalRef(env, illegalArgument);
	}

	if (enumClass != NULL) {
		(*env) -> DeleteGlobalRef(env, enumClass);
	}

	if (oomClass != NULL) {
		(*env) -> DeleteGlobalRef(env, oomClass);
	}

	if (ioExcClass != NULL) {
		(*env) -> DeleteGlobalRef(env, ioExcClass);
	}

	if (FileSystemLoopException != NULL) {
		(*env) -> DeleteGlobalRef(env, FileSystemLoopException);
	}

	if (AccessDeniedException != NULL) {
		(*env) -> DeleteGlobalRef(env, AccessDeniedException);
	}

	if (InvalidPathException != NULL) {
		(*env) -> DeleteGlobalRef(env, InvalidPathException);
	}

	if (UnsupportedOperationException != NULL) {
		(*env) -> DeleteGlobalRef(env, UnsupportedOperationException);
	}


	if (ReadOnlyFileSystemException != NULL) {
		(*env) -> DeleteGlobalRef(env, ReadOnlyFileSystemException);
	}

	if (Exception != NULL) {
		(*env) -> DeleteGlobalRef(env, Exception);
	}

	if (StatClass != NULL) {
		(*env) -> DeleteGlobalRef(env, StatClass);
	}

	if (FileNotFoundException != NULL) {
		(*env) -> DeleteGlobalRef(env, FileNotFoundException);
	}

	if (Win32FileAttributeData != NULL) {
		(*env) -> DeleteGlobalRef(env, Win32FileAttributeData);
	}

	if (NotDirectoryException != NULL) {
		(*env) -> DeleteGlobalRef(env, NotDirectoryException);
	}

	if (QuotaExceededException != NULL) {
		(*env) -> DeleteGlobalRef(env, QuotaExceededException);
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

	SharingViolationException = NULL;
	SharingViolationExceptionConstructor = NULL;

	NullPointerException = NULL;
	Field = NULL;
	Field_getModifier = NULL;
	Field_getDeclaringClass = NULL;


	QuotaExceededException = NULL;
	QuotaExceededExceptionConstructor = NULL;

	NotDirectoryException = NULL;
	Win32FileAttributeData = NULL;
	Win32FileAttributeDataConstructor = NULL;
	Win32FileAttributeData_dwFileAttributes = NULL;
	Win32FileAttributeData_nFileSizeLow = NULL;
	Win32FileAttributeData_nFileSizeHigh = NULL;
	Win32FileAttributeData_ftLastAccessTimeLow = NULL;
	Win32FileAttributeData_ftLastAccessTimeHigh = NULL;
	Win32FileAttributeData_ftLastWriteTimeHigh = NULL;
	Win32FileAttributeData_ftLastWriteTimeLow = NULL;
	Win32FileAttributeData_ftCreationTimeHigh = NULL;
	Win32FileAttributeData_ftCreationTimeLow = NULL;

	FileNotFoundException = NULL;

	StatClass = NULL;
	StatClass_dev = NULL;
	StatClass_ino = NULL;
	StatClass_mode = NULL;
	StatClass_nlink = NULL;
	StatClass_uid = NULL;
	StatClass_gid = NULL;
	StatClass_rdev = NULL;
	StatClass_size = NULL;
	StatClass_size = NULL;
	StatClass_blksize = NULL;
	StatClass_blocks = NULL;
	StatClass_atime = NULL;
	StatClass_mtime = NULL;
	StatClass_ctime = NULL;

	fdClass = NULL;
	badFDClass = NULL;
	unknownErrorClass = NULL;
	illegalArgument = NULL;
	enumClass = NULL;
	oomClass = NULL;
	ioExcClass = NULL;
	FileSystemLoopException = NULL;
	AccessDeniedException = NULL;
	InvalidPathException = NULL;
	UnsupportedOperationException = NULL;
	ReadOnlyFileSystemException = NULL;
	Exception = NULL;
	ReadOnlyFileSystemExceptionConstructor = NULL;

	enumOrdinal = NULL;
	badFDConstructor = NULL;
	unknownErrorConstructor = NULL;
	fdIntField = NULL;
	fdHandleField = NULL;
	AccessDeniedExceptionConstructor = NULL;
	InvalidPathExceptionConstructor = NULL;
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

bool makeRefs(JNIEnv * env) {

	Exception = makeGlobalClassRef(env, "java/lang/Exception");
	if (Exception == NULL) {
		return false;
	}

	NullPointerException = makeGlobalClassRef(env, "java/lang/NullPointerException");
	if (NullPointerException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/NullPointerException");
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

	QuotaExceededException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/QuotaExceededException");
	if (QuotaExceededException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/QuotaExceededException");
		return false;
	}

	QuotaExceededExceptionConstructor = (*env) ->GetMethodID(env, QuotaExceededException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");;
	if (QuotaExceededExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/QuotaExceededException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}

	SharingViolationException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException");
	if (SharingViolationException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException");
		return false;
	}

	SharingViolationExceptionConstructor = (*env) ->GetMethodID(env, SharingViolationException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");;
	if (SharingViolationExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}



	Win32FileAttributeData = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData");
	if (Win32FileAttributeData == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData");
		return false;
	}

	Win32FileAttributeDataConstructor = (*env) ->GetMethodID(env, Win32FileAttributeData, "<init>", "()V");;
	if (Win32FileAttributeDataConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.<init>()V");
		return false;
	}

	Win32FileAttributeData_dwFileAttributes = (*env) ->GetFieldID(env, Win32FileAttributeData, "dwFileAttributes", "J");
	if (Win32FileAttributeData_dwFileAttributes == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_dwFileAttributes J");
		return false;
	}

	Win32FileAttributeData_nFileSizeLow = (*env) ->GetFieldID(env, Win32FileAttributeData, "nFileSizeLow", "J");
	if (Win32FileAttributeData_nFileSizeLow == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_nFileSizeLow J");
		return false;
	}

	Win32FileAttributeData_nFileSizeHigh = (*env) ->GetFieldID(env, Win32FileAttributeData, "nFileSizeHigh", "J");
	if (Win32FileAttributeData_nFileSizeHigh == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_nFileSizeHigh J");
		return false;
	}

	Win32FileAttributeData_ftLastAccessTimeLow = (*env) ->GetFieldID(env, Win32FileAttributeData, "ftLastAccessTimeLow", "J");
	if (Win32FileAttributeData_ftLastAccessTimeLow == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftLastAccessTimeLow J");
		return false;
	}

	Win32FileAttributeData_ftLastAccessTimeHigh = (*env) ->GetFieldID(env, Win32FileAttributeData, "ftLastAccessTimeHigh", "J");
	if (Win32FileAttributeData_ftLastAccessTimeHigh == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftLastAccessTimeHigh J");
		return false;
	}

	Win32FileAttributeData_ftLastWriteTimeLow = (*env) ->GetFieldID(env, Win32FileAttributeData, "ftLastWriteTimeLow", "J");
	if (Win32FileAttributeData_ftLastWriteTimeLow == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftLastWriteTimeLow J");
		return false;
	}

	Win32FileAttributeData_ftCreationTimeHigh = (*env) ->GetFieldID(env, Win32FileAttributeData, "ftCreationTimeHigh", "J");
	if (Win32FileAttributeData_ftCreationTimeHigh == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftCreationTimeHigh J");
		return false;
	}

	Win32FileAttributeData_ftCreationTimeLow = (*env) ->GetFieldID(env, Win32FileAttributeData, "ftCreationTimeLow", "J");
	if (Win32FileAttributeData_ftCreationTimeLow == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftCreationTimeLow J");
		return false;
	}

	FileNotFoundException = makeGlobalClassRef(env, "java/io/FileNotFoundException");
	if (FileNotFoundException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/io/FileNotFoundException");
		return false;
	}

	StatClass = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Stat");
	if (StatClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat");
		return false;
	}

	StatClassConstructor = (*env) ->GetMethodID(env, StatClass, "<init>", "()V");
	if (StatClassConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.<init>()V");
		return false;
	}


	StatClass_dev = (*env) ->GetFieldID(env, StatClass, "dev", "J");
	if (StatClass_dev == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.dev J");
		return false;
	}

	StatClass_ino = (*env) ->GetFieldID(env, StatClass, "ino", "J");
	if (StatClass_ino == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.ino J");
		return false;
	}

	StatClass_mode = (*env) ->GetFieldID(env, StatClass, "mode", "J");
	if (StatClass_mode == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.mode J");
		return false;
	}

	StatClass_nlink = (*env) ->GetFieldID(env, StatClass, "nlink", "J");
	if (StatClass_nlink == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.nlink J");
		return false;
	}

	StatClass_uid = (*env) ->GetFieldID(env, StatClass, "uid", "J");
	if (StatClass_uid == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.uid J");
		return false;
	}

	StatClass_gid = (*env) ->GetFieldID(env, StatClass, "gid", "J");
	if (StatClass_gid == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.gid J");
		return false;
	}

	StatClass_rdev = (*env) ->GetFieldID(env, StatClass, "rdev", "J");
	if (StatClass_rdev == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.rdev J");
		return false;
	}

	StatClass_size = (*env) ->GetFieldID(env, StatClass, "size", "J");
	if (StatClass_size == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.size J");
		return false;
	}

	StatClass_blksize = (*env) ->GetFieldID(env, StatClass, "blksize", "J");
	if (StatClass_blksize == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.blksize J");
		return false;
	}

	StatClass_blocks = (*env) ->GetFieldID(env, StatClass, "blocks", "J");
	if (StatClass_blocks == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.blocks J");
		return false;
	}

	StatClass_atime = (*env) ->GetFieldID(env, StatClass, "atime", "J");
	if (StatClass_atime == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.atime J");
		return false;
	}

	StatClass_mtime = (*env) ->GetFieldID(env, StatClass, "mtime", "J");
	if (StatClass_mtime == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.mtime J");
		return false;
	}

	StatClass_ctime = (*env) ->GetFieldID(env, StatClass, "ctime", "J");
	if (StatClass_ctime == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.ctime J");
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

	InvalidPathException = makeGlobalClassRef(env, "java/nio/file/InvalidPathException");
	if (InvalidPathException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/AccessDeniedException");
		return false;
	}

	ReadOnlyFileSystemException = makeGlobalClassRef(env, "java/nio/file/ReadOnlyFileSystemException");
	if (ReadOnlyFileSystemException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/ReadOnlyFileSystemException");
		return false;
	}

	ReadOnlyFileSystemExceptionConstructor = (*env) ->GetMethodID(env, ReadOnlyFileSystemException, "<init>", "()V");
	if (ReadOnlyFileSystemExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/ReadOnlyFileSystemException.<init>()V");
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

	AccessDeniedException = makeGlobalClassRef(env, "java/nio/file/AccessDeniedException");
	if (AccessDeniedException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/AccessDeniedException");
		return false;
	}

	AccessDeniedExceptionConstructor = (*env) ->GetMethodID(env, AccessDeniedException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (AccessDeniedExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/AccessDeniedException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}

	FileAlreadyExistsException = makeGlobalClassRef(env, "java/nio/file/FileAlreadyExistsException");
	if (FileAlreadyExistsException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/FileAlreadyExistsException");
		return false;
	}

	FileAlreadyExistsExceptionConstructor = (*env) ->GetMethodID(env, FileAlreadyExistsException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (FileAlreadyExistsExceptionConstructor == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/FileAlreadyExistsException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		return false;
	}

	FileSystemLoopException = makeGlobalClassRef(env, "java/nio/file/FileSystemLoopException");
	if (FileSystemLoopException == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/nio/file/FileSystemLoopException");
		return false;
	}

	oomClass = makeGlobalClassRef(env, "java/lang/OutOfMemoryError");
	if (oomClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/lang/OutOfMemoryError");
		return false;
	}

	ioExcClass = makeGlobalClassRef(env, "java/io/IOException");
	if (ioExcClass == NULL) {
		(*env) -> ExceptionClear(env);
		(*env) -> ThrowNew(env, Exception, "cant find java/io/IOException");
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

void unknownError(JNIEnv * env, jlong code) {
	jobject inst = (*env) -> NewObject(env, unknownErrorClass, unknownErrorConstructor, code);
	if (inst == NULL) {
		//OOM already thrown
		return;
	}
	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void badFileDescriptor(JNIEnv * env) {
	jobject inst = (*env) -> NewObject(env, badFDClass, badFDConstructor);
	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst );
}

void throwFSLoop(JNIEnv * env, const char* file) {
	(*env)->ThrowNew( env, FileSystemLoopException, file);
}

void throwUnsupportedExc(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, UnsupportedOperationException, message);
}

void throwFSReadOnly(JNIEnv * env) {
	jobject inst = (*env) -> NewObject(env, ReadOnlyFileSystemException, ReadOnlyFileSystemExceptionConstructor);
	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst);
	(*env)->DeleteLocalRef(env, inst);
}

void throwNotDirectoryException(JNIEnv * env, const char* path) {
	(*env)->ThrowNew(env, NotDirectoryException, path);
}

void throwInvalidPath(JNIEnv * env, const char* path, const char* reason) {
	jstring fileString = toJString(env, path);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, InvalidPathException, InvalidPathExceptionConstructor, fileString, reasonString);

	delRef(env, fileString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwQuotaExceededException(JNIEnv * env, const char* file, const char* other, const char* reason) {
	jstring fileString = toJString(env, file);
	jstring otherString = toJString(env, other);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, QuotaExceededException, QuotaExceededExceptionConstructor, fileString, otherString, reasonString);

	delRef(env, fileString);
	delRef(env, otherString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwFSAccessDenied(JNIEnv * env, const char* file, const char* other, const char* reason) {
	jstring fileString = toJString(env, file);
	jstring otherString = toJString(env, other);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, AccessDeniedException, AccessDeniedExceptionConstructor, fileString, otherString, reasonString);

	delRef(env, fileString);
	delRef(env, otherString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwShareingViolationException(JNIEnv * env, const char* file, const char* other, const char* reason) {
	jstring fileString = toJString(env, file);
	jstring otherString = toJString(env, other);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, SharingViolationException, SharingViolationExceptionConstructor, fileString, otherString, reasonString);

	delRef(env, fileString);
	delRef(env, otherString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwFileAlreadyExistsExc(JNIEnv * env, const char* file, const char* other, const char* reason) {
	jstring fileString = toJString(env, file);
	jstring otherString = toJString(env, other);
	jstring reasonString = toJString(env, reason);

	jobject inst = (*env) -> NewObject(env, FileAlreadyExistsException, FileAlreadyExistsExceptionConstructor, fileString, otherString, reasonString);

	delRef(env, fileString);
	delRef(env, otherString);
	delRef(env, reasonString);

	if (inst == NULL) {
		//OOM already thrown
		return;
	}

	(*env)->Throw( env, inst );
	(*env)->DeleteLocalRef(env, inst);
}

void throwOOM(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, oomClass, message );
}

void throwIOExc(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, ioExcClass, message );
}

void throwNullPointerException(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, NullPointerException, message );
}

void illegalArgs(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, illegalArgument, message);
}

void throwFileNotFoundExc(JNIEnv * env, const char* message) {
	(*env)->ThrowNew( env, FileNotFoundException, message);
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
	return (*env)->CallIntMethod(env, field, Field_getModifier) & 0x00000008 == 0x00000008;
}

jclass getDeclareingClass(JNIEnv *env, jobject field) {
	return (jclass) (*env)->CallObjectMethod(env, field, Field_getDeclaringClass);
}

int getEnumOrdinal(JNIEnv * env, jobject e) {
	if (e == NULL) {
		return -1;
	}

	return (int) (*env) -> CallIntMethod(env, e, enumOrdinal);
}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIEnv * env;

	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_1) != JNI_OK) {
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

	delRefs(env);
}

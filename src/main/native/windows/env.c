#include "../common/jni/io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil.h"
#include "../common/common.h"

#include <windows.h>
#include <errhandlingapi.h>

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetModuleFileNameA
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetModuleFileNameA
  (JNIEnv * env, jobject inst, jlong handle) {

	size_t size = 256;

	while(size < 0xffff) {

		void * buf = malloc(size);
		if (buf == NULL) {
			throwOOM(env, "malloc");
			return NULL;
		}

		memset(buf, 0, size);

		LPSTR str = (LPSTR) buf;

		GetModuleFileNameA((HMODULE) (uintptr_t) handle, str, size-1);
		DWORD lerr = GetLastError();
		if (lerr == ERROR_SUCCESS) {
			jstring jstr = (*env)->NewStringUTF(env, str);
			free(str);
			return jstr;
		}

		free(buf);

		if (lerr != ERROR_INSUFFICIENT_BUFFER) {
			throwUnknownError(env, lerr);
			return NULL;
		}

		size+=256;
	}


	throwUnknownError(env, ERROR_INSUFFICIENT_BUFFER);
	return NULL;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetEnvironmentVariableA
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_SetEnvironmentVariableA
  (JNIEnv * env, jobject inst, jstring name, jstring value) {

	if (name == NULL) {
		throwNullPointerException(env, "name");
		return;
	}

	const char * namePtr = (*env)->GetStringUTFChars(env, name, NULL);
	if (namePtr == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return;
	}

	if (value == NULL) {
		WINBOOL b = SetEnvironmentVariableA(namePtr, NULL);

		(*env)->ReleaseStringUTFChars(env, name, namePtr);

		if (!b) {
			throwUnknownError(env, GetLastError());
		}


		return;
	}

	const char * valuePtr = (*env)->GetStringUTFChars(env, value, NULL);
	if (valuePtr == NULL) {
		(*env)->ReleaseStringUTFChars(env, name, namePtr);
		throwOOM(env, "GetStringUTFChars");
		return;
	}


	WINBOOL b = SetEnvironmentVariableA(namePtr, valuePtr);

	(*env)->ReleaseStringUTFChars(env, name, namePtr);
	(*env)->ReleaseStringUTFChars(env, value, valuePtr);

	if (!b) {
		throwUnknownError(env, GetLastError());
	}
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ExpandEnvironmentStringsA
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ExpandEnvironmentStringsA
  (JNIEnv * env, jobject inst, jstring str) {
	if (str == NULL) {
		throwNullPointerException(env, "name");
		return NULL;
	}

	const char * strPtr = (*env)->GetStringUTFChars(env, str, NULL);
	if (strPtr == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return NULL;
	}

	char small[256];
	memset((void*) small, 0, 256);
	DWORD size = ExpandEnvironmentStringsA(strPtr, small, 256);
	if (size == 0) {
		(*env)->ReleaseStringUTFChars(env, str, strPtr);
		throwUnknownError(env, GetLastError());
		return NULL;
	}

	if (size <= 256) {
		(*env)->ReleaseStringUTFChars(env, str, strPtr);
		return (*env)->NewStringUTF(env, small);
	}

	char * large = (char *) malloc(size);
	memset((void*) large, 0, size);
	DWORD nsize = ExpandEnvironmentStringsA(strPtr, large, size);

	(*env)->ReleaseStringUTFChars(env, str, strPtr);
	if (size == 0) {
		free((void*)large);
		throwUnknownError(env, GetLastError());
		return NULL;
	}

	if (nsize <= size) {
		jstring str = (*env)->NewStringUTF(env, large);
		free((void*)large);
		return str;
	}


	free((void*)large);
	throwUnknownError(env, ERROR_INSUFFICIENT_BUFFER);
	return NULL;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetEnvironmentVariableA
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetEnvironmentVariableA
  (JNIEnv * env, jobject inst, jstring name) {
	if (name == NULL) {
		throwNullPointerException(env, "name");
		return NULL;
	}

	const char * namePtr = (*env)->GetStringUTFChars(env, name, NULL);
	if (namePtr == NULL) {
		throwOOM(env, "GetStringUTFChars");
		return NULL;
	}


	LPSTR str = "";
	DWORD res = GetEnvironmentVariableA(namePtr, str, 0);
	if (res <= 0) {
		DWORD lerr = GetLastError();
		if (lerr == ERROR_ENVVAR_NOT_FOUND) {
			(*env)->ReleaseStringUTFChars(env, name, namePtr);
			return NULL;
		}

		(*env)->ReleaseStringUTFChars(env, name, namePtr);
		throwUnknownError(env, lerr);
		return NULL;
	}


	int i = 0;

	while(i++ < 10) {

		//Windows has scammed me before im now doing +2 just because
		void * buf = malloc(res+2);
		if (buf == NULL) {
			(*env)->ReleaseStringUTFChars(env, name, namePtr);
			throwOOM(env, "malloc");
			return NULL;
		}

		memset(buf, 0, res+2);
		str = (LPSTR) buf;

		DWORD nres = GetEnvironmentVariableA(namePtr, str, res+1);

		if (nres <= 0) {
			DWORD lerr = GetLastError();
			if (lerr == ERROR_ENVVAR_NOT_FOUND) {
				(*env)->ReleaseStringUTFChars(env, name, namePtr);
				return NULL;
			}

			(*env)->ReleaseStringUTFChars(env, name, namePtr);
			throwUnknownError(env, lerr);
			return NULL;
		}

		//Modification out of nowhere
		if (nres > res) {
			free(buf);
			res = nres;
			continue;
		}

		(*env)->ReleaseStringUTFChars(env, name, namePtr);
		jstring jstr = (*env)->NewStringUTF(env, str);
		free(buf);
		return jstr;
	}


	throwUnknownError(env, ERROR_BUSY);
	return NULL;

}

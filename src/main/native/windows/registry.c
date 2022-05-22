#include "../common/jni/io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil.h"
#include "../common/common.h"

#include <windows.h>
#include <winreg.h>
#include <errhandlingapi.h>
#include <stdio.h>

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegOpenKeyExA
 * Signature: (JLjava/lang/String;II)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_RegOpenKeyExA
  (JNIEnv * env, jobject inst, jlong hkey, jstring subKey, jint options, jint sam) {

	LPCSTR subKeyS = NULL;

	if (subKey != NULL) {
		subKeyS = (*env)->GetStringUTFChars(env, subKey, NULL);
		if (subKeyS == NULL) {
			throwOOM(env, "GetStringUTFChars");
			return 0;
		}
	}

	HKEY out;
	LONG err = RegOpenKeyExA((HKEY) (uintptr_t) hkey, subKeyS, (DWORD) options, (REGSAM) sam, &out);

	if (subKey != NULL) {
		(*env)->ReleaseStringUTFChars(env, subKey, subKeyS);
	}

	if (err == ERROR_SUCCESS) {
		return (jlong) (uintptr_t) out;
	}

	throwUnknownError(env, err);
	return 0;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegCloseKey
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_RegCloseKey
  (JNIEnv * env, jobject inst, jlong hkey) {
	LONG err = RegCloseKey((HKEY) (uintptr_t) hkey);
	if (err == ERROR_SUCCESS) {
		return;
	}

	throwUnknownError(env, err);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegQueryValueExA
 * Signature: (JLjava/lang/String;)Lio/github/alexanderschuetz97/nativeutils/api/structs/RegData;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_RegQueryValueExA
  (JNIEnv * env, jobject inst, jlong hkey, jstring valueName) {


	jbyteArray bytes = NULL;
	jstring str;
	jobject ret = NULL;
	void * vdata = NULL;
	LPCSTR valueNameS = NULL;

	if (valueName != NULL) {
		valueNameS = (*env)->GetStringUTFChars(env, valueName, NULL);
		if (valueNameS == NULL) {
			throwOOM(env, "GetStringUTFChars");
			goto clean;
		}
	}

	DWORD type = 0;
	void * data = (void*) "";
	DWORD len = 0;
	LONG err = RegQueryValueExA((HKEY) (uintptr_t) hkey, valueNameS, 0, &type, (LPBYTE) data, &len);
	if (err == ERROR_SUCCESS) {
		len = 0;
		goto parseData;
	}


	if (err != ERROR_MORE_DATA) {
		throwUnknownError(env, err);
		goto clean;
	}


	data = malloc(len+1);
	vdata = data;
	if (data == NULL) {
		throwOOM(env, "malloc");
		goto clean;
	}

	memset(data, 0, len+1);

	type = 0;
	err = RegQueryValueExA((HKEY) (uintptr_t) hkey, valueNameS, 0, &type, (LPBYTE) data, &len);
	if (err != ERROR_SUCCESS) {
		throwUnknownError(env, err);
		goto clean;
	}


	parseData:

	switch(type) {
	//TODO ENDIAN SUPPORT ?
	case REG_MULTI_SZ: {
		const char * charBuf = (const char*) data;
		int count = 0;

		for (int i = 0; i < len; i++) {
			if (charBuf[i] == 0) {
				count++;
			}
		}

		jobjectArray stringArray = (*env)->NewObjectArray(env, count, String_Class, NULL);
		if (stringArray == NULL) {
			throwOOM(env, "NewObjectArray");
			goto clean;
		}

		int off = 0;
		for (int i = 0; i < count; i++) {
			jstring nstring = (*env)->NewStringUTF(env, &charBuf[off]);
			if (nstring == NULL) {
				throwOOM(env, "NewStringUTF");
				goto clean;
			}
			off = strlen(&charBuf[off]+1);
			if (off >= len) {
				break;
			}

			(*env)->SetObjectArrayElement(env, stringArray, i, nstring);
			(*env)->DeleteLocalRef(env, nstring);
		}

		ret = (*env)->NewObject(env, RegData, RegData_Object, stringArray, RegData_types[4]);
		goto clean;
	}
	case REG_EXPAND_SZ:
		str = (*env)->NewStringUTF(env, (const char*) data);
		if (str == NULL) {
			throwOOM(env, "NewStringUTF");
			goto clean;
		}
		ret = (*env)->NewObject(env, RegData, RegData_Object, str, RegData_types[2]);
		goto clean;
	case REG_LINK:
		str = (*env)->NewStringUTF(env, (const char*) data);
		if (str == NULL) {
			throwOOM(env, "NewStringUTF");
			goto clean;
		}
		ret = (*env)->NewObject(env, RegData, RegData_Object, str, RegData_types[3]);
		goto clean;
	case REG_SZ:
		str = (*env)->NewStringUTF(env, (const char*) data);
		if (str == NULL) {
			throwOOM(env, "NewStringUTF");
			goto clean;
		}
		ret = (*env)->NewObject(env, RegData, RegData_Object, str, RegData_types[7]);
		goto clean;
	case REG_QWORD:
		if (len < 8) {
			throwUnknownError(env, ERROR_INVALID_USER_BUFFER);
			goto clean;
		}
		jlong* lptr = (jlong*) data;
		ret = (*env)->NewObject(env, RegData, RegData_Long, *lptr);
		goto clean;
	case REG_DWORD:
		if (len < 4) {
			throwUnknownError(env, ERROR_INVALID_USER_BUFFER);
			goto clean;
		}
		jint* iptr = (jint*) data;
		ret = (*env)->NewObject(env, RegData, RegData_Int, *iptr);
		goto clean;
	case REG_BINARY:
		bytes = (*env)->NewByteArray(env, len);
		if (bytes == NULL) {
			throwOOM(env, "NewByteArray");
			goto clean;
		}

		ret = (*env)->NewObject(env, RegData, RegData_Object, bytes, RegData_types[0]);
		goto clean;
	case REG_NONE:
	default:
		bytes = (*env)->NewByteArray(env, len);
		if (bytes == NULL) {
			throwOOM(env, "NewByteArray");
			goto clean;
		}

		ret = (*env)->NewObject(env, RegData, RegData_Object, bytes, RegData_types[5]);
		goto clean;
	}


	clean:
	if (valueName != NULL) {
		(*env)->ReleaseStringUTFChars(env, valueName, valueNameS);
	}
	if (vdata != NULL) {
		free(vdata);
	}
	return ret;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegQueryInfoKeyA
 * Signature: (J)Lio/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_RegQueryInfoKeyA
  (JNIEnv * env, jobject inst, jlong hkey) {
	DWORD lpcchClass = 0;
	DWORD lpcSubKeys;
	DWORD lpcbMaxSubKeyLen;
	DWORD lpcbMaxClassLen;
	DWORD lpcValues;
	DWORD lpcbMaxValueNameLen;
	DWORD lpcbMaxValueLen;
	DWORD lpcbSecurityDescriptor;
	FILETIME lpftLastWriteTime;
	char * lpClass = NULL;
	jobject result = NULL;

	LSTATUS ret = RegQueryInfoKeyA((HKEY)(uintptr_t) hkey,
			NULL,
			&lpcchClass,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL);

	if (ret != ERROR_SUCCESS) {
		throwUnknownError(env, ret);
		goto cleanup;
	}

	if (lpcchClass < 0) {
		lpcchClass = 0;
	}


	lpcchClass++;
	lpClass = malloc(lpcchClass + 1);
	if (lpClass == NULL) {
		throwOOM(env, "malloc");
		goto cleanup;
	}

	memset((void*) lpClass, 0, lpcchClass + 1);

	ret = RegQueryInfoKeyA((HKEY)(uintptr_t) hkey,
			lpClass,
			&lpcchClass,
			NULL,
			&lpcSubKeys,
			&lpcbMaxSubKeyLen,
			&lpcbMaxClassLen,
			&lpcValues,
			&lpcbMaxValueNameLen,
			&lpcbMaxValueLen,
			&lpcbSecurityDescriptor,
			&lpftLastWriteTime);

	if (ret != ERROR_SUCCESS) {
		throwUnknownError(env, ret);
		goto cleanup;
	}

	jstring jlpClass = (*env)->NewStringUTF(env, lpClass);

	if (jlpClass == NULL) {
		throwOOM(env, "NewStringUTF");
		goto cleanup;
	}


	result = (*env)->NewObject(env, RegQueryInfoKeyResult_Class, RegQueryInfoKeyResult_Constructor);
	if (result == NULL) {
		throwOOM(env, "NewObject");
		goto cleanup;
	}


	(*env)->SetObjectField(env, result, RegQueryInfoKeyResult_keyClass, jlpClass);
	(*env)->SetIntField(env, result, RegQueryInfoKeyResult_subKeys, lpcSubKeys);
	(*env)->SetIntField(env, result, RegQueryInfoKeyResult_maxSubKeyLen, lpcbMaxSubKeyLen);
	(*env)->SetIntField(env, result, RegQueryInfoKeyResult_maxClassLen, lpcbMaxClassLen);
	(*env)->SetIntField(env, result, RegQueryInfoKeyResult_values, lpcValues);
	(*env)->SetIntField(env, result, RegQueryInfoKeyResult_maxValueNameLen, lpcbMaxValueNameLen);
	(*env)->SetIntField(env, result, RegQueryInfoKeyResult_maxValueLen, lpcbMaxValueLen);
	(*env)->SetIntField(env, result, RegQueryInfoKeyResult_securityDescriptorSize, lpcbSecurityDescriptor);

	uint64_t temp = lpftLastWriteTime.dwHighDateTime;
	temp <<= 32;
	temp += lpftLastWriteTime.dwLowDateTime;

	(*env)->SetLongField(env, result, RegQueryInfoKeyResult_lastWriteTime, temp);




	cleanup:
	if (lpClass != NULL) {
		free((void*)lpClass);
	}

	return result;






}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegEnumKeyA
 * Signature: (JII)Ljava/lang/String;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_RegEnumKeyExA
  (JNIEnv * env, jobject inst, jlong hkey, jint index, jint nameSize, jint classSize) {
	if (nameSize <= 0 || classSize <= 0) {
		DWORD nsize = 0;
		DWORD csize = 0;
		LSTATUS ret = RegQueryInfoKeyA((HKEY)(uintptr_t) hkey,
			NULL,
			NULL,
			NULL, //RES
			NULL,
			&nsize,
			&csize,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL);

		if (ret != ERROR_SUCCESS) {
			throwUnknownError(env, ret);
			return NULL;
		}

		nameSize = nsize;
		classSize = csize;
	}



	nameSize++;
	classSize++;
	char * cmem = NULL;
	char * nmem = NULL;
	jobject obj = NULL;


	cmem = (char*) malloc(classSize+1);
	if (cmem == NULL) {
		throwOOM(env, "malloc");
		return NULL;
	}

	nmem = (char*) malloc(nameSize+1);
	if (nmem == NULL) {
		throwOOM(env, "malloc");
		goto cleanup;
	}

	memset((void*) cmem, 0, classSize+1);
	memset((void*) nmem, 0, nameSize+1);

	DWORD nsize = nameSize;
	DWORD csize = classSize;
	FILETIME ftime;

	LSTATUS ret = RegEnumKeyExA((HKEY)(uintptr_t) hkey, (DWORD) index, nmem, &nsize, NULL, cmem, &csize, &ftime);

	if (ret == ERROR_NO_MORE_ITEMS) {
		goto cleanup;
	}

	if (ret != ERROR_SUCCESS) {
		throwUnknownError(env, ret);
		goto cleanup;
	}

	jstring jname = (*env)->NewStringUTF(env, (const char *) nmem);
	if (jname == NULL) {
		throwOOM(env, "NewStringUTF");
		goto cleanup;
	}

	jstring jclass = (*env)->NewStringUTF(env, (const char *) cmem);
	if (jclass == NULL) {
		throwOOM(env, "NewStringUTF");
		goto cleanup;
	}

	uint64_t jtime = ftime.dwHighDateTime;
	jtime <<= 32;
	jtime += ftime.dwLowDateTime;

	obj = (*env)->NewObject(env, RegEnumKeyExResult_Class, RegEnumKeyExResult_Constructor);
	if (obj == NULL) {
		throwOOM(env, "NewObject");
		goto cleanup;
	}
	(*env)->SetObjectField(env, obj, RegEnumKeyExResult_name, jname);
	(*env)->SetObjectField(env, obj, RegEnumKeyExResult_className, jclass);
	(*env)->SetLongField(env, obj, RegEnumKeyExResult_lastWriteTime, jtime);

	cleanup:
	if (cmem != NULL) {
		free((void*) cmem);
	}

	if (nmem != NULL) {
		free((void *) nmem);
	}

	return obj;
}

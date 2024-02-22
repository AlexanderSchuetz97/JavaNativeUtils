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
#include "../common/jni/eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil.h"
#include "../common/common.h"

#include <windows.h>
#include <winreg.h>
#include <errhandlingapi.h>
#include <stdio.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegOpenKeyExA
 * Signature: (JLjava/lang/String;II)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegOpenKeyExA
  (JNIEnv * env, jobject inst, jlong hkey, jstring subKey, jint options, jint sam) {

	LPCSTR subKeyS = NULL;

	if (subKey != NULL) {
		subKeyS = (*env)->GetStringUTFChars(env, subKey, NULL);
		if (subKeyS == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
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

	jthrow_UnknownNativeErrorException_1(env, err);
	return 0;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegCloseKey
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegCloseKey
  (JNIEnv * env, jobject inst, jlong hkey) {
	LONG err = RegCloseKey((HKEY) (uintptr_t) hkey);
	if (err == ERROR_SUCCESS) {
		return;
	}

	jthrow_UnknownNativeErrorException_1(env, err);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegQueryValueExA
 * Signature: (JLjava/lang/String;)Leu/aschuetz/nativeutils/api/structs/RegData;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegQueryValueExA
  (JNIEnv * env, jobject inst, jlong hkey, jstring valueName) {


	jbyteArray bytes = NULL;
	jstring str;
	jobject ret = NULL;
	void * vdata = NULL;
	LPCSTR valueNameS = NULL;

	if (valueName != NULL) {
		valueNameS = (*env)->GetStringUTFChars(env, valueName, NULL);
		if (valueNameS == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
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
		jthrow_UnknownNativeErrorException_1(env, err);
		goto clean;
	}


	data = malloc(len+1);
	vdata = data;
	if (data == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "malloc");
		goto clean;
	}

	memset(data, 0, len+1);

	type = 0;
	err = RegQueryValueExA((HKEY) (uintptr_t) hkey, valueNameS, 0, &type, (LPBYTE) data, &len);
	if (err != ERROR_SUCCESS) {
		jthrow_UnknownNativeErrorException_1(env, err);
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

		jobjectArray stringArray = jStringArray(env, count);
		if (stringArray == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "NewObjectArray");
			goto clean;
		}

		int off = 0;
		for (int i = 0; i < count; i++) {
			jstring nstring = (*env)->NewStringUTF(env, &charBuf[off]);
			if (nstring == NULL) {
				jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
				goto clean;
			}
			off = strlen(&charBuf[off]+1);
			if (off >= len) {
				break;
			}

			(*env)->SetObjectArrayElement(env, stringArray, i, nstring);
			(*env)->DeleteLocalRef(env, nstring);
		}

		ret = jnew_RegData_2(env, stringArray, jenum_RegData$RegType_REG_MULTI_SZ());
		goto clean;
	}
	case REG_EXPAND_SZ:
		str = (*env)->NewStringUTF(env, (const char*) data);
		if (str == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
			goto clean;
		}

		ret = jnew_RegData_2(env, str, jenum_RegData$RegType_REG_EXPAND_SZ());
		goto clean;
	case REG_LINK:
		str = (*env)->NewStringUTF(env, (const char*) data);
		if (str == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
			goto clean;
		}
		ret = jnew_RegData_2(env, str, jenum_RegData$RegType_REG_LINK());
		goto clean;
	case REG_SZ:
		str = (*env)->NewStringUTF(env, (const char*) data);
		if (str == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
			goto clean;
		}

		ret = jnew_RegData_2(env, str, jenum_RegData$RegType_REG_SZ());
		goto clean;
	case REG_QWORD:
		if (len < 8) {
			jthrow_UnknownNativeErrorException_1(env, ERROR_INVALID_USER_BUFFER);
			goto clean;
		}
		jlong* lptr = (jlong*) data;
		ret = jnew_RegData_1(env, *lptr);
		goto clean;
	case REG_DWORD:
		if (len < 4) {
			jthrow_UnknownNativeErrorException_1(env, ERROR_INVALID_USER_BUFFER);
			goto clean;
		}
		jint* iptr = (jint*) data;
		ret = jnew_RegData(env, *iptr);
		goto clean;
	case REG_BINARY:
		bytes = jarrayB(env, (jbyte*) data, len);
		if (bytes == NULL) {
			goto clean;
		}

		ret = jnew_RegData_2(env, bytes, jenum_RegData$RegType_REG_BINARY());
		goto clean;
	case REG_NONE:
	default:
		bytes = jarrayB(env, (jbyte*) data, len);
		if (bytes == NULL) {
			goto clean;
		}

		ret = jnew_RegData_2(env, bytes, jenum_RegData$RegType_REG_NONE());
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
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegEnumValueA
 * Signature: (JI)Leu/aschuetz/nativeutils/api/structs/RegEnumValueResult;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegEnumValueA
        (JNIEnv * env, jobject inst, jlong hkey, jint index) {

    jbyteArray bytes = NULL;
    jstring str = NULL;
    jstring jname = NULL;

    void * vdata = NULL;
    jobject retValue = NULL;
    jobject regData = NULL;

    DWORD type = 0;
    DWORD nameLen = 4096;
    char * name = (char*) malloc(nameLen+1);
    if (name == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "malloc");
        return NULL;
    }
    memset((void*)name, 0, nameLen+1);

    void * data = (void*) "";
    DWORD dataLen = 0;
    LONG result = RegEnumValueA((HKEY) (uintptr_t) hkey, (DWORD) index, (LPSTR) name, &nameLen,NULL,&type,(LPBYTE)data,&dataLen);
    if (result == ERROR_SUCCESS) {
        goto parse;
    }

    if (result == ERROR_NO_MORE_ITEMS) {
        goto clean;
    }

    if (result != ERROR_MORE_DATA) {
        jthrow_UnknownNativeErrorException_1(env, (jlong) result);
        goto clean;
    }

    if (dataLen != 0) {
        vdata = malloc(dataLen+1);
        memset(vdata, 0, dataLen+1);
        if (vdata == NULL) {
            jthrowCC_OutOfMemoryError_1(env, "malloc");
            goto clean;
        }
        data = vdata;
    }

    if (nameLen != 0) {
        free(name);
        name = (char*) malloc(nameLen+1);
        if (name == NULL) {
            jthrowCC_OutOfMemoryError_1(env, "malloc");
            goto clean;
        }
        memset((void*)name, 0, nameLen+1);
    }

    DWORD dataLenBase = dataLen;

    while(true) {
        result = RegEnumValueA((HKEY) (uintptr_t) hkey, (DWORD) index, (LPSTR) name, &nameLen,NULL,&type,(LPBYTE)data,&dataLen);
        if (result == ERROR_SUCCESS) {
            goto parse;
        }

        if (result == ERROR_MORE_DATA) {
            if (dataLenBase != dataLen) {
                free(vdata);
                vdata = malloc(dataLen+1);
                if (vdata == NULL) {
                    jthrowCC_OutOfMemoryError_1(env, "malloc");
                    goto clean;
                }

                memset((void*) vdata, 0, dataLen+1);

                data = vdata;
                dataLenBase = dataLen;
            }

            if (nameLen > 0x10000) {
                jthrow_UnknownNativeErrorException_1(env, (jlong) result);
                goto clean;
            }
            free(name);


            nameLen+=4096;
            name = (char*) malloc(nameLen+1);
            if (name == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "malloc");
                goto clean;
            }
            memset((void*)name, 0, nameLen+1);
            continue;
        }


        jthrow_UnknownNativeErrorException_1(env, (jlong) result);
        goto clean;

    }


parse:
    switch(type) {
        //TODO ENDIAN SUPPORT ?
        case REG_MULTI_SZ: {
            const char * charBuf = (const char*) data;
            int count = 0;

            for (int i = 0; i < dataLen; i++) {
                if (charBuf[i] == 0) {
                    count++;
                }
            }

            jobjectArray stringArray = jStringArray(env, count);
            if (stringArray == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "NewObjectArray");
                goto clean;
            }

            int off = 0;
            for (int i = 0; i < count; i++) {
                jstring nstring = (*env)->NewStringUTF(env, &charBuf[off]);
                if (nstring == NULL) {
                    jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
                    goto clean;
                }
                off = strlen(&charBuf[off]+1);
                if (off >= dataLen) {
                    break;
                }

                (*env)->SetObjectArrayElement(env, stringArray, i, nstring);
                (*env)->DeleteLocalRef(env, nstring);
            }

            regData = jnew_RegData_2(env, stringArray, jenum_RegData$RegType_REG_MULTI_SZ());
            goto assemble;
        }
        case REG_EXPAND_SZ:
            str = (*env)->NewStringUTF(env, (const char*) data);
            if (str == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
                goto clean;
            }

            regData = jnew_RegData_2(env, str, jenum_RegData$RegType_REG_EXPAND_SZ());
            goto assemble;
        case REG_LINK:
            str = (*env)->NewStringUTF(env, (const char*) data);
            if (str == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
                goto clean;
            }
            regData = jnew_RegData_2(env, str, jenum_RegData$RegType_REG_LINK());
            goto assemble;
        case REG_SZ:
            str = (*env)->NewStringUTF(env, (const char*) data);
            if (str == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
                goto clean;
            }

            regData = jnew_RegData_2(env, str, jenum_RegData$RegType_REG_SZ());
            goto assemble;
        case REG_QWORD:
            if (dataLen < 8) {
                jthrow_UnknownNativeErrorException_1(env, ERROR_INVALID_USER_BUFFER);
                goto clean;
            }
            jlong* lptr = (jlong*) data;
            regData = jnew_RegData_1(env, *lptr);
            goto assemble;
        case REG_DWORD:
            if (dataLen < 4) {
                jthrow_UnknownNativeErrorException_1(env, ERROR_INVALID_USER_BUFFER);
                goto clean;
            }
            jint* iptr = (jint*) data;
            regData = jnew_RegData(env, *iptr);
            goto assemble;
        case REG_BINARY:
            bytes = jarrayB(env, (jbyte*) data, (jsize) dataLen);
            if (bytes == NULL) {
                goto clean;
            }

            regData = jnew_RegData_2(env, bytes, jenum_RegData$RegType_REG_BINARY());
            goto assemble;
        case REG_NONE:
        default:
            bytes = jarrayB(env, (jbyte*) data, (jsize) dataLen);
            if (bytes == NULL) {
                goto clean;
            }

            regData = jnew_RegData_2(env, bytes, jenum_RegData$RegType_REG_NONE());
            goto assemble;
    }

assemble:
    if (regData == NULL) {
        goto clean;
    }

    jname = (*env)->NewStringUTF(env, (const char*) name);
    if (jname == NULL) {
        goto clean;
    }
    retValue = jnew_RegEnumValueResult_1(env, jname, regData);
    goto clean;
clean:
    if (vdata != NULL) {
        free(vdata);
    }

    if (name != NULL) {
        free(name);
    }
    return retValue;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegQueryInfoKeyA
 * Signature: (J)Leu/aschuetz/nativeutils/api/structs/RegQueryInfoKeyResult;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegQueryInfoKeyA
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
		jthrow_UnknownNativeErrorException_1(env, ret);
		goto cleanup;
	}

	if (lpcchClass < 0) {
		lpcchClass = 0;
	}


	lpcchClass++;
	lpClass = malloc(lpcchClass + 1);
	if (lpClass == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "malloc");
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
		jthrow_UnknownNativeErrorException_1(env, ret);
		goto cleanup;
	}

	jstring jlpClass = (*env)->NewStringUTF(env, lpClass);

	if (jlpClass == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
		goto cleanup;
	}



	result = jnew_RegQueryInfoKeyResult(env);
	if (result == NULL) {
		goto cleanup;
	}

	jset_RegQueryInfoKeyResult_keyClass(env, result, jlpClass);
	jset_RegQueryInfoKeyResult_subKeys(env, result, lpcSubKeys);
	jset_RegQueryInfoKeyResult_maxSubKeyLen(env, result, lpcbMaxSubKeyLen);
	jset_RegQueryInfoKeyResult_maxClassLen(env, result, lpcbMaxClassLen);
	jset_RegQueryInfoKeyResult_values(env, result, lpcValues);
	jset_RegQueryInfoKeyResult_maxValueNameLen(env, result, lpcbMaxValueNameLen);
	jset_RegQueryInfoKeyResult_maxValueLen(env, result, lpcbMaxValueLen);
	jset_RegQueryInfoKeyResult_securityDescriptorSize(env, result, lpcbSecurityDescriptor);

	uint64_t temp = lpftLastWriteTime.dwHighDateTime;
	temp <<= 32;
	temp += lpftLastWriteTime.dwLowDateTime;


	jset_RegQueryInfoKeyResult_lastWriteTime(env, result, temp);

	cleanup:
	if (lpClass != NULL) {
		free((void*)lpClass);
	}

	return result;






}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegEnumKeyA
 * Signature: (JII)Ljava/lang/String;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegEnumKeyExA
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
			jthrow_UnknownNativeErrorException_1(env, ret);
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
		jthrowCC_OutOfMemoryError_1(env, "malloc");
		return NULL;
	}

	nmem = (char*) malloc(nameSize+1);
	if (nmem == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "malloc");
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
		jthrow_UnknownNativeErrorException_1(env, ret);
		goto cleanup;
	}

	jstring jname = (*env)->NewStringUTF(env, (const char *) nmem);
	if (jname == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
		goto cleanup;
	}

	jstring jclass = (*env)->NewStringUTF(env, (const char *) cmem);
	if (jclass == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
		goto cleanup;
	}

	uint64_t jtime = ftime.dwHighDateTime;
	jtime <<= 32;
	jtime += ftime.dwLowDateTime;

	obj = jnew_RegEnumKeyExResult(env);
	if (obj == NULL) {
		goto cleanup;
	}
	jset_RegEnumKeyExResult_className(env, obj, jclass);
	jset_RegEnumKeyExResult_name(env, obj, jname);
	jset_RegEnumKeyExResult_lastWriteTime(env, obj, jtime);

	cleanup:
	if (cmem != NULL) {
		free((void*) cmem);
	}

	if (nmem != NULL) {
		free((void *) nmem);
	}

	return obj;
}

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
#include "../common/jni/io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil.h"
#include "../common/common.h"
#include <windows.h>
#include <setupapi.h>
#include <assert.h>

static_assert(sizeof(ULONG_PTR) <= sizeof(jlong), "ULONG_PTR doesnt fit in jlong");

jobject GUID_to_java(JNIEnv* env, GUID * guid, jobject mapped) {

	if (mapped == NULL) {
		mapped = jnew_GUID(env);
		if (mapped == NULL) {
			return NULL;
		}
	}

	jset_GUID_data1(env, mapped, guid->Data1);
	jset_GUID_data2(env, mapped, guid->Data2);
	jset_GUID_data3(env, mapped, guid->Data3);

	jbyteArray array = jget_GUID_data4(env, mapped);
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "GUID.data4");
		return NULL;
	}

	if ((*env)->GetArrayLength(env, array) != 8) {
		jthrowCC_IllegalArgumentException_1(env, "GUID.data4.length != 8");
		return NULL;
	}

	(*env)->SetByteArrayRegion(env, array, 0, 8, (jbyte*)guid->Data4);
	(*env)->DeleteLocalRef(env, array);

	return mapped;
}

jboolean GUID_to_c(JNIEnv* env, GUID * guid, jobject mapped) {
	if (mapped == NULL) {
		memset(guid, 0, sizeof(GUID));
		return true;
	}

	guid->Data1 = jget_GUID_data1(env, mapped);
	guid->Data2 = jget_GUID_data2(env, mapped);
	guid->Data3 = jget_GUID_data3(env, mapped);

	memset(guid->Data4, 0, 8);

	//If the array is null someone sudoed it with reflection.
	jbyteArray array = jget_GUID_data4(env, mapped);
	if (array == NULL) {
		jthrowCC_NullPointerException_1(env, "GUID.data4");
		return false;
	}

	if ((*env)->GetArrayLength(env, array) != 8) {
		jthrowCC_IllegalArgumentException_1(env, "GUID.data4.length != 8");
		return false;
	}


	(*env)->GetByteArrayRegion(env, array, 0, 8, (jbyte*)guid->Data4);
	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiGetClassDevsA
 * Signature: (Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;Ljava/lang/String;JI)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_SetupDiGetClassDevsA
  (JNIEnv * env, jobject inst, jobject jguid, jstring enumerator, jlong parent, jint flags) {

	GUID* cguidPtr = NULL;
	GUID cguid;
	if (jguid != NULL) {
		cguidPtr = &cguid;
		if (!GUID_to_c(env, cguidPtr, jguid)) {
			return 0;
		}
	}

	const char* cPtr = NULL;
	if (enumerator != NULL) {
		cPtr = (*env)->GetStringUTFChars(env, enumerator, NULL);
		if (cPtr == NULL) {
			jthrowCC_OutOfMemoryError_1(env, "GetStringUTFChars");
			return 0;
		}
	}

	HDEVINFO info = SetupDiGetClassDevsA(cguidPtr, cPtr, (HWND) (uintptr_t) parent, (DWORD) flags);
	if (info == INVALID_HANDLE_VALUE) {
		if (cPtr != NULL) {
			(*env)->ReleaseStringUTFChars(env, enumerator, cPtr);
		}

		jthrow_UnknownNativeErrorException_1(env, GetLastError());
		return 0;
	}

	if (cPtr != NULL) {
		(*env)->ReleaseStringUTFChars(env, enumerator, cPtr);
	}

	return (jlong) (uintptr_t) info;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiEnumDeviceInterfaces
 * Signature: (JLio/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInfoData;Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;I)Lio/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInterfaceData;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_SetupDiEnumDeviceInterfaces
  (JNIEnv * env, jobject inst, jlong jptr, jobject jdevInfo, jobject jguid, jint index) {

	if (jguid == NULL) {
		jthrowCC_NullPointerException_1(env, "guid");
		return NULL;
	}

	GUID cguid;
	GUID* cguidPtr = &cguid;

	cguidPtr = &cguid;
	if (!GUID_to_c(env, cguidPtr, jguid)) {
		return NULL;
	}


	PSP_DEVINFO_DATA cInfoPtr = NULL;
	SP_DEVINFO_DATA cInfo;
	if (jdevInfo != NULL) {
		cInfoPtr = &cInfo;

		cInfo.cbSize = jget_SpDeviceInfoData_cbSize(env, jdevInfo);
		cInfo.DevInst = jget_SpDeviceInfoData_DevInst(env, jdevInfo);
		cInfo.Reserved = jget_SpDeviceInfoData_ptr(env, jdevInfo);

		if (!GUID_to_c(env, &cInfo.ClassGuid, jget_SpDeviceInfoData_InterfaceClassGuid(env, jdevInfo))) {
			return NULL;
		}
	}

	SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;

	//OTHERWISE we get some error!
	memset(&DeviceInterfaceData, 0, sizeof(SP_DEVICE_INTERFACE_DATA));
	DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	if (!SetupDiEnumDeviceInterfaces((HDEVINFO)(uintptr_t) jptr, cInfoPtr, cguidPtr, (DWORD) index, &DeviceInterfaceData)) {
		DWORD err = GetLastError();
		if (err == ERROR_NO_MORE_ITEMS) {
			return NULL;
		}

		jthrow_UnknownNativeErrorException_1(env, err);
		return NULL;
	}

	jobject did = jnew_SpDeviceInfoData(env);
	if (did == NULL) {
		return NULL;
	}


	jobject nguid = jget_SpDeviceInfoData_InterfaceClassGuid(env, jdevInfo);
	if (nguid == NULL) {
		//Shouldnt be possible
		jthrowCC_NullPointerException_1(env, "SpDeviceInfoData.InterfaceClassGuid");
		return NULL;
	}

	GUID_to_java(env, &DeviceInterfaceData.InterfaceClassGuid, nguid);

	jset_SpDeviceInterfaceData_cbSize(env, did, DeviceInterfaceData.cbSize);
	jset_SpDeviceInterfaceData_flags(env, did, DeviceInterfaceData.Flags);
	jset_SpDeviceInterfaceData_ptr(env, did, DeviceInterfaceData.Reserved);

	return did;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiGetDeviceInterfaceDetail
 * Signature: (JLio/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInterfaceData;Lio/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInfoData;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_SetupDiGetDeviceInterfaceDetail
  (JNIEnv * env, jobject inst, jlong jptr, jobject jdifd, jobject jdid) {

	jstring res = NULL;
	SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;

	DeviceInterfaceData.cbSize = jget_SpDeviceInterfaceData_cbSize(env, jdifd);
	DeviceInterfaceData.Flags = jget_SpDeviceInterfaceData_flags(env, jdifd);
	DeviceInterfaceData.Reserved = jget_SpDeviceInterfaceData_ptr(env, jdifd);

	if (!GUID_to_c(env, &DeviceInterfaceData.InterfaceClassGuid, jget_SpDeviceInterfaceData_InterfaceClassGuid(env, jdifd))) {
		return NULL;
	}

	PSP_DEVINFO_DATA devinfoPtr = NULL;
	SP_DEVINFO_DATA devInfo;
	if (jdid != NULL) {
		devinfoPtr = &devInfo;
		//OTHERWISE we get some error!
		memset(devinfoPtr, 0, sizeof(SP_DEVINFO_DATA));
		devInfo.cbSize = sizeof(SP_DEVINFO_DATA);
	}


	DWORD RequiredSize = 0;

	WINBOOL result = SetupDiGetDeviceInterfaceDetailA(
			(HDEVINFO)(uintptr_t) jptr,
			&DeviceInterfaceData, NULL, 0, &RequiredSize, devinfoPtr);

	if (result) {
		// should never happen
		res = (*env)->NewStringUTF(env, "");
		goto mapResultAndReturn;
	}

	DWORD err = GetLastError();

	if (err != ERROR_INSUFFICIENT_BUFFER) {
		jthrow_UnknownNativeErrorException_1(env, err);
		return NULL;
	}

	if (RequiredSize < sizeof(DWORD)) {
		//should never happen. This buffer would be smaller than the length prefix.
		jthrow_UnknownNativeErrorException_1(env, -1);
		return NULL;
	}

	PSP_DEVICE_INTERFACE_DETAIL_DATA_A dptr = malloc(RequiredSize+1);

	if (dptr == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "malloc");
		return NULL;
	}

	memset(dptr, 0, RequiredSize+1);
	dptr->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);


	if (!SetupDiGetDeviceInterfaceDetailA((HDEVINFO)(uintptr_t) jptr, &DeviceInterfaceData, dptr,  RequiredSize, NULL, devinfoPtr)) {
		free(dptr);
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
		return NULL;
	}


	char* buf = (char*) dptr;
	buf[RequiredSize] = 0;

	res = (*env)->NewStringUTF(env, (const char*) dptr->DevicePath);
	free(dptr);

	mapResultAndReturn:

	if (res == NULL) {
		jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
		return NULL;
	}

	if (devinfoPtr != NULL) {
		jset_SpDeviceInfoData_cbSize(env, jdid, devInfo.cbSize);
		jset_SpDeviceInfoData_DevInst(env, jdid, devInfo.DevInst);
		jset_SpDeviceInfoData_ptr(env, jdid, devInfo.Reserved);
		jset_SpDeviceInfoData_InterfaceClassGuid(env, jdid, GUID_to_java(env, &devInfo.ClassGuid, NULL));
	}

	return res;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiDestroyDeviceInfoList
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_SetupDiDestroyDeviceInfoList
  (JNIEnv * env, jobject inst, jlong jptr) {
	if (!SetupDiDestroyDeviceInfoList((HDEVINFO)(uintptr_t) jptr)) {
		jthrow_UnknownNativeErrorException_1(env, GetLastError());
	}
}

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
		mapped = (*env)->NewObject(env, GUID_Class, GUID_constructor);
		if (mapped == NULL) {
			throwOOM(env, "NewObject");
			return NULL;
		}
	}


	(*env)->SetIntField(env, mapped, GUID_data1, guid->Data1);
	(*env)->SetShortField(env, mapped, GUID_data2, guid->Data2);
	(*env)->SetShortField(env, mapped, GUID_data3, guid->Data3);

	jbyteArray array = (jbyteArray) (*env)->GetObjectField(env, mapped, GUID_data4);
	if (array == NULL) {
		throwNullPointerException(env, "GUID.data4");
		return NULL;
	}

	(*env)->SetByteArrayRegion(env, array, 0, 8, (jbyte*)guid->Data4);

	return mapped;
}

void GUID_to_c(JNIEnv* env, GUID * guid, jobject mapped) {
	if (mapped == NULL) {
		memset(guid, 0, sizeof(GUID));
		return;
	}

	guid->Data1 = (*env)->GetIntField(env, mapped, GUID_data1);
	guid->Data2 = (*env)->GetShortField(env, mapped, GUID_data2);
	guid->Data3 = (*env)->GetShortField(env, mapped, GUID_data3);

	memset(guid->Data4, 0, 8);

	//If the array is null someone sudoed it with reflection.
	jbyteArray array = (jbyteArray) (*env)->GetObjectField(env, mapped, GUID_data4);
	if (array == NULL) {
		throwNullPointerException(env, "GUID.data4");
		return;
	}


	(*env)->GetByteArrayRegion(env, array, 0, 8, (jbyte*)guid->Data4);
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
		GUID_to_c(env, cguidPtr, jguid);
	}

	const char* cPtr = NULL;
	if (enumerator != NULL) {
		cPtr = (*env)->GetStringUTFChars(env, enumerator, NULL);
		if (cPtr == NULL) {
			throwOOM(env, "GetStringUTFChars");
			return 0;
		}
	}

	HDEVINFO info = SetupDiGetClassDevsA(cguidPtr, cPtr, (HWND) (uintptr_t) parent, (DWORD) flags);
	if (info == INVALID_HANDLE_VALUE) {
		if (cPtr != NULL) {
			(*env)->ReleaseStringUTFChars(env, enumerator, cPtr);
		}

		throwUnknownError(env, GetLastError());

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
		throwNullPointerException(env, "guid");
		return NULL;
	}

	GUID cguid;
	GUID* cguidPtr = &cguid;

	cguidPtr = &cguid;
	GUID_to_c(env, cguidPtr, jguid);

	PSP_DEVINFO_DATA cInfoPtr = NULL;
	SP_DEVINFO_DATA cInfo;
	if (jdevInfo != NULL) {
		cInfoPtr = &cInfo;
		cInfo.cbSize = (*env)->GetIntField(env, jdevInfo, SpDeviceInfoData_cbSize);
		cInfo.DevInst = (*env)->GetIntField(env, jdevInfo, SpDeviceInfoData_DevInst);
		cInfo.Reserved = (*env)->GetLongField(env, jdevInfo, SpDeviceInfoData_ptr);
		GUID_to_c(env, &cInfo.ClassGuid, (*env)->GetObjectField(env, jdevInfo, SpDeviceInfoData_InterfaceClassGuid));
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

		throwUnknownError(env, err);
		return NULL;
	}

	jobject did = (*env)->NewObject(env, SpDeviceInterfaceData , SpDeviceInterfaceData_constructor);
	if (did == NULL) {
		throwOOM(env, "NewObject");
		return NULL;
	}


	jobject nguid = (*env)->GetObjectField(env, did, SpDeviceInterfaceData_InterfaceClassGuid);
	if (nguid == NULL) {
		//Shouldnt be possible
		throwNullPointerException(env, "SpDeviceInfoData.InterfaceClassGuid");
		return NULL;
	}

	GUID_to_java(env, &DeviceInterfaceData.InterfaceClassGuid, nguid);

	(*env)->SetIntField(env, did, SpDeviceInterfaceData_cbSize, DeviceInterfaceData.cbSize);
	(*env)->SetIntField(env, did, SpDeviceInterfaceData_flags, DeviceInterfaceData.Flags);
	(*env)->SetLongField(env, did, SpDeviceInterfaceData_ptr, DeviceInterfaceData.Reserved);

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

	DeviceInterfaceData.cbSize = (*env)->GetIntField(env, jdifd, SpDeviceInterfaceData_cbSize);
	DeviceInterfaceData.Flags = (*env)->GetIntField(env, jdifd, SpDeviceInterfaceData_flags);
	DeviceInterfaceData.Reserved = (*env)->GetLongField(env, jdifd, SpDeviceInterfaceData_ptr);
	GUID_to_c(env, &DeviceInterfaceData.InterfaceClassGuid, (*env)->GetObjectField(env, jdifd, SpDeviceInterfaceData_InterfaceClassGuid));

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
		throwUnknownError(env, err);
		return NULL;
	}

	if (RequiredSize < sizeof(DWORD)) {
		//should never happen. This buffer would be smaller than the length prefix.
		throwUnknownError(env, -1);
		return NULL;
	}

	PSP_DEVICE_INTERFACE_DETAIL_DATA_A dptr = malloc(RequiredSize+1);

	if (dptr == NULL) {
		throwOOM(env, "malloc");
		return NULL;
	}

	memset(dptr, 0, RequiredSize+1);
	dptr->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);


	if (!SetupDiGetDeviceInterfaceDetailA((HDEVINFO)(uintptr_t) jptr, &DeviceInterfaceData, dptr,  RequiredSize, NULL, devinfoPtr)) {
		free(dptr);
		throwUnknownError(env, GetLastError());
		return NULL;
	}


	char* buf = (char*) dptr;
	buf[RequiredSize] = 0;

	res = (*env)->NewStringUTF(env, (const char*) dptr->DevicePath);
	free(dptr);

	mapResultAndReturn:

	if (res == NULL) {
		throwOOM(env, "NewStringUTF");
		return NULL;
	}

	if (devinfoPtr != NULL) {
		(*env)->SetIntField(env, jdid, SpDeviceInfoData_cbSize, devInfo.cbSize);
		(*env)->SetIntField(env, jdid, SpDeviceInfoData_DevInst, devInfo.DevInst);
		(*env)->SetLongField(env, jdid, SpDeviceInfoData_ptr, devInfo.Reserved);
		(*env)->SetObjectField(env, jdid, SpDeviceInfoData_InterfaceClassGuid, GUID_to_java(env, &devInfo.ClassGuid, NULL));
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
		throwUnknownError(env, GetLastError());
	}
}

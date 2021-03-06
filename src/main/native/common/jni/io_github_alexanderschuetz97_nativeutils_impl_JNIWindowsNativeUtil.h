/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil */

#ifndef _Included_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
#define _Included_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    LockFileEx
 * Signature: (JZZJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_LockFileEx
  (JNIEnv *, jobject, jlong, jboolean, jboolean, jlong, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    UnlockFileEx
 * Signature: (JJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_UnlockFileEx
  (JNIEnv *, jobject, jlong, jlong, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    getFD
 * Signature: (Ljava/io/FileDescriptor;)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_getFD
  (JNIEnv *, jobject, jobject);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    getHandle
 * Signature: (Ljava/io/FileDescriptor;)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_getHandle
  (JNIEnv *, jobject, jobject);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    _locking
 * Signature: (ILio/github/alexanderschuetz97/nativeutils/api/WindowsNativeUtil/_locking_Mode;J)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil__1locking
  (JNIEnv *, jobject, jint, jobject, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    _stat64
 * Signature: (Ljava/lang/String;)Lio/github/alexanderschuetz97/nativeutils/api/structs/Stat;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil__1stat64
  (JNIEnv *, jobject, jstring);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFileAttributesEx
 * Signature: (Ljava/lang/String;)Lio/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetFileAttributesEx
  (JNIEnv *, jobject, jstring);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateSymbolicLinkA
 * Signature: (Ljava/lang/String;Ljava/lang/String;ZZ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateSymbolicLinkA
  (JNIEnv *, jobject, jstring, jstring, jboolean, jboolean);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateHardLinkA
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateHardLinkA
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateFileA
 * Signature: (Ljava/lang/String;IZZZLio/github/alexanderschuetz97/nativeutils/api/WindowsNativeUtil/CreateFileA_createMode;I)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateFileA
  (JNIEnv *, jobject, jstring, jint, jboolean, jboolean, jboolean, jobject, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateFileW
 * Signature: (Ljava/lang/String;IZZZLio/github/alexanderschuetz97/nativeutils/api/WindowsNativeUtil/CreateFileA_createMode;I)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateFileW
  (JNIEnv *, jobject, jstring, jint, jboolean, jboolean, jboolean, jobject, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CloseHandle
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CloseHandle
  (JNIEnv *, jobject, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiGetClassDevsA
 * Signature: (Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;Ljava/lang/String;JI)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_SetupDiGetClassDevsA
  (JNIEnv *, jobject, jobject, jstring, jlong, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiEnumDeviceInterfaces
 * Signature: (JLio/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInfoData;Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;I)Lio/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInterfaceData;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_SetupDiEnumDeviceInterfaces
  (JNIEnv *, jobject, jlong, jobject, jobject, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiGetDeviceInterfaceDetail
 * Signature: (JLio/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInterfaceData;Lio/github/alexanderschuetz97/nativeutils/api/structs/SpDeviceInfoData;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_SetupDiGetDeviceInterfaceDetail
  (JNIEnv *, jobject, jlong, jobject, jobject);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiDestroyDeviceInfoList
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_SetupDiDestroyDeviceInfoList
  (JNIEnv *, jobject, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DeviceIoControl
 * Signature: (JI[BII[BII)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_DeviceIoControl__JI_3BII_3BII
  (JNIEnv *, jobject, jlong, jint, jbyteArray, jint, jint, jbyteArray, jint, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DeviceIoControl
 * Signature: (JIJJIJJI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_DeviceIoControl__JIJJIJJI
  (JNIEnv *, jclass, jlong, jint, jlong, jlong, jint, jlong, jlong, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateEventA
 * Signature: (JZZLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CreateEventA
  (JNIEnv *, jobject, jlong, jboolean, jboolean, jstring);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ResetEvent
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ResetEvent
  (JNIEnv *, jobject, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WaitForSingleObject
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_WaitForSingleObject
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WaitForMultipleObjects
 * Signature: ([JIZ)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_WaitForMultipleObjects
  (JNIEnv *, jobject, jlongArray, jint, jboolean);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    strerror_s
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_strerror_1s
  (JNIEnv *, jobject, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    FormatMessageA
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_FormatMessageA
  (JNIEnv *, jobject, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetVolumePathNameW
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetVolumePathNameW
  (JNIEnv *, jobject, jstring);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetModuleFileNameA
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetModuleFileNameA
  (JNIEnv *, jobject, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetEnvironmentVariableA
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_SetEnvironmentVariableA
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ExpandEnvironmentStringsA
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ExpandEnvironmentStringsA
  (JNIEnv *, jobject, jstring);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetEnvironmentVariableA
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetEnvironmentVariableA
  (JNIEnv *, jobject, jstring);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFinalPathNameByHandleA
 * Signature: (JZLio/github/alexanderschuetz97/nativeutils/api/WindowsNativeUtil/Path_VolumeName;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetFinalPathNameByHandleA
  (JNIEnv *, jobject, jlong, jboolean, jobject);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFinalPathNameByHandleW
 * Signature: (JZLio/github/alexanderschuetz97/nativeutils/api/WindowsNativeUtil/Path_VolumeName;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetFinalPathNameByHandleW
  (JNIEnv *, jobject, jlong, jboolean, jobject);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFileAttributesA
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetFileAttributesA
  (JNIEnv *, jobject, jstring);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetFileAttributesA
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_SetFileAttributesA
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegOpenKeyExA
 * Signature: (JLjava/lang/String;II)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_RegOpenKeyExA
  (JNIEnv *, jobject, jlong, jstring, jint, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegCloseKey
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_RegCloseKey
  (JNIEnv *, jobject, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegQueryValueExA
 * Signature: (JLjava/lang/String;)Lio/github/alexanderschuetz97/nativeutils/api/structs/RegData;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_RegQueryValueExA
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegQueryInfoKeyA
 * Signature: (J)Lio/github/alexanderschuetz97/nativeutils/api/structs/RegQueryInfoKeyResult;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_RegQueryInfoKeyA
  (JNIEnv *, jobject, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegEnumKeyExA
 * Signature: (JIII)Lio/github/alexanderschuetz97/nativeutils/api/structs/RegEnumKeyExResult;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_RegEnumKeyExA
  (JNIEnv *, jobject, jlong, jint, jint, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCurrentThread
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetCurrentThread
  (JNIEnv *, jobject);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCurrentProcess
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetCurrentProcess
  (JNIEnv *, jobject);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DuplicateHandle
 * Signature: (JJJIZZZ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_DuplicateHandle
  (JNIEnv *, jobject, jlong, jlong, jlong, jint, jboolean, jboolean, jboolean);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CancelIo
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CancelIo
  (JNIEnv *, jobject, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CancelIoEx
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CancelIoEx
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CancelSynchronousIo
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_CancelSynchronousIo
  (JNIEnv *, jobject, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ReadFile
 * Signature: (J[BII)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ReadFile__J_3BII
  (JNIEnv *, jobject, jlong, jbyteArray, jint, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ReadFile
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ReadFile__JJI
  (JNIEnv *, jobject, jlong, jlong, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ReadFile
 * Signature: (JJIJ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_ReadFile__JJIJ
  (JNIEnv *, jobject, jlong, jlong, jint, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WriteFile
 * Signature: (J[BII)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_WriteFile__J_3BII
  (JNIEnv *, jobject, jlong, jbyteArray, jint, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WriteFile
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_WriteFile__JJI
  (JNIEnv *, jobject, jlong, jlong, jint);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WriteFile
 * Signature: (JJIJ)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_WriteFile__JJIJ
  (JNIEnv *, jobject, jlong, jlong, jint, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetOverlappedResult
 * Signature: (JJZ)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetOverlappedResult
  (JNIEnv *, jobject, jlong, jlong, jboolean);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFriendlyIfIndex
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetFriendlyIfIndex
  (JNIEnv *, jobject, jlong);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetAdapterIndex
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetAdapterIndex
  (JNIEnv *, jobject, jstring);

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetAdaptersAddresses
 * Signature: (JJ)Ljava/util/Collection;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetAdaptersAddresses
  (JNIEnv *, jobject, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif

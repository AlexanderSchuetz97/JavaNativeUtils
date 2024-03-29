/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil */

#ifndef _Included_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
#define _Included_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    LockFileEx
 * Signature: (JZZJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_LockFileEx
  (JNIEnv *, jobject, jlong, jboolean, jboolean, jlong, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    UnlockFileEx
 * Signature: (JJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_UnlockFileEx
  (JNIEnv *, jobject, jlong, jlong, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    getFD
 * Signature: (Ljava/io/FileDescriptor;)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_getFD
  (JNIEnv *, jobject, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    getHandle
 * Signature: (Ljava/io/FileDescriptor;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_getHandle
  (JNIEnv *, jobject, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    _locking
 * Signature: (ILeu/aschuetz/nativeutils/api/WindowsNativeUtil/_locking_Mode;J)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil__1locking
  (JNIEnv *, jobject, jint, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    _stat64
 * Signature: (Ljava/lang/String;)Leu/aschuetz/nativeutils/api/structs/Stat;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil__1stat64
  (JNIEnv *, jobject, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFileAttributesEx
 * Signature: (Ljava/lang/String;)Leu/aschuetz/nativeutils/api/structs/Win32FileAttributeData;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetFileAttributesEx
  (JNIEnv *, jobject, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateSymbolicLinkA
 * Signature: (Ljava/lang/String;Ljava/lang/String;ZZ)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CreateSymbolicLinkA
  (JNIEnv *, jobject, jstring, jstring, jboolean, jboolean);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateHardLinkA
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CreateHardLinkA
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateFileA
 * Signature: (Ljava/lang/String;IZZZLeu/aschuetz/nativeutils/api/WindowsNativeUtil/CreateFileA_createMode;I)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CreateFileA
  (JNIEnv *, jobject, jstring, jint, jboolean, jboolean, jboolean, jobject, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateFileW
 * Signature: (Ljava/lang/String;IZZZLeu/aschuetz/nativeutils/api/WindowsNativeUtil/CreateFileA_createMode;I)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CreateFileW
  (JNIEnv *, jobject, jstring, jint, jboolean, jboolean, jboolean, jobject, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateFileMappingA
 * Signature: (JJIIILjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CreateFileMappingA
  (JNIEnv *, jobject, jlong, jlong, jint, jint, jint, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    OpenFileMappingA
 * Signature: (IZLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_OpenFileMappingA
  (JNIEnv *, jobject, jint, jboolean, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    _MapViewOfFileEx
 * Signature: (JIIIIJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil__1MapViewOfFileEx
  (JNIEnv *, jclass, jlong, jint, jint, jint, jint, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    _UnmapViewOfFile
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil__1UnmapViewOfFile
  (JNIEnv *, jclass, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CloseHandle
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CloseHandle
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiGetClassDevsA
 * Signature: (Leu/aschuetz/nativeutils/api/structs/GUID;Ljava/lang/String;JI)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetupDiGetClassDevsA
  (JNIEnv *, jobject, jobject, jstring, jlong, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiEnumDeviceInterfaces
 * Signature: (JLeu/aschuetz/nativeutils/api/structs/SpDeviceInfoData;Leu/aschuetz/nativeutils/api/structs/GUID;I)Leu/aschuetz/nativeutils/api/structs/SpDeviceInterfaceData;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetupDiEnumDeviceInterfaces
  (JNIEnv *, jobject, jlong, jobject, jobject, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiGetDeviceInterfaceDetail
 * Signature: (JLeu/aschuetz/nativeutils/api/structs/SpDeviceInterfaceData;Leu/aschuetz/nativeutils/api/structs/SpDeviceInfoData;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetupDiGetDeviceInterfaceDetail
  (JNIEnv *, jobject, jlong, jobject, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupDiDestroyDeviceInfoList
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetupDiDestroyDeviceInfoList
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DeviceIoControl
 * Signature: (JI[BII[BII)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_DeviceIoControl__JI_3BII_3BII
  (JNIEnv *, jobject, jlong, jint, jbyteArray, jint, jint, jbyteArray, jint, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DeviceIoControl
 * Signature: (JIJJIJJI)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_DeviceIoControl__JIJJIJJI
  (JNIEnv *, jclass, jlong, jint, jlong, jlong, jint, jlong, jlong, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateEventA
 * Signature: (JZZLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CreateEventA
  (JNIEnv *, jobject, jlong, jboolean, jboolean, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    OpenEventA
 * Signature: (IZLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_OpenEventA
  (JNIEnv *, jobject, jint, jboolean, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetEvent
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetEvent
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ResetEvent
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ResetEvent
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WaitForSingleObject
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_WaitForSingleObject
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WaitForMultipleObjects
 * Signature: ([JIZ)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_WaitForMultipleObjects
  (JNIEnv *, jobject, jlongArray, jint, jboolean);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    strerror_s
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_strerror_1s
  (JNIEnv *, jobject, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    FormatMessageA
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_FormatMessageA
  (JNIEnv *, jobject, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetVolumePathNameW
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetVolumePathNameW
  (JNIEnv *, jobject, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetModuleFileNameA
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetModuleFileNameA
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetEnvironmentVariableA
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetEnvironmentVariableA
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ExpandEnvironmentStringsA
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ExpandEnvironmentStringsA
  (JNIEnv *, jobject, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetEnvironmentVariableA
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetEnvironmentVariableA
  (JNIEnv *, jobject, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFinalPathNameByHandleA
 * Signature: (JZLeu/aschuetz/nativeutils/api/WindowsNativeUtil/Path_VolumeName;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetFinalPathNameByHandleA
  (JNIEnv *, jobject, jlong, jboolean, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFinalPathNameByHandleW
 * Signature: (JZLeu/aschuetz/nativeutils/api/WindowsNativeUtil/Path_VolumeName;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetFinalPathNameByHandleW
  (JNIEnv *, jobject, jlong, jboolean, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFileAttributesA
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetFileAttributesA
  (JNIEnv *, jobject, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetFileAttributesA
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetFileAttributesA
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegOpenKeyExA
 * Signature: (JLjava/lang/String;II)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegOpenKeyExA
  (JNIEnv *, jobject, jlong, jstring, jint, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegCloseKey
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegCloseKey
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegQueryValueExA
 * Signature: (JLjava/lang/String;)Leu/aschuetz/nativeutils/api/structs/RegData;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegQueryValueExA
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegQueryInfoKeyA
 * Signature: (J)Leu/aschuetz/nativeutils/api/structs/RegQueryInfoKeyResult;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegQueryInfoKeyA
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegEnumKeyExA
 * Signature: (JIII)Leu/aschuetz/nativeutils/api/structs/RegEnumKeyExResult;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegEnumKeyExA
  (JNIEnv *, jobject, jlong, jint, jint, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    RegEnumValueA
 * Signature: (JI)Leu/aschuetz/nativeutils/api/structs/RegEnumValueResult;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_RegEnumValueA
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCurrentThread
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCurrentThread
  (JNIEnv *, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCurrentProcess
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCurrentProcess
  (JNIEnv *, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DuplicateHandle
 * Signature: (JJJIZZZ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_DuplicateHandle
  (JNIEnv *, jobject, jlong, jlong, jlong, jint, jboolean, jboolean, jboolean);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CancelIo
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CancelIo
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CancelIoEx
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CancelIoEx
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CancelSynchronousIo
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CancelSynchronousIo
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ReadFile
 * Signature: (J[BII)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ReadFile__J_3BII
  (JNIEnv *, jobject, jlong, jbyteArray, jint, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ReadFile
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ReadFile__JJI
  (JNIEnv *, jobject, jlong, jlong, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ReadFile
 * Signature: (JJIJJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ReadFile__JJIJJ
  (JNIEnv *, jobject, jlong, jlong, jint, jlong, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WriteFile
 * Signature: (J[BII)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_WriteFile__J_3BII
  (JNIEnv *, jobject, jlong, jbyteArray, jint, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WriteFile
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_WriteFile__JJI
  (JNIEnv *, jobject, jlong, jlong, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WriteFile
 * Signature: (JJIJJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_WriteFile__JJIJJ
  (JNIEnv *, jobject, jlong, jlong, jint, jlong, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetOverlappedResult
 * Signature: (JJZ)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetOverlappedResult
  (JNIEnv *, jobject, jlong, jlong, jboolean);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFriendlyIfIndex
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetFriendlyIfIndex
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetAdapterIndex
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetAdapterIndex
  (JNIEnv *, jobject, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetAdaptersAddresses
 * Signature: (JJ)Ljava/util/Collection;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetAdaptersAddresses
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    OpenProcessToken
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_OpenProcessToken
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetTokenInformation
 * Signature: (JI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetTokenInformation
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ShellExecuteA
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ShellExecuteA
  (JNIEnv *, jobject, jlong, jstring, jstring, jstring, jstring, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    INVALID_HANDLE_VALUE
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_INVALID_1HANDLE_1VALUE
  (JNIEnv *, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateNamedPipeA
 * Signature: (Ljava/lang/String;IIIIIIJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CreateNamedPipeA
  (JNIEnv *, jobject, jstring, jint, jint, jint, jint, jint, jint, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConnectNamedPipe
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConnectNamedPipe__J
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConnectNamedPipe
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConnectNamedPipe__JJ
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WaitNamedPipeA
 * Signature: (Ljava/lang/String;J)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_WaitNamedPipeA
  (JNIEnv *, jobject, jstring, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DisconnectNamedPipe
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_DisconnectNamedPipe
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    FlushFileBuffers
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_FlushFileBuffers
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetIpForwardTable2
 * Signature: (I)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetIpForwardTable2
  (JNIEnv *, jobject, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateIpForwardEntry2
 * Signature: (Leu/aschuetz/nativeutils/api/structs/MibIpForwardRow2;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CreateIpForwardEntry2
  (JNIEnv *, jobject, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DeleteIpForwardEntry2
 * Signature: (Leu/aschuetz/nativeutils/api/structs/MibIpForwardRow2;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_DeleteIpForwardEntry2
  (JNIEnv *, jobject, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConvertInterfaceIndexToLuid
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConvertInterfaceIndexToLuid
  (JNIEnv *, jobject, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConvertInterfaceLuidToIndex
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConvertInterfaceLuidToIndex
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConvertInterfaceLuidToNameA
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConvertInterfaceLuidToNameA
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConvertInterfaceLuidToAlias
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConvertInterfaceLuidToAlias
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConvertInterfaceNameToLuidA
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConvertInterfaceNameToLuidA
  (JNIEnv *, jobject, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateSemaphoreExA
 * Signature: (JJJLjava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CreateSemaphoreExA
  (JNIEnv *, jobject, jlong, jlong, jlong, jstring, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ReleaseSemaphore
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ReleaseSemaphore
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetupComm
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetupComm
  (JNIEnv *, jobject, jlong, jint, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetCommTimeouts
 * Signature: (JLeu/aschuetz/nativeutils/api/structs/CommTimeouts;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetCommTimeouts
  (JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    WaitCommEvent
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_WaitCommEvent
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    TransmitCommChar
 * Signature: (JB)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_TransmitCommChar
  (JNIEnv *, jobject, jlong, jbyte);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetDefaultCommConfigA
 * Signature: (Ljava/lang/String;Leu/aschuetz/nativeutils/api/structs/CommConfig;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetDefaultCommConfigA
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetCommState
 * Signature: (JLeu/aschuetz/nativeutils/api/structs/DCB;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetCommState
  (JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetCommMask
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetCommMask
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetCommConfig
 * Signature: (JLeu/aschuetz/nativeutils/api/structs/CommConfig;)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetCommConfig
  (JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    SetCommBreak
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetCommBreak
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    PurgeComm
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_PurgeComm
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetDefaultCommConfigA
 * Signature: (Ljava/lang/String;)Leu/aschuetz/nativeutils/api/structs/CommConfig;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetDefaultCommConfigA
  (JNIEnv *, jobject, jstring);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCommTimeouts
 * Signature: (J)Leu/aschuetz/nativeutils/api/structs/CommTimeouts;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommTimeouts
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCommState
 * Signature: (J)Leu/aschuetz/nativeutils/api/structs/DCB;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommState
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCommProperties
 * Signature: (J)Leu/aschuetz/nativeutils/api/structs/CommProp;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommProperties
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCommModemStatus
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommModemStatus
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCommMask
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommMask
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetCommConfig
 * Signature: (J)Leu/aschuetz/nativeutils/api/structs/CommConfig;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommConfig
  (JNIEnv *, jobject, jlong);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    EscapeCommFunction
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_EscapeCommFunction
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ClearCommError
 * Signature: (JLeu/aschuetz/nativeutils/api/structs/ComStat;)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ClearCommError
  (JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ClearCommBreak
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ClearCommBreak
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif

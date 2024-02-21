//
// Copyright Alexander Schütz, 2024
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


void COMMPROP_to_java(JNIEnv *env, LPCOMMPROP prop, jobject value) {
    jset_CommProp_dwCurrentRxQueue(env, value, prop->dwCurrentRxQueue);
    jset_CommProp_wPacketLength(env, value, prop->wPacketLength);
    jset_CommProp_wPacketVersion(env, value, prop->wPacketVersion);
    jset_CommProp_dwServiceMask(env, value, prop->dwServiceMask);
    jset_CommProp_dwReserved1(env, value, prop->dwReserved1);
    jset_CommProp_dwMaxTxQueue(env, value, prop->dwMaxTxQueue);
    jset_CommProp_dwMaxRxQueue(env, value, prop->dwMaxRxQueue);
    jset_CommProp_dwMaxBaud(env, value, prop->dwMaxBaud);
    jset_CommProp_dwProvSubType(env, value, prop->dwProvSubType);
    jset_CommProp_dwProvCapabilities(env, value, prop->dwProvCapabilities);
    jset_CommProp_dwSettableParams(env, value, prop->dwSettableParams);
    jset_CommProp_dwSettableBaud(env, value, prop->dwSettableBaud);
    jset_CommProp_wSettableData(env, value, prop->wSettableData);
    jset_CommProp_wSettableStopParity(env, value, prop->wSettableStopParity);
    jset_CommProp_dwCurrentTxQueue(env, value, prop->dwCurrentTxQueue);
    jset_CommProp_dwCurrentRxQueue(env, value, prop->dwCurrentRxQueue);
    jset_CommProp_dwProvSpec1(env, value, prop->dwProvSpec1);
    jset_CommProp_dwProvSpec2(env, value, prop->dwProvSpec2);
}

void COMSTAT_to_java(JNIEnv *env, LPCOMSTAT stat, jobject value) {
    jset_ComStat_cbInQue(env, value, stat->cbInQue);
    jset_ComStat_cbOutQue(env, value, stat->cbOutQue);
    jset_ComStat_fCtsHold(env, value, stat->fCtsHold);
    jset_ComStat_fDsrHold(env, value, stat->fDsrHold);
    jset_ComStat_fRlsdHold(env, value, stat->fRlsdHold);
    jset_ComStat_fXoffHold(env, value, stat->fXoffHold);
    jset_ComStat_fXoffSent(env, value, stat->fXoffSent);
    jset_ComStat_fEof(env, value, stat->fEof);
    jset_ComStat_fTxim(env, value, stat->fTxim);
}

void COMMTIMEOUTS_to_java(JNIEnv *env, LPCOMMTIMEOUTS timeouts, jobject value) {
    jset_CommTimeouts_ReadIntervalTimeout(env, value, timeouts->ReadIntervalTimeout);
    jset_CommTimeouts_ReadTotalTimeoutMultiplier(env, value, timeouts->ReadTotalTimeoutMultiplier);
    jset_CommTimeouts_ReadTotalTimeoutConstant(env, value, timeouts->ReadTotalTimeoutConstant);
    jset_CommTimeouts_WriteTotalTimeoutMultiplier(env, value, timeouts->WriteTotalTimeoutMultiplier);
    jset_CommTimeouts_WriteTotalTimeoutConstant(env, value, timeouts->WriteTotalTimeoutConstant);
}

void java_to_DCB(JNIEnv *env, LPDCB dcb, jobject value) {
    memset((void*) dcb, 0, sizeof(DCB));
    dcb->BaudRate = jget_DCB_BaudRate(env, value);
    dcb->fBinary = jget_DCB_fBinary(env, value);
    dcb->fParity = jget_DCB_fParity(env, value);
    dcb->fOutxCtsFlow = jget_DCB_fOutxCtsFlow(env, value);
    dcb->fOutxDsrFlow = jget_DCB_fOutxDsrFlow(env, value);
    dcb->fDtrControl = jget_DCB_fDtrControl(env, value);
    dcb->fDsrSensitivity = jget_DCB_fDsrSensitivity(env, value);
    dcb->fTXContinueOnXoff = jget_DCB_fTXContinueOnXoff(env, value);
    dcb->fOutX = jget_DCB_fOutX(env, value);
    dcb->fInX = jget_DCB_fInX(env, value);
    dcb->fErrorChar = jget_DCB_fErrorChar(env, value);
    dcb->fNull = jget_DCB_fNull(env, value);
    dcb->fRtsControl = jget_DCB_fRtsControl(env, value);
    dcb->fAbortOnError = jget_DCB_fAbortOnError(env, value);
    dcb->XonLim = jget_DCB_XonLim(env, value);
    dcb->XoffLim = jget_DCB_XoffLim(env, value);
    dcb->ByteSize = jget_DCB_ByteSize(env, value);
    dcb->Parity = jget_DCB_Parity(env, value);
    dcb->StopBits = jget_DCB_StopBits(env, value);
    dcb->XonChar = (char) jget_DCB_XonChar(env, value);
    dcb->XoffChar = (char) jget_DCB_XoffChar(env, value);
    dcb->ErrorChar = (char) jget_DCB_ErrorChar(env, value);
    dcb->EofChar = (char) jget_DCB_EofChar(env, value);
    dcb->EvtChar = (char) jget_DCB_EvtChar(env, value);
}


void DCB_to_java(JNIEnv *env, LPDCB dcb, jobject value) {
    jset_DCB_BaudRate(env, value, dcb->BaudRate);
    jset_DCB_XonLim(env, value, dcb->XonLim);
    jset_DCB_XoffLim(env, value, dcb->XoffLim);
    jset_DCB_ByteSize(env, value, dcb->ByteSize);
    jset_DCB_Parity(env, value, dcb->Parity);
    jset_DCB_StopBits(env, value, dcb->StopBits);
    jset_DCB_XonChar(env, value, dcb->XonChar);
    jset_DCB_XoffChar(env, value, dcb->XoffChar);
    jset_DCB_ErrorChar(env, value, dcb->ErrorChar);
    jset_DCB_EofChar(env, value, dcb->EofChar);
    jset_DCB_EvtChar(env, value, dcb->EvtChar);
    jset_DCB_fBinary(env, value, dcb->fBinary);
    jset_DCB_fParity(env, value, dcb->fParity);
    jset_DCB_fOutxCtsFlow(env, value, dcb->fOutxCtsFlow);
    jset_DCB_fOutxDsrFlow(env, value, dcb->fOutxDsrFlow);
    jset_DCB_fDtrControl(env, value, dcb->fDtrControl);
    jset_DCB_fDsrSensitivity(env, value, dcb->fDsrSensitivity);
    jset_DCB_fTXContinueOnXoff(env, value, dcb->fTXContinueOnXoff);
    jset_DCB_fOutX(env, value, dcb->fOutX);
    jset_DCB_fInX(env, value, dcb->fInX);
    jset_DCB_fErrorChar(env, value, dcb->fErrorChar);
    jset_DCB_fNull(env, value, dcb->fNull);
    jset_DCB_fRtsControl(env, value, dcb->fRtsControl);
    jset_DCB_fAbortOnError(env, value, dcb->fAbortOnError);
}

void COMMCONFIG_to_java(JNIEnv *env, LPCOMMCONFIG config, jobject value) {
    jobject dcb = jnew_DCB(env);
    if (dcb == NULL) {
        return;
    }
    DCB_to_java(env, &config->dcb, dcb);

    jset_CommConfig_dcb(env, value, dcb);
    jset_CommConfig_wVersion(env, value, config->wVersion);
    jset_CommConfig_dwProviderSubType(env, value, config->dwProviderSubType);
    jsetA_CommConfig_wcProviderData(env, value, (jbyte*) &config->wcProviderData, (jsize) config->dwProviderSize);
}



JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetupComm
(JNIEnv *env, jobject inst, jlong jhandle, jint inQueue, jint outQueue) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    if (SetupComm(h, (DWORD) inQueue, (DWORD) outQueue)) {
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetCommTimeouts
(JNIEnv *env, jobject inst, jlong jhandle, jobject value) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    if (value == NULL) {
        jthrowCC_NullPointerException_1(env, "value");
        return;
    }

    COMMTIMEOUTS timeouts;
    timeouts.ReadIntervalTimeout = jget_CommTimeouts_ReadIntervalTimeout(env, value);
    timeouts.ReadTotalTimeoutMultiplier = jget_CommTimeouts_ReadTotalTimeoutMultiplier(env, value);
    timeouts.ReadTotalTimeoutConstant = jget_CommTimeouts_ReadTotalTimeoutConstant(env, value);
    timeouts.WriteTotalTimeoutMultiplier = jget_CommTimeouts_WriteTotalTimeoutMultiplier(env, value);
    timeouts.WriteTotalTimeoutConstant = jget_CommTimeouts_WriteTotalTimeoutConstant(env, value);

    if (SetCommTimeouts(h, &timeouts)) {
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_WaitCommEvent
(JNIEnv *env, jobject inst, jlong jhandle) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    DWORD event = 0;
    if (WaitCommEvent(h, &event, NULL)) {
        return (jint) event;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
    return 0;
}

JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_TransmitCommChar
(JNIEnv *env, jobject inst, jlong jhandle, jbyte data) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    if (TransmitCommChar(h, data)) {
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetDefaultCommConfigA
(JNIEnv *env, jobject inst, jstring jname, jobject jcfg) {
    if (jcfg == NULL) {
        jthrowCC_NullPointerException_1(env, "cfg");
        return;
    }

    jobject jdcb = jget_CommConfig_dcb(env, jcfg);

    if (jdcb == NULL) {
        jthrowCC_NullPointerException_1(env, "cfg.dcb");
        return;
    }

    jobject jdata = jget_CommConfig_wcProviderData(env, jcfg);

    if (jdata == NULL) {
        jthrowCC_NullPointerException_1(env, "cfg.wcProviderData");
        return;
    }

    jsize arr_len = (*env)->GetArrayLength(env, jdata);
    size_t size = sizeof(COMMCONFIG) + arr_len + 1;

    LPCOMMCONFIG cfg = malloc(size);
    if (cfg == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "malloc");
        return;
    }

    memset((void*) cfg, 0, sizeof(COMMCONFIG));
    cfg->dwSize = sizeof(COMMCONFIG);
    cfg->wVersion = jget_CommConfig_wVersion(env, jcfg);
    cfg->dwProviderSubType = jget_CommConfig_wVersion(env, jcfg);
    cfg->dwProviderOffset = ((uintptr_t)(&cfg->wcProviderData)) - ((uintptr_t)cfg);
    cfg->dwProviderSize = arr_len;
    java_to_DCB(env, &cfg->dcb, jdcb);
    if (arr_len > 0) {
        (*env)->GetByteArrayRegion(env, jdata, 0, arr_len, (jbyte*) &cfg->wcProviderData);
    }

    const char* ptr = (*env)->GetStringUTFChars(env, jname, NULL);
    WINBOOL res = SetDefaultCommConfigA(ptr, cfg, size);
    free(cfg);
    (*env)->ReleaseStringUTFChars(env, jname, ptr);

    if (res) {
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetCommState
(JNIEnv *env, jobject inst, jlong jhandle, jobject jdcb) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    if (jdcb == NULL) {
        jthrowCC_NullPointerException_1(env, "dcb");
        return;
    }

    DCB dcb;
    java_to_DCB(env, &dcb, jdcb);

    if (SetCommState(h, &dcb)) {
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetCommMask
(JNIEnv *env, jobject inst, jlong jhandle, jint mask) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    if (SetCommMask(h, (DWORD) mask)) {
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetCommConfig
(JNIEnv *env, jobject inst, jlong jhandle, jobject jcfg) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    if (jcfg == NULL) {
        jthrowCC_NullPointerException_1(env, "cfg");
        return;
    }

    jobject jdcb = jget_CommConfig_dcb(env, jcfg);

    if (jdcb == NULL) {
        jthrowCC_NullPointerException_1(env, "cfg.dcb");
        return;
    }

    jobject jdata = jget_CommConfig_wcProviderData(env, jcfg);

    if (jdata == NULL) {
        jthrowCC_NullPointerException_1(env, "cfg.wcProviderData");
        return;
    }

    jsize arr_len = (*env)->GetArrayLength(env, jdata);
    size_t size = sizeof(COMMCONFIG) + arr_len + 1;

    LPCOMMCONFIG cfg = malloc(size);
    if (cfg == NULL) {
        jthrowCC_OutOfMemoryError_1(env, "malloc");
        return;
    }

    memset((void*) cfg, 0, sizeof(COMMCONFIG));
    cfg->dwSize = sizeof(COMMCONFIG);
    cfg->wVersion = jget_CommConfig_wVersion(env, jcfg);
    cfg->dwProviderSubType = jget_CommConfig_wVersion(env, jcfg);
    cfg->dwProviderOffset = ((uintptr_t)(&cfg->wcProviderData)) - ((uintptr_t)cfg);
    cfg->dwProviderSize = arr_len;
    java_to_DCB(env, &cfg->dcb, jdcb);
    if (arr_len > 0) {
        (*env)->GetByteArrayRegion(env, jdata, 0, arr_len, (jbyte*) &cfg->wcProviderData);
    }

    WINBOOL res = SetCommConfig(h, cfg, size);
    free(cfg);

    if (res) {
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_SetCommBreak
(JNIEnv *env, jobject inst, jlong jhandle) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    if (SetCommBreak(h)) {
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_PurgeComm
(JNIEnv *env, jobject inst, jlong jhandle, jint flags) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    if (PurgeComm(h, (DWORD) flags)) {
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetDefaultCommConfigA
(JNIEnv *env, jobject inst, jstring jname) {

    COMMCONFIG cfg;
    memset(&cfg, 0, sizeof(COMMCONFIG));
    cfg.dwSize = sizeof(COMMCONFIG);

    const char* ptr = (*env)->GetStringUTFChars(env, jname, NULL);

    DWORD size = sizeof(COMMCONFIG);

    WINBOOL res = GetDefaultCommConfigA(ptr, &cfg, &size);
    (*env)->ReleaseStringUTFChars(env, jname, ptr);
    if (res) {
        jobject com = jnew_CommConfig(env);
        if (com == NULL) {
            return NULL;
        }

        COMMCONFIG_to_java(env, &cfg, com);
        return com;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
    return NULL;
}

JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommTimeouts
(JNIEnv *env, jobject inst, jlong jhandle) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    COMMTIMEOUTS timeouts;
    memset((void*) &timeouts, 0, sizeof(COMMTIMEOUTS ));

    if (GetCommTimeouts(h, &timeouts)) {
        jobject jcfg = jnew_CommTimeouts(env);
        if (jcfg == NULL) {
            return NULL;
        }

        COMMTIMEOUTS_to_java(env, &timeouts, jcfg);
        return jcfg;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());

}

JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommState
(JNIEnv *env, jobject inst, jlong jhandle) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    DCB dcb;
    memset((void*) &dcb, 0, sizeof(DCB ));

    if (GetCommState(h, &dcb)) {
        jobject jcfg = jnew_DCB(env);
        if (jcfg == NULL) {
            return NULL;
        }

        DCB_to_java(env, &dcb, jcfg);
        return jcfg;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommProperties
(JNIEnv *env, jobject inst, jlong jhandle) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    COMMPROP cfg;
    memset((void*) &cfg, 0, sizeof(COMMPROP));

    if (GetCommProperties(h, &cfg)) {
        jobject jcfg = jnew_CommProp(env);
        if (jcfg == NULL) {
            return NULL;
        }

        COMMPROP_to_java(env, &cfg, jcfg);
        return jcfg;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommModemStatus
(JNIEnv *env, jobject inst, jlong jhandle) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    DWORD result = 0;
    if (GetCommModemStatus(h, &result)) {
        return (jint) result;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
    return 0;
}

JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommMask
(JNIEnv *env, jobject inst, jlong jhandle) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    DWORD result = 0;
    if (GetCommMask(h, &result)) {
        return (jint) result;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
    return 0;
}

JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetCommConfig
(JNIEnv *env, jobject inst, jlong jhandle) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    COMMCONFIG cfg;
    DWORD cfgSize = sizeof(COMMCONFIG);
    if (GetCommConfig(h, &cfg, &cfgSize)) {
        jobject jcfg = jnew_CommConfig(env);
        if (jcfg == NULL) {
            return NULL;
        }

        COMMCONFIG_to_java(env, &cfg, jcfg);
        return jcfg;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_EscapeCommFunction
(JNIEnv *env, jobject inst, jlong jhandle, jint data) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    if (EscapeCommFunction(h, data)) {
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ClearCommError
(JNIEnv *env, jobject inst, jlong jhandle, jobject jcomm) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;
    COMSTAT comm;
    LPCOMSTAT ptr = NULL;
    if (jcomm != NULL) {
        ptr = &comm;
        memset((void*) &comm, 0, sizeof(COMSTAT));
    }

    DWORD result = 0;
    if (ClearCommError(h, &result, ptr)) {
        if (ptr != NULL) {
            COMSTAT_to_java(env, ptr, jcomm);
        }
        return (jint) result;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}

JNIEXPORT void JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ClearCommBreak
(JNIEnv *env, jobject inst, jlong jhandle) {
    HANDLE h = (HANDLE) (uintptr_t) jhandle;

    if (ClearCommBreak(h)) {
        return;
    }

    jthrow_UnknownNativeErrorException_1(env, (jlong) GetLastError());
}
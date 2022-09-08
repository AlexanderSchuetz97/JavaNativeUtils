//THIS FILE IS MACHINE GENERATED, DO NOT EDIT
#include "jnigenerator.h"
static jclass internal_Exception = 0;
static jclass internal_OutOfMemoryError = 0;
static jclass internal_IllegalArgumentException = 0;
static jclass internal_NullPointerException = 0;
static jclass internal_Enum = 0;
static jmethodID internal_Enum_ordinal = 0;
static jmethodID internal_Enum_name = 0;

static jclass makeGlobalClassRef(JNIEnv * env, const char * name) {
   jclass clazz = (*env) -> FindClass(env, name);
   if (clazz == 0) {
       return 0;
   }

   jclass global = (*env) -> NewGlobalRef(env, clazz);
   (*env) -> DeleteLocalRef(env, clazz);
   return global;
}

static void throw_internal_OutOfMemoryError(JNIEnv * env, const char* message) {
    if (!(*env) -> ExceptionCheck(env)) {
        (*env) -> ThrowNew(env, internal_OutOfMemoryError, message);
    }
}

static void throw_internal_IllegalArgumentException(JNIEnv * env, const char * message) {
    if (!(*env) -> ExceptionCheck(env)) {
        (*env) -> ThrowNew(env, internal_IllegalArgumentException, message);
    }
}

static void throw_internal_NullPointerException(JNIEnv * env, const char * message) {
    if (!(*env) -> ExceptionCheck(env)) {
        (*env) -> ThrowNew(env, internal_NullPointerException, message);
    }
}

jboolean jerr(JNIEnv * env) {
    return (*env) -> ExceptionCheck(env);
}

jbyteArray jarrayB(JNIEnv * env, jbyte * buffer, jsize len) {
    if (len < 0) {
        throw_internal_IllegalArgumentException(env, "jarrayB len < 0");
        return 0;
    }
    jbyteArray res = (*env) -> NewByteArray(env, len);
    if (res == 0) {
        throw_internal_OutOfMemoryError(env, "jarrayB NewByteArray");
        return 0;
    }
    if (len == 0) {
        return 0;
    }
    if (buffer == 0) {
        (*env)->DeleteLocalRef(env, res);
        throw_internal_NullPointerException(env, "jarrayB buffer = NULL");
    }
    (*env)->SetByteArrayRegion(env, res, 0, len, (const jbyte*) buffer);
    return res;
}

jint jenum_ordinal(JNIEnv * env, jobject enumValue) {
    if (enumValue == 0) {
        return -1;
    }
    return (jint) (*env) -> CallIntMethod(env, enumValue, internal_Enum_ordinal);
}

jstring jenum_name(JNIEnv * env, jobject enumValue) {
    if (enumValue == 0) {
        return 0;
    }
    return (jstring) (*env) -> CallObjectMethod(env, enumValue, internal_Enum_name);
}

static jclass IpAdapterAddresses = 0;
jboolean jinstanceof_IpAdapterAddresses(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, IpAdapterAddresses);
}

static jclass IllegalStateException = 0;
jboolean jinstanceof_IllegalStateException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, IllegalStateException);
}

static jclass Win32FileAttributeData = 0;
jboolean jinstanceof_Win32FileAttributeData(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, Win32FileAttributeData);
}

static jclass IpAdapterAddresses$IpAdapterUnicastAddress = 0;
jboolean jinstanceof_IpAdapterAddresses$IpAdapterUnicastAddress(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, IpAdapterAddresses$IpAdapterUnicastAddress);
}

static jclass OperationInProgressException = 0;
jboolean jinstanceof_OperationInProgressException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, OperationInProgressException);
}

static jclass PermissionDeniedException = 0;
jboolean jinstanceof_PermissionDeniedException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, PermissionDeniedException);
}

static jclass ShellExecuteException = 0;
jboolean jinstanceof_ShellExecuteException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, ShellExecuteException);
}

static jclass GUID = 0;
jboolean jinstanceof_GUID(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, GUID);
}

static jclass BindException = 0;
jboolean jinstanceof_BindException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, BindException);
}

static jclass Iterable = 0;
jboolean jinstanceof_Iterable(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, Iterable);
}

static jclass NullPointerException = 0;
jboolean jinstanceof_NullPointerException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, NullPointerException);
}

static jclass Utsname = 0;
jboolean jinstanceof_Utsname(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, Utsname);
}

static jclass ArrayList = 0;
jboolean jinstanceof_ArrayList(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, ArrayList);
}

static jclass InetAddress = 0;
jboolean jinstanceof_InetAddress(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, InetAddress);
}

static jclass Cmsghdr = 0;
jboolean jinstanceof_Cmsghdr(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, Cmsghdr);
}

static jclass InvalidPathException = 0;
jboolean jinstanceof_InvalidPathException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, InvalidPathException);
}

static jclass FileSystemLoopException = 0;
jboolean jinstanceof_FileSystemLoopException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, FileSystemLoopException);
}

static jclass UnknownNativeErrorException = 0;
jboolean jinstanceof_UnknownNativeErrorException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, UnknownNativeErrorException);
}

static jclass ConnectException = 0;
jboolean jinstanceof_ConnectException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, ConnectException);
}

static jclass PollFD = 0;
jboolean jinstanceof_PollFD(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, PollFD);
}

static jclass UnsupportedOperationException = 0;
jboolean jinstanceof_UnsupportedOperationException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, UnsupportedOperationException);
}

static jclass Stat = 0;
jboolean jinstanceof_Stat(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, Stat);
}

static jclass Iterator = 0;
jboolean jinstanceof_Iterator(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, Iterator);
}

static jclass NotDirectoryException = 0;
jboolean jinstanceof_NotDirectoryException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, NotDirectoryException);
}

static jclass Collection = 0;
jboolean jinstanceof_Collection(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, Collection);
}

static jclass NotLinkException = 0;
jboolean jinstanceof_NotLinkException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, NotLinkException);
}

static jclass Msghdr = 0;
jboolean jinstanceof_Msghdr(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, Msghdr);
}

static jclass IOException = 0;
jboolean jinstanceof_IOException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, IOException);
}

static jclass IllegalArgumentException = 0;
jboolean jinstanceof_IllegalArgumentException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, IllegalArgumentException);
}

static jclass FileAlreadyExistsException = 0;
jboolean jinstanceof_FileAlreadyExistsException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, FileAlreadyExistsException);
}

static jclass InetSocketAddress = 0;
jboolean jinstanceof_InetSocketAddress(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, InetSocketAddress);
}

static jclass FileNotFoundException = 0;
jboolean jinstanceof_FileNotFoundException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, FileNotFoundException);
}

static jclass Exception = 0;
jboolean jinstanceof_Exception(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, Exception);
}

static jclass QuotaExceededException = 0;
jboolean jinstanceof_QuotaExceededException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, QuotaExceededException);
}

static jclass InvalidFileDescriptorException = 0;
jboolean jinstanceof_InvalidFileDescriptorException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, InvalidFileDescriptorException);
}

static jclass PollFD$PollEvent = 0;
jboolean jinstanceof_PollFD$PollEvent(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, PollFD$PollEvent);
}

static jclass Iovec = 0;
jboolean jinstanceof_Iovec(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, Iovec);
}

static jclass Sockaddr = 0;
jboolean jinstanceof_Sockaddr(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, Sockaddr);
}

static jclass MutexAbandonedException = 0;
jboolean jinstanceof_MutexAbandonedException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, MutexAbandonedException);
}

static jclass AccessDeniedException = 0;
jboolean jinstanceof_AccessDeniedException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, AccessDeniedException);
}

static jclass ReadOnlyFileSystemException = 0;
jboolean jinstanceof_ReadOnlyFileSystemException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, ReadOnlyFileSystemException);
}

static jclass OutOfMemoryError = 0;
jboolean jinstanceof_OutOfMemoryError(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, OutOfMemoryError);
}

static jclass SharingViolationException = 0;
jboolean jinstanceof_SharingViolationException(JNIEnv * env, jobject value) {
   return (*env)->IsInstanceOf(env, value, SharingViolationException);
}

static jfieldID Cmsghdr_cmsg_level = 0;
void jset_Cmsghdr_cmsg_level(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, Cmsghdr_cmsg_level, value);
}

jint jget_Cmsghdr_cmsg_level(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, Cmsghdr_cmsg_level);
}

static jfieldID Cmsghdr_cmsg_type = 0;
void jset_Cmsghdr_cmsg_type(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, Cmsghdr_cmsg_type, value);
}

jint jget_Cmsghdr_cmsg_type(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, Cmsghdr_cmsg_type);
}

static jfieldID Cmsghdr_payload = 0;
void jset_Cmsghdr_payload(JNIEnv * env, jobject instance, jbyteArray value) {
   (*env)->SetObjectField(env, instance, Cmsghdr_payload, value);
}

jboolean jsetA_Cmsghdr_payload(JNIEnv * env, jobject instance, jbyte * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Cmsghdr_payload, 0);
        return JNI_TRUE;
    }
    if (len < 0) {
        len = 0;
    }
    jbyteArray tmp = (*env)->NewByteArray(env, len);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    if (len > 0) {
        (*env)->SetByteArrayRegion(env, tmp, 0, len, (const jbyte*) value);
    }
    (*env)->SetObjectField(env, instance, Cmsghdr_payload, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jbyteArray jget_Cmsghdr_payload(JNIEnv * env, jobject instance) {
   return (jbyteArray) (*env)->GetObjectField(env, instance, Cmsghdr_payload);
}

static jmethodID Cmsghdr_C_0 = 0;
jobject jnew_Cmsghdr(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, Cmsghdr, Cmsghdr_C_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Cmsghdr_M_getLevel_0 = 0;
jint jcall_Cmsghdr_getLevel(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, Cmsghdr_M_getLevel_0);
}

static jmethodID Cmsghdr_M_getPayload_0 = 0;
jbyteArray jcall_Cmsghdr_getPayload(JNIEnv * env, jobject instance) {
    return (jbyteArray) (*env) -> CallObjectMethod(env, instance, Cmsghdr_M_getPayload_0);
}

static jmethodID Cmsghdr_M_getType_0 = 0;
jint jcall_Cmsghdr_getType(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, Cmsghdr_M_getType_0);
}

static jmethodID Cmsghdr_M_setPayload_0 = 0;
void jcall_Cmsghdr_setPayload(JNIEnv * env, jobject instance, jbyteArray p0) {
    (*env) -> CallVoidMethod(env, instance, Cmsghdr_M_setPayload_0, p0);
}

static jfieldID GUID_data1 = 0;
void jset_GUID_data1(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, GUID_data1, value);
}

jint jget_GUID_data1(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, GUID_data1);
}

static jfieldID GUID_data2 = 0;
void jset_GUID_data2(JNIEnv * env, jobject instance, jshort value) {
   (*env)->SetShortField(env, instance, GUID_data2, value);
}

jshort jget_GUID_data2(JNIEnv * env, jobject instance) {
   return (*env)->GetShortField(env, instance, GUID_data2);
}

static jfieldID GUID_data3 = 0;
void jset_GUID_data3(JNIEnv * env, jobject instance, jshort value) {
   (*env)->SetShortField(env, instance, GUID_data3, value);
}

jshort jget_GUID_data3(JNIEnv * env, jobject instance) {
   return (*env)->GetShortField(env, instance, GUID_data3);
}

static jfieldID GUID_data4 = 0;
void jset_GUID_data4(JNIEnv * env, jobject instance, jbyteArray value) {
   (*env)->SetObjectField(env, instance, GUID_data4, value);
}

jboolean jsetA_GUID_data4(JNIEnv * env, jobject instance, jbyte * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,GUID_data4, 0);
        return JNI_TRUE;
    }
    if (len < 0) {
        len = 0;
    }
    jbyteArray tmp = (*env)->NewByteArray(env, len);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    if (len > 0) {
        (*env)->SetByteArrayRegion(env, tmp, 0, len, (const jbyte*) value);
    }
    (*env)->SetObjectField(env, instance, GUID_data4, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jbyteArray jget_GUID_data4(JNIEnv * env, jobject instance) {
   return (jbyteArray) (*env)->GetObjectField(env, instance, GUID_data4);
}

static jmethodID GUID_C_0 = 0;
jobject jnew_GUID(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, GUID, GUID_C_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID GUID_C_1 = 0;
jobject jnew_GUID_1(JNIEnv * env, jstring p0) {
    jobject obj = (*env) -> NewObject(env, GUID, GUID_C_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID GUID_M_clone_0 = 0;
jobject jcall_GUID_clone(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, GUID_M_clone_0);
}

static jmethodID GUID_M_getData1_0 = 0;
jint jcall_GUID_getData1(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, GUID_M_getData1_0);
}

static jmethodID GUID_M_getData2_0 = 0;
jshort jcall_GUID_getData2(JNIEnv * env, jobject instance) {
    return (*env) -> CallShortMethod(env, instance, GUID_M_getData2_0);
}

static jmethodID GUID_M_getData3_0 = 0;
jshort jcall_GUID_getData3(JNIEnv * env, jobject instance) {
    return (*env) -> CallShortMethod(env, instance, GUID_M_getData3_0);
}

static jmethodID GUID_M_getData4_0 = 0;
jbyteArray jcall_GUID_getData4(JNIEnv * env, jobject instance) {
    return (jbyteArray) (*env) -> CallObjectMethod(env, instance, GUID_M_getData4_0);
}

static jmethodID GUID_M_setData1_0 = 0;
void jcall_GUID_setData1(JNIEnv * env, jobject instance, jint p0) {
    (*env) -> CallVoidMethod(env, instance, GUID_M_setData1_0, p0);
}

static jmethodID GUID_M_setData2_0 = 0;
void jcall_GUID_setData2(JNIEnv * env, jobject instance, jshort p0) {
    (*env) -> CallVoidMethod(env, instance, GUID_M_setData2_0, p0);
}

static jmethodID GUID_M_setData3_0 = 0;
void jcall_GUID_setData3(JNIEnv * env, jobject instance, jshort p0) {
    (*env) -> CallVoidMethod(env, instance, GUID_M_setData3_0, p0);
}

static jmethodID GUID_M_setData4_0 = 0;
void jcall_GUID_setData4(JNIEnv * env, jobject instance, jbyteArray p0) {
    (*env) -> CallVoidMethod(env, instance, GUID_M_setData4_0, p0);
}

static jmethodID GUID_M_toString_0 = 0;
jstring jcall_GUID_toString(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, GUID_M_toString_0);
}

static jfieldID Iovec_payload = 0;
void jset_Iovec_payload(JNIEnv * env, jobject instance, jbyteArray value) {
   (*env)->SetObjectField(env, instance, Iovec_payload, value);
}

jboolean jsetA_Iovec_payload(JNIEnv * env, jobject instance, jbyte * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Iovec_payload, 0);
        return JNI_TRUE;
    }
    if (len < 0) {
        len = 0;
    }
    jbyteArray tmp = (*env)->NewByteArray(env, len);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    if (len > 0) {
        (*env)->SetByteArrayRegion(env, tmp, 0, len, (const jbyte*) value);
    }
    (*env)->SetObjectField(env, instance, Iovec_payload, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jbyteArray jget_Iovec_payload(JNIEnv * env, jobject instance) {
   return (jbyteArray) (*env)->GetObjectField(env, instance, Iovec_payload);
}

static jfieldID Iovec_off = 0;
void jset_Iovec_off(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, Iovec_off, value);
}

jint jget_Iovec_off(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, Iovec_off);
}

static jfieldID Iovec_len = 0;
void jset_Iovec_len(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, Iovec_len, value);
}

jint jget_Iovec_len(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, Iovec_len);
}

static jfieldID Iovec_size = 0;
void jset_Iovec_size(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, Iovec_size, value);
}

jint jget_Iovec_size(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, Iovec_size);
}

static jmethodID Iovec_C_0 = 0;
jobject jnew_Iovec(JNIEnv * env, jint p0) {
    jobject obj = (*env) -> NewObject(env, Iovec, Iovec_C_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Iovec_C_1 = 0;
jobject jnew_Iovec_1(JNIEnv * env, jbyteArray p0) {
    jobject obj = (*env) -> NewObject(env, Iovec, Iovec_C_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Iovec_C_2 = 0;
jobject jnew_Iovec_2(JNIEnv * env, jbyteArray p0, jint p1, jint p2) {
    jobject obj = (*env) -> NewObject(env, Iovec, Iovec_C_2, p0, p1, p2);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Iovec_M_getLen_0 = 0;
jint jcall_Iovec_getLen(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, Iovec_M_getLen_0);
}

static jmethodID Iovec_M_getOff_0 = 0;
jint jcall_Iovec_getOff(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, Iovec_M_getOff_0);
}

static jmethodID Iovec_M_getPayload_0 = 0;
jbyteArray jcall_Iovec_getPayload(JNIEnv * env, jobject instance) {
    return (jbyteArray) (*env) -> CallObjectMethod(env, instance, Iovec_M_getPayload_0);
}

static jmethodID Iovec_M_getSize_0 = 0;
jint jcall_Iovec_getSize(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, Iovec_M_getSize_0);
}

static jfieldID IpAdapterAddresses_AdapterName = 0;
void jset_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_AdapterName, value);
}

jboolean jsetC_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance, char * value) {
    return jsetCC_IpAdapterAddresses_AdapterName(env, instance, (char*) value);
}

jboolean jsetCC_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance, const char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_AdapterName, 0);
        return JNI_TRUE;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewStringUTF");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_AdapterName, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jboolean jsetWC_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_AdapterName, 0);
        return JNI_TRUE;
    }
    
    jsize i = 0;
    while (value[i] != 0) {
        i++;
    }
    
    jstring tmp;
    if (sizeof(wchar_t) == sizeof(jchar)) {
        tmp = (*env) -> NewString(env, (const jchar*) value, i);
    } else {
        jchar tBuf[i];
        for (jsize j = 0; j < i; j++) {
            tBuf[j] = (jchar) value[j];
        }
        tmp = (*env) -> NewString(env, (const jchar*) tBuf, i);
    }
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_AdapterName, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jstring jget_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, IpAdapterAddresses_AdapterName);
}

static jfieldID IpAdapterAddresses_UnicastAddress = 0;
void jset_IpAdapterAddresses_UnicastAddress(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_UnicastAddress, value);
}

jobject jget_IpAdapterAddresses_UnicastAddress(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, IpAdapterAddresses_UnicastAddress);
}

static jfieldID IpAdapterAddresses_AnycastAddress = 0;
void jset_IpAdapterAddresses_AnycastAddress(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_AnycastAddress, value);
}

jobject jget_IpAdapterAddresses_AnycastAddress(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, IpAdapterAddresses_AnycastAddress);
}

static jfieldID IpAdapterAddresses_MulticastAddress = 0;
void jset_IpAdapterAddresses_MulticastAddress(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_MulticastAddress, value);
}

jobject jget_IpAdapterAddresses_MulticastAddress(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, IpAdapterAddresses_MulticastAddress);
}

static jfieldID IpAdapterAddresses_DnsServerAddress = 0;
void jset_IpAdapterAddresses_DnsServerAddress(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_DnsServerAddress, value);
}

jobject jget_IpAdapterAddresses_DnsServerAddress(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, IpAdapterAddresses_DnsServerAddress);
}

static jfieldID IpAdapterAddresses_DnsSuffix = 0;
void jset_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_DnsSuffix, value);
}

jboolean jsetC_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance, char * value) {
    return jsetCC_IpAdapterAddresses_DnsSuffix(env, instance, (char*) value);
}

jboolean jsetCC_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance, const char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_DnsSuffix, 0);
        return JNI_TRUE;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewStringUTF");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_DnsSuffix, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jboolean jsetWC_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_DnsSuffix, 0);
        return JNI_TRUE;
    }
    
    jsize i = 0;
    while (value[i] != 0) {
        i++;
    }
    
    jstring tmp;
    if (sizeof(wchar_t) == sizeof(jchar)) {
        tmp = (*env) -> NewString(env, (const jchar*) value, i);
    } else {
        jchar tBuf[i];
        for (jsize j = 0; j < i; j++) {
            tBuf[j] = (jchar) value[j];
        }
        tmp = (*env) -> NewString(env, (const jchar*) tBuf, i);
    }
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_DnsSuffix, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jstring jget_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, IpAdapterAddresses_DnsSuffix);
}

static jfieldID IpAdapterAddresses_Description = 0;
void jset_IpAdapterAddresses_Description(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_Description, value);
}

jboolean jsetC_IpAdapterAddresses_Description(JNIEnv * env, jobject instance, char * value) {
    return jsetCC_IpAdapterAddresses_Description(env, instance, (char*) value);
}

jboolean jsetCC_IpAdapterAddresses_Description(JNIEnv * env, jobject instance, const char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_Description, 0);
        return JNI_TRUE;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewStringUTF");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_Description, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jboolean jsetWC_IpAdapterAddresses_Description(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_Description, 0);
        return JNI_TRUE;
    }
    
    jsize i = 0;
    while (value[i] != 0) {
        i++;
    }
    
    jstring tmp;
    if (sizeof(wchar_t) == sizeof(jchar)) {
        tmp = (*env) -> NewString(env, (const jchar*) value, i);
    } else {
        jchar tBuf[i];
        for (jsize j = 0; j < i; j++) {
            tBuf[j] = (jchar) value[j];
        }
        tmp = (*env) -> NewString(env, (const jchar*) tBuf, i);
    }
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_Description, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jstring jget_IpAdapterAddresses_Description(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, IpAdapterAddresses_Description);
}

static jfieldID IpAdapterAddresses_FriendlyName = 0;
void jset_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_FriendlyName, value);
}

jboolean jsetC_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance, char * value) {
    return jsetCC_IpAdapterAddresses_FriendlyName(env, instance, (char*) value);
}

jboolean jsetCC_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance, const char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_FriendlyName, 0);
        return JNI_TRUE;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewStringUTF");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_FriendlyName, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jboolean jsetWC_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_FriendlyName, 0);
        return JNI_TRUE;
    }
    
    jsize i = 0;
    while (value[i] != 0) {
        i++;
    }
    
    jstring tmp;
    if (sizeof(wchar_t) == sizeof(jchar)) {
        tmp = (*env) -> NewString(env, (const jchar*) value, i);
    } else {
        jchar tBuf[i];
        for (jsize j = 0; j < i; j++) {
            tBuf[j] = (jchar) value[j];
        }
        tmp = (*env) -> NewString(env, (const jchar*) tBuf, i);
    }
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_FriendlyName, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jstring jget_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, IpAdapterAddresses_FriendlyName);
}

static jfieldID IpAdapterAddresses_PhysicalAddress = 0;
void jset_IpAdapterAddresses_PhysicalAddress(JNIEnv * env, jobject instance, jbyteArray value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_PhysicalAddress, value);
}

jboolean jsetA_IpAdapterAddresses_PhysicalAddress(JNIEnv * env, jobject instance, jbyte * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_PhysicalAddress, 0);
        return JNI_TRUE;
    }
    if (len < 0) {
        len = 0;
    }
    jbyteArray tmp = (*env)->NewByteArray(env, len);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    if (len > 0) {
        (*env)->SetByteArrayRegion(env, tmp, 0, len, (const jbyte*) value);
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_PhysicalAddress, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jbyteArray jget_IpAdapterAddresses_PhysicalAddress(JNIEnv * env, jobject instance) {
   return (jbyteArray) (*env)->GetObjectField(env, instance, IpAdapterAddresses_PhysicalAddress);
}

static jfieldID IpAdapterAddresses_Mtu = 0;
void jset_IpAdapterAddresses_Mtu(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_Mtu, value);
}

jlong jget_IpAdapterAddresses_Mtu(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_Mtu);
}

static jfieldID IpAdapterAddresses_IfType = 0;
void jset_IpAdapterAddresses_IfType(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_IfType, value);
}

jlong jget_IpAdapterAddresses_IfType(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_IfType);
}

static jfieldID IpAdapterAddresses_OperStatus = 0;
void jset_IpAdapterAddresses_OperStatus(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, IpAdapterAddresses_OperStatus, value);
}

jint jget_IpAdapterAddresses_OperStatus(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, IpAdapterAddresses_OperStatus);
}

static jfieldID IpAdapterAddresses_Ipv6IfIndex = 0;
void jset_IpAdapterAddresses_Ipv6IfIndex(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_Ipv6IfIndex, value);
}

jlong jget_IpAdapterAddresses_Ipv6IfIndex(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_Ipv6IfIndex);
}

static jfieldID IpAdapterAddresses_ZoneIndices = 0;
void jset_IpAdapterAddresses_ZoneIndices(JNIEnv * env, jobject instance, jlongArray value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_ZoneIndices, value);
}

jboolean jsetA_IpAdapterAddresses_ZoneIndices(JNIEnv * env, jobject instance, jlong * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_ZoneIndices, 0);
        return JNI_TRUE;
    }
    if (len < 0) {
        len = 0;
    }
    jlongArray tmp = (*env)->NewLongArray(env, len);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    if (len > 0) {
        (*env)->SetLongArrayRegion(env, tmp, 0, len, (const jlong*) value);
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_ZoneIndices, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jlongArray jget_IpAdapterAddresses_ZoneIndices(JNIEnv * env, jobject instance) {
   return (jlongArray) (*env)->GetObjectField(env, instance, IpAdapterAddresses_ZoneIndices);
}

static jfieldID IpAdapterAddresses_Prefix = 0;
void jset_IpAdapterAddresses_Prefix(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_Prefix, value);
}

jobject jget_IpAdapterAddresses_Prefix(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, IpAdapterAddresses_Prefix);
}

static jfieldID IpAdapterAddresses_TransmitLinkSpeed = 0;
void jset_IpAdapterAddresses_TransmitLinkSpeed(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_TransmitLinkSpeed, value);
}

jlong jget_IpAdapterAddresses_TransmitLinkSpeed(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_TransmitLinkSpeed);
}

static jfieldID IpAdapterAddresses_ReceiveLinkSpeed = 0;
void jset_IpAdapterAddresses_ReceiveLinkSpeed(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_ReceiveLinkSpeed, value);
}

jlong jget_IpAdapterAddresses_ReceiveLinkSpeed(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_ReceiveLinkSpeed);
}

static jfieldID IpAdapterAddresses_WinsServerAddress = 0;
void jset_IpAdapterAddresses_WinsServerAddress(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_WinsServerAddress, value);
}

jobject jget_IpAdapterAddresses_WinsServerAddress(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, IpAdapterAddresses_WinsServerAddress);
}

static jfieldID IpAdapterAddresses_GatewayAddress = 0;
void jset_IpAdapterAddresses_GatewayAddress(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_GatewayAddress, value);
}

jobject jget_IpAdapterAddresses_GatewayAddress(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, IpAdapterAddresses_GatewayAddress);
}

static jfieldID IpAdapterAddresses_Ipv4Metric = 0;
void jset_IpAdapterAddresses_Ipv4Metric(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_Ipv4Metric, value);
}

jlong jget_IpAdapterAddresses_Ipv4Metric(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_Ipv4Metric);
}

static jfieldID IpAdapterAddresses_Ipv6Metric = 0;
void jset_IpAdapterAddresses_Ipv6Metric(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_Ipv6Metric, value);
}

jlong jget_IpAdapterAddresses_Ipv6Metric(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_Ipv6Metric);
}

static jfieldID IpAdapterAddresses_Luid_Value = 0;
void jset_IpAdapterAddresses_Luid_Value(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_Luid_Value, value);
}

jlong jget_IpAdapterAddresses_Luid_Value(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_Luid_Value);
}

static jfieldID IpAdapterAddresses_Luid_NetLuidIndex = 0;
void jset_IpAdapterAddresses_Luid_NetLuidIndex(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_Luid_NetLuidIndex, value);
}

jlong jget_IpAdapterAddresses_Luid_NetLuidIndex(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_Luid_NetLuidIndex);
}

static jfieldID IpAdapterAddresses_Luid_IfType = 0;
void jset_IpAdapterAddresses_Luid_IfType(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_Luid_IfType, value);
}

jlong jget_IpAdapterAddresses_Luid_IfType(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_Luid_IfType);
}

static jfieldID IpAdapterAddresses_Dhcpv4Server = 0;
void jset_IpAdapterAddresses_Dhcpv4Server(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_Dhcpv4Server, value);
}

jobject jget_IpAdapterAddresses_Dhcpv4Server(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, IpAdapterAddresses_Dhcpv4Server);
}

static jfieldID IpAdapterAddresses_CompartmentId = 0;
void jset_IpAdapterAddresses_CompartmentId(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_CompartmentId, value);
}

jlong jget_IpAdapterAddresses_CompartmentId(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_CompartmentId);
}

static jfieldID IpAdapterAddresses_NetworkGuid = 0;
void jset_IpAdapterAddresses_NetworkGuid(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_NetworkGuid, value);
}

jobject jget_IpAdapterAddresses_NetworkGuid(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, IpAdapterAddresses_NetworkGuid);
}

static jfieldID IpAdapterAddresses_ConnectionType = 0;
void jset_IpAdapterAddresses_ConnectionType(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, IpAdapterAddresses_ConnectionType, value);
}

jint jget_IpAdapterAddresses_ConnectionType(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, IpAdapterAddresses_ConnectionType);
}

static jfieldID IpAdapterAddresses_TunnelType = 0;
void jset_IpAdapterAddresses_TunnelType(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, IpAdapterAddresses_TunnelType, value);
}

jint jget_IpAdapterAddresses_TunnelType(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, IpAdapterAddresses_TunnelType);
}

static jfieldID IpAdapterAddresses_Dhcpv6Server = 0;
void jset_IpAdapterAddresses_Dhcpv6Server(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_Dhcpv6Server, value);
}

jobject jget_IpAdapterAddresses_Dhcpv6Server(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, IpAdapterAddresses_Dhcpv6Server);
}

static jfieldID IpAdapterAddresses_Dhcpv6ClientDuid = 0;
void jset_IpAdapterAddresses_Dhcpv6ClientDuid(JNIEnv * env, jobject instance, jbyteArray value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_Dhcpv6ClientDuid, value);
}

jboolean jsetA_IpAdapterAddresses_Dhcpv6ClientDuid(JNIEnv * env, jobject instance, jbyte * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_Dhcpv6ClientDuid, 0);
        return JNI_TRUE;
    }
    if (len < 0) {
        len = 0;
    }
    jbyteArray tmp = (*env)->NewByteArray(env, len);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    if (len > 0) {
        (*env)->SetByteArrayRegion(env, tmp, 0, len, (const jbyte*) value);
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_Dhcpv6ClientDuid, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jbyteArray jget_IpAdapterAddresses_Dhcpv6ClientDuid(JNIEnv * env, jobject instance) {
   return (jbyteArray) (*env)->GetObjectField(env, instance, IpAdapterAddresses_Dhcpv6ClientDuid);
}

static jfieldID IpAdapterAddresses_Dhcpv6Iaid = 0;
void jset_IpAdapterAddresses_Dhcpv6Iaid(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses_Dhcpv6Iaid, value);
}

jlong jget_IpAdapterAddresses_Dhcpv6Iaid(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses_Dhcpv6Iaid);
}

static jmethodID IpAdapterAddresses_C_0 = 0;
jobject jnew_IpAdapterAddresses(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, IpAdapterAddresses, IpAdapterAddresses_C_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID IpAdapterAddresses_M_getAdapterName_0 = 0;
jstring jcall_IpAdapterAddresses_getAdapterName(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getAdapterName_0);
}

static jmethodID IpAdapterAddresses_M_getAnycastAddress_0 = 0;
jobject jcall_IpAdapterAddresses_getAnycastAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getAnycastAddress_0);
}

static jmethodID IpAdapterAddresses_M_getCompartmentId_0 = 0;
jlong jcall_IpAdapterAddresses_getCompartmentId(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getCompartmentId_0);
}

static jmethodID IpAdapterAddresses_M_getConnectionType_0 = 0;
jint jcall_IpAdapterAddresses_getConnectionType(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, IpAdapterAddresses_M_getConnectionType_0);
}

static jmethodID IpAdapterAddresses_M_getDescription_0 = 0;
jstring jcall_IpAdapterAddresses_getDescription(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getDescription_0);
}

static jmethodID IpAdapterAddresses_M_getDhcpv4Server_0 = 0;
jobject jcall_IpAdapterAddresses_getDhcpv4Server(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getDhcpv4Server_0);
}

static jmethodID IpAdapterAddresses_M_getDhcpv6ClientDuid_0 = 0;
jbyteArray jcall_IpAdapterAddresses_getDhcpv6ClientDuid(JNIEnv * env, jobject instance) {
    return (jbyteArray) (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getDhcpv6ClientDuid_0);
}

static jmethodID IpAdapterAddresses_M_getDhcpv6Iaid_0 = 0;
jlong jcall_IpAdapterAddresses_getDhcpv6Iaid(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getDhcpv6Iaid_0);
}

static jmethodID IpAdapterAddresses_M_getDhcpv6Server_0 = 0;
jobject jcall_IpAdapterAddresses_getDhcpv6Server(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getDhcpv6Server_0);
}

static jmethodID IpAdapterAddresses_M_getDnsServerAddress_0 = 0;
jobject jcall_IpAdapterAddresses_getDnsServerAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getDnsServerAddress_0);
}

static jmethodID IpAdapterAddresses_M_getDnsSuffix_0 = 0;
jstring jcall_IpAdapterAddresses_getDnsSuffix(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getDnsSuffix_0);
}

static jmethodID IpAdapterAddresses_M_getFriendlyName_0 = 0;
jstring jcall_IpAdapterAddresses_getFriendlyName(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getFriendlyName_0);
}

static jmethodID IpAdapterAddresses_M_getGatewayAddress_0 = 0;
jobject jcall_IpAdapterAddresses_getGatewayAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getGatewayAddress_0);
}

static jmethodID IpAdapterAddresses_M_getIfType_0 = 0;
jlong jcall_IpAdapterAddresses_getIfType(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getIfType_0);
}

static jmethodID IpAdapterAddresses_M_getIpv4Metric_0 = 0;
jlong jcall_IpAdapterAddresses_getIpv4Metric(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getIpv4Metric_0);
}

static jmethodID IpAdapterAddresses_M_getIpv6IfIndex_0 = 0;
jlong jcall_IpAdapterAddresses_getIpv6IfIndex(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getIpv6IfIndex_0);
}

static jmethodID IpAdapterAddresses_M_getIpv6Metric_0 = 0;
jlong jcall_IpAdapterAddresses_getIpv6Metric(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getIpv6Metric_0);
}

static jmethodID IpAdapterAddresses_M_getLuid_IfType_0 = 0;
jlong jcall_IpAdapterAddresses_getLuid_IfType(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getLuid_IfType_0);
}

static jmethodID IpAdapterAddresses_M_getLuid_NetLuidIndex_0 = 0;
jlong jcall_IpAdapterAddresses_getLuid_NetLuidIndex(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getLuid_NetLuidIndex_0);
}

static jmethodID IpAdapterAddresses_M_getLuid_Value_0 = 0;
jlong jcall_IpAdapterAddresses_getLuid_Value(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getLuid_Value_0);
}

static jmethodID IpAdapterAddresses_M_getMtu_0 = 0;
jlong jcall_IpAdapterAddresses_getMtu(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getMtu_0);
}

static jmethodID IpAdapterAddresses_M_getMulticastAddress_0 = 0;
jobject jcall_IpAdapterAddresses_getMulticastAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getMulticastAddress_0);
}

static jmethodID IpAdapterAddresses_M_getNetworkGuid_0 = 0;
jobject jcall_IpAdapterAddresses_getNetworkGuid(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getNetworkGuid_0);
}

static jmethodID IpAdapterAddresses_M_getOperStatus_0 = 0;
jint jcall_IpAdapterAddresses_getOperStatus(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, IpAdapterAddresses_M_getOperStatus_0);
}

static jmethodID IpAdapterAddresses_M_getPhysicalAddress_0 = 0;
jbyteArray jcall_IpAdapterAddresses_getPhysicalAddress(JNIEnv * env, jobject instance) {
    return (jbyteArray) (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getPhysicalAddress_0);
}

static jmethodID IpAdapterAddresses_M_getPrefix_0 = 0;
jobject jcall_IpAdapterAddresses_getPrefix(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getPrefix_0);
}

static jmethodID IpAdapterAddresses_M_getReceiveLinkSpeed_0 = 0;
jlong jcall_IpAdapterAddresses_getReceiveLinkSpeed(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getReceiveLinkSpeed_0);
}

static jmethodID IpAdapterAddresses_M_getTransmitLinkSpeed_0 = 0;
jlong jcall_IpAdapterAddresses_getTransmitLinkSpeed(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getTransmitLinkSpeed_0);
}

static jmethodID IpAdapterAddresses_M_getTunnelType_0 = 0;
jint jcall_IpAdapterAddresses_getTunnelType(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, IpAdapterAddresses_M_getTunnelType_0);
}

static jmethodID IpAdapterAddresses_M_getUnicastAddress_0 = 0;
jobject jcall_IpAdapterAddresses_getUnicastAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getUnicastAddress_0);
}

static jmethodID IpAdapterAddresses_M_getWinsServerAddress_0 = 0;
jobject jcall_IpAdapterAddresses_getWinsServerAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getWinsServerAddress_0);
}

static jmethodID IpAdapterAddresses_M_getZoneIndices_0 = 0;
jlongArray jcall_IpAdapterAddresses_getZoneIndices(JNIEnv * env, jobject instance) {
    return (jlongArray) (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getZoneIndices_0);
}

static jfieldID IpAdapterAddresses$IpAdapterUnicastAddress_Address = 0;
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_Address(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_Address, value);
}

jobject jget_IpAdapterAddresses$IpAdapterUnicastAddress_Address(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_Address);
}

static jfieldID IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin = 0;
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin, value);
}

jint jget_IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin);
}

static jfieldID IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin = 0;
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin, value);
}

jint jget_IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin);
}

static jfieldID IpAdapterAddresses$IpAdapterUnicastAddress_DadState = 0;
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_DadState(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_DadState, value);
}

jint jget_IpAdapterAddresses$IpAdapterUnicastAddress_DadState(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_DadState);
}

static jfieldID IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime = 0;
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime, value);
}

jlong jget_IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime);
}

static jfieldID IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime = 0;
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime, value);
}

jlong jget_IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime);
}

static jfieldID IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime = 0;
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime, value);
}

jlong jget_IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime);
}

static jfieldID IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength = 0;
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength, value);
}

jint jget_IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength);
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_C_0 = 0;
jobject jnew_IpAdapterAddresses$IpAdapterUnicastAddress(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, IpAdapterAddresses$IpAdapterUnicastAddress, IpAdapterAddresses$IpAdapterUnicastAddress_C_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_M_getAddress_0 = 0;
jobject jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_M_getAddress_0);
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_M_getDadState_0 = 0;
jint jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getDadState(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_M_getDadState_0);
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_M_getLeaseLifetime_0 = 0;
jlong jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getLeaseLifetime(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_M_getLeaseLifetime_0);
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_M_getOnLinkPrefixLength_0 = 0;
jint jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getOnLinkPrefixLength(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_M_getOnLinkPrefixLength_0);
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_M_getPreferredLifetime_0 = 0;
jlong jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getPreferredLifetime(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_M_getPreferredLifetime_0);
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_M_getPrefixOrigin_0 = 0;
jint jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getPrefixOrigin(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_M_getPrefixOrigin_0);
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_M_getSuffixOrigin_0 = 0;
jint jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getSuffixOrigin(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_M_getSuffixOrigin_0);
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_M_getValidLifetime_0 = 0;
jlong jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getValidLifetime(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_M_getValidLifetime_0);
}

static jfieldID Msghdr_msg_iov = 0;
void jset_Msghdr_msg_iov(JNIEnv * env, jobject instance, jobjectArray value) {
   (*env)->SetObjectField(env, instance, Msghdr_msg_iov, value);
}

jobjectArray jget_Msghdr_msg_iov(JNIEnv * env, jobject instance) {
   return (jobjectArray) (*env)->GetObjectField(env, instance, Msghdr_msg_iov);
}

static jfieldID Msghdr_msg_control = 0;
void jset_Msghdr_msg_control(JNIEnv * env, jobject instance, jbyteArray value) {
   (*env)->SetObjectField(env, instance, Msghdr_msg_control, value);
}

jboolean jsetA_Msghdr_msg_control(JNIEnv * env, jobject instance, jbyte * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Msghdr_msg_control, 0);
        return JNI_TRUE;
    }
    if (len < 0) {
        len = 0;
    }
    jbyteArray tmp = (*env)->NewByteArray(env, len);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    if (len > 0) {
        (*env)->SetByteArrayRegion(env, tmp, 0, len, (const jbyte*) value);
    }
    (*env)->SetObjectField(env, instance, Msghdr_msg_control, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jbyteArray jget_Msghdr_msg_control(JNIEnv * env, jobject instance) {
   return (jbyteArray) (*env)->GetObjectField(env, instance, Msghdr_msg_control);
}

static jfieldID Msghdr_msg_name = 0;
void jset_Msghdr_msg_name(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, Msghdr_msg_name, value);
}

jobject jget_Msghdr_msg_name(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, Msghdr_msg_name);
}

static jfieldID Msghdr_complete = 0;
void jset_Msghdr_complete(JNIEnv * env, jobject instance, jboolean value) {
   (*env)->SetBooleanField(env, instance, Msghdr_complete, value);
}

jboolean jget_Msghdr_complete(JNIEnv * env, jobject instance) {
   return (*env)->GetBooleanField(env, instance, Msghdr_complete);
}

static jfieldID Msghdr_truncated = 0;
void jset_Msghdr_truncated(JNIEnv * env, jobject instance, jboolean value) {
   (*env)->SetBooleanField(env, instance, Msghdr_truncated, value);
}

jboolean jget_Msghdr_truncated(JNIEnv * env, jobject instance) {
   return (*env)->GetBooleanField(env, instance, Msghdr_truncated);
}

static jfieldID Msghdr_controlDataTruncated = 0;
void jset_Msghdr_controlDataTruncated(JNIEnv * env, jobject instance, jboolean value) {
   (*env)->SetBooleanField(env, instance, Msghdr_controlDataTruncated, value);
}

jboolean jget_Msghdr_controlDataTruncated(JNIEnv * env, jobject instance) {
   return (*env)->GetBooleanField(env, instance, Msghdr_controlDataTruncated);
}

static jfieldID Msghdr_outOfBand = 0;
void jset_Msghdr_outOfBand(JNIEnv * env, jobject instance, jboolean value) {
   (*env)->SetBooleanField(env, instance, Msghdr_outOfBand, value);
}

jboolean jget_Msghdr_outOfBand(JNIEnv * env, jobject instance) {
   return (*env)->GetBooleanField(env, instance, Msghdr_outOfBand);
}

static jfieldID Msghdr_errQueue = 0;
void jset_Msghdr_errQueue(JNIEnv * env, jobject instance, jboolean value) {
   (*env)->SetBooleanField(env, instance, Msghdr_errQueue, value);
}

jboolean jget_Msghdr_errQueue(JNIEnv * env, jobject instance) {
   return (*env)->GetBooleanField(env, instance, Msghdr_errQueue);
}

static jfieldID Msghdr_msg_controllen = 0;
void jset_Msghdr_msg_controllen(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, Msghdr_msg_controllen, value);
}

jint jget_Msghdr_msg_controllen(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, Msghdr_msg_controllen);
}

static jmethodID Msghdr_C_0 = 0;
jobject jnew_Msghdr(JNIEnv * env, jobject p0) {
    jobject obj = (*env) -> NewObject(env, Msghdr, Msghdr_C_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Msghdr_C_1 = 0;
jobject jnew_Msghdr_1(JNIEnv * env, jobject p0, jobject p1, jbyteArray p2) {
    jobject obj = (*env) -> NewObject(env, Msghdr, Msghdr_C_1, p0, p1, p2);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Msghdr_C_2 = 0;
jobject jnew_Msghdr_2(JNIEnv * env, jbyteArray p0, jint p1, jint p2) {
    jobject obj = (*env) -> NewObject(env, Msghdr, Msghdr_C_2, p0, p1, p2);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Msghdr_C_3 = 0;
jobject jnew_Msghdr_3(JNIEnv * env, jobjectArray p0) {
    jobject obj = (*env) -> NewObject(env, Msghdr, Msghdr_C_3, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Msghdr_C_4 = 0;
jobject jnew_Msghdr_4(JNIEnv * env, jobjectArray p0, jobject p1) {
    jobject obj = (*env) -> NewObject(env, Msghdr, Msghdr_C_4, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Msghdr_C_5 = 0;
jobject jnew_Msghdr_5(JNIEnv * env, jobjectArray p0, jobject p1, jbyteArray p2) {
    jobject obj = (*env) -> NewObject(env, Msghdr, Msghdr_C_5, p0, p1, p2);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Msghdr_C_6 = 0;
jobject jnew_Msghdr_6(JNIEnv * env, jobjectArray p0, jbyteArray p1) {
    jobject obj = (*env) -> NewObject(env, Msghdr, Msghdr_C_6, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Msghdr_M_getMsg_control_0 = 0;
jbyteArray jcall_Msghdr_getMsg_control(JNIEnv * env, jobject instance) {
    return (jbyteArray) (*env) -> CallObjectMethod(env, instance, Msghdr_M_getMsg_control_0);
}

static jmethodID Msghdr_M_getMsg_controllen_0 = 0;
jint jcall_Msghdr_getMsg_controllen(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, Msghdr_M_getMsg_controllen_0);
}

static jmethodID Msghdr_M_getMsg_iov_0 = 0;
jobjectArray jcall_Msghdr_getMsg_iov(JNIEnv * env, jobject instance) {
    return (jobjectArray) (*env) -> CallObjectMethod(env, instance, Msghdr_M_getMsg_iov_0);
}

static jmethodID Msghdr_M_getMsg_name_0 = 0;
jobject jcall_Msghdr_getMsg_name(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, Msghdr_M_getMsg_name_0);
}

static jmethodID Msghdr_M_isComplete_0 = 0;
jboolean jcall_Msghdr_isComplete(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Msghdr_M_isComplete_0);
}

static jmethodID Msghdr_M_isControlDataTruncated_0 = 0;
jboolean jcall_Msghdr_isControlDataTruncated(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Msghdr_M_isControlDataTruncated_0);
}

static jmethodID Msghdr_M_isErrQueue_0 = 0;
jboolean jcall_Msghdr_isErrQueue(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Msghdr_M_isErrQueue_0);
}

static jmethodID Msghdr_M_isOutOfBand_0 = 0;
jboolean jcall_Msghdr_isOutOfBand(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Msghdr_M_isOutOfBand_0);
}

static jmethodID Msghdr_M_isTruncated_0 = 0;
jboolean jcall_Msghdr_isTruncated(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Msghdr_M_isTruncated_0);
}

static jfieldID PollFD_fd = 0;
void jset_PollFD_fd(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, PollFD_fd, value);
}

jint jget_PollFD_fd(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, PollFD_fd);
}

static jfieldID PollFD_events = 0;
void jset_PollFD_events(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, PollFD_events, value);
}

jobject jget_PollFD_events(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, PollFD_events);
}

static jfieldID PollFD_revents = 0;
void jset_PollFD_revents(JNIEnv * env, jobject instance, jobject value) {
   (*env)->SetObjectField(env, instance, PollFD_revents, value);
}

jobject jget_PollFD_revents(JNIEnv * env, jobject instance) {
   return (*env)->GetObjectField(env, instance, PollFD_revents);
}

static jmethodID PollFD_C_0 = 0;
jobject jnew_PollFD(JNIEnv * env, jint p0, jobject p1) {
    jobject obj = (*env) -> NewObject(env, PollFD, PollFD_C_0, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID PollFD_M_getEvents_0 = 0;
jobject jcall_PollFD_getEvents(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, PollFD_M_getEvents_0);
}

static jmethodID PollFD_M_getFd_0 = 0;
jint jcall_PollFD_getFd(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, PollFD_M_getFd_0);
}

static jmethodID PollFD_M_getREvents_0 = 0;
jobject jcall_PollFD_getREvents(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, PollFD_M_getREvents_0);
}

static jmethodID PollFD_M_test_0 = 0;
jboolean jcall_PollFD_test(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, PollFD_M_test_0, p0);
}

static jobject PollFD$PollEvent_POLLIN = 0;
jobject jenum_PollFD$PollEvent_POLLIN() {
   return PollFD$PollEvent_POLLIN;
}

static jobject PollFD$PollEvent_POLLPRI = 0;
jobject jenum_PollFD$PollEvent_POLLPRI() {
   return PollFD$PollEvent_POLLPRI;
}

static jobject PollFD$PollEvent_POLLOUT = 0;
jobject jenum_PollFD$PollEvent_POLLOUT() {
   return PollFD$PollEvent_POLLOUT;
}

static jobject PollFD$PollEvent_POLLRDNORM = 0;
jobject jenum_PollFD$PollEvent_POLLRDNORM() {
   return PollFD$PollEvent_POLLRDNORM;
}

static jobject PollFD$PollEvent_POLLRDBAND = 0;
jobject jenum_PollFD$PollEvent_POLLRDBAND() {
   return PollFD$PollEvent_POLLRDBAND;
}

static jobject PollFD$PollEvent_POLLWRNORM = 0;
jobject jenum_PollFD$PollEvent_POLLWRNORM() {
   return PollFD$PollEvent_POLLWRNORM;
}

static jobject PollFD$PollEvent_POLLWRBAND = 0;
jobject jenum_PollFD$PollEvent_POLLWRBAND() {
   return PollFD$PollEvent_POLLWRBAND;
}

static jobject PollFD$PollEvent_POLLMSG = 0;
jobject jenum_PollFD$PollEvent_POLLMSG() {
   return PollFD$PollEvent_POLLMSG;
}

static jobject PollFD$PollEvent_POLLREMOVE = 0;
jobject jenum_PollFD$PollEvent_POLLREMOVE() {
   return PollFD$PollEvent_POLLREMOVE;
}

static jobject PollFD$PollEvent_POLLRDHUP = 0;
jobject jenum_PollFD$PollEvent_POLLRDHUP() {
   return PollFD$PollEvent_POLLRDHUP;
}

static jobject PollFD$PollEvent_POLLERR = 0;
jobject jenum_PollFD$PollEvent_POLLERR() {
   return PollFD$PollEvent_POLLERR;
}

static jobject PollFD$PollEvent_POLLHUP = 0;
jobject jenum_PollFD$PollEvent_POLLHUP() {
   return PollFD$PollEvent_POLLHUP;
}

static jobject PollFD$PollEvent_POLLNVAL = 0;
jobject jenum_PollFD$PollEvent_POLLNVAL() {
   return PollFD$PollEvent_POLLNVAL;
}

static jfieldID PollFD$PollEvent_$VALUES = 0;
void jset_PollFD$PollEvent_$VALUES(JNIEnv * env, jobjectArray value) {
   (*env)->SetStaticObjectField(env, PollFD$PollEvent, PollFD$PollEvent_$VALUES, value);
}

jobjectArray jget_PollFD$PollEvent_$VALUES(JNIEnv * env) {
   return (jobjectArray) (*env)->GetStaticObjectField(env, PollFD$PollEvent, PollFD$PollEvent_$VALUES);
}

jsize jenum_PollFD$PollEvent_count() {
    return 13;
}
jobject PollFD$PollEvent_enum_values[13];
jobject* jenum_PollFD$PollEvent_values() {
    return PollFD$PollEvent_enum_values;
}

static jmethodID PollFD$PollEvent_C_0 = 0;
jobject jnew_PollFD$PollEvent(JNIEnv * env, jstring p0, jint p1) {
    jobject obj = (*env) -> NewObject(env, PollFD$PollEvent, PollFD$PollEvent_C_0, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jfieldID Sockaddr_EMPTY = 0;
void jset_Sockaddr_EMPTY(JNIEnv * env, jbyteArray value) {
   (*env)->SetStaticObjectField(env, Sockaddr, Sockaddr_EMPTY, value);
}

jbyteArray jget_Sockaddr_EMPTY(JNIEnv * env) {
   return (jbyteArray) (*env)->GetStaticObjectField(env, Sockaddr, Sockaddr_EMPTY);
}

static jfieldID Sockaddr_addressFamily = 0;
void jset_Sockaddr_addressFamily(JNIEnv * env, jobject instance, jint value) {
   (*env)->SetIntField(env, instance, Sockaddr_addressFamily, value);
}

jint jget_Sockaddr_addressFamily(JNIEnv * env, jobject instance) {
   return (*env)->GetIntField(env, instance, Sockaddr_addressFamily);
}

static jfieldID Sockaddr_address = 0;
void jset_Sockaddr_address(JNIEnv * env, jobject instance, jbyteArray value) {
   (*env)->SetObjectField(env, instance, Sockaddr_address, value);
}

jboolean jsetA_Sockaddr_address(JNIEnv * env, jobject instance, jbyte * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Sockaddr_address, 0);
        return JNI_TRUE;
    }
    if (len < 0) {
        len = 0;
    }
    jbyteArray tmp = (*env)->NewByteArray(env, len);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    if (len > 0) {
        (*env)->SetByteArrayRegion(env, tmp, 0, len, (const jbyte*) value);
    }
    (*env)->SetObjectField(env, instance, Sockaddr_address, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jbyteArray jget_Sockaddr_address(JNIEnv * env, jobject instance) {
   return (jbyteArray) (*env)->GetObjectField(env, instance, Sockaddr_address);
}

static jmethodID Sockaddr_C_0 = 0;
jobject jnew_Sockaddr(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, Sockaddr, Sockaddr_C_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Sockaddr_C_1 = 0;
jobject jnew_Sockaddr_1(JNIEnv * env, jint p0, jbyteArray p1) {
    jobject obj = (*env) -> NewObject(env, Sockaddr, Sockaddr_C_1, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Sockaddr_C_2 = 0;
jobject jnew_Sockaddr_2(JNIEnv * env, jobject p0) {
    jobject obj = (*env) -> NewObject(env, Sockaddr, Sockaddr_C_2, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Sockaddr_M_clone_0 = 0;
jobject jcall_Sockaddr_clone(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, Sockaddr_M_clone_0);
}

static jmethodID Sockaddr_M_copyTo_0 = 0;
void jcall_Sockaddr_copyTo(JNIEnv * env, jobject instance, jobject p0) {
    (*env) -> CallVoidMethod(env, instance, Sockaddr_M_copyTo_0, p0);
}

static jmethodID Sockaddr_M_getAddress_0 = 0;
jbyteArray jcall_Sockaddr_getAddress(JNIEnv * env, jobject instance) {
    return (jbyteArray) (*env) -> CallObjectMethod(env, instance, Sockaddr_M_getAddress_0);
}

static jmethodID Sockaddr_M_getAddressFamily_0 = 0;
jint jcall_Sockaddr_getAddressFamily(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, Sockaddr_M_getAddressFamily_0);
}

static jfieldID Stat_dev = 0;
void jset_Stat_dev(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_dev, value);
}

jlong jget_Stat_dev(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_dev);
}

static jfieldID Stat_ino = 0;
void jset_Stat_ino(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_ino, value);
}

jlong jget_Stat_ino(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_ino);
}

static jfieldID Stat_mode = 0;
void jset_Stat_mode(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_mode, value);
}

jlong jget_Stat_mode(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_mode);
}

static jfieldID Stat_nlink = 0;
void jset_Stat_nlink(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_nlink, value);
}

jlong jget_Stat_nlink(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_nlink);
}

static jfieldID Stat_uid = 0;
void jset_Stat_uid(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_uid, value);
}

jlong jget_Stat_uid(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_uid);
}

static jfieldID Stat_gid = 0;
void jset_Stat_gid(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_gid, value);
}

jlong jget_Stat_gid(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_gid);
}

static jfieldID Stat_rdev = 0;
void jset_Stat_rdev(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_rdev, value);
}

jlong jget_Stat_rdev(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_rdev);
}

static jfieldID Stat_size = 0;
void jset_Stat_size(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_size, value);
}

jlong jget_Stat_size(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_size);
}

static jfieldID Stat_blksize = 0;
void jset_Stat_blksize(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_blksize, value);
}

jlong jget_Stat_blksize(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_blksize);
}

static jfieldID Stat_blocks = 0;
void jset_Stat_blocks(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_blocks, value);
}

jlong jget_Stat_blocks(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_blocks);
}

static jfieldID Stat_atime = 0;
void jset_Stat_atime(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_atime, value);
}

jlong jget_Stat_atime(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_atime);
}

static jfieldID Stat_mtime = 0;
void jset_Stat_mtime(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_mtime, value);
}

jlong jget_Stat_mtime(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_mtime);
}

static jfieldID Stat_ctime = 0;
void jset_Stat_ctime(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Stat_ctime, value);
}

jlong jget_Stat_ctime(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Stat_ctime);
}

static jfieldID Stat_OR = 0;
void jset_Stat_OR(JNIEnv * env, jint value) {
   (*env)->SetStaticIntField(env, Stat, Stat_OR, value);
}

jint jget_Stat_OR(JNIEnv * env) {
   return (*env)->GetStaticIntField(env, Stat, Stat_OR);
}

static jfieldID Stat_OW = 0;
void jset_Stat_OW(JNIEnv * env, jint value) {
   (*env)->SetStaticIntField(env, Stat, Stat_OW, value);
}

jint jget_Stat_OW(JNIEnv * env) {
   return (*env)->GetStaticIntField(env, Stat, Stat_OW);
}

static jfieldID Stat_OE = 0;
void jset_Stat_OE(JNIEnv * env, jint value) {
   (*env)->SetStaticIntField(env, Stat, Stat_OE, value);
}

jint jget_Stat_OE(JNIEnv * env) {
   return (*env)->GetStaticIntField(env, Stat, Stat_OE);
}

static jfieldID Stat_GR = 0;
void jset_Stat_GR(JNIEnv * env, jint value) {
   (*env)->SetStaticIntField(env, Stat, Stat_GR, value);
}

jint jget_Stat_GR(JNIEnv * env) {
   return (*env)->GetStaticIntField(env, Stat, Stat_GR);
}

static jfieldID Stat_GW = 0;
void jset_Stat_GW(JNIEnv * env, jint value) {
   (*env)->SetStaticIntField(env, Stat, Stat_GW, value);
}

jint jget_Stat_GW(JNIEnv * env) {
   return (*env)->GetStaticIntField(env, Stat, Stat_GW);
}

static jfieldID Stat_GE = 0;
void jset_Stat_GE(JNIEnv * env, jint value) {
   (*env)->SetStaticIntField(env, Stat, Stat_GE, value);
}

jint jget_Stat_GE(JNIEnv * env) {
   return (*env)->GetStaticIntField(env, Stat, Stat_GE);
}

static jfieldID Stat_ER = 0;
void jset_Stat_ER(JNIEnv * env, jint value) {
   (*env)->SetStaticIntField(env, Stat, Stat_ER, value);
}

jint jget_Stat_ER(JNIEnv * env) {
   return (*env)->GetStaticIntField(env, Stat, Stat_ER);
}

static jfieldID Stat_EW = 0;
void jset_Stat_EW(JNIEnv * env, jint value) {
   (*env)->SetStaticIntField(env, Stat, Stat_EW, value);
}

jint jget_Stat_EW(JNIEnv * env) {
   return (*env)->GetStaticIntField(env, Stat, Stat_EW);
}

static jfieldID Stat_EE = 0;
void jset_Stat_EE(JNIEnv * env, jint value) {
   (*env)->SetStaticIntField(env, Stat, Stat_EE, value);
}

jint jget_Stat_EE(JNIEnv * env) {
   return (*env)->GetStaticIntField(env, Stat, Stat_EE);
}

static jmethodID Stat_C_0 = 0;
jobject jnew_Stat(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, Stat, Stat_C_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Stat_M_canGroupExecute_0 = 0;
jboolean jcall_Stat_canGroupExecute(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_canGroupExecute_0);
}

static jmethodID Stat_M_canGroupRead_0 = 0;
jboolean jcall_Stat_canGroupRead(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_canGroupRead_0);
}

static jmethodID Stat_M_canGroupWrite_0 = 0;
jboolean jcall_Stat_canGroupWrite(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_canGroupWrite_0);
}

static jmethodID Stat_M_canOthersExecute_0 = 0;
jboolean jcall_Stat_canOthersExecute(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_canOthersExecute_0);
}

static jmethodID Stat_M_canOthersRead_0 = 0;
jboolean jcall_Stat_canOthersRead(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_canOthersRead_0);
}

static jmethodID Stat_M_canOthersWrite_0 = 0;
jboolean jcall_Stat_canOthersWrite(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_canOthersWrite_0);
}

static jmethodID Stat_M_canOwnerExecute_0 = 0;
jboolean jcall_Stat_canOwnerExecute(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_canOwnerExecute_0);
}

static jmethodID Stat_M_canOwnerRead_0 = 0;
jboolean jcall_Stat_canOwnerRead(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_canOwnerRead_0);
}

static jmethodID Stat_M_canOwnerWrite_0 = 0;
jboolean jcall_Stat_canOwnerWrite(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_canOwnerWrite_0);
}

static jmethodID Stat_M_getAtime_0 = 0;
jlong jcall_Stat_getAtime(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getAtime_0);
}

static jmethodID Stat_M_getBlksize_0 = 0;
jlong jcall_Stat_getBlksize(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getBlksize_0);
}

static jmethodID Stat_M_getBlocks_0 = 0;
jlong jcall_Stat_getBlocks(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getBlocks_0);
}

static jmethodID Stat_M_getCtime_0 = 0;
jlong jcall_Stat_getCtime(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getCtime_0);
}

static jmethodID Stat_M_getDev_0 = 0;
jlong jcall_Stat_getDev(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getDev_0);
}

static jmethodID Stat_M_getGid_0 = 0;
jlong jcall_Stat_getGid(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getGid_0);
}

static jmethodID Stat_M_getIno_0 = 0;
jlong jcall_Stat_getIno(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getIno_0);
}

static jmethodID Stat_M_getMode_0 = 0;
jlong jcall_Stat_getMode(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getMode_0);
}

static jmethodID Stat_M_getMtime_0 = 0;
jlong jcall_Stat_getMtime(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getMtime_0);
}

static jmethodID Stat_M_getNlink_0 = 0;
jlong jcall_Stat_getNlink(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getNlink_0);
}

static jmethodID Stat_M_getPermissions_0 = 0;
jstring jcall_Stat_getPermissions(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, Stat_M_getPermissions_0);
}

static jmethodID Stat_M_getRdev_0 = 0;
jlong jcall_Stat_getRdev(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getRdev_0);
}

static jmethodID Stat_M_getSize_0 = 0;
jlong jcall_Stat_getSize(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getSize_0);
}

static jmethodID Stat_M_getUid_0 = 0;
jlong jcall_Stat_getUid(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Stat_M_getUid_0);
}

static jmethodID Stat_M_isBlockDevice_0 = 0;
jboolean jcall_Stat_isBlockDevice(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_isBlockDevice_0);
}

static jmethodID Stat_M_isCharacterDevice_0 = 0;
jboolean jcall_Stat_isCharacterDevice(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_isCharacterDevice_0);
}

static jmethodID Stat_M_isDir_0 = 0;
jboolean jcall_Stat_isDir(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_isDir_0);
}

static jmethodID Stat_M_isFIFO_0 = 0;
jboolean jcall_Stat_isFIFO(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_isFIFO_0);
}

static jmethodID Stat_M_isRegularFile_0 = 0;
jboolean jcall_Stat_isRegularFile(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_isRegularFile_0);
}

static jmethodID Stat_M_isSocket_0 = 0;
jboolean jcall_Stat_isSocket(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_isSocket_0);
}

static jmethodID Stat_M_isSymbolicLink_0 = 0;
jboolean jcall_Stat_isSymbolicLink(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Stat_M_isSymbolicLink_0);
}

static jmethodID Stat_M_toString_0 = 0;
jstring jcall_Stat_toString(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, Stat_M_toString_0);
}

static jfieldID Utsname_sysname = 0;
void jset_Utsname_sysname(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, Utsname_sysname, value);
}

jboolean jsetC_Utsname_sysname(JNIEnv * env, jobject instance, char * value) {
    return jsetCC_Utsname_sysname(env, instance, (char*) value);
}

jboolean jsetCC_Utsname_sysname(JNIEnv * env, jobject instance, const char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Utsname_sysname, 0);
        return JNI_TRUE;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewStringUTF");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, Utsname_sysname, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jboolean jsetWC_Utsname_sysname(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Utsname_sysname, 0);
        return JNI_TRUE;
    }
    
    jsize i = 0;
    while (value[i] != 0) {
        i++;
    }
    
    jstring tmp;
    if (sizeof(wchar_t) == sizeof(jchar)) {
        tmp = (*env) -> NewString(env, (const jchar*) value, i);
    } else {
        jchar tBuf[i];
        for (jsize j = 0; j < i; j++) {
            tBuf[j] = (jchar) value[j];
        }
        tmp = (*env) -> NewString(env, (const jchar*) tBuf, i);
    }
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, Utsname_sysname, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jstring jget_Utsname_sysname(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, Utsname_sysname);
}

static jfieldID Utsname_nodename = 0;
void jset_Utsname_nodename(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, Utsname_nodename, value);
}

jboolean jsetC_Utsname_nodename(JNIEnv * env, jobject instance, char * value) {
    return jsetCC_Utsname_nodename(env, instance, (char*) value);
}

jboolean jsetCC_Utsname_nodename(JNIEnv * env, jobject instance, const char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Utsname_nodename, 0);
        return JNI_TRUE;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewStringUTF");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, Utsname_nodename, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jboolean jsetWC_Utsname_nodename(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Utsname_nodename, 0);
        return JNI_TRUE;
    }
    
    jsize i = 0;
    while (value[i] != 0) {
        i++;
    }
    
    jstring tmp;
    if (sizeof(wchar_t) == sizeof(jchar)) {
        tmp = (*env) -> NewString(env, (const jchar*) value, i);
    } else {
        jchar tBuf[i];
        for (jsize j = 0; j < i; j++) {
            tBuf[j] = (jchar) value[j];
        }
        tmp = (*env) -> NewString(env, (const jchar*) tBuf, i);
    }
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, Utsname_nodename, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jstring jget_Utsname_nodename(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, Utsname_nodename);
}

static jfieldID Utsname_release = 0;
void jset_Utsname_release(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, Utsname_release, value);
}

jboolean jsetC_Utsname_release(JNIEnv * env, jobject instance, char * value) {
    return jsetCC_Utsname_release(env, instance, (char*) value);
}

jboolean jsetCC_Utsname_release(JNIEnv * env, jobject instance, const char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Utsname_release, 0);
        return JNI_TRUE;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewStringUTF");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, Utsname_release, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jboolean jsetWC_Utsname_release(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Utsname_release, 0);
        return JNI_TRUE;
    }
    
    jsize i = 0;
    while (value[i] != 0) {
        i++;
    }
    
    jstring tmp;
    if (sizeof(wchar_t) == sizeof(jchar)) {
        tmp = (*env) -> NewString(env, (const jchar*) value, i);
    } else {
        jchar tBuf[i];
        for (jsize j = 0; j < i; j++) {
            tBuf[j] = (jchar) value[j];
        }
        tmp = (*env) -> NewString(env, (const jchar*) tBuf, i);
    }
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, Utsname_release, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jstring jget_Utsname_release(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, Utsname_release);
}

static jfieldID Utsname_version = 0;
void jset_Utsname_version(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, Utsname_version, value);
}

jboolean jsetC_Utsname_version(JNIEnv * env, jobject instance, char * value) {
    return jsetCC_Utsname_version(env, instance, (char*) value);
}

jboolean jsetCC_Utsname_version(JNIEnv * env, jobject instance, const char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Utsname_version, 0);
        return JNI_TRUE;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewStringUTF");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, Utsname_version, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jboolean jsetWC_Utsname_version(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Utsname_version, 0);
        return JNI_TRUE;
    }
    
    jsize i = 0;
    while (value[i] != 0) {
        i++;
    }
    
    jstring tmp;
    if (sizeof(wchar_t) == sizeof(jchar)) {
        tmp = (*env) -> NewString(env, (const jchar*) value, i);
    } else {
        jchar tBuf[i];
        for (jsize j = 0; j < i; j++) {
            tBuf[j] = (jchar) value[j];
        }
        tmp = (*env) -> NewString(env, (const jchar*) tBuf, i);
    }
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, Utsname_version, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jstring jget_Utsname_version(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, Utsname_version);
}

static jfieldID Utsname_machine = 0;
void jset_Utsname_machine(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, Utsname_machine, value);
}

jboolean jsetC_Utsname_machine(JNIEnv * env, jobject instance, char * value) {
    return jsetCC_Utsname_machine(env, instance, (char*) value);
}

jboolean jsetCC_Utsname_machine(JNIEnv * env, jobject instance, const char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Utsname_machine, 0);
        return JNI_TRUE;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewStringUTF");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, Utsname_machine, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jboolean jsetWC_Utsname_machine(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Utsname_machine, 0);
        return JNI_TRUE;
    }
    
    jsize i = 0;
    while (value[i] != 0) {
        i++;
    }
    
    jstring tmp;
    if (sizeof(wchar_t) == sizeof(jchar)) {
        tmp = (*env) -> NewString(env, (const jchar*) value, i);
    } else {
        jchar tBuf[i];
        for (jsize j = 0; j < i; j++) {
            tBuf[j] = (jchar) value[j];
        }
        tmp = (*env) -> NewString(env, (const jchar*) tBuf, i);
    }
    if (tmp == 0) {
        throw_internal_OutOfMemoryError(env, "NewByteArray");
        return JNI_FALSE;
    }
    (*env)->SetObjectField(env, instance, Utsname_machine, tmp);
    (*env)->DeleteLocalRef(env, tmp);
    return JNI_TRUE;
}

jstring jget_Utsname_machine(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, Utsname_machine);
}

static jmethodID Utsname_C_0 = 0;
jobject jnew_Utsname(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, Utsname, Utsname_C_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Utsname_M_getMachine_0 = 0;
jstring jcall_Utsname_getMachine(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, Utsname_M_getMachine_0);
}

static jmethodID Utsname_M_getNodename_0 = 0;
jstring jcall_Utsname_getNodename(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, Utsname_M_getNodename_0);
}

static jmethodID Utsname_M_getRelease_0 = 0;
jstring jcall_Utsname_getRelease(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, Utsname_M_getRelease_0);
}

static jmethodID Utsname_M_getSysname_0 = 0;
jstring jcall_Utsname_getSysname(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, Utsname_M_getSysname_0);
}

static jmethodID Utsname_M_getVersion_0 = 0;
jstring jcall_Utsname_getVersion(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, Utsname_M_getVersion_0);
}

static jfieldID Win32FileAttributeData_dwFileAttributes = 0;
void jset_Win32FileAttributeData_dwFileAttributes(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Win32FileAttributeData_dwFileAttributes, value);
}

jlong jget_Win32FileAttributeData_dwFileAttributes(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Win32FileAttributeData_dwFileAttributes);
}

static jfieldID Win32FileAttributeData_nFileSizeLow = 0;
void jset_Win32FileAttributeData_nFileSizeLow(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Win32FileAttributeData_nFileSizeLow, value);
}

jlong jget_Win32FileAttributeData_nFileSizeLow(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Win32FileAttributeData_nFileSizeLow);
}

static jfieldID Win32FileAttributeData_nFileSizeHigh = 0;
void jset_Win32FileAttributeData_nFileSizeHigh(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Win32FileAttributeData_nFileSizeHigh, value);
}

jlong jget_Win32FileAttributeData_nFileSizeHigh(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Win32FileAttributeData_nFileSizeHigh);
}

static jfieldID Win32FileAttributeData_ftLastAccessTimeLow = 0;
void jset_Win32FileAttributeData_ftLastAccessTimeLow(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Win32FileAttributeData_ftLastAccessTimeLow, value);
}

jlong jget_Win32FileAttributeData_ftLastAccessTimeLow(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Win32FileAttributeData_ftLastAccessTimeLow);
}

static jfieldID Win32FileAttributeData_ftLastAccessTimeHigh = 0;
void jset_Win32FileAttributeData_ftLastAccessTimeHigh(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Win32FileAttributeData_ftLastAccessTimeHigh, value);
}

jlong jget_Win32FileAttributeData_ftLastAccessTimeHigh(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Win32FileAttributeData_ftLastAccessTimeHigh);
}

static jfieldID Win32FileAttributeData_ftLastWriteTimeHigh = 0;
void jset_Win32FileAttributeData_ftLastWriteTimeHigh(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Win32FileAttributeData_ftLastWriteTimeHigh, value);
}

jlong jget_Win32FileAttributeData_ftLastWriteTimeHigh(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Win32FileAttributeData_ftLastWriteTimeHigh);
}

static jfieldID Win32FileAttributeData_ftLastWriteTimeLow = 0;
void jset_Win32FileAttributeData_ftLastWriteTimeLow(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Win32FileAttributeData_ftLastWriteTimeLow, value);
}

jlong jget_Win32FileAttributeData_ftLastWriteTimeLow(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Win32FileAttributeData_ftLastWriteTimeLow);
}

static jfieldID Win32FileAttributeData_ftCreationTimeHigh = 0;
void jset_Win32FileAttributeData_ftCreationTimeHigh(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Win32FileAttributeData_ftCreationTimeHigh, value);
}

jlong jget_Win32FileAttributeData_ftCreationTimeHigh(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Win32FileAttributeData_ftCreationTimeHigh);
}

static jfieldID Win32FileAttributeData_ftCreationTimeLow = 0;
void jset_Win32FileAttributeData_ftCreationTimeLow(JNIEnv * env, jobject instance, jlong value) {
   (*env)->SetLongField(env, instance, Win32FileAttributeData_ftCreationTimeLow, value);
}

jlong jget_Win32FileAttributeData_ftCreationTimeLow(JNIEnv * env, jobject instance) {
   return (*env)->GetLongField(env, instance, Win32FileAttributeData_ftCreationTimeLow);
}

static jmethodID Win32FileAttributeData_C_0 = 0;
jobject jnew_Win32FileAttributeData(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, Win32FileAttributeData, Win32FileAttributeData_C_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID Win32FileAttributeData_M_getDwFileAttributes_0 = 0;
jlong jcall_Win32FileAttributeData_getDwFileAttributes(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Win32FileAttributeData_M_getDwFileAttributes_0);
}

static jmethodID Win32FileAttributeData_M_getFtCreationTimeHigh_0 = 0;
jlong jcall_Win32FileAttributeData_getFtCreationTimeHigh(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Win32FileAttributeData_M_getFtCreationTimeHigh_0);
}

static jmethodID Win32FileAttributeData_M_getFtCreationTimeLow_0 = 0;
jlong jcall_Win32FileAttributeData_getFtCreationTimeLow(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Win32FileAttributeData_M_getFtCreationTimeLow_0);
}

static jmethodID Win32FileAttributeData_M_getFtLastAccessTimeHigh_0 = 0;
jlong jcall_Win32FileAttributeData_getFtLastAccessTimeHigh(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Win32FileAttributeData_M_getFtLastAccessTimeHigh_0);
}

static jmethodID Win32FileAttributeData_M_getFtLastAccessTimeLow_0 = 0;
jlong jcall_Win32FileAttributeData_getFtLastAccessTimeLow(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Win32FileAttributeData_M_getFtLastAccessTimeLow_0);
}

static jmethodID Win32FileAttributeData_M_getFtLastWriteTimeHigh_0 = 0;
jlong jcall_Win32FileAttributeData_getFtLastWriteTimeHigh(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Win32FileAttributeData_M_getFtLastWriteTimeHigh_0);
}

static jmethodID Win32FileAttributeData_M_getFtLastWriteTimeLow_0 = 0;
jlong jcall_Win32FileAttributeData_getFtLastWriteTimeLow(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Win32FileAttributeData_M_getFtLastWriteTimeLow_0);
}

static jmethodID Win32FileAttributeData_M_getnFileSizeHigh_0 = 0;
jlong jcall_Win32FileAttributeData_getnFileSizeHigh(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Win32FileAttributeData_M_getnFileSizeHigh_0);
}

static jmethodID Win32FileAttributeData_M_getnFileSizeLow_0 = 0;
jlong jcall_Win32FileAttributeData_getnFileSizeLow(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, Win32FileAttributeData_M_getnFileSizeLow_0);
}

static jmethodID Iterable_M_iterator_0 = 0;
jobject jcall_Iterable_iterator(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, Iterable_M_iterator_0);
}

static jmethodID InetAddress_M_equals_0 = 0;
jboolean jcall_InetAddress_equals(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_equals_0, p0);
}

static jmethodID InetAddress_M_getAddress_0 = 0;
jbyteArray jcall_InetAddress_getAddress(JNIEnv * env, jobject instance) {
    return (jbyteArray) (*env) -> CallObjectMethod(env, instance, InetAddress_M_getAddress_0);
}

static jmethodID InetAddress_M_getAllByName_0 = 0;
jobjectArray jcall_InetAddress_getAllByName(JNIEnv * env, jstring p0) {
    return (jobjectArray) (*env) -> CallStaticObjectMethod(env, InetAddress, InetAddress_M_getAllByName_0, p0);
}

static jmethodID InetAddress_M_getByAddress_0 = 0;
jobject jcall_InetAddress_getByAddress(JNIEnv * env, jstring p0, jbyteArray p1) {
    return (*env) -> CallStaticObjectMethod(env, InetAddress, InetAddress_M_getByAddress_0, p0, p1);
}

static jmethodID InetAddress_M_getByAddress_1 = 0;
jobject jcall_InetAddress_getByAddress_1(JNIEnv * env, jbyteArray p0) {
    return (*env) -> CallStaticObjectMethod(env, InetAddress, InetAddress_M_getByAddress_1, p0);
}

static jmethodID InetAddress_M_getByName_0 = 0;
jobject jcall_InetAddress_getByName(JNIEnv * env, jstring p0) {
    return (*env) -> CallStaticObjectMethod(env, InetAddress, InetAddress_M_getByName_0, p0);
}

static jmethodID InetAddress_M_getCanonicalHostName_0 = 0;
jstring jcall_InetAddress_getCanonicalHostName(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, InetAddress_M_getCanonicalHostName_0);
}

static jmethodID InetAddress_M_getHostAddress_0 = 0;
jstring jcall_InetAddress_getHostAddress(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, InetAddress_M_getHostAddress_0);
}

static jmethodID InetAddress_M_getHostName_0 = 0;
jstring jcall_InetAddress_getHostName(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, InetAddress_M_getHostName_0);
}

static jmethodID InetAddress_M_getLocalHost_0 = 0;
jobject jcall_InetAddress_getLocalHost(JNIEnv * env) {
    return (*env) -> CallStaticObjectMethod(env, InetAddress, InetAddress_M_getLocalHost_0);
}

static jmethodID InetAddress_M_getLoopbackAddress_0 = 0;
jobject jcall_InetAddress_getLoopbackAddress(JNIEnv * env) {
    return (*env) -> CallStaticObjectMethod(env, InetAddress, InetAddress_M_getLoopbackAddress_0);
}

static jmethodID InetAddress_M_hashCode_0 = 0;
jint jcall_InetAddress_hashCode(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, InetAddress_M_hashCode_0);
}

static jmethodID InetAddress_M_isAnyLocalAddress_0 = 0;
jboolean jcall_InetAddress_isAnyLocalAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isAnyLocalAddress_0);
}

static jmethodID InetAddress_M_isLinkLocalAddress_0 = 0;
jboolean jcall_InetAddress_isLinkLocalAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isLinkLocalAddress_0);
}

static jmethodID InetAddress_M_isLoopbackAddress_0 = 0;
jboolean jcall_InetAddress_isLoopbackAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isLoopbackAddress_0);
}

static jmethodID InetAddress_M_isMCGlobal_0 = 0;
jboolean jcall_InetAddress_isMCGlobal(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isMCGlobal_0);
}

static jmethodID InetAddress_M_isMCLinkLocal_0 = 0;
jboolean jcall_InetAddress_isMCLinkLocal(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isMCLinkLocal_0);
}

static jmethodID InetAddress_M_isMCNodeLocal_0 = 0;
jboolean jcall_InetAddress_isMCNodeLocal(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isMCNodeLocal_0);
}

static jmethodID InetAddress_M_isMCOrgLocal_0 = 0;
jboolean jcall_InetAddress_isMCOrgLocal(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isMCOrgLocal_0);
}

static jmethodID InetAddress_M_isMCSiteLocal_0 = 0;
jboolean jcall_InetAddress_isMCSiteLocal(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isMCSiteLocal_0);
}

static jmethodID InetAddress_M_isMulticastAddress_0 = 0;
jboolean jcall_InetAddress_isMulticastAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isMulticastAddress_0);
}

static jmethodID InetAddress_M_isReachable_0 = 0;
jboolean jcall_InetAddress_isReachable(JNIEnv * env, jobject instance, jint p0) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isReachable_0, p0);
}

static jmethodID InetAddress_M_isReachable_1 = 0;
jboolean jcall_InetAddress_isReachable_1(JNIEnv * env, jobject instance, jobject p0, jint p1, jint p2) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isReachable_1, p0, p1, p2);
}

static jmethodID InetAddress_M_isSiteLocalAddress_0 = 0;
jboolean jcall_InetAddress_isSiteLocalAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, InetAddress_M_isSiteLocalAddress_0);
}

static jmethodID InetAddress_M_toString_0 = 0;
jstring jcall_InetAddress_toString(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, InetAddress_M_toString_0);
}

static jmethodID InetSocketAddress_C_0 = 0;
jobject jnew_InetSocketAddress(JNIEnv * env, jint p0) {
    jobject obj = (*env) -> NewObject(env, InetSocketAddress, InetSocketAddress_C_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID InetSocketAddress_C_1 = 0;
jobject jnew_InetSocketAddress_1(JNIEnv * env, jstring p0, jint p1) {
    jobject obj = (*env) -> NewObject(env, InetSocketAddress, InetSocketAddress_C_1, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID InetSocketAddress_C_2 = 0;
jobject jnew_InetSocketAddress_2(JNIEnv * env, jobject p0, jint p1) {
    jobject obj = (*env) -> NewObject(env, InetSocketAddress, InetSocketAddress_C_2, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID InetSocketAddress_M_createUnresolved_0 = 0;
jobject jcall_InetSocketAddress_createUnresolved(JNIEnv * env, jstring p0, jint p1) {
    return (*env) -> CallStaticObjectMethod(env, InetSocketAddress, InetSocketAddress_M_createUnresolved_0, p0, p1);
}

static jmethodID InetSocketAddress_M_equals_0 = 0;
jboolean jcall_InetSocketAddress_equals(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, InetSocketAddress_M_equals_0, p0);
}

static jmethodID InetSocketAddress_M_getAddress_0 = 0;
jobject jcall_InetSocketAddress_getAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, InetSocketAddress_M_getAddress_0);
}

static jmethodID InetSocketAddress_M_getHostName_0 = 0;
jstring jcall_InetSocketAddress_getHostName(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, InetSocketAddress_M_getHostName_0);
}

static jmethodID InetSocketAddress_M_getHostString_0 = 0;
jstring jcall_InetSocketAddress_getHostString(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, InetSocketAddress_M_getHostString_0);
}

static jmethodID InetSocketAddress_M_getPort_0 = 0;
jint jcall_InetSocketAddress_getPort(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, InetSocketAddress_M_getPort_0);
}

static jmethodID InetSocketAddress_M_hashCode_0 = 0;
jint jcall_InetSocketAddress_hashCode(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, InetSocketAddress_M_hashCode_0);
}

static jmethodID InetSocketAddress_M_isUnresolved_0 = 0;
jboolean jcall_InetSocketAddress_isUnresolved(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, InetSocketAddress_M_isUnresolved_0);
}

static jmethodID InetSocketAddress_M_toString_0 = 0;
jstring jcall_InetSocketAddress_toString(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, InetSocketAddress_M_toString_0);
}

static jmethodID ArrayList_C_0 = 0;
jobject jnew_ArrayList(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, ArrayList, ArrayList_C_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID ArrayList_C_1 = 0;
jobject jnew_ArrayList_1(JNIEnv * env, jint p0) {
    jobject obj = (*env) -> NewObject(env, ArrayList, ArrayList_C_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID ArrayList_C_2 = 0;
jobject jnew_ArrayList_2(JNIEnv * env, jobject p0) {
    jobject obj = (*env) -> NewObject(env, ArrayList, ArrayList_C_2, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
    }
    return obj;
}

static jmethodID ArrayList_M_add_0 = 0;
void jcall_ArrayList_add(JNIEnv * env, jobject instance, jint p0, jobject p1) {
    (*env) -> CallVoidMethod(env, instance, ArrayList_M_add_0, p0, p1);
}

static jmethodID ArrayList_M_add_1 = 0;
jboolean jcall_ArrayList_add_1(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, ArrayList_M_add_1, p0);
}

static jmethodID ArrayList_M_addAll_0 = 0;
jboolean jcall_ArrayList_addAll(JNIEnv * env, jobject instance, jint p0, jobject p1) {
    return (*env) -> CallBooleanMethod(env, instance, ArrayList_M_addAll_0, p0, p1);
}

static jmethodID ArrayList_M_addAll_1 = 0;
jboolean jcall_ArrayList_addAll_1(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, ArrayList_M_addAll_1, p0);
}

static jmethodID ArrayList_M_clear_0 = 0;
void jcall_ArrayList_clear(JNIEnv * env, jobject instance) {
    (*env) -> CallVoidMethod(env, instance, ArrayList_M_clear_0);
}

static jmethodID ArrayList_M_clone_0 = 0;
jobject jcall_ArrayList_clone(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, ArrayList_M_clone_0);
}

static jmethodID ArrayList_M_contains_0 = 0;
jboolean jcall_ArrayList_contains(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, ArrayList_M_contains_0, p0);
}

static jmethodID ArrayList_M_ensureCapacity_0 = 0;
void jcall_ArrayList_ensureCapacity(JNIEnv * env, jobject instance, jint p0) {
    (*env) -> CallVoidMethod(env, instance, ArrayList_M_ensureCapacity_0, p0);
}

static jmethodID ArrayList_M_get_0 = 0;
jobject jcall_ArrayList_get(JNIEnv * env, jobject instance, jint p0) {
    return (*env) -> CallObjectMethod(env, instance, ArrayList_M_get_0, p0);
}

static jmethodID ArrayList_M_indexOf_0 = 0;
jint jcall_ArrayList_indexOf(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallIntMethod(env, instance, ArrayList_M_indexOf_0, p0);
}

static jmethodID ArrayList_M_isEmpty_0 = 0;
jboolean jcall_ArrayList_isEmpty(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, ArrayList_M_isEmpty_0);
}

static jmethodID ArrayList_M_iterator_0 = 0;
jobject jcall_ArrayList_iterator(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, ArrayList_M_iterator_0);
}

static jmethodID ArrayList_M_lastIndexOf_0 = 0;
jint jcall_ArrayList_lastIndexOf(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallIntMethod(env, instance, ArrayList_M_lastIndexOf_0, p0);
}

static jmethodID ArrayList_M_listIterator_0 = 0;
jobject jcall_ArrayList_listIterator(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, ArrayList_M_listIterator_0);
}

static jmethodID ArrayList_M_listIterator_1 = 0;
jobject jcall_ArrayList_listIterator_1(JNIEnv * env, jobject instance, jint p0) {
    return (*env) -> CallObjectMethod(env, instance, ArrayList_M_listIterator_1, p0);
}

static jmethodID ArrayList_M_remove_0 = 0;
jobject jcall_ArrayList_remove(JNIEnv * env, jobject instance, jint p0) {
    return (*env) -> CallObjectMethod(env, instance, ArrayList_M_remove_0, p0);
}

static jmethodID ArrayList_M_remove_1 = 0;
jboolean jcall_ArrayList_remove_1(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, ArrayList_M_remove_1, p0);
}

static jmethodID ArrayList_M_removeAll_0 = 0;
jboolean jcall_ArrayList_removeAll(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, ArrayList_M_removeAll_0, p0);
}

static jmethodID ArrayList_M_retainAll_0 = 0;
jboolean jcall_ArrayList_retainAll(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, ArrayList_M_retainAll_0, p0);
}

static jmethodID ArrayList_M_set_0 = 0;
jobject jcall_ArrayList_set(JNIEnv * env, jobject instance, jint p0, jobject p1) {
    return (*env) -> CallObjectMethod(env, instance, ArrayList_M_set_0, p0, p1);
}

static jmethodID ArrayList_M_size_0 = 0;
jint jcall_ArrayList_size(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, ArrayList_M_size_0);
}

static jmethodID ArrayList_M_subList_0 = 0;
jobject jcall_ArrayList_subList(JNIEnv * env, jobject instance, jint p0, jint p1) {
    return (*env) -> CallObjectMethod(env, instance, ArrayList_M_subList_0, p0, p1);
}

static jmethodID ArrayList_M_toArray_0 = 0;
jobjectArray jcall_ArrayList_toArray(JNIEnv * env, jobject instance) {
    return (jobjectArray) (*env) -> CallObjectMethod(env, instance, ArrayList_M_toArray_0);
}

static jmethodID ArrayList_M_toArray_1 = 0;
jobjectArray jcall_ArrayList_toArray_1(JNIEnv * env, jobject instance, jobjectArray p0) {
    return (jobjectArray) (*env) -> CallObjectMethod(env, instance, ArrayList_M_toArray_1, p0);
}

static jmethodID ArrayList_M_trimToSize_0 = 0;
void jcall_ArrayList_trimToSize(JNIEnv * env, jobject instance) {
    (*env) -> CallVoidMethod(env, instance, ArrayList_M_trimToSize_0);
}

static jmethodID Collection_M_add_0 = 0;
jboolean jcall_Collection_add(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, Collection_M_add_0, p0);
}

static jmethodID Collection_M_addAll_0 = 0;
jboolean jcall_Collection_addAll(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, Collection_M_addAll_0, p0);
}

static jmethodID Collection_M_clear_0 = 0;
void jcall_Collection_clear(JNIEnv * env, jobject instance) {
    (*env) -> CallVoidMethod(env, instance, Collection_M_clear_0);
}

static jmethodID Collection_M_contains_0 = 0;
jboolean jcall_Collection_contains(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, Collection_M_contains_0, p0);
}

static jmethodID Collection_M_containsAll_0 = 0;
jboolean jcall_Collection_containsAll(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, Collection_M_containsAll_0, p0);
}

static jmethodID Collection_M_equals_0 = 0;
jboolean jcall_Collection_equals(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, Collection_M_equals_0, p0);
}

static jmethodID Collection_M_hashCode_0 = 0;
jint jcall_Collection_hashCode(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, Collection_M_hashCode_0);
}

static jmethodID Collection_M_isEmpty_0 = 0;
jboolean jcall_Collection_isEmpty(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Collection_M_isEmpty_0);
}

static jmethodID Collection_M_iterator_0 = 0;
jobject jcall_Collection_iterator(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, Collection_M_iterator_0);
}

static jmethodID Collection_M_remove_0 = 0;
jboolean jcall_Collection_remove(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, Collection_M_remove_0, p0);
}

static jmethodID Collection_M_removeAll_0 = 0;
jboolean jcall_Collection_removeAll(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, Collection_M_removeAll_0, p0);
}

static jmethodID Collection_M_retainAll_0 = 0;
jboolean jcall_Collection_retainAll(JNIEnv * env, jobject instance, jobject p0) {
    return (*env) -> CallBooleanMethod(env, instance, Collection_M_retainAll_0, p0);
}

static jmethodID Collection_M_size_0 = 0;
jint jcall_Collection_size(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, Collection_M_size_0);
}

static jmethodID Collection_M_toArray_0 = 0;
jobjectArray jcall_Collection_toArray(JNIEnv * env, jobject instance) {
    return (jobjectArray) (*env) -> CallObjectMethod(env, instance, Collection_M_toArray_0);
}

static jmethodID Collection_M_toArray_1 = 0;
jobjectArray jcall_Collection_toArray_1(JNIEnv * env, jobject instance, jobjectArray p0) {
    return (jobjectArray) (*env) -> CallObjectMethod(env, instance, Collection_M_toArray_1, p0);
}

static jmethodID Iterator_M_hasNext_0 = 0;
jboolean jcall_Iterator_hasNext(JNIEnv * env, jobject instance) {
    return (*env) -> CallBooleanMethod(env, instance, Iterator_M_hasNext_0);
}

static jmethodID Iterator_M_next_0 = 0;
jobject jcall_Iterator_next(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, Iterator_M_next_0);
}

static jmethodID Iterator_M_remove_0 = 0;
void jcall_Iterator_remove(JNIEnv * env, jobject instance) {
    (*env) -> CallVoidMethod(env, instance, Iterator_M_remove_0);
}

static jmethodID InvalidFileDescriptorException_EC_0 = 0;
void jthrow_InvalidFileDescriptorException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, InvalidFileDescriptorException, InvalidFileDescriptorException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID MutexAbandonedException_EC_0 = 0;
void jthrow_MutexAbandonedException(JNIEnv * env, jlong p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, MutexAbandonedException, MutexAbandonedException_EC_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID OperationInProgressException_EC_0 = 0;
void jthrow_OperationInProgressException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, OperationInProgressException, OperationInProgressException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID OperationInProgressException_EC_1 = 0;
void jthrow_OperationInProgressException_1(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, OperationInProgressException, OperationInProgressException_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_OperationInProgressException_1(JNIEnv * env, char* p0) {
    jthrowCC_OperationInProgressException_1(env, (const char*)p0);
}

void jthrowCC_OperationInProgressException_1(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, OperationInProgressException, p0);
}
static jmethodID PermissionDeniedException_EC_0 = 0;
void jthrow_PermissionDeniedException(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, PermissionDeniedException, PermissionDeniedException_EC_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_PermissionDeniedException(JNIEnv * env, char* p0) {
    jthrowCC_PermissionDeniedException(env, (const char*)p0);
}

void jthrowCC_PermissionDeniedException(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, PermissionDeniedException, p0);
}
static jmethodID PermissionDeniedException_EC_1 = 0;
void jthrow_PermissionDeniedException_1(JNIEnv * env, jstring p0, jstring p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, PermissionDeniedException, PermissionDeniedException_EC_1, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_PermissionDeniedException_1(JNIEnv * env, char* p0, char* p1) {
    jthrowCC_PermissionDeniedException_1(env, (const char*)p0, (const char*)p1);
}

void jthrowCC_PermissionDeniedException_1(JNIEnv * env, const char* p0, const char* p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[2];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p1 == 0) {
        parameters[1].l = 0;
    } else {
        parameters[1].l = (*env) -> NewStringUTF(env, p1);
        if (parameters[1].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    jobject obj = (*env) -> NewObjectA(env, PermissionDeniedException, PermissionDeniedException_EC_1, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID QuotaExceededException_EC_0 = 0;
void jthrow_QuotaExceededException(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, QuotaExceededException, QuotaExceededException_EC_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_QuotaExceededException(JNIEnv * env, char* p0) {
    jthrowCC_QuotaExceededException(env, (const char*)p0);
}

void jthrowCC_QuotaExceededException(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, QuotaExceededException, p0);
}
static jmethodID QuotaExceededException_EC_1 = 0;
void jthrow_QuotaExceededException_1(JNIEnv * env, jstring p0, jstring p1, jstring p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, QuotaExceededException, QuotaExceededException_EC_1, p0, p1, p2);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_QuotaExceededException_1(JNIEnv * env, char* p0, char* p1, char* p2) {
    jthrowCC_QuotaExceededException_1(env, (const char*)p0, (const char*)p1, (const char*)p2);
}

void jthrowCC_QuotaExceededException_1(JNIEnv * env, const char* p0, const char* p1, const char* p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[3];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p1 == 0) {
        parameters[1].l = 0;
    } else {
        parameters[1].l = (*env) -> NewStringUTF(env, p1);
        if (parameters[1].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p2 == 0) {
        parameters[2].l = 0;
    } else {
        parameters[2].l = (*env) -> NewStringUTF(env, p2);
        if (parameters[2].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    jobject obj = (*env) -> NewObjectA(env, QuotaExceededException, QuotaExceededException_EC_1, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID SharingViolationException_EC_0 = 0;
void jthrow_SharingViolationException(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, SharingViolationException, SharingViolationException_EC_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_SharingViolationException(JNIEnv * env, char* p0) {
    jthrowCC_SharingViolationException(env, (const char*)p0);
}

void jthrowCC_SharingViolationException(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, SharingViolationException, p0);
}
static jmethodID SharingViolationException_EC_1 = 0;
void jthrow_SharingViolationException_1(JNIEnv * env, jstring p0, jstring p1, jstring p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, SharingViolationException, SharingViolationException_EC_1, p0, p1, p2);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_SharingViolationException_1(JNIEnv * env, char* p0, char* p1, char* p2) {
    jthrowCC_SharingViolationException_1(env, (const char*)p0, (const char*)p1, (const char*)p2);
}

void jthrowCC_SharingViolationException_1(JNIEnv * env, const char* p0, const char* p1, const char* p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[3];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p1 == 0) {
        parameters[1].l = 0;
    } else {
        parameters[1].l = (*env) -> NewStringUTF(env, p1);
        if (parameters[1].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p2 == 0) {
        parameters[2].l = 0;
    } else {
        parameters[2].l = (*env) -> NewStringUTF(env, p2);
        if (parameters[2].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    jobject obj = (*env) -> NewObjectA(env, SharingViolationException, SharingViolationException_EC_1, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID ShellExecuteException_EC_0 = 0;
void jthrow_ShellExecuteException(JNIEnv * env, jlong p0, jlong p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, ShellExecuteException, ShellExecuteException_EC_0, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID UnknownNativeErrorException_EC_0 = 0;
void jthrow_UnknownNativeErrorException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, UnknownNativeErrorException, UnknownNativeErrorException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID UnknownNativeErrorException_EC_1 = 0;
void jthrow_UnknownNativeErrorException_1(JNIEnv * env, jlong p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, UnknownNativeErrorException, UnknownNativeErrorException_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID FileNotFoundException_EC_0 = 0;
void jthrow_FileNotFoundException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, FileNotFoundException, FileNotFoundException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID FileNotFoundException_EC_1 = 0;
void jthrow_FileNotFoundException_1(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, FileNotFoundException, FileNotFoundException_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_FileNotFoundException_1(JNIEnv * env, char* p0) {
    jthrowCC_FileNotFoundException_1(env, (const char*)p0);
}

void jthrowCC_FileNotFoundException_1(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, FileNotFoundException, p0);
}
static jmethodID IOException_EC_0 = 0;
void jthrow_IOException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IOException, IOException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID IOException_EC_1 = 0;
void jthrow_IOException_1(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IOException, IOException_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_IOException_1(JNIEnv * env, char* p0) {
    jthrowCC_IOException_1(env, (const char*)p0);
}

void jthrowCC_IOException_1(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, IOException, p0);
}
static jmethodID IOException_EC_2 = 0;
void jthrow_IOException_2(JNIEnv * env, jstring p0, jobject p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IOException, IOException_EC_2, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_IOException_2(JNIEnv * env, char* p0, jobject p1) {
    jthrowCC_IOException_2(env, (const char*)p0, p1);
}

void jthrowCC_IOException_2(JNIEnv * env, const char* p0, jobject p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[2];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    parameters[1].l = p1;
    jobject obj = (*env) -> NewObjectA(env, IOException, IOException_EC_2, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID IOException_EC_3 = 0;
void jthrow_IOException_3(JNIEnv * env, jobject p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IOException, IOException_EC_3, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID Exception_EC_0 = 0;
void jthrow_Exception(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, Exception, Exception_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID Exception_EC_1 = 0;
void jthrow_Exception_1(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, Exception, Exception_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_Exception_1(JNIEnv * env, char* p0) {
    jthrowCC_Exception_1(env, (const char*)p0);
}

void jthrowCC_Exception_1(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, Exception, p0);
}
static jmethodID Exception_EC_2 = 0;
void jthrow_Exception_2(JNIEnv * env, jstring p0, jobject p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, Exception, Exception_EC_2, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_Exception_2(JNIEnv * env, char* p0, jobject p1) {
    jthrowCC_Exception_2(env, (const char*)p0, p1);
}

void jthrowCC_Exception_2(JNIEnv * env, const char* p0, jobject p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[2];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    parameters[1].l = p1;
    jobject obj = (*env) -> NewObjectA(env, Exception, Exception_EC_2, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID Exception_EC_3 = 0;
void jthrow_Exception_3(JNIEnv * env, jobject p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, Exception, Exception_EC_3, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID IllegalArgumentException_EC_0 = 0;
void jthrow_IllegalArgumentException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IllegalArgumentException, IllegalArgumentException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID IllegalArgumentException_EC_1 = 0;
void jthrow_IllegalArgumentException_1(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IllegalArgumentException, IllegalArgumentException_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_IllegalArgumentException_1(JNIEnv * env, char* p0) {
    jthrowCC_IllegalArgumentException_1(env, (const char*)p0);
}

void jthrowCC_IllegalArgumentException_1(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, IllegalArgumentException, p0);
}
static jmethodID IllegalArgumentException_EC_2 = 0;
void jthrow_IllegalArgumentException_2(JNIEnv * env, jstring p0, jobject p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IllegalArgumentException, IllegalArgumentException_EC_2, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_IllegalArgumentException_2(JNIEnv * env, char* p0, jobject p1) {
    jthrowCC_IllegalArgumentException_2(env, (const char*)p0, p1);
}

void jthrowCC_IllegalArgumentException_2(JNIEnv * env, const char* p0, jobject p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[2];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    parameters[1].l = p1;
    jobject obj = (*env) -> NewObjectA(env, IllegalArgumentException, IllegalArgumentException_EC_2, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID IllegalArgumentException_EC_3 = 0;
void jthrow_IllegalArgumentException_3(JNIEnv * env, jobject p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IllegalArgumentException, IllegalArgumentException_EC_3, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID IllegalStateException_EC_0 = 0;
void jthrow_IllegalStateException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IllegalStateException, IllegalStateException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID IllegalStateException_EC_1 = 0;
void jthrow_IllegalStateException_1(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IllegalStateException, IllegalStateException_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_IllegalStateException_1(JNIEnv * env, char* p0) {
    jthrowCC_IllegalStateException_1(env, (const char*)p0);
}

void jthrowCC_IllegalStateException_1(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, IllegalStateException, p0);
}
static jmethodID IllegalStateException_EC_2 = 0;
void jthrow_IllegalStateException_2(JNIEnv * env, jstring p0, jobject p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IllegalStateException, IllegalStateException_EC_2, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_IllegalStateException_2(JNIEnv * env, char* p0, jobject p1) {
    jthrowCC_IllegalStateException_2(env, (const char*)p0, p1);
}

void jthrowCC_IllegalStateException_2(JNIEnv * env, const char* p0, jobject p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[2];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    parameters[1].l = p1;
    jobject obj = (*env) -> NewObjectA(env, IllegalStateException, IllegalStateException_EC_2, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID IllegalStateException_EC_3 = 0;
void jthrow_IllegalStateException_3(JNIEnv * env, jobject p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, IllegalStateException, IllegalStateException_EC_3, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID NullPointerException_EC_0 = 0;
void jthrow_NullPointerException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, NullPointerException, NullPointerException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID NullPointerException_EC_1 = 0;
void jthrow_NullPointerException_1(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, NullPointerException, NullPointerException_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_NullPointerException_1(JNIEnv * env, char* p0) {
    jthrowCC_NullPointerException_1(env, (const char*)p0);
}

void jthrowCC_NullPointerException_1(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, NullPointerException, p0);
}
static jmethodID OutOfMemoryError_EC_0 = 0;
void jthrow_OutOfMemoryError(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, OutOfMemoryError, OutOfMemoryError_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID OutOfMemoryError_EC_1 = 0;
void jthrow_OutOfMemoryError_1(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, OutOfMemoryError, OutOfMemoryError_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_OutOfMemoryError_1(JNIEnv * env, char* p0) {
    jthrowCC_OutOfMemoryError_1(env, (const char*)p0);
}

void jthrowCC_OutOfMemoryError_1(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, OutOfMemoryError, p0);
}
static jmethodID UnsupportedOperationException_EC_0 = 0;
void jthrow_UnsupportedOperationException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, UnsupportedOperationException, UnsupportedOperationException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID UnsupportedOperationException_EC_1 = 0;
void jthrow_UnsupportedOperationException_1(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, UnsupportedOperationException, UnsupportedOperationException_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_UnsupportedOperationException_1(JNIEnv * env, char* p0) {
    jthrowCC_UnsupportedOperationException_1(env, (const char*)p0);
}

void jthrowCC_UnsupportedOperationException_1(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, UnsupportedOperationException, p0);
}
static jmethodID UnsupportedOperationException_EC_2 = 0;
void jthrow_UnsupportedOperationException_2(JNIEnv * env, jstring p0, jobject p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, UnsupportedOperationException, UnsupportedOperationException_EC_2, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_UnsupportedOperationException_2(JNIEnv * env, char* p0, jobject p1) {
    jthrowCC_UnsupportedOperationException_2(env, (const char*)p0, p1);
}

void jthrowCC_UnsupportedOperationException_2(JNIEnv * env, const char* p0, jobject p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[2];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    parameters[1].l = p1;
    jobject obj = (*env) -> NewObjectA(env, UnsupportedOperationException, UnsupportedOperationException_EC_2, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID UnsupportedOperationException_EC_3 = 0;
void jthrow_UnsupportedOperationException_3(JNIEnv * env, jobject p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, UnsupportedOperationException, UnsupportedOperationException_EC_3, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID BindException_EC_0 = 0;
void jthrow_BindException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, BindException, BindException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID BindException_EC_1 = 0;
void jthrow_BindException_1(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, BindException, BindException_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_BindException_1(JNIEnv * env, char* p0) {
    jthrowCC_BindException_1(env, (const char*)p0);
}

void jthrowCC_BindException_1(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, BindException, p0);
}
static jmethodID ConnectException_EC_0 = 0;
void jthrow_ConnectException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, ConnectException, ConnectException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID ConnectException_EC_1 = 0;
void jthrow_ConnectException_1(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, ConnectException, ConnectException_EC_1, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_ConnectException_1(JNIEnv * env, char* p0) {
    jthrowCC_ConnectException_1(env, (const char*)p0);
}

void jthrowCC_ConnectException_1(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, ConnectException, p0);
}
static jmethodID AccessDeniedException_EC_0 = 0;
void jthrow_AccessDeniedException(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, AccessDeniedException, AccessDeniedException_EC_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_AccessDeniedException(JNIEnv * env, char* p0) {
    jthrowCC_AccessDeniedException(env, (const char*)p0);
}

void jthrowCC_AccessDeniedException(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, AccessDeniedException, p0);
}
static jmethodID AccessDeniedException_EC_1 = 0;
void jthrow_AccessDeniedException_1(JNIEnv * env, jstring p0, jstring p1, jstring p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, AccessDeniedException, AccessDeniedException_EC_1, p0, p1, p2);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_AccessDeniedException_1(JNIEnv * env, char* p0, char* p1, char* p2) {
    jthrowCC_AccessDeniedException_1(env, (const char*)p0, (const char*)p1, (const char*)p2);
}

void jthrowCC_AccessDeniedException_1(JNIEnv * env, const char* p0, const char* p1, const char* p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[3];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p1 == 0) {
        parameters[1].l = 0;
    } else {
        parameters[1].l = (*env) -> NewStringUTF(env, p1);
        if (parameters[1].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p2 == 0) {
        parameters[2].l = 0;
    } else {
        parameters[2].l = (*env) -> NewStringUTF(env, p2);
        if (parameters[2].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    jobject obj = (*env) -> NewObjectA(env, AccessDeniedException, AccessDeniedException_EC_1, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID FileAlreadyExistsException_EC_0 = 0;
void jthrow_FileAlreadyExistsException(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, FileAlreadyExistsException, FileAlreadyExistsException_EC_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_FileAlreadyExistsException(JNIEnv * env, char* p0) {
    jthrowCC_FileAlreadyExistsException(env, (const char*)p0);
}

void jthrowCC_FileAlreadyExistsException(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, FileAlreadyExistsException, p0);
}
static jmethodID FileAlreadyExistsException_EC_1 = 0;
void jthrow_FileAlreadyExistsException_1(JNIEnv * env, jstring p0, jstring p1, jstring p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, FileAlreadyExistsException, FileAlreadyExistsException_EC_1, p0, p1, p2);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_FileAlreadyExistsException_1(JNIEnv * env, char* p0, char* p1, char* p2) {
    jthrowCC_FileAlreadyExistsException_1(env, (const char*)p0, (const char*)p1, (const char*)p2);
}

void jthrowCC_FileAlreadyExistsException_1(JNIEnv * env, const char* p0, const char* p1, const char* p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[3];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p1 == 0) {
        parameters[1].l = 0;
    } else {
        parameters[1].l = (*env) -> NewStringUTF(env, p1);
        if (parameters[1].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p2 == 0) {
        parameters[2].l = 0;
    } else {
        parameters[2].l = (*env) -> NewStringUTF(env, p2);
        if (parameters[2].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    jobject obj = (*env) -> NewObjectA(env, FileAlreadyExistsException, FileAlreadyExistsException_EC_1, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID FileSystemLoopException_EC_0 = 0;
void jthrow_FileSystemLoopException(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, FileSystemLoopException, FileSystemLoopException_EC_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_FileSystemLoopException(JNIEnv * env, char* p0) {
    jthrowCC_FileSystemLoopException(env, (const char*)p0);
}

void jthrowCC_FileSystemLoopException(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, FileSystemLoopException, p0);
}
static jmethodID InvalidPathException_EC_0 = 0;
void jthrow_InvalidPathException(JNIEnv * env, jstring p0, jstring p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, InvalidPathException, InvalidPathException_EC_0, p0, p1);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_InvalidPathException(JNIEnv * env, char* p0, char* p1) {
    jthrowCC_InvalidPathException(env, (const char*)p0, (const char*)p1);
}

void jthrowCC_InvalidPathException(JNIEnv * env, const char* p0, const char* p1) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[2];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p1 == 0) {
        parameters[1].l = 0;
    } else {
        parameters[1].l = (*env) -> NewStringUTF(env, p1);
        if (parameters[1].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    jobject obj = (*env) -> NewObjectA(env, InvalidPathException, InvalidPathException_EC_0, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID InvalidPathException_EC_1 = 0;
void jthrow_InvalidPathException_1(JNIEnv * env, jstring p0, jstring p1, jint p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, InvalidPathException, InvalidPathException_EC_1, p0, p1, p2);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_InvalidPathException_1(JNIEnv * env, char* p0, char* p1, jint p2) {
    jthrowCC_InvalidPathException_1(env, (const char*)p0, (const char*)p1, p2);
}

void jthrowCC_InvalidPathException_1(JNIEnv * env, const char* p0, const char* p1, jint p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[3];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p1 == 0) {
        parameters[1].l = 0;
    } else {
        parameters[1].l = (*env) -> NewStringUTF(env, p1);
        if (parameters[1].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    parameters[2].i = p2;
    jobject obj = (*env) -> NewObjectA(env, InvalidPathException, InvalidPathException_EC_1, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID NotDirectoryException_EC_0 = 0;
void jthrow_NotDirectoryException(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, NotDirectoryException, NotDirectoryException_EC_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_NotDirectoryException(JNIEnv * env, char* p0) {
    jthrowCC_NotDirectoryException(env, (const char*)p0);
}

void jthrowCC_NotDirectoryException(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, NotDirectoryException, p0);
}
static jmethodID NotLinkException_EC_0 = 0;
void jthrow_NotLinkException(JNIEnv * env, jstring p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, NotLinkException, NotLinkException_EC_0, p0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_NotLinkException(JNIEnv * env, char* p0) {
    jthrowCC_NotLinkException(env, (const char*)p0);
}

void jthrowCC_NotLinkException(JNIEnv * env, const char* p0) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    (*env) -> ThrowNew(env, NotLinkException, p0);
}
static jmethodID NotLinkException_EC_1 = 0;
void jthrow_NotLinkException_1(JNIEnv * env, jstring p0, jstring p1, jstring p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, NotLinkException, NotLinkException_EC_1, p0, p1, p2);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}

void jthrowC_NotLinkException_1(JNIEnv * env, char* p0, char* p1, char* p2) {
    jthrowCC_NotLinkException_1(env, (const char*)p0, (const char*)p1, (const char*)p2);
}

void jthrowCC_NotLinkException_1(JNIEnv * env, const char* p0, const char* p1, const char* p2) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jvalue parameters[3];
    if (p0 == 0) {
        parameters[0].l = 0;
    } else {
        parameters[0].l = (*env) -> NewStringUTF(env, p0);
        if (parameters[0].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p1 == 0) {
        parameters[1].l = 0;
    } else {
        parameters[1].l = (*env) -> NewStringUTF(env, p1);
        if (parameters[1].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    if (p2 == 0) {
        parameters[2].l = 0;
    } else {
        parameters[2].l = (*env) -> NewStringUTF(env, p2);
        if (parameters[2].l == 0) {
            throw_internal_OutOfMemoryError(env, "NewStringUTF");
            return;
        }
    }
    jobject obj = (*env) -> NewObjectA(env, NotLinkException, NotLinkException_EC_1, (const jvalue*) parameters);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObjectA");
        return;
    }
    (*env)->Throw(env, obj);
}

static jmethodID ReadOnlyFileSystemException_EC_0 = 0;
void jthrow_ReadOnlyFileSystemException(JNIEnv * env) {
    if ((*env) -> ExceptionCheck(env)) {
        return;
    }
    jobject obj = (*env) -> NewObject(env, ReadOnlyFileSystemException, ReadOnlyFileSystemException_EC_0);
    if (obj == NULL) {
        throw_internal_OutOfMemoryError(env, "NewObject");
        return;
    }
    (*env)->Throw(env, obj);
}


jboolean jnigenerator_init(JNIEnv * env) {
    internal_Exception = makeGlobalClassRef(env, "java/lang/Exception");
    if (internal_Exception == 0) {
        return JNI_FALSE;
    }

    internal_OutOfMemoryError = makeGlobalClassRef(env, "java/lang/OutOfMemoryError");
    if (internal_OutOfMemoryError == 0) {
        return JNI_FALSE;
    }

    internal_IllegalArgumentException = makeGlobalClassRef(env, "java/lang/IllegalArgumentException");
    if (internal_IllegalArgumentException == 0) {
        return JNI_FALSE;
    }

    internal_NullPointerException = makeGlobalClassRef(env, "java/lang/NullPointerException");
    if (internal_NullPointerException == 0) {
        return JNI_FALSE;
    }
    internal_Enum = makeGlobalClassRef(env, "java/lang/Enum");
    if (internal_Enum == 0) {
        return JNI_FALSE;
    }

    internal_Enum_ordinal = (*env) ->GetMethodID(env, internal_Enum, "ordinal", "()I");
    if (internal_Enum_ordinal == 0) {
        return JNI_FALSE;
    }

    internal_Enum_name = (*env) ->GetMethodID(env, internal_Enum, "name", "()Ljava/lang/String;");
    if (internal_Enum_name == 0) {
        return JNI_FALSE;
    }

    IpAdapterAddresses = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses");
    if (IpAdapterAddresses == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses");
        return JNI_FALSE;
    }

    IllegalStateException = makeGlobalClassRef(env, "java/lang/IllegalStateException");
    if (IllegalStateException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalStateException");
        return JNI_FALSE;
    }

    Win32FileAttributeData = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData");
    if (Win32FileAttributeData == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress");
    if (IpAdapterAddresses$IpAdapterUnicastAddress == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress");
        return JNI_FALSE;
    }

    OperationInProgressException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/OperationInProgressException");
    if (OperationInProgressException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/OperationInProgressException");
        return JNI_FALSE;
    }

    PermissionDeniedException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/PermissionDeniedException");
    if (PermissionDeniedException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/PermissionDeniedException");
        return JNI_FALSE;
    }

    ShellExecuteException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/ShellExecuteException");
    if (ShellExecuteException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/ShellExecuteException");
        return JNI_FALSE;
    }

    GUID = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/GUID");
    if (GUID == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID");
        return JNI_FALSE;
    }

    BindException = makeGlobalClassRef(env, "java/net/BindException");
    if (BindException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/BindException");
        return JNI_FALSE;
    }

    Iterable = makeGlobalClassRef(env, "java/lang/Iterable");
    if (Iterable == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/Iterable");
        return JNI_FALSE;
    }

    NullPointerException = makeGlobalClassRef(env, "java/lang/NullPointerException");
    if (NullPointerException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/NullPointerException");
        return JNI_FALSE;
    }

    Utsname = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Utsname");
    if (Utsname == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname");
        return JNI_FALSE;
    }

    ArrayList = makeGlobalClassRef(env, "java/util/ArrayList");
    if (ArrayList == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList");
        return JNI_FALSE;
    }

    InetAddress = makeGlobalClassRef(env, "java/net/InetAddress");
    if (InetAddress == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress");
        return JNI_FALSE;
    }

    Cmsghdr = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr");
    if (Cmsghdr == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr");
        return JNI_FALSE;
    }

    InvalidPathException = makeGlobalClassRef(env, "java/nio/file/InvalidPathException");
    if (InvalidPathException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/InvalidPathException");
        return JNI_FALSE;
    }

    FileSystemLoopException = makeGlobalClassRef(env, "java/nio/file/FileSystemLoopException");
    if (FileSystemLoopException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/FileSystemLoopException");
        return JNI_FALSE;
    }

    UnknownNativeErrorException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/UnknownNativeErrorException");
    if (UnknownNativeErrorException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/UnknownNativeErrorException");
        return JNI_FALSE;
    }

    ConnectException = makeGlobalClassRef(env, "java/net/ConnectException");
    if (ConnectException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/ConnectException");
        return JNI_FALSE;
    }

    PollFD = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/PollFD");
    if (PollFD == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD");
        return JNI_FALSE;
    }

    UnsupportedOperationException = makeGlobalClassRef(env, "java/lang/UnsupportedOperationException");
    if (UnsupportedOperationException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/UnsupportedOperationException");
        return JNI_FALSE;
    }

    Stat = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Stat");
    if (Stat == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat");
        return JNI_FALSE;
    }

    Iterator = makeGlobalClassRef(env, "java/util/Iterator");
    if (Iterator == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Iterator");
        return JNI_FALSE;
    }

    NotDirectoryException = makeGlobalClassRef(env, "java/nio/file/NotDirectoryException");
    if (NotDirectoryException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/NotDirectoryException");
        return JNI_FALSE;
    }

    Collection = makeGlobalClassRef(env, "java/util/Collection");
    if (Collection == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection");
        return JNI_FALSE;
    }

    NotLinkException = makeGlobalClassRef(env, "java/nio/file/NotLinkException");
    if (NotLinkException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/NotLinkException");
        return JNI_FALSE;
    }

    Msghdr = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr");
    if (Msghdr == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr");
        return JNI_FALSE;
    }

    IOException = makeGlobalClassRef(env, "java/io/IOException");
    if (IOException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/io/IOException");
        return JNI_FALSE;
    }

    IllegalArgumentException = makeGlobalClassRef(env, "java/lang/IllegalArgumentException");
    if (IllegalArgumentException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalArgumentException");
        return JNI_FALSE;
    }

    FileAlreadyExistsException = makeGlobalClassRef(env, "java/nio/file/FileAlreadyExistsException");
    if (FileAlreadyExistsException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/FileAlreadyExistsException");
        return JNI_FALSE;
    }

    InetSocketAddress = makeGlobalClassRef(env, "java/net/InetSocketAddress");
    if (InetSocketAddress == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress");
        return JNI_FALSE;
    }

    FileNotFoundException = makeGlobalClassRef(env, "java/io/FileNotFoundException");
    if (FileNotFoundException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/io/FileNotFoundException");
        return JNI_FALSE;
    }

    Exception = makeGlobalClassRef(env, "java/lang/Exception");
    if (Exception == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/Exception");
        return JNI_FALSE;
    }

    QuotaExceededException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/QuotaExceededException");
    if (QuotaExceededException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/QuotaExceededException");
        return JNI_FALSE;
    }

    InvalidFileDescriptorException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/InvalidFileDescriptorException");
    if (InvalidFileDescriptorException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/InvalidFileDescriptorException");
        return JNI_FALSE;
    }

    PollFD$PollEvent = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent");
    if (PollFD$PollEvent == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent");
        return JNI_FALSE;
    }

    Iovec = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Iovec");
    if (Iovec == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec");
        return JNI_FALSE;
    }

    Sockaddr = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr");
    if (Sockaddr == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr");
        return JNI_FALSE;
    }

    MutexAbandonedException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/MutexAbandonedException");
    if (MutexAbandonedException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/MutexAbandonedException");
        return JNI_FALSE;
    }

    AccessDeniedException = makeGlobalClassRef(env, "java/nio/file/AccessDeniedException");
    if (AccessDeniedException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/AccessDeniedException");
        return JNI_FALSE;
    }

    ReadOnlyFileSystemException = makeGlobalClassRef(env, "java/nio/file/ReadOnlyFileSystemException");
    if (ReadOnlyFileSystemException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/ReadOnlyFileSystemException");
        return JNI_FALSE;
    }

    OutOfMemoryError = makeGlobalClassRef(env, "java/lang/OutOfMemoryError");
    if (OutOfMemoryError == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/OutOfMemoryError");
        return JNI_FALSE;
    }

    SharingViolationException = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException");
    if (SharingViolationException == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException");
        return JNI_FALSE;
    }

    Cmsghdr_cmsg_level = (*env) -> GetFieldID(env, Cmsghdr, "cmsg_level", "I");
    if (Cmsghdr_cmsg_level == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr_cmsg_level_I");
        return JNI_FALSE;
    }

    Cmsghdr_cmsg_type = (*env) -> GetFieldID(env, Cmsghdr, "cmsg_type", "I");
    if (Cmsghdr_cmsg_type == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr_cmsg_type_I");
        return JNI_FALSE;
    }

    Cmsghdr_payload = (*env) -> GetFieldID(env, Cmsghdr, "payload", "[B");
    if (Cmsghdr_payload == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr_payload_[B");
        return JNI_FALSE;
    }

    Cmsghdr_C_0 = (*env) -> GetMethodID(env, Cmsghdr, "<init>", "()V");
    if (Cmsghdr_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr.<init>()V");
        return JNI_FALSE;
    }

    Cmsghdr_M_getLevel_0 = (*env) -> GetMethodID(env, Cmsghdr, "getLevel", "()I");
    if (Cmsghdr_M_getLevel_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr.getLevel()I");
        return JNI_FALSE;
    }

    Cmsghdr_M_getPayload_0 = (*env) -> GetMethodID(env, Cmsghdr, "getPayload", "()[B");
    if (Cmsghdr_M_getPayload_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr.getPayload()[B");
        return JNI_FALSE;
    }

    Cmsghdr_M_getType_0 = (*env) -> GetMethodID(env, Cmsghdr, "getType", "()I");
    if (Cmsghdr_M_getType_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr.getType()I");
        return JNI_FALSE;
    }

    Cmsghdr_M_setPayload_0 = (*env) -> GetMethodID(env, Cmsghdr, "setPayload", "([B)V");
    if (Cmsghdr_M_setPayload_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Cmsghdr.setPayload([B)V");
        return JNI_FALSE;
    }

    GUID_data1 = (*env) -> GetFieldID(env, GUID, "data1", "I");
    if (GUID_data1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID_data1_I");
        return JNI_FALSE;
    }

    GUID_data2 = (*env) -> GetFieldID(env, GUID, "data2", "S");
    if (GUID_data2 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID_data2_S");
        return JNI_FALSE;
    }

    GUID_data3 = (*env) -> GetFieldID(env, GUID, "data3", "S");
    if (GUID_data3 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID_data3_S");
        return JNI_FALSE;
    }

    GUID_data4 = (*env) -> GetFieldID(env, GUID, "data4", "[B");
    if (GUID_data4 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID_data4_[B");
        return JNI_FALSE;
    }

    GUID_C_0 = (*env) -> GetMethodID(env, GUID, "<init>", "()V");
    if (GUID_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.<init>()V");
        return JNI_FALSE;
    }

    GUID_C_1 = (*env) -> GetMethodID(env, GUID, "<init>", "(Ljava/lang/String;)V");
    if (GUID_C_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    GUID_M_clone_0 = (*env) -> GetMethodID(env, GUID, "clone", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
    if (GUID_M_clone_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.clone()Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
        return JNI_FALSE;
    }

    GUID_M_getData1_0 = (*env) -> GetMethodID(env, GUID, "getData1", "()I");
    if (GUID_M_getData1_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.getData1()I");
        return JNI_FALSE;
    }

    GUID_M_getData2_0 = (*env) -> GetMethodID(env, GUID, "getData2", "()S");
    if (GUID_M_getData2_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.getData2()S");
        return JNI_FALSE;
    }

    GUID_M_getData3_0 = (*env) -> GetMethodID(env, GUID, "getData3", "()S");
    if (GUID_M_getData3_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.getData3()S");
        return JNI_FALSE;
    }

    GUID_M_getData4_0 = (*env) -> GetMethodID(env, GUID, "getData4", "()[B");
    if (GUID_M_getData4_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.getData4()[B");
        return JNI_FALSE;
    }

    GUID_M_setData1_0 = (*env) -> GetMethodID(env, GUID, "setData1", "(I)V");
    if (GUID_M_setData1_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.setData1(I)V");
        return JNI_FALSE;
    }

    GUID_M_setData2_0 = (*env) -> GetMethodID(env, GUID, "setData2", "(S)V");
    if (GUID_M_setData2_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.setData2(S)V");
        return JNI_FALSE;
    }

    GUID_M_setData3_0 = (*env) -> GetMethodID(env, GUID, "setData3", "(S)V");
    if (GUID_M_setData3_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.setData3(S)V");
        return JNI_FALSE;
    }

    GUID_M_setData4_0 = (*env) -> GetMethodID(env, GUID, "setData4", "([B)V");
    if (GUID_M_setData4_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.setData4([B)V");
        return JNI_FALSE;
    }

    GUID_M_toString_0 = (*env) -> GetMethodID(env, GUID, "toString", "()Ljava/lang/String;");
    if (GUID_M_toString_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.toString()Ljava/lang/String;");
        return JNI_FALSE;
    }

    Iovec_payload = (*env) -> GetFieldID(env, Iovec, "payload", "[B");
    if (Iovec_payload == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec_payload_[B");
        return JNI_FALSE;
    }

    Iovec_off = (*env) -> GetFieldID(env, Iovec, "off", "I");
    if (Iovec_off == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec_off_I");
        return JNI_FALSE;
    }

    Iovec_len = (*env) -> GetFieldID(env, Iovec, "len", "I");
    if (Iovec_len == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec_len_I");
        return JNI_FALSE;
    }

    Iovec_size = (*env) -> GetFieldID(env, Iovec, "size", "I");
    if (Iovec_size == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec_size_I");
        return JNI_FALSE;
    }

    Iovec_C_0 = (*env) -> GetMethodID(env, Iovec, "<init>", "(I)V");
    if (Iovec_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec.<init>(I)V");
        return JNI_FALSE;
    }

    Iovec_C_1 = (*env) -> GetMethodID(env, Iovec, "<init>", "([B)V");
    if (Iovec_C_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec.<init>([B)V");
        return JNI_FALSE;
    }

    Iovec_C_2 = (*env) -> GetMethodID(env, Iovec, "<init>", "([BII)V");
    if (Iovec_C_2 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec.<init>([BII)V");
        return JNI_FALSE;
    }

    Iovec_M_getLen_0 = (*env) -> GetMethodID(env, Iovec, "getLen", "()I");
    if (Iovec_M_getLen_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec.getLen()I");
        return JNI_FALSE;
    }

    Iovec_M_getOff_0 = (*env) -> GetMethodID(env, Iovec, "getOff", "()I");
    if (Iovec_M_getOff_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec.getOff()I");
        return JNI_FALSE;
    }

    Iovec_M_getPayload_0 = (*env) -> GetMethodID(env, Iovec, "getPayload", "()[B");
    if (Iovec_M_getPayload_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec.getPayload()[B");
        return JNI_FALSE;
    }

    Iovec_M_getSize_0 = (*env) -> GetMethodID(env, Iovec, "getSize", "()I");
    if (Iovec_M_getSize_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Iovec.getSize()I");
        return JNI_FALSE;
    }

    IpAdapterAddresses_AdapterName = (*env) -> GetFieldID(env, IpAdapterAddresses, "AdapterName", "Ljava/lang/String;");
    if (IpAdapterAddresses_AdapterName == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_AdapterName_Ljava/lang/String;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_UnicastAddress = (*env) -> GetFieldID(env, IpAdapterAddresses, "UnicastAddress", "Ljava/util/List;");
    if (IpAdapterAddresses_UnicastAddress == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_UnicastAddress_Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_AnycastAddress = (*env) -> GetFieldID(env, IpAdapterAddresses, "AnycastAddress", "Ljava/util/List;");
    if (IpAdapterAddresses_AnycastAddress == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_AnycastAddress_Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_MulticastAddress = (*env) -> GetFieldID(env, IpAdapterAddresses, "MulticastAddress", "Ljava/util/List;");
    if (IpAdapterAddresses_MulticastAddress == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_MulticastAddress_Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_DnsServerAddress = (*env) -> GetFieldID(env, IpAdapterAddresses, "DnsServerAddress", "Ljava/util/List;");
    if (IpAdapterAddresses_DnsServerAddress == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_DnsServerAddress_Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_DnsSuffix = (*env) -> GetFieldID(env, IpAdapterAddresses, "DnsSuffix", "Ljava/lang/String;");
    if (IpAdapterAddresses_DnsSuffix == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_DnsSuffix_Ljava/lang/String;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Description = (*env) -> GetFieldID(env, IpAdapterAddresses, "Description", "Ljava/lang/String;");
    if (IpAdapterAddresses_Description == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Description_Ljava/lang/String;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_FriendlyName = (*env) -> GetFieldID(env, IpAdapterAddresses, "FriendlyName", "Ljava/lang/String;");
    if (IpAdapterAddresses_FriendlyName == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_FriendlyName_Ljava/lang/String;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_PhysicalAddress = (*env) -> GetFieldID(env, IpAdapterAddresses, "PhysicalAddress", "[B");
    if (IpAdapterAddresses_PhysicalAddress == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_PhysicalAddress_[B");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Mtu = (*env) -> GetFieldID(env, IpAdapterAddresses, "Mtu", "J");
    if (IpAdapterAddresses_Mtu == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Mtu_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_IfType = (*env) -> GetFieldID(env, IpAdapterAddresses, "IfType", "J");
    if (IpAdapterAddresses_IfType == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_IfType_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_OperStatus = (*env) -> GetFieldID(env, IpAdapterAddresses, "OperStatus", "I");
    if (IpAdapterAddresses_OperStatus == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_OperStatus_I");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Ipv6IfIndex = (*env) -> GetFieldID(env, IpAdapterAddresses, "Ipv6IfIndex", "J");
    if (IpAdapterAddresses_Ipv6IfIndex == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Ipv6IfIndex_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_ZoneIndices = (*env) -> GetFieldID(env, IpAdapterAddresses, "ZoneIndices", "[J");
    if (IpAdapterAddresses_ZoneIndices == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_ZoneIndices_[J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Prefix = (*env) -> GetFieldID(env, IpAdapterAddresses, "Prefix", "Ljava/util/List;");
    if (IpAdapterAddresses_Prefix == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Prefix_Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_TransmitLinkSpeed = (*env) -> GetFieldID(env, IpAdapterAddresses, "TransmitLinkSpeed", "J");
    if (IpAdapterAddresses_TransmitLinkSpeed == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_TransmitLinkSpeed_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_ReceiveLinkSpeed = (*env) -> GetFieldID(env, IpAdapterAddresses, "ReceiveLinkSpeed", "J");
    if (IpAdapterAddresses_ReceiveLinkSpeed == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_ReceiveLinkSpeed_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_WinsServerAddress = (*env) -> GetFieldID(env, IpAdapterAddresses, "WinsServerAddress", "Ljava/util/List;");
    if (IpAdapterAddresses_WinsServerAddress == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_WinsServerAddress_Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_GatewayAddress = (*env) -> GetFieldID(env, IpAdapterAddresses, "GatewayAddress", "Ljava/util/List;");
    if (IpAdapterAddresses_GatewayAddress == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_GatewayAddress_Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Ipv4Metric = (*env) -> GetFieldID(env, IpAdapterAddresses, "Ipv4Metric", "J");
    if (IpAdapterAddresses_Ipv4Metric == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Ipv4Metric_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Ipv6Metric = (*env) -> GetFieldID(env, IpAdapterAddresses, "Ipv6Metric", "J");
    if (IpAdapterAddresses_Ipv6Metric == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Ipv6Metric_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Luid_Value = (*env) -> GetFieldID(env, IpAdapterAddresses, "Luid_Value", "J");
    if (IpAdapterAddresses_Luid_Value == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Luid_Value_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Luid_NetLuidIndex = (*env) -> GetFieldID(env, IpAdapterAddresses, "Luid_NetLuidIndex", "J");
    if (IpAdapterAddresses_Luid_NetLuidIndex == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Luid_NetLuidIndex_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Luid_IfType = (*env) -> GetFieldID(env, IpAdapterAddresses, "Luid_IfType", "J");
    if (IpAdapterAddresses_Luid_IfType == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Luid_IfType_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Dhcpv4Server = (*env) -> GetFieldID(env, IpAdapterAddresses, "Dhcpv4Server", "Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (IpAdapterAddresses_Dhcpv4Server == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Dhcpv4Server_Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_CompartmentId = (*env) -> GetFieldID(env, IpAdapterAddresses, "CompartmentId", "J");
    if (IpAdapterAddresses_CompartmentId == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_CompartmentId_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_NetworkGuid = (*env) -> GetFieldID(env, IpAdapterAddresses, "NetworkGuid", "Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
    if (IpAdapterAddresses_NetworkGuid == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_NetworkGuid_Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_ConnectionType = (*env) -> GetFieldID(env, IpAdapterAddresses, "ConnectionType", "I");
    if (IpAdapterAddresses_ConnectionType == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_ConnectionType_I");
        return JNI_FALSE;
    }

    IpAdapterAddresses_TunnelType = (*env) -> GetFieldID(env, IpAdapterAddresses, "TunnelType", "I");
    if (IpAdapterAddresses_TunnelType == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_TunnelType_I");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Dhcpv6Server = (*env) -> GetFieldID(env, IpAdapterAddresses, "Dhcpv6Server", "Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (IpAdapterAddresses_Dhcpv6Server == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Dhcpv6Server_Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Dhcpv6ClientDuid = (*env) -> GetFieldID(env, IpAdapterAddresses, "Dhcpv6ClientDuid", "[B");
    if (IpAdapterAddresses_Dhcpv6ClientDuid == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Dhcpv6ClientDuid_[B");
        return JNI_FALSE;
    }

    IpAdapterAddresses_Dhcpv6Iaid = (*env) -> GetFieldID(env, IpAdapterAddresses, "Dhcpv6Iaid", "J");
    if (IpAdapterAddresses_Dhcpv6Iaid == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses_Dhcpv6Iaid_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_C_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "<init>", "()V");
    if (IpAdapterAddresses_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.<init>()V");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getAdapterName_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getAdapterName", "()Ljava/lang/String;");
    if (IpAdapterAddresses_M_getAdapterName_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getAdapterName()Ljava/lang/String;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getAnycastAddress_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getAnycastAddress", "()Ljava/util/List;");
    if (IpAdapterAddresses_M_getAnycastAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getAnycastAddress()Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getCompartmentId_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getCompartmentId", "()J");
    if (IpAdapterAddresses_M_getCompartmentId_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getCompartmentId()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getConnectionType_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getConnectionType", "()I");
    if (IpAdapterAddresses_M_getConnectionType_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getConnectionType()I");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getDescription_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getDescription", "()Ljava/lang/String;");
    if (IpAdapterAddresses_M_getDescription_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getDescription()Ljava/lang/String;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getDhcpv4Server_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getDhcpv4Server", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (IpAdapterAddresses_M_getDhcpv4Server_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getDhcpv4Server()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getDhcpv6ClientDuid_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getDhcpv6ClientDuid", "()[B");
    if (IpAdapterAddresses_M_getDhcpv6ClientDuid_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getDhcpv6ClientDuid()[B");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getDhcpv6Iaid_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getDhcpv6Iaid", "()J");
    if (IpAdapterAddresses_M_getDhcpv6Iaid_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getDhcpv6Iaid()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getDhcpv6Server_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getDhcpv6Server", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (IpAdapterAddresses_M_getDhcpv6Server_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getDhcpv6Server()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getDnsServerAddress_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getDnsServerAddress", "()Ljava/util/List;");
    if (IpAdapterAddresses_M_getDnsServerAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getDnsServerAddress()Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getDnsSuffix_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getDnsSuffix", "()Ljava/lang/String;");
    if (IpAdapterAddresses_M_getDnsSuffix_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getDnsSuffix()Ljava/lang/String;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getFriendlyName_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getFriendlyName", "()Ljava/lang/String;");
    if (IpAdapterAddresses_M_getFriendlyName_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getFriendlyName()Ljava/lang/String;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getGatewayAddress_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getGatewayAddress", "()Ljava/util/List;");
    if (IpAdapterAddresses_M_getGatewayAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getGatewayAddress()Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getIfType_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getIfType", "()J");
    if (IpAdapterAddresses_M_getIfType_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getIfType()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getIpv4Metric_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getIpv4Metric", "()J");
    if (IpAdapterAddresses_M_getIpv4Metric_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getIpv4Metric()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getIpv6IfIndex_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getIpv6IfIndex", "()J");
    if (IpAdapterAddresses_M_getIpv6IfIndex_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getIpv6IfIndex()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getIpv6Metric_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getIpv6Metric", "()J");
    if (IpAdapterAddresses_M_getIpv6Metric_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getIpv6Metric()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getLuid_IfType_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getLuid_IfType", "()J");
    if (IpAdapterAddresses_M_getLuid_IfType_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getLuid_IfType()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getLuid_NetLuidIndex_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getLuid_NetLuidIndex", "()J");
    if (IpAdapterAddresses_M_getLuid_NetLuidIndex_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getLuid_NetLuidIndex()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getLuid_Value_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getLuid_Value", "()J");
    if (IpAdapterAddresses_M_getLuid_Value_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getLuid_Value()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getMtu_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getMtu", "()J");
    if (IpAdapterAddresses_M_getMtu_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getMtu()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getMulticastAddress_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getMulticastAddress", "()Ljava/util/List;");
    if (IpAdapterAddresses_M_getMulticastAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getMulticastAddress()Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getNetworkGuid_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getNetworkGuid", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
    if (IpAdapterAddresses_M_getNetworkGuid_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getNetworkGuid()Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getOperStatus_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getOperStatus", "()I");
    if (IpAdapterAddresses_M_getOperStatus_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getOperStatus()I");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getPhysicalAddress_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getPhysicalAddress", "()[B");
    if (IpAdapterAddresses_M_getPhysicalAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getPhysicalAddress()[B");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getPrefix_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getPrefix", "()Ljava/util/List;");
    if (IpAdapterAddresses_M_getPrefix_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getPrefix()Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getReceiveLinkSpeed_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getReceiveLinkSpeed", "()J");
    if (IpAdapterAddresses_M_getReceiveLinkSpeed_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getReceiveLinkSpeed()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getTransmitLinkSpeed_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getTransmitLinkSpeed", "()J");
    if (IpAdapterAddresses_M_getTransmitLinkSpeed_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getTransmitLinkSpeed()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getTunnelType_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getTunnelType", "()I");
    if (IpAdapterAddresses_M_getTunnelType_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getTunnelType()I");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getUnicastAddress_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getUnicastAddress", "()Ljava/util/List;");
    if (IpAdapterAddresses_M_getUnicastAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getUnicastAddress()Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getWinsServerAddress_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getWinsServerAddress", "()Ljava/util/List;");
    if (IpAdapterAddresses_M_getWinsServerAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getWinsServerAddress()Ljava/util/List;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getZoneIndices_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getZoneIndices", "()[J");
    if (IpAdapterAddresses_M_getZoneIndices_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getZoneIndices()[J");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_Address = (*env) -> GetFieldID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "Address", "Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_Address == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress_Address_Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin = (*env) -> GetFieldID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "PrefixOrigin", "I");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin_I");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin = (*env) -> GetFieldID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "SuffixOrigin", "I");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin_I");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_DadState = (*env) -> GetFieldID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "DadState", "I");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_DadState == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress_DadState_I");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime = (*env) -> GetFieldID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "ValidLifetime", "J");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime = (*env) -> GetFieldID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "PreferredLifetime", "J");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime = (*env) -> GetFieldID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "LeaseLifetime", "J");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime_J");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength = (*env) -> GetFieldID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "OnLinkPrefixLength", "I");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength_I");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_C_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "<init>", "()V");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.<init>()V");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_M_getAddress_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "getAddress", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_M_getAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.getAddress()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_M_getDadState_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "getDadState", "()I");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_M_getDadState_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.getDadState()I");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_M_getLeaseLifetime_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "getLeaseLifetime", "()J");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_M_getLeaseLifetime_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.getLeaseLifetime()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_M_getOnLinkPrefixLength_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "getOnLinkPrefixLength", "()I");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_M_getOnLinkPrefixLength_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.getOnLinkPrefixLength()I");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_M_getPreferredLifetime_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "getPreferredLifetime", "()J");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_M_getPreferredLifetime_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.getPreferredLifetime()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_M_getPrefixOrigin_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "getPrefixOrigin", "()I");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_M_getPrefixOrigin_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.getPrefixOrigin()I");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_M_getSuffixOrigin_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "getSuffixOrigin", "()I");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_M_getSuffixOrigin_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.getSuffixOrigin()I");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_M_getValidLifetime_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "getValidLifetime", "()J");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_M_getValidLifetime_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.getValidLifetime()J");
        return JNI_FALSE;
    }

    Msghdr_msg_iov = (*env) -> GetFieldID(env, Msghdr, "msg_iov", "[Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;");
    if (Msghdr_msg_iov == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr_msg_iov_[Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;");
        return JNI_FALSE;
    }

    Msghdr_msg_control = (*env) -> GetFieldID(env, Msghdr, "msg_control", "[B");
    if (Msghdr_msg_control == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr_msg_control_[B");
        return JNI_FALSE;
    }

    Msghdr_msg_name = (*env) -> GetFieldID(env, Msghdr, "msg_name", "Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (Msghdr_msg_name == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr_msg_name_Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
        return JNI_FALSE;
    }

    Msghdr_complete = (*env) -> GetFieldID(env, Msghdr, "complete", "Z");
    if (Msghdr_complete == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr_complete_Z");
        return JNI_FALSE;
    }

    Msghdr_truncated = (*env) -> GetFieldID(env, Msghdr, "truncated", "Z");
    if (Msghdr_truncated == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr_truncated_Z");
        return JNI_FALSE;
    }

    Msghdr_controlDataTruncated = (*env) -> GetFieldID(env, Msghdr, "controlDataTruncated", "Z");
    if (Msghdr_controlDataTruncated == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr_controlDataTruncated_Z");
        return JNI_FALSE;
    }

    Msghdr_outOfBand = (*env) -> GetFieldID(env, Msghdr, "outOfBand", "Z");
    if (Msghdr_outOfBand == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr_outOfBand_Z");
        return JNI_FALSE;
    }

    Msghdr_errQueue = (*env) -> GetFieldID(env, Msghdr, "errQueue", "Z");
    if (Msghdr_errQueue == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr_errQueue_Z");
        return JNI_FALSE;
    }

    Msghdr_msg_controllen = (*env) -> GetFieldID(env, Msghdr, "msg_controllen", "I");
    if (Msghdr_msg_controllen == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr_msg_controllen_I");
        return JNI_FALSE;
    }

    Msghdr_C_0 = (*env) -> GetMethodID(env, Msghdr, "<init>", "(Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;)V");
    if (Msghdr_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.<init>(Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;)V");
        return JNI_FALSE;
    }

    Msghdr_C_1 = (*env) -> GetMethodID(env, Msghdr, "<init>", "(Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;[B)V");
    if (Msghdr_C_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.<init>(Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;[B)V");
        return JNI_FALSE;
    }

    Msghdr_C_2 = (*env) -> GetMethodID(env, Msghdr, "<init>", "([BII)V");
    if (Msghdr_C_2 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.<init>([BII)V");
        return JNI_FALSE;
    }

    Msghdr_C_3 = (*env) -> GetMethodID(env, Msghdr, "<init>", "([Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;)V");
    if (Msghdr_C_3 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.<init>([Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;)V");
        return JNI_FALSE;
    }

    Msghdr_C_4 = (*env) -> GetMethodID(env, Msghdr, "<init>", "([Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)V");
    if (Msghdr_C_4 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.<init>([Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)V");
        return JNI_FALSE;
    }

    Msghdr_C_5 = (*env) -> GetMethodID(env, Msghdr, "<init>", "([Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;[B)V");
    if (Msghdr_C_5 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.<init>([Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;[B)V");
        return JNI_FALSE;
    }

    Msghdr_C_6 = (*env) -> GetMethodID(env, Msghdr, "<init>", "([Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;[B)V");
    if (Msghdr_C_6 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.<init>([Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;[B)V");
        return JNI_FALSE;
    }

    Msghdr_M_getMsg_control_0 = (*env) -> GetMethodID(env, Msghdr, "getMsg_control", "()[B");
    if (Msghdr_M_getMsg_control_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.getMsg_control()[B");
        return JNI_FALSE;
    }

    Msghdr_M_getMsg_controllen_0 = (*env) -> GetMethodID(env, Msghdr, "getMsg_controllen", "()I");
    if (Msghdr_M_getMsg_controllen_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.getMsg_controllen()I");
        return JNI_FALSE;
    }

    Msghdr_M_getMsg_iov_0 = (*env) -> GetMethodID(env, Msghdr, "getMsg_iov", "()[Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;");
    if (Msghdr_M_getMsg_iov_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.getMsg_iov()[Lio/github/alexanderschuetz97/nativeutils/api/structs/Iovec;");
        return JNI_FALSE;
    }

    Msghdr_M_getMsg_name_0 = (*env) -> GetMethodID(env, Msghdr, "getMsg_name", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (Msghdr_M_getMsg_name_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.getMsg_name()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
        return JNI_FALSE;
    }

    Msghdr_M_isComplete_0 = (*env) -> GetMethodID(env, Msghdr, "isComplete", "()Z");
    if (Msghdr_M_isComplete_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.isComplete()Z");
        return JNI_FALSE;
    }

    Msghdr_M_isControlDataTruncated_0 = (*env) -> GetMethodID(env, Msghdr, "isControlDataTruncated", "()Z");
    if (Msghdr_M_isControlDataTruncated_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.isControlDataTruncated()Z");
        return JNI_FALSE;
    }

    Msghdr_M_isErrQueue_0 = (*env) -> GetMethodID(env, Msghdr, "isErrQueue", "()Z");
    if (Msghdr_M_isErrQueue_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.isErrQueue()Z");
        return JNI_FALSE;
    }

    Msghdr_M_isOutOfBand_0 = (*env) -> GetMethodID(env, Msghdr, "isOutOfBand", "()Z");
    if (Msghdr_M_isOutOfBand_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.isOutOfBand()Z");
        return JNI_FALSE;
    }

    Msghdr_M_isTruncated_0 = (*env) -> GetMethodID(env, Msghdr, "isTruncated", "()Z");
    if (Msghdr_M_isTruncated_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Msghdr.isTruncated()Z");
        return JNI_FALSE;
    }

    PollFD_fd = (*env) -> GetFieldID(env, PollFD, "fd", "I");
    if (PollFD_fd == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD_fd_I");
        return JNI_FALSE;
    }

    PollFD_events = (*env) -> GetFieldID(env, PollFD, "events", "Ljava/util/EnumSet;");
    if (PollFD_events == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD_events_Ljava/util/EnumSet;");
        return JNI_FALSE;
    }

    PollFD_revents = (*env) -> GetFieldID(env, PollFD, "revents", "Ljava/util/EnumSet;");
    if (PollFD_revents == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD_revents_Ljava/util/EnumSet;");
        return JNI_FALSE;
    }

    PollFD_C_0 = (*env) -> GetMethodID(env, PollFD, "<init>", "(ILjava/util/EnumSet;)V");
    if (PollFD_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD.<init>(ILjava/util/EnumSet;)V");
        return JNI_FALSE;
    }

    PollFD_M_getEvents_0 = (*env) -> GetMethodID(env, PollFD, "getEvents", "()Ljava/util/EnumSet;");
    if (PollFD_M_getEvents_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD.getEvents()Ljava/util/EnumSet;");
        return JNI_FALSE;
    }

    PollFD_M_getFd_0 = (*env) -> GetMethodID(env, PollFD, "getFd", "()I");
    if (PollFD_M_getFd_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD.getFd()I");
        return JNI_FALSE;
    }

    PollFD_M_getREvents_0 = (*env) -> GetMethodID(env, PollFD, "getREvents", "()Ljava/util/EnumSet;");
    if (PollFD_M_getREvents_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD.getREvents()Ljava/util/EnumSet;");
        return JNI_FALSE;
    }

    PollFD_M_test_0 = (*env) -> GetMethodID(env, PollFD, "test", "(Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;)Z");
    if (PollFD_M_test_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD.test(Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;)Z");
        return JNI_FALSE;
    }

    PollFD$PollEvent_POLLIN = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLIN = 0;
    enum_field_init_PollFD$PollEvent_POLLIN = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLIN", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLIN == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLIN_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLIN = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLIN);
    if (PollFD$PollEvent_POLLIN == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLIN_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLPRI = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLPRI = 0;
    enum_field_init_PollFD$PollEvent_POLLPRI = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLPRI", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLPRI == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLPRI_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLPRI = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLPRI);
    if (PollFD$PollEvent_POLLPRI == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLPRI_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLOUT = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLOUT = 0;
    enum_field_init_PollFD$PollEvent_POLLOUT = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLOUT", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLOUT == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLOUT_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLOUT = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLOUT);
    if (PollFD$PollEvent_POLLOUT == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLOUT_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLRDNORM = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLRDNORM = 0;
    enum_field_init_PollFD$PollEvent_POLLRDNORM = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLRDNORM", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLRDNORM == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLRDNORM_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLRDNORM = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLRDNORM);
    if (PollFD$PollEvent_POLLRDNORM == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLRDNORM_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLRDBAND = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLRDBAND = 0;
    enum_field_init_PollFD$PollEvent_POLLRDBAND = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLRDBAND", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLRDBAND == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLRDBAND_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLRDBAND = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLRDBAND);
    if (PollFD$PollEvent_POLLRDBAND == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLRDBAND_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLWRNORM = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLWRNORM = 0;
    enum_field_init_PollFD$PollEvent_POLLWRNORM = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLWRNORM", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLWRNORM == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLWRNORM_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLWRNORM = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLWRNORM);
    if (PollFD$PollEvent_POLLWRNORM == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLWRNORM_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLWRBAND = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLWRBAND = 0;
    enum_field_init_PollFD$PollEvent_POLLWRBAND = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLWRBAND", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLWRBAND == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLWRBAND_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLWRBAND = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLWRBAND);
    if (PollFD$PollEvent_POLLWRBAND == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLWRBAND_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLMSG = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLMSG = 0;
    enum_field_init_PollFD$PollEvent_POLLMSG = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLMSG", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLMSG == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLMSG_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLMSG = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLMSG);
    if (PollFD$PollEvent_POLLMSG == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLMSG_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLREMOVE = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLREMOVE = 0;
    enum_field_init_PollFD$PollEvent_POLLREMOVE = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLREMOVE", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLREMOVE == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLREMOVE_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLREMOVE = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLREMOVE);
    if (PollFD$PollEvent_POLLREMOVE == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLREMOVE_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLRDHUP = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLRDHUP = 0;
    enum_field_init_PollFD$PollEvent_POLLRDHUP = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLRDHUP", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLRDHUP == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLRDHUP_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLRDHUP = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLRDHUP);
    if (PollFD$PollEvent_POLLRDHUP == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLRDHUP_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLERR = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLERR = 0;
    enum_field_init_PollFD$PollEvent_POLLERR = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLERR", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLERR == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLERR_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLERR = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLERR);
    if (PollFD$PollEvent_POLLERR == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLERR_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLHUP = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLHUP = 0;
    enum_field_init_PollFD$PollEvent_POLLHUP = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLHUP", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLHUP == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLHUP_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLHUP = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLHUP);
    if (PollFD$PollEvent_POLLHUP == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLHUP_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_POLLNVAL = 0;
    jfieldID enum_field_init_PollFD$PollEvent_POLLNVAL = 0;
    enum_field_init_PollFD$PollEvent_POLLNVAL = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "POLLNVAL", "Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (enum_field_init_PollFD$PollEvent_POLLNVAL == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLNVAL_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    PollFD$PollEvent_POLLNVAL = (*env) -> GetStaticObjectField(env, PollFD$PollEvent, enum_field_init_PollFD$PollEvent_POLLNVAL);
    if (PollFD$PollEvent_POLLNVAL == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant get enum value of io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_POLLNVAL_Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }
    
    PollFD$PollEvent_$VALUES = (*env) -> GetStaticFieldID(env, PollFD$PollEvent, "$VALUES", "[Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
    if (PollFD$PollEvent_$VALUES == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent_$VALUES_[Lio/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent;");
        return JNI_FALSE;
    }

    for (int i = 0; i < 13; i++) {
        PollFD$PollEvent_enum_values[i] = 0;
    }
    PollFD$PollEvent_enum_values[0] = PollFD$PollEvent_POLLIN;
    PollFD$PollEvent_enum_values[1] = PollFD$PollEvent_POLLPRI;
    PollFD$PollEvent_enum_values[2] = PollFD$PollEvent_POLLOUT;
    PollFD$PollEvent_enum_values[3] = PollFD$PollEvent_POLLRDNORM;
    PollFD$PollEvent_enum_values[4] = PollFD$PollEvent_POLLRDBAND;
    PollFD$PollEvent_enum_values[5] = PollFD$PollEvent_POLLWRNORM;
    PollFD$PollEvent_enum_values[6] = PollFD$PollEvent_POLLWRBAND;
    PollFD$PollEvent_enum_values[7] = PollFD$PollEvent_POLLMSG;
    PollFD$PollEvent_enum_values[8] = PollFD$PollEvent_POLLREMOVE;
    PollFD$PollEvent_enum_values[9] = PollFD$PollEvent_POLLRDHUP;
    PollFD$PollEvent_enum_values[10] = PollFD$PollEvent_POLLERR;
    PollFD$PollEvent_enum_values[11] = PollFD$PollEvent_POLLHUP;
    PollFD$PollEvent_enum_values[12] = PollFD$PollEvent_POLLNVAL;
    PollFD$PollEvent_C_0 = (*env) -> GetMethodID(env, PollFD$PollEvent, "<init>", "(Ljava/lang/String;I)V");
    if (PollFD$PollEvent_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/PollFD$PollEvent.<init>(Ljava/lang/String;I)V");
        return JNI_FALSE;
    }

    Sockaddr_EMPTY = (*env) -> GetStaticFieldID(env, Sockaddr, "EMPTY", "[B");
    if (Sockaddr_EMPTY == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr_EMPTY_[B");
        return JNI_FALSE;
    }

    Sockaddr_addressFamily = (*env) -> GetFieldID(env, Sockaddr, "addressFamily", "I");
    if (Sockaddr_addressFamily == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr_addressFamily_I");
        return JNI_FALSE;
    }

    Sockaddr_address = (*env) -> GetFieldID(env, Sockaddr, "address", "[B");
    if (Sockaddr_address == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr_address_[B");
        return JNI_FALSE;
    }

    Sockaddr_C_0 = (*env) -> GetMethodID(env, Sockaddr, "<init>", "()V");
    if (Sockaddr_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.<init>()V");
        return JNI_FALSE;
    }

    Sockaddr_C_1 = (*env) -> GetMethodID(env, Sockaddr, "<init>", "(I[B)V");
    if (Sockaddr_C_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.<init>(I[B)V");
        return JNI_FALSE;
    }

    Sockaddr_C_2 = (*env) -> GetMethodID(env, Sockaddr, "<init>", "(Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)V");
    if (Sockaddr_C_2 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.<init>(Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)V");
        return JNI_FALSE;
    }

    Sockaddr_M_clone_0 = (*env) -> GetMethodID(env, Sockaddr, "clone", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (Sockaddr_M_clone_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.clone()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
        return JNI_FALSE;
    }

    Sockaddr_M_copyTo_0 = (*env) -> GetMethodID(env, Sockaddr, "copyTo", "(Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)V");
    if (Sockaddr_M_copyTo_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.copyTo(Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)V");
        return JNI_FALSE;
    }

    Sockaddr_M_getAddress_0 = (*env) -> GetMethodID(env, Sockaddr, "getAddress", "()[B");
    if (Sockaddr_M_getAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.getAddress()[B");
        return JNI_FALSE;
    }

    Sockaddr_M_getAddressFamily_0 = (*env) -> GetMethodID(env, Sockaddr, "getAddressFamily", "()I");
    if (Sockaddr_M_getAddressFamily_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.getAddressFamily()I");
        return JNI_FALSE;
    }

    Stat_dev = (*env) -> GetFieldID(env, Stat, "dev", "J");
    if (Stat_dev == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_dev_J");
        return JNI_FALSE;
    }

    Stat_ino = (*env) -> GetFieldID(env, Stat, "ino", "J");
    if (Stat_ino == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_ino_J");
        return JNI_FALSE;
    }

    Stat_mode = (*env) -> GetFieldID(env, Stat, "mode", "J");
    if (Stat_mode == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_mode_J");
        return JNI_FALSE;
    }

    Stat_nlink = (*env) -> GetFieldID(env, Stat, "nlink", "J");
    if (Stat_nlink == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_nlink_J");
        return JNI_FALSE;
    }

    Stat_uid = (*env) -> GetFieldID(env, Stat, "uid", "J");
    if (Stat_uid == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_uid_J");
        return JNI_FALSE;
    }

    Stat_gid = (*env) -> GetFieldID(env, Stat, "gid", "J");
    if (Stat_gid == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_gid_J");
        return JNI_FALSE;
    }

    Stat_rdev = (*env) -> GetFieldID(env, Stat, "rdev", "J");
    if (Stat_rdev == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_rdev_J");
        return JNI_FALSE;
    }

    Stat_size = (*env) -> GetFieldID(env, Stat, "size", "J");
    if (Stat_size == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_size_J");
        return JNI_FALSE;
    }

    Stat_blksize = (*env) -> GetFieldID(env, Stat, "blksize", "J");
    if (Stat_blksize == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_blksize_J");
        return JNI_FALSE;
    }

    Stat_blocks = (*env) -> GetFieldID(env, Stat, "blocks", "J");
    if (Stat_blocks == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_blocks_J");
        return JNI_FALSE;
    }

    Stat_atime = (*env) -> GetFieldID(env, Stat, "atime", "J");
    if (Stat_atime == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_atime_J");
        return JNI_FALSE;
    }

    Stat_mtime = (*env) -> GetFieldID(env, Stat, "mtime", "J");
    if (Stat_mtime == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_mtime_J");
        return JNI_FALSE;
    }

    Stat_ctime = (*env) -> GetFieldID(env, Stat, "ctime", "J");
    if (Stat_ctime == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_ctime_J");
        return JNI_FALSE;
    }

    Stat_OR = (*env) -> GetStaticFieldID(env, Stat, "OR", "I");
    if (Stat_OR == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_OR_I");
        return JNI_FALSE;
    }

    Stat_OW = (*env) -> GetStaticFieldID(env, Stat, "OW", "I");
    if (Stat_OW == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_OW_I");
        return JNI_FALSE;
    }

    Stat_OE = (*env) -> GetStaticFieldID(env, Stat, "OE", "I");
    if (Stat_OE == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_OE_I");
        return JNI_FALSE;
    }

    Stat_GR = (*env) -> GetStaticFieldID(env, Stat, "GR", "I");
    if (Stat_GR == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_GR_I");
        return JNI_FALSE;
    }

    Stat_GW = (*env) -> GetStaticFieldID(env, Stat, "GW", "I");
    if (Stat_GW == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_GW_I");
        return JNI_FALSE;
    }

    Stat_GE = (*env) -> GetStaticFieldID(env, Stat, "GE", "I");
    if (Stat_GE == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_GE_I");
        return JNI_FALSE;
    }

    Stat_ER = (*env) -> GetStaticFieldID(env, Stat, "ER", "I");
    if (Stat_ER == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_ER_I");
        return JNI_FALSE;
    }

    Stat_EW = (*env) -> GetStaticFieldID(env, Stat, "EW", "I");
    if (Stat_EW == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_EW_I");
        return JNI_FALSE;
    }

    Stat_EE = (*env) -> GetStaticFieldID(env, Stat, "EE", "I");
    if (Stat_EE == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat_EE_I");
        return JNI_FALSE;
    }

    Stat_C_0 = (*env) -> GetMethodID(env, Stat, "<init>", "()V");
    if (Stat_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.<init>()V");
        return JNI_FALSE;
    }

    Stat_M_canGroupExecute_0 = (*env) -> GetMethodID(env, Stat, "canGroupExecute", "()Z");
    if (Stat_M_canGroupExecute_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.canGroupExecute()Z");
        return JNI_FALSE;
    }

    Stat_M_canGroupRead_0 = (*env) -> GetMethodID(env, Stat, "canGroupRead", "()Z");
    if (Stat_M_canGroupRead_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.canGroupRead()Z");
        return JNI_FALSE;
    }

    Stat_M_canGroupWrite_0 = (*env) -> GetMethodID(env, Stat, "canGroupWrite", "()Z");
    if (Stat_M_canGroupWrite_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.canGroupWrite()Z");
        return JNI_FALSE;
    }

    Stat_M_canOthersExecute_0 = (*env) -> GetMethodID(env, Stat, "canOthersExecute", "()Z");
    if (Stat_M_canOthersExecute_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.canOthersExecute()Z");
        return JNI_FALSE;
    }

    Stat_M_canOthersRead_0 = (*env) -> GetMethodID(env, Stat, "canOthersRead", "()Z");
    if (Stat_M_canOthersRead_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.canOthersRead()Z");
        return JNI_FALSE;
    }

    Stat_M_canOthersWrite_0 = (*env) -> GetMethodID(env, Stat, "canOthersWrite", "()Z");
    if (Stat_M_canOthersWrite_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.canOthersWrite()Z");
        return JNI_FALSE;
    }

    Stat_M_canOwnerExecute_0 = (*env) -> GetMethodID(env, Stat, "canOwnerExecute", "()Z");
    if (Stat_M_canOwnerExecute_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.canOwnerExecute()Z");
        return JNI_FALSE;
    }

    Stat_M_canOwnerRead_0 = (*env) -> GetMethodID(env, Stat, "canOwnerRead", "()Z");
    if (Stat_M_canOwnerRead_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.canOwnerRead()Z");
        return JNI_FALSE;
    }

    Stat_M_canOwnerWrite_0 = (*env) -> GetMethodID(env, Stat, "canOwnerWrite", "()Z");
    if (Stat_M_canOwnerWrite_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.canOwnerWrite()Z");
        return JNI_FALSE;
    }

    Stat_M_getAtime_0 = (*env) -> GetMethodID(env, Stat, "getAtime", "()J");
    if (Stat_M_getAtime_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getAtime()J");
        return JNI_FALSE;
    }

    Stat_M_getBlksize_0 = (*env) -> GetMethodID(env, Stat, "getBlksize", "()J");
    if (Stat_M_getBlksize_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getBlksize()J");
        return JNI_FALSE;
    }

    Stat_M_getBlocks_0 = (*env) -> GetMethodID(env, Stat, "getBlocks", "()J");
    if (Stat_M_getBlocks_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getBlocks()J");
        return JNI_FALSE;
    }

    Stat_M_getCtime_0 = (*env) -> GetMethodID(env, Stat, "getCtime", "()J");
    if (Stat_M_getCtime_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getCtime()J");
        return JNI_FALSE;
    }

    Stat_M_getDev_0 = (*env) -> GetMethodID(env, Stat, "getDev", "()J");
    if (Stat_M_getDev_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getDev()J");
        return JNI_FALSE;
    }

    Stat_M_getGid_0 = (*env) -> GetMethodID(env, Stat, "getGid", "()J");
    if (Stat_M_getGid_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getGid()J");
        return JNI_FALSE;
    }

    Stat_M_getIno_0 = (*env) -> GetMethodID(env, Stat, "getIno", "()J");
    if (Stat_M_getIno_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getIno()J");
        return JNI_FALSE;
    }

    Stat_M_getMode_0 = (*env) -> GetMethodID(env, Stat, "getMode", "()J");
    if (Stat_M_getMode_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getMode()J");
        return JNI_FALSE;
    }

    Stat_M_getMtime_0 = (*env) -> GetMethodID(env, Stat, "getMtime", "()J");
    if (Stat_M_getMtime_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getMtime()J");
        return JNI_FALSE;
    }

    Stat_M_getNlink_0 = (*env) -> GetMethodID(env, Stat, "getNlink", "()J");
    if (Stat_M_getNlink_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getNlink()J");
        return JNI_FALSE;
    }

    Stat_M_getPermissions_0 = (*env) -> GetMethodID(env, Stat, "getPermissions", "()Ljava/lang/String;");
    if (Stat_M_getPermissions_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getPermissions()Ljava/lang/String;");
        return JNI_FALSE;
    }

    Stat_M_getRdev_0 = (*env) -> GetMethodID(env, Stat, "getRdev", "()J");
    if (Stat_M_getRdev_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getRdev()J");
        return JNI_FALSE;
    }

    Stat_M_getSize_0 = (*env) -> GetMethodID(env, Stat, "getSize", "()J");
    if (Stat_M_getSize_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getSize()J");
        return JNI_FALSE;
    }

    Stat_M_getUid_0 = (*env) -> GetMethodID(env, Stat, "getUid", "()J");
    if (Stat_M_getUid_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.getUid()J");
        return JNI_FALSE;
    }

    Stat_M_isBlockDevice_0 = (*env) -> GetMethodID(env, Stat, "isBlockDevice", "()Z");
    if (Stat_M_isBlockDevice_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.isBlockDevice()Z");
        return JNI_FALSE;
    }

    Stat_M_isCharacterDevice_0 = (*env) -> GetMethodID(env, Stat, "isCharacterDevice", "()Z");
    if (Stat_M_isCharacterDevice_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.isCharacterDevice()Z");
        return JNI_FALSE;
    }

    Stat_M_isDir_0 = (*env) -> GetMethodID(env, Stat, "isDir", "()Z");
    if (Stat_M_isDir_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.isDir()Z");
        return JNI_FALSE;
    }

    Stat_M_isFIFO_0 = (*env) -> GetMethodID(env, Stat, "isFIFO", "()Z");
    if (Stat_M_isFIFO_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.isFIFO()Z");
        return JNI_FALSE;
    }

    Stat_M_isRegularFile_0 = (*env) -> GetMethodID(env, Stat, "isRegularFile", "()Z");
    if (Stat_M_isRegularFile_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.isRegularFile()Z");
        return JNI_FALSE;
    }

    Stat_M_isSocket_0 = (*env) -> GetMethodID(env, Stat, "isSocket", "()Z");
    if (Stat_M_isSocket_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.isSocket()Z");
        return JNI_FALSE;
    }

    Stat_M_isSymbolicLink_0 = (*env) -> GetMethodID(env, Stat, "isSymbolicLink", "()Z");
    if (Stat_M_isSymbolicLink_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.isSymbolicLink()Z");
        return JNI_FALSE;
    }

    Stat_M_toString_0 = (*env) -> GetMethodID(env, Stat, "toString", "()Ljava/lang/String;");
    if (Stat_M_toString_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Stat.toString()Ljava/lang/String;");
        return JNI_FALSE;
    }

    Utsname_sysname = (*env) -> GetFieldID(env, Utsname, "sysname", "Ljava/lang/String;");
    if (Utsname_sysname == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname_sysname_Ljava/lang/String;");
        return JNI_FALSE;
    }

    Utsname_nodename = (*env) -> GetFieldID(env, Utsname, "nodename", "Ljava/lang/String;");
    if (Utsname_nodename == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname_nodename_Ljava/lang/String;");
        return JNI_FALSE;
    }

    Utsname_release = (*env) -> GetFieldID(env, Utsname, "release", "Ljava/lang/String;");
    if (Utsname_release == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname_release_Ljava/lang/String;");
        return JNI_FALSE;
    }

    Utsname_version = (*env) -> GetFieldID(env, Utsname, "version", "Ljava/lang/String;");
    if (Utsname_version == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname_version_Ljava/lang/String;");
        return JNI_FALSE;
    }

    Utsname_machine = (*env) -> GetFieldID(env, Utsname, "machine", "Ljava/lang/String;");
    if (Utsname_machine == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname_machine_Ljava/lang/String;");
        return JNI_FALSE;
    }

    Utsname_C_0 = (*env) -> GetMethodID(env, Utsname, "<init>", "()V");
    if (Utsname_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.<init>()V");
        return JNI_FALSE;
    }

    Utsname_M_getMachine_0 = (*env) -> GetMethodID(env, Utsname, "getMachine", "()Ljava/lang/String;");
    if (Utsname_M_getMachine_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.getMachine()Ljava/lang/String;");
        return JNI_FALSE;
    }

    Utsname_M_getNodename_0 = (*env) -> GetMethodID(env, Utsname, "getNodename", "()Ljava/lang/String;");
    if (Utsname_M_getNodename_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.getNodename()Ljava/lang/String;");
        return JNI_FALSE;
    }

    Utsname_M_getRelease_0 = (*env) -> GetMethodID(env, Utsname, "getRelease", "()Ljava/lang/String;");
    if (Utsname_M_getRelease_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.getRelease()Ljava/lang/String;");
        return JNI_FALSE;
    }

    Utsname_M_getSysname_0 = (*env) -> GetMethodID(env, Utsname, "getSysname", "()Ljava/lang/String;");
    if (Utsname_M_getSysname_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.getSysname()Ljava/lang/String;");
        return JNI_FALSE;
    }

    Utsname_M_getVersion_0 = (*env) -> GetMethodID(env, Utsname, "getVersion", "()Ljava/lang/String;");
    if (Utsname_M_getVersion_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Utsname.getVersion()Ljava/lang/String;");
        return JNI_FALSE;
    }

    Win32FileAttributeData_dwFileAttributes = (*env) -> GetFieldID(env, Win32FileAttributeData, "dwFileAttributes", "J");
    if (Win32FileAttributeData_dwFileAttributes == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_dwFileAttributes_J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_nFileSizeLow = (*env) -> GetFieldID(env, Win32FileAttributeData, "nFileSizeLow", "J");
    if (Win32FileAttributeData_nFileSizeLow == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_nFileSizeLow_J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_nFileSizeHigh = (*env) -> GetFieldID(env, Win32FileAttributeData, "nFileSizeHigh", "J");
    if (Win32FileAttributeData_nFileSizeHigh == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_nFileSizeHigh_J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_ftLastAccessTimeLow = (*env) -> GetFieldID(env, Win32FileAttributeData, "ftLastAccessTimeLow", "J");
    if (Win32FileAttributeData_ftLastAccessTimeLow == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftLastAccessTimeLow_J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_ftLastAccessTimeHigh = (*env) -> GetFieldID(env, Win32FileAttributeData, "ftLastAccessTimeHigh", "J");
    if (Win32FileAttributeData_ftLastAccessTimeHigh == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftLastAccessTimeHigh_J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_ftLastWriteTimeHigh = (*env) -> GetFieldID(env, Win32FileAttributeData, "ftLastWriteTimeHigh", "J");
    if (Win32FileAttributeData_ftLastWriteTimeHigh == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftLastWriteTimeHigh_J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_ftLastWriteTimeLow = (*env) -> GetFieldID(env, Win32FileAttributeData, "ftLastWriteTimeLow", "J");
    if (Win32FileAttributeData_ftLastWriteTimeLow == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftLastWriteTimeLow_J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_ftCreationTimeHigh = (*env) -> GetFieldID(env, Win32FileAttributeData, "ftCreationTimeHigh", "J");
    if (Win32FileAttributeData_ftCreationTimeHigh == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftCreationTimeHigh_J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_ftCreationTimeLow = (*env) -> GetFieldID(env, Win32FileAttributeData, "ftCreationTimeLow", "J");
    if (Win32FileAttributeData_ftCreationTimeLow == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData_ftCreationTimeLow_J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_C_0 = (*env) -> GetMethodID(env, Win32FileAttributeData, "<init>", "()V");
    if (Win32FileAttributeData_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.<init>()V");
        return JNI_FALSE;
    }

    Win32FileAttributeData_M_getDwFileAttributes_0 = (*env) -> GetMethodID(env, Win32FileAttributeData, "getDwFileAttributes", "()J");
    if (Win32FileAttributeData_M_getDwFileAttributes_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.getDwFileAttributes()J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_M_getFtCreationTimeHigh_0 = (*env) -> GetMethodID(env, Win32FileAttributeData, "getFtCreationTimeHigh", "()J");
    if (Win32FileAttributeData_M_getFtCreationTimeHigh_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.getFtCreationTimeHigh()J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_M_getFtCreationTimeLow_0 = (*env) -> GetMethodID(env, Win32FileAttributeData, "getFtCreationTimeLow", "()J");
    if (Win32FileAttributeData_M_getFtCreationTimeLow_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.getFtCreationTimeLow()J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_M_getFtLastAccessTimeHigh_0 = (*env) -> GetMethodID(env, Win32FileAttributeData, "getFtLastAccessTimeHigh", "()J");
    if (Win32FileAttributeData_M_getFtLastAccessTimeHigh_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.getFtLastAccessTimeHigh()J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_M_getFtLastAccessTimeLow_0 = (*env) -> GetMethodID(env, Win32FileAttributeData, "getFtLastAccessTimeLow", "()J");
    if (Win32FileAttributeData_M_getFtLastAccessTimeLow_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.getFtLastAccessTimeLow()J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_M_getFtLastWriteTimeHigh_0 = (*env) -> GetMethodID(env, Win32FileAttributeData, "getFtLastWriteTimeHigh", "()J");
    if (Win32FileAttributeData_M_getFtLastWriteTimeHigh_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.getFtLastWriteTimeHigh()J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_M_getFtLastWriteTimeLow_0 = (*env) -> GetMethodID(env, Win32FileAttributeData, "getFtLastWriteTimeLow", "()J");
    if (Win32FileAttributeData_M_getFtLastWriteTimeLow_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.getFtLastWriteTimeLow()J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_M_getnFileSizeHigh_0 = (*env) -> GetMethodID(env, Win32FileAttributeData, "getnFileSizeHigh", "()J");
    if (Win32FileAttributeData_M_getnFileSizeHigh_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.getnFileSizeHigh()J");
        return JNI_FALSE;
    }

    Win32FileAttributeData_M_getnFileSizeLow_0 = (*env) -> GetMethodID(env, Win32FileAttributeData, "getnFileSizeLow", "()J");
    if (Win32FileAttributeData_M_getnFileSizeLow_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Win32FileAttributeData.getnFileSizeLow()J");
        return JNI_FALSE;
    }

    Iterable_M_iterator_0 = (*env) -> GetMethodID(env, Iterable, "iterator", "()Ljava/util/Iterator;");
    if (Iterable_M_iterator_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/Iterable.iterator()Ljava/util/Iterator;");
        return JNI_FALSE;
    }

    InetAddress_M_equals_0 = (*env) -> GetMethodID(env, InetAddress, "equals", "(Ljava/lang/Object;)Z");
    if (InetAddress_M_equals_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.equals(Ljava/lang/Object;)Z");
        return JNI_FALSE;
    }

    InetAddress_M_getAddress_0 = (*env) -> GetMethodID(env, InetAddress, "getAddress", "()[B");
    if (InetAddress_M_getAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getAddress()[B");
        return JNI_FALSE;
    }

    InetAddress_M_getAllByName_0 = (*env) -> GetStaticMethodID(env, InetAddress, "getAllByName", "(Ljava/lang/String;)[Ljava/net/InetAddress;");
    if (InetAddress_M_getAllByName_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getAllByName(Ljava/lang/String;)[Ljava/net/InetAddress;");
        return JNI_FALSE;
    }

    InetAddress_M_getByAddress_0 = (*env) -> GetStaticMethodID(env, InetAddress, "getByAddress", "(Ljava/lang/String;[B)Ljava/net/InetAddress;");
    if (InetAddress_M_getByAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getByAddress(Ljava/lang/String;[B)Ljava/net/InetAddress;");
        return JNI_FALSE;
    }

    InetAddress_M_getByAddress_1 = (*env) -> GetStaticMethodID(env, InetAddress, "getByAddress", "([B)Ljava/net/InetAddress;");
    if (InetAddress_M_getByAddress_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getByAddress([B)Ljava/net/InetAddress;");
        return JNI_FALSE;
    }

    InetAddress_M_getByName_0 = (*env) -> GetStaticMethodID(env, InetAddress, "getByName", "(Ljava/lang/String;)Ljava/net/InetAddress;");
    if (InetAddress_M_getByName_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getByName(Ljava/lang/String;)Ljava/net/InetAddress;");
        return JNI_FALSE;
    }

    InetAddress_M_getCanonicalHostName_0 = (*env) -> GetMethodID(env, InetAddress, "getCanonicalHostName", "()Ljava/lang/String;");
    if (InetAddress_M_getCanonicalHostName_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getCanonicalHostName()Ljava/lang/String;");
        return JNI_FALSE;
    }

    InetAddress_M_getHostAddress_0 = (*env) -> GetMethodID(env, InetAddress, "getHostAddress", "()Ljava/lang/String;");
    if (InetAddress_M_getHostAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getHostAddress()Ljava/lang/String;");
        return JNI_FALSE;
    }

    InetAddress_M_getHostName_0 = (*env) -> GetMethodID(env, InetAddress, "getHostName", "()Ljava/lang/String;");
    if (InetAddress_M_getHostName_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getHostName()Ljava/lang/String;");
        return JNI_FALSE;
    }

    InetAddress_M_getLocalHost_0 = (*env) -> GetStaticMethodID(env, InetAddress, "getLocalHost", "()Ljava/net/InetAddress;");
    if (InetAddress_M_getLocalHost_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getLocalHost()Ljava/net/InetAddress;");
        return JNI_FALSE;
    }

    InetAddress_M_getLoopbackAddress_0 = (*env) -> GetStaticMethodID(env, InetAddress, "getLoopbackAddress", "()Ljava/net/InetAddress;");
    if (InetAddress_M_getLoopbackAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.getLoopbackAddress()Ljava/net/InetAddress;");
        return JNI_FALSE;
    }

    InetAddress_M_hashCode_0 = (*env) -> GetMethodID(env, InetAddress, "hashCode", "()I");
    if (InetAddress_M_hashCode_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.hashCode()I");
        return JNI_FALSE;
    }

    InetAddress_M_isAnyLocalAddress_0 = (*env) -> GetMethodID(env, InetAddress, "isAnyLocalAddress", "()Z");
    if (InetAddress_M_isAnyLocalAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isAnyLocalAddress()Z");
        return JNI_FALSE;
    }

    InetAddress_M_isLinkLocalAddress_0 = (*env) -> GetMethodID(env, InetAddress, "isLinkLocalAddress", "()Z");
    if (InetAddress_M_isLinkLocalAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isLinkLocalAddress()Z");
        return JNI_FALSE;
    }

    InetAddress_M_isLoopbackAddress_0 = (*env) -> GetMethodID(env, InetAddress, "isLoopbackAddress", "()Z");
    if (InetAddress_M_isLoopbackAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isLoopbackAddress()Z");
        return JNI_FALSE;
    }

    InetAddress_M_isMCGlobal_0 = (*env) -> GetMethodID(env, InetAddress, "isMCGlobal", "()Z");
    if (InetAddress_M_isMCGlobal_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isMCGlobal()Z");
        return JNI_FALSE;
    }

    InetAddress_M_isMCLinkLocal_0 = (*env) -> GetMethodID(env, InetAddress, "isMCLinkLocal", "()Z");
    if (InetAddress_M_isMCLinkLocal_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isMCLinkLocal()Z");
        return JNI_FALSE;
    }

    InetAddress_M_isMCNodeLocal_0 = (*env) -> GetMethodID(env, InetAddress, "isMCNodeLocal", "()Z");
    if (InetAddress_M_isMCNodeLocal_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isMCNodeLocal()Z");
        return JNI_FALSE;
    }

    InetAddress_M_isMCOrgLocal_0 = (*env) -> GetMethodID(env, InetAddress, "isMCOrgLocal", "()Z");
    if (InetAddress_M_isMCOrgLocal_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isMCOrgLocal()Z");
        return JNI_FALSE;
    }

    InetAddress_M_isMCSiteLocal_0 = (*env) -> GetMethodID(env, InetAddress, "isMCSiteLocal", "()Z");
    if (InetAddress_M_isMCSiteLocal_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isMCSiteLocal()Z");
        return JNI_FALSE;
    }

    InetAddress_M_isMulticastAddress_0 = (*env) -> GetMethodID(env, InetAddress, "isMulticastAddress", "()Z");
    if (InetAddress_M_isMulticastAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isMulticastAddress()Z");
        return JNI_FALSE;
    }

    InetAddress_M_isReachable_0 = (*env) -> GetMethodID(env, InetAddress, "isReachable", "(I)Z");
    if (InetAddress_M_isReachable_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isReachable(I)Z");
        return JNI_FALSE;
    }

    InetAddress_M_isReachable_1 = (*env) -> GetMethodID(env, InetAddress, "isReachable", "(Ljava/net/NetworkInterface;II)Z");
    if (InetAddress_M_isReachable_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isReachable(Ljava/net/NetworkInterface;II)Z");
        return JNI_FALSE;
    }

    InetAddress_M_isSiteLocalAddress_0 = (*env) -> GetMethodID(env, InetAddress, "isSiteLocalAddress", "()Z");
    if (InetAddress_M_isSiteLocalAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.isSiteLocalAddress()Z");
        return JNI_FALSE;
    }

    InetAddress_M_toString_0 = (*env) -> GetMethodID(env, InetAddress, "toString", "()Ljava/lang/String;");
    if (InetAddress_M_toString_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetAddress.toString()Ljava/lang/String;");
        return JNI_FALSE;
    }

    InetSocketAddress_C_0 = (*env) -> GetMethodID(env, InetSocketAddress, "<init>", "(I)V");
    if (InetSocketAddress_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.<init>(I)V");
        return JNI_FALSE;
    }

    InetSocketAddress_C_1 = (*env) -> GetMethodID(env, InetSocketAddress, "<init>", "(Ljava/lang/String;I)V");
    if (InetSocketAddress_C_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.<init>(Ljava/lang/String;I)V");
        return JNI_FALSE;
    }

    InetSocketAddress_C_2 = (*env) -> GetMethodID(env, InetSocketAddress, "<init>", "(Ljava/net/InetAddress;I)V");
    if (InetSocketAddress_C_2 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.<init>(Ljava/net/InetAddress;I)V");
        return JNI_FALSE;
    }

    InetSocketAddress_M_createUnresolved_0 = (*env) -> GetStaticMethodID(env, InetSocketAddress, "createUnresolved", "(Ljava/lang/String;I)Ljava/net/InetSocketAddress;");
    if (InetSocketAddress_M_createUnresolved_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.createUnresolved(Ljava/lang/String;I)Ljava/net/InetSocketAddress;");
        return JNI_FALSE;
    }

    InetSocketAddress_M_equals_0 = (*env) -> GetMethodID(env, InetSocketAddress, "equals", "(Ljava/lang/Object;)Z");
    if (InetSocketAddress_M_equals_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.equals(Ljava/lang/Object;)Z");
        return JNI_FALSE;
    }

    InetSocketAddress_M_getAddress_0 = (*env) -> GetMethodID(env, InetSocketAddress, "getAddress", "()Ljava/net/InetAddress;");
    if (InetSocketAddress_M_getAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.getAddress()Ljava/net/InetAddress;");
        return JNI_FALSE;
    }

    InetSocketAddress_M_getHostName_0 = (*env) -> GetMethodID(env, InetSocketAddress, "getHostName", "()Ljava/lang/String;");
    if (InetSocketAddress_M_getHostName_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.getHostName()Ljava/lang/String;");
        return JNI_FALSE;
    }

    InetSocketAddress_M_getHostString_0 = (*env) -> GetMethodID(env, InetSocketAddress, "getHostString", "()Ljava/lang/String;");
    if (InetSocketAddress_M_getHostString_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.getHostString()Ljava/lang/String;");
        return JNI_FALSE;
    }

    InetSocketAddress_M_getPort_0 = (*env) -> GetMethodID(env, InetSocketAddress, "getPort", "()I");
    if (InetSocketAddress_M_getPort_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.getPort()I");
        return JNI_FALSE;
    }

    InetSocketAddress_M_hashCode_0 = (*env) -> GetMethodID(env, InetSocketAddress, "hashCode", "()I");
    if (InetSocketAddress_M_hashCode_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.hashCode()I");
        return JNI_FALSE;
    }

    InetSocketAddress_M_isUnresolved_0 = (*env) -> GetMethodID(env, InetSocketAddress, "isUnresolved", "()Z");
    if (InetSocketAddress_M_isUnresolved_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.isUnresolved()Z");
        return JNI_FALSE;
    }

    InetSocketAddress_M_toString_0 = (*env) -> GetMethodID(env, InetSocketAddress, "toString", "()Ljava/lang/String;");
    if (InetSocketAddress_M_toString_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/InetSocketAddress.toString()Ljava/lang/String;");
        return JNI_FALSE;
    }

    ArrayList_C_0 = (*env) -> GetMethodID(env, ArrayList, "<init>", "()V");
    if (ArrayList_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.<init>()V");
        return JNI_FALSE;
    }

    ArrayList_C_1 = (*env) -> GetMethodID(env, ArrayList, "<init>", "(I)V");
    if (ArrayList_C_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.<init>(I)V");
        return JNI_FALSE;
    }

    ArrayList_C_2 = (*env) -> GetMethodID(env, ArrayList, "<init>", "(Ljava/util/Collection;)V");
    if (ArrayList_C_2 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.<init>(Ljava/util/Collection;)V");
        return JNI_FALSE;
    }

    ArrayList_M_add_0 = (*env) -> GetMethodID(env, ArrayList, "add", "(ILjava/lang/Object;)V");
    if (ArrayList_M_add_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.add(ILjava/lang/Object;)V");
        return JNI_FALSE;
    }

    ArrayList_M_add_1 = (*env) -> GetMethodID(env, ArrayList, "add", "(Ljava/lang/Object;)Z");
    if (ArrayList_M_add_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.add(Ljava/lang/Object;)Z");
        return JNI_FALSE;
    }

    ArrayList_M_addAll_0 = (*env) -> GetMethodID(env, ArrayList, "addAll", "(ILjava/util/Collection;)Z");
    if (ArrayList_M_addAll_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.addAll(ILjava/util/Collection;)Z");
        return JNI_FALSE;
    }

    ArrayList_M_addAll_1 = (*env) -> GetMethodID(env, ArrayList, "addAll", "(Ljava/util/Collection;)Z");
    if (ArrayList_M_addAll_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.addAll(Ljava/util/Collection;)Z");
        return JNI_FALSE;
    }

    ArrayList_M_clear_0 = (*env) -> GetMethodID(env, ArrayList, "clear", "()V");
    if (ArrayList_M_clear_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.clear()V");
        return JNI_FALSE;
    }

    ArrayList_M_clone_0 = (*env) -> GetMethodID(env, ArrayList, "clone", "()Ljava/lang/Object;");
    if (ArrayList_M_clone_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.clone()Ljava/lang/Object;");
        return JNI_FALSE;
    }

    ArrayList_M_contains_0 = (*env) -> GetMethodID(env, ArrayList, "contains", "(Ljava/lang/Object;)Z");
    if (ArrayList_M_contains_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.contains(Ljava/lang/Object;)Z");
        return JNI_FALSE;
    }

    ArrayList_M_ensureCapacity_0 = (*env) -> GetMethodID(env, ArrayList, "ensureCapacity", "(I)V");
    if (ArrayList_M_ensureCapacity_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.ensureCapacity(I)V");
        return JNI_FALSE;
    }

    ArrayList_M_get_0 = (*env) -> GetMethodID(env, ArrayList, "get", "(I)Ljava/lang/Object;");
    if (ArrayList_M_get_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.get(I)Ljava/lang/Object;");
        return JNI_FALSE;
    }

    ArrayList_M_indexOf_0 = (*env) -> GetMethodID(env, ArrayList, "indexOf", "(Ljava/lang/Object;)I");
    if (ArrayList_M_indexOf_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.indexOf(Ljava/lang/Object;)I");
        return JNI_FALSE;
    }

    ArrayList_M_isEmpty_0 = (*env) -> GetMethodID(env, ArrayList, "isEmpty", "()Z");
    if (ArrayList_M_isEmpty_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.isEmpty()Z");
        return JNI_FALSE;
    }

    ArrayList_M_iterator_0 = (*env) -> GetMethodID(env, ArrayList, "iterator", "()Ljava/util/Iterator;");
    if (ArrayList_M_iterator_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.iterator()Ljava/util/Iterator;");
        return JNI_FALSE;
    }

    ArrayList_M_lastIndexOf_0 = (*env) -> GetMethodID(env, ArrayList, "lastIndexOf", "(Ljava/lang/Object;)I");
    if (ArrayList_M_lastIndexOf_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.lastIndexOf(Ljava/lang/Object;)I");
        return JNI_FALSE;
    }

    ArrayList_M_listIterator_0 = (*env) -> GetMethodID(env, ArrayList, "listIterator", "()Ljava/util/ListIterator;");
    if (ArrayList_M_listIterator_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.listIterator()Ljava/util/ListIterator;");
        return JNI_FALSE;
    }

    ArrayList_M_listIterator_1 = (*env) -> GetMethodID(env, ArrayList, "listIterator", "(I)Ljava/util/ListIterator;");
    if (ArrayList_M_listIterator_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.listIterator(I)Ljava/util/ListIterator;");
        return JNI_FALSE;
    }

    ArrayList_M_remove_0 = (*env) -> GetMethodID(env, ArrayList, "remove", "(I)Ljava/lang/Object;");
    if (ArrayList_M_remove_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.remove(I)Ljava/lang/Object;");
        return JNI_FALSE;
    }

    ArrayList_M_remove_1 = (*env) -> GetMethodID(env, ArrayList, "remove", "(Ljava/lang/Object;)Z");
    if (ArrayList_M_remove_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.remove(Ljava/lang/Object;)Z");
        return JNI_FALSE;
    }

    ArrayList_M_removeAll_0 = (*env) -> GetMethodID(env, ArrayList, "removeAll", "(Ljava/util/Collection;)Z");
    if (ArrayList_M_removeAll_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.removeAll(Ljava/util/Collection;)Z");
        return JNI_FALSE;
    }

    ArrayList_M_retainAll_0 = (*env) -> GetMethodID(env, ArrayList, "retainAll", "(Ljava/util/Collection;)Z");
    if (ArrayList_M_retainAll_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.retainAll(Ljava/util/Collection;)Z");
        return JNI_FALSE;
    }

    ArrayList_M_set_0 = (*env) -> GetMethodID(env, ArrayList, "set", "(ILjava/lang/Object;)Ljava/lang/Object;");
    if (ArrayList_M_set_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.set(ILjava/lang/Object;)Ljava/lang/Object;");
        return JNI_FALSE;
    }

    ArrayList_M_size_0 = (*env) -> GetMethodID(env, ArrayList, "size", "()I");
    if (ArrayList_M_size_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.size()I");
        return JNI_FALSE;
    }

    ArrayList_M_subList_0 = (*env) -> GetMethodID(env, ArrayList, "subList", "(II)Ljava/util/List;");
    if (ArrayList_M_subList_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.subList(II)Ljava/util/List;");
        return JNI_FALSE;
    }

    ArrayList_M_toArray_0 = (*env) -> GetMethodID(env, ArrayList, "toArray", "()[Ljava/lang/Object;");
    if (ArrayList_M_toArray_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.toArray()[Ljava/lang/Object;");
        return JNI_FALSE;
    }

    ArrayList_M_toArray_1 = (*env) -> GetMethodID(env, ArrayList, "toArray", "([Ljava/lang/Object;)[Ljava/lang/Object;");
    if (ArrayList_M_toArray_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.toArray([Ljava/lang/Object;)[Ljava/lang/Object;");
        return JNI_FALSE;
    }

    ArrayList_M_trimToSize_0 = (*env) -> GetMethodID(env, ArrayList, "trimToSize", "()V");
    if (ArrayList_M_trimToSize_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/ArrayList.trimToSize()V");
        return JNI_FALSE;
    }

    Collection_M_add_0 = (*env) -> GetMethodID(env, Collection, "add", "(Ljava/lang/Object;)Z");
    if (Collection_M_add_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.add(Ljava/lang/Object;)Z");
        return JNI_FALSE;
    }

    Collection_M_addAll_0 = (*env) -> GetMethodID(env, Collection, "addAll", "(Ljava/util/Collection;)Z");
    if (Collection_M_addAll_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.addAll(Ljava/util/Collection;)Z");
        return JNI_FALSE;
    }

    Collection_M_clear_0 = (*env) -> GetMethodID(env, Collection, "clear", "()V");
    if (Collection_M_clear_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.clear()V");
        return JNI_FALSE;
    }

    Collection_M_contains_0 = (*env) -> GetMethodID(env, Collection, "contains", "(Ljava/lang/Object;)Z");
    if (Collection_M_contains_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.contains(Ljava/lang/Object;)Z");
        return JNI_FALSE;
    }

    Collection_M_containsAll_0 = (*env) -> GetMethodID(env, Collection, "containsAll", "(Ljava/util/Collection;)Z");
    if (Collection_M_containsAll_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.containsAll(Ljava/util/Collection;)Z");
        return JNI_FALSE;
    }

    Collection_M_equals_0 = (*env) -> GetMethodID(env, Collection, "equals", "(Ljava/lang/Object;)Z");
    if (Collection_M_equals_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.equals(Ljava/lang/Object;)Z");
        return JNI_FALSE;
    }

    Collection_M_hashCode_0 = (*env) -> GetMethodID(env, Collection, "hashCode", "()I");
    if (Collection_M_hashCode_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.hashCode()I");
        return JNI_FALSE;
    }

    Collection_M_isEmpty_0 = (*env) -> GetMethodID(env, Collection, "isEmpty", "()Z");
    if (Collection_M_isEmpty_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.isEmpty()Z");
        return JNI_FALSE;
    }

    Collection_M_iterator_0 = (*env) -> GetMethodID(env, Collection, "iterator", "()Ljava/util/Iterator;");
    if (Collection_M_iterator_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.iterator()Ljava/util/Iterator;");
        return JNI_FALSE;
    }

    Collection_M_remove_0 = (*env) -> GetMethodID(env, Collection, "remove", "(Ljava/lang/Object;)Z");
    if (Collection_M_remove_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.remove(Ljava/lang/Object;)Z");
        return JNI_FALSE;
    }

    Collection_M_removeAll_0 = (*env) -> GetMethodID(env, Collection, "removeAll", "(Ljava/util/Collection;)Z");
    if (Collection_M_removeAll_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.removeAll(Ljava/util/Collection;)Z");
        return JNI_FALSE;
    }

    Collection_M_retainAll_0 = (*env) -> GetMethodID(env, Collection, "retainAll", "(Ljava/util/Collection;)Z");
    if (Collection_M_retainAll_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.retainAll(Ljava/util/Collection;)Z");
        return JNI_FALSE;
    }

    Collection_M_size_0 = (*env) -> GetMethodID(env, Collection, "size", "()I");
    if (Collection_M_size_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.size()I");
        return JNI_FALSE;
    }

    Collection_M_toArray_0 = (*env) -> GetMethodID(env, Collection, "toArray", "()[Ljava/lang/Object;");
    if (Collection_M_toArray_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.toArray()[Ljava/lang/Object;");
        return JNI_FALSE;
    }

    Collection_M_toArray_1 = (*env) -> GetMethodID(env, Collection, "toArray", "([Ljava/lang/Object;)[Ljava/lang/Object;");
    if (Collection_M_toArray_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Collection.toArray([Ljava/lang/Object;)[Ljava/lang/Object;");
        return JNI_FALSE;
    }

    Iterator_M_hasNext_0 = (*env) -> GetMethodID(env, Iterator, "hasNext", "()Z");
    if (Iterator_M_hasNext_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Iterator.hasNext()Z");
        return JNI_FALSE;
    }

    Iterator_M_next_0 = (*env) -> GetMethodID(env, Iterator, "next", "()Ljava/lang/Object;");
    if (Iterator_M_next_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Iterator.next()Ljava/lang/Object;");
        return JNI_FALSE;
    }

    Iterator_M_remove_0 = (*env) -> GetMethodID(env, Iterator, "remove", "()V");
    if (Iterator_M_remove_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/util/Iterator.remove()V");
        return JNI_FALSE;
    }

    InvalidFileDescriptorException_EC_0 = (*env) -> GetMethodID(env, InvalidFileDescriptorException, "<init>", "()V");
    if (InvalidFileDescriptorException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/InvalidFileDescriptorException.<init>()V");
        return JNI_FALSE;
    }

    MutexAbandonedException_EC_0 = (*env) -> GetMethodID(env, MutexAbandonedException, "<init>", "(J)V");
    if (MutexAbandonedException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/MutexAbandonedException.<init>(J)V");
        return JNI_FALSE;
    }

    OperationInProgressException_EC_0 = (*env) -> GetMethodID(env, OperationInProgressException, "<init>", "()V");
    if (OperationInProgressException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/OperationInProgressException.<init>()V");
        return JNI_FALSE;
    }

    OperationInProgressException_EC_1 = (*env) -> GetMethodID(env, OperationInProgressException, "<init>", "(Ljava/lang/String;)V");
    if (OperationInProgressException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/OperationInProgressException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    PermissionDeniedException_EC_0 = (*env) -> GetMethodID(env, PermissionDeniedException, "<init>", "(Ljava/lang/String;)V");
    if (PermissionDeniedException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/PermissionDeniedException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    PermissionDeniedException_EC_1 = (*env) -> GetMethodID(env, PermissionDeniedException, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (PermissionDeniedException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/PermissionDeniedException.<init>(Ljava/lang/String;Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    QuotaExceededException_EC_0 = (*env) -> GetMethodID(env, QuotaExceededException, "<init>", "(Ljava/lang/String;)V");
    if (QuotaExceededException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/QuotaExceededException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    QuotaExceededException_EC_1 = (*env) -> GetMethodID(env, QuotaExceededException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    if (QuotaExceededException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/QuotaExceededException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    SharingViolationException_EC_0 = (*env) -> GetMethodID(env, SharingViolationException, "<init>", "(Ljava/lang/String;)V");
    if (SharingViolationException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    SharingViolationException_EC_1 = (*env) -> GetMethodID(env, SharingViolationException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    if (SharingViolationException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/SharingViolationException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    ShellExecuteException_EC_0 = (*env) -> GetMethodID(env, ShellExecuteException, "<init>", "(JJ)V");
    if (ShellExecuteException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/ShellExecuteException.<init>(JJ)V");
        return JNI_FALSE;
    }

    UnknownNativeErrorException_EC_0 = (*env) -> GetMethodID(env, UnknownNativeErrorException, "<init>", "()V");
    if (UnknownNativeErrorException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/UnknownNativeErrorException.<init>()V");
        return JNI_FALSE;
    }

    UnknownNativeErrorException_EC_1 = (*env) -> GetMethodID(env, UnknownNativeErrorException, "<init>", "(J)V");
    if (UnknownNativeErrorException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/exceptions/UnknownNativeErrorException.<init>(J)V");
        return JNI_FALSE;
    }

    FileNotFoundException_EC_0 = (*env) -> GetMethodID(env, FileNotFoundException, "<init>", "()V");
    if (FileNotFoundException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/io/FileNotFoundException.<init>()V");
        return JNI_FALSE;
    }

    FileNotFoundException_EC_1 = (*env) -> GetMethodID(env, FileNotFoundException, "<init>", "(Ljava/lang/String;)V");
    if (FileNotFoundException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/io/FileNotFoundException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    IOException_EC_0 = (*env) -> GetMethodID(env, IOException, "<init>", "()V");
    if (IOException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/io/IOException.<init>()V");
        return JNI_FALSE;
    }

    IOException_EC_1 = (*env) -> GetMethodID(env, IOException, "<init>", "(Ljava/lang/String;)V");
    if (IOException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/io/IOException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    IOException_EC_2 = (*env) -> GetMethodID(env, IOException, "<init>", "(Ljava/lang/String;Ljava/lang/Throwable;)V");
    if (IOException_EC_2 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/io/IOException.<init>(Ljava/lang/String;Ljava/lang/Throwable;)V");
        return JNI_FALSE;
    }

    IOException_EC_3 = (*env) -> GetMethodID(env, IOException, "<init>", "(Ljava/lang/Throwable;)V");
    if (IOException_EC_3 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/io/IOException.<init>(Ljava/lang/Throwable;)V");
        return JNI_FALSE;
    }

    Exception_EC_0 = (*env) -> GetMethodID(env, Exception, "<init>", "()V");
    if (Exception_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/Exception.<init>()V");
        return JNI_FALSE;
    }

    Exception_EC_1 = (*env) -> GetMethodID(env, Exception, "<init>", "(Ljava/lang/String;)V");
    if (Exception_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/Exception.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    Exception_EC_2 = (*env) -> GetMethodID(env, Exception, "<init>", "(Ljava/lang/String;Ljava/lang/Throwable;)V");
    if (Exception_EC_2 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/Exception.<init>(Ljava/lang/String;Ljava/lang/Throwable;)V");
        return JNI_FALSE;
    }

    Exception_EC_3 = (*env) -> GetMethodID(env, Exception, "<init>", "(Ljava/lang/Throwable;)V");
    if (Exception_EC_3 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/Exception.<init>(Ljava/lang/Throwable;)V");
        return JNI_FALSE;
    }

    IllegalArgumentException_EC_0 = (*env) -> GetMethodID(env, IllegalArgumentException, "<init>", "()V");
    if (IllegalArgumentException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalArgumentException.<init>()V");
        return JNI_FALSE;
    }

    IllegalArgumentException_EC_1 = (*env) -> GetMethodID(env, IllegalArgumentException, "<init>", "(Ljava/lang/String;)V");
    if (IllegalArgumentException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalArgumentException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    IllegalArgumentException_EC_2 = (*env) -> GetMethodID(env, IllegalArgumentException, "<init>", "(Ljava/lang/String;Ljava/lang/Throwable;)V");
    if (IllegalArgumentException_EC_2 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalArgumentException.<init>(Ljava/lang/String;Ljava/lang/Throwable;)V");
        return JNI_FALSE;
    }

    IllegalArgumentException_EC_3 = (*env) -> GetMethodID(env, IllegalArgumentException, "<init>", "(Ljava/lang/Throwable;)V");
    if (IllegalArgumentException_EC_3 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalArgumentException.<init>(Ljava/lang/Throwable;)V");
        return JNI_FALSE;
    }

    IllegalStateException_EC_0 = (*env) -> GetMethodID(env, IllegalStateException, "<init>", "()V");
    if (IllegalStateException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalStateException.<init>()V");
        return JNI_FALSE;
    }

    IllegalStateException_EC_1 = (*env) -> GetMethodID(env, IllegalStateException, "<init>", "(Ljava/lang/String;)V");
    if (IllegalStateException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalStateException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    IllegalStateException_EC_2 = (*env) -> GetMethodID(env, IllegalStateException, "<init>", "(Ljava/lang/String;Ljava/lang/Throwable;)V");
    if (IllegalStateException_EC_2 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalStateException.<init>(Ljava/lang/String;Ljava/lang/Throwable;)V");
        return JNI_FALSE;
    }

    IllegalStateException_EC_3 = (*env) -> GetMethodID(env, IllegalStateException, "<init>", "(Ljava/lang/Throwable;)V");
    if (IllegalStateException_EC_3 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/IllegalStateException.<init>(Ljava/lang/Throwable;)V");
        return JNI_FALSE;
    }

    NullPointerException_EC_0 = (*env) -> GetMethodID(env, NullPointerException, "<init>", "()V");
    if (NullPointerException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/NullPointerException.<init>()V");
        return JNI_FALSE;
    }

    NullPointerException_EC_1 = (*env) -> GetMethodID(env, NullPointerException, "<init>", "(Ljava/lang/String;)V");
    if (NullPointerException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/NullPointerException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    OutOfMemoryError_EC_0 = (*env) -> GetMethodID(env, OutOfMemoryError, "<init>", "()V");
    if (OutOfMemoryError_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/OutOfMemoryError.<init>()V");
        return JNI_FALSE;
    }

    OutOfMemoryError_EC_1 = (*env) -> GetMethodID(env, OutOfMemoryError, "<init>", "(Ljava/lang/String;)V");
    if (OutOfMemoryError_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/OutOfMemoryError.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    UnsupportedOperationException_EC_0 = (*env) -> GetMethodID(env, UnsupportedOperationException, "<init>", "()V");
    if (UnsupportedOperationException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/UnsupportedOperationException.<init>()V");
        return JNI_FALSE;
    }

    UnsupportedOperationException_EC_1 = (*env) -> GetMethodID(env, UnsupportedOperationException, "<init>", "(Ljava/lang/String;)V");
    if (UnsupportedOperationException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/UnsupportedOperationException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    UnsupportedOperationException_EC_2 = (*env) -> GetMethodID(env, UnsupportedOperationException, "<init>", "(Ljava/lang/String;Ljava/lang/Throwable;)V");
    if (UnsupportedOperationException_EC_2 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/UnsupportedOperationException.<init>(Ljava/lang/String;Ljava/lang/Throwable;)V");
        return JNI_FALSE;
    }

    UnsupportedOperationException_EC_3 = (*env) -> GetMethodID(env, UnsupportedOperationException, "<init>", "(Ljava/lang/Throwable;)V");
    if (UnsupportedOperationException_EC_3 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/lang/UnsupportedOperationException.<init>(Ljava/lang/Throwable;)V");
        return JNI_FALSE;
    }

    BindException_EC_0 = (*env) -> GetMethodID(env, BindException, "<init>", "()V");
    if (BindException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/BindException.<init>()V");
        return JNI_FALSE;
    }

    BindException_EC_1 = (*env) -> GetMethodID(env, BindException, "<init>", "(Ljava/lang/String;)V");
    if (BindException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/BindException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    ConnectException_EC_0 = (*env) -> GetMethodID(env, ConnectException, "<init>", "()V");
    if (ConnectException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/ConnectException.<init>()V");
        return JNI_FALSE;
    }

    ConnectException_EC_1 = (*env) -> GetMethodID(env, ConnectException, "<init>", "(Ljava/lang/String;)V");
    if (ConnectException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/net/ConnectException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    AccessDeniedException_EC_0 = (*env) -> GetMethodID(env, AccessDeniedException, "<init>", "(Ljava/lang/String;)V");
    if (AccessDeniedException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/AccessDeniedException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    AccessDeniedException_EC_1 = (*env) -> GetMethodID(env, AccessDeniedException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    if (AccessDeniedException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/AccessDeniedException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    FileAlreadyExistsException_EC_0 = (*env) -> GetMethodID(env, FileAlreadyExistsException, "<init>", "(Ljava/lang/String;)V");
    if (FileAlreadyExistsException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/FileAlreadyExistsException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    FileAlreadyExistsException_EC_1 = (*env) -> GetMethodID(env, FileAlreadyExistsException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    if (FileAlreadyExistsException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/FileAlreadyExistsException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    FileSystemLoopException_EC_0 = (*env) -> GetMethodID(env, FileSystemLoopException, "<init>", "(Ljava/lang/String;)V");
    if (FileSystemLoopException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/FileSystemLoopException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    InvalidPathException_EC_0 = (*env) -> GetMethodID(env, InvalidPathException, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (InvalidPathException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/InvalidPathException.<init>(Ljava/lang/String;Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    InvalidPathException_EC_1 = (*env) -> GetMethodID(env, InvalidPathException, "<init>", "(Ljava/lang/String;Ljava/lang/String;I)V");
    if (InvalidPathException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/InvalidPathException.<init>(Ljava/lang/String;Ljava/lang/String;I)V");
        return JNI_FALSE;
    }

    NotDirectoryException_EC_0 = (*env) -> GetMethodID(env, NotDirectoryException, "<init>", "(Ljava/lang/String;)V");
    if (NotDirectoryException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/NotDirectoryException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    NotLinkException_EC_0 = (*env) -> GetMethodID(env, NotLinkException, "<init>", "(Ljava/lang/String;)V");
    if (NotLinkException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/NotLinkException.<init>(Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    NotLinkException_EC_1 = (*env) -> GetMethodID(env, NotLinkException, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    if (NotLinkException_EC_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/NotLinkException.<init>(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        return JNI_FALSE;
    }

    ReadOnlyFileSystemException_EC_0 = (*env) -> GetMethodID(env, ReadOnlyFileSystemException, "<init>", "()V");
    if (ReadOnlyFileSystemException_EC_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find java/nio/file/ReadOnlyFileSystemException.<init>()V");
        return JNI_FALSE;
    }


    return JNI_TRUE;
}

void jnigenerator_destroy(JNIEnv * env) {
    if (internal_Exception != 0) {
        (*env) -> DeleteGlobalRef(env, internal_Exception);
        internal_Exception = 0;
    }
    if (internal_OutOfMemoryError != 0) {
        (*env) -> DeleteGlobalRef(env, internal_OutOfMemoryError);
        internal_OutOfMemoryError = 0;
    }
    if (internal_IllegalArgumentException != 0) {
        (*env) -> DeleteGlobalRef(env, internal_IllegalArgumentException);
        internal_IllegalArgumentException = 0;
    }
    if (internal_NullPointerException != 0) {
        (*env) -> DeleteGlobalRef(env, internal_NullPointerException);
        internal_NullPointerException = 0;
    }
    if (internal_Enum != 0) {
        (*env) -> DeleteGlobalRef(env, internal_Enum);
        internal_Enum = 0;
    }
    internal_Enum_name = 0;
    internal_Enum_ordinal = 0;

    if (IpAdapterAddresses != 0) {
        (*env) -> DeleteGlobalRef(env, IpAdapterAddresses);
        IpAdapterAddresses = 0;
    }

    if (IllegalStateException != 0) {
        (*env) -> DeleteGlobalRef(env, IllegalStateException);
        IllegalStateException = 0;
    }

    if (Win32FileAttributeData != 0) {
        (*env) -> DeleteGlobalRef(env, Win32FileAttributeData);
        Win32FileAttributeData = 0;
    }

    if (IpAdapterAddresses$IpAdapterUnicastAddress != 0) {
        (*env) -> DeleteGlobalRef(env, IpAdapterAddresses$IpAdapterUnicastAddress);
        IpAdapterAddresses$IpAdapterUnicastAddress = 0;
    }

    if (OperationInProgressException != 0) {
        (*env) -> DeleteGlobalRef(env, OperationInProgressException);
        OperationInProgressException = 0;
    }

    if (PermissionDeniedException != 0) {
        (*env) -> DeleteGlobalRef(env, PermissionDeniedException);
        PermissionDeniedException = 0;
    }

    if (ShellExecuteException != 0) {
        (*env) -> DeleteGlobalRef(env, ShellExecuteException);
        ShellExecuteException = 0;
    }

    if (GUID != 0) {
        (*env) -> DeleteGlobalRef(env, GUID);
        GUID = 0;
    }

    if (BindException != 0) {
        (*env) -> DeleteGlobalRef(env, BindException);
        BindException = 0;
    }

    if (Iterable != 0) {
        (*env) -> DeleteGlobalRef(env, Iterable);
        Iterable = 0;
    }

    if (NullPointerException != 0) {
        (*env) -> DeleteGlobalRef(env, NullPointerException);
        NullPointerException = 0;
    }

    if (Utsname != 0) {
        (*env) -> DeleteGlobalRef(env, Utsname);
        Utsname = 0;
    }

    if (ArrayList != 0) {
        (*env) -> DeleteGlobalRef(env, ArrayList);
        ArrayList = 0;
    }

    if (InetAddress != 0) {
        (*env) -> DeleteGlobalRef(env, InetAddress);
        InetAddress = 0;
    }

    if (Cmsghdr != 0) {
        (*env) -> DeleteGlobalRef(env, Cmsghdr);
        Cmsghdr = 0;
    }

    if (InvalidPathException != 0) {
        (*env) -> DeleteGlobalRef(env, InvalidPathException);
        InvalidPathException = 0;
    }

    if (FileSystemLoopException != 0) {
        (*env) -> DeleteGlobalRef(env, FileSystemLoopException);
        FileSystemLoopException = 0;
    }

    if (UnknownNativeErrorException != 0) {
        (*env) -> DeleteGlobalRef(env, UnknownNativeErrorException);
        UnknownNativeErrorException = 0;
    }

    if (ConnectException != 0) {
        (*env) -> DeleteGlobalRef(env, ConnectException);
        ConnectException = 0;
    }

    if (PollFD != 0) {
        (*env) -> DeleteGlobalRef(env, PollFD);
        PollFD = 0;
    }

    if (UnsupportedOperationException != 0) {
        (*env) -> DeleteGlobalRef(env, UnsupportedOperationException);
        UnsupportedOperationException = 0;
    }

    if (Stat != 0) {
        (*env) -> DeleteGlobalRef(env, Stat);
        Stat = 0;
    }

    if (Iterator != 0) {
        (*env) -> DeleteGlobalRef(env, Iterator);
        Iterator = 0;
    }

    if (NotDirectoryException != 0) {
        (*env) -> DeleteGlobalRef(env, NotDirectoryException);
        NotDirectoryException = 0;
    }

    if (Collection != 0) {
        (*env) -> DeleteGlobalRef(env, Collection);
        Collection = 0;
    }

    if (NotLinkException != 0) {
        (*env) -> DeleteGlobalRef(env, NotLinkException);
        NotLinkException = 0;
    }

    if (Msghdr != 0) {
        (*env) -> DeleteGlobalRef(env, Msghdr);
        Msghdr = 0;
    }

    if (IOException != 0) {
        (*env) -> DeleteGlobalRef(env, IOException);
        IOException = 0;
    }

    if (IllegalArgumentException != 0) {
        (*env) -> DeleteGlobalRef(env, IllegalArgumentException);
        IllegalArgumentException = 0;
    }

    if (FileAlreadyExistsException != 0) {
        (*env) -> DeleteGlobalRef(env, FileAlreadyExistsException);
        FileAlreadyExistsException = 0;
    }

    if (InetSocketAddress != 0) {
        (*env) -> DeleteGlobalRef(env, InetSocketAddress);
        InetSocketAddress = 0;
    }

    if (FileNotFoundException != 0) {
        (*env) -> DeleteGlobalRef(env, FileNotFoundException);
        FileNotFoundException = 0;
    }

    if (Exception != 0) {
        (*env) -> DeleteGlobalRef(env, Exception);
        Exception = 0;
    }

    if (QuotaExceededException != 0) {
        (*env) -> DeleteGlobalRef(env, QuotaExceededException);
        QuotaExceededException = 0;
    }

    if (InvalidFileDescriptorException != 0) {
        (*env) -> DeleteGlobalRef(env, InvalidFileDescriptorException);
        InvalidFileDescriptorException = 0;
    }

    if (PollFD$PollEvent != 0) {
        (*env) -> DeleteGlobalRef(env, PollFD$PollEvent);
        PollFD$PollEvent = 0;
    }

    if (Iovec != 0) {
        (*env) -> DeleteGlobalRef(env, Iovec);
        Iovec = 0;
    }

    if (Sockaddr != 0) {
        (*env) -> DeleteGlobalRef(env, Sockaddr);
        Sockaddr = 0;
    }

    if (MutexAbandonedException != 0) {
        (*env) -> DeleteGlobalRef(env, MutexAbandonedException);
        MutexAbandonedException = 0;
    }

    if (AccessDeniedException != 0) {
        (*env) -> DeleteGlobalRef(env, AccessDeniedException);
        AccessDeniedException = 0;
    }

    if (ReadOnlyFileSystemException != 0) {
        (*env) -> DeleteGlobalRef(env, ReadOnlyFileSystemException);
        ReadOnlyFileSystemException = 0;
    }

    if (OutOfMemoryError != 0) {
        (*env) -> DeleteGlobalRef(env, OutOfMemoryError);
        OutOfMemoryError = 0;
    }

    if (SharingViolationException != 0) {
        (*env) -> DeleteGlobalRef(env, SharingViolationException);
        SharingViolationException = 0;
    }

    Cmsghdr_cmsg_level = 0;
    Cmsghdr_cmsg_type = 0;
    Cmsghdr_payload = 0;
    Cmsghdr_C_0 = 0;
    Cmsghdr_M_getLevel_0 = 0;
    Cmsghdr_M_getPayload_0 = 0;
    Cmsghdr_M_getType_0 = 0;
    Cmsghdr_M_setPayload_0 = 0;
    GUID_data1 = 0;
    GUID_data2 = 0;
    GUID_data3 = 0;
    GUID_data4 = 0;
    GUID_C_0 = 0;
    GUID_C_1 = 0;
    GUID_M_clone_0 = 0;
    GUID_M_getData1_0 = 0;
    GUID_M_getData2_0 = 0;
    GUID_M_getData3_0 = 0;
    GUID_M_getData4_0 = 0;
    GUID_M_setData1_0 = 0;
    GUID_M_setData2_0 = 0;
    GUID_M_setData3_0 = 0;
    GUID_M_setData4_0 = 0;
    GUID_M_toString_0 = 0;
    Iovec_payload = 0;
    Iovec_off = 0;
    Iovec_len = 0;
    Iovec_size = 0;
    Iovec_C_0 = 0;
    Iovec_C_1 = 0;
    Iovec_C_2 = 0;
    Iovec_M_getLen_0 = 0;
    Iovec_M_getOff_0 = 0;
    Iovec_M_getPayload_0 = 0;
    Iovec_M_getSize_0 = 0;
    IpAdapterAddresses_AdapterName = 0;
    IpAdapterAddresses_UnicastAddress = 0;
    IpAdapterAddresses_AnycastAddress = 0;
    IpAdapterAddresses_MulticastAddress = 0;
    IpAdapterAddresses_DnsServerAddress = 0;
    IpAdapterAddresses_DnsSuffix = 0;
    IpAdapterAddresses_Description = 0;
    IpAdapterAddresses_FriendlyName = 0;
    IpAdapterAddresses_PhysicalAddress = 0;
    IpAdapterAddresses_Mtu = 0;
    IpAdapterAddresses_IfType = 0;
    IpAdapterAddresses_OperStatus = 0;
    IpAdapterAddresses_Ipv6IfIndex = 0;
    IpAdapterAddresses_ZoneIndices = 0;
    IpAdapterAddresses_Prefix = 0;
    IpAdapterAddresses_TransmitLinkSpeed = 0;
    IpAdapterAddresses_ReceiveLinkSpeed = 0;
    IpAdapterAddresses_WinsServerAddress = 0;
    IpAdapterAddresses_GatewayAddress = 0;
    IpAdapterAddresses_Ipv4Metric = 0;
    IpAdapterAddresses_Ipv6Metric = 0;
    IpAdapterAddresses_Luid_Value = 0;
    IpAdapterAddresses_Luid_NetLuidIndex = 0;
    IpAdapterAddresses_Luid_IfType = 0;
    IpAdapterAddresses_Dhcpv4Server = 0;
    IpAdapterAddresses_CompartmentId = 0;
    IpAdapterAddresses_NetworkGuid = 0;
    IpAdapterAddresses_ConnectionType = 0;
    IpAdapterAddresses_TunnelType = 0;
    IpAdapterAddresses_Dhcpv6Server = 0;
    IpAdapterAddresses_Dhcpv6ClientDuid = 0;
    IpAdapterAddresses_Dhcpv6Iaid = 0;
    IpAdapterAddresses_C_0 = 0;
    IpAdapterAddresses_M_getAdapterName_0 = 0;
    IpAdapterAddresses_M_getAnycastAddress_0 = 0;
    IpAdapterAddresses_M_getCompartmentId_0 = 0;
    IpAdapterAddresses_M_getConnectionType_0 = 0;
    IpAdapterAddresses_M_getDescription_0 = 0;
    IpAdapterAddresses_M_getDhcpv4Server_0 = 0;
    IpAdapterAddresses_M_getDhcpv6ClientDuid_0 = 0;
    IpAdapterAddresses_M_getDhcpv6Iaid_0 = 0;
    IpAdapterAddresses_M_getDhcpv6Server_0 = 0;
    IpAdapterAddresses_M_getDnsServerAddress_0 = 0;
    IpAdapterAddresses_M_getDnsSuffix_0 = 0;
    IpAdapterAddresses_M_getFriendlyName_0 = 0;
    IpAdapterAddresses_M_getGatewayAddress_0 = 0;
    IpAdapterAddresses_M_getIfType_0 = 0;
    IpAdapterAddresses_M_getIpv4Metric_0 = 0;
    IpAdapterAddresses_M_getIpv6IfIndex_0 = 0;
    IpAdapterAddresses_M_getIpv6Metric_0 = 0;
    IpAdapterAddresses_M_getLuid_IfType_0 = 0;
    IpAdapterAddresses_M_getLuid_NetLuidIndex_0 = 0;
    IpAdapterAddresses_M_getLuid_Value_0 = 0;
    IpAdapterAddresses_M_getMtu_0 = 0;
    IpAdapterAddresses_M_getMulticastAddress_0 = 0;
    IpAdapterAddresses_M_getNetworkGuid_0 = 0;
    IpAdapterAddresses_M_getOperStatus_0 = 0;
    IpAdapterAddresses_M_getPhysicalAddress_0 = 0;
    IpAdapterAddresses_M_getPrefix_0 = 0;
    IpAdapterAddresses_M_getReceiveLinkSpeed_0 = 0;
    IpAdapterAddresses_M_getTransmitLinkSpeed_0 = 0;
    IpAdapterAddresses_M_getTunnelType_0 = 0;
    IpAdapterAddresses_M_getUnicastAddress_0 = 0;
    IpAdapterAddresses_M_getWinsServerAddress_0 = 0;
    IpAdapterAddresses_M_getZoneIndices_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_Address = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_DadState = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_C_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_M_getAddress_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_M_getDadState_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_M_getLeaseLifetime_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_M_getOnLinkPrefixLength_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_M_getPreferredLifetime_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_M_getPrefixOrigin_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_M_getSuffixOrigin_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_M_getValidLifetime_0 = 0;
    Msghdr_msg_iov = 0;
    Msghdr_msg_control = 0;
    Msghdr_msg_name = 0;
    Msghdr_complete = 0;
    Msghdr_truncated = 0;
    Msghdr_controlDataTruncated = 0;
    Msghdr_outOfBand = 0;
    Msghdr_errQueue = 0;
    Msghdr_msg_controllen = 0;
    Msghdr_C_0 = 0;
    Msghdr_C_1 = 0;
    Msghdr_C_2 = 0;
    Msghdr_C_3 = 0;
    Msghdr_C_4 = 0;
    Msghdr_C_5 = 0;
    Msghdr_C_6 = 0;
    Msghdr_M_getMsg_control_0 = 0;
    Msghdr_M_getMsg_controllen_0 = 0;
    Msghdr_M_getMsg_iov_0 = 0;
    Msghdr_M_getMsg_name_0 = 0;
    Msghdr_M_isComplete_0 = 0;
    Msghdr_M_isControlDataTruncated_0 = 0;
    Msghdr_M_isErrQueue_0 = 0;
    Msghdr_M_isOutOfBand_0 = 0;
    Msghdr_M_isTruncated_0 = 0;
    PollFD_fd = 0;
    PollFD_events = 0;
    PollFD_revents = 0;
    PollFD_C_0 = 0;
    PollFD_M_getEvents_0 = 0;
    PollFD_M_getFd_0 = 0;
    PollFD_M_getREvents_0 = 0;
    PollFD_M_test_0 = 0;
    if (PollFD$PollEvent_POLLIN != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLIN);
    }
    PollFD$PollEvent_POLLIN = 0;
    if (PollFD$PollEvent_POLLPRI != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLPRI);
    }
    PollFD$PollEvent_POLLPRI = 0;
    if (PollFD$PollEvent_POLLOUT != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLOUT);
    }
    PollFD$PollEvent_POLLOUT = 0;
    if (PollFD$PollEvent_POLLRDNORM != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLRDNORM);
    }
    PollFD$PollEvent_POLLRDNORM = 0;
    if (PollFD$PollEvent_POLLRDBAND != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLRDBAND);
    }
    PollFD$PollEvent_POLLRDBAND = 0;
    if (PollFD$PollEvent_POLLWRNORM != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLWRNORM);
    }
    PollFD$PollEvent_POLLWRNORM = 0;
    if (PollFD$PollEvent_POLLWRBAND != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLWRBAND);
    }
    PollFD$PollEvent_POLLWRBAND = 0;
    if (PollFD$PollEvent_POLLMSG != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLMSG);
    }
    PollFD$PollEvent_POLLMSG = 0;
    if (PollFD$PollEvent_POLLREMOVE != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLREMOVE);
    }
    PollFD$PollEvent_POLLREMOVE = 0;
    if (PollFD$PollEvent_POLLRDHUP != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLRDHUP);
    }
    PollFD$PollEvent_POLLRDHUP = 0;
    if (PollFD$PollEvent_POLLERR != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLERR);
    }
    PollFD$PollEvent_POLLERR = 0;
    if (PollFD$PollEvent_POLLHUP != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLHUP);
    }
    PollFD$PollEvent_POLLHUP = 0;
    if (PollFD$PollEvent_POLLNVAL != 0) {
        (*env)->DeleteGlobalRef(env, PollFD$PollEvent_POLLNVAL);
    }
    PollFD$PollEvent_POLLNVAL = 0;
    PollFD$PollEvent_$VALUES = 0;
    for (int i = 0; i < 13; i++) {
        PollFD$PollEvent_enum_values[i] = 0;
    }

    PollFD$PollEvent_C_0 = 0;
    Sockaddr_EMPTY = 0;
    Sockaddr_addressFamily = 0;
    Sockaddr_address = 0;
    Sockaddr_C_0 = 0;
    Sockaddr_C_1 = 0;
    Sockaddr_C_2 = 0;
    Sockaddr_M_clone_0 = 0;
    Sockaddr_M_copyTo_0 = 0;
    Sockaddr_M_getAddress_0 = 0;
    Sockaddr_M_getAddressFamily_0 = 0;
    Stat_dev = 0;
    Stat_ino = 0;
    Stat_mode = 0;
    Stat_nlink = 0;
    Stat_uid = 0;
    Stat_gid = 0;
    Stat_rdev = 0;
    Stat_size = 0;
    Stat_blksize = 0;
    Stat_blocks = 0;
    Stat_atime = 0;
    Stat_mtime = 0;
    Stat_ctime = 0;
    Stat_OR = 0;
    Stat_OW = 0;
    Stat_OE = 0;
    Stat_GR = 0;
    Stat_GW = 0;
    Stat_GE = 0;
    Stat_ER = 0;
    Stat_EW = 0;
    Stat_EE = 0;
    Stat_C_0 = 0;
    Stat_M_canGroupExecute_0 = 0;
    Stat_M_canGroupRead_0 = 0;
    Stat_M_canGroupWrite_0 = 0;
    Stat_M_canOthersExecute_0 = 0;
    Stat_M_canOthersRead_0 = 0;
    Stat_M_canOthersWrite_0 = 0;
    Stat_M_canOwnerExecute_0 = 0;
    Stat_M_canOwnerRead_0 = 0;
    Stat_M_canOwnerWrite_0 = 0;
    Stat_M_getAtime_0 = 0;
    Stat_M_getBlksize_0 = 0;
    Stat_M_getBlocks_0 = 0;
    Stat_M_getCtime_0 = 0;
    Stat_M_getDev_0 = 0;
    Stat_M_getGid_0 = 0;
    Stat_M_getIno_0 = 0;
    Stat_M_getMode_0 = 0;
    Stat_M_getMtime_0 = 0;
    Stat_M_getNlink_0 = 0;
    Stat_M_getPermissions_0 = 0;
    Stat_M_getRdev_0 = 0;
    Stat_M_getSize_0 = 0;
    Stat_M_getUid_0 = 0;
    Stat_M_isBlockDevice_0 = 0;
    Stat_M_isCharacterDevice_0 = 0;
    Stat_M_isDir_0 = 0;
    Stat_M_isFIFO_0 = 0;
    Stat_M_isRegularFile_0 = 0;
    Stat_M_isSocket_0 = 0;
    Stat_M_isSymbolicLink_0 = 0;
    Stat_M_toString_0 = 0;
    Utsname_sysname = 0;
    Utsname_nodename = 0;
    Utsname_release = 0;
    Utsname_version = 0;
    Utsname_machine = 0;
    Utsname_C_0 = 0;
    Utsname_M_getMachine_0 = 0;
    Utsname_M_getNodename_0 = 0;
    Utsname_M_getRelease_0 = 0;
    Utsname_M_getSysname_0 = 0;
    Utsname_M_getVersion_0 = 0;
    Win32FileAttributeData_dwFileAttributes = 0;
    Win32FileAttributeData_nFileSizeLow = 0;
    Win32FileAttributeData_nFileSizeHigh = 0;
    Win32FileAttributeData_ftLastAccessTimeLow = 0;
    Win32FileAttributeData_ftLastAccessTimeHigh = 0;
    Win32FileAttributeData_ftLastWriteTimeHigh = 0;
    Win32FileAttributeData_ftLastWriteTimeLow = 0;
    Win32FileAttributeData_ftCreationTimeHigh = 0;
    Win32FileAttributeData_ftCreationTimeLow = 0;
    Win32FileAttributeData_C_0 = 0;
    Win32FileAttributeData_M_getDwFileAttributes_0 = 0;
    Win32FileAttributeData_M_getFtCreationTimeHigh_0 = 0;
    Win32FileAttributeData_M_getFtCreationTimeLow_0 = 0;
    Win32FileAttributeData_M_getFtLastAccessTimeHigh_0 = 0;
    Win32FileAttributeData_M_getFtLastAccessTimeLow_0 = 0;
    Win32FileAttributeData_M_getFtLastWriteTimeHigh_0 = 0;
    Win32FileAttributeData_M_getFtLastWriteTimeLow_0 = 0;
    Win32FileAttributeData_M_getnFileSizeHigh_0 = 0;
    Win32FileAttributeData_M_getnFileSizeLow_0 = 0;
    Iterable_M_iterator_0 = 0;
    InetAddress_M_equals_0 = 0;
    InetAddress_M_getAddress_0 = 0;
    InetAddress_M_getAllByName_0 = 0;
    InetAddress_M_getByAddress_0 = 0;
    InetAddress_M_getByAddress_1 = 0;
    InetAddress_M_getByName_0 = 0;
    InetAddress_M_getCanonicalHostName_0 = 0;
    InetAddress_M_getHostAddress_0 = 0;
    InetAddress_M_getHostName_0 = 0;
    InetAddress_M_getLocalHost_0 = 0;
    InetAddress_M_getLoopbackAddress_0 = 0;
    InetAddress_M_hashCode_0 = 0;
    InetAddress_M_isAnyLocalAddress_0 = 0;
    InetAddress_M_isLinkLocalAddress_0 = 0;
    InetAddress_M_isLoopbackAddress_0 = 0;
    InetAddress_M_isMCGlobal_0 = 0;
    InetAddress_M_isMCLinkLocal_0 = 0;
    InetAddress_M_isMCNodeLocal_0 = 0;
    InetAddress_M_isMCOrgLocal_0 = 0;
    InetAddress_M_isMCSiteLocal_0 = 0;
    InetAddress_M_isMulticastAddress_0 = 0;
    InetAddress_M_isReachable_0 = 0;
    InetAddress_M_isReachable_1 = 0;
    InetAddress_M_isSiteLocalAddress_0 = 0;
    InetAddress_M_toString_0 = 0;
    InetSocketAddress_C_0 = 0;
    InetSocketAddress_C_1 = 0;
    InetSocketAddress_C_2 = 0;
    InetSocketAddress_M_createUnresolved_0 = 0;
    InetSocketAddress_M_equals_0 = 0;
    InetSocketAddress_M_getAddress_0 = 0;
    InetSocketAddress_M_getHostName_0 = 0;
    InetSocketAddress_M_getHostString_0 = 0;
    InetSocketAddress_M_getPort_0 = 0;
    InetSocketAddress_M_hashCode_0 = 0;
    InetSocketAddress_M_isUnresolved_0 = 0;
    InetSocketAddress_M_toString_0 = 0;
    ArrayList_C_0 = 0;
    ArrayList_C_1 = 0;
    ArrayList_C_2 = 0;
    ArrayList_M_add_0 = 0;
    ArrayList_M_add_1 = 0;
    ArrayList_M_addAll_0 = 0;
    ArrayList_M_addAll_1 = 0;
    ArrayList_M_clear_0 = 0;
    ArrayList_M_clone_0 = 0;
    ArrayList_M_contains_0 = 0;
    ArrayList_M_ensureCapacity_0 = 0;
    ArrayList_M_get_0 = 0;
    ArrayList_M_indexOf_0 = 0;
    ArrayList_M_isEmpty_0 = 0;
    ArrayList_M_iterator_0 = 0;
    ArrayList_M_lastIndexOf_0 = 0;
    ArrayList_M_listIterator_0 = 0;
    ArrayList_M_listIterator_1 = 0;
    ArrayList_M_remove_0 = 0;
    ArrayList_M_remove_1 = 0;
    ArrayList_M_removeAll_0 = 0;
    ArrayList_M_retainAll_0 = 0;
    ArrayList_M_set_0 = 0;
    ArrayList_M_size_0 = 0;
    ArrayList_M_subList_0 = 0;
    ArrayList_M_toArray_0 = 0;
    ArrayList_M_toArray_1 = 0;
    ArrayList_M_trimToSize_0 = 0;
    Collection_M_add_0 = 0;
    Collection_M_addAll_0 = 0;
    Collection_M_clear_0 = 0;
    Collection_M_contains_0 = 0;
    Collection_M_containsAll_0 = 0;
    Collection_M_equals_0 = 0;
    Collection_M_hashCode_0 = 0;
    Collection_M_isEmpty_0 = 0;
    Collection_M_iterator_0 = 0;
    Collection_M_remove_0 = 0;
    Collection_M_removeAll_0 = 0;
    Collection_M_retainAll_0 = 0;
    Collection_M_size_0 = 0;
    Collection_M_toArray_0 = 0;
    Collection_M_toArray_1 = 0;
    Iterator_M_hasNext_0 = 0;
    Iterator_M_next_0 = 0;
    Iterator_M_remove_0 = 0;
    InvalidFileDescriptorException_EC_0 = 0;
    MutexAbandonedException_EC_0 = 0;
    OperationInProgressException_EC_0 = 0;
    OperationInProgressException_EC_1 = 0;
    PermissionDeniedException_EC_0 = 0;
    PermissionDeniedException_EC_1 = 0;
    QuotaExceededException_EC_0 = 0;
    QuotaExceededException_EC_1 = 0;
    SharingViolationException_EC_0 = 0;
    SharingViolationException_EC_1 = 0;
    ShellExecuteException_EC_0 = 0;
    UnknownNativeErrorException_EC_0 = 0;
    UnknownNativeErrorException_EC_1 = 0;
    FileNotFoundException_EC_0 = 0;
    FileNotFoundException_EC_1 = 0;
    IOException_EC_0 = 0;
    IOException_EC_1 = 0;
    IOException_EC_2 = 0;
    IOException_EC_3 = 0;
    Exception_EC_0 = 0;
    Exception_EC_1 = 0;
    Exception_EC_2 = 0;
    Exception_EC_3 = 0;
    IllegalArgumentException_EC_0 = 0;
    IllegalArgumentException_EC_1 = 0;
    IllegalArgumentException_EC_2 = 0;
    IllegalArgumentException_EC_3 = 0;
    IllegalStateException_EC_0 = 0;
    IllegalStateException_EC_1 = 0;
    IllegalStateException_EC_2 = 0;
    IllegalStateException_EC_3 = 0;
    NullPointerException_EC_0 = 0;
    NullPointerException_EC_1 = 0;
    OutOfMemoryError_EC_0 = 0;
    OutOfMemoryError_EC_1 = 0;
    UnsupportedOperationException_EC_0 = 0;
    UnsupportedOperationException_EC_1 = 0;
    UnsupportedOperationException_EC_2 = 0;
    UnsupportedOperationException_EC_3 = 0;
    BindException_EC_0 = 0;
    BindException_EC_1 = 0;
    ConnectException_EC_0 = 0;
    ConnectException_EC_1 = 0;
    AccessDeniedException_EC_0 = 0;
    AccessDeniedException_EC_1 = 0;
    FileAlreadyExistsException_EC_0 = 0;
    FileAlreadyExistsException_EC_1 = 0;
    FileSystemLoopException_EC_0 = 0;
    InvalidPathException_EC_0 = 0;
    InvalidPathException_EC_1 = 0;
    NotDirectoryException_EC_0 = 0;
    NotLinkException_EC_0 = 0;
    NotLinkException_EC_1 = 0;
    ReadOnlyFileSystemException_EC_0 = 0;

}

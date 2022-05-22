//THIS FILE IS MACHINE GENERATED, DO NOT EDIT
#include "jstub.h"
static jclass Exception = 0;
static jclass OutOfMemoryError = 0;
static jclass IllegalArgumentException = 0;
static jclass NullPointerException = 0;

static jclass makeGlobalClassRef(JNIEnv * env, const char * name) {
   jclass clazz = (*env) -> FindClass(env, name);
   if (clazz == 0) {
       return 0;
   }

   jclass global = (*env) -> NewGlobalRef(env, clazz);
   (*env) -> DeleteLocalRef(env, clazz);
   return global;
}

static void throwOOM(JNIEnv * env, const char * name) {
    (*env) -> ThrowNew(env, OutOfMemoryError, name);
}

static void throwOptOOM(JNIEnv * env, const char * name) {
    if (!(*env) -> ExceptionCheck(env)) {
        (*env) -> ThrowNew(env, OutOfMemoryError, name);
    }
}

static void throwOptIllegalArgumentException(JNIEnv * env, const char * name) {
    if (!(*env) -> ExceptionCheck(env)) {
        (*env) -> ThrowNew(env, IllegalArgumentException, name);
    }
}

static void throwOptNPE(JNIEnv * env, const char * name) {
    if (!(*env) -> ExceptionCheck(env)) {
        (*env) -> ThrowNew(env, NullPointerException, name);
    }
}

jboolean jerr(JNIEnv * env) {
    return (*env) -> ExceptionCheck(env);
}

jbyteArray jarrayB(JNIEnv * env, jbyte * buffer, jsize len) {
    if (len < 0) {
        throwOptIllegalArgumentException(env, "jarrayB len < 0");
        return 0;
    }
    jbyteArray res = (*env) -> NewByteArray(env, len);
    if (res == 0) {
        throwOptOOM(env, "jarrayB NewByteArray");
        return 0;
    }
    if (len == 0) {
        return 0;
    }
    if (buffer == 0) {
        (*env)->DeleteLocalRef(env, res);
        throwOptNPE(env, "jarrayB buffer = NULL");
    }
    (*env)->SetByteArrayRegion(env, res, 0, len, (const jbyte*) buffer);
    return res;
}

static jclass IpAdapterAddresses = 0;
static jfieldID IpAdapterAddresses_AdapterName = 0;
void jset_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_AdapterName, value);
}

void jsetC_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance, char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_AdapterName, 0);
        return;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throwOptOOM(env, "NewStringUTF");
        return;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_AdapterName, tmp);
    (*env)->DeleteLocalRef(env, tmp);
}

void jsetWC_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_AdapterName, 0);
        return;
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
        throwOptOOM(env, "NewByteArray");
        return;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_AdapterName, tmp);
    (*env)->DeleteLocalRef(env, tmp);
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

void jsetC_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance, char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_DnsSuffix, 0);
        return;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throwOptOOM(env, "NewStringUTF");
        return;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_DnsSuffix, tmp);
    (*env)->DeleteLocalRef(env, tmp);
}

void jsetWC_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_DnsSuffix, 0);
        return;
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
        throwOptOOM(env, "NewByteArray");
        return;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_DnsSuffix, tmp);
    (*env)->DeleteLocalRef(env, tmp);
}

jstring jget_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, IpAdapterAddresses_DnsSuffix);
}

static jfieldID IpAdapterAddresses_Description = 0;
void jset_IpAdapterAddresses_Description(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_Description, value);
}

void jsetC_IpAdapterAddresses_Description(JNIEnv * env, jobject instance, char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_Description, 0);
        return;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throwOptOOM(env, "NewStringUTF");
        return;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_Description, tmp);
    (*env)->DeleteLocalRef(env, tmp);
}

void jsetWC_IpAdapterAddresses_Description(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_Description, 0);
        return;
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
        throwOptOOM(env, "NewByteArray");
        return;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_Description, tmp);
    (*env)->DeleteLocalRef(env, tmp);
}

jstring jget_IpAdapterAddresses_Description(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, IpAdapterAddresses_Description);
}

static jfieldID IpAdapterAddresses_FriendlyName = 0;
void jset_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance, jstring value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_FriendlyName, value);
}

void jsetC_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance, char * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_FriendlyName, 0);
        return;
    }
    jstring tmp = (*env)->NewStringUTF(env, value);
    if (tmp == 0) {
        throwOptOOM(env, "NewStringUTF");
        return;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_FriendlyName, tmp);
    (*env)->DeleteLocalRef(env, tmp);
}

void jsetWC_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance, wchar_t * value) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_FriendlyName, 0);
        return;
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
        throwOptOOM(env, "NewByteArray");
        return;
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_FriendlyName, tmp);
    (*env)->DeleteLocalRef(env, tmp);
}

jstring jget_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance) {
   return (jstring) (*env)->GetObjectField(env, instance, IpAdapterAddresses_FriendlyName);
}

static jfieldID IpAdapterAddresses_PhysicalAddress = 0;
void jset_IpAdapterAddresses_PhysicalAddress(JNIEnv * env, jobject instance, jbyteArray value) {
   (*env)->SetObjectField(env, instance, IpAdapterAddresses_PhysicalAddress, value);
}

void jsetA_IpAdapterAddresses_PhysicalAddress(JNIEnv * env, jobject instance, jbyte * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_PhysicalAddress, 0);
        return;
    }
    if (len < 0) {
        len = 0;
    }
    jbyteArray tmp = (*env)->NewByteArray(env, len);
    if (tmp == 0) {
        throwOptOOM(env, "NewByteArray");
        return;
    }
    if (len > 0) {
        (*env)->SetByteArrayRegion(env, tmp, 0, len, (const jbyte*) value);
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_PhysicalAddress, tmp);
    (*env)->DeleteLocalRef(env, tmp);
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

void jsetA_IpAdapterAddresses_ZoneIndices(JNIEnv * env, jobject instance, jlong * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_ZoneIndices, 0);
        return;
    }
    if (len < 0) {
        len = 0;
    }
    jlongArray tmp = (*env)->NewLongArray(env, len);
    if (tmp == 0) {
        throwOptOOM(env, "NewByteArray");
        return;
    }
    if (len > 0) {
        (*env)->SetLongArrayRegion(env, tmp, 0, len, (const jlong*) value);
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_ZoneIndices, tmp);
    (*env)->DeleteLocalRef(env, tmp);
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

void jsetA_IpAdapterAddresses_Dhcpv6ClientDuid(JNIEnv * env, jobject instance, jbyte * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,IpAdapterAddresses_Dhcpv6ClientDuid, 0);
        return;
    }
    if (len < 0) {
        len = 0;
    }
    jbyteArray tmp = (*env)->NewByteArray(env, len);
    if (tmp == 0) {
        throwOptOOM(env, "NewByteArray");
        return;
    }
    if (len > 0) {
        (*env)->SetByteArrayRegion(env, tmp, 0, len, (const jbyte*) value);
    }
    (*env)->SetObjectField(env, instance, IpAdapterAddresses_Dhcpv6ClientDuid, tmp);
    (*env)->DeleteLocalRef(env, tmp);
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

static jmethodID IpAdapterAddresses_M_getTunnelType_0 = 0;
jint jcall_IpAdapterAddresses_getTunnelType(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, IpAdapterAddresses_M_getTunnelType_0);
}

static jmethodID IpAdapterAddresses_M_getDhcpv6Iaid_0 = 0;
jlong jcall_IpAdapterAddresses_getDhcpv6Iaid(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses_M_getDhcpv6Iaid_0);
}

static jmethodID IpAdapterAddresses_M_getNetworkGuid_0 = 0;
jobject jcall_IpAdapterAddresses_getNetworkGuid(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getNetworkGuid_0);
}

static jmethodID IpAdapterAddresses_M_getDhcpv6Server_0 = 0;
jobject jcall_IpAdapterAddresses_getDhcpv6Server(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getDhcpv6Server_0);
}

static jmethodID IpAdapterAddresses_M_getFriendlyName_0 = 0;
jstring jcall_IpAdapterAddresses_getFriendlyName(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getFriendlyName_0);
}

static jmethodID IpAdapterAddresses_M_getGatewayAddress_0 = 0;
jobject jcall_IpAdapterAddresses_getGatewayAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getGatewayAddress_0);
}

static jmethodID IpAdapterAddresses_C_0 = 0;
jobject jnew_IpAdapterAddresses(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, IpAdapterAddresses, IpAdapterAddresses_C_0);
    if (obj == NULL) {
        throwOptOOM(env, "NewObject");
    }
    return obj;
}

static jmethodID IpAdapterAddresses_M_getDhcpv6ClientDuid_0 = 0;
jbyteArray jcall_IpAdapterAddresses_getDhcpv6ClientDuid(JNIEnv * env, jobject instance) {
    return (jbyteArray) (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getDhcpv6ClientDuid_0);
}

static jmethodID IpAdapterAddresses_M_getZoneIndices_0 = 0;
jlongArray jcall_IpAdapterAddresses_getZoneIndices(JNIEnv * env, jobject instance) {
    return (jlongArray) (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses_M_getZoneIndices_0);
}

static jclass IpAdapterAddresses$IpAdapterUnicastAddress = 0;
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

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_M_getOnLinkPrefixLength_0 = 0;
jint jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getOnLinkPrefixLength(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_M_getOnLinkPrefixLength_0);
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_M_getLeaseLifetime_0 = 0;
jlong jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getLeaseLifetime(JNIEnv * env, jobject instance) {
    return (*env) -> CallLongMethod(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_M_getLeaseLifetime_0);
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_M_getAddress_0 = 0;
jobject jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getAddress(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, IpAdapterAddresses$IpAdapterUnicastAddress_M_getAddress_0);
}

static jmethodID IpAdapterAddresses$IpAdapterUnicastAddress_C_0 = 0;
jobject jnew_IpAdapterAddresses$IpAdapterUnicastAddress(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, IpAdapterAddresses$IpAdapterUnicastAddress, IpAdapterAddresses$IpAdapterUnicastAddress_C_0);
    if (obj == NULL) {
        throwOptOOM(env, "NewObject");
    }
    return obj;
}

static jclass Sockaddr = 0;
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

void jsetA_Sockaddr_address(JNIEnv * env, jobject instance, jbyte * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,Sockaddr_address, 0);
        return;
    }
    if (len < 0) {
        len = 0;
    }
    jbyteArray tmp = (*env)->NewByteArray(env, len);
    if (tmp == 0) {
        throwOptOOM(env, "NewByteArray");
        return;
    }
    if (len > 0) {
        (*env)->SetByteArrayRegion(env, tmp, 0, len, (const jbyte*) value);
    }
    (*env)->SetObjectField(env, instance, Sockaddr_address, tmp);
    (*env)->DeleteLocalRef(env, tmp);
}

jbyteArray jget_Sockaddr_address(JNIEnv * env, jobject instance) {
   return (jbyteArray) (*env)->GetObjectField(env, instance, Sockaddr_address);
}

static jmethodID Sockaddr_M_getAddressFamily_0 = 0;
jint jcall_Sockaddr_getAddressFamily(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, Sockaddr_M_getAddressFamily_0);
}

static jmethodID Sockaddr_M_clone_0 = 0;
jobject jcall_Sockaddr_clone(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, Sockaddr_M_clone_0);
}

static jmethodID Sockaddr_M_clone_1 = 0;
jobject jcall_Sockaddr_clone_1(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, Sockaddr_M_clone_1);
}

static jmethodID Sockaddr_M_getAddress_0 = 0;
jbyteArray jcall_Sockaddr_getAddress(JNIEnv * env, jobject instance) {
    return (jbyteArray) (*env) -> CallObjectMethod(env, instance, Sockaddr_M_getAddress_0);
}

static jmethodID Sockaddr_C_0 = 0;
jobject jnew_Sockaddr(JNIEnv * env, jint p0, jbyteArray p1) {
    jobject obj = (*env) -> NewObject(env, Sockaddr, Sockaddr_C_0, p0, p1);
    if (obj == NULL) {
        throwOptOOM(env, "NewObject");
    }
    return obj;
}

static jmethodID Sockaddr_M_copyTo_0 = 0;
void jcall_Sockaddr_copyTo(JNIEnv * env, jobject instance, jobject p0) {
    (*env) -> CallVoidMethod(env, instance, Sockaddr_M_copyTo_0, p0);
}

static jclass GUID = 0;
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

void jsetA_GUID_data4(JNIEnv * env, jobject instance, jbyte * value, jsize len) {
    if (value == 0) {
        (*env)->SetObjectField(env, instance,GUID_data4, 0);
        return;
    }
    if (len < 0) {
        len = 0;
    }
    jbyteArray tmp = (*env)->NewByteArray(env, len);
    if (tmp == 0) {
        throwOptOOM(env, "NewByteArray");
        return;
    }
    if (len > 0) {
        (*env)->SetByteArrayRegion(env, tmp, 0, len, (const jbyte*) value);
    }
    (*env)->SetObjectField(env, instance, GUID_data4, tmp);
    (*env)->DeleteLocalRef(env, tmp);
}

jbyteArray jget_GUID_data4(JNIEnv * env, jobject instance) {
   return (jbyteArray) (*env)->GetObjectField(env, instance, GUID_data4);
}

static jmethodID GUID_M_getData1_0 = 0;
jint jcall_GUID_getData1(JNIEnv * env, jobject instance) {
    return (*env) -> CallIntMethod(env, instance, GUID_M_getData1_0);
}

static jmethodID GUID_M_clone_0 = 0;
jobject jcall_GUID_clone(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, GUID_M_clone_0);
}

static jmethodID GUID_M_clone_1 = 0;
jobject jcall_GUID_clone_1(JNIEnv * env, jobject instance) {
    return (*env) -> CallObjectMethod(env, instance, GUID_M_clone_1);
}

static jmethodID GUID_M_toString_0 = 0;
jstring jcall_GUID_toString(JNIEnv * env, jobject instance) {
    return (jstring) (*env) -> CallObjectMethod(env, instance, GUID_M_toString_0);
}

static jmethodID GUID_M_getData3_0 = 0;
jshort jcall_GUID_getData3(JNIEnv * env, jobject instance) {
    return (*env) -> CallShortMethod(env, instance, GUID_M_getData3_0);
}

static jmethodID GUID_C_0 = 0;
jobject jnew_GUID(JNIEnv * env) {
    jobject obj = (*env) -> NewObject(env, GUID, GUID_C_0);
    if (obj == NULL) {
        throwOptOOM(env, "NewObject");
    }
    return obj;
}

static jmethodID GUID_M_getData4_0 = 0;
jbyteArray jcall_GUID_getData4(JNIEnv * env, jobject instance) {
    return (jbyteArray) (*env) -> CallObjectMethod(env, instance, GUID_M_getData4_0);
}

static jmethodID GUID_M_setData1_0 = 0;
void jcall_GUID_setData1(JNIEnv * env, jobject instance, jint p0) {
    (*env) -> CallVoidMethod(env, instance, GUID_M_setData1_0, p0);
}

static jmethodID GUID_C_1 = 0;
jobject jnew_GUID_1(JNIEnv * env, jstring p0) {
    jobject obj = (*env) -> NewObject(env, GUID, GUID_C_1, p0);
    if (obj == NULL) {
        throwOptOOM(env, "NewObject");
    }
    return obj;
}

static jmethodID GUID_M_setData3_0 = 0;
void jcall_GUID_setData3(JNIEnv * env, jobject instance, jshort p0) {
    (*env) -> CallVoidMethod(env, instance, GUID_M_setData3_0, p0);
}

static jmethodID GUID_M_setData4_0 = 0;
void jcall_GUID_setData4(JNIEnv * env, jobject instance, jbyteArray p0) {
    (*env) -> CallVoidMethod(env, instance, GUID_M_setData4_0, p0);
}


jboolean jstub_init(JNIEnv * env) {
    Exception = makeGlobalClassRef(env, "java/lang/Exception");
    if (Exception == 0) {
        return JNI_FALSE;
    }

    OutOfMemoryError = makeGlobalClassRef(env, "java/lang/OutOfMemoryError");
    if (OutOfMemoryError == 0) {
        return JNI_FALSE;
    }

    IllegalArgumentException = makeGlobalClassRef(env, "java/lang/IllegalArgumentException");
    if (IllegalArgumentException == 0) {
        return JNI_FALSE;
    }

    NullPointerException = makeGlobalClassRef(env, "java/lang/NullPointerException");
    if (NullPointerException == 0) {
        return JNI_FALSE;
    }

    IpAdapterAddresses = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses");
    if (IpAdapterAddresses == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses");
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

    IpAdapterAddresses_M_getTunnelType_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getTunnelType", "()I");
    if (IpAdapterAddresses_M_getTunnelType_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getTunnelType()I");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getDhcpv6Iaid_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getDhcpv6Iaid", "()J");
    if (IpAdapterAddresses_M_getDhcpv6Iaid_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getDhcpv6Iaid()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getNetworkGuid_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getNetworkGuid", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
    if (IpAdapterAddresses_M_getNetworkGuid_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getNetworkGuid()Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getDhcpv6Server_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getDhcpv6Server", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (IpAdapterAddresses_M_getDhcpv6Server_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getDhcpv6Server()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
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

    IpAdapterAddresses_C_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "<init>", "()V");
    if (IpAdapterAddresses_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.<init>()V");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getDhcpv6ClientDuid_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getDhcpv6ClientDuid", "()[B");
    if (IpAdapterAddresses_M_getDhcpv6ClientDuid_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getDhcpv6ClientDuid()[B");
        return JNI_FALSE;
    }

    IpAdapterAddresses_M_getZoneIndices_0 = (*env) -> GetMethodID(env, IpAdapterAddresses, "getZoneIndices", "()[J");
    if (IpAdapterAddresses_M_getZoneIndices_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses.getZoneIndices()[J");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress");
    if (IpAdapterAddresses$IpAdapterUnicastAddress == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress");
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

    IpAdapterAddresses$IpAdapterUnicastAddress_M_getOnLinkPrefixLength_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "getOnLinkPrefixLength", "()I");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_M_getOnLinkPrefixLength_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.getOnLinkPrefixLength()I");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_M_getLeaseLifetime_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "getLeaseLifetime", "()J");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_M_getLeaseLifetime_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.getLeaseLifetime()J");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_M_getAddress_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "getAddress", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_M_getAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.getAddress()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
        return JNI_FALSE;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_C_0 = (*env) -> GetMethodID(env, IpAdapterAddresses$IpAdapterUnicastAddress, "<init>", "()V");
    if (IpAdapterAddresses$IpAdapterUnicastAddress_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses$IpAdapterUnicastAddress.<init>()V");
        return JNI_FALSE;
    }

    Sockaddr = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr");
    if (Sockaddr == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr");
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

    Sockaddr_M_getAddressFamily_0 = (*env) -> GetMethodID(env, Sockaddr, "getAddressFamily", "()I");
    if (Sockaddr_M_getAddressFamily_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.getAddressFamily()I");
        return JNI_FALSE;
    }

    Sockaddr_M_clone_0 = (*env) -> GetMethodID(env, Sockaddr, "clone", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
    if (Sockaddr_M_clone_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.clone()Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;");
        return JNI_FALSE;
    }

    Sockaddr_M_clone_1 = (*env) -> GetMethodID(env, Sockaddr, "clone", "()Ljava/lang/Object;");
    if (Sockaddr_M_clone_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.clone()Ljava/lang/Object;");
        return JNI_FALSE;
    }

    Sockaddr_M_getAddress_0 = (*env) -> GetMethodID(env, Sockaddr, "getAddress", "()[B");
    if (Sockaddr_M_getAddress_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.getAddress()[B");
        return JNI_FALSE;
    }

    Sockaddr_C_0 = (*env) -> GetMethodID(env, Sockaddr, "<init>", "(I[B)V");
    if (Sockaddr_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.<init>(I[B)V");
        return JNI_FALSE;
    }

    Sockaddr_M_copyTo_0 = (*env) -> GetMethodID(env, Sockaddr, "copyTo", "(Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)V");
    if (Sockaddr_M_copyTo_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr.copyTo(Lio/github/alexanderschuetz97/nativeutils/api/structs/Sockaddr;)V");
        return JNI_FALSE;
    }

    GUID = makeGlobalClassRef(env, "io/github/alexanderschuetz97/nativeutils/api/structs/GUID");
    if (GUID == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID");
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

    GUID_M_getData1_0 = (*env) -> GetMethodID(env, GUID, "getData1", "()I");
    if (GUID_M_getData1_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.getData1()I");
        return JNI_FALSE;
    }

    GUID_M_clone_0 = (*env) -> GetMethodID(env, GUID, "clone", "()Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
    if (GUID_M_clone_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.clone()Lio/github/alexanderschuetz97/nativeutils/api/structs/GUID;");
        return JNI_FALSE;
    }

    GUID_M_clone_1 = (*env) -> GetMethodID(env, GUID, "clone", "()Ljava/lang/Object;");
    if (GUID_M_clone_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.clone()Ljava/lang/Object;");
        return JNI_FALSE;
    }

    GUID_M_toString_0 = (*env) -> GetMethodID(env, GUID, "toString", "()Ljava/lang/String;");
    if (GUID_M_toString_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.toString()Ljava/lang/String;");
        return JNI_FALSE;
    }

    GUID_M_getData3_0 = (*env) -> GetMethodID(env, GUID, "getData3", "()S");
    if (GUID_M_getData3_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.getData3()S");
        return JNI_FALSE;
    }

    GUID_C_0 = (*env) -> GetMethodID(env, GUID, "<init>", "()V");
    if (GUID_C_0 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.<init>()V");
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

    GUID_C_1 = (*env) -> GetMethodID(env, GUID, "<init>", "(Ljava/lang/String;)V");
    if (GUID_C_1 == 0) {
        (*env) -> ExceptionClear(env);
        (*env) -> ThrowNew(env, Exception, "cant find io/github/alexanderschuetz97/nativeutils/api/structs/GUID.<init>(Ljava/lang/String;)V");
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


    return JNI_TRUE;
}

void jstub_destroy(JNIEnv * env) {
    if (Exception != 0) {        (*env) -> DeleteGlobalRef(env, Exception);
        Exception = 0;
    }

    if (IpAdapterAddresses != 0) {        (*env) -> DeleteGlobalRef(env, IpAdapterAddresses);
        IpAdapterAddresses = 0;
    }

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
    IpAdapterAddresses_M_getTunnelType_0 = 0;
    IpAdapterAddresses_M_getDhcpv6Iaid_0 = 0;
    IpAdapterAddresses_M_getNetworkGuid_0 = 0;
    IpAdapterAddresses_M_getDhcpv6Server_0 = 0;
    IpAdapterAddresses_M_getFriendlyName_0 = 0;
    IpAdapterAddresses_M_getGatewayAddress_0 = 0;
    IpAdapterAddresses_C_0 = 0;
    IpAdapterAddresses_M_getDhcpv6ClientDuid_0 = 0;
    IpAdapterAddresses_M_getZoneIndices_0 = 0;
    if (IpAdapterAddresses$IpAdapterUnicastAddress != 0) {        (*env) -> DeleteGlobalRef(env, IpAdapterAddresses$IpAdapterUnicastAddress);
        IpAdapterAddresses$IpAdapterUnicastAddress = 0;
    }

    IpAdapterAddresses$IpAdapterUnicastAddress_Address = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_DadState = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_M_getOnLinkPrefixLength_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_M_getLeaseLifetime_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_M_getAddress_0 = 0;
    IpAdapterAddresses$IpAdapterUnicastAddress_C_0 = 0;
    if (Sockaddr != 0) {        (*env) -> DeleteGlobalRef(env, Sockaddr);
        Sockaddr = 0;
    }

    Sockaddr_EMPTY = 0;
    Sockaddr_addressFamily = 0;
    Sockaddr_address = 0;
    Sockaddr_M_getAddressFamily_0 = 0;
    Sockaddr_M_clone_0 = 0;
    Sockaddr_M_clone_1 = 0;
    Sockaddr_M_getAddress_0 = 0;
    Sockaddr_C_0 = 0;
    Sockaddr_M_copyTo_0 = 0;
    if (GUID != 0) {        (*env) -> DeleteGlobalRef(env, GUID);
        GUID = 0;
    }

    GUID_data1 = 0;
    GUID_data2 = 0;
    GUID_data3 = 0;
    GUID_data4 = 0;
    GUID_M_getData1_0 = 0;
    GUID_M_clone_0 = 0;
    GUID_M_clone_1 = 0;
    GUID_M_toString_0 = 0;
    GUID_M_getData3_0 = 0;
    GUID_C_0 = 0;
    GUID_M_getData4_0 = 0;
    GUID_M_setData1_0 = 0;
    GUID_C_1 = 0;
    GUID_M_setData3_0 = 0;
    GUID_M_setData4_0 = 0;

}

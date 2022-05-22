//THIS FILE IS MACHINE GENERATED, DO NOT EDIT
#include <jni.h>
#include <stddef.h>

/**
 * initializes the stubbing. Must be called once when your library loads. 
 * returns true if initialization succeeds. If this method returns false then an exception is pending in the JNIEnv that explains the error.
 * it is recommended to call this method in your JNI_OnLoad method
*/
jboolean jstub_init(JNIEnv * env);

/**
 * destroys the stubbing. You can safely call jstub_init() again afterwards. 
 * it is recommended to call this method in your JNI_OnUnload method
*/
void jstub_destroy(JNIEnv * env);

/**
 * equivalent to (*env)->ExceptionCheck(env) just much shorter to write.
 */
jboolean jerr(JNIEnv * env);

/**
 * Creates a new byte array of the given length and copies the give buffer into it.
 * Return NULL when array creation fails. In this case a java exception is thrown.
 */
jbyteArray jarrayB(JNIEnv * env, jbyte * buffer, jsize len);

void jset_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance, jstring value);
void jsetC_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance, char * value);
void jsetWC_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance, wchar_t * value);
jstring jget_IpAdapterAddresses_AdapterName(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_UnicastAddress(JNIEnv * env, jobject instance, jobject value);
jobject jget_IpAdapterAddresses_UnicastAddress(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_AnycastAddress(JNIEnv * env, jobject instance, jobject value);
jobject jget_IpAdapterAddresses_AnycastAddress(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_MulticastAddress(JNIEnv * env, jobject instance, jobject value);
jobject jget_IpAdapterAddresses_MulticastAddress(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_DnsServerAddress(JNIEnv * env, jobject instance, jobject value);
jobject jget_IpAdapterAddresses_DnsServerAddress(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance, jstring value);
void jsetC_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance, char * value);
void jsetWC_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance, wchar_t * value);
jstring jget_IpAdapterAddresses_DnsSuffix(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Description(JNIEnv * env, jobject instance, jstring value);
void jsetC_IpAdapterAddresses_Description(JNIEnv * env, jobject instance, char * value);
void jsetWC_IpAdapterAddresses_Description(JNIEnv * env, jobject instance, wchar_t * value);
jstring jget_IpAdapterAddresses_Description(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance, jstring value);
void jsetC_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance, char * value);
void jsetWC_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance, wchar_t * value);
jstring jget_IpAdapterAddresses_FriendlyName(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_PhysicalAddress(JNIEnv * env, jobject instance, jbyteArray value);
void jsetA_IpAdapterAddresses_PhysicalAddress(JNIEnv * env, jobject instance, jbyte * value, jsize len);
jbyteArray jget_IpAdapterAddresses_PhysicalAddress(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Mtu(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_Mtu(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_IfType(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_IfType(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_OperStatus(JNIEnv * env, jobject instance, jint value);
jint jget_IpAdapterAddresses_OperStatus(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Ipv6IfIndex(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_Ipv6IfIndex(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_ZoneIndices(JNIEnv * env, jobject instance, jlongArray value);
void jsetA_IpAdapterAddresses_ZoneIndices(JNIEnv * env, jobject instance, jlong * value, jsize len);
jlongArray jget_IpAdapterAddresses_ZoneIndices(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Prefix(JNIEnv * env, jobject instance, jobject value);
jobject jget_IpAdapterAddresses_Prefix(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_TransmitLinkSpeed(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_TransmitLinkSpeed(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_ReceiveLinkSpeed(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_ReceiveLinkSpeed(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_WinsServerAddress(JNIEnv * env, jobject instance, jobject value);
jobject jget_IpAdapterAddresses_WinsServerAddress(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_GatewayAddress(JNIEnv * env, jobject instance, jobject value);
jobject jget_IpAdapterAddresses_GatewayAddress(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Ipv4Metric(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_Ipv4Metric(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Ipv6Metric(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_Ipv6Metric(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Luid_Value(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_Luid_Value(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Luid_NetLuidIndex(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_Luid_NetLuidIndex(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Luid_IfType(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_Luid_IfType(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Dhcpv4Server(JNIEnv * env, jobject instance, jobject value);
jobject jget_IpAdapterAddresses_Dhcpv4Server(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_CompartmentId(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_CompartmentId(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_NetworkGuid(JNIEnv * env, jobject instance, jobject value);
jobject jget_IpAdapterAddresses_NetworkGuid(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_ConnectionType(JNIEnv * env, jobject instance, jint value);
jint jget_IpAdapterAddresses_ConnectionType(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_TunnelType(JNIEnv * env, jobject instance, jint value);
jint jget_IpAdapterAddresses_TunnelType(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Dhcpv6Server(JNIEnv * env, jobject instance, jobject value);
jobject jget_IpAdapterAddresses_Dhcpv6Server(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Dhcpv6ClientDuid(JNIEnv * env, jobject instance, jbyteArray value);
void jsetA_IpAdapterAddresses_Dhcpv6ClientDuid(JNIEnv * env, jobject instance, jbyte * value, jsize len);
jbyteArray jget_IpAdapterAddresses_Dhcpv6ClientDuid(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses_Dhcpv6Iaid(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses_Dhcpv6Iaid(JNIEnv * env, jobject instance);
jint jcall_IpAdapterAddresses_getTunnelType(JNIEnv * env, jobject instance);
jlong jcall_IpAdapterAddresses_getDhcpv6Iaid(JNIEnv * env, jobject instance);
jobject jcall_IpAdapterAddresses_getNetworkGuid(JNIEnv * env, jobject instance);
jobject jcall_IpAdapterAddresses_getDhcpv6Server(JNIEnv * env, jobject instance);
jstring jcall_IpAdapterAddresses_getFriendlyName(JNIEnv * env, jobject instance);
jobject jcall_IpAdapterAddresses_getGatewayAddress(JNIEnv * env, jobject instance);
jobject jnew_IpAdapterAddresses(JNIEnv * env);
jbyteArray jcall_IpAdapterAddresses_getDhcpv6ClientDuid(JNIEnv * env, jobject instance);
jlongArray jcall_IpAdapterAddresses_getZoneIndices(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_Address(JNIEnv * env, jobject instance, jobject value);
jobject jget_IpAdapterAddresses$IpAdapterUnicastAddress_Address(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin(JNIEnv * env, jobject instance, jint value);
jint jget_IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin(JNIEnv * env, jobject instance, jint value);
jint jget_IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_DadState(JNIEnv * env, jobject instance, jint value);
jint jget_IpAdapterAddresses$IpAdapterUnicastAddress_DadState(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime(JNIEnv * env, jobject instance, jlong value);
jlong jget_IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime(JNIEnv * env, jobject instance);
void jset_IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength(JNIEnv * env, jobject instance, jint value);
jint jget_IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength(JNIEnv * env, jobject instance);
jint jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getOnLinkPrefixLength(JNIEnv * env, jobject instance);
jlong jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getLeaseLifetime(JNIEnv * env, jobject instance);
jobject jcall_IpAdapterAddresses$IpAdapterUnicastAddress_getAddress(JNIEnv * env, jobject instance);
jobject jnew_IpAdapterAddresses$IpAdapterUnicastAddress(JNIEnv * env);
void jset_Sockaddr_EMPTY(JNIEnv * env, jbyteArray value);
jbyteArray jget_Sockaddr_EMPTY(JNIEnv * env);
void jset_Sockaddr_addressFamily(JNIEnv * env, jobject instance, jint value);
jint jget_Sockaddr_addressFamily(JNIEnv * env, jobject instance);
void jset_Sockaddr_address(JNIEnv * env, jobject instance, jbyteArray value);
void jsetA_Sockaddr_address(JNIEnv * env, jobject instance, jbyte * value, jsize len);
jbyteArray jget_Sockaddr_address(JNIEnv * env, jobject instance);
jint jcall_Sockaddr_getAddressFamily(JNIEnv * env, jobject instance);
jobject jcall_Sockaddr_clone(JNIEnv * env, jobject instance);
jobject jcall_Sockaddr_clone_1(JNIEnv * env, jobject instance);
jbyteArray jcall_Sockaddr_getAddress(JNIEnv * env, jobject instance);
jobject jnew_Sockaddr(JNIEnv * env, jint p0, jbyteArray p1);
void jcall_Sockaddr_copyTo(JNIEnv * env, jobject instance, jobject p0);
void jset_GUID_data1(JNIEnv * env, jobject instance, jint value);
jint jget_GUID_data1(JNIEnv * env, jobject instance);
void jset_GUID_data2(JNIEnv * env, jobject instance, jshort value);
jshort jget_GUID_data2(JNIEnv * env, jobject instance);
void jset_GUID_data3(JNIEnv * env, jobject instance, jshort value);
jshort jget_GUID_data3(JNIEnv * env, jobject instance);
void jset_GUID_data4(JNIEnv * env, jobject instance, jbyteArray value);
void jsetA_GUID_data4(JNIEnv * env, jobject instance, jbyte * value, jsize len);
jbyteArray jget_GUID_data4(JNIEnv * env, jobject instance);
jint jcall_GUID_getData1(JNIEnv * env, jobject instance);
jobject jcall_GUID_clone(JNIEnv * env, jobject instance);
jobject jcall_GUID_clone_1(JNIEnv * env, jobject instance);
jstring jcall_GUID_toString(JNIEnv * env, jobject instance);
jshort jcall_GUID_getData3(JNIEnv * env, jobject instance);
jobject jnew_GUID(JNIEnv * env);
jbyteArray jcall_GUID_getData4(JNIEnv * env, jobject instance);
void jcall_GUID_setData1(JNIEnv * env, jobject instance, jint p0);
jobject jnew_GUID_1(JNIEnv * env, jstring p0);
void jcall_GUID_setData3(JNIEnv * env, jobject instance, jshort p0);
void jcall_GUID_setData4(JNIEnv * env, jobject instance, jbyteArray p0);

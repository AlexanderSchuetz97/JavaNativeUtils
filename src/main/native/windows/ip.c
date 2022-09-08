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


#include <iphlpapi.h>
#include <errhandlingapi.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFriendlyIfIndex
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetFriendlyIfIndex
  (JNIEnv * env, jobject inst, jlong idx) {
	return GetFriendlyIfIndex(idx);
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetAdapterIndex
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetAdapterIndex
  (JNIEnv * env, jobject inst, jstring name) {
	ULONG idx = 0;

	if (name == NULL) {
		jthrowCC_NullPointerException_1(env, "name");
		return 0;

	}

	wchar_t * ptr = toWCharsMalloc(env, name);
	if (ptr == NULL) {
		return 0;
	}
	LPWSTR l = (LPWSTR) ptr;

	DWORD ret = GetAdapterIndex(l, &idx);
	free((void*)ptr);
	if (ret == NO_ERROR) {
		return idx;
	}

	jthrow_UnknownNativeErrorException_1(env, ret);
	return 0;
}

bool mapSockAddress(JNIEnv * env, void * ptr, jobject jcollection) {
	PIP_ADAPTER_ANYCAST_ADDRESS_XP current = (PIP_ADAPTER_ANYCAST_ADDRESS_XP) ptr;
	while (current != NULL) {
		if (current->Address.lpSockaddr != NULL) {
			jbyteArray array = jarrayB(env, (jbyte*) current->Address.lpSockaddr, current->Address.iSockaddrLength);
			if (array == NULL) {
				return false;
			}

			jobject jCurrent = jnew_Sockaddr_1(env, current->Address.lpSockaddr->sa_family, array);
			if (jerr(env)) {
				return false;
			}

			if (!jcall_Collection_add(env, jcollection, jCurrent)) {
				return false;
			}
		}


		current = current->Next;
	}

	return true;
}

bool mapUniSockAddress(JNIEnv * env, PIP_ADAPTER_UNICAST_ADDRESS_LH current, jobject jcollection) {
	while (current != NULL) {
		if (current->Address.lpSockaddr != NULL) {
			jbyteArray array = jarrayB(env, (jbyte*) current->Address.lpSockaddr, current->Address.iSockaddrLength);
			if (array == NULL) {
				return false;
			}

			jobject jSockAddr = jnew_Sockaddr_1(env, current->Address.lpSockaddr->sa_family, array);
			if (jerr(env)) {
				return false;
			}

			jobject jip = jnew_IpAdapterAddresses$IpAdapterUnicastAddress(env);
			jset_IpAdapterAddresses$IpAdapterUnicastAddress_Address(env, jip, jSockAddr);
			jset_IpAdapterAddresses$IpAdapterUnicastAddress_PrefixOrigin(env, jip, current->PrefixOrigin);
			jset_IpAdapterAddresses$IpAdapterUnicastAddress_SuffixOrigin(env, jip, current->SuffixOrigin);
			jset_IpAdapterAddresses$IpAdapterUnicastAddress_DadState(env, jip, current->DadState);
			jset_IpAdapterAddresses$IpAdapterUnicastAddress_ValidLifetime(env, jip, current->ValidLifetime);
			jset_IpAdapterAddresses$IpAdapterUnicastAddress_PreferredLifetime(env, jip, current->PreferredLifetime);
			jset_IpAdapterAddresses$IpAdapterUnicastAddress_LeaseLifetime(env, jip, current->LeaseLifetime);
			jset_IpAdapterAddresses$IpAdapterUnicastAddress_OnLinkPrefixLength(env, jip, current->OnLinkPrefixLength);

			if (!jcall_Collection_add(env, jcollection, jip)) {
				return false;
			}
		}


		current = current->Next;
	}

	return true;
}

/*
 * Class:     io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetAdaptersAddresses
 * Signature: (JJ)Lio/github/alexanderschuetz97/nativeutils/api/structs/IpAdapterAddresses;
 */
JNIEXPORT jobject JNICALL Java_io_github_alexanderschuetz97_nativeutils_impl_JNIWindowsNativeUtil_GetAdaptersAddresses
  (JNIEnv * env, jobject inst, jlong family, jlong flags) {
	ULONG size = 320000;
	int i = 10;
	PIP_ADAPTER_ADDRESSES_LH pip = NULL;
	while(true) {
		if (i-- <= 0) {
			jthrow_UnknownNativeErrorException_1(env, ERROR_BUFFER_OVERFLOW);
			return NULL;
		}

		pip = (PIP_ADAPTER_ADDRESSES_LH) malloc(size);
		memset((void*) pip, 0, size);
		DWORD retval = GetAdaptersAddresses((ULONG)family, (ULONG) flags, NULL, (void*) pip, &size);
		if (retval == ERROR_BUFFER_OVERFLOW) {
			free(pip);
			continue;
		}

		if (retval != NO_ERROR) {
			free(pip);
			jthrow_UnknownNativeErrorException_1(env, retval);
			return NULL;
		}

		break;
	}


	jobject jret = jnew_ArrayList(env);
	if (jret == NULL) {
		goto errorCleanup;
	}

	while(pip != NULL) {
		jobject jstruct = jnew_IpAdapterAddresses(env);
		if (jstruct == NULL) {
			goto errorCleanup;
		}

		jcall_Collection_add(env, jret, jstruct);

		jsetC_IpAdapterAddresses_AdapterName(env, jstruct, pip->AdapterName);
		if (jerr(env)) {
			goto errorCleanup;
		}

		jsetWC_IpAdapterAddresses_DnsSuffix(env, jstruct, pip->DnsSuffix);
		if (jerr(env)) {
			goto errorCleanup;
		}

		jsetWC_IpAdapterAddresses_Description(env, jstruct, pip->Description);
		if (jerr(env)) {
			goto errorCleanup;
		}

		jsetWC_IpAdapterAddresses_FriendlyName(env, jstruct, pip->FriendlyName);
		if (jerr(env)) {
			goto errorCleanup;
		}

		jsetA_IpAdapterAddresses_PhysicalAddress(env, jstruct, pip->PhysicalAddress, MAX_ADAPTER_ADDRESS_LENGTH);
		if (jerr(env)) {
			goto errorCleanup;
		}

		jset_IpAdapterAddresses_Mtu(env, jstruct, pip->Mtu);

		jset_IpAdapterAddresses_IfType(env, jstruct, pip->IfType);

		jset_IpAdapterAddresses_OperStatus(env, jstruct, pip->OperStatus);

		jset_IpAdapterAddresses_Ipv6IfIndex(env, jstruct, pip->Ipv6IfIndex);


		jlong jZoneIndices[16];
		for (int i = 0; i < 16; i++) {
			jZoneIndices[i] = (jlong) pip->ZoneIndices[i];
		}

		jsetA_IpAdapterAddresses_ZoneIndices(env, jstruct, jZoneIndices, 16);
		if (jerr(env)) {
			goto errorCleanup;
		}

		jset_IpAdapterAddresses_TransmitLinkSpeed(env, jstruct, pip->TransmitLinkSpeed);

		jset_IpAdapterAddresses_ReceiveLinkSpeed(env, jstruct, pip->ReceiveLinkSpeed);

		jset_IpAdapterAddresses_Ipv4Metric(env, jstruct, pip->Ipv4Metric);

		jset_IpAdapterAddresses_Ipv6Metric(env, jstruct, pip->Ipv6Metric);

		jset_IpAdapterAddresses_Luid_Value(env, jstruct, pip->Luid.Value);

		jset_IpAdapterAddresses_Luid_NetLuidIndex(env, jstruct, pip->Luid.Info.NetLuidIndex);

		jset_IpAdapterAddresses_Luid_IfType(env, jstruct, pip->Luid.Info.IfType);

		jset_IpAdapterAddresses_CompartmentId(env, jstruct, pip->CompartmentId);

		jset_IpAdapterAddresses_ConnectionType(env, jstruct, pip->ConnectionType);

		jset_IpAdapterAddresses_TunnelType(env, jstruct, pip->TunnelType);

		jsetA_IpAdapterAddresses_Dhcpv6ClientDuid(env, jstruct, pip->Dhcpv6ClientDuid, MAX_DHCPV6_DUID_LENGTH);
		if (jerr(env)) {
			jthrowCC_OutOfMemoryError_1(env, "jsetA_IpAdapterAddresses_Dhcpv6ClientDuid");
			goto errorCleanup;
		}

		jset_IpAdapterAddresses_Dhcpv6Iaid(env, jstruct, pip->Dhcpv6Iaid);

		jobject NetworkGuid = jnew_GUID(env);
		if (NetworkGuid == NULL) {
			goto errorCleanup;
		}

		jset_GUID_data1(env, NetworkGuid, pip->NetworkGuid.Data1);
		jset_GUID_data2(env, NetworkGuid, pip->NetworkGuid.Data2);
		jset_GUID_data3(env, NetworkGuid, pip->NetworkGuid.Data3);
		jsetA_GUID_data4(env, NetworkGuid, pip->NetworkGuid.Data4, 8);
		if (jerr(env)) {
			goto errorCleanup;
		}

		jset_IpAdapterAddresses_NetworkGuid(env, jstruct, NetworkGuid);

		if (pip->Dhcpv4Server.lpSockaddr != NULL) {
			jbyteArray array = jarrayB(env, (jbyte*) pip->Dhcpv4Server.lpSockaddr, pip->Dhcpv4Server.iSockaddrLength);
			if (array == NULL) {
				goto errorCleanup;
			}

			jobject Dhcpv4Server = jnew_Sockaddr_1(env, pip->Dhcpv4Server.lpSockaddr->sa_family, array);
			if (jerr(env)) {
				goto errorCleanup;
			}

			jset_IpAdapterAddresses_Dhcpv4Server(env, jstruct, Dhcpv4Server);
		}

		if (!mapSockAddress(env, (void*)pip->FirstAnycastAddress, jget_IpAdapterAddresses_AnycastAddress(env, jstruct))) {
			goto errorCleanup;
		}

		if (!mapSockAddress(env, (void*)pip->FirstMulticastAddress, jget_IpAdapterAddresses_MulticastAddress(env, jstruct))) {
			goto errorCleanup;
		}

		if (!mapSockAddress(env, (void*)pip->FirstDnsServerAddress, jget_IpAdapterAddresses_DnsServerAddress(env, jstruct))) {
			goto errorCleanup;
		}

		if (!mapSockAddress(env, (void*)pip->FirstWinsServerAddress, jget_IpAdapterAddresses_WinsServerAddress(env, jstruct))) {
			goto errorCleanup;
		}

		if (!mapSockAddress(env, (void*)pip->FirstGatewayAddress, jget_IpAdapterAddresses_GatewayAddress(env, jstruct))) {
			goto errorCleanup;
		}

		if (!mapUniSockAddress(env, pip->FirstUnicastAddress, jget_IpAdapterAddresses_UnicastAddress(env, jstruct))) {
			goto errorCleanup;
		}

		pip = pip->Next;
	}


	goto cleanup;

	errorCleanup:
	if (!jerr(env)) {
		jthrowCC_IllegalStateException_1(env, "no error in errorCleanup");
	}
	jret = NULL;

	cleanup:
	free(pip);
	return jret;


}

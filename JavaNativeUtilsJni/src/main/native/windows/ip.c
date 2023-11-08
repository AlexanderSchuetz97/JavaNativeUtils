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

#include <ws2ipdef.h>
#include <iphlpapi.h>
//#define _WS2IPDEF_
#include <netioapi.h>
#include <errhandlingapi.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetFriendlyIfIndex
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetFriendlyIfIndex
  (JNIEnv * env, jobject inst, jlong idx) {
	return GetFriendlyIfIndex(idx);
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetAdapterIndex
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetAdapterIndex
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
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetAdaptersAddresses
 * Signature: (JJ)Leu/aschuetz/nativeutils/api/structs/IpAdapterAddresses;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetAdaptersAddresses
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

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    GetIpForwardTable2
 * Signature: (I)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_GetIpForwardTable2
  (JNIEnv * env, jobject inst, jint Family) {

	PMIB_IPFORWARD_TABLE2 mibTable = NULL;

	DWORD result = GetIpForwardTable2(Family, &mibTable);

	if (result != NO_ERROR) {
		switch(result) {
		case(ERROR_INVALID_PARAMETER):
				jthrowCC_IllegalArgumentException_1(env, "Invalid address family");
				return NULL;
		case(ERROR_NOT_ENOUGH_MEMORY):
				jthrowCC_OutOfMemoryError_1(env, "Not enough memory to allocate MIB_IPFORWARD_TABLE2");
				return NULL;
		case(ERROR_NOT_FOUND):
				return jnew_ArrayList(env);
		case(ERROR_NOT_SUPPORTED):
				jthrowCC_UnsupportedOperationException_1(env, "Address family not supported on this computer because windows is missing the network stack for the desired address family.");
				return NULL;
		default:
			jthrow_UnknownNativeErrorException_1(env, (jlong) result);
			return NULL;
		}
	}

	if (mibTable == NULL) {
		jthrowC_NullPointerException_1(env, "GetIpForwardTable2 failed fill MIB_IPFORWARD_TABLE2 with a valid value.");
		return NULL;
	}

	jobject theList = jnew_ArrayList(env);
	if (jerr(env)) {
		goto cleanup;
	}


	for (ULONG idx = 0; idx < mibTable->NumEntries; idx++) {
		PMIB_IPFORWARD_ROW2 mibRow = &mibTable->Table[idx];
		jbyteArray array;

		if (mibRow->DestinationPrefix.Prefix.si_family == AF_INET) {
			array = jarrayB(env, (jbyte*) &mibRow->DestinationPrefix.Prefix.Ipv4, sizeof(SOCKADDR_IN));
		} else if (mibRow->DestinationPrefix.Prefix.si_family == AF_INET6) {
			array = jarrayB(env, (jbyte*) &mibRow->DestinationPrefix.Prefix.Ipv6, sizeof(SOCKADDR_IN6));
		} else {
			jthrowCC_IllegalStateException_1(env, "MIB_IPFORWARD_ROW2 contains invalid address family");
			goto cleanup;
		}

		if (jerr(env)) {
			goto cleanup;
		}


		jobject jDestinationPrefixAddress = jnew_Sockaddr_1(env, mibRow->DestinationPrefix.Prefix.si_family, array);
		if (jerr(env)) {
			goto cleanup;
		}


		(*env)->DeleteLocalRef(env, array);

		if (mibRow->NextHop.si_family == AF_INET) {
			array = jarrayB(env, (jbyte*) &mibRow->NextHop.Ipv4, sizeof(SOCKADDR_IN));
		} else if (mibRow->DestinationPrefix.Prefix.si_family == AF_INET6) {
			array = jarrayB(env, (jbyte*) &mibRow->NextHop.Ipv6, sizeof(SOCKADDR_IN6));
		} else {
			jthrowCC_IllegalStateException_1(env, "MIB_IPFORWARD_ROW2 contains invalid address family");
			goto cleanup;
		}

		jobject jNextHop = jnew_Sockaddr_1(env, mibRow->NextHop.si_family, array);
		if (jerr(env)) {
			goto cleanup;
		}


		jobject jmib = jnew_MibIpForwardRow2(env);
		if (jerr(env)) {
			goto cleanup;
		}

		jcall_ArrayList_add_1(env, theList, jmib);
		if (jerr(env)) {
			goto cleanup;
		}

		jset_MibIpForwardRow2_InterfaceLuid(env, jmib, mibRow->InterfaceLuid.Value);
		jset_MibIpForwardRow2_InterfaceIndex(env, jmib, mibRow->InterfaceIndex);
		jset_MibIpForwardRow2_DestinationPrefixLength(env, jmib, mibRow->DestinationPrefix.PrefixLength);
		jset_MibIpForwardRow2_DestinationPrefixAddress(env, jmib, jDestinationPrefixAddress);
		jset_MibIpForwardRow2_NextHop(env, jmib, jNextHop);
		jset_MibIpForwardRow2_SitePrefixLength(env, jmib, mibRow->SitePrefixLength);
		jset_MibIpForwardRow2_ValidLifetime(env, jmib, mibRow->ValidLifetime);
		jset_MibIpForwardRow2_PreferredLifetime(env, jmib, mibRow->PreferredLifetime);
		jset_MibIpForwardRow2_Metric(env, jmib, mibRow->Metric);
		jset_MibIpForwardRow2_Protocol(env, jmib, mibRow->Protocol);
		jset_MibIpForwardRow2_Loopback(env, jmib, mibRow->Loopback);
		jset_MibIpForwardRow2_AutoconfigureAddress(env, jmib, mibRow->AutoconfigureAddress);
		jset_MibIpForwardRow2_Publish(env, jmib, mibRow->Publish);
		jset_MibIpForwardRow2_Immortal(env, jmib, mibRow->Immortal);
		jset_MibIpForwardRow2_Age(env, jmib, mibRow->Age);
		jset_MibIpForwardRow2_Origin(env, jmib, mibRow->Origin);

		(*env)->DeleteLocalRef(env, jmib);
		(*env)->DeleteLocalRef(env, array);
		(*env)->DeleteLocalRef(env, jNextHop);
		(*env)->DeleteLocalRef(env, jDestinationPrefixAddress);
	}


	FreeMibTable(mibTable);
	return theList;

	cleanup:
	FreeMibTable(mibTable);
	return NULL;
}

bool mapMIB(JNIEnv * env, jobject jmib, MIB_IPFORWARD_ROW2 * mibRow) {
    if (jmib == NULL) {
        jthrowCC_NullPointerException_1(env, "MibIpForwardRow2 is null");
        return false;
    }

    jobject jDestinationPrefix = jget_MibIpForwardRow2_DestinationPrefixAddress(env, jmib);
    if (jDestinationPrefix == NULL) {
        jthrowCC_NullPointerException_1(env, "MibIpForwardRow2.DestinationPrefixAddress is null");
        return false;
    }

    jbyteArray jDestinationPrefixBytes = jget_Sockaddr_address(env, jDestinationPrefix);
    if (jDestinationPrefixBytes == NULL) {
        jthrowCC_NullPointerException_1(env, "MibIpForwardRow2.DestinationPrefixAddress.address is null");
        return false;
    }

    (*env)->DeleteLocalRef(env, jDestinationPrefix);


    if ((*env)->GetArrayLength(env, jDestinationPrefixBytes) != sizeof(SOCKADDR_INET)) {
        jthrowCC_IllegalArgumentException_1(env, "MibIpForwardRow2.DestinationPrefixAddress.address does not have the same size as SOCKADDR_INET");
        return false;
    }


    jobject jNextHop = jget_MibIpForwardRow2_NextHop(env, jmib);
    if (jNextHop == NULL) {
        jthrowCC_NullPointerException_1(env, "MibIpForwardRow2.NextHop is null");
        return false;
    }

    jbyteArray jNextHopBytes = jget_Sockaddr_address(env, jNextHop);
    if (jDestinationPrefixBytes == NULL) {
        jthrowCC_NullPointerException_1(env, "MibIpForwardRow2.NextHop.address is null");
        return false;
    }

    (*env)->DeleteLocalRef(env, jNextHop);

    if ((*env)->GetArrayLength(env, jNextHopBytes) != sizeof(SOCKADDR_INET)) {
        jthrowCC_IllegalArgumentException_1(env, "MibIpForwardRow2.NextHop.address does not have the same size as SOCKADDR_INET");
        return false;
    }

    memset((void*) mibRow, 0, sizeof(MIB_IPFORWARD_ROW2));

    (*env)->GetByteArrayRegion(env, jDestinationPrefixBytes, 0, sizeof(SOCKADDR_INET), (jbyte*) &mibRow->DestinationPrefix.Prefix);
    (*env)->GetByteArrayRegion(env, jNextHopBytes, 0, sizeof(SOCKADDR_INET), (jbyte*) &mibRow->NextHop);
    (*env)->DeleteLocalRef(env, jDestinationPrefixBytes);
    (*env)->DeleteLocalRef(env, jNextHopBytes);

    mibRow->InterfaceLuid.Value = jget_MibIpForwardRow2_InterfaceLuid(env, jmib);
    mibRow->InterfaceIndex = jget_MibIpForwardRow2_InterfaceIndex(env, jmib);
    mibRow->DestinationPrefix.PrefixLength = jget_MibIpForwardRow2_DestinationPrefixLength(env, jmib);
    mibRow->SitePrefixLength = jget_MibIpForwardRow2_SitePrefixLength(env, jmib);
    mibRow->ValidLifetime = jget_MibIpForwardRow2_ValidLifetime(env, jmib);
    mibRow->PreferredLifetime = jget_MibIpForwardRow2_PreferredLifetime(env, jmib);
    mibRow->Metric = jget_MibIpForwardRow2_Metric(env, jmib);
    mibRow->Protocol = jget_MibIpForwardRow2_Protocol(env, jmib);
    mibRow->Loopback = jget_MibIpForwardRow2_Loopback(env, jmib);
    mibRow->AutoconfigureAddress = jget_MibIpForwardRow2_AutoconfigureAddress(env, jmib);
    mibRow->Publish = jget_MibIpForwardRow2_Publish(env, jmib);
    mibRow->Immortal = jget_MibIpForwardRow2_Immortal(env, jmib);
    mibRow->Age = jget_MibIpForwardRow2_Age(env, jmib);
    mibRow->Origin = jget_MibIpForwardRow2_Origin(env, jmib);

    return true;
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    CreateIpForwardEntry2
 * Signature: (Leu/aschuetz/nativeutils/api/structs/MibIpForwardRow2;)V
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_CreateIpForwardEntry2
  (JNIEnv * env, jobject inst, jobject jmib) {
    MIB_IPFORWARD_ROW2 mibRow;
    if (!mapMIB(env, jmib, &mibRow)) {
        return false;
    }

	DWORD result = CreateIpForwardEntry2((const MIB_IPFORWARD_ROW2*) &mibRow);

	switch(result) {
	case(NO_ERROR):
		return true;
	case(ERROR_ACCESS_DENIED):
		jthrowCC_AccessDeniedException(env, "Access Denied");
		return false;
	case(ERROR_INVALID_PARAMETER):
		jthrowCC_IllegalArgumentException_1(env, "MibIpForwardRow2 contains invalid data");
		return false;
	case(ERROR_NOT_FOUND):
		jthrowCC_NoSuchElementException_1(env, "Network interface not found");
		return false;
	case(ERROR_NOT_SUPPORTED):
		jthrowCC_UnsupportedOperationException_1(env, "Windows is missing the network stack to perform the request");
		return false;
	case(ERROR_OBJECT_ALREADY_EXISTS):
		return false;
	default:
		jthrow_UnknownNativeErrorException_1(env, result);
		return false;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    DeleteIpForwardEntry2
 * Signature: (Leu/aschuetz/nativeutils/api/structs/MibIpForwardRow2;)Z
 */
JNIEXPORT jboolean JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_DeleteIpForwardEntry2
        (JNIEnv * env, jobject inst, jobject jmib) {
    MIB_IPFORWARD_ROW2 mibRow;
    if (!mapMIB(env, jmib, &mibRow)) {
        return false;
    }

    DWORD result = DeleteIpForwardEntry2((const MIB_IPFORWARD_ROW2*) &mibRow);

    switch(result) {
        case(NO_ERROR):
            return true;
        case(ERROR_ACCESS_DENIED):
            jthrowCC_AccessDeniedException(env, "Access Denied");
            return false;
        case(ERROR_INVALID_PARAMETER):
            jthrowCC_IllegalArgumentException_1(env, "MibIpForwardRow2 contains invalid data");
            return false;
        case(ERROR_NOT_FOUND):
            return false;
        case(ERROR_NOT_SUPPORTED):
            jthrowCC_UnsupportedOperationException_1(env, "Windows is missing the network stack to perform the request");
            return false;
        case(ERROR_OBJECT_ALREADY_EXISTS):
            return false;
        default:
            jthrow_UnknownNativeErrorException_1(env, result);
            return false;
    }
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConvertInterfaceIndexToLuid
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConvertInterfaceIndexToLuid
  (JNIEnv * env, jobject inst, jint idx) {
	NET_LUID luid;
	NETIO_STATUS status = ConvertInterfaceIndexToLuid((NET_IFINDEX) idx, &luid);
	switch(status) {
	case(NO_ERROR):
		return (jlong) luid.Value;
	case(ERROR_FILE_NOT_FOUND):
		jthrowCC_NoSuchElementException_1(env, "interface not found");
		return 0;
	case(ERROR_INVALID_PARAMETER):
		jthrowCC_IllegalArgumentException_1(env, "interface index is invalid");
		return 0;
	default:
		jthrow_UnknownNativeErrorException_1(env, (jlong) status);
		return 0;
	}
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConvertInterfaceLuidToNameA
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConvertInterfaceLuidToNameA
        (JNIEnv * env, jobject inst, jlong luid) {

    NET_LUID cluid;
    cluid.Value = (ULONG64) luid;

    char name[NDIS_IF_MAX_STRING_SIZE + 2];
    name[NDIS_IF_MAX_STRING_SIZE+1] = 0;

    DWORD result = ConvertInterfaceLuidToNameA((CONST NET_LUID *)&cluid, name, NDIS_IF_MAX_STRING_SIZE+1);

    switch (result) {
        case 0: {
            jstring str = (*env)->NewStringUTF(env, (const char*) name);
            if (str == NULL) {
                jthrowCC_OutOfMemoryError_1(env, "NewStringUTF");
            }
            return str;
        }
        case ERROR_INVALID_PARAMETER:
            jthrowCC_NoSuchElementException_1(env, "InterfaceLuid not found");
            return NULL;
        case ERROR_NOT_ENOUGH_MEMORY:
            jthrowCC_IllegalStateException_1(env, "ConvertInterfaceLuidToNameA reports ERROR_NOT_ENOUGH_MEMORY but a buffer with NDIS_IF_MAX_STRING_SIZE + 1 was supplied. This should not be possible.");
            return NULL;
        default:
            jthrow_UnknownNativeErrorException_1(env, result);
            return NULL;
    }
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConvertInterfaceLuidToAlias
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConvertInterfaceLuidToAlias
        (JNIEnv * env, jobject inst, jlong luid) {

    NET_LUID cluid;
    cluid.Value = (ULONG64) luid;

    wchar_t name[NDIS_IF_MAX_STRING_SIZE + 2];
    name[NDIS_IF_MAX_STRING_SIZE+1] = 0;

    DWORD result = ConvertInterfaceLuidToAlias((CONST NET_LUID *)&cluid, name, NDIS_IF_MAX_STRING_SIZE+1);

    switch (result) {
        case 0:
            return fromWChars(env, name);
        case ERROR_INVALID_PARAMETER:
            jthrowCC_NoSuchElementException_1(env, "InterfaceLuid not found");
            return NULL;
        case ERROR_NOT_ENOUGH_MEMORY:
            jthrowCC_IllegalStateException_1(env, "ConvertInterfaceLuidToAlias reports ERROR_NOT_ENOUGH_MEMORY but a buffer with NDIS_IF_MAX_STRING_SIZE + 1 was supplied. This should not be possible.");
            return NULL;
        default:
            jthrow_UnknownNativeErrorException_1(env, result);
            return NULL;
    }
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConvertInterfaceNameToLuidA
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConvertInterfaceNameToLuidA
        (JNIEnv * env, jobject inst, jstring name) {
    if (name == NULL) {
        jthrowCC_NullPointerException_1(env, "name");
        return 0;
    }

    NET_LUID cluid;
    cluid.Value = (ULONG64) 0;

    const char *cname = (*env)->GetStringUTFChars(env, name, NULL);

    DWORD result = ConvertInterfaceNameToLuidA(cname, &cluid);
    (*env)->ReleaseStringUTFChars(env, name, cname);

    switch (result) {
        case 0:
            return (jlong) cluid.Value;
        case ERROR_INVALID_PARAMETER:
            jthrowCC_NoSuchElementException_1(env, "InterfaceName not found");
            return 0;
        default:
            jthrow_UnknownNativeErrorException_1(env, result);
            return 0;
    }
}

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil
 * Method:    ConvertInterfaceLuidToIndex
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_eu_aschuetz_nativeutils_impl_JNIWindowsNativeUtil_ConvertInterfaceLuidToIndex
  (JNIEnv * env, jobject inst, jlong luid) {
	NET_LUID cluid;
	cluid.Value = (ULONG64) luid;
	NET_IFINDEX index;
	NETIO_STATUS status = ConvertInterfaceLuidToIndex((CONST NET_LUID*) &cluid, &index);
	switch(status) {
	case(NO_ERROR):
		return (jint) index;
	case(ERROR_INVALID_PARAMETER):
		jthrowCC_IllegalArgumentException_1(env, "interface luid is invalid");
		return 0;
	default:
		jthrow_UnknownNativeErrorException_1(env, (jlong) status);
		return 0;
	}
}

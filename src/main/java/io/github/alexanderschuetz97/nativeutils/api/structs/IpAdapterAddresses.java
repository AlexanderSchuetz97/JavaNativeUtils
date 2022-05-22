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
package io.github.alexanderschuetz97.nativeutils.api.structs;

import java.util.ArrayList;
import java.util.List;

public class IpAdapterAddresses {

    private String AdapterName;
    private List<IpAdapterUnicastAddress> UnicastAddress = new ArrayList<>();
    private List<Sockaddr> AnycastAddress = new ArrayList<>();
    private List<Sockaddr> MulticastAddress = new ArrayList<>();
    private List<Sockaddr> DnsServerAddress = new ArrayList<>();
    private String DnsSuffix;
    private String Description;
    private String FriendlyName;
    private byte[] PhysicalAddress;
    private long Mtu;
    private long IfType;
    private int OperStatus;
    private long Ipv6IfIndex;
    private long[] ZoneIndices;
    private List<AdapterPrefix> Prefix = new ArrayList<>();
    private long TransmitLinkSpeed;
    private long ReceiveLinkSpeed;
    private List<Sockaddr> WinsServerAddress = new ArrayList<>();
    private List<Sockaddr> GatewayAddress = new ArrayList<>();
    private long Ipv4Metric;
    private long Ipv6Metric;
    private long Luid_Value;
    private long Luid_NetLuidIndex;
    private long Luid_IfType;
    private Sockaddr Dhcpv4Server;
    private long CompartmentId;
    private GUID NetworkGuid;
    private int ConnectionType;
    private int TunnelType;
    private Sockaddr Dhcpv6Server;
    private byte[] Dhcpv6ClientDuid;
    private long Dhcpv6Iaid;

    public String getAdapterName() {
        return AdapterName;
    }

    public List<IpAdapterUnicastAddress> getUnicastAddress() {
        return UnicastAddress;
    }

    public List<Sockaddr> getAnycastAddress() {
        return AnycastAddress;
    }

    public List<Sockaddr> getMulticastAddress() {
        return MulticastAddress;
    }

    public List<Sockaddr> getDnsServerAddress() {
        return DnsServerAddress;
    }

    public String getDnsSuffix() {
        return DnsSuffix;
    }

    public String getDescription() {
        return Description;
    }

    public String getFriendlyName() {
        return FriendlyName;
    }

    public byte[] getPhysicalAddress() {
        return PhysicalAddress;
    }

    public long getMtu() {
        return Mtu;
    }

    public long getIfType() {
        return IfType;
    }

    public int getOperStatus() {
        return OperStatus;
    }

    public long getIpv6IfIndex() {
        return Ipv6IfIndex;
    }

    public long[] getZoneIndices() {
        return ZoneIndices;
    }

    public List<AdapterPrefix> getPrefix() {
        return Prefix;
    }

    public long getTransmitLinkSpeed() {
        return TransmitLinkSpeed;
    }

    public long getReceiveLinkSpeed() {
        return ReceiveLinkSpeed;
    }

    public List<Sockaddr> getWinsServerAddress() {
        return WinsServerAddress;
    }

    public List<Sockaddr> getGatewayAddress() {
        return GatewayAddress;
    }

    public long getIpv4Metric() {
        return Ipv4Metric;
    }

    public long getIpv6Metric() {
        return Ipv6Metric;
    }

    public long getLuid_Value() {
        return Luid_Value;
    }

    public long getLuid_NetLuidIndex() {
        return Luid_NetLuidIndex;
    }

    public long getLuid_IfType() {
        return Luid_IfType;
    }

    public Sockaddr getDhcpv4Server() {
        return Dhcpv4Server;
    }

    public long getCompartmentId() {
        return CompartmentId;
    }

    public GUID getNetworkGuid() {
        return NetworkGuid;
    }

    public int getConnectionType() {
        return ConnectionType;
    }

    public int getTunnelType() {
        return TunnelType;
    }

    public Sockaddr getDhcpv6Server() {
        return Dhcpv6Server;
    }

    public byte[] getDhcpv6ClientDuid() {
        return Dhcpv6ClientDuid;
    }

    public long getDhcpv6Iaid() {
        return Dhcpv6Iaid;
    }

    public static class AdapterPrefix {
        private Sockaddr Address;
        private long PrefixLength;
    }

    public static class IpAdapterUnicastAddress {
        private Sockaddr Address;
        private int PrefixOrigin;
        private int SuffixOrigin;
        private int DadState;
        private long ValidLifetime;
        private long PreferredLifetime;
        private long LeaseLifetime;
        private int OnLinkPrefixLength;

        public Sockaddr getAddress() {
            return Address;
        }

        public int getPrefixOrigin() {
            return PrefixOrigin;
        }

        public int getSuffixOrigin() {
            return SuffixOrigin;
        }

        public int getDadState() {
            return DadState;
        }

        public long getValidLifetime() {
            return ValidLifetime;
        }

        public long getPreferredLifetime() {
            return PreferredLifetime;
        }

        public long getLeaseLifetime() {
            return LeaseLifetime;
        }

        public int getOnLinkPrefixLength() {
            return OnLinkPrefixLength;
        }
    }


}

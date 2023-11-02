package eu.aschuetz.nativeutils.api.structs;

import java.net.InetSocketAddress;

public class MibIpForwardRow2 {
    private long InterfaceLuid;
    private int InterfaceIndex;
    private Sockaddr DestinationPrefixAddress;

    private int DestinationPrefixLength;
    private Sockaddr NextHop;
    private byte SitePrefixLength;
    private long ValidLifetime;
    private long PreferredLifetime;
    private long Metric;
    private long Protocol;
    private boolean Loopback;
    private boolean AutoconfigureAddress;
    private boolean Publish;
    private boolean Immortal;
    private long Age;
    private long Origin;

    public long getInterfaceLuid() {
        return InterfaceLuid;
    }

    public void setInterfaceLuid(long interfaceLuid) {
        InterfaceLuid = interfaceLuid;
    }

    public int getInterfaceIndex() {
        return InterfaceIndex;
    }

    public void setInterfaceIndex(int interfaceIndex) {
        InterfaceIndex = interfaceIndex;
    }

    public Sockaddr getDestinationPrefixAddress() {
        return DestinationPrefixAddress;
    }

    public void setDestinationPrefixAddress(Sockaddr destinationPrefixAddress) {
        DestinationPrefixAddress = destinationPrefixAddress;
    }

    public int getDestinationPrefixLength() {
        return DestinationPrefixLength;
    }

    public void setDestinationPrefixLength(int destinationPrefixLength) {
        DestinationPrefixLength = destinationPrefixLength;
    }

    public Sockaddr getNextHop() {
        return NextHop;
    }

    public void setNextHop(Sockaddr nextHop) {
        NextHop = nextHop;
    }

    public byte getSitePrefixLength() {
        return SitePrefixLength;
    }

    public void setSitePrefixLength(byte sitePrefixLength) {
        SitePrefixLength = sitePrefixLength;
    }

    public long getValidLifetime() {
        return ValidLifetime;
    }

    public void setValidLifetime(long validLifetime) {
        ValidLifetime = validLifetime;
    }

    public long getPreferredLifetime() {
        return PreferredLifetime;
    }

    public void setPreferredLifetime(long preferredLifetime) {
        PreferredLifetime = preferredLifetime;
    }

    public long getMetric() {
        return Metric;
    }

    public void setMetric(long metric) {
        Metric = metric;
    }

    public long getProtocol() {
        return Protocol;
    }

    public void setProtocol(long protocol) {
        Protocol = protocol;
    }

    public boolean isLoopback() {
        return Loopback;
    }

    public void setLoopback(boolean loopback) {
        Loopback = loopback;
    }

    public boolean isAutoconfigureAddress() {
        return AutoconfigureAddress;
    }

    public void setAutoconfigureAddress(boolean autoconfigureAddress) {
        AutoconfigureAddress = autoconfigureAddress;
    }

    public boolean isPublish() {
        return Publish;
    }

    public void setPublish(boolean publish) {
        Publish = publish;
    }

    public boolean isImmortal() {
        return Immortal;
    }

    public void setImmortal(boolean immortal) {
        Immortal = immortal;
    }

    public long getAge() {
        return Age;
    }

    public void setAge(long age) {
        Age = age;
    }

    public long getOrigin() {
        return Origin;
    }

    public void setOrigin(long origin) {
        Origin = origin;
    }

    @Override
    public String toString() {
        String dstPaddr = "null";
        if (DestinationPrefixAddress != null) {
            InetSocketAddress inetSocketAddress = DestinationPrefixAddress.parseWin32_SOCKADDR_INET();
            if (inetSocketAddress != null) {
                dstPaddr = inetSocketAddress.toString();
            } else {
                dstPaddr = DestinationPrefixAddress.toString();
            }
        }

        String nxHopaddr = "null";
        if (NextHop != null) {
            InetSocketAddress inetSocketAddress = NextHop.parseWin32_SOCKADDR_INET();
            if (inetSocketAddress != null) {
                nxHopaddr = inetSocketAddress.toString();
            } else {
                nxHopaddr = NextHop.toString();
            }
        }


        return "MibIpForwardRow2{" +
                "InterfaceLuid=" + InterfaceLuid +
                ", InterfaceIndex=" + InterfaceIndex +
                ", DestinationPrefixAddress=" + dstPaddr +
                ", DestinationPrefixLength=" + DestinationPrefixLength +
                ", NextHop=" + nxHopaddr +
                ", SitePrefixLength=" + SitePrefixLength +
                ", ValidLifetime=" + ValidLifetime +
                ", PreferredLifetime=" + PreferredLifetime +
                ", Metric=" + Metric +
                ", Protocol=" + Protocol +
                ", Loopback=" + Loopback +
                ", AutoconfigureAddress=" + AutoconfigureAddress +
                ", Publish=" + Publish +
                ", Immortal=" + Immortal +
                ", Age=" + Age +
                ", Origin=" + Origin +
                '}';
    }
}

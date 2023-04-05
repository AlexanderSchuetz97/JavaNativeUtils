package io.github.alexanderschuetz97.nativeutils.api.structs;

/**
 * Struct for CreateIpForwardEntry
 */
public class MibIpForwardRow {
    /**
     * Note: this is in Big Endian (Network order)
     * so 1.2.3.4 would be 0x04030201
     */
    private int dwForwardDest;

    /**
     * Note: this is in Big Endian (Network order)
     * so 1.2.3.4 would be 0x04030201
     */
    private int dwForwardMask;
    private int dwForwardPolicy;
    private int dwForwardNextHop;
    private int dwForwardIfIndex;

    enum MIB_IPFORWARD_TYPE {
        MIB_IPROUTE_TYPE_OTHER(1),
        MIB_IPROUTE_TYPE_INVALID(2),
        MIB_IPROUTE_TYPE_DIRECT(3),
        MIB_IPROUTE_TYPE_INDIRECT(4);
        private final int dwForwardType;

        MIB_IPFORWARD_TYPE(int dwForwardType) {
            this.dwForwardType = dwForwardType;
        }

        public int getDwForwardType() {
            return dwForwardType;
        }

        static MIB_IPFORWARD_TYPE getForDwForwardType(int dwForwardType) {
            switch (dwForwardType) {
                case(1):
                    return MIB_IPROUTE_TYPE_OTHER;
                case(2):
                    return MIB_IPROUTE_TYPE_INVALID;
                case(3):
                    return MIB_IPROUTE_TYPE_DIRECT;
                case(4):
                    return MIB_IPROUTE_TYPE_INDIRECT;
                default:
                    return null;
            }
        }
    }


    private MIB_IPFORWARD_TYPE ForwardType;

    enum MIB_IPFORWARD_PROTO {
        MIB_IPPROTO_OTHER(1),
        MIB_IPPROTO_LOCAL(2),
        MIB_IPPROTO_NETMGMT(3),
        MIB_IPPROTO_ICMP(4),
        MIB_IPPROTO_EGP(5),
        MIB_IPPROTO_GGP(6),
        MIB_IPPROTO_HELLO(7),
        MIB_IPPROTO_RIP(8),
        MIB_IPPROTO_IS_IS(9),
        MIB_IPPROTO_ES_IS(10),
        MIB_IPPROTO_CISCO(11),
        MIB_IPPROTO_BBN(12),
        MIB_IPPROTO_OSPF(13),
        MIB_IPPROTO_BGP(14),
        MIB_IPPROTO_NT_AUTOSTATIC(10002),
        MIB_IPPROTO_NT_STATIC(10006),
        MIB_IPPROTO_NT_STATIC_NON_DOD(10007),

        ;
        private final int dwForwardProto;

        MIB_IPFORWARD_PROTO(int dwForwardProto) {
            this.dwForwardProto = dwForwardProto;
        }

        public int getDwForwardProto() {
            return dwForwardProto;
        }

        static MIB_IPFORWARD_PROTO getForDwForwardProto(int dwForwardType) {
            switch (dwForwardType) {
                case(1):
                    return MIB_IPPROTO_OTHER;
                case(2):
                    return MIB_IPPROTO_LOCAL;
                case(3):
                    return MIB_IPPROTO_NETMGMT;
                case(4):
                    return MIB_IPPROTO_ICMP;
                case(5):
                    return MIB_IPPROTO_EGP;
                case(6):
                    return MIB_IPPROTO_GGP;
                case(7):
                    return MIB_IPPROTO_HELLO;
                case(8):
                    return MIB_IPPROTO_RIP;
                case(9):
                    return MIB_IPPROTO_IS_IS;
                case(10):
                    return MIB_IPPROTO_ES_IS;
                case(11):
                    return MIB_IPPROTO_CISCO;
                case(12):
                    return MIB_IPPROTO_BBN;
                case(13):
                    return MIB_IPPROTO_OSPF;
                case(14):
                    return MIB_IPPROTO_BGP;
                case(10002):
                    return MIB_IPPROTO_NT_AUTOSTATIC;
                case(10006):
                    return MIB_IPPROTO_NT_STATIC;
                case(10007):
                    return MIB_IPPROTO_NT_STATIC_NON_DOD;
                default:
                    return null;
            }
        }
    }

    private MIB_IPFORWARD_PROTO ForwardProto;

    private int dwForwardAge;
    private int dwForwardNextHopAS;
    private int dwForwardMetric1 = -1;
    private int dwForwardMetric2 = -1;
    private int dwForwardMetric3 = -1;
    private int dwForwardMetric4 = -1;
    private int dwForwardMetric5 = -1;

    public int getDwForwardDest() {
        return dwForwardDest;
    }

    public void setDwForwardDest(int dwForwardDest) {
        this.dwForwardDest = dwForwardDest;
    }

    public int getDwForwardMask() {
        return dwForwardMask;
    }

    public void setDwForwardMask(int dwForwardMask) {
        this.dwForwardMask = dwForwardMask;
    }

    public int getDwForwardPolicy() {
        return dwForwardPolicy;
    }

    public void setDwForwardPolicy(int dwForwardPolicy) {
        this.dwForwardPolicy = dwForwardPolicy;
    }

    public int getDwForwardNextHop() {
        return dwForwardNextHop;
    }

    public void setDwForwardNextHop(int dwForwardNextHop) {
        this.dwForwardNextHop = dwForwardNextHop;
    }

    public int getDwForwardIfIndex() {
        return dwForwardIfIndex;
    }

    public void setDwForwardIfIndex(int dwForwardIfIndex) {
        this.dwForwardIfIndex = dwForwardIfIndex;
    }

    public MIB_IPFORWARD_TYPE getForwardType() {
        return ForwardType;
    }

    public void setForwardType(MIB_IPFORWARD_TYPE forwardType) {
        ForwardType = forwardType;
    }

    public int getDwForwardAge() {
        return dwForwardAge;
    }

    public void setDwForwardAge(int dwForwardAge) {
        this.dwForwardAge = dwForwardAge;
    }

    public int getDwForwardNextHopAS() {
        return dwForwardNextHopAS;
    }

    public void setDwForwardNextHopAS(int dwForwardNextHopAS) {
        this.dwForwardNextHopAS = dwForwardNextHopAS;
    }

    public int getDwForwardMetric1() {
        return dwForwardMetric1;
    }

    public void setDwForwardMetric1(int dwForwardMetric1) {
        this.dwForwardMetric1 = dwForwardMetric1;
    }

    public int getDwForwardMetric2() {
        return dwForwardMetric2;
    }

    public void setDwForwardMetric2(int dwForwardMetric2) {
        this.dwForwardMetric2 = dwForwardMetric2;
    }

    public int getDwForwardMetric3() {
        return dwForwardMetric3;
    }

    public void setDwForwardMetric3(int dwForwardMetric3) {
        this.dwForwardMetric3 = dwForwardMetric3;
    }

    public int getDwForwardMetric4() {
        return dwForwardMetric4;
    }

    public void setDwForwardMetric4(int dwForwardMetric4) {
        this.dwForwardMetric4 = dwForwardMetric4;
    }

    public int getDwForwardMetric5() {
        return dwForwardMetric5;
    }

    public void setDwForwardMetric5(int dwForwardMetric5) {
        this.dwForwardMetric5 = dwForwardMetric5;
    }

    public MIB_IPFORWARD_PROTO getForwardProto() {
        return ForwardProto;
    }

    public void setForwardProto(MIB_IPFORWARD_PROTO forwardProto) {
        ForwardProto = forwardProto;
    }
}

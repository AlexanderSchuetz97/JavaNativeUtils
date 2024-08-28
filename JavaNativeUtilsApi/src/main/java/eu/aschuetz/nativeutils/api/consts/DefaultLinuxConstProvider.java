//
// Copyright Alexander Schütz, 2021-2024
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
package eu.aschuetz.nativeutils.api.consts;

/**
 * This class contains LinuxConstants valid for the AMD64 architecture and GLIBC.
 */
public class DefaultLinuxConstProvider implements LinuxConstProvider {

    /**
     * domain not specified.
     */
    int AF_UNSPEC = 0;

    /**
     * domain for unix sockets
     */
    int AF_UNIX = 1;

    /**
     * domain for ipv4 sockets
     */
    int AF_INET = 2;

    /**
     * domain for ipv6 sockets
     */
    int AF_INET6 = 10;

    /**
     * domain for configuring network interfaces in the kernel.
     */
    int AF_NETLINK = 16;

    /**
     * type for stream based sockets with reliable transport
     */
    int SOCK_STREAM = 1;

    /**
     * type for datagram based sockets with unreliable transport
     */
    int SOCK_DGRAM = 2;

    /**
     * type for raw socket.
     */
    int SOCK_RAW = 3;

    /**
     *  Option for AF_NETLINK.
     *  Receives routing and link updates and may be used to
     *  modify the routing tables.
     */
    int NETLINK_ROUTE = 0;

    ///////////////////////////////////////////////
    //Socketopt constants
    ///////////////////////////////////////////////

    int SOL_SOCKET = 1;
    int SO_DEBUG = 1;
    int SO_REUSEADDR = 2;
    int SO_TYPE = 3;
    int SO_ERROR = 4;
    int SO_DONTROUTE = 5;
    int SO_BROADCAST = 6;
    int SO_SNDBUF = 7;
    int SO_RCVBUF = 8;
    int SO_SNDBUFFORCE = 32;
    int SO_RCVBUFFORCE = 33;
    int SO_KEEPALIVE = 9;
    int SO_OOBINLINE = 10;
    int SO_NO_CHECK = 11;
    int SO_PRIORITY = 12;
    int SO_LINGER = 13;
    int SO_BSDCOMPAT = 14;
    int SO_REUSEPORT = 15;
    int SO_PASSCRED = 16;
    int SO_PEERCRED = 17;
    int SO_RCVLOWAT = 18;
    int SO_SNDLOWAT = 19;
    int SO_RCVTIMEO = 20;
    int SO_SNDTIMEO = 21;
    int SO_SECURITY_AUTHENTICATION = 22;
    int SO_SECURITY_ENCRYPTION_TRANSPORT = 23;
    int SO_SECURITY_ENCRYPTION_NETWORK = 24;
    int SO_BINDTODEVICE = 25;
    int SO_ATTACH_FILTER = 26;
    int SO_DETACH_FILTER = 27;
    int SO_GET_FILTER = 26;
    int SO_PEERNAME = 28;
    int SO_TIMESTAMP = 29;
    int SCM_TIMESTAMP = 29;
    int SO_ACCEPTCONN = 30;
    int SO_PEERSEC = 31;
    int SO_PASSSEC = 34;
    int SO_TIMESTAMPNS = 35;
    int SCM_TIMESTAMPNS = 35;
    int SO_MARK = 36;
    int SO_TIMESTAMPING = 37;
    int SCM_TIMESTAMPING = 37;
    int SO_PROTOCOL = 38;
    int SO_DOMAIN = 39;
    int SO_RXQ_OVFL = 40;
    int SO_WIFI_STATUS = 41;
    int SCM_WIFI_STATUS = 41;
    int SO_PEEK_OFF = 42;
    int SO_NOFCS = 43;
    int SO_LOCK_FILTER = 44;
    int SO_SELECT_ERR_QUEUE = 45;
    int SO_BUSY_POLL = 46;
    int SO_MAX_PACING_RATE = 47;
    int SO_BPF_EXTENSIONS = 48;
    int SO_INCOMING_CPU = 49;
    int SO_ATTACH_BPF = 50;
    int SO_DETACH_BPF = 27;
    int SO_ATTACH_REUSEPORT_CBPF = 51;
    int SO_ATTACH_REUSEPORT_EBPF = 52;
    int SO_CNX_ADVICE = 53;
    int SCM_TIMESTAMPING_OPT_STATS = 54;
    int SO_MEMINFO = 55;
    int SO_INCOMING_NAPI_ID = 56;
    int SO_COOKIE = 57;
    int SCM_TIMESTAMPING_PKTINFO = 58;
    int SO_PEERGROUPS = 59;
    int SO_ZEROCOPY = 60;

    /**
     * CMSG HDR type for file descriptor transfer
     */
    int SCM_RIGHTS = 1;
    //FOR MMAP FLAGS
    int MAP_SHARED = 1;
    int MAP_PRIVATE = 2;

    /////
    // Open flags
    ////

    int O_ACCMODE = 0003;
    int O_RDONLY = 00;
    int O_WRONLY = 01;
    int O_RDWR = 02;
    int O_CREAT = 0100;
    int O_EXCL = 0200;
    int O_NOCTTY = 0400;
    int O_TRUNC = 01000;
    int O_APPEND = 02000;
    int O_NONBLOCK = 04000;
    int O_NDELAY = O_NONBLOCK;
    int O_SYNC = 04010000;
    int O_ASYNC = 020000;
    int O_LARGEFILE = 0100000;
    int O_DIRECTORY = 0200000;
    int O_NOFOLLOW = 0400000;
    int O_CLOEXEC = 02000000;
    int O_DIRECT = 040000;
    int O_NOATIME = 01000000;
    int O_PATH = 010000000;
    int O_DSYNC = 010000;

    int S_IRUSR = 0400;
    int S_IWUSR = 0200;
    int S_IXUSR = 0100;
    int S_IRGRP = S_IRUSR >> 3;
    int S_IWGRP = S_IWUSR >> 3;
    int S_IXGRP = S_IXUSR >> 3;
    int S_IROTH = S_IRGRP >> 3;
    int S_IWOTH = S_IWGRP >> 3;
    int S_IXOTH = S_IXGRP >> 3;
    int S_IRWXU = S_IRUSR | S_IWUSR | S_IXUSR;
    int S_IRWXG = S_IRWXU >> 3;
    int S_IRWXO = S_IRWXG >> 3;

    int IFNAMSIZ = 16;

    //ioctls.h
    int SIOCGIFFLAGS = 0x8913;
    int SIOCSIFFLAGS = 0x8914;
    int SIOCGIFMTU = 0x8921;

    //netlink.h
    short NLM_F_REQUEST = 0x1;
    short NLM_F_DUMP = 768;
    short NLM_F_MULTI = 0x2;
    short NLM_F_CREATE= 0x400;
    short NLM_F_EXCL = 0x200;
    short NLM_F_ACK = 4;

    short NLMSG_NOOP = 0x1;
    short NLMSG_ERROR =	0x2;
    short NLMSG_DONE = 0x3;
    short NLMSG_OVERRUN = 0x4;

    //rtnetlink.h
    short RTM_GETLINK = 18;
    short RTM_DELADDR = 21;
    short RTM_GETADDR = 22;
    short RTM_NEWADDR = 20;
    byte RT_SCOPE_UNIVERSE = 0;
    short ARPHRD_NETROM = 0;
    short IFLA_IFNAME = 3;
    short IFA_UNSPEC = 0;
    short IFA_ADDRESS = 1;
    short IFA_LOCAL = 2;
    short IFA_LABEL = 3;
    short IFA_BROADCAST = 4;
    short IFA_ANYCAST = 5;
    short IFA_CACHEINFO = 6;
    int IFA_F_PERMANENT = 0x80;
    int IFA_F_SECONDARY = 0x1;

    int IFF_UP = 1;

    int IFF_NO_PI = 4096;

    //if_tun.h
    int TUNSETIFF = 1074025674;
    int TUNSETPERSIST = 1074025675;
    int TUNGETSNDBUF = (int) 2147767507L;


    int RTA_UNSPEC = 0;
    int RTA_DST = 1;
    int RTA_SRC = 2;
    int RTA_IIF = 3;
    int RTA_OIF = 4;
    int RTA_GATEWAY = 5;
    int RTA_PRIORITY = 6;
    int RTA_PREFSRC = 7;
    int RTA_METRICS = 8;
    int RTA_MULTIPATH = 9;
    int RTA_PROTOINFO = 10; /* no longer used */
    int RTA_FLOW = 11;
    int RTA_CACHEINFO = 12;
    int RTA_SESSION = 13; /* no longer used */
    int RTA_MP_ALGO = 14; /* no longer used */
    int RTA_TABLE = 15;
    int RTA_MARK = 16;
    int RTA_MFC_STATS = 17;
    int RTA_VIA = 18;
    int RTA_NEWDST = 19;
    int RTA_PREF = 20;
    int RTA_ENCAP_TYPE = 21;
    int RTA_ENCAP = 22;
    int RTA_EXPIRES = 23;
    int RTA_PAD = 24;
    int RTA_UID = 25;
    int RTA_TTL_PROPAGATE = 26;
    int RTA_IP_PROTO = 27;
    int RTA_SPORT = 28;
    int RTA_DPORT = 29;
    int RTA_NH_ID = 30;

    int PTHREAD_MUTEX_STALLED = 0;
    int PTHREAD_MUTEX_ROBUST = 1;

    int PTHREAD_PROCESS_SHARED = 1;

    int PTHREAD_PROCESS_PRIVATE = 0;

    int PTHREAD_MUTEX_RECURSIVE = 2;
    int PTHREAD_MUTEX_ERRORCHECK = 1;
    int PTHREAD_MUTEX_DEFAULT = 0;
    int PTHREAD_MUTEX_NORMAL = 0;

    int MFD_CLOEXEC = 0x0001;

    int MFD_ALLOW_SEALING = 0x0002;

    int MFD_HUGETLB = 0x0004;
    int MFD_HUGE_64KB;
    int MFD_HUGE_512KB;
    int MFD_HUGE_1MB;
    int MFD_HUGE_2MB;
    int MFD_HUGE_8MB;
    int MFD_HUGE_16MB;
    int MFD_HUGE_256MB;
    int MFD_HUGE_1GB;
    int MFD_HUGE_2GB;
    int MFD_HUGE_16GB;

    int MADV_DONTNEED;

    int MADV_NORMAL;

    int MADV_RANDOM;

    int MADV_SEQUENTIAL;

    int MADV_WILLNEED;


    int MADV_REMOVE;

    int MADV_DONTFORK;

    int MADV_DOFORK;

    int MADV_HWPOISON;

    int MADV_MERGEABLE;

    int MADV_UNMERGEABLE;


    int MADV_HUGEPAGE;

    int MADV_NOHUGEPAGE;

    int MADV_DONTDUMP;

    int MADV_DODUMP;

    int MADV_WIPEONFORK;

    int MADV_KEEPONFORK;


    @Override
    public int AF_UNSPEC() {
        return AF_UNSPEC;
    }

    @Override
    public int AF_UNIX() {
        return AF_UNIX;
    }

    @Override
    public int AF_INET() {
        return AF_INET;
    }

    @Override
    public int AF_INET6() {
        return AF_INET6;
    }

    @Override
    public int AF_NETLINK() {
        return AF_NETLINK;
    }

    @Override
    public int SOCK_STREAM() {
        return SOCK_STREAM;
    }

    @Override
    public int SOCK_DGRAM() {
        return SOCK_DGRAM;
    }

    @Override
    public int SOCK_RAW() {
        return SOCK_RAW;
    }

    @Override
    public int NETLINK_ROUTE() {
        return NETLINK_ROUTE;
    }

    @Override
    public int SOL_SOCKET() {
        return SOL_SOCKET;
    }

    @Override
    public int SO_DEBUG() {
        return SO_DEBUG;
    }

    @Override
    public int SO_REUSEADDR() {
        return SO_REUSEADDR;
    }

    @Override
    public int SO_TYPE() {
        return SO_TYPE;
    }

    @Override
    public int SO_ERROR() {
        return SO_ERROR;
    }

    @Override
    public int SO_DONTROUTE() {
        return SO_DONTROUTE;
    }

    @Override
    public int SO_BROADCAST() {
        return SO_BROADCAST;
    }

    @Override
    public int SO_SNDBUF() {
        return SO_SNDBUF;
    }

    @Override
    public int SO_RCVBUF() {
        return SO_RCVBUF;
    }

    @Override
    public int SO_SNDBUFFORCE() {
        return SO_SNDBUFFORCE;
    }

    @Override
    public int SO_RCVBUFFORCE() {
        return SO_RCVBUFFORCE;
    }

    @Override
    public int SO_KEEPALIVE() {
        return SO_KEEPALIVE;
    }

    @Override
    public int SO_OOBINLINE() {
        return SO_OOBINLINE;
    }

    @Override
    public int SO_NO_CHECK() {
        return SO_NO_CHECK;
    }

    @Override
    public int SO_PRIORITY() {
        return SO_PRIORITY;
    }

    @Override
    public int SO_LINGER() {
        return SO_LINGER;
    }

    @Override
    public int SO_BSDCOMPAT() {
        return SO_BSDCOMPAT;
    }

    @Override
    public int SO_REUSEPORT() {
        return SO_REUSEPORT;
    }

    @Override
    public int SO_PASSCRED() {
        return SO_PASSCRED;
    }

    @Override
    public int SO_PEERCRED() {
        return SO_PEERCRED;
    }

    @Override
    public int SO_RCVLOWAT() {
        return SO_RCVLOWAT;
    }

    @Override
    public int SO_SNDLOWAT() {
        return SO_SNDLOWAT;
    }

    @Override
    public int SO_RCVTIMEO() {
        return SO_RCVTIMEO;
    }

    @Override
    public int SO_SNDTIMEO() {
        return SO_SNDTIMEO;
    }

    @Override
    public int SO_SECURITY_AUTHENTICATION() {
        return SO_SECURITY_AUTHENTICATION;
    }

    @Override
    public int SO_SECURITY_ENCRYPTION_TRANSPORT() {
        return SO_SECURITY_ENCRYPTION_TRANSPORT;
    }

    @Override
    public int SO_SECURITY_ENCRYPTION_NETWORK() {
        return SO_SECURITY_ENCRYPTION_NETWORK;
    }

    @Override
    public int SO_BINDTODEVICE() {
        return SO_BINDTODEVICE;
    }

    @Override
    public int SO_ATTACH_FILTER() {
        return SO_ATTACH_FILTER;
    }

    @Override
    public int SO_DETACH_FILTER() {
        return SO_DETACH_FILTER;
    }

    @Override
    public int SO_GET_FILTER() {
        return SO_GET_FILTER;
    }

    @Override
    public int SO_PEERNAME() {
        return SO_PEERNAME;
    }

    @Override
    public int SO_TIMESTAMP() {
        return SO_TIMESTAMP;
    }

    @Override
    public int SCM_TIMESTAMP() {
        return SCM_TIMESTAMP;
    }

    @Override
    public int SO_ACCEPTCONN() {
        return SO_ACCEPTCONN;
    }

    @Override
    public int SO_PEERSEC() {
        return SO_PEERSEC;
    }

    @Override
    public int SO_PASSSEC() {
        return SO_PASSSEC;
    }

    @Override
    public int SO_TIMESTAMPNS() {
        return SO_TIMESTAMPNS;
    }

    @Override
    public int SCM_TIMESTAMPNS() {
        return SCM_TIMESTAMPNS;
    }

    @Override
    public int SO_MARK() {
        return SO_MARK;
    }

    @Override
    public int SO_TIMESTAMPING() {
        return SO_TIMESTAMPING;
    }

    @Override
    public int SCM_TIMESTAMPING() {
        return SCM_TIMESTAMPING;
    }

    @Override
    public int SO_PROTOCOL() {
        return SO_PROTOCOL;
    }

    @Override
    public int SO_DOMAIN() {
        return SO_DOMAIN;
    }

    @Override
    public int SO_RXQ_OVFL() {
        return SO_RXQ_OVFL;
    }

    @Override
    public int SO_WIFI_STATUS() {
        return SO_WIFI_STATUS;
    }

    @Override
    public int SCM_WIFI_STATUS() {
        return SCM_WIFI_STATUS;
    }

    @Override
    public int SO_PEEK_OFF() {
        return SO_PEEK_OFF;
    }

    @Override
    public int SO_NOFCS() {
        return SO_NOFCS;
    }

    @Override
    public int SO_LOCK_FILTER() {
        return SO_LOCK_FILTER;
    }

    @Override
    public int SO_SELECT_ERR_QUEUE() {
        return SO_SELECT_ERR_QUEUE;
    }

    @Override
    public int SO_BUSY_POLL() {
        return SO_BUSY_POLL;
    }

    @Override
    public int SO_MAX_PACING_RATE() {
        return SO_MAX_PACING_RATE;
    }

    @Override
    public int SO_BPF_EXTENSIONS() {
        return SO_BPF_EXTENSIONS;
    }

    @Override
    public int SO_INCOMING_CPU() {
        return SO_INCOMING_CPU;
    }

    @Override
    public int SO_ATTACH_BPF() {
        return SO_ATTACH_BPF;
    }

    @Override
    public int SO_DETACH_BPF() {
        return SO_DETACH_BPF;
    }

    @Override
    public int SO_ATTACH_REUSEPORT_CBPF() {
        return SO_ATTACH_REUSEPORT_CBPF;
    }

    @Override
    public int SO_ATTACH_REUSEPORT_EBPF() {
        return SO_ATTACH_REUSEPORT_EBPF;
    }

    @Override
    public int SO_CNX_ADVICE() {
        return SO_CNX_ADVICE;
    }

    @Override
    public int SCM_TIMESTAMPING_OPT_STATS() {
        return SCM_TIMESTAMPING_OPT_STATS;
    }

    @Override
    public int SO_MEMINFO() {
        return SO_MEMINFO;
    }

    @Override
    public int SO_INCOMING_NAPI_ID() {
        return SO_INCOMING_NAPI_ID;
    }

    @Override
    public int SO_COOKIE() {
        return SO_COOKIE;
    }

    @Override
    public int SCM_TIMESTAMPING_PKTINFO() {
        return SCM_TIMESTAMPING_PKTINFO;
    }

    @Override
    public int SO_PEERGROUPS() {
        return SO_PEERGROUPS;
    }

    @Override
    public int SO_ZEROCOPY() {
        return SO_ZEROCOPY;
    }

    @Override
    public int SCM_RIGHTS() {
        return SCM_RIGHTS;
    }

    @Override
    public int MAP_SHARED() {
        return MAP_SHARED;
    }

    @Override
    public int MAP_PRIVATE() {
        return MAP_PRIVATE;
    }

    @Override
    public int O_ACCMODE() {
        return O_ACCMODE;
    }

    @Override
    public int O_RDONLY() {
        return O_RDONLY;
    }

    @Override
    public int O_WRONLY() {
        return O_WRONLY;
    }

    @Override
    public int O_RDWR() {
        return O_RDWR;
    }

    @Override
    public int O_CREAT() {
        return O_CREAT;
    }

    @Override
    public int O_EXCL() {
        return O_EXCL;
    }

    @Override
    public int O_NOCTTY() {
        return O_NOCTTY;
    }

    @Override
    public int O_TRUNC() {
        return O_TRUNC;
    }

    @Override
    public int O_APPEND() {
        return O_APPEND;
    }

    @Override
    public int O_NONBLOCK() {
        return O_NONBLOCK;
    }

    @Override
    public int O_NDELAY() {
        return O_NDELAY;
    }

    @Override
    public int O_SYNC() {
        return O_SYNC;
    }

    @Override
    public int O_ASYNC() {
        return O_ASYNC;
    }

    @Override
    public int O_LARGEFILE() {
        return O_LARGEFILE;
    }

    @Override
    public int O_DIRECTORY() {
        return O_DIRECTORY;
    }

    @Override
    public int O_NOFOLLOW() {
        return O_NOFOLLOW;
    }

    @Override
    public int O_CLOEXEC() {
        return O_CLOEXEC;
    }

    @Override
    public int O_DIRECT() {
        return O_DIRECT;
    }

    @Override
    public int O_NOATIME() {
        return O_NOATIME;
    }

    @Override
    public int O_PATH() {
        return O_PATH;
    }

    @Override
    public int O_DSYNC() {
        return O_DSYNC;
    }

    @Override
    public int S_IRUSR() {
        return S_IRUSR;
    }

    @Override
    public int S_IWUSR() {
        return S_IWUSR;
    }

    @Override
    public int S_IXUSR() {
        return S_IXUSR;
    }

    @Override
    public int S_IRGRP() {
        return S_IRGRP;
    }

    @Override
    public int S_IWGRP() {
        return S_IWGRP;
    }

    @Override
    public int S_IXGRP() {
        return S_IXGRP;
    }

    @Override
    public int S_IROTH() {
        return S_IROTH;
    }

    @Override
    public int S_IWOTH() {
        return S_IWOTH;
    }

    @Override
    public int S_IXOTH() {
        return S_IXOTH;
    }

    @Override
    public int S_IRWXU() {
        return S_IRWXU;
    }

    @Override
    public int S_IRWXG() {
        return S_IRWXG;
    }

    @Override
    public int S_IRWXO() {
        return S_IRWXO;
    }

    @Override
    public int IFNAMSIZ() {
        return IFNAMSIZ;
    }

    @Override
    public int SIOCGIFFLAGS() {
        return SIOCGIFFLAGS;
    }

    @Override
    public int SIOCSIFFLAGS() {
        return SIOCSIFFLAGS;
    }

    @Override
    public int SIOCGIFMTU() {
        return SIOCGIFMTU;
    }

    @Override
    public short NLM_F_REQUEST() {
        return NLM_F_REQUEST;
    }

    @Override
    public short NLM_F_DUMP() {
        return NLM_F_DUMP;
    }

    @Override
    public short NLM_F_MULTI() {
        return NLM_F_MULTI;
    }

    @Override
    public short NLM_F_CREATE() {
        return NLM_F_CREATE;
    }

    @Override
    public short NLM_F_EXCL() {
        return NLM_F_EXCL;
    }

    @Override
    public short NLM_F_ACK() {
        return NLM_F_ACK;
    }

    @Override
    public short NLMSG_NOOP() {
        return NLMSG_NOOP;
    }

    @Override
    public short NLMSG_ERROR() {
        return NLMSG_ERROR;
    }

    @Override
    public short NLMSG_DONE() {
        return NLMSG_DONE;
    }

    @Override
    public short NLMSG_OVERRUN() {
        return NLMSG_OVERRUN;
    }

    @Override
    public short RTM_GETLINK() {
        return RTM_GETLINK;
    }

    @Override
    public short RTM_DELADDR() {
        return RTM_DELADDR;
    }

    @Override
    public short RTM_GETADDR() {
        return RTM_GETADDR;
    }

    @Override
    public short RTM_NEWADDR() {
        return RTM_NEWADDR;
    }

    @Override
    public byte RT_SCOPE_UNIVERSE() {
        return RT_SCOPE_UNIVERSE;
    }

    @Override
    public short ARPHRD_NETROM() {
        return ARPHRD_NETROM;
    }

    @Override
    public short IFLA_IFNAME() {
        return IFLA_IFNAME;
    }

    @Override
    public short IFA_UNSPEC() {
        return IFA_UNSPEC;
    }

    @Override
    public short IFA_ADDRESS() {
        return IFA_ADDRESS;
    }

    @Override
    public short IFA_LOCAL() {
        return IFA_LOCAL;
    }

    @Override
    public short IFA_LABEL() {
        return IFA_LABEL;
    }

    @Override
    public short IFA_BROADCAST() {
        return IFA_BROADCAST;
    }

    @Override
    public short IFA_ANYCAST() {
        return IFA_ANYCAST;
    }

    @Override
    public short IFA_CACHEINFO() {
        return IFA_CACHEINFO;
    }

    @Override
    public int IFA_F_PERMANENT() {
        return IFA_F_PERMANENT;
    }

    @Override
    public int IFA_F_SECONDARY() {
        return IFA_F_SECONDARY;
    }

    @Override
    public int IFF_UP() {
        return IFF_UP;
    }

    @Override
    public int IFF_NO_PI() {
        return IFF_NO_PI;
    }

    @Override
    public int TUNSETIFF() {
        return TUNSETIFF;
    }

    @Override
    public int TUNSETPERSIST() {
        return TUNSETPERSIST;
    }

    @Override
    public int TUNGETSNDBUF() {
        return TUNGETSNDBUF;
    }

    @Override
    public int RTA_UNSPEC() {
        return RTA_UNSPEC;
    }

    @Override
    public int RTA_DST() {
        return RTA_DST;
    }

    @Override
    public int RTA_SRC() {
        return RTA_SRC;
    }

    @Override
    public int RTA_IIF() {
        return RTA_IIF;
    }

    @Override
    public int RTA_OIF() {
        return RTA_OIF;
    }

    @Override
    public int RTA_GATEWAY() {
        return RTA_GATEWAY;
    }

    @Override
    public int RTA_PRIORITY() {
        return RTA_PRIORITY;
    }

    @Override
    public int RTA_PREFSRC() {
        return RTA_PREFSRC;
    }

    @Override
    public int RTA_METRICS() {
        return RTA_METRICS;
    }

    @Override
    public int RTA_MULTIPATH() {
        return RTA_MULTIPATH;
    }

    @Override
    public int RTA_PROTOINFO() {
        return RTA_PROTOINFO;
    }

    @Override
    public int RTA_FLOW() {
        return RTA_FLOW;
    }

    @Override
    public int RTA_CACHEINFO() {
        return RTA_CACHEINFO;
    }

    @Override
    public int RTA_SESSION() {
        return RTA_SESSION;
    }

    @Override
    public int RTA_MP_ALGO() {
        return RTA_MP_ALGO;
    }

    @Override
    public int RTA_TABLE() {
        return RTA_TABLE;
    }

    @Override
    public int RTA_MARK() {
        return RTA_MARK;
    }

    @Override
    public int RTA_MFC_STATS() {
        return RTA_MFC_STATS;
    }

    @Override
    public int RTA_VIA() {
        return RTA_VIA;
    }

    @Override
    public int RTA_NEWDST() {
        return RTA_NEWDST;
    }

    @Override
    public int RTA_PREF() {
        return RTA_PREF;
    }

    @Override
    public int RTA_ENCAP_TYPE() {
        return RTA_ENCAP_TYPE;
    }

    @Override
    public int RTA_ENCAP() {
        return RTA_ENCAP;
    }

    @Override
    public int RTA_EXPIRES() {
        return RTA_EXPIRES;
    }

    @Override
    public int RTA_PAD() {
        return RTA_PAD;
    }

    @Override
    public int RTA_UID() {
        return RTA_UID;
    }

    @Override
    public int RTA_TTL_PROPAGATE() {
        return RTA_TTL_PROPAGATE;
    }

    @Override
    public int RTA_IP_PROTO() {
        return RTA_IP_PROTO;
    }

    @Override
    public int RTA_SPORT() {
        return RTA_SPORT;
    }

    @Override
    public int RTA_DPORT() {
        return RTA_DPORT;
    }

    @Override
    public int RTA_NH_ID() {
        return RTA_NH_ID;
    }

    @Override
    public int PTHREAD_MUTEX_STALLED() {
        return PTHREAD_MUTEX_STALLED;
    }

    @Override
    public int PTHREAD_MUTEX_ROBUST() {
        return PTHREAD_MUTEX_ROBUST;
    }

    @Override
    public int PTHREAD_PROCESS_SHARED() {
        return PTHREAD_PROCESS_SHARED;
    }

    @Override
    public int PTHREAD_PROCESS_PRIVATE() {
        return PTHREAD_PROCESS_PRIVATE;
    }

    @Override
    public int PTHREAD_MUTEX_RECURSIVE() {
        return PTHREAD_MUTEX_RECURSIVE;
    }

    @Override
    public int PTHREAD_MUTEX_ERRORCHECK() {
        return PTHREAD_MUTEX_ERRORCHECK;
    }

    @Override
    public int PTHREAD_MUTEX_DEFAULT() {
        return PTHREAD_MUTEX_DEFAULT;
    }

    @Override
    public int PTHREAD_MUTEX_NORMAL() {
        return PTHREAD_MUTEX_NORMAL;
    }

    @Override
    public int MFD_CLOEXEC() {
        return MFD_CLOEXEC;
    }

    @Override
    public int MFD_ALLOW_SEALING() {
        return MFD_ALLOW_SEALING;
    }

    @Override
    public int MFD_HUGETLB() {
        return MFD_HUGETLB;
    }

    @Override
    public int MFD_HUGE_64KB() {
        return MFD_HUGE_64KB;
    }

    @Override
    public int MFD_HUGE_512KB() {
        return MFD_HUGE_512KB;
    }

    @Override
    public int MFD_HUGE_1MB() {
        return MFD_HUGE_1MB;
    }

    @Override
    public int MFD_HUGE_2MB() {
        return MFD_HUGE_2MB;
    }

    @Override
    public int MFD_HUGE_8MB() {
        return MFD_HUGE_8MB;
    }

    @Override
    public int MFD_HUGE_16MB() {
        return MFD_HUGE_16MB;
    }

    @Override
    public int MFD_HUGE_256MB() {
        return MFD_HUGE_256MB;
    }

    @Override
    public int MFD_HUGE_1GB() {
        return MFD_HUGE_1GB;
    }

    @Override
    public int MFD_HUGE_2GB() {
        return MFD_HUGE_2GB;
    }
    @Override
    public int MFD_HUGE_16GB() {
        return MFD_HUGE_16GB;
    }
    @Override
    public int MADV_DONTNEED() {
        return MADV_DONTNEED;
    }
    @Override
    public int MADV_NORMAL() {
        return MADV_NORMAL;
    }
    @Override
    public int MADV_RANDOM() {
        return MADV_RANDOM;
    }
    @Override
    public int MADV_SEQUENTIAL() {
        return MADV_SEQUENTIAL;
    }
    @Override
    public int MADV_WILLNEED() {
        return MADV_WILLNEED;
    }
    @Override
    public int MADV_REMOVE() {
        return MADV_REMOVE;
    }
    @Override
    public int MADV_DONTFORK() {
        return MADV_DONTFORK;
    }
    @Override
    public int MADV_DOFORK() {
        return MADV_DOFORK;
    }
    @Override
    public int MADV_HWPOISON() {
        return MADV_HWPOISON;
    }
    @Override
    public int MADV_MERGEABLE() {
        return MADV_MERGEABLE;
    }
    @Override
    public int MADV_UNMERGEABLE() {
        return MADV_UNMERGEABLE;
    }
    @Override
    public int MADV_HUGEPAGE() {
        return MADV_HUGEPAGE;
    }
    @Override
    public int MADV_NOHUGEPAGE() {
        return MADV_NOHUGEPAGE;
    }
    @Override
    public int MADV_DONTDUMP() {
        return MADV_DONTDUMP;
    }
    @Override
    public int MADV_DODUMP() {
        return MADV_DODUMP;
    }
    @Override
    public int MADV_WIPEONFORK() {
        return MADV_WIPEONFORK;
    }
    @Override
    public int MADV_KEEPONFORK() {
        return MADV_KEEPONFORK;
    }
}

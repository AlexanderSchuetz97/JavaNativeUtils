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
package eu.aschuetz.nativeutils.api.consts;

/**
 * This file contains some constants from the linux header files.
 */
public interface LinuxConstProvider {
    ///////////////////////////////////////////////
    //Commonly used constants for socket syscalls
    ///////////////////////////////////////////////

    /**
     * domain not specified.
     */
    int AF_UNSPEC();
    /**
     * domain for unix sockets
     */
    int AF_UNIX();

    /**
     * domain for ipv4 sockets
     */
    int AF_INET();

    /**
     * domain for ipv6 sockets
     */
    int AF_INET6();

    /**
     * domain for configuring network interfaces in the kernel.
     */
    int AF_NETLINK();

    /**
     * type for stream based sockets with reliable transport
     */
    int SOCK_STREAM();

    /**
     * type for datagram based sockets with unreliable transport
     */
    int SOCK_DGRAM();

    /**
     * type for raw socket.
     */
    int SOCK_RAW();

    /**
     *  Option for AF_NETLINK.
     *  Receives routing and link updates and may be used to
     *  modify the routing tables.
     */
    int NETLINK_ROUTE();

    ///////////////////////////////////////////////
    //Socketopt constants
    ///////////////////////////////////////////////

    int SOL_SOCKET();
    int SO_DEBUG();
    int SO_REUSEADDR();
    int SO_TYPE();
    int SO_ERROR();
    int SO_DONTROUTE();
    int SO_BROADCAST();
    int SO_SNDBUF() ;
    int SO_RCVBUF() ;
    int SO_SNDBUFFORCE() ;
    int SO_RCVBUFFORCE() ;
    int SO_KEEPALIVE() ;
    int SO_OOBINLINE();
    int SO_NO_CHECK() ;
    int SO_PRIORITY() ;
    int SO_LINGER() ;
    int SO_BSDCOMPAT() ;
    int SO_REUSEPORT() ;
    int SO_PASSCRED();
    int SO_PEERCRED() ;
    int SO_RCVLOWAT() ;
    int SO_SNDLOWAT() ;
    int SO_RCVTIMEO() ;
    int SO_SNDTIMEO() ;
    int SO_SECURITY_AUTHENTICATION() ;
    int SO_SECURITY_ENCRYPTION_TRANSPORT() ;
    int SO_SECURITY_ENCRYPTION_NETWORK() ;
    int SO_BINDTODEVICE() ;
    int SO_ATTACH_FILTER() ;
    int SO_DETACH_FILTER() ;
    int SO_GET_FILTER() ;
    int SO_PEERNAME() ;
    int SO_TIMESTAMP() ;
    int SCM_TIMESTAMP() ;
    int SO_ACCEPTCONN() ;
    int SO_PEERSEC() ;
    int SO_PASSSEC() ;
    int SO_TIMESTAMPNS() ;
    int SCM_TIMESTAMPNS() ;
    int SO_MARK() ;
    int SO_TIMESTAMPING() ;
    int SCM_TIMESTAMPING() ;
    int SO_PROTOCOL() ;
    int SO_DOMAIN() ;
    int SO_RXQ_OVFL() ;
    int SO_WIFI_STATUS() ;
    int SCM_WIFI_STATUS() ;
    int SO_PEEK_OFF() ;
    int SO_NOFCS() ;
    int SO_LOCK_FILTER() ;
    int SO_SELECT_ERR_QUEUE() ;
    int SO_BUSY_POLL() ;
    int SO_MAX_PACING_RATE() ;
    int SO_BPF_EXTENSIONS() ;
    int SO_INCOMING_CPU() ;
    int SO_ATTACH_BPF() ;
    int SO_DETACH_BPF() ;
    int SO_ATTACH_REUSEPORT_CBPF() ;
    int SO_ATTACH_REUSEPORT_EBPF() ;
    int SO_CNX_ADVICE() ;
    int SCM_TIMESTAMPING_OPT_STATS() ;
    int SO_MEMINFO() ;
    int SO_INCOMING_NAPI_ID() ;
    int SO_COOKIE() ;
    int SCM_TIMESTAMPING_PKTINFO() ;
    int SO_PEERGROUPS() ;
    int SO_ZEROCOPY();

    /**
     * CMSG HDR type for file descriptor transfer
     */
    int SCM_RIGHTS();
    //FOR MMAP FLAGS
    int MAP_SHARED();
    int MAP_PRIVATE();

    /////
    // Open flags
    ////

    int O_ACCMODE() ;
    int O_RDONLY() ;
    int O_WRONLY() ;
    int O_RDWR() ;
    int O_CREAT();
    int O_EXCL();
    int O_NOCTTY();
    int O_TRUNC();
    int O_APPEND();
    int O_NONBLOCK();
    int O_NDELAY();
    int O_SYNC() ;
    int O_ASYNC();

    int O_LARGEFILE();
    int O_DIRECTORY();
    int O_NOFOLLOW();
    int O_CLOEXEC();
    int O_DIRECT();
    int O_NOATIME();
    int O_PATH();
    int O_DSYNC();

    int S_IRUSR();
    int S_IWUSR();
    int S_IXUSR();
    int S_IRGRP() ;
    int S_IWGRP() ;
    int S_IXGRP() ;
    int S_IROTH() ;
    int S_IWOTH() ;
    int S_IXOTH() ;
    int S_IRWXU() ;
    int S_IRWXG() ;
    int S_IRWXO() ;

    int IFNAMSIZ();

    //ioctls.h
    int SIOCGIFFLAGS();
    int SIOCSIFFLAGS();
    int SIOCGIFMTU();

    //netlink.h
    short NLM_F_REQUEST();
    short NLM_F_DUMP();
    short NLM_F_MULTI();
    short NLM_F_CREATE();
    short NLM_F_EXCL();
    short NLM_F_ACK();

    short NLMSG_NOOP();
    short NLMSG_ERROR()	;
    short NLMSG_DONE() ;
    short NLMSG_OVERRUN() ;

    //rtnetlink.h
    short RTM_GETLINK() ;
    short RTM_DELADDR() ;
    short RTM_GETADDR() ;
    short RTM_NEWADDR() ;
    byte RT_SCOPE_UNIVERSE();
    short ARPHRD_NETROM();
    short IFLA_IFNAME();
    short IFA_UNSPEC();
    short IFA_ADDRESS();
    short IFA_LOCAL();
    short IFA_LABEL();
    short IFA_BROADCAST();
    short IFA_ANYCAST();
    short IFA_CACHEINFO() ;
    int IFA_F_PERMANENT();
    int IFA_F_SECONDARY() ;

    int IFF_UP();

    int IFF_NO_PI() ;

    //if_tun.h
    int TUNSETIFF();
    int TUNSETPERSIST();
    int TUNGETSNDBUF();


    int RTA_UNSPEC();
    int RTA_DST();
    int RTA_SRC();
    int RTA_IIF();
    int RTA_OIF();
    int RTA_GATEWAY();
    int RTA_PRIORITY() ;
    int RTA_PREFSRC() ;
    int RTA_METRICS() ;
    int RTA_MULTIPATH() ;
    int RTA_PROTOINFO();
    int RTA_FLOW() ;
    int RTA_CACHEINFO() ;
    int RTA_SESSION() ;
    int RTA_MP_ALGO() ;
    int RTA_TABLE() ;
    int RTA_MARK();
    int RTA_MFC_STATS() ;
    int RTA_VIA() ;
    int RTA_NEWDST() ;
    int RTA_PREF() ;
    int RTA_ENCAP_TYPE() ;
    int RTA_ENCAP() ;
    int RTA_EXPIRES() ;
    int RTA_PAD() ;
    int RTA_UID() ;
    int RTA_TTL_PROPAGATE() ;
    int RTA_IP_PROTO() ;
    int RTA_SPORT() ;
    int RTA_DPORT() ;
    int RTA_NH_ID() ;

    int PTHREAD_MUTEX_STALLED();
    int PTHREAD_MUTEX_ROBUST();

    int PTHREAD_PROCESS_SHARED();

    int PTHREAD_PROCESS_PRIVATE();

    int PTHREAD_MUTEX_RECURSIVE();
    int PTHREAD_MUTEX_ERRORCHECK();
    int PTHREAD_MUTEX_DEFAULT();
    int PTHREAD_MUTEX_NORMAL();

    //memfd.h
    int MFD_CLOEXEC();

    int MFD_ALLOW_SEALING();

    int MFD_HUGETLB();
    int MFD_HUGE_64KB();
    int MFD_HUGE_512KB();
    int MFD_HUGE_1MB();
    int MFD_HUGE_2MB();
    int MFD_HUGE_8MB();
    int MFD_HUGE_16MB();
    int MFD_HUGE_256MB();
    int MFD_HUGE_1GB();
    int MFD_HUGE_2GB();
    int MFD_HUGE_16GB();

    int MADV_DONTNEED();

    int MADV_NORMAL();

    int MADV_RANDOM();

    int MADV_SEQUENTIAL();

    int MADV_WILLNEED();

    int MADV_REMOVE();

    int MADV_DONTFORK();

    int MADV_DOFORK();

    int MADV_HWPOISON();

    int MADV_MERGEABLE();

    int MADV_UNMERGEABLE();

    int MADV_HUGEPAGE();

    int MADV_NOHUGEPAGE();

    int MADV_DONTDUMP();

    int MADV_DODUMP();

    int MADV_WIPEONFORK();

    int MADV_KEEPONFORK();
}


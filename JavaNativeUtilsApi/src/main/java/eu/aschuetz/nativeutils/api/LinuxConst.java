package eu.aschuetz.nativeutils.api;

import eu.aschuetz.nativeutils.api.consts.DefaultLinuxConstProvider;
import eu.aschuetz.nativeutils.api.consts.LinuxConstProvider;

public class LinuxConst {
    /**
     * domain not specified.
     */
   public static final int AF_UNSPEC; 

    /**
     * domain for unix sockets
     */
   public static final int AF_UNIX; 

    /**
     * domain for ipv4 sockets
     */
   public static final int AF_INET; 

    /**
     * domain for ipv6 sockets
     */
   public static final int AF_INET6; 

    /**
     * domain for configuring network interfaces in the kernel.
     */
   public static final int AF_NETLINK; 

    /**
     * type for stream based sockets with reliable transport
     */
   public static final int SOCK_STREAM; 

    /**
     * type for datagram based sockets with unreliable transport
     */
   public static final int SOCK_DGRAM; 

    /**
     * type for raw socket.
     */
   public static final int SOCK_RAW; 

    /**
     *  Option for AF_NETLINK.
     *  Receives routing and link updates and may be used to
     *  modify the routing tables.
     */
   public static final int NETLINK_ROUTE; 

    ///////////////////////////////////////////////
    //Socketopt constants
    ///////////////////////////////////////////////

   public static final int SOL_SOCKET; 
   public static final int SO_DEBUG; 
   public static final int SO_REUSEADDR; 
   public static final int SO_TYPE; 
   public static final int SO_ERROR; 
   public static final int SO_DONTROUTE; 
   public static final int SO_BROADCAST; 
   public static final int SO_SNDBUF; 
   public static final int SO_RCVBUF; 
   public static final int SO_SNDBUFFORCE; 
   public static final int SO_RCVBUFFORCE; 
   public static final int SO_KEEPALIVE; 
   public static final int SO_OOBINLINE; 
   public static final int SO_NO_CHECK; 
   public static final int SO_PRIORITY; 
   public static final int SO_LINGER; 
   public static final int SO_BSDCOMPAT; 
   public static final int SO_REUSEPORT; 
   public static final int SO_PASSCRED; 
   public static final int SO_PEERCRED; 
   public static final int SO_RCVLOWAT; 
   public static final int SO_SNDLOWAT; 
   public static final int SO_RCVTIMEO; 
   public static final int SO_SNDTIMEO; 
   public static final int SO_SECURITY_AUTHENTICATION; 
   public static final int SO_SECURITY_ENCRYPTION_TRANSPORT; 
   public static final int SO_SECURITY_ENCRYPTION_NETWORK; 
   public static final int SO_BINDTODEVICE; 
   public static final int SO_ATTACH_FILTER; 
   public static final int SO_DETACH_FILTER; 
   public static final int SO_GET_FILTER; 
   public static final int SO_PEERNAME; 
   public static final int SO_TIMESTAMP; 
   public static final int SCM_TIMESTAMP; 
   public static final int SO_ACCEPTCONN; 
   public static final int SO_PEERSEC; 
   public static final int SO_PASSSEC; 
   public static final int SO_TIMESTAMPNS; 
   public static final int SCM_TIMESTAMPNS; 
   public static final int SO_MARK; 
   public static final int SO_TIMESTAMPING; 
   public static final int SCM_TIMESTAMPING; 
   public static final int SO_PROTOCOL; 
   public static final int SO_DOMAIN; 
   public static final int SO_RXQ_OVFL; 
   public static final int SO_WIFI_STATUS; 
   public static final int SCM_WIFI_STATUS; 
   public static final int SO_PEEK_OFF; 
   public static final int SO_NOFCS; 
   public static final int SO_LOCK_FILTER; 
   public static final int SO_SELECT_ERR_QUEUE; 
   public static final int SO_BUSY_POLL; 
   public static final int SO_MAX_PACING_RATE; 
   public static final int SO_BPF_EXTENSIONS; 
   public static final int SO_INCOMING_CPU; 
   public static final int SO_ATTACH_BPF; 
   public static final int SO_DETACH_BPF; 
   public static final int SO_ATTACH_REUSEPORT_CBPF; 
   public static final int SO_ATTACH_REUSEPORT_EBPF; 
   public static final int SO_CNX_ADVICE; 
   public static final int SCM_TIMESTAMPING_OPT_STATS; 
   public static final int SO_MEMINFO; 
   public static final int SO_INCOMING_NAPI_ID; 
   public static final int SO_COOKIE; 
   public static final int SCM_TIMESTAMPING_PKTINFO; 
   public static final int SO_PEERGROUPS; 
   public static final int SO_ZEROCOPY; 

    /**
     * CMSG HDR type for file descriptor transfer
     */
   public static final int SCM_RIGHTS; 
    //FOR MMAP FLAGS
   public static final int MAP_SHARED; 
   public static final int MAP_PRIVATE; 

    /////
    // Open flags
    ////

   public static final int O_ACCMODE; 
   public static final int O_RDONLY; 
   public static final int O_WRONLY; 
   public static final int O_RDWR; 
   public static final int O_CREAT; 
   public static final int O_EXCL; 
   public static final int O_NOCTTY; 
   public static final int O_TRUNC; 
   public static final int O_APPEND; 
   public static final int O_NONBLOCK; 
   public static final int O_NDELAY;
   public static final int O_SYNC;
   public static final int O_ASYNC;
   public static final int O_LARGEFILE;
   public static final int O_DIRECTORY; 
   public static final int O_NOFOLLOW; 
   public static final int O_CLOEXEC; 
   public static final int O_DIRECT; 
   public static final int O_NOATIME; 
   public static final int O_PATH; 
   public static final int O_DSYNC; 

   public static final int S_IRUSR; 
   public static final int S_IWUSR; 
   public static final int S_IXUSR; 
   public static final int S_IRGRP;
   public static final int S_IWGRP;
   public static final int S_IXGRP;
   public static final int S_IROTH;
   public static final int S_IWOTH;
   public static final int S_IXOTH;
   public static final int S_IRWXU;
   public static final int S_IRWXG;
   public static final int S_IRWXO; 

   public static final int IFNAMSIZ; 

    //ioctls.h
   public static final int SIOCGIFFLAGS; 
   public static final int SIOCSIFFLAGS; 
   public static final int SIOCGIFMTU; 

    //netlink.h
   public static final short NLM_F_REQUEST; 
   public static final short NLM_F_DUMP; 
   public static final short NLM_F_MULTI; 
   public static final short NLM_F_CREATE;
   public static final short NLM_F_EXCL; 
   public static final short NLM_F_ACK; 

   public static final short NLMSG_NOOP; 
   public static final short NLMSG_ERROR;
   public static final short NLMSG_DONE; 
   public static final short NLMSG_OVERRUN; 

    //rtnetlink.h
   public static final short RTM_GETLINK; 
   public static final short RTM_DELADDR; 
   public static final short RTM_GETADDR; 
   public static final short RTM_NEWADDR;
   public static final byte RT_SCOPE_UNIVERSE; 
   public static final short ARPHRD_NETROM; 
   public static final short IFLA_IFNAME; 
   public static final short IFA_UNSPEC; 
   public static final short IFA_ADDRESS; 
   public static final short IFA_LOCAL; 
   public static final short IFA_LABEL; 
   public static final short IFA_BROADCAST; 
   public static final short IFA_ANYCAST; 
   public static final short IFA_CACHEINFO; 
   public static final int IFA_F_PERMANENT; 
   public static final int IFA_F_SECONDARY; 

   public static final int IFF_UP; 

   public static final int IFF_NO_PI; 

    //if_tun.h
   public static final int TUNSETIFF;
   public static final int TUNSETPERSIST;
   public static final int TUNGETSNDBUF;


   public static final int RTA_UNSPEC; 
   public static final int RTA_DST; 
   public static final int RTA_SRC; 
   public static final int RTA_IIF; 
   public static final int RTA_OIF; 
   public static final int RTA_GATEWAY; 
   public static final int RTA_PRIORITY; 
   public static final int RTA_PREFSRC; 
   public static final int RTA_METRICS; 
   public static final int RTA_MULTIPATH; 
   public static final int RTA_PROTOINFO;
   public static final int RTA_FLOW; 
   public static final int RTA_CACHEINFO; 
   public static final int RTA_SESSION;
   public static final int RTA_MP_ALGO;
   public static final int RTA_TABLE; 
   public static final int RTA_MARK; 
   public static final int RTA_MFC_STATS; 
   public static final int RTA_VIA; 
   public static final int RTA_NEWDST; 
   public static final int RTA_PREF; 
   public static final int RTA_ENCAP_TYPE; 
   public static final int RTA_ENCAP; 
   public static final int RTA_EXPIRES; 
   public static final int RTA_PAD; 
   public static final int RTA_UID; 
   public static final int RTA_TTL_PROPAGATE; 
   public static final int RTA_IP_PROTO; 
   public static final int RTA_SPORT; 
   public static final int RTA_DPORT; 
   public static final int RTA_NH_ID; 

   public static final int PTHREAD_MUTEX_STALLED; 
   public static final int PTHREAD_MUTEX_ROBUST; 

   public static final int PTHREAD_PROCESS_SHARED; 

   public static final int PTHREAD_PROCESS_PRIVATE; 

   public static final int PTHREAD_MUTEX_RECURSIVE; 
   public static final int PTHREAD_MUTEX_ERRORCHECK; 
   public static final int PTHREAD_MUTEX_DEFAULT; 
   public static final int PTHREAD_MUTEX_NORMAL;

   static {

      LinuxConstProvider provider = null;
      try {
         NativeUtil utils = NativeUtils.get();
         if (NativeUtils.isLinux()) {
            provider = NativeUtils.getLinuxUtil().getLinuxConstProvider();
         } else {
            provider = new DefaultLinuxConstProvider(); //fallback to Linux amd64 constants
         }
      } catch (Throwable t) {
         provider = new DefaultLinuxConstProvider();
      }

      AF_UNSPEC = provider.AF_UNSPEC();
      AF_UNIX = provider.AF_UNIX();
      AF_INET = provider.AF_INET();
      AF_INET6 = provider.AF_INET6();
      AF_NETLINK = provider.AF_NETLINK();
      SOCK_STREAM = provider.SOCK_STREAM();
      SOCK_DGRAM = provider.SOCK_DGRAM();
      SOCK_RAW = provider.SOCK_RAW();
      NETLINK_ROUTE = provider.NETLINK_ROUTE();
      SOL_SOCKET = provider.SOL_SOCKET();
      SO_DEBUG = provider.SO_DEBUG();
      SO_REUSEADDR = provider.SO_REUSEADDR();
      SO_TYPE = provider.SO_TYPE();
      SO_ERROR = provider.SO_ERROR();
      SO_DONTROUTE = provider.SO_DONTROUTE();
      SO_BROADCAST = provider.SO_BROADCAST();
      SO_SNDBUF = provider.SO_SNDBUF();
      SO_RCVBUF = provider.SO_RCVBUF();
      SO_SNDBUFFORCE = provider.SO_SNDBUFFORCE();
      SO_RCVBUFFORCE = provider.SO_RCVBUFFORCE();
      SO_KEEPALIVE = provider.SO_KEEPALIVE();
      SO_OOBINLINE = provider.SO_OOBINLINE();
      SO_NO_CHECK = provider.SO_NO_CHECK();
      SO_PRIORITY = provider.SO_PRIORITY();
      SO_LINGER = provider.SO_LINGER();
      SO_BSDCOMPAT = provider.SO_BSDCOMPAT();
      SO_REUSEPORT = provider.SO_REUSEPORT();
      SO_PASSCRED = provider.SO_PASSCRED();
      SO_PEERCRED = provider.SO_PEERCRED();
      SO_RCVLOWAT = provider.SO_RCVLOWAT();
      SO_SNDLOWAT = provider.SO_SNDLOWAT();
      SO_RCVTIMEO = provider.SO_RCVTIMEO();
      SO_SNDTIMEO = provider.SO_SNDTIMEO();
      SO_SECURITY_AUTHENTICATION = provider.SO_SECURITY_AUTHENTICATION();
      SO_SECURITY_ENCRYPTION_TRANSPORT = provider.SO_SECURITY_ENCRYPTION_TRANSPORT();
      SO_SECURITY_ENCRYPTION_NETWORK = provider.SO_SECURITY_ENCRYPTION_NETWORK();
      SO_BINDTODEVICE = provider.SO_BINDTODEVICE();
      SO_ATTACH_FILTER = provider.SO_ATTACH_FILTER();
      SO_DETACH_FILTER = provider.SO_DETACH_FILTER();
      SO_GET_FILTER = provider.SO_GET_FILTER();
      SO_PEERNAME = provider.SO_PEERNAME();
      SO_TIMESTAMP = provider.SO_TIMESTAMP();
      SCM_TIMESTAMP = provider.SCM_TIMESTAMP();
      SO_ACCEPTCONN = provider.SO_ACCEPTCONN();
      SO_PEERSEC = provider.SO_PEERSEC();
      SO_PASSSEC = provider.SO_PASSSEC();
      SO_TIMESTAMPNS = provider.SO_TIMESTAMPNS();
      SCM_TIMESTAMPNS = provider.SCM_TIMESTAMPNS();
      SO_MARK = provider.SO_MARK();
      SO_TIMESTAMPING = provider.SO_TIMESTAMPING();
      SCM_TIMESTAMPING = provider.SCM_TIMESTAMPING();
      SO_PROTOCOL = provider.SO_PROTOCOL();
      SO_DOMAIN = provider.SO_DOMAIN();
      SO_RXQ_OVFL = provider.SO_RXQ_OVFL();
      SO_WIFI_STATUS = provider.SO_WIFI_STATUS();
      SCM_WIFI_STATUS = provider.SCM_WIFI_STATUS();
      SO_PEEK_OFF = provider.SO_PEEK_OFF();
      SO_NOFCS = provider.SO_NOFCS();
      SO_LOCK_FILTER = provider.SO_LOCK_FILTER();
      SO_SELECT_ERR_QUEUE = provider.SO_SELECT_ERR_QUEUE();
      SO_BUSY_POLL = provider.SO_BUSY_POLL();
      SO_MAX_PACING_RATE = provider.SO_MAX_PACING_RATE();
      SO_BPF_EXTENSIONS = provider.SO_BPF_EXTENSIONS();
      SO_INCOMING_CPU = provider.SO_INCOMING_CPU();
      SO_ATTACH_BPF = provider.SO_ATTACH_BPF();
      SO_DETACH_BPF = provider.SO_DETACH_BPF();
      SO_ATTACH_REUSEPORT_CBPF = provider.SO_ATTACH_REUSEPORT_CBPF();
      SO_ATTACH_REUSEPORT_EBPF = provider.SO_ATTACH_REUSEPORT_EBPF();
      SO_CNX_ADVICE = provider.SO_CNX_ADVICE();
      SCM_TIMESTAMPING_OPT_STATS = provider.SCM_TIMESTAMPING_OPT_STATS();
      SO_MEMINFO = provider.SO_MEMINFO();
      SO_INCOMING_NAPI_ID = provider.SO_INCOMING_NAPI_ID();
      SO_COOKIE = provider.SO_COOKIE();
      SCM_TIMESTAMPING_PKTINFO = provider.SCM_TIMESTAMPING_PKTINFO();
      SO_PEERGROUPS = provider.SO_PEERGROUPS();
      SO_ZEROCOPY = provider.SO_ZEROCOPY();
      SCM_RIGHTS = provider.SCM_RIGHTS();
      MAP_SHARED = provider.MAP_SHARED();
      MAP_PRIVATE = provider.MAP_PRIVATE();
      O_ACCMODE = provider.O_ACCMODE();
      O_RDONLY = provider.O_RDONLY();
      O_WRONLY = provider.O_WRONLY();
      O_RDWR = provider.O_RDWR();
      O_CREAT = provider.O_CREAT();
      O_EXCL = provider.O_EXCL();
      O_NOCTTY = provider.O_NOCTTY();
      O_TRUNC = provider.O_TRUNC();
      O_APPEND = provider.O_APPEND();
      O_NONBLOCK = provider.O_NONBLOCK();
      O_NDELAY = provider.O_NDELAY();
      O_SYNC = provider.O_SYNC();
      O_ASYNC = provider.O_ASYNC();
      O_LARGEFILE = provider.O_LARGEFILE();
      O_DIRECTORY = provider.O_DIRECTORY();
      O_NOFOLLOW = provider.O_NOFOLLOW();
      O_CLOEXEC = provider.O_CLOEXEC();
      O_DIRECT = provider.O_DIRECT();
      O_NOATIME = provider.O_NOATIME();
      O_PATH = provider.O_PATH();
      O_DSYNC = provider.O_DSYNC();
      S_IRUSR = provider.S_IRUSR();
      S_IWUSR = provider.S_IWUSR();
      S_IXUSR = provider.S_IXUSR();
      S_IRGRP = provider.S_IRGRP();
      S_IWGRP = provider.S_IWGRP();
      S_IXGRP = provider.S_IXGRP();
      S_IROTH = provider.S_IROTH();
      S_IWOTH = provider.S_IWOTH();
      S_IXOTH = provider.S_IXOTH();
      S_IRWXU = provider.S_IRWXU();
      S_IRWXG = provider.S_IRWXG();
      S_IRWXO = provider.S_IRWXO();
      IFNAMSIZ = provider.IFNAMSIZ();
      SIOCGIFFLAGS = provider.SIOCGIFFLAGS();
      SIOCSIFFLAGS = provider.SIOCSIFFLAGS();
      SIOCGIFMTU = provider.SIOCGIFMTU();
      NLM_F_REQUEST = provider.NLM_F_REQUEST();
      NLM_F_DUMP = provider.NLM_F_DUMP();
      NLM_F_MULTI = provider.NLM_F_MULTI();
      NLM_F_CREATE= provider.NLM_F_CREATE();
      NLM_F_EXCL = provider.NLM_F_EXCL();
      NLM_F_ACK = provider.NLM_F_ACK();
      NLMSG_NOOP = provider.NLMSG_NOOP();
      NLMSG_ERROR =	provider.NLMSG_ERROR();
      NLMSG_DONE = provider.NLMSG_DONE();
      NLMSG_OVERRUN = provider.NLMSG_OVERRUN();
      RTM_GETLINK = provider.RTM_GETLINK();
      RTM_DELADDR = provider.RTM_DELADDR();
      RTM_GETADDR = provider.RTM_GETADDR();
      RTM_NEWADDR = provider.RTM_NEWADDR();
      RT_SCOPE_UNIVERSE = provider.RT_SCOPE_UNIVERSE();
      ARPHRD_NETROM = provider.ARPHRD_NETROM();
      IFLA_IFNAME = provider.IFLA_IFNAME();
      IFA_UNSPEC = provider.IFA_UNSPEC();
      IFA_ADDRESS = provider.IFA_ADDRESS();
      IFA_LOCAL = provider.IFA_LOCAL();
      IFA_LABEL = provider.IFA_LABEL();
      IFA_BROADCAST = provider.IFA_BROADCAST();
      IFA_ANYCAST = provider.IFA_ANYCAST();
      IFA_CACHEINFO = provider.IFA_CACHEINFO();
      IFA_F_PERMANENT = provider.IFA_F_PERMANENT();
      IFA_F_SECONDARY = provider.IFA_F_SECONDARY();
      IFF_UP = provider.IFF_UP();
      IFF_NO_PI = provider.IFF_NO_PI();
      TUNSETIFF = provider.TUNSETIFF();
      TUNSETPERSIST = provider.TUNSETPERSIST();
      TUNGETSNDBUF = provider.TUNGETSNDBUF();
      RTA_UNSPEC = provider.RTA_UNSPEC();
      RTA_DST = provider.RTA_DST();
      RTA_SRC = provider.RTA_SRC();
      RTA_IIF = provider.RTA_IIF();
      RTA_OIF = provider.RTA_OIF();
      RTA_GATEWAY = provider.RTA_GATEWAY();
      RTA_PRIORITY = provider.RTA_PRIORITY();
      RTA_PREFSRC = provider.RTA_PREFSRC();
      RTA_METRICS = provider.RTA_METRICS();
      RTA_MULTIPATH = provider.RTA_MULTIPATH();
      RTA_PROTOINFO = provider.RTA_PROTOINFO();
      RTA_FLOW = provider.RTA_FLOW();
      RTA_CACHEINFO = provider.RTA_CACHEINFO();
      RTA_SESSION = provider.RTA_SESSION();
      RTA_MP_ALGO = provider.RTA_MP_ALGO();
      RTA_TABLE = provider.RTA_TABLE();
      RTA_MARK = provider.RTA_MARK();
      RTA_MFC_STATS = provider.RTA_MFC_STATS();
      RTA_VIA = provider.RTA_VIA();
      RTA_NEWDST = provider.RTA_NEWDST();
      RTA_PREF = provider.RTA_PREF();
      RTA_ENCAP_TYPE = provider.RTA_ENCAP_TYPE();
      RTA_ENCAP = provider.RTA_ENCAP();
      RTA_EXPIRES = provider.RTA_EXPIRES();
      RTA_PAD = provider.RTA_PAD();
      RTA_UID = provider.RTA_UID();
      RTA_TTL_PROPAGATE = provider.RTA_TTL_PROPAGATE();
      RTA_IP_PROTO = provider.RTA_IP_PROTO();
      RTA_SPORT = provider.RTA_SPORT();
      RTA_DPORT = provider.RTA_DPORT();
      RTA_NH_ID = provider.RTA_NH_ID();
      PTHREAD_MUTEX_STALLED = provider.PTHREAD_MUTEX_STALLED();
      PTHREAD_MUTEX_ROBUST = provider.PTHREAD_MUTEX_ROBUST();
      PTHREAD_PROCESS_SHARED = provider.PTHREAD_PROCESS_SHARED();
      PTHREAD_PROCESS_PRIVATE = provider.PTHREAD_PROCESS_PRIVATE();
      PTHREAD_MUTEX_RECURSIVE = provider.PTHREAD_MUTEX_RECURSIVE();
      PTHREAD_MUTEX_ERRORCHECK = provider.PTHREAD_MUTEX_ERRORCHECK();
      PTHREAD_MUTEX_DEFAULT = provider.PTHREAD_MUTEX_DEFAULT();
      PTHREAD_MUTEX_NORMAL = provider.PTHREAD_MUTEX_NORMAL();
   }
}

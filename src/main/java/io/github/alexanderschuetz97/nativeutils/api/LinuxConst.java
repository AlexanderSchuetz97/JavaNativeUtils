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
package io.github.alexanderschuetz97.nativeutils.api;

/**
 * This file contains some constants from the linux header files.
 */
public interface LinuxConst {
    ///////////////////////////////////////////////
    //Commonly used constants for socket syscalls
    ///////////////////////////////////////////////

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
     * type for stream based sockets with reliable transport
     */
    int SOCK_STREAM = 1;

    /**
     * type for datagram based sockets with unreliable transport
     */
    int SOCK_DGRAM = 2;

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
    int O_FSYNC = O_SYNC;
    int O_ASYNC = 020000;
    int O_LARGEFILE = 0100000;
    int O_DIRECTORY = 0200000;
    int O_NOFOLLOW = 0400000;
    int O_CLOEXEC = 02000000;
    int O_DIRECT = 040000;
    int O_NOATIME = 01000000;
    int O_PATH = 010000000;
    int O_DSYNC = 010000;
    int O_RSYNC = (020000000 | O_DIRECTORY);

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
}


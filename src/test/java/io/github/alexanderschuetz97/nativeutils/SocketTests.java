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
package io.github.alexanderschuetz97.nativeutils;

import io.github.alexanderschuetz97.nativeutils.api.LinuxConst;
import io.github.alexanderschuetz97.nativeutils.api.LinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeMemory;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import io.github.alexanderschuetz97.nativeutils.api.PointerHandler;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import io.github.alexanderschuetz97.nativeutils.api.structs.Cmsghdr;
import io.github.alexanderschuetz97.nativeutils.api.structs.Iovec;
import io.github.alexanderschuetz97.nativeutils.api.structs.Msghdr;
import io.github.alexanderschuetz97.nativeutils.api.structs.Sockaddr;
import io.github.alexanderschuetz97.nativeutils.api.structs.Stat;
import org.junit.Ignore;
import org.junit.Test;

import java.io.SyncFailedException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.Collection;

public class SocketTests {

    @Test
    @Ignore
    public void test() throws Exception {
        LinuxNativeUtil lni = NativeUtils.getLinuxUtil();
        int fd = lni.socket(LinuxConst.AF_INET6, LinuxConst.SOCK_STREAM, 0);

        lni.setsockopt(fd, 1, 21, lni.to_struct_timeval(5000));
        byte[] buf2 = lni.getsockopt(fd, LinuxConst.SOL_SOCKET, LinuxConst.SO_SNDTIMEO, 64);
        System.out.println(lni.from_struct_timeval(buf2));

        InetAddress inetAddress = InetAddress.getByName("0:0:0:0:0:0:0:1");
        Sockaddr sockaddr = lni.to_sockaddr_in(new InetSocketAddress(inetAddress, 80));
        try {
            lni.connect(fd, sockaddr);
        } catch (Exception exc) {
            exc.printStackTrace();
        }

        byte[] buf = "GET / HTTP/1.1\r\nHost: MEEP\r\n\r\n".getBytes(StandardCharsets.UTF_8);
        int i = lni.write(fd, buf, 0, buf.length);
        System.out.println(i);
        System.out.println(buf.length);

        Sockaddr raddr = new Sockaddr();
        //Thread.sleep(2000);
        byte[] bb = new byte[4096];
        int rr = lni.recvfrom(fd, bb, 0, 4096, 0, raddr);
        System.out.println(rr);
        System.out.println(new String(bb, 0, rr, StandardCharsets.UTF_8));

        lni.close(fd);
    }

    @Test
    @Ignore
    public void test2() throws Exception {
        final LinuxNativeUtil lni = NativeUtils.getLinuxUtil();
        int i = lni.socket(LinuxConst.AF_UNIX, LinuxConst.SOCK_STREAM, 0);
        lni.setsockopt(i,LinuxConst.SOL_SOCKET, LinuxConst.SO_RCVTIMEO, lni.to_struct_timeval(5000));
        lni.connect(i, lni.to_sockaddr_un("/tmp/shmemsock"));
        Iovec buf = new Iovec(8);
        byte[] ctl = new byte[1024];
        byte[] payload = buf.getPayload();

        Sockaddr sockaddr = new Sockaddr();
        Msghdr msghdr = new Msghdr(new Iovec[]{buf}, sockaddr, ctl);
        int x = lni.recvmsg(i, msghdr, 0);
        System.out.println(x);
        System.out.println(lni.from_sockaddr_un(sockaddr));


        x = lni.recvmsg(i, msghdr, 0);
        System.out.println(x);
        System.out.println(lni.from_sockaddr_un(sockaddr));

        int peer = (payload[0] & 0xff) + ((payload[1] & 0xff) << 8);
        System.out.println(peer);

        x = lni.recvmsg(i, msghdr, 0);
        System.out.println(x);
        System.out.println(lni.from_sockaddr_un(sockaddr));

        Collection<Cmsghdr> parsed = lni.parseCMSG_HDR(msghdr.getMsg_control(), msghdr.getMsg_controllen());
        System.out.println(parsed);
        Cmsghdr first = parsed.iterator().next();
        byte[] pl = first.getPayload();
        int fd = (pl[0] & 0xff) + ((pl[1] & 0xff) << 8) + ((pl[2] & 0xff) << 16) + ((pl[3] & 0xff) << 24);
        System.out.println(fd);
        Stat stat = lni.fstat(fd);
        System.out.println(stat.getSize());
        System.out.println(lni.getpagesize());

        long memPtr = lni.mmap(fd, stat.getSize(), LinuxConst.MAP_SHARED, true, true, 0);
        NativeMemory mem = lni.pointer(memPtr, stat.getSize(), new PointerHandler() {
            @Override
            public void handleClose(long ptr, long size, boolean read, boolean write) {
                try {
                    lni.munmap(ptr, size);
                } catch (UnknownNativeErrorException e) {
                    //DC
                }
            }

            @Override
            public void handleSync(long ptr, long size, boolean read, boolean write, long offset, long length, boolean invalidate) throws SyncFailedException {

            }
        });

        System.out.println(mem);
        mem.write(1, 4);
        System.out.println(mem.readInt(0));
        mem.close();


        lni.close(i);
    }
}

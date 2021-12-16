//
// Copyright Alexander Schütz, 2021
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
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import io.github.alexanderschuetz97.nativeutils.api.structs.PollFD;
import io.github.alexanderschuetz97.nativeutils.api.structs.Sockaddr;
import org.junit.Ignore;
import org.junit.Test;

import java.net.Inet4Address;
import java.net.Inet6Address;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.EnumSet;

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
}

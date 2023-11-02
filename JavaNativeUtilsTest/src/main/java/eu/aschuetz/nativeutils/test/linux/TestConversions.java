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
package eu.aschuetz.nativeutils.test.linux;

import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.structs.GUID;
import eu.aschuetz.nativeutils.api.structs.Sockaddr;
import org.junit.Assert;
import org.junit.Test;

import java.net.InetAddress;
import java.net.InetSocketAddress;

public class TestConversions {

    @Test
    public void testTimeVal() {
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        byte[] timeval = util.to_struct_timeval(12345667);
        long l = util.from_struct_timeval(timeval);
        Assert.assertEquals(12345667L, l);
    }

    @Test
    public void testInetAddress4() throws Exception{
        byte[] b = new byte[] {1,2,3,4};
        InetAddress in = InetAddress.getByAddress(b);
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        Sockaddr sockaddr = util.to_sockaddr_in(new InetSocketAddress(in, 64641));
        InetSocketAddress socketAddress = util.from_sockaddr_in(sockaddr);
        byte[] d = socketAddress.getAddress().getAddress();
        Assert.assertArrayEquals(b, d);
        Assert.assertEquals(64641, socketAddress.getPort());

    }

    @Test
    public void testInetAddress6() throws Exception{
        byte[] b = new byte[] {1,2,3,4, 5, 6, 7, 8, 9, 10, 11 , 12 ,13, 14 ,15, 16};
        InetAddress in = InetAddress.getByAddress(b);
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        Sockaddr sockaddr = util.to_sockaddr_in(new InetSocketAddress(in, 64641));
        InetSocketAddress socketAddress = util.from_sockaddr_in(sockaddr);
        byte[] d = socketAddress.getAddress().getAddress();
        Assert.assertArrayEquals(b, d);
        Assert.assertEquals(64641, socketAddress.getPort());
    }

    @Test
    public void testAFUnix() throws Exception {
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 107; i++) {
            sb.append('A');
            String s = sb.toString();
            Sockaddr sockaddr = util.to_sockaddr_un(s);
            String s2 = util.from_sockaddr_un(sockaddr);
            Assert.assertEquals(""+i, s, s2);
        }
    }

    @Test
    public void testGUID() {
        GUID guid = new GUID("6B29FC40-CA47-1067-B31D-00DD010662DA");
        Assert.assertEquals("6B29FC40-CA47-1067-B31D-00DD010662DA", guid.toString());
    }
}

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
package eu.aschuetz.nativeutils.test.linux;

import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Test;

public class IfTests {

    @Test
    public void test() throws Exception {
        LinuxNativeUtil lni = NativeUtils.getLinuxUtil();
        String res = lni.if_indextoname(1);
        Assert.assertEquals("lo", res);
    }

    @Test
    public void test2() throws Exception {
        LinuxNativeUtil lni = NativeUtils.getLinuxUtil();
        int idx = lni.if_nametoindex("lo");
        Assert.assertEquals(1, idx);
    }

    @Test
    public void test3() throws Exception {
        LinuxNativeUtil lni = NativeUtils.getLinuxUtil();
        int idx = lni.if_nametoindex("feelsBadMan");
        Assert.assertEquals(0, idx);
    }

    @Test
    public void test4() throws Exception {
        LinuxNativeUtil lni = NativeUtils.getLinuxUtil();
        String res = lni.if_indextoname(1829381293);
        Assert.assertNull(res);
    }
}

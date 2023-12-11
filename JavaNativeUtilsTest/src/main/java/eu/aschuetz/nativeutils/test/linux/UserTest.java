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
import eu.aschuetz.nativeutils.api.structs.Group;
import eu.aschuetz.nativeutils.api.structs.Passwd;
import org.junit.Assert;
import org.junit.Assume;
import org.junit.Test;

import java.util.Arrays;

public class UserTest {

    @Test
    public void testUser() throws Exception {
        LinuxNativeUtil lnu = NativeUtils.getLinuxUtil();
        long uid = lnu.getuid();
        Passwd passwd = lnu.getpwuid_r(uid);
        Passwd passwd2 = lnu.getpwnam_r(passwd.getPw_name());
        Assert.assertEquals(passwd, passwd2);

        String username = passwd.getPw_name();

        long[] gid = lnu.getgrouplist(username, passwd.getPw_gid());
        boolean found = false;
        for (long l : gid) {
            if (l == passwd.getPw_gid()) {
                found = true;
                continue;
            }

            Group group = lnu.getgrgid_r(l);
            Assert.assertNotNull(group.getGr_name());
            Assert.assertTrue(group.getGr_mem().contains(username));
        }

        Assert.assertTrue(Arrays.toString(gid) + "->" + passwd.getPw_gid(), found);
    }

    @Test
    public void testUser2() throws Exception {
        LinuxNativeUtil lnu = NativeUtils.getLinuxUtil();
        long uid = lnu.getuid();
        String username = null;
        try {
            username = lnu.getlogin_r();
        } catch (IllegalStateException e) {
            //No terminal/stdin etc
            Assume.assumeFalse("The calling process has no controlling terminal.".equals(e.getMessage()));
            Assume.assumeFalse("Standard input didn't refer to a terminal.".equals(e.getMessage()));
        }

        Passwd passwd = lnu.getpwuid_r(uid);
        Assert.assertEquals(passwd.getPw_name(), username);
    }
}

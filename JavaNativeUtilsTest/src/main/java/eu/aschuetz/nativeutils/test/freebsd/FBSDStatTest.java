
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
package eu.aschuetz.nativeutils.test.freebsd;

import eu.aschuetz.nativeutils.api.FreeBSDNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.structs.Stat;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;

public class FBSDStatTest {

    String path1;

    @Before
    public void before() {
        Random rng = new Random();
        path1 = "/tmp/testo" + Math.abs(rng.nextInt());
    }

    @After
    public void after() {
        new File(path1).delete();
    }

    @Test
    public void testToString() throws Exception{
        FreeBSDNativeUtil util = NativeUtils.getFreeBSDUtil();
        Stat stat = util.stat("/tmp");
        String str = stat.toString();
        System.out.println(str);
        Assert.assertNotNull(str);
    }

    @Test
    public void testNotFound() throws Exception {
        FreeBSDNativeUtil util = NativeUtils.getFreeBSDUtil();
        try {
            util.stat(path1);
            Assert.fail("FileNotFoundException expected");
        } catch (FileNotFoundException exception) {
            Assert.assertEquals(path1, exception.getMessage());
        }
    }


    @Test
    public void testSimple() throws Exception {
        FreeBSDNativeUtil util = NativeUtils.getFreeBSDUtil();
        new File(path1).createNewFile();
        Stat s = util.stat(path1);
        Assert.assertEquals(0, s.getSize());
        Assert.assertEquals(1, s.getBlocks()); //ZFS
        Assert.assertTrue(s.getDev() != 0);
        Assert.assertTrue(s.getIno() != 0);
        Assert.assertTrue(s.getAtime() > 0);
        Assert.assertTrue(s.getAtime() + " " + s.getMtime() + " " + s.getCtime(), s.getAtime() == s.getMtime() && s.getMtime() == s.getCtime());
        Assert.assertTrue(s.isRegularFile());
    }
}

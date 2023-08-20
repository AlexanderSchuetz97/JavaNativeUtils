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

import io.github.alexanderschuetz97.nativeutils.api.LinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import io.github.alexanderschuetz97.nativeutils.api.structs.Stat;
import io.github.alexanderschuetz97.nativeutils.api.structs.Statvfs;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Random;

public class LinuxStatTest {

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
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        Stat stat = util.stat("/tmp");
        String str = stat.toString();
        System.out.println(str);
        Assert.assertNotNull(str);
    }

    @Test
    public void testNotFound() throws Exception {
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        try {
            util.stat(path1);
            Assert.fail("FileNotFoundException expected");
        } catch (FileNotFoundException exception) {
            Assert.assertEquals(path1, exception.getMessage());
        }
    }

    @Test
    public void testvfs() throws IOException, UnknownNativeErrorException {
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        Statvfs stat = util.statvfs("/dev/shm");
        System.out.println(stat);
    }

    @Test
    public void testSimple() throws Exception {
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        new File(path1).createNewFile();
        Stat s = util.stat(path1);
        Assert.assertEquals(0, s.getSize());
        Assert.assertEquals(0, s.getBlocks());
        Assert.assertTrue(s.getDev() != 0);
        Assert.assertTrue(s.getIno() != 0);
        Assert.assertTrue(s.getAtime() > 0);
        Assert.assertTrue(s.getAtime() + " " + s.getMtime() + " " + s.getCtime(), s.getAtime() == s.getMtime() && s.getMtime() == s.getCtime());
        Assert.assertTrue(s.isRegularFile());
    }

    @Test
    public void testFDWithWrite() throws Exception {
        File f = new File(path1);
        f.createNewFile();
        try(FileOutputStream faos = new FileOutputStream(f)) {
            LinuxNativeUtil util = NativeUtils.getLinuxUtil();
            Stat s = util.fstat(util.getFD(faos.getFD()));
            Assert.assertEquals(0, s.getSize());
            Assert.assertEquals(0, s.getBlocks());
            Assert.assertTrue(s.getDev() != 0);
            Assert.assertTrue(s.getIno() != 0);
            Assert.assertTrue(s.getAtime() > 0);
            Assert.assertTrue(s.getAtime() + " " + s.getMtime() + " " + s.getCtime(), s.getAtime() == s.getMtime() && s.getMtime() == s.getCtime());
            //Assert.assertTrue(s.isRegularFile());

            Thread.sleep(1000);

            faos.write(1);
            faos.getFD().sync();


            Stat s2 = util.fstat(util.getFD(faos.getFD()));
            Assert.assertEquals(1, s2.getSize());
            Assert.assertTrue(s2.getBlocks() > 0);
            Assert.assertTrue(s2.getDev() != 0);
            Assert.assertTrue(s2.getIno() != 0);
            Assert.assertTrue(s2.getAtime() > 0);
            Assert.assertTrue(s2.getAtime() + " " + s2.getMtime() + " " + s2.getCtime(), s2.getAtime() != s2.getMtime() && s2.getMtime() == s2.getCtime());
            Assert.assertTrue(s2.isRegularFile());

            Assert.assertEquals(s.getDev(),  s2.getDev());
            Assert.assertEquals(s.getIno(), s2.getIno());
        }
    }
}

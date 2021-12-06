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

import io.github.alexanderschuetz97.nativeutils.api.LinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import io.github.alexanderschuetz97.nativeutils.impl.NativeLibraryLoaderHelper;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Random;

public class LinuxLockTests {

    @BeforeClass
    public static void loadIt() {
        NativeLibraryLoaderHelper.loadNativeLibraries();
    }

    File f;
    RandomAccessFile raf;


    @Before
    public void before() throws Exception {
        Random rng = new Random();
        f = new File("/tmp/testo" + Math.abs(rng.nextInt()));
        f.createNewFile();
        raf = new RandomAccessFile(f, "rw");
    }

    @After
    public void after() throws IOException {
        raf.close();
        f.delete();
    }

    @Test
    public void testGetLK() throws Throwable{
        LinuxNativeUtil utils = NativeUtils.getLinuxUtil();
        int pid = utils.fnctl_F_GETLK(utils.getFD(raf.getFD()), true, 0, Long.MAX_VALUE);
        Assert.assertEquals(-1, pid);
    }

    @Test
    public void testLockWriteUnlock() throws Throwable{
        LinuxNativeUtil utils = NativeUtils.getLinuxUtil();
        raf.write(1);
        utils.fnctl_F_SETLKW(utils.getFD(raf.getFD()), LinuxNativeUtil.fnctl_F_SETLK_Mode.F_WRLCK, 0, Long.MAX_VALUE);
        raf.write(1);
        utils.fnctl_F_SETLKW(utils.getFD(raf.getFD()), LinuxNativeUtil.fnctl_F_SETLK_Mode.F_UNLCK, 0, Long.MAX_VALUE);
        raf.write(1);
    }
}

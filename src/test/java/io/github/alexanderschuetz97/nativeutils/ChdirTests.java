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
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Test;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.nio.file.AccessDeniedException;
import java.nio.file.FileSystemLoopException;
import java.nio.file.NotDirectoryException;

public class ChdirTests {

    @Test
    public void testAccess() throws Exception {
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        try {
            util.chdir("/root");
            Assert.fail("AccessDeniedException expected");
        } catch (AccessDeniedException exc) {
            //expected
        }
    }

    @Test
    public void testDoesNotExist() throws Exception {
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        try {
            util.chdir("/tmp/doesntexist");
            Assert.fail("FileNotFoundException expected");
        } catch (FileNotFoundException exc) {
            //expected
        }
    }

    @Test
    public void testNotDir() throws Exception {
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        File f = new File("/tmp/notadir");
        f.createNewFile();
        try {
            util.chdir(f.getAbsolutePath());
            Assert.fail("NotDirectoryException expected");
        } catch (NotDirectoryException exc) {
            //expected
        } finally {
            f.delete();
        }
    }

    @Test
    public void testLoop() throws Exception {
        File f = new File("/tmp/loop1");

        File f2 = new File("/tmp/loop2");

        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        util.symlink(f.getAbsolutePath(), f2.getAbsolutePath());
        util.symlink(f2.getAbsolutePath(), f.getAbsolutePath());

        try {
            util.chdir("/tmp/loop1/beep");
            Assert.fail("FileSystemLoopException expected");
        } catch (FileSystemLoopException exc) {
            //expected
        } finally {
            f.delete();
            f2.delete();
        }

    }

    @Test
    public void testSuccess() throws Exception {
        String path = new File(".").getAbsolutePath();
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        util.chdir("/tmp");
        Process process = new ProcessBuilder().command("pwd").start();
        Assert.assertEquals(0, process.waitFor());
        InputStream input = process.getInputStream();

        byte[] b = new byte[512];
        int i = input.read(b);
        if (i < 0) {
            Assert.fail("0");
        }


        util.chdir(path);

        Assert.assertEquals("/tmp\n", new String(b, 0, i));

    }
}

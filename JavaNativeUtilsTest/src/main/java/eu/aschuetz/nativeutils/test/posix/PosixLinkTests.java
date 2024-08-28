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
package eu.aschuetz.nativeutils.test.posix;

import eu.aschuetz.nativeutils.api.FreeBSDNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.PosixNativeUtil;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.file.AccessDeniedException;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.FileSystemLoopException;
import java.nio.file.InvalidPathException;
import java.util.Random;

public class PosixLinkTests {

    String path1;
    String path2;

    @Before
    public void before() {
        Random rng = new Random();
        path1 = "/tmp/testo" + Math.abs(rng.nextInt());
        path2 = path1 + "T2";
    }

    @After
    public void after() {
        new File(path1).delete();
        new File(path2).delete();
    }

    @Test
    public void testLink() throws Exception {
        File f = new File(path1);
        f.createNewFile();
        try( FileOutputStream faos = new FileOutputStream(path1)) {
            faos.write(0x69);
        }
        PosixNativeUtil utils = NativeUtils.getPosixUtil();
        utils.symlink(path1, path2);

        File f2 = new File(path2);
        try(FileInputStream fais = new FileInputStream(f2)) {
            Assert.assertEquals(0x69, fais.read());
        }

        utils.unlink(path2);
        Assert.assertFalse(f2.exists());
        Assert.assertTrue(f.exists());
    }

    @Test
    public void testLoop() throws Exception {
        PosixNativeUtil utils = NativeUtils.getPosixUtil();
        utils.symlink(path1, path2);
        utils.symlink(path2, path1);

        try {
            utils.symlink("/tmp", path1 + "/dupp");
            Assert.fail("FileSystemLoopException expected");
        } catch (FileSystemLoopException exc) {
            Assert.assertEquals(path1 + "/dupp", exc.getFile());
        }
    }

    @Test
    public void testInvalidPath() throws Exception {
        PosixNativeUtil utils = NativeUtils.getPosixUtil();
        try {
            utils.symlink(path1, path2 + "/wupp");
            Assert.fail("InvalidPathException expected");
        } catch (InvalidPathException exc) {
            Assert.assertEquals(path2 + "/wupp", exc.getInput());
        }
    }

    @Test
    public void testExists() throws Exception {
        new File(path1).createNewFile();
        PosixNativeUtil utils = NativeUtils.getPosixUtil();
        try {
            utils.symlink("/tmp", path1);
            Assert.fail("FileAlreadyExistsException expected");
        } catch (FileAlreadyExistsException exc) {
            Assert.assertEquals(path1, exc.getFile());
        }
    }

    @Test
    public void testAccess() throws Exception {
        //Will not be green as root user...
        PosixNativeUtil utils = NativeUtils.getPosixUtil();
        try {
            utils.symlink("/tmp", "/root/meep");
            //someone ran this as root...
            new File("/root/meep").delete();
            Assert.fail("AccessDeniedException expected");
        } catch (AccessDeniedException exc) {

        }
    }

}

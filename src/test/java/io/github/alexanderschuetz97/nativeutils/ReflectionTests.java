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
import io.github.alexanderschuetz97.nativeutils.api.NativeField;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Test;

import java.io.FileDescriptor;

public class ReflectionTests {

    private LinuxNativeUtil util = NativeUtils.getLinuxUtil();

    @Test
    public void testFD() throws NoSuchFieldException, IllegalAccessException {
        FileDescriptor fd = new FileDescriptor();
        NativeField<FileDescriptor, Integer> field = util.GetFieldID(FileDescriptor.class, "fd", "I");
        Assert.assertEquals(-1, field.get(fd).intValue());
        field.set(fd, 1);
        Assert.assertEquals(1, field.get(fd).intValue());
        field.set(fd, -1);
        Assert.assertEquals(-1, field.get(fd).intValue());
    }
}

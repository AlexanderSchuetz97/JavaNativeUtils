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
package eu.aschuetz.nativeutils.test.common;

import eu.aschuetz.nativeutils.api.LinuxConst;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.consts.DefaultLinuxConstProvider;
import eu.aschuetz.nativeutils.api.consts.LinuxConstProvider;
import eu.aschuetz.nativeutils.impl.NativeLibraryLoaderHelper;
import org.junit.Assert;
import org.junit.Test;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Map;

public class TestLibLoad {

    @Test
    public void testConstants() throws Exception {
        Assert.assertNotEquals(LinuxConst.O_CREAT, 0);

        LinuxConstProvider cp = new DefaultLinuxConstProvider();
        if (NativeUtils.isLinux()) {
            cp = NativeUtils.getLinuxUtil().getLinuxConstProvider();
        }
        for (Field f : LinuxConst.class.getFields()) {
            if (!Modifier.isStatic(f.getModifiers())) {
                continue;
            }

            Object a = f.get(null);
            Method method = LinuxConstProvider.class.getMethod(f.getName());
            Object b = method.invoke(cp);

            Assert.assertEquals(f.getName(), a,b);
        }
    }



    @Test
    public void testReadAll() {
        Map<String, byte[]> theMap = NativeLibraryLoaderHelper.getNativeLibraryBinaries();
        for (Map.Entry<String, byte[]> e : theMap.entrySet()) {
            Assert.assertNotNull(e.getKey(), e.getValue());
        }

        Assert.assertEquals(13, theMap.size());


    }
}

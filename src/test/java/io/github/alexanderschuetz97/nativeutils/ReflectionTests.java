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

import io.github.alexanderschuetz97.nativeutils.api.JVMNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.LinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeField;
import io.github.alexanderschuetz97.nativeutils.api.NativeMethod;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Test;
import sun.misc.BASE64Decoder;

import java.io.FileDescriptor;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.concurrent.Callable;

public class ReflectionTests {

    private JVMNativeUtil util = NativeUtils.getJVMUtil();

    private static final byte[] THE_TESTCLASS = new byte[]{-54, -2, -70, -66, 0, 0, 0, 51, 0, 30, 10, 0, 5, 0, 23, 8, 0, 24, 10, 0, 4, 0, 25, 7, 0, 26, 7, 0, 27, 7, 0, 28, 1, 0, 6, 60, 105, 110, 105, 116, 62, 1, 0, 3, 40, 41, 86, 1, 0, 4, 67, 111, 100, 101, 1, 0, 15, 76, 105, 110, 101, 78, 117, 109, 98, 101, 114, 84, 97, 98, 108, 101, 1, 0, 18, 76, 111, 99, 97, 108, 86, 97, 114, 105, 97, 98, 108, 101, 84, 97, 98, 108, 101, 1, 0, 4, 116, 104, 105, 115, 1, 0, 55, 76, 105, 111, 47, 103, 105, 116, 104, 117, 98, 47, 97, 108, 101, 120, 97, 110, 100, 101, 114, 115, 99, 104, 117, 101, 116, 122, 57, 55, 47, 110, 97, 116, 105, 118, 101, 117, 116, 105, 108, 115, 47, 84, 101, 115, 116, 67, 97, 108, 108, 97, 98, 108, 101, 59, 1, 0, 4, 99, 97, 108, 108, 1, 0, 20, 40, 41, 76, 106, 97, 118, 97, 47, 108, 97, 110, 103, 47, 83, 116, 114, 105, 110, 103, 59, 1, 0, 10, 69, 120, 99, 101, 112, 116, 105, 111, 110, 115, 7, 0, 29, 1, 0, 20, 40, 41, 76, 106, 97, 118, 97, 47, 108, 97, 110, 103, 47, 79, 98, 106, 101, 99, 116, 59, 1, 0, 9, 83, 105, 103, 110, 97, 116, 117, 114, 101, 1, 0, 69, 76, 106, 97, 118, 97, 47, 108, 97, 110, 103, 47, 79, 98, 106, 101, 99, 116, 59, 76, 106, 97, 118, 97, 47, 117, 116, 105, 108, 47, 99, 111, 110, 99, 117, 114, 114, 101, 110, 116, 47, 67, 97, 108, 108, 97, 98, 108, 101, 60, 76, 106, 97, 118, 97, 47, 108, 97, 110, 103, 47, 83, 116, 114, 105, 110, 103, 59, 62, 59, 1, 0, 10, 83, 111, 117, 114, 99, 101, 70, 105, 108, 101, 1, 0, 17, 84, 101, 115, 116, 67, 97, 108, 108, 97, 98, 108, 101, 46, 106, 97, 118, 97, 12, 0, 7, 0, 8, 1, 0, 2, 79, 75, 12, 0, 14, 0, 15, 1, 0, 53, 105, 111, 47, 103, 105, 116, 104, 117, 98, 47, 97, 108, 101, 120, 97, 110, 100, 101, 114, 115, 99, 104, 117, 101, 116, 122, 57, 55, 47, 110, 97, 116, 105, 118, 101, 117, 116, 105, 108, 115, 47, 84, 101, 115, 116, 67, 97, 108, 108, 97, 98, 108, 101, 1, 0, 16, 106, 97, 118, 97, 47, 108, 97, 110, 103, 47, 79, 98, 106, 101, 99, 116, 1, 0, 29, 106, 97, 118, 97, 47, 117, 116, 105, 108, 47, 99, 111, 110, 99, 117, 114, 114, 101, 110, 116, 47, 67, 97, 108, 108, 97, 98, 108, 101, 1, 0, 19, 106, 97, 118, 97, 47, 108, 97, 110, 103, 47, 69, 120, 99, 101, 112, 116, 105, 111, 110, 0, 33, 0, 4, 0, 5, 0, 1, 0, 6, 0, 0, 0, 3, 0, 1, 0, 7, 0, 8, 0, 1, 0, 9, 0, 0, 0, 47, 0, 1, 0, 1, 0, 0, 0, 5, 42, -73, 0, 1, -79, 0, 0, 0, 2, 0, 10, 0, 0, 0, 6, 0, 1, 0, 0, 0, 5, 0, 11, 0, 0, 0, 12, 0, 1, 0, 0, 0, 5, 0, 12, 0, 13, 0, 0, 0, 1, 0, 14, 0, 15, 0, 2, 0, 9, 0, 0, 0, 45, 0, 1, 0, 1, 0, 0, 0, 3, 18, 2, -80, 0, 0, 0, 2, 0, 10, 0, 0, 0, 6, 0, 1, 0, 0, 0, 8, 0, 11, 0, 0, 0, 12, 0, 1, 0, 0, 0, 3, 0, 12, 0, 13, 0, 0, 0, 16, 0, 0, 0, 4, 0, 1, 0, 17, 16, 65, 0, 14, 0, 18, 0, 2, 0, 9, 0, 0, 0, 47, 0, 1, 0, 1, 0, 0, 0, 5, 42, -74, 0, 3, -80, 0, 0, 0, 2, 0, 10, 0, 0, 0, 6, 0, 1, 0, 0, 0, 5, 0, 11, 0, 0, 0, 12, 0, 1, 0, 0, 0, 5, 0, 12, 0, 13, 0, 0, 0, 16, 0, 0, 0, 4, 0, 1, 0, 17, 0, 2, 0, 19, 0, 0, 0, 2, 0, 20, 0, 21, 0, 0, 0, 2, 0, 22};

    @Test
    public void testDefine() throws Exception {
        Class<?> cc = util.DefineClass("io/github/alexanderschuetz97/nativeutils/TestCallable", ClassLoader.getSystemClassLoader(), THE_TESTCLASS, 0, THE_TESTCLASS.length);
        Callable cal = (Callable) cc.newInstance();
        Assert.assertEquals("OK", cal.call());
    }


    @Test
    public void testConstr() {
        NativeMethod<TClass, TClass> nm = util.GetMethodID(TClass.class, "<init>", "(I)V");
        Assert.assertNotNull(nm);
        Assert.assertTrue(nm.isConstructor());
        TClass t = nm.CallAnyMethod(null, 5);
        Assert.assertNotNull(t);
        Assert.assertEquals(5, t.x);


    }

    @Test
    public void testAllocPrimitve() {
        Assert.assertNull(util.GetMethodID(int.class, "<init>", "()V"));

        try {
            util.AllocObject(int.class);
            Assert.fail();
        } catch (IllegalArgumentException e) {
            //EXPECTED
        }

    }

    @Test
    public void testThrow() {
        Exception beep = new Exception();
        try {
            util.Throw(beep);
            Assert.fail();
        } catch (Exception exc) {
            Assert.assertTrue(exc == beep);
        }

        try {
            util.Throw(null);
            Assert.fail();
        } catch (NullPointerException e) {
            //
        }


    }

    @Test
    public void testConstrResolv() throws NoSuchMethodException, InvocationTargetException {
        Constructor<TClass> tClassConstructor = TClass.class.getDeclaredConstructor(int.class);

        NativeMethod<TClass, TClass> nm = util.FromReflectedMethod(tClassConstructor);
        Assert.assertNotNull(nm);
        Assert.assertTrue(nm.isConstructor());
        TClass t = nm.invoke(null, 5);
        Assert.assertNotNull(t);
        Assert.assertEquals(5, t.x);
    }

    @Test
    public void testAllocCall() throws InvocationTargetException {
        TClass t = util.AllocObject(TClass.class);
        Assert.assertEquals(0, t.x);
        NativeMethod<TClass, TClass> nm = util.GetMethodID(TClass.class, "<init>", "(I)V");
        Assert.assertNotNull(nm);
        nm.CallAnyMethod(t, 5);
        Assert.assertEquals(5, t.x);
        nm.invoke(t, 6);
        Assert.assertEquals(6, t.x);
    }

    @Test
    public void testFD() throws NoSuchFieldException, IllegalAccessException {
        FileDescriptor fd = new FileDescriptor();
        NativeField<FileDescriptor, Integer> field = util.GetFieldID(FileDescriptor.class, "fd", "I");
        Assert.assertEquals(-1, field.get(fd).intValue());
        field.set(fd, 1);
        Assert.assertEquals(1, field.GetIntField(fd));
        field.set(fd, -1);
        Assert.assertEquals(-1, field.get(fd).intValue());
    }

    @Test
    public void testMethod() {
        NativeMethod<Integer, ReflectionTests> method = util.GetMethodID(ReflectionTests.class, "testo", "(ILjava/lang/Integer;Ljava/lang/String;J)I");
        int x = method.CallIntMethod(this, new Object[]{1, 2, "bub", 4l});
        Assert.assertEquals("bub".hashCode() + 4+2+1, x);
    }

    public int testo(int i, Integer o, String b, long r) {
        return i+o+b.hashCode()+((int)r);
    }

    public static class TClass {

        public int x;

        public TClass(int i) {
            x = i;
        }
    }
}

package io.github.alexanderschuetz97.nativeutils;

import io.github.alexanderschuetz97.nativeutils.api.LinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Ignore;
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

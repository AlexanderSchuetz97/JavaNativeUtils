package io.github.alexanderschuetz97.nativeutils;

import io.github.alexanderschuetz97.nativeutils.api.JVMNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.LinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Test;

import java.util.Arrays;
import java.util.Map;

public class WordExp {

    private LinuxNativeUtil util = NativeUtils.getLinuxUtil();

    @Test
    public void test() {
        Map.Entry<String, String> e = System.getenv().entrySet().iterator().next();
        String[] ss = util.wordexp("a $"+e.getKey()+" b", true, true, true);
        Assert.assertArrayEquals(new String[]{"a", e.getValue(), "b"}, ss);
    }
}

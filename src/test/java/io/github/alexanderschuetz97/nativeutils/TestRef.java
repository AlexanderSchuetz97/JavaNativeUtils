package io.github.alexanderschuetz97.nativeutils;

import io.github.alexanderschuetz97.nativeutils.api.JVMNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;

public class TestRef {

    JVMNativeUtil jvmu = NativeUtils.getJVMUtil();

    private long ngref()  {
        ArrayList<String> ar = new ArrayList();
        ar.add("bleh");
        return jvmu.NewGlobalRef(ar);
    }

    @Test
    public void test() {
        long l = ngref();
        System.gc();
        ArrayList<String> ar = jvmu.NewLocalRef(l);
        jvmu.DeleteGlobalRef(l);
        Assert.assertEquals("bleh", ar.get(0));
    }

}

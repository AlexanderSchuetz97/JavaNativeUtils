package io.github.alexanderschuetz97.nativeutils;

import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import org.junit.Test;

import java.io.File;
import java.io.IOException;

public class ChmodTest {

    @Test
    public void testChmod() throws IOException {
        File f = new File("/tmp/chmodtest");
        f.createNewFile();

        int mode = 0777;

        NativeUtils.getLinuxUtil().chmod("/tmp/chmodtest", mode);
    }

}

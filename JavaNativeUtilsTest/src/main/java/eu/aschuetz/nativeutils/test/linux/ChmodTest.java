package eu.aschuetz.nativeutils.test.linux;

import eu.aschuetz.nativeutils.api.NativeUtils;
import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.io.UnsupportedEncodingException;

public class ChmodTest {

    @Test
    public void testChmod() throws IOException {
        File f = new File("/tmp/chmodtest");
        f.createNewFile();

        int mode = 0777;

        NativeUtils.getLinuxUtil().chmod("/tmp/chmodtest", mode);
    }

}

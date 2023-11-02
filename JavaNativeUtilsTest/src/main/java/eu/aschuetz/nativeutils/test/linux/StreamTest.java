package eu.aschuetz.nativeutils.test.linux;

import eu.aschuetz.nativeutils.api.LinuxConst;
import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import org.junit.Assert;
import org.junit.Test;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.UUID;

public class StreamTest {

    @Test
    public void testReadWrite() throws UnknownNativeErrorException, IOException {
        UUID r = UUID.randomUUID();
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        int fd = util.open("/tmp/" + r.toString(), LinuxConst.O_CREAT | LinuxConst.O_RDWR, 0777);
        try(OutputStream outputStream = util.outputStreamFromFD(fd, true)) {
            outputStream.write("Hallo ".getBytes(StandardCharsets.UTF_8));
            outputStream.flush();
            outputStream.write("Welt!".getBytes(StandardCharsets.UTF_8));
        }

        fd = util.open("/tmp/" + r.toString(), LinuxConst.O_RDONLY);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        byte[] buf = new byte[4];
        try(InputStream inputStream = util.inputStreamFromFD(fd, true)) {

            int x = 0;
            while(x != -1) {
                x = inputStream.read(buf, 0, buf.length);
                if (x > 0) {
                    baos.write(buf, 0, x);
                }
            }
        }

        Assert.assertEquals("Hallo Welt!", baos.toString("UTF-8"));
        Assert.assertTrue(new File("/tmp/" +r.toString()).delete());
    }
}

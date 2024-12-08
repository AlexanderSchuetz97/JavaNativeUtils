package eu.aschuetz.nativeutils.test.posix;

import eu.aschuetz.nativeutils.api.*;
import eu.aschuetz.nativeutils.api.consts.PosixConstProvider;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import org.junit.Assert;
import org.junit.Test;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.UUID;

public class OpenWriteReadTest {

    @Test
    public void testReadWrite() throws UnknownNativeErrorException, IOException {
        UUID r = UUID.randomUUID();
        PosixNativeUtil util = NativeUtils.getPosixUtil();

        int fd = util.open("/tmp/" + r.toString(), PosixConst.O_CREAT | PosixConst.O_RDWR, 0777);
        byte[] buf1 = "Hallo ".getBytes(StandardCharsets.UTF_8);
        byte[] buf2 = "Welt!".getBytes(StandardCharsets.UTF_8);

        util.write(fd, buf1, 0, buf1.length);
        util.write(fd, buf2, 0, buf2.length);

        util.close(fd);

        fd = util.open("/tmp/" + r.toString(), PosixConst.O_RDONLY);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        byte[] buf = new byte[4];

        int x = 0;
        while(x != -1) {
            x = util.read(fd, buf, 0, buf.length);
            if (x > 0) {
                baos.write(buf, 0, x);
            }
        }
        util.close(fd);

        Assert.assertEquals("Hallo Welt!", baos.toString("UTF-8"));
        Assert.assertTrue(new File("/tmp/" +r.toString()).delete());
    }
}

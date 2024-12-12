package eu.aschuetz.nativeutils.test.posix;

import eu.aschuetz.nativeutils.api.*;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import org.junit.Assert;
import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.io.SyncFailedException;
import java.nio.file.AccessDeniedException;
import java.util.UUID;

public class PosixMMapTest {

    @Test
    public void testMMap() throws UnknownNativeErrorException, IOException, InterruptedException {
        UUID uuid = UUID.randomUUID();
        final PosixNativeUtil lnu = NativeUtils.getPosixUtil();
        int fd = lnu.open("/tmp/" + uuid.toString(), PosixConst.O_CREAT | PosixConst.O_RDWR, 0777);
        lnu.lseek(fd, 100_000_000, PosixNativeUtil.lseek_whence.SEEK_SET);
        lnu.write(fd, new byte[1], 0, 1);
        long ptr = lnu.mmap(fd, 100_000_000, PosixConst.MAP_SHARED, true, true, 0);
        NativeMemory mem = lnu.pointer(ptr, 100_000_000, new PointerHandler() {
            @Override
            public void handleClose(long ptr, long size) {
                //NOOP
            }

            @Override
            public void handleSync(long ptr, long size, long offset, long length, boolean invalidate) throws SyncFailedException {
                try {
                    lnu.msync(ptr, offset, length, invalidate);
                } catch (Exception e) {
                    throw new SyncFailedException(e.getMessage());
                }
            }
        });

        mem.sync(0, mem.size(), true);

        Assert.assertTrue(new File("/tmp/" + uuid.toString()).delete());
        Thread.sleep(5000);
        mem.writeByte(80_000_000, 1);
        Assert.assertEquals(1, mem.readUnsignedByte(80_000_000));
        lnu.munmap(ptr, 100_000_000);
        lnu.close(fd);
    }

}

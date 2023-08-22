package io.github.alexanderschuetz97.nativeutils;

import io.github.alexanderschuetz97.nativeutils.api.*;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import org.junit.Assert;
import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.io.SyncFailedException;
import java.util.UUID;

public class MMapTest {

    @Test
    public void testMMap() throws UnknownNativeErrorException, IOException, InterruptedException {
        UUID uuid = UUID.randomUUID();
        LinuxNativeUtil lnu = NativeUtils.getLinuxUtil();
        int fd = lnu.open("/dev/shm/" + uuid.toString(), LinuxConst.O_CREAT | LinuxConst.O_RDWR, 0777);
        lnu.lseek(fd, 100_000_000, LinuxNativeUtil.lseek_whence.SEEK_SET);
        lnu.write(fd, new byte[1], 0, 1);
        long ptr = lnu.mmap(fd, 100_000_000, LinuxConst.MAP_SHARED, true, true, 0);
        NativeMemory mem = lnu.pointer(ptr, 100_000_000, new PointerHandler() {
            @Override
            public void handleClose(long ptr, long size, boolean read, boolean write) {
                //NOOP
            }

            @Override
            public void handleSync(long ptr, long size, boolean read, boolean write, long offset, long length, boolean invalidate) throws SyncFailedException {
                //NOOP
            }
        });

        Assert.assertTrue(new File("/dev/shm/" + uuid.toString()).delete());
        Thread.sleep(5000);
        mem.write(80_000_000, 1);
        Assert.assertEquals(1, mem.readUnsignedByte(80_000_000));
        lnu.munmap(ptr, 100_000_000);
        lnu.close(fd);
    }

}

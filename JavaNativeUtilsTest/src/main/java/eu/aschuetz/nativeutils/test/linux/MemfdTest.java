package eu.aschuetz.nativeutils.test.linux;

import eu.aschuetz.nativeutils.api.LinuxConst;
import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.PointerHandler;
import eu.aschuetz.nativeutils.api.exceptions.PermissionDeniedException;
import eu.aschuetz.nativeutils.api.exceptions.QuotaExceededException;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import eu.aschuetz.nativeutils.test.common.MemTest;
import org.junit.Assert;

import java.io.File;
import java.io.IOException;
import java.io.SyncFailedException;
import java.nio.file.Files;

public class MemfdTest extends MemTest {

    @Override
    protected void mkmemory() {
        final LinuxNativeUtil linuxUtil = NativeUtils.getLinuxUtil();
        try {
            final int fd = linuxUtil.memfd_create("nase", 0);
            //System.out.println(new String(Files.readAllBytes(new File("/proc/self/stat").toPath())));

            linuxUtil.ftruncate(fd, 4096);
            long ptr = linuxUtil.mmap(fd, 4096, LinuxConst.MAP_SHARED, true, true, 0);
            memory = linuxUtil.pointer(ptr, 4096, new PointerHandler() {
                @Override
                public void handleClose(long ptr, long size) {
                    try {
                        linuxUtil.munmap(ptr, size);
                    } catch (UnknownNativeErrorException e) {
                        Assert.fail(e.getMessage());
                    }
                    try {
                        linuxUtil.close(fd);
                    } catch (IOException e) {
                        Assert.fail(e.getMessage());
                    }
                }

                @Override
                public void handleSync(long ptr, long size, long offset, long length, boolean invalidate) throws SyncFailedException {
                    try {
                        linuxUtil.fsync(fd);
                    } catch (IOException e) {
                        Assert.fail(e.getMessage());
                    }
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
            Assert.fail(e.getMessage());
        }
    }
}

package eu.aschuetz.nativeutils.test.linux;

import eu.aschuetz.nativeutils.api.NativeMemory;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.PointerHandler;
import org.junit.Assert;
import org.junit.Test;

import java.io.File;
import java.io.RandomAccessFile;
import java.io.SyncFailedException;
import java.nio.ByteOrder;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.util.Random;

public class TestMBuf {

    @Test
    public void testMapSharedMemory() throws Exception {
        Random rng = new Random();
        rng.nextInt();
        File f = new File("/tmp/" + rng.nextInt());
        f.createNewFile();
        long x;
        NativeMemory nmem;
        try (RandomAccessFile raf = new RandomAccessFile(f, "rw")) {
            raf.setLength(1000);
            raf.write(0);
            MappedByteBuffer buf = raf.getChannel().map(FileChannel.MapMode.READ_WRITE, 0, 1000);
            x = NativeUtils.getJVMUtil().GetDirectBufferAddress(buf);
            Assert.assertNotEquals(0, x);
            nmem = NativeUtils.getLinuxUtil().pointer(x, 1000, new MappedByteBufferPointerHandler(buf));

            nmem.write(124, 0xdeadbeef);
            buf.order(ByteOrder.nativeOrder());
            int v = buf.getInt(124);
            Assert.assertEquals(0xdeadbeef, v);

            buf = null;
        }

        System.gc();
        Assert.assertEquals(0xdeadbeef, nmem.readInt(124));
        nmem.read(124);
        nmem.close();
        System.gc();

        //This assert may be wonky depending on gc...
        Assert.assertTrue(f.delete());
    }

    static class MappedByteBufferPointerHandler implements PointerHandler {

        private volatile MappedByteBuffer buffer;

        public MappedByteBufferPointerHandler(MappedByteBuffer buf) {
            buffer = buf;
        }

        @Override
        public void handleClose(long ptr, long size) {
            buffer = null;
            //GC will actually close to buffer
        }

        @Override
        public void handleSync(long ptr, long size, long offset, long length, boolean invalidate) throws SyncFailedException {

        }
    }
}

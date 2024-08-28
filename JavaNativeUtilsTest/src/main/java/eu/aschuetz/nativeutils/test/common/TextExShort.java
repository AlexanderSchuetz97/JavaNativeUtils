package eu.aschuetz.nativeutils.test.common;

import eu.aschuetz.nativeutils.api.NativeMemory;
import eu.aschuetz.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Test;

import java.nio.ByteOrder;
import java.util.Arrays;

public class TextExShort {

    private static NativeMemory alloc(int sz) {
        if (NativeUtils.isPosix()) {
            return NativeUtils.getPosixUtil().malloc(sz);
        }

        return NativeUtils.getWindowsUtil().malloc(sz);
    }

    @Test
    public void test() {
        NativeMemory memory = alloc(4096);
        memory.zero();
        short[] x = new short[]{0x24, (short) 0xFE77};
        memory.writeByte(8, 1);
        memory.write(0, x, 4, 0, 2);
        byte[] b = new byte[8];
        memory.read(0,b);
        System.out.println(Arrays.toString(b));

        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x24, 0x00, 0x00, (byte) 0xFE, 0x77} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00, 0x00};
        byte[] x3 = new byte[8];
        memory.read(0, x3);
        short[] r2 = new short[2];
        memory.read(0, r2, 4, 0, 2);
        Assert.assertArrayEquals(Arrays.toString(r2), x, r2);
        Assert.assertEquals(1, memory.read(8));
        Assert.assertArrayEquals(Arrays.toString(x3), x2, x3);
    }
}

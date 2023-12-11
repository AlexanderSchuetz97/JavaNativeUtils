package eu.aschuetz.nativeutils.test.common;

import eu.aschuetz.nativeutils.api.NativeMemory;
import eu.aschuetz.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Test;


public class MemCmpXchgTest {

    @Test
    public void test1B() {
        NativeMemory memory = NativeUtils.get().isWindows() ? NativeUtils.getWindowsUtil().malloc(4096) : NativeUtils.getLinuxUtil().malloc(4096);

        memory.zero();

        if (!memory.supportsCompareAndSet1Byte()) {
            try {
                memory.compareAndSet(0,(byte) 0,(byte) 1);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            try {
                memory.getAndAdd(0, (byte) 1);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            try {
                memory.getAndSet(0, (byte) 1);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            return;
        }

        memory.writeByte(1, 1);
        Assert.assertFalse(memory.compareAndSet(0, (byte) 4, (byte) 2));
        Assert.assertEquals(0, memory.read(0));
        Assert.assertTrue(memory.compareAndSet(0, (byte) 0, (byte) 1));

        Assert.assertEquals(1, memory.read( 0));
        Assert.assertEquals(1, memory.readUnsignedByte(1));

        for (long i = 0; i < 64; i++) {
            try {
                memory.compareAndSet(i,69,(byte) 1);
                if ((i % memory.compareAndSet1ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet1ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }

        for (long i = 0; i < 64; i++) {
            try {
                memory.getAndAdd(i,(byte) 69);
                if ((i % memory.compareAndSet1ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet1ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }

        for (long i = 0; i < 64; i++) {
            try {
                memory.getAndSet(i,(byte) 69);
                if ((i % memory.compareAndSet1ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet1ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }


        memory.close();
    }

    @Test
    public void test2B() {
        NativeMemory memory = NativeUtils.get().isWindows() ? NativeUtils.getWindowsUtil().malloc(4096) : NativeUtils.getLinuxUtil().malloc(4096);

        memory.zero();

        if (!memory.supportsCompareAndSet2Byte()) {
            try {
                memory.compareAndSet(0,(short) 0,(short) 1);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            try {
                memory.getAndAdd(0, (short) 1);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            try {
                memory.getAndSet(0, (short) 1);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            return;
        }

        memory.writeByte(2, 1);
        Assert.assertFalse(memory.compareAndSet(0, (short) 4, (short) 2));
        Assert.assertEquals(0, memory.readShort(0));
        Assert.assertTrue(memory.compareAndSet(0, (short) 0, (short) 1));

        Assert.assertEquals(1, memory.readShort( 0));
        Assert.assertEquals(1, memory.readUnsignedByte(2));

        for (long i = 0; i < 64; i++) {
            try {
                memory.compareAndSet(i,69,(short) 1);
                if ((i % memory.compareAndSet2ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet2ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }

        for (long i = 0; i < 64; i++) {
            try {
                memory.getAndAdd(i,(short) 69);
                if ((i % memory.compareAndSet2ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet2ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }

        for (long i = 0; i < 64; i++) {
            try {
                memory.getAndSet(i,(short) 69);
                if ((i % memory.compareAndSet2ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet2ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }


        memory.close();
    }

    @Test
    public void test4B() {
        NativeMemory memory = NativeUtils.get().isWindows() ? NativeUtils.getWindowsUtil().malloc(4096) : NativeUtils.getLinuxUtil().malloc(4096);

        memory.zero();

        if (!memory.supportsCompareAndSet4Byte()) {
            try {
                memory.compareAndSet(0,0,1);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            try {
                memory.getAndAdd(0, 1);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            try {
                memory.getAndSet(0, 1);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            return;
        }

        memory.writeInt(0, 69);
        memory.writeByte(4, 1);
        Assert.assertFalse(memory.compareAndSet(0, 4, 2));
        Assert.assertEquals(69, memory.readInt(0));
        Assert.assertTrue(memory.compareAndSet(0, 69, 1));

        Assert.assertEquals(1, memory.readInt(0));
        Assert.assertEquals(1, memory.readUnsignedByte(4));

        for (long i = 0; i < 64; i++) {
            try {
                memory.compareAndSet(i,69,1);
                if ((i % memory.compareAndSet4ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet4ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }

        for (long i = 0; i < 64; i++) {
            try {
                memory.getAndAdd(i,69);
                if ((i % memory.compareAndSet4ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet4ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }

        for (long i = 0; i < 64; i++) {
            try {
                memory.getAndSet(i,69);
                if ((i % memory.compareAndSet4ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet4ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }


        memory.close();
    }

    @Test
    public void test8B() {
        NativeMemory memory = NativeUtils.get().isWindows() ? NativeUtils.getWindowsUtil().malloc(4096) : NativeUtils.getLinuxUtil().malloc(4096);

        memory.zero();

        if (!memory.supportsCompareAndSet8Byte()) {
            try {
                memory.compareAndSet(0,0L,1L);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            try {
                memory.getAndAdd(0, 1L);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            try {
                memory.getAndSet(0, 1L);
                Assert.fail("uoe");
            } catch (UnsupportedOperationException uoe) {

            }

            return;
        }

        memory.writeByte(8, 1);
        Assert.assertFalse(memory.compareAndSet(0, 4L, 2L));
        Assert.assertEquals(0, memory.readLong(0));
        Assert.assertTrue(memory.compareAndSet(0, 0L, 1L));

        Assert.assertEquals(1, memory.readLong(0));
        Assert.assertEquals(1, memory.readUnsignedByte(8));

        for (long i = 0; i < 64; i++) {
            try {
                memory.compareAndSet(i,69L,1L);
                if ((i % memory.compareAndSet8ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet8ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }

        for (long i = 0; i < 64; i++) {
            try {
                memory.getAndAdd(i,69L);
                if ((i % memory.compareAndSet8ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet8ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }

        for (long i = 0; i < 64; i++) {
            try {
                memory.getAndSet(i,69L);
                if ((i % memory.compareAndSet8ByteAlignment()) != 0) {
                    Assert.fail("iae expected");
                }
            } catch (IllegalArgumentException iae) {
                if ((i % memory.compareAndSet8ByteAlignment()) == 0) {
                    Assert.fail("no iae expected");
                }
            }
        }


        memory.close();
    }
}

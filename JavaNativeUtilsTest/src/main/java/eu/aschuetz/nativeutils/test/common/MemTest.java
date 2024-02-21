//
// Copyright Alexander Schütz, 2021-2022
//
// This file is part of JavaNativeUtils.
//
// JavaNativeUtils is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JavaNativeUtils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// A copy of the GNU Lesser General Public License should be provided
// in the COPYING & COPYING.LESSER files in top level directory of JavaNativeUtils.
// If not, see <https://www.gnu.org/licenses/>.
//
package eu.aschuetz.nativeutils.test.common;

import eu.aschuetz.nativeutils.api.NativeMemory;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.exceptions.InvalidFileDescriptorException;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import org.junit.*;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.*;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

public class MemTest {

    protected Random rng = new Random();

    protected NativeMemory memory;

    private long[] randomLongs = new long[256];
    private int[] randomInts = new int[256];
    private short[] randomShorts = new short[256];

    private void mkRandom() {
        for (int i = 0; i < randomLongs.length; i++) {
            randomLongs[i] = rng.nextLong();
        }
        for (int i = 0; i < randomInts.length; i++) {
            randomInts[i] = rng.nextInt();
        }

        for (int i = 0; i < randomShorts.length; i++) {
            randomShorts[i] = (short) rng.nextInt();
        }
    }

    @Before
    public void before() throws Throwable {
        mkmemory();
        rng.setSeed(0);
        memory.zero();
    }

    protected void mkmemory() {
        memory = NativeUtils.get().isWindows() ? NativeUtils.getWindowsUtil().malloc(4096) : NativeUtils.getLinuxUtil().malloc(4096);
    }

    @After
    public void after() throws Throwable {
        memory.close();
    }

    @Test
    public void testAtomicShort() throws Exception {
        if (!memory.supportsCompareAndSet2Byte()) {
            return;
        }

        memory.zero();

        final AtomicBoolean bool = new AtomicBoolean(true);
        List<Thread> tt = new ArrayList<>();
        List<Collection<Integer>> listo = new ArrayList<>();
        for (int i = 0; i < Runtime.getRuntime().availableProcessors(); i++) {

            final Collection<Integer> inti = new LinkedList<>();
            Thread x = new Thread(new Runnable() {
                @Override
                public void run() {
                    while (bool.get()) {
                        int o = memory.getAndAdd(64, (short) 1) & 0xFFFF;
                        inti.add(o);
                        if (o > 0xFFE0) {
                            return;
                        }
                    }

                }
            });

            tt.add(x);
            listo.add(inti);
        }

        for (Thread t : tt) {
            t.start();
        }

        Thread.sleep(5000);
        bool.set(false);
        for (Thread t : tt) {
            t.join();
        }

        int sz = 0;

        for (Collection<Integer> inti : listo) {
            Assert.assertFalse(inti.isEmpty());
            sz += inti.size();
        }

        boolean[] res = new boolean[sz];
        for (Collection<Integer> inti : listo) {
            for (int i : inti) {
                Assert.assertFalse(res[i]);
                res[i] = true;
            }
        }

        for (int i = 0; i < res.length; i++) {
            Assert.assertTrue(res[i]);
        }

        Assert.assertEquals(res.length, memory.readInt(64));


        for (Collection<Integer> inti : listo) {
            Iterator<Integer> iterator = inti.iterator();
            long oval = iterator.next();
            while (iterator.hasNext()) {
                long next = iterator.next();
                Assert.assertTrue(next > oval);
                oval = next;
            }
        }
    }

    @Test
    public void testAtomicLong() throws Exception {
        if (!memory.supportsCompareAndSet8Byte()) {
            return;
        }

        memory.zero();

        final AtomicBoolean bool = new AtomicBoolean(true);
        List<Thread> tt = new ArrayList<>();
        List<Collection<Long>> listo = new ArrayList<>();
        for (int i = 0; i < Runtime.getRuntime().availableProcessors(); i++) {

            final Collection<Long> inti = new LinkedList<>();
            Thread x = new Thread(new Runnable() {
                @Override
                public void run() {
                    while (bool.get()) {
                        long o = memory.getAndAdd(64, 1L);
                        inti.add(o);
                        if (o > 16_000) {
                            return;
                        }
                    }

                }
            });

            tt.add(x);
            listo.add(inti);
        }

        for (Thread t : tt) {
            t.start();
        }

        Thread.sleep(5000);
        bool.set(false);
        for (Thread t : tt) {
            t.join();
        }

        int sz = 0;

        for (Collection<Long> inti : listo) {
            Assert.assertFalse(inti.isEmpty());
            sz += inti.size();
        }

        boolean[] res = new boolean[sz];
        for (Collection<Long> inti : listo) {
            for (long i : inti) {
                Assert.assertFalse(res[(int) i]);
                res[(int) i] = true;
            }
        }

        for (int i = 0; i < res.length; i++) {
            Assert.assertTrue(res[i]);
        }

        Assert.assertEquals(res.length, memory.readInt(64));


        for (Collection<Long> inti : listo) {
            Iterator<Long> iterator = inti.iterator();
            long oval = iterator.next();
            while (iterator.hasNext()) {
                long next = iterator.next();
                Assert.assertTrue(next > oval);
                oval = next;
            }
        }

        listo.clear();
        System.gc();

    }

    @Test
    public void testAtomicInteger() throws Exception {
        if (!memory.supportsCompareAndSet4Byte()) {
            return;
        }

        memory.zero();

        final AtomicBoolean bool = new AtomicBoolean(true);
        List<Thread> tt = new ArrayList<>();
        List<Collection<Integer>> listo = new ArrayList<>();
        for (int i = 0; i < Runtime.getRuntime().availableProcessors(); i++) {

            final Collection<Integer> inti = new LinkedList<>();
            Thread x = new Thread(new Runnable() {
                @Override
                public void run() {
                    while (bool.get()) {
                        int o = memory.getAndAdd(64, 1);
                        inti.add(o);
                        if (o > 16_000) {
                            return;
                        }
                    }

                }
            });

            tt.add(x);
            listo.add(inti);
        }

        for (Thread t : tt) {
            t.start();
        }

        Thread.sleep(5000);
        bool.set(false);
        for (Thread t : tt) {
            t.join();
        }

        int sz = 0;

        for (Collection<Integer> inti : listo) {
            Assert.assertFalse(inti.isEmpty());
            sz += inti.size();
        }

        boolean[] res = new boolean[sz];
        for (Collection<Integer> inti : listo) {
            for (int i : inti) {
                Assert.assertFalse(res[i]);
                res[i] = true;
            }
        }

        for (int i = 0; i < res.length; i++) {
            Assert.assertTrue(res[i]);
        }

        Assert.assertEquals(res.length, memory.readInt(64));


        for (Collection<Integer> inti : listo) {
            Iterator<Integer> iterator = inti.iterator();
            int oval = iterator.next();
            while (iterator.hasNext()) {
                int next = iterator.next();
                Assert.assertTrue(next > oval);
                oval = next;
            }
        }

        listo.clear();
        System.gc();
    }

    @Test
    public void testMTCas4() throws Exception {
        if (!memory.supportsCompareAndSet4Byte()) {
            return;
        }

        memory.zero();

        final AtomicBoolean bool = new AtomicBoolean(true);
        List<Thread> tt = new ArrayList<>();
        List<Collection<Integer>> listo = new ArrayList<>();
        for (int i = 0; i < Runtime.getRuntime().availableProcessors(); i++) {

            final Collection<Integer> inti = new LinkedList<>();
            Thread x = new Thread(new Runnable() {
                @Override
                public void run() {
                    while (bool.get()) {
                        int o = memory.readInt(64);
                        if (memory.compareAndSet(64, o, o + 1)) {
                            inti.add(o);
                            if (o > 16_000) {
                                return;
                            }
                        }
                    }

                }
            });

            tt.add(x);
            listo.add(inti);
        }

        for (Thread t : tt) {
            t.start();
        }

        Thread.sleep(5000);
        bool.set(false);
        for (Thread t : tt) {
            t.join();
        }

        int sz = 0;

        for (Collection<Integer> inti : listo) {
            Assert.assertFalse(inti.isEmpty());
            sz += inti.size();
        }

        boolean[] res = new boolean[sz];
        for (Collection<Integer> inti : listo) {
            for (int i : inti) {
                Assert.assertFalse(res[i]);
                res[i] = true;
            }
        }

        for (int i = 0; i < res.length; i++) {
            Assert.assertTrue(res[i]);
        }

        Assert.assertEquals(res.length, memory.readInt(64));


        for (Collection<Integer> inti : listo) {
            Iterator<Integer> iterator = inti.iterator();
            int oval = iterator.next();
            while (iterator.hasNext()) {
                int next = iterator.next();
                Assert.assertTrue(next > oval);
                oval = next;
            }
        }
    }

    @Test
    public void testSingleByteWriteAndRead() throws Throwable {
        ArrayList<Integer> tempInt = new ArrayList<>(0xff);
        for (int i = 0; i < 0xff; i++) {
            tempInt.add(i);
        }

        Collections.shuffle(tempInt);

        for (int value : tempInt) {
            for (long i = 0; i < memory.size(); i++) {
                memory.write(i, (byte) value);
                Assert.assertEquals((byte) value, memory.read(i));
                Assert.assertEquals(value, memory.readUnsignedByte(i));

            }
        }
    }

    @Test
    public void testSingleShortWriteAndRead() throws Throwable {
        mkRandom();

        for (short value : randomShorts) {
            for (long i = 0; i + 1 < memory.size(); i++) {
                memory.write(i, value);
                Assert.assertEquals(value, memory.readShort(i));
                Assert.assertEquals(value & 0xffff, memory.readUnsignedShort(i));
            }
        }
    }

    @Test
    public void testSingleIntWriteAndRead() throws Throwable {
        mkRandom();

        for (int value : randomInts) {
            for (long i = 0; i + 3 < memory.size(); i++) {
                memory.write(i, value);
                Assert.assertEquals(value, memory.readInt(i));
            }
        }
    }

    @Test
    public void testSingleLongWriteAndRead() throws Throwable {
        mkRandom();

        for (long value : randomLongs) {
            for (long i = 0; i + 7 < memory.size(); i++) {
                //System.out.println(i);
                memory.write(i, value);
                Assert.assertEquals(value, memory.readLong(i));
            }
        }
    }


    @Test
    public void testHeapBufferRead() throws Throwable {
        for (int i = 0; i < memory.size(); i++) {
            memory.writeByte(i, (byte) i);
        }

        ByteBuffer direct = ByteBuffer.allocateDirect((int) (memory.size()));
        ByteBuffer direct2 = ByteBuffer.allocateDirect((int) (memory.size()));

        for (int i = 0; i < memory.size(); ) {
            int rem = (int) memory.remaining(i);
            int nextRead = rem == 1 ? 1 : rng.nextInt(rem - 1) + 1;
            memory.read(i, direct, nextRead);
            i += nextRead;
        }

        memory.read(0, direct2, (int) memory.size());

        Assert.assertEquals(memory.size(), direct.position());
        Assert.assertEquals(memory.size(), direct2.position());
        direct.position(0);
        for (int i = 0; i < memory.size(); i++) {
            Assert.assertEquals((byte) i, direct.get(i));
            Assert.assertEquals((byte) i, direct2.get(i));
        }
    }

    @Test
    public void testByteBufferRead() throws Throwable {
        for (int i = 0; i < memory.size(); i++) {
            memory.writeByte(i, (byte) i);
        }

        ByteBuffer direct = ByteBuffer.allocate((int) (memory.size()));
        ByteBuffer direct2 = ByteBuffer.allocate((int) (memory.size()));

        for (int i = 0; i < memory.size(); ) {
            int rem = (int) memory.remaining(i);
            int nextRead = rem == 1 ? 1 : rng.nextInt(rem - 1) + 1;
            memory.read(i, direct, nextRead);
            i += nextRead;
        }

        memory.read(0, direct2, (int) memory.size());

        Assert.assertEquals(memory.size(), direct.position());
        Assert.assertEquals(memory.size(), direct2.position());
        direct.position(0);
        for (int i = 0; i < memory.size(); i++) {
            Assert.assertEquals((byte) i, direct.get(i));
            Assert.assertEquals((byte) i, direct2.get(i));
        }
    }

    @Test
    public void testHeapBufferWrite() throws Throwable {
        ByteBuffer direct = ByteBuffer.allocateDirect((int) (memory.size()));
        ByteBuffer direct2 = ByteBuffer.allocateDirect((int) (memory.size()));
        memory.zero();
        for (int i = 0; i < memory.size(); i++) {
            direct.put(i, (byte) i);
            direct2.put(i, (byte) i);
        }

        for (int i = 0; i < memory.size(); ) {
            int rem = (int) memory.remaining(i);
            int nextRead = rem == 1 ? 1 : rng.nextInt(rem - 1) + 1;
            memory.write(i, direct, nextRead);
            i += nextRead;
        }

        Assert.assertEquals(memory.size(), direct.position());
        for (int i = 0; i < memory.size(); i++) {
            Assert.assertEquals((byte) i, memory.read(i));
        }

        memory.zero();
        memory.write(0, direct2, direct2.remaining());
        Assert.assertEquals(memory.size(), direct2.position());
        for (int i = 0; i < memory.size(); i++) {
            Assert.assertEquals((byte) i, memory.read(i));
        }
    }

    @Test
    public void testByteBufferWrite() throws Throwable {
        ByteBuffer direct = ByteBuffer.allocate((int) (memory.size()));
        ByteBuffer direct2 = ByteBuffer.allocate((int) (memory.size()));
        memory.zero();
        for (int i = 0; i < memory.size(); i++) {
            direct.put(i, (byte) i);
            direct2.put(i, (byte) i);
        }

        for (int i = 0; i < memory.size(); ) {
            int rem = (int) memory.remaining(i);
            int nextRead = rem == 1 ? 1 : rng.nextInt(rem - 1) + 1;
            memory.write(i, direct, nextRead);
            i += nextRead;
        }

        Assert.assertEquals(memory.size(), direct.position());
        for (int i = 0; i < memory.size(); i++) {
            Assert.assertEquals((byte) i, memory.read(i));
        }

        memory.zero();
        memory.write(0, direct2, direct2.remaining());
        Assert.assertEquals(memory.size(), direct2.position());
        for (int i = 0; i < memory.size(); i++) {
            Assert.assertEquals((byte) i, memory.read(i));
        }
    }


    @Test
    public void xadd1Byte() throws Throwable {
        if (!memory.supportsCompareAndSet1Byte()) {
            try {
                memory.getAndAdd(0, (byte) 1);
                Assert.fail("uoe expected");
            } catch (UnsupportedOperationException uoe) {

            }
            return;
        }

        for (long i = 0; i < memory.size(); i++) {
            memory.write(i, (byte) 0);
            if ((i % memory.compareAndSet1ByteAlignment()) != 0) {
                try {
                    memory.getAndAdd(i, (byte) 1);
                    Assert.fail("iae expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().toLowerCase().contains("align"));
                }
                continue;
            }

            for (int j = 0; j <= 0xff; j++) {
                byte aByte = memory.getAndAdd(i, (byte) 1);
                Assert.assertEquals(j, aByte & 0xFF);
            }
            memory.write(i, (byte) 0);
            for (int j = 0; j <= 0xff; j++) {
                byte aByte = memory.getAndAdd(i, (byte) -1);
                Assert.assertEquals((byte) -j, aByte);
            }

            memory.write(i, Byte.MAX_VALUE);
            memory.getAndAdd(i, (byte) 1);
            Assert.assertEquals(Byte.MIN_VALUE, memory.read(i));
            memory.getAndAdd(i, (byte) -1);
            Assert.assertEquals(Byte.MAX_VALUE, memory.read(i));
        }
    }

    @Test
    public void xadd2Byte() throws Throwable {
        if (!memory.supportsCompareAndSet2Byte()) {
            try {
                memory.getAndAdd(0, (short) 1);
                Assert.fail("uoe expected");
            } catch (UnsupportedOperationException uoe) {

            }
            return;
        }

        mkRandom();
        for (long i = 0; i + 1 < memory.size(); i++) {
            memory.write(i, (short) 0);
            if ((i % memory.compareAndSet2ByteAlignment()) != 0) {
                try {
                    memory.getAndAdd(i, (short) 1);
                    Assert.fail("iae expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().toLowerCase().contains("align"));
                }
                continue;
            }
            int akku = 0;
            for (short j : randomShorts) {
                short aByte = memory.getAndAdd(i, j);
                Assert.assertEquals(akku, aByte & 0xFFFF);
                akku += j;
                akku &= 0xffff;
            }

            memory.write(i, Short.MAX_VALUE);
            memory.getAndAdd(i, (short) 1);
            Assert.assertEquals(Short.MIN_VALUE, memory.readShort(i));
            memory.getAndAdd(i, (short) -1);
            Assert.assertEquals(Short.MAX_VALUE, memory.readShort(i));
        }
    }

    @Test
    public void xadd4Byte() throws Throwable {
        if (!memory.supportsCompareAndSet4Byte()) {
            try {
                memory.getAndAdd(0, 1);
                Assert.fail("uoe expected");
            } catch (UnsupportedOperationException uoe) {

            }
            return;
        }

        mkRandom();
        for (long i = 0; i + 3 < memory.size(); i++) {
            memory.write(i, 0);
            int akku = 0;
            if ((i % memory.compareAndSet4ByteAlignment()) != 0) {
                try {
                    memory.getAndAdd(i, 1);
                    Assert.fail("iae expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().toLowerCase().contains("align"));
                }
                continue;
            }

            for (int j : randomInts) {
                int aByte = memory.getAndAdd(i, j);
                Assert.assertEquals(akku, aByte);
                akku += j;
            }

            memory.write(i, Integer.MAX_VALUE);
            memory.getAndAdd(i, 1);
            Assert.assertEquals(Integer.MIN_VALUE, memory.readInt(i));
            memory.getAndAdd(i, -1);
            Assert.assertEquals(Integer.MAX_VALUE, memory.readInt(i));
        }
    }

    @Test
    public void xadd8Byte() throws Throwable {
        if (!memory.supportsCompareAndSet8Byte()) {
            try {
                memory.getAndAdd(0, 1L);
                Assert.fail("uoe expected");
            } catch (UnsupportedOperationException uoe) {

            }
            return;
        }

        mkRandom();
        int inc = 1;

        for (long i = 0; i + 7 < memory.size(); i += inc) {
            memory.write(i, (long) 0);
            long akku = 0;
            if ((i % memory.compareAndSet8ByteAlignment()) != 0) {
                try {
                    memory.getAndAdd(i, 1L);
                    Assert.fail("iae expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().toLowerCase().contains("align"));
                }
                continue;
            }
            for (long j : randomLongs) {
                long aByte = memory.getAndAdd(i, j);
                Assert.assertEquals(akku, aByte);
                akku += j;
            }

            memory.write(i, Long.MAX_VALUE);
            memory.getAndAdd(i, (long) 1);
            Assert.assertEquals(Long.MIN_VALUE, memory.readLong(i));
            memory.getAndAdd(i, (long) -1);
            Assert.assertEquals(Long.MAX_VALUE, memory.readLong(i));
        }
    }

    @Test
    public void cmpxchg1b() throws Throwable {
        if (!memory.supportsCompareAndSet1Byte()) {
            try {
                memory.compareAndSet(0, (byte) 0, (byte) 1);
                Assert.fail("uoe expected");
            } catch (UnsupportedOperationException uoe) {

            }
            return;
        }

        for (long i = 0; i < memory.size(); i++) {
            if ((i % memory.compareAndSet2ByteAlignment()) != 0) {
                try {
                    memory.compareAndSet(0, (byte) 0, (byte) 1);
                    Assert.fail("IAE expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().contains("align"));
                }
                continue;
            }
            for (int j = 0; j < 0xff; j++) {
                memory.write(i, (byte) j);
                Assert.assertFalse(memory.compareAndSet(i, (byte) (j + 1), (byte) (j + 2)));
                Assert.assertTrue(memory.compareAndSet(i, (byte) j, (byte) (j + 1)));
                Assert.assertFalse(memory.compareAndSet(i, (byte) j, (byte) (j + 2)));
            }
        }
    }

    @Test
    public void cmpxchg2b() throws Throwable {
        if (!memory.supportsCompareAndSet2Byte()) {
            try {
                memory.compareAndSet(0, (short) 0, (short) 1);
                Assert.fail("uoe expected");
            } catch (UnsupportedOperationException uoe) {

            }
            return;
        }

        mkRandom();
        for (long i = 0; i + 1 < memory.size(); i++) {
            if ((i % memory.compareAndSet1ByteAlignment()) != 0) {
                try {
                    memory.compareAndSet(i, (short) 0, (short) 1);
                    Assert.fail("IAE expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().contains("align"));
                }
                continue;
            }
            for (short j : randomShorts) {
                memory.write(i, j);
                Assert.assertFalse(memory.compareAndSet(i, (short) (j + 1), (short) (j)));
                Assert.assertTrue(memory.compareAndSet(i, j, (short) (j + 1)));
                Assert.assertFalse(memory.compareAndSet(i, j, (short) (j + 2)));
            }
        }
    }

    @Test
    public void cmpxchg4b() throws Throwable {
        if (!memory.supportsCompareAndSet4Byte()) {
            try {
                memory.compareAndSet(0, 0, 1);
                Assert.fail("uoe expected");
            } catch (UnsupportedOperationException uoe) {

            }
            return;
        }

        mkRandom();
        for (long i = 0; i + 3 < memory.size(); i++) {
            if ((i % memory.compareAndSet4ByteAlignment()) != 0) {
                try {
                    memory.compareAndSet(i, 0, 1);
                    Assert.fail("IAE expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().contains("align"));
                }
                continue;
            }
            for (int j : randomInts) {
                memory.write(i, j);
                Assert.assertFalse(memory.compareAndSet(i, j + 1, j + 2));
                Assert.assertTrue(memory.compareAndSet(i, j, j + 1));
                Assert.assertFalse(memory.compareAndSet(i, j, j + 2));
            }
        }
    }

    @Test
    public void cmpxchg8b() throws Throwable {
        if (!memory.supportsCompareAndSet8Byte()) {
            try {
                memory.compareAndSet(0, 0L, 1L);
                Assert.fail("uoe expected");
            } catch (UnsupportedOperationException uoe) {

            }
            return;
        }

        mkRandom();

        for (long i = 0; i + 7 < memory.size(); i++) {
            if ((i % memory.compareAndSet8ByteAlignment()) != 0) {
                try {
                    memory.compareAndSet(i, 0L, 1L);
                    Assert.fail("IAE expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().contains("align"));
                }
                continue;
            }
            for (long j : randomLongs) {
                memory.write(i, j);
                Assert.assertFalse(memory.compareAndSet(i, j + 1, j + 2));
                Assert.assertEquals(memory.readLong(i), j);
                if (!memory.compareAndSet(i, j, j + 1)) {
                    System.out.println("MEMOP " + i + " " + j);
                    Assert.fail();
                }

                Assert.assertEquals(memory.readLong(i), j + 1);
                Assert.assertFalse(memory.compareAndSet(i, j, j + 2));
                Assert.assertEquals(memory.readLong(i), j + 1);
            }
        }
    }

    @Test
    public void compxchg16b() throws Throwable {
        byte[] buf = new byte[16];
        byte[] buf2 = new byte[16];
        byte[] buf3 = new byte[32];

        if (!memory.supportsCompareAndSet16Byte()) {
            try {
                memory.compareAndSet(0, buf3);
                Assert.fail();
            } catch (UnsupportedOperationException exc) {

            }
            return;
        }

        long start = memory.getNativePointer() % memory.compareAndSet16ByteAlignment();


        for (long i = start; i + 15 < memory.size(); i++) {
            rng.nextBytes(buf);
            rng.nextBytes(buf2);
            System.arraycopy(buf, 0, buf3, 0, buf.length);
            System.arraycopy(buf2, 0, buf3, buf.length, buf2.length);
            memory.write(i, buf);

            if (((i - start) % memory.compareAndSet16ByteAlignment()) != 0) {
                try {
                    memory.compareAndSet(i, buf3);
                    Assert.fail("IAE expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().contains("align"));
                }
                continue;
            }

            Assert.assertTrue(memory.compareAndSet(i, buf3));

            memory.read(i, buf, 0, buf.length);
            Assert.assertTrue(Arrays.equals(buf, buf2));
        }

        try {
            memory.compareAndSet(1, buf3);
            Assert.fail();
        } catch (IllegalArgumentException exc) {

        }

    }

    @Test
    public void xchg8b() throws Throwable {
        if (!memory.supportsCompareAndSet8Byte()) {
            try {
                memory.getAndSet(0, 0L);
                Assert.fail();
            } catch (UnsupportedOperationException exc) {

            }
            return;
        }

        for (long i = 0; i + 7 < memory.size(); i++) {
            long tempBase = rng.nextLong();
            long tempSet = rng.nextLong();
            memory.write(i, tempBase);
            if ((i % memory.compareAndSet8ByteAlignment()) != 0) {
                try {
                    memory.getAndSet(i, tempSet);
                    Assert.fail("IAE expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().contains("align"));
                }
                continue;
            }

            Assert.assertEquals(tempBase, memory.getAndSet(i, tempSet));
            Assert.assertEquals(tempSet, memory.readLong(i));
        }
    }


    @Test
    public void xchg4b() throws Throwable {
        if (!memory.supportsCompareAndSet4Byte()) {
            try {
                memory.getAndSet(0, 0);
                Assert.fail();
            } catch (UnsupportedOperationException exc) {

            }
            return;
        }


        for (long i = 0; i + 7 < memory.size(); i++) {
            int tempBase = rng.nextInt();
            int tempSet = rng.nextInt();
            memory.write(i, tempBase);
            if ((i % memory.compareAndSet4ByteAlignment()) != 0) {
                try {
                    memory.getAndSet(i, tempSet);
                    Assert.fail("IAE expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().contains("align"));
                }
                continue;
            }
            Assert.assertEquals(tempBase, memory.getAndSet(i, tempSet));
            Assert.assertEquals(tempSet, memory.readInt(i));
        }
    }

    @Test
    public void xchg2b() throws Throwable {
        if (!memory.supportsCompareAndSet2Byte()) {
            try {
                memory.getAndSet(0, (short) 0);
                Assert.fail();
            } catch (UnsupportedOperationException exc) {

            }
            return;
        }


        for (long i = 0; i + 7 < memory.size(); i++) {
            short tempBase = (short) rng.nextInt();
            short tempSet = (short) rng.nextInt();
            memory.write(i, tempBase);
            if ((i % memory.compareAndSet2ByteAlignment()) != 0) {
                try {
                    memory.getAndSet(i, tempSet);
                    Assert.fail("IAE expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().contains("align"));
                }
                continue;
            }
            Assert.assertEquals(tempBase, memory.getAndSet(i, tempSet));
            Assert.assertEquals(tempSet, memory.readShort(i));
        }
    }

    @Test
    public void xchg1b() throws Throwable {
        if (!memory.supportsCompareAndSet1Byte()) {
            try {
                memory.getAndSet(0, (byte) 0);
                Assert.fail();
            } catch (UnsupportedOperationException exc) {

            }
            return;
        }


        for (long i = 0; i + 7 < memory.size(); i++) {
            byte tempBase = (byte) rng.nextInt();
            byte tempSet = (byte) rng.nextInt();
            memory.write(i, tempBase);
            if ((i % memory.compareAndSet1ByteAlignment()) != 0) {
                try {
                    memory.getAndSet(i, tempSet);
                    Assert.fail("IAE expected");
                } catch (IllegalArgumentException iae) {
                    Assert.assertTrue(iae.getMessage().contains("align"));
                }
                continue;
            }
            Assert.assertEquals(tempBase, memory.getAndSet(i, tempSet));
            Assert.assertEquals(tempSet, memory.read(i));
        }
    }

    @Test
    public void testWriteAndReadByteArrays() throws Throwable {
        int size = (int) memory.size() / 8;

        byte[] buf = new byte[size];
        byte[] buf2 = new byte[size];

        for (int i = 0; i < 8; i++) {
            rng.nextBytes(buf);
            memory.write(i * size, buf, 0, size);
            memory.read(i * size, buf2, 0, size);
            Assert.assertTrue(Arrays.equals(buf, buf2));
        }
    }

    @Test
    public void testOutOfBoundsWrite() throws Throwable {
        try {
            memory.write(memory.size(), (byte) 0);
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.write(memory.size() + 1, (byte) 0);
            Assert.fail();
        } catch (Exception e) {

        }
        memory.write(memory.size() - 1, (byte) 0);

        try {
            memory.write(memory.size() - 1, (short) 0);
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.write(memory.size(), (short) 0);
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.write(memory.size() + 1, (short) 0);
            Assert.fail();
        } catch (Exception e) {

        }
        memory.write(memory.size() - 2, (short) 0);

        try {
            memory.write(memory.size() - 3, 0);
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.write(memory.size(), 0);
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.write(memory.size() + 1, 0);
            Assert.fail();
        } catch (Exception e) {

        }
        memory.write(memory.size() - 4, 0);

        try {
            memory.write(memory.size() - 7, (long) 0);
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.write(memory.size(), (long) 0);
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.write(memory.size() + 1, (long) 0);
            Assert.fail();
        } catch (Exception e) {

        }
        memory.write(memory.size() - 8, (long) 0);

        try {
            memory.write(-1, (long) 0);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.write(-64, (long) 0);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.write(-64, 0);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.write(-1, 0);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.write(-64, (short) 0);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.write(-1, (short) 0);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.write(-64, (byte) 0);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.write(-1, (byte) 0);
            Assert.fail();
        } catch (Exception exc) {

        }
    }

    @Test
    public void testOutOfBoundsRead() throws Throwable {
        try {
            memory.read(memory.size());
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.read(memory.size() + 1);
            Assert.fail();
        } catch (Exception e) {

        }
        memory.read(memory.size() - 1);

        try {
            memory.readShort(memory.size() - 1);
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.readShort(memory.size());
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.readShort(memory.size() + 1);
            Assert.fail();
        } catch (Exception e) {

        }
        memory.readShort(memory.size() - 2);

        try {
            memory.readInt(memory.size() - 3);
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.readInt(memory.size());
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.readInt(memory.size() + 1);
            Assert.fail();
        } catch (Exception e) {

        }
        memory.readInt(memory.size() - 4);

        try {
            memory.readLong(memory.size() - 7);
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.readLong(memory.size());
            Assert.fail();
        } catch (Exception e) {

        }
        try {
            memory.readLong(memory.size() + 1);
            Assert.fail();
        } catch (Exception e) {

        }
        memory.readLong(memory.size() - 8);

        try {
            memory.readLong(-1);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.readLong(-64);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.readInt(-64);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.readInt(-1);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.readShort(-64);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.readShort(-1);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.read(-64);
            Assert.fail();
        } catch (Exception exc) {

        }
        try {
            memory.read(-1);
            Assert.fail();
        } catch (Exception exc) {

        }
    }

    @Test
    public void testOutOfBoundsCMPXCHG() throws Throwable {
        if (memory.supportsCompareAndSet1Byte()) {
            //CMGPXCHG byte
            try {
                memory.compareAndSet(memory.size(), (byte) 0, (byte) 0);
                Assert.fail();
            } catch (Exception exc) {

            }

            try {
                memory.compareAndSet(memory.size() + 1, (byte) 0, (byte) 0);
                Assert.fail();
            } catch (Exception exc) {

            }

            try {
                memory.compareAndSet(-64, (byte) 0, (byte) 0);
                Assert.fail();
            } catch (Exception exc) {

            }

            try {
                memory.compareAndSet(-1, (byte) 0, (byte) 0);
                Assert.fail();
            } catch (Exception exc) {

            }

            memory.compareAndSet(memory.size() - 1, (byte) 0, (byte) 0);
        }


        //CMGPXCHG short
        if (memory.supportsCompareAndSet2Byte()) {
            try {
                memory.compareAndSet(memory.size() - 1, (short) 0, (short) 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(memory.size(), (short) 0, (short) 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(memory.size() + 1, (short) 0, (short) 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(-64, (short) 0, (short) 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(-1, (short) 0, (short) 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            memory.compareAndSet(memory.size() - 2, (short) 0, (short) 0);
        }
        //CMGPXCHG int
        if (memory.supportsCompareAndSet4Byte()) {
            try {
                memory.compareAndSet(memory.size() - 3, 0, 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(memory.size(), 0, 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(memory.size() + 1, 0, 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(-64, 0, 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(-1, 0, 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            memory.compareAndSet(memory.size() - 4, 0, 0);
        }
        //CMGPXCHG long
        if (memory.supportsCompareAndSet8Byte()) {
            try {
                memory.compareAndSet(memory.size() - 7, (long) 0, (long) 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(memory.size(), (long) 0, (long) 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(memory.size() + 1, (long) 0, (long) 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(-64, (long) 0, (long) 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(-1, (long) 0, (long) 0);
                Assert.fail();
            } catch (Exception exc) {

            }
            memory.compareAndSet(memory.size() - 8, (long) 0, (long) 0);
        }

        if (memory.supportsCompareAndSet16Byte()) {
            //CMPXCHG16B
            byte[] tempBuf = new byte[32];
            try {
                memory.compareAndSet(memory.size() - 15, tempBuf);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(memory.size(), tempBuf);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(memory.size() + 1, tempBuf);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(-64, tempBuf);
                Assert.fail();
            } catch (Exception exc) {

            }
            try {
                memory.compareAndSet(-7, tempBuf);
                Assert.fail();
            } catch (Exception exc) {

            }
            memory.compareAndSet(memory.size() - 16, tempBuf);
        }
    }

    @Test
    public void testOutOfBoundsXADD() throws Throwable {

        if (memory.supportsCompareAndSet8Byte()) {
            try {
                memory.getAndAdd(-1, (long) 1);
                Assert.fail();
            } catch (Exception exc) {

            }

            try {
                memory.getAndAdd(memory.size() - 7, (long) 1);
                Assert.fail();
            } catch (Exception exc) {

            }


            memory.getAndAdd(memory.size() - 8, (long) 1);
        }

        if (memory.supportsCompareAndSet4Byte()) {
            try {
                memory.getAndAdd(-1, 1);
                Assert.fail();
            } catch (Exception exc) {

            }

            try {
                memory.getAndAdd(memory.size() - 3, 1);
                Assert.fail();
            } catch (Exception exc) {

            }

            memory.getAndAdd(memory.size() - 4, 1);
        }

        if (memory.supportsCompareAndSet2Byte()) {
            try {
                memory.getAndAdd(-1, (short) 1);
                Assert.fail();
            } catch (Exception exc) {

            }

            try {
                memory.getAndAdd(memory.size() - 1, (short) 1);
                Assert.fail();
            } catch (Exception exc) {

            }


            memory.getAndAdd(memory.size() - 2, (short) 1);
        }


        if (memory.supportsCompareAndSet1Byte()) {
            try {
                memory.getAndAdd(-1, (byte) 1);
                Assert.fail();
            } catch (Exception exc) {

            }

            //TEST OOB TOO BIG
            try {
                memory.getAndAdd(memory.size(), (byte) 1);
                Assert.fail();
            } catch (Exception exc) {

            }


            memory.getAndAdd(memory.size() - 1, (byte) 1);
        }
    }

    @Test
    public void testOutOfBoundsXCHG() throws Throwable {
        //UNDERFLOW
        if (memory.supportsCompareAndSet8Byte()) {
            try {
                memory.getAndSet(-1, (long) 1);
                Assert.fail();
            } catch (Exception exc) {

            }

            try {
                memory.getAndSet(memory.size() - 7, (long) 1);
                Assert.fail();
            } catch (Exception exc) {

            }


            memory.getAndSet(memory.size() - 8, (long) 1);
        }

        if (memory.supportsCompareAndSet4Byte()) {
            try {
                memory.getAndSet(-1, 1);
                Assert.fail();
            } catch (Exception exc) {

            }

            try {
                memory.getAndSet(memory.size() - 3, 1);
                Assert.fail();
            } catch (Exception exc) {

            }

            memory.getAndSet(memory.size() - 4, 1);
        }

        if (memory.supportsCompareAndSet2Byte()) {
            try {
                memory.getAndSet(-1, (short) 1);
                Assert.fail();
            } catch (Exception exc) {

            }

            try {
                memory.getAndSet(memory.size() - 1, (short) 1);
                Assert.fail();
            } catch (Exception exc) {

            }


            memory.getAndSet(memory.size() - 2, (short) 1);
        }


        if (memory.supportsCompareAndSet1Byte()) {
            try {
                memory.getAndSet(-1, (byte) 1);
                Assert.fail();
            } catch (Exception exc) {

            }

            //TEST OOB TOO BIG
            try {
                memory.getAndSet(memory.size(), (byte) 1);
                Assert.fail();
            } catch (Exception exc) {

            }


            memory.getAndSet(memory.size() - 1, (byte) 1);
        }
    }

    private boolean checkOffset(long l) {
        if (l < 0) {
            return false;
        }

        return memory.size() - l > 0;
    }

    @Test
    public void testMemset() throws Throwable {
        byte tempVal = 0;
        for (long l = 0; l < memory.size(); l++) {
            tempVal++;
            long tempLen = Math.min(memory.size() - l, Math.abs(rng.nextLong()) % 32);


            if (checkOffset(l - 1)) {
                memory.write(l - 1, (byte) (tempVal - 1));
            }

            if (checkOffset(l + tempLen)) {
                memory.write(l + tempLen, (byte) (tempVal + 1));
            }

            for (long i = 0; i < tempLen; i++) {
                memory.write(l + i, (byte) (tempVal - 2));
            }

            memory.set(l, tempVal, tempLen);

            if (checkOffset(l - 1)) {
                Assert.assertEquals((byte) (tempVal - 1), memory.read(l - 1));
            }


            if (checkOffset(l + tempLen)) {
                Assert.assertEquals((byte) (tempVal + 1), memory.read(l + tempLen));
            }


            for (long i = 0; i < tempLen; i++) {
                Assert.assertEquals(tempVal, memory.read(l + i));
            }

            memory.write(l, (byte) 2);
            memory.set(l, (byte) 1, 0);
            Assert.assertEquals((byte) 2, memory.read(l));

            try {
                memory.set(l, (byte) 0, (memory.size() - l) + 1);
                Assert.fail();
            } catch (Exception exc) {

            }

            try {
                memory.set(l, (byte) 0, -1);
                Assert.fail();
            } catch (Exception exc) {

            }

        }

        memory.set(memory.size() - 1, (byte) 0, 1);

        try {
            memory.set(memory.size(), (byte) 0, 1);
            Assert.fail();
        } catch (Exception exc) {

        }


        try {
            memory.set(memory.size(), (byte) 0, -1);
            Assert.fail();
        } catch (Exception exc) {

        }


        try {
            memory.set(memory.size() + 5, (byte) 0, -8);
            Assert.fail();
        } catch (Exception exc) {

        }


        try {
            memory.set(memory.size() + 5, (byte) 0, 1);
            Assert.fail();
        } catch (Exception exc) {

        }


        try {
            memory.set(memory.size(), (byte) 0, 0);
            Assert.fail();
        } catch (Exception exc) {

        }
    }


    @Test
    public void testExInt1() {
        int[] x = new int[]{0x24, 0xFE77};
        memory.writeByte(3, 1);
        memory.write(0, x, 1, 0, 2);
        x = new int[]{0x24, 0x77};
        byte[] x2 = new byte[]{0x24, 0x77};
        byte[] x3 = new byte[2];
        int[] r2 = new int[2];
        memory.read(0, r2, 1, 0, 2);
        memory.read(0, x3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertArrayEquals(x2, x3);
        Assert.assertEquals(1, memory.read(3));
    }

    @Test
    public void testExInt2() {
        int[] x = new int[]{0x24, 0x77FE};
        memory.writeByte(4, 1);
        memory.write(0, x, 2, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x24, 0x77, (byte) 0xFE} :
                new byte[]{0x24, 0x00, (byte) 0xFE, 0x77};
        byte[] x3 = new byte[4];
        memory.read(0, x3);
        int[] r2 = new int[2];
        memory.read(0, r2, 2, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(4));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExInt3() {
        int[] x = new int[]{0x24, 0x77FE};
        memory.writeByte(6, 1);
        memory.write(0, x, 3, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x24, 0x00, 0x77, (byte) 0xFE} :
                new byte[]{0x24, 0x00, 0x00, (byte) 0xFE, 0x77, 0x00};
        byte[] x3 = new byte[6];
        memory.read(0, x3);
        int[] r2 = new int[2];
        memory.read(0, r2, 3, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(6));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExInt4() {
        int[] x = new int[]{0x24, 0x77FE};
        memory.writeByte(8, 1);
        memory.write(0, x, 4, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x77, (byte) 0xFE} :
                new byte[]{0x24, 0x00, 0x00, 0x00, (byte) 0xFE, 0x77, 0x00, 0x00};
        byte[] x3 = new byte[8];
        memory.read(0, x3);
        int[] r2 = new int[2];
        memory.read(0, r2, 4, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(8));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExInt5() {
        int[] x = new int[]{0x24, 0x77FE};
        memory.writeByte(10, 1);
        memory.write(0, x, 5, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x00, (byte) 0xFE, 0x77, 0x00, 0x00, 0x00};
        byte[] x3 = new byte[10];
        memory.read(0, x3);
        int[] r2 = new int[2];
        memory.read(0, r2, 5, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(10));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExInt6() {
        int[] x = new int[]{0x24, 0x77FE};
        memory.writeByte(12, 1);
        memory.write(0, x, 6, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x00, 0x00, (byte) 0xFE, 0x77, 0x00, 0x00, 0x00, 0x00};
        byte[] x3 = new byte[12];
        memory.read(0, x3);
        int[] r2 = new int[2];
        memory.read(0, r2, 6, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(12));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExLong1() {
        long[] x = new long[]{0x24, 0xFE77, 0xFEABC0AA42L};
        memory.writeByte(4, 1);
        memory.write(0, x, 1, 0, 3);
        x = new long[]{0x24, 0x77, 0x42};
        byte[] x2 = new byte[]{0x24, 0x77, 0x42};
        byte[] x3 = new byte[3];
        long[] r2 = new long[3];
        memory.read(0, r2, 1, 0, 3);
        memory.read(0, x3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertArrayEquals(x2, x3);
        Assert.assertEquals(1, memory.read(4));
    }

    @Test
    public void testExLong2() {
        long[] x = new long[]{0x24, 0xFE77, 0xFEABC0AA42L};
        memory.writeByte(6, 1);
        memory.write(0, x, 2, 0, 3);
        x = new long[]{0x24, 0xFE77, 0xAA42L};
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x24, (byte) 0xFE, 0x77, (byte) 0xAA, 0x42} :
                new byte[]{0x24, 0x00, 0x77, (byte) 0xFE, 0x42, (byte) 0xAA};
        byte[] x3 = new byte[6];
        memory.read(0, x3);
        long[] r2 = new long[3];
        memory.read(0, r2, 2, 0, 3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(6));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExLong3() {
        long[] x = new long[]{0x24, 0xFE77, 0xFEABC0AA42L};
        memory.writeByte(9, 1);
        memory.write(0, x, 3, 0, 3);
        x = new long[]{0x24, 0xFE77, 0xC0AA42L};
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x24, 0x00, (byte) 0xFE, 0x77, (byte) 0xC0, (byte) 0xAA, 0x42} :
                new byte[]{0x24, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00, 0x42, (byte) 0xAA, (byte) 0xC0};
        byte[] x3 = new byte[9];
        memory.read(0, x3);
        long[] r2 = new long[3];
        memory.read(0, r2, 3, 0, 3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(9));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExLong4() {
        long[] x = new long[]{0x24, 0xFE77, 0xFEABC0AA42L};
        memory.writeByte(12, 1);
        memory.write(0, x, 4, 0, 3);
        x = new long[]{0x24, 0xFE77, 0xABC0AA42L};
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x24, 0x00, 0x00, (byte) 0xFE, 0x77, (byte) 0xAB, (byte) 0xC0, (byte) 0xAA, 0x42} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00, 0x00, 0x42, (byte) 0xAA, (byte) 0xC0, (byte) 0xAB};
        byte[] x3 = new byte[12];
        memory.read(0, x3);
        long[] r2 = new long[3];
        memory.read(0, r2, 4, 0, 3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(12));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExLong5() {
        long[] x = new long[]{0x24, 0xFE77, 0xFEABC0AA42L};
        memory.writeByte(15, 1);
        memory.write(0, x, 5, 0, 3);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, (byte) 0xFE, 0x77, (byte) 0xFE, (byte) 0xAB, (byte) 0xC0, (byte) 0xAA, 0x42} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00, 0x00, 0x00, 0x42, (byte) 0xAA, (byte) 0xC0, (byte) 0xAB, (byte) 0xFE};
        byte[] x3 = new byte[15];
        memory.read(0, x3);
        long[] r2 = new long[3];
        memory.read(0, r2, 5, 0, 3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(15));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExLong6() {
        long[] x = new long[]{0x24, 0xFE77, 0xFEABC0AA42L};
        memory.writeByte(18, 1);
        memory.write(0, x, 6, 0, 3);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, (byte) 0xFE, 0x77, 0x00, (byte) 0xFE, (byte) 0xAB, (byte) 0xC0, (byte) 0xAA, 0x42} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00, 0x00, 0x00, 0x00, 0x42, (byte) 0xAA, (byte) 0xC0, (byte) 0xAB, (byte) 0xFE, 0x00};
        byte[] x3 = new byte[18];
        memory.read(0, x3);
        long[] r2 = new long[3];
        memory.read(0, r2, 6, 0, 3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(18));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExLong7() {
        long[] x = new long[]{0x24, 0xFE77, 0xFEABC0AA42L};
        memory.writeByte(21, 1);
        memory.write(0, x, 7, 0, 3);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, (byte) 0xFE, 0x77, 0x00, 0x00, (byte) 0xFE, (byte) 0xAB, (byte) 0xC0, (byte) 0xAA, 0x42} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, (byte) 0xAA, (byte) 0xC0, (byte) 0xAB, (byte) 0xFE, 0x00, 0x00};
        byte[] x3 = new byte[21];
        memory.read(0, x3);
        long[] r2 = new long[3];
        memory.read(0, r2, 7, 0, 3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(21));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExLong8() {
        long[] x = new long[]{0x24, 0xFE77, 0xFEABC0AA42L};
        memory.writeByte(24, 1);
        memory.write(0, x, 8, 0, 3);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, (byte) 0xFE, 0x77, 0x00, 0x00, 0x00, (byte) 0xFE, (byte) 0xAB, (byte) 0xC0, (byte) 0xAA, 0x42} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, (byte) 0xAA, (byte) 0xC0, (byte) 0xAB, (byte) 0xFE, 0x00, 0x00, 0x00};
        byte[] x3 = new byte[24];
        memory.read(0, x3);
        long[] r2 = new long[3];
        memory.read(0, r2, 8, 0, 3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(24));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExLong9() {
        long[] x = new long[]{0x24, 0xFE77, 0xFEABC0AA42L};
        memory.writeByte(27, 1);
        memory.write(0, x, 9, 0, 3);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, (byte) 0xFE, 0x77, 0x00, 0x00, 0x00, 0x00, (byte) 0xFE, (byte) 0xAB, (byte) 0xC0, (byte) 0xAA, 0x42} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, (byte) 0xAA, (byte) 0xC0, (byte) 0xAB, (byte) 0xFE, 0x00, 0x00, 0x00, 0x00};
        byte[] x3 = new byte[27];
        memory.read(0, x3);
        long[] r2 = new long[3];
        memory.read(0, r2, 9, 0, 3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(27));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExLong10() {
        long[] x = new long[]{0x24, 0xFE77, 0xFEABC0AA42L};
        memory.writeByte(30, 1);
        memory.write(0, x, 10, 0, 3);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, (byte) 0xFE, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, (byte) 0xFE, (byte) 0xAB, (byte) 0xC0, (byte) 0xAA, 0x42} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, (byte) 0xAA, (byte) 0xC0, (byte) 0xAB, (byte) 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00};
        byte[] x3 = new byte[30];
        memory.read(0, x3);
        long[] r2 = new long[3];
        memory.read(0, r2, 10, 0, 3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(30));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExShort1() {
        short[] x = new short[]{0x24, (short) 0xFE77};
        memory.writeByte(2, 1);
        memory.write(0, x, 1, 0, 2);
        x = new short[]{0x24, (short) 0x77};
        byte[] x2 = new byte[]{0x24, 0x77};
        byte[] x3 = new byte[2];
        memory.read(0, x3);
        short[] r2 = new short[2];
        memory.read(0, r2, 1, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(2));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExShort2() {
        short[] x = new short[]{0x24, (short) 0xFE77};
        memory.writeByte(4, 1);
        memory.write(0, x, 2, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x24, (byte) 0xFE, 0x77} :
                new byte[]{0x24, 0x00, 0x77, (byte) 0xFE};
        byte[] x3 = new byte[4];
        memory.read(0, x3);
        short[] r2 = new short[2];
        memory.read(0, r2, 2, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(4));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExShort3() {
        short[] x = new short[]{0x24, (short) 0xFE77};
        memory.writeByte(6, 1);
        memory.write(0, x, 3, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x24, 0x00, (byte) 0xFE, 0x77} :
                new byte[]{0x24, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00};
        byte[] x3 = new byte[6];
        memory.read(0, x3);
        short[] r2 = new short[2];
        memory.read(0, r2, 3, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(6));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExShort4() {
        short[] x = new short[]{0x24, (short) 0xFE77};
        memory.writeByte(8, 1);
        memory.write(0, x, 4, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x24, 0x00, 0x00, (byte) 0xFE, 0x77} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00, 0x00};
        byte[] x3 = new byte[8];
        memory.read(0, x3);
        short[] r2 = new short[2];
        memory.read(0, r2, 4, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(8));
        Assert.assertArrayEquals(x2, x3);
    }


    @Test
    public void testExChar1() {
        char[] x = new char[]{0x24, (char) 0xFE77};
        memory.writeByte(2, 1);
        memory.write(0, x, 1, 0, 2);
        x = new char[]{0x24, (char) 0x77};
        byte[] x2 = new byte[]{0x24, 0x77};
        byte[] x3 = new byte[2];
        memory.read(0, x3);
        char[] r2 = new char[2];
        memory.read(0, r2, 1, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(2));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExChar2() {
        char[] x = new char[]{0x24, (char) 0xFE77};
        memory.writeByte(4, 1);
        memory.write(0, x, 2, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x24, (byte) 0xFE, 0x77} :
                new byte[]{0x24, 0x00, 0x77, (byte) 0xFE};
        byte[] x3 = new byte[4];
        memory.read(0, x3);
        char[] r2 = new char[2];
        memory.read(0, r2, 2, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(4));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExChar3() {
        char[] x = new char[]{0x24, (char) 0xFE77};
        memory.writeByte(6, 1);
        memory.write(0, x, 3, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x24, 0x00, (byte) 0xFE, 0x77} :
                new byte[]{0x24, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00};
        byte[] x3 = new byte[6];
        memory.read(0, x3);
        char[] r2 = new char[2];
        memory.read(0, r2, 3, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(6));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExChar4() {
        char[] x = new char[]{0x24, (char) 0xFE77};
        memory.writeByte(8, 1);
        memory.write(0, x, 4, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x00, 0x24, 0x00, 0x00, (byte) 0xFE, 0x77} :
                new byte[]{0x24, 0x00, 0x00, 0x00, 0x77, (byte) 0xFE, 0x00, 0x00};
        byte[] x3 = new byte[8];
        memory.read(0, x3);
        char[] r2 = new char[2];
        memory.read(0, r2, 4, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(8));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testExByte1() {
        byte[] x = new byte[]{0x24, (byte) 0xFE};
        memory.writeByte(2, 1);
        memory.write(0, x, 1, 0, 2);
        byte[] x2 = new byte[]{0x24, (byte) 0xFE};
        byte[] x3 = new byte[2];
        memory.read(0, x3);
        byte[] r2 = new byte[2];
        memory.read(0, r2, 1, 0, 2);
        Assert.assertArrayEquals(x2, x3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(2));
    }

    @Test
    public void testExByte2() {
        byte[] x = new byte[]{0x24, (byte) 0xFE};
        memory.writeByte(4, 1);
        memory.write(0, x, 2, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x24, 0x00, (byte) 0xFE} :
                new byte[]{0x24, 0x00, (byte) 0xFE, 0x00};
        byte[] x3 = new byte[4];
        memory.read(0, x3);
        byte[] r2 = new byte[2];
        memory.read(0, r2, 2, 0, 2);
        Assert.assertArrayEquals(x2, x3);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(4));
    }


    @Test
    public void testExByte3() {
        byte[] x = new byte[]{0x24, (byte) 0xFE};
        memory.writeByte(6, 1);
        memory.write(0, x, 3, 0, 2);
        byte[] x2 = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN ?
                new byte[]{0x00, 0x00, 0x24, 0x00, 0x00, (byte) 0xFE} :
                new byte[]{0x24, 0x00, 0x00, (byte) 0xFE, 0x00, 0x00};
        byte[] x3 = new byte[6];
        memory.read(0, x3);
        byte[] r2 = new byte[2];
        memory.read(0, r2, 3, 0, 2);
        Assert.assertArrayEquals(x, r2);
        Assert.assertEquals(1, memory.read(6));
        Assert.assertArrayEquals(x2, x3);
    }

    @Test
    public void testEndian() {
        memory.zero();
        Random r = new Random();
        r.setSeed(0);
        ByteBuffer buffa = NativeUtils.getJVMUtil().NewDirectByteBuffer(memory.getNativePointer(), memory.size());
        buffa.order(ByteOrder.BIG_ENDIAN);
        for (int i = 0; i < 256; i++) {
            int ri = r.nextInt();
            int rs = r.nextInt() & 0xFFFF;
            long rl = r.nextLong();
            buffa.putInt(0, ri);
            Assert.assertEquals(ri, memory.readIntBE(0));
            Assert.assertEquals(ri & 0xFFFF_FFFFL, memory.readUnsignedIntBE(0));
            buffa.putLong(0, rl);
            Assert.assertEquals(rl, memory.readLongBE(0));
            buffa.putShort(0, (short) rs);
            Assert.assertEquals((short) rs, memory.readShortBE(0));
            Assert.assertEquals(rs, memory.readUnsignedShortBE(0));
        }

        memory.zero();

        buffa.order(ByteOrder.LITTLE_ENDIAN);
        for (int i = 0; i < 256; i++) {
            int ri = r.nextInt();
            int rs = r.nextInt() & 0xFFFF;
            long rl = r.nextLong();
            buffa.putInt(0, ri);
            Assert.assertEquals(ri, memory.readIntLE(0));
            Assert.assertEquals(ri & 0xFFFF_FFFFL, memory.readUnsignedIntLE(0));
            buffa.putLong(0, rl);
            Assert.assertEquals(rl, memory.readLongLE(0));
            buffa.putShort(0, (short) rs);
            Assert.assertEquals((short) rs, memory.readShortLE(0));
            Assert.assertEquals(rs, memory.readUnsignedShortLE(0));
        }

    }


}

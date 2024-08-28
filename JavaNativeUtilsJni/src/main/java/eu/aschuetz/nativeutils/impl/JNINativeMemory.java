//
// Copyright Alexander Schütz, 2021-2024
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
package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.NativeBuffer;
import eu.aschuetz.nativeutils.api.NativeMemory;
import eu.aschuetz.nativeutils.api.PointerHandler;
import eu.aschuetz.nativeutils.api.StructHelper;

import java.io.SyncFailedException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Objects;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLongFieldUpdater;
import java.util.concurrent.atomic.AtomicReferenceFieldUpdater;
import java.util.concurrent.locks.ReentrantReadWriteLock;

class JNINativeMemory implements NativeMemory {

    private static final AtomicLongFieldUpdater<JNINativeMemory> PTR_UPDATER = AtomicLongFieldUpdater.newUpdater(JNINativeMemory.class, "ptr");
    private volatile long ptr;
    private final long size;
    private final PointerHandler handler;
    private final int hashCode;
    private static final AtomicReferenceFieldUpdater<JNINativeMemory, ByteBuffer> SPIN_GUARD_UPDATER = AtomicReferenceFieldUpdater.newUpdater(JNINativeMemory.class, ByteBuffer.class, "spinGuard");
    private static final ByteBuffer NO_SPIN_GUARD = ByteBuffer.allocateDirect(1);
    static {
        NO_SPIN_GUARD.put(0, (byte) 1);
    }
    private volatile ByteBuffer spinGuard;

    private static final boolean BE = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN;
    private static final boolean LE = ByteOrder.nativeOrder() == ByteOrder.LITTLE_ENDIAN;

    JNINativeMemory(long ptr, long size, PointerHandler handler) {
        this.ptr = ptr;
        this.size = size;
        this.handler = Objects.requireNonNull(handler);
        this.hashCode = (int)(ptr ^ (ptr >>> 32));
    }

    @Override
    public native boolean supportsCompareAndSet16Byte();

    @Override
    public long compareAndSet16ByteAlignment() {
        //only amd64 has this, always 16.
        return 16;
    }

    @Override
    public void close() {
        long optr = PTR_UPDATER.getAndSet(this, 0);

        if (optr == 0) {
            return;
        }

        SPIN_GUARD_UPDATER.compareAndSet(this, null, NO_SPIN_GUARD);
        spinGuard.put(0, (byte) 1);
        handler.handleClose(optr, size);
    }

    @Override
    public void read(long off, NativeMemory dst, long dstOff, long len) {
        if (len == 0) {
            return;
        }
        if (!dst.isValid(dstOff, len)) {
            throw new IllegalArgumentException("dst out of bounds");
        }

        memmove(ptr, off, dst.getNativePointer(dstOff), len);
    }

    @Override
    public void read(long offset, ByteBuffer buffer, int len) {
        if (buffer.isReadOnly()) {
            throw new IllegalArgumentException("Buffer is read only");
        }

        if (len == 0) {
            return;
        }

        if (!buffer.isDirect()) {
            if (!buffer.hasArray()) {
                byte[] tmp = new byte[len];
                read(offset, tmp, 0, len);
                buffer.put(tmp);
                return;
            }

            int pos = buffer.position();
            byte[] buf = buffer.array();
            read(offset, buf, pos, len);
            buffer.position(pos+len);
            return;
        }


        checkOffset(offset, len);
        int pos = buffer.position();
        readBuffer(ptr, offset, buffer, pos, len);
        buffer.position(pos+len);
    }

    @Override
    public void sync(long offset, long length, boolean invalidate) throws SyncFailedException {
        checkOffset(offset, length);
        handler.handleSync(ptr, size, offset, length, invalidate);
    }

    @Override
    public long getNativePointer() {
        return ptr;
    }

    @Override
    public long getNativePointer(long off) {
        if (off < 0 || off >= size) {
            throw new IllegalArgumentException("out of bounds");
        }

        long p = ptr;
        if (p == 0) {
            return 0;
        }

        return off(ptr, off);
    }

    @Override
    public boolean isValid() {
        return ptr != 0;
    }

    @Override
    public boolean isValid(long off) {
        return ptr != 0 && size > off && off >= 0;
    }

    @Override
    public boolean isValid(long off, long len) {
        long l2 = off+len;

        if (len == 0) {
            len++;
        }

        return ptr != 0 && len >= 0 && off >= 0 && size >= l2;
    }

    @Override
    public long size() {
        return this.size;
    }

    @Override
    public long remaining(long off) {
        return Math.max(size-off, 0);
    }


    protected void checkOffset(long offset, long len) {
        if (ptr == 0) {
            throw new NullPointerException();
        }

        if (offset < 0 || len < 0 || offset >= size || offset+len > size) {
            throw new IllegalArgumentException("out of bounds");
        }
    }

    protected void initSpinGuard() {
        if (spinGuard != null) {
            return;
        }

        if (ptr == 0) {
            throw new NullPointerException();
        }

        SPIN_GUARD_UPDATER.compareAndSet(this, null, ByteBuffer.allocateDirect(1));
    }


    @Override
    public void set(long offset, byte value, long len) {
        checkOffset(offset, len);
        set(ptr, offset, value, len);

    }

    @Override
    public void set(long offset, int value, long len) {
        checkOffset(offset, len);
        set(ptr, offset, (byte) value, len);
    }

    @Override
    public void zero() {
        set(0, (byte) 0, size);
    }

    @Override
    public void write(long offset, byte[] buffer, int bufferOffset, int len) {
        if (buffer == null) {
            throw new NullPointerException("buffer");
        }

        if (bufferOffset < 0 || len < 0 || bufferOffset+len > buffer.length) {
            throw new ArrayIndexOutOfBoundsException();
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, len);
        write(ptr, offset, buffer, bufferOffset, len);
    }

    @Override
    public void write(long offset, byte[] buffer) {
       write(offset, buffer, 0, buffer.length);
    }

    @Override
    public void write(long offset, ByteBuffer buffer, int len) {
        if (len == 0) {
            return;
        }

        if (!buffer.isDirect()) {
            if (!buffer.hasArray()) {
                byte[] tmp = new byte[len];
                buffer.get(tmp);
                write(offset, tmp);
                return;
            }

            if (len == 0) {
                return;
            }

            int pos = buffer.position();
            byte[] buf = buffer.array();
            write(offset, buf, pos, len);
            buffer.position(pos+len);
            return;
        }

        checkOffset(offset, len);
        int pos = buffer.position();
        writeBuffer(ptr, offset, buffer, pos, len);
        buffer.position(pos+len);
    }

    @Override
    public void write(long offset, byte[] bytes, int size, int off, int len) {
        if (size <= 0) {
            throw new IllegalArgumentException("size");
        }

        if (len < 0 || off < 0 || off+len > bytes.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (size == 1) {
            write(offset, bytes, off, len);
            return;
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, ((long)len)*size);
        writeExpandedByteArray(ptr, offset, bytes, size, off, len);
    }

    static native void writeExpandedByteArray(long ptr, long offset, byte[] bytes, int size, int off, int len);

    @Override
    public void read(long offset, byte[] bytes, int size, int off, int len) {
        if (size <= 0) {
            throw new IllegalArgumentException("size");
        }

        if (len < 0 || off < 0 || off+len > bytes.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (size == 1) {
            read(offset, bytes, off, len);
            return;
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, ((long)len)*size);
        readExpandedByteArray(ptr, offset, bytes, size, off, len);
    }

    static native void readExpandedByteArray(long ptr, long offset, byte[] bytes, int size, int off, int len);


    @Override
    public void write(long offset, char[] chars, int size, int off, int len) {
        if (size <= 0) {
            throw new IllegalArgumentException("size");
        }

        if (len < 0 || off < 0 || off+len > chars.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, ((long)len)*size);
        writeExpandedCharArray(ptr, offset, chars, size, off, len);
    }

    static native void writeExpandedCharArray(long ptr, long offset, char[] chars, int size, int off, int len);
    @Override
    public void read(long offset, char[] chars, int size, int off, int len) {
        if (size <= 0) {
            throw new IllegalArgumentException("size");
        }

        if (len < 0 || off < 0 || off+len > chars.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, ((long)len)*size);
        readExpandedCharArray(ptr, offset, chars, size, off, len);
    }

    static native void readExpandedCharArray(long ptr, long offset, char[] chars, int size, int off, int len);

    @Override
    public void write(long offset, short[] shorts, int size, int off, int len) {
        if (size <= 0) {
            throw new IllegalArgumentException("size");
        }

        if (len < 0 || off < 0 || off+len > shorts.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, ((long)len)*size);
        writeExpandedShortArray(ptr, offset, shorts, size, off, len);
    }


    static native void writeExpandedShortArray(long ptr, long offset, short[] chars, int size, int off, int len);
    @Override
    public void read(long offset, short[] shorts, int size, int off, int len) {
        if (size <= 0) {
            throw new IllegalArgumentException("size");
        }

        if (len < 0 || off < 0 || off+len > shorts.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, ((long)len)*size);
        readExpandedShortArray(ptr, offset, shorts, size, off, len);
    }

    static native void readExpandedShortArray(long ptr, long offset, short[] chars, int size, int off, int len);

    @Override
    public void write(long offset, int[] ints, int size, int off, int len) {
        if (size <= 0) {
            throw new IllegalArgumentException("size");
        }

        if (len < 0 || off < 0 || off+len > ints.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, ((long)len)*size);
        writeExpandedIntArray(ptr, offset, ints, size, off, len);
    }

    static native void writeExpandedIntArray(long ptr, long offset, int[] ints, int size, int off, int len);

    @Override
    public void read(long offset, int[] ints, int size, int off, int len) {
        if (size <= 0) {
            throw new IllegalArgumentException("size");
        }

        if (len < 0 || off < 0 || off+len > ints.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, ((long)len)*size);
        readExpandedIntArray(ptr, offset, ints, size, off, len);
    }

    static native void readExpandedIntArray(long ptr, long offset, int[] ints, int size, int off, int len);

    @Override
    public void write(long offset, long[] longs, int size, int off, int len) {
        if (size <= 0) {
            throw new IllegalArgumentException("size");
        }

        if (len < 0 || off < 0 || off+len > longs.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, ((long)len)*size);
        writeExpandedLongArray(ptr, offset, longs, size, off, len);
    }

    static native void writeExpandedLongArray(long ptr, long offset, long[] ints, int size, int off, int len);
    @Override
    public void read(long offset, long[] longs, int size, int off, int len) {
        if (size <= 0) {
            throw new IllegalArgumentException("size");
        }

        if (len < 0 || off < 0 || off+len > longs.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, ((long)len)*size);
        readExpandedLongArray(ptr, offset, longs, size, off, len);
    }

    static native void readExpandedLongArray(long ptr, long offset, long[] ints, int size, int off, int len);

    @Override
    public void write(long offset, float[] floats, int off, int len) {
        if (len < 0 || off < 0 || off+len > floats.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, (len * 4L));
        writeFloatArray(ptr, offset, floats, off, len);
    }

    static native void writeFloatArray(long ptr, long offset, float[] floats, int off, int len);

    @Override
    public void read(long offset, float[] floats, int off, int len) {
        if (len < 0 || off < 0 || off+len > floats.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, (len * 4L));
        readFloatArray(ptr, offset, floats, off, len);
    }

    static native void readFloatArray(long ptr, long offset, float[] floats, int off, int len);

    @Override
    public void write(long offset, double[] doubles, int off, int len) {
        if (len < 0 || off < 0 || off+len > doubles.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, (len * 8L));
        writeDoubleArray(ptr, offset, doubles, off, len);
    }

    static native void writeDoubleArray(long ptr, long offset, double[] doubles, int off, int len);

    @Override
    public void read(long offset, double[] doubles, int off, int len) {
        if (len < 0 || off < 0 || off+len > doubles.length) {
            throw new IllegalArgumentException("offsets");
        }

        if (len == 0) {
            return;
        }

        checkOffset(offset, (len * 8L));
        readDoubleArray(ptr, offset, doubles, off, len);
    }

    static native void readDoubleArray(long ptr, long offset, double[] doubles, int off, int len);


    @Override
    public void write(long offset, byte aByte) {
        checkOffset(offset, 1);
        write(ptr, offset, aByte);
    }

    @Override
    public void writeByte(long offset, byte aByte) {
        write(offset, aByte);
    }

    @Override
    public void writeByte(long offset, int aByte) {
        writeByte(offset, (byte) aByte);
    }

    @Override
    public void writePointer(long offset, long ptr) {
        if (JNICommonNativeUtil._getPointerSize() == 4) {
            write(offset, (int) ptr);
            return;
        }

        write(offset, ptr);
    }

    @Override
    public void write(long offset, int aInt) {
        checkOffset(offset, 4);
        write(ptr, offset, aInt);
    }

    @Override
    public void writeInt(long offset, int aInt) {
        write(offset, aInt);
    }

    @Override
    public void writeIntBE(long offset, int aInt) {
        if (BE) {
            writeInt(offset, aInt);
            return;
        }

        writeInt(offset, StructHelper.byteSwapInt(aInt));
    }

    @Override
    public void writeIntLE(long offset, int aInt) {
        if (LE) {
            writeInt(offset, aInt);
            return;
        }

        writeInt(offset, StructHelper.byteSwapInt(aInt));
    }

    @Override
    public void write(long offset, long aLong) {
        checkOffset(offset, 8);
        write(ptr, offset, aLong);
    }

    @Override
    public void writeLong(long offset, long aLong) {
        write(offset, aLong);
    }

    @Override
    public void writeLongBE(long offset, long aLong) {
        if (BE) {
            writeLong(offset, aLong);
            return;
        }

        writeLong(offset, StructHelper.byteSwapLong(aLong));
    }

    @Override
    public void writeLongLE(long offset, long aLong) {
        if (LE) {
            writeLong(offset, aLong);
            return;
        }

        writeLong(offset, StructHelper.byteSwapLong(aLong));
    }

    @Override
    public void write(long offset, float aFloat) {
        checkOffset(offset, 4);
        write(ptr, offset, aFloat);
    }

    @Override
    public void writeFloat(long offset, float aFloat) {
        write(offset, aFloat);
    }

    @Override
    public void write(long offset, double aDouble) {
        checkOffset(offset, 8);
        write(ptr, offset, aDouble);
    }

    @Override
    public void writeDouble(long offset, double aDouble) {
        write(offset, aDouble);
    }

    @Override
    public void write(long offset, short aShort) {
        checkOffset(offset, 2);
        write(ptr, offset, aShort);
    }

    @Override
    public void writeShort(long offset, short aShort) {
        write(offset, aShort);
    }

    @Override
    public void writeShort(long offset, int aShort) {
        write(offset, (short) aShort);
    }

    @Override
    public void writeShortBE(long offset, int aShort) {
        if (BE) {
            writeShort(offset, aShort);
            return;
        }

        writeShort(offset, StructHelper.byteSwapUShort(aShort));
    }

    @Override
    public void writeShortLE(long offset, int aShort) {
        if (LE) {
            writeShort(offset, aShort);
            return;
        }

        writeShort(offset, StructHelper.byteSwapUShort(aShort));
    }

    @Override
    public void writeShortBE(long offset, short aShort) {
        if (BE) {
            writeShort(offset, aShort);
            return;
        }

        writeShort(offset, StructHelper.byteSwapShort(aShort));
    }

    @Override
    public void writeShortLE(long offset, short aShort) {
        if (LE) {
            writeShort(offset, aShort);
            return;
        }

        writeShort(offset, StructHelper.byteSwapShort(aShort));
    }

    @Override
    public void read(long offset, byte[] buffer, int bufferOffset, int len) {
        if (buffer == null) {
            throw new NullPointerException();
        }

        if (bufferOffset < 0 || len < 0 || bufferOffset+len > buffer.length) {
            throw new IndexOutOfBoundsException();
        }
        if (len == 0) {
            return;
        }


        checkOffset(offset, len);
        read(ptr, offset, buffer, bufferOffset, len);
    }

    @Override
    public void read(long offset, byte[] buffer) {
        read(offset, buffer, 0, buffer.length);
    }

    @Override
    public int readInt(long offset) {
        checkOffset(offset, 4);
        return readInt(ptr, offset);
    }

    @Override
    public int readIntBE(long offset) {
        if (BE) {
            return readInt(offset);
        }


        return StructHelper.byteSwapInt(readInt(offset));
    }

    @Override
    public int readIntLE(long offset) {
        if (LE) {
            return readInt(offset);
        }

        return StructHelper.byteSwapInt(readInt(offset));
    }

    @Override
    public long readUnsignedInt(long offset) {
        return ((long)readInt(offset)) & 0xffffffffL;
    }

    @Override
    public long readUnsignedIntBE(long offset) {
        if (BE) {
            return readUnsignedInt(offset);
        }


        return StructHelper.byteSwapUInt(readUnsignedInt(offset));
    }

    @Override
    public long readUnsignedIntLE(long offset) {
        if (LE) {
            return readUnsignedInt(offset);
        }


        return StructHelper.byteSwapUInt(readUnsignedInt(offset));
    }

    @Override
    public long readLong(long offset) {
        checkOffset(offset, 8);
        return readLong(ptr, offset);
    }

    @Override
    public long readLongBE(long offset) {
        if (BE) {
            return readLong(offset);
        }


        return StructHelper.byteSwapLong(readLong(offset));
    }

    @Override
    public long readLongLE(long offset) {
        if (LE) {
            return readLong(offset);
        }


        return StructHelper.byteSwapLong(readLong(offset));
    }

    @Override
    public long readPointer(long offset) {
        if (JNICommonNativeUtil._getPointerSize() == 4) {
            return readInt(offset);
        }

        return readLong(offset);
    }

    @Override
    public float readFloat(long offset) {
        checkOffset(offset, 4);
        return readFloat(ptr, offset);
    }

    @Override
    public double readDouble(long offset) {
        checkOffset(offset, 8);
        return readDouble(ptr, offset);
    }

    @Override
    public short readShort(long offset) {
        checkOffset(offset, 2);
        return readShort(ptr, offset);
    }

    @Override
    public short readShortBE(long offset) {
        if (BE) {
            return readShort(offset);
        }


        return StructHelper.byteSwapShort(readShort(offset));
    }

    @Override
    public short readShortLE(long offset) {
        if (LE) {
            return readShort(offset);
        }


        return StructHelper.byteSwapShort(readShort(offset));
    }

    @Override
    public int readUnsignedShort(long offset) {
        return readShort(offset) & 0xffff;
    }

    @Override
    public int readUnsignedShortBE(long offset) {
        if (BE) {
            return readUnsignedShort(offset);
        }


        return StructHelper.byteSwapUShort(readUnsignedShort(offset));
    }

    @Override
    public int readUnsignedShortLE(long offset) {
        if (LE) {
            return readUnsignedShort(offset);
        }


        return StructHelper.byteSwapUShort(readUnsignedShort(offset));
    }

    @Override
    public byte read(long offset) {
        checkOffset(offset, 1);
        return readByte(ptr, offset);
    }

    @Override
    public int readUnsignedByte(long offset) {
        return read(offset) & 0xff;
    }



    @Override
    public long getAndAdd(long offset, long aLong) {
        checkOffset(offset, 8);
        return getAndAdd(ptr, offset, aLong);
    }

    @Override
    public long getAndAddLong(long offset, long aLong) {
        return getAndAdd(offset, aLong);
    }

    @Override
    public int getAndAdd(long offset, int aInt) {
        checkOffset(offset, 4);
        return getAndAdd(ptr, offset, aInt);
    }

    @Override
    public int getAndAddInt(long offset, int aInt) {
        return getAndAdd(offset, aInt);
    }

    @Override
    public short getAndAdd(long offset, short aShort) {
        checkOffset(offset, 2);
        return getAndAdd(ptr, offset, aShort);
    }

    @Override
    public short getAndAddShort(long offset, short aShort) {
        return getAndAdd(offset, aShort);
    }

    @Override
    public byte getAndAdd(long offset, byte aByte) {
        checkOffset(offset, 1);
        return getAndAdd(ptr, offset, aByte);
    }

    @Override
    public byte getAndAddByte(long offset, byte aByte) {
        return getAndAdd(offset, aByte);
    }

    @Override
    public long getAndSet(long offset, long aLong) {
        checkOffset(offset, 8);
        return getAndSet(ptr, offset, aLong);
    }

    @Override
    public long getAndSetLong(long offset, long aLong) {
        return getAndSet(offset, aLong);
    }

    @Override
    public int getAndSet(long offset, int aInt) {
        checkOffset(offset, 4);
        return getAndSet(ptr, offset, aInt);
    }

    @Override
    public int getAndSetInt(long offset, int aInt) {
        return getAndSet(offset, aInt);
    }

    @Override
    public short getAndSet(long offset, short aShort) {
        checkOffset(offset, 2);
        return getAndSet(ptr, offset, aShort);
    }

    @Override
    public short getAndSetShort(long offset, short aShort) {
        return getAndSet(offset, aShort);
    }

    @Override
    public byte getAndSet(long offset, byte aByte) {
        checkOffset(offset, 1);
        return getAndSet(ptr, offset, aByte);
    }

    @Override
    public byte getAndSetByte(long offset, byte aByte) {
        return getAndSet(offset, aByte);
    }

    @Override
    public boolean compareAndSet(long offset, long expect, long update) {
        checkOffset(offset, 8);
        return compareAndSet(ptr, offset, expect, update);
    }

    @Override
    public boolean compareAndSetLong(long offset, long expect, long update) {
        return compareAndSet(offset, expect, update);
    }

    @Override
    public native boolean supportsCompareAndSet8Byte();

    @Override
    public native long compareAndSet8ByteAlignment();

    @Override
    public boolean compareAndSet(long offset, int expect, int update) {
        checkOffset(offset, 4);
        return compareAndSet(ptr, offset, expect, update);

    }

    @Override
    public boolean compareAndSetInt(long offset, int expect, int update) {
        return compareAndSet(offset, expect, update);
    }

    @Override
    public native boolean supportsCompareAndSet4Byte();

    @Override
    public native long compareAndSet4ByteAlignment();

    @Override
    public boolean compareAndSet(long offset, short expect, short update) {
        checkOffset(offset, 2);
        return compareAndSet(ptr, offset, expect, update);
    }

    @Override
    public boolean compareAndSetShort(long offset, short expect, short update) {
        return compareAndSet(offset, expect, update);
    }

    @Override
    public native boolean supportsCompareAndSet2Byte();

    @Override
    public native long compareAndSet2ByteAlignment();

    @Override
    public boolean compareAndSet(long offset, byte expect, byte update) {
        checkOffset(offset, 1);
        return compareAndSet(ptr, offset, expect, update);
    }

    @Override
    public boolean compareAndSetByte(long offset, byte expect, byte update) {
        return compareAndSet(offset, expect, update);
    }

    @Override
    public native boolean supportsCompareAndSet1Byte();

    @Override
    public native long compareAndSet1ByteAlignment();

    @Override
    public void stopSpin() {
        SPIN_GUARD_UPDATER.compareAndSet(this, null, NO_SPIN_GUARD);
        spinGuard.put(0, (byte) 1);
    }

    @Override
    public boolean spinAndSet(long offset, long expect, long update, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        checkOffset(offset, 8);
        initSpinGuard();
        return spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout), spinGuard);
    }


    @Override
    public boolean spinAndSet(long offset, int expect, int update, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        checkOffset(offset, 4);
        initSpinGuard();
        return spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout), spinGuard);
    }

    @Override
    public boolean spinAndSet(long offset, short expect, short update, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        checkOffset(offset, 2);
        initSpinGuard();
        return spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout), spinGuard);
    }

    @Override
    public boolean spinAndSet(long offset, byte expect, byte update, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        checkOffset(offset, 1);
        initSpinGuard();
        return spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout), spinGuard);
    }

    @Override
    public void spinAndSet(long offset, long expect, long update, long aSpinTime, TimeUnit aUnit) {
        checkOffset(offset, 8);
        initSpinGuard();
        spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), spinGuard);
    }


    @Override
    public void spinAndSet(long offset, int expect, int update, long aSpinTime, TimeUnit aUnit) {
        checkOffset(offset, 4);
        initSpinGuard();
        spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), spinGuard);
    }

    @Override
    public void spinAndSet(long offset, short expect, short update, long aSpinTime, TimeUnit aUnit) {
        checkOffset(offset, 2);
        initSpinGuard();
        spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), spinGuard);
    }

    @Override
    public void spinAndSet(long offset, byte expect, byte update, long aSpinTime, TimeUnit aUnit) {
        checkOffset(offset, 1);
        initSpinGuard();
        spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), spinGuard);
    }

    @Override
    public boolean spin(long offset, long expect, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        checkOffset(offset, 8);
        initSpinGuard();
        return spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout), spinGuard);
    }




    @Override
    public boolean spin(long offset, int expect, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        checkOffset(offset, 4);
        return spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout), spinGuard);
    }

    @Override
    public boolean spin(long offset, short expect, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        checkOffset(offset, 2);
        return spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout), spinGuard);
    }

    @Override
    public boolean spin(long offset, byte expect, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        checkOffset(offset, 1);
        return spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout), spinGuard);
    }

    @Override
    public void spin(long offset, long expect, long aSpinTime, TimeUnit aUnit) {
        checkOffset(offset, 8);
        initSpinGuard();
        spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), spinGuard);
    }


    @Override
    public void spin(long offset, int expect, long aSpinTime, TimeUnit aUnit) {
        checkOffset(offset, 8);
        initSpinGuard();
        spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), spinGuard);
    }

    @Override
    public void spin(long offset, short expect, long aSpinTime, TimeUnit aUnit) {
        checkOffset(offset, 8);
        initSpinGuard();
        spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), spinGuard);
    }

    @Override
    public void spin(long offset, byte expect, long aSpinTime, TimeUnit aUnit) {
        checkOffset(offset, 8);
        initSpinGuard();
        spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), spinGuard);
    }

    @Override
    public boolean compareAndSet(long offset, byte[] data) {
        if (data == null) {
            throw new NullPointerException();
        }

        if (data.length != 32) {
            throw new IllegalArgumentException(data.length + " != 32 (array length)");
        }

        checkOffset(offset, 16);
        return compareAndSet(ptr, offset, data);
    }

    @Override
    public long indexOf(long offset, byte value) {
        checkOffset(offset, 1);
        return indexOf(ptr, offset, remaining(offset), value);
    }

    @Override
    public int readUntilByte(long offset, byte value, byte[] buffer, int off, int len) {
        if (len < 0 || off < 0) {
            throw new IllegalArgumentException("buffer offset");
        }

        if (ptr == 0) {
            throw new NullPointerException();
        }

        if (len == 0) {
            return 0;
        }

        if (offset < 0) {
            throw new IllegalArgumentException("out of bounds");
        }

        int max = (int) Math.min(remaining(offset), len);
        if (max == 0) {
            return 0;
        }
        return readUntilByte(ptr, offset, max, value, buffer, off);
    }

    @Override
    public NativeBuffer stream() {
        return new MemoryNativeBuffer(this, 0);
    }

    @Override
    public NativeBuffer stream(long offset) {
        if (isValid(offset)) {
            throw new IndexOutOfBoundsException(""+offset);
        }
        return new MemoryNativeBuffer(this, offset);
    }

    static native int readUntilByte(long ptr, long offset, int max, byte value, byte[] buffer, int off);

    static native long indexOf(long ptr, long offset, long max, byte value);

    //NATIVE STUFF
    static native long off(long ptr, long offset);

    /*
     * Read/Write
     */

    static native void write(long ptr, long offset, byte[] buffer, int bufferOffset, int len);

    static native void write(long ptr, long offset, byte aByte);

    static native void write(long ptr, long offset, int aInt);

    static native void write(long ptr, long offset, long aLong);

    static native void write(long ptr, long offset, float aFloat);

    static native void write(long ptr, long offset, double aDouble);

    static native void write(long ptr, long offset, short aShort);

    static native void read(long ptr, long offset, byte[] buffer, int bufferOffset, int len);

    static native int readInt(long ptr, long offset);

    static native long readLong(long ptr, long offset);

    static native float readFloat(long ptr, long offset);

    static native double readDouble(long ptr, long offset);

    static native short readShort(long ptr, long offset);

    static native byte readByte(long ptr, long offset);

    static native void set(long ptr, long offset, byte value, long len);

    /*
     * Atomics
     */
    static native long getAndAdd(long ptr, long offset, long aLong);

    static native int getAndAdd(long ptr, long offset, int aInt);

    static native short getAndAdd(long ptr, long offset, short aShort);

    static native byte getAndAdd(long ptr, long offset, byte aByte);

    static native long getAndSet(long ptr, long offset, long aLong);

    static native int getAndSet(long ptr, long offset, int aInt);

    static native short getAndSet(long ptr, long offset, short aShort);

    static native byte getAndSet(long ptr, long offset, byte aByte);

    static native boolean compareAndSet(long ptr, long offset, long expect, long update);

    static native boolean compareAndSet(long ptr, long offset, int expect, int update);

    static native boolean compareAndSet(long ptr, long offset, short expect, short update);

    static native boolean compareAndSet(long ptr, long offset, byte expect, byte update);

    /*
     * data has to be 32 bytes long and first 16 bytes is expect next 16 bytes is update.
     */
    static native boolean compareAndSet(long ptr, long offset, byte[] data);

    native boolean spinAndSet(long ptr, long offset, long expect, long update, long aSpinTime, long aTimeout, ByteBuffer spinGuard);
    native void spinAndSet(long ptr, long offset, long expect, long update, long aSpinTime, ByteBuffer spinGuard);
    native boolean spin(long ptr, long offset, long expect, long aSpinTime, long aTimeout, ByteBuffer spinGuard);
    native void spin(long ptr, long offset, long expect, long aSpinTime, ByteBuffer spinGuard);

    native boolean spinAndSet(long ptr, long offset, int expect, int update, long aSpinTime, long aTimeout, ByteBuffer spinGuard);
    native void spinAndSet(long ptr, long offset, int expect, int update, long aSpinTime, ByteBuffer spinGuard);
    native boolean spin(long ptr, long offset, int expect, long aSpinTime, long aTimeout, ByteBuffer spinGuard);
    native void spin(long ptr, long offset, int expect, long aSpinTime, ByteBuffer spinGuard);

    native boolean spinAndSet(long ptr, long offset, short expect, short update, long aSpinTime, long aTimeout, ByteBuffer spinGuard);
    native void spinAndSet(long ptr, long offset, short expect, short update, long aSpinTime, ByteBuffer spinGuard);
    native boolean spin(long ptr, long offset, short expect, long aSpinTime, long aTimeout, ByteBuffer spinGuard);
    native void spin(long ptr, long offset, short expect, long aSpinTime, ByteBuffer spinGuard);

    native boolean spinAndSet(long ptr, long offset, byte expect, byte update, long aSpinTime, long aTimeout, ByteBuffer spinGuard);
    native void spinAndSet(long ptr, long offset, byte expect, byte update, long aSpinTime, ByteBuffer spinGuard);
    native boolean spin(long ptr, long offset, byte expect, long aSpinTime, long aTimeout, ByteBuffer spinGuard);
    native void spin(long ptr, long offset, byte expect, long aSpinTime, ByteBuffer spinGuard);

    static native void memmove(long ptr, long offset, long target, long len);
    static native void readBuffer(long ptr, long offset, ByteBuffer buffer, int off, int len);
    static native void writeBuffer(long ptr, long offset, ByteBuffer buffer, int off, int len);


    @Override
    public String toString() {
        long ptr = this.ptr;
        if (ptr == 0) {
            return "INVALID";
        }
        return "0x" + Long.toHexString(ptr)  + " - 0x" + Long.toHexString(ptr+size);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }

        JNINativeMemory that = (JNINativeMemory) o;
        return ptr == that.ptr && hashCode == that.hashCode;
    }

    @Override
    public int hashCode() {
        return hashCode;
    }
}

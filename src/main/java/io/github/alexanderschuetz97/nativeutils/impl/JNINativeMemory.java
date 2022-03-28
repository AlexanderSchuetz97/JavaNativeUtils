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
package io.github.alexanderschuetz97.nativeutils.impl;

import io.github.alexanderschuetz97.nativeutils.api.NativeMemory;
import io.github.alexanderschuetz97.nativeutils.api.PointerHandler;

import java.io.SyncFailedException;
import java.util.Objects;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantReadWriteLock;

class JNINativeMemory implements NativeMemory {

    private final boolean read;
    private final boolean write;
    private volatile long ptr;
    private final long size;
    private final PointerHandler handler;

    private final ReentrantReadWriteLock rwl = new ReentrantReadWriteLock();
    private final ReentrantReadWriteLock.ReadLock rLock = rwl.readLock();
    private final ReentrantReadWriteLock.WriteLock wLock = rwl.writeLock();

    JNINativeMemory(long ptr, long size, boolean read, boolean write, PointerHandler handler) {
        this.ptr = ptr;
        this.size = size;
        this.read = read;
        this.write = write;
        this.handler = Objects.requireNonNull(handler);
    }



    @Override
    public native boolean atomic8ByteOperationsRequireAlignment();

    @Override
    public void close() {
        long optr = ptr;
        ptr = 0;
        if (optr == 0) {
            return;
        }

        wLock.lock();
        try {
            handler.handleClose(optr, size, read, write);
        } finally {
            wLock.unlock();
        }
    }

    public void sync(long offset, long length, boolean invalidate) throws SyncFailedException {
        lockForWrite(offset, length);
        try {
            handler.handleSync(ptr, size, read, write, offset, length, invalidate);
        } finally {
            rLock.unlock();
        }

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

        return off(ptr, off);
    }

    @Override
    public ReentrantReadWriteLock.ReadLock readLock() {
        return this.rLock;
    }

    @Override
    public ReentrantReadWriteLock.WriteLock writeLock() {
        return this.wLock;
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
    public boolean isReadable() {
        return read;
    }

    @Override
    public boolean isWriteable() {
        return write;
    }

    @Override
    public long size() {
        return this.size;
    }


    protected void lockForWrite(long offset, long len) {
        if (!write) {
            throw new UnsupportedOperationException("memory does not support writing");
        }

        if (ptr == 0) {
            throw new NullPointerException();
        }

        if (offset < 0 || len < 0 || offset >= size || offset+len > size) {
            throw new IllegalArgumentException("out of bounds");
        }

        rLock.lock();
    }

    protected void lockForRead(long offset, long len) {
        //C checks it again, this is intentionally left before the call to lock.
        if (ptr == 0) {
            throw new NullPointerException();
        }

        if (!read) {
            throw new UnsupportedOperationException("memory does not support reading");
        }

        if (offset < 0 || len <= 0 || offset+len > size) {
            throw new IllegalArgumentException("out of bounds");
        }

        rLock.lock();
    }

    protected void lockForReadWrite(long offset, long len) {
        //C checks it again, this is intentionally left before the call to lock.
        if (ptr == 0) {
            throw new NullPointerException();
        }

        if (!write) {
            throw new UnsupportedOperationException("memory does not support writing");
        }

        if (!read) {
            throw new UnsupportedOperationException("memory does not support reading");
        }

        if (offset < 0 || len <= 0 || offset >= size || offset+len > size) {
            throw new IllegalArgumentException("out of bounds");
        }

        rLock.lock();
    }


    @Override
    public void set(long offset, byte value, long len) {
        lockForWrite(offset, len);
        try {
            set(ptr, offset, value, len);
        } finally {
            rLock.unlock();
        }
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

        lockForWrite(offset, len);
        try {
            write(ptr, offset, buffer, bufferOffset, len);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void write(long offset, byte[] buffer) {
       write(offset, buffer, 0, buffer.length);
    }

    @Override
    public void write(long offset, byte aByte) {
        lockForWrite(offset, 1);
        try {
            write(ptr, offset, aByte);
        } finally {
            rLock.unlock();
        }
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
        lockForWrite(offset, 4);
        try {
            write(ptr, offset, aInt);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void write(long offset, long aLong) {
        lockForWrite(offset, 8);
        try {
            write(ptr, offset, aLong);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void write(long offset, float aFloat) {
        lockForWrite(offset, 4);
        try {
            write(ptr, offset, aFloat);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void write(long offset, double aDouble) {
        lockForWrite(offset, 8);
        try {
            write(ptr, offset, aDouble);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void write(long offset, short aShort) {
        lockForWrite(offset, 2);
        try {
            write(ptr, offset, aShort);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void read(long offset, byte[] buffer, int bufferOffset, int len) {
        if (buffer == null) {
            throw new NullPointerException();
        }

        if (bufferOffset < 0 || len < 0 || bufferOffset+len > buffer.length) {
            throw new ArrayIndexOutOfBoundsException();
        }
        if (len == 0) {
            return;
        }


        lockForRead(offset, len);
        try {
            read(ptr, offset, buffer, bufferOffset, len);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public int readInt(long offset) {
        lockForRead(offset, 4);
        try {
            return readInt(ptr, offset);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public long readUnsignedInt(long offset) {
        return ((long)readInt(offset)) & 0xffffffffL;
    }

    @Override
    public long readLong(long offset) {
        lockForRead(offset, 8);
        try {
            return readLong(ptr, offset);
        } finally {
            rLock.unlock();
        }
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
        lockForRead(offset, 4);
        try {
            return readFloat(ptr, offset);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public double readDouble(long offset) {
        lockForRead(offset, 8);
        try {
            return readDouble(ptr, offset);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public short readShort(long offset) {
        lockForRead(offset, 2);
        try {
            return readShort(ptr, offset);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public int readUnsignedShort(long offset) {
        return readShort(offset) & 0xffff;
    }

    @Override
    public byte read(long offset) {
        lockForRead(offset, 1);
        try {
            return readByte(ptr, offset);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public int readUnsignedByte(long offset) {
        return read(offset) & 0xff;
    }

    @Override
    public native boolean supportsAtomicOperations();

    @Override
    public native boolean supports16ByteCompareAndSet();

    @Override
    public long getAndAdd(long offset, long aLong) {
        lockForReadWrite(offset, 8);
        try {
            return getAndAdd(ptr, offset, aLong);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public int getAndAdd(long offset, int aInt) {
        lockForReadWrite(offset, 4);
        try {
            return getAndAdd(ptr, offset, aInt);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public short getAndAdd(long offset, short aShort) {
        lockForReadWrite(offset, 2);
        try {
            return getAndAdd(ptr, offset, aShort);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public byte getAndAdd(long offset, byte aByte) {
        lockForReadWrite(offset, 1);
        try {
            return getAndAdd(ptr, offset, aByte);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public long getAndSet(long offset, long aLong) {
        lockForReadWrite(offset, 8);
        try {
            return getAndSet(ptr, offset, aLong);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public int getAndSet(long offset, int aInt) {
        lockForReadWrite(offset, 4);
        try {
            return getAndSet(ptr, offset, aInt);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public short getAndSet(long offset, short aShort) {
        lockForReadWrite(offset, 2);
        try {
            return getAndSet(ptr, offset, aShort);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public byte getAndSet(long offset, byte aByte) {
        lockForReadWrite(offset, 1);
        try {
            return getAndSet(ptr, offset, aByte);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public boolean compareAndSet(long offset, long expect, long update) {
        lockForReadWrite(offset, 8);
        try {
            return compareAndSet(ptr, offset, expect, update);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public boolean compareAndSet(long offset, int expect, int update) {
        lockForReadWrite(offset, 4);
        try {
            return compareAndSet(ptr, offset, expect, update);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public boolean compareAndSet(long offset, short expect, short update) {
        lockForReadWrite(offset, 2);
        try {
            return compareAndSet(ptr, offset, expect, update);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public boolean compareAndSet(long offset, byte expect, byte update) {
        lockForReadWrite(offset, 1);
        try {
            return compareAndSet(ptr, offset, expect, update);
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public boolean spinAndSet(long offset, long expect, long update, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        lockForReadWrite(offset, 8);
        try {
            return spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout));
        } finally {
            rLock.unlock();
        }

    }


    @Override
    public boolean spinAndSet(long offset, int expect, int update, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        lockForReadWrite(offset, 4);
        try {
            return spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public boolean spinAndSet(long offset, short expect, short update, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        lockForReadWrite(offset, 2);
        try {
            return spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public boolean spinAndSet(long offset, byte expect, byte update, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        lockForReadWrite(offset, 1);
        try {
            return spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void spinAndSet(long offset, long expect, long update, long aSpinTime, TimeUnit aUnit) {
        lockForReadWrite(offset, 8);
        try {
            spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime));
        } finally {
            rLock.unlock();
        }
    }


    @Override
    public void spinAndSet(long offset, int expect, int update, long aSpinTime, TimeUnit aUnit) {
        lockForReadWrite(offset, 4);
        try {
            spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void spinAndSet(long offset, short expect, short update, long aSpinTime, TimeUnit aUnit) {
        lockForReadWrite(offset, 2);
        try {
            spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void spinAndSet(long offset, byte expect, byte update, long aSpinTime, TimeUnit aUnit) {
        lockForReadWrite(offset, 1);
        try {
            spinAndSet(ptr, offset, expect, update, aUnit.toMillis(aSpinTime));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public boolean spin(long offset, long expect, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        lockForRead(offset, 8);
        try {
            return spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout));
        } finally {
            rLock.unlock();
        }
    }




    @Override
    public boolean spin(long offset, int expect, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        lockForRead(offset, 4);
        try {
            return spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public boolean spin(long offset, short expect, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        lockForRead(offset, 2);
        try {
            return spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public boolean spin(long offset, byte expect, long aSpinTime, long aTimeout, TimeUnit aUnit) {
        lockForRead(offset, 1);
        try {
            return spin(ptr, offset, expect, aUnit.toMillis(aSpinTime), aUnit.toMillis(aTimeout));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void spin(long offset, long expect, long aSpinTime, TimeUnit aUnit) {
        lockForRead(offset, 8);
        try {
            spin(ptr, offset, expect, aUnit.toMillis(aSpinTime));
        } finally {
            rLock.unlock();
        }
    }


    @Override
    public void spin(long offset, int expect, long aSpinTime, TimeUnit aUnit) {
        lockForRead(offset, 8);
        try {
            spin(ptr, offset, expect, aUnit.toMillis(aSpinTime));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void spin(long offset, short expect, long aSpinTime, TimeUnit aUnit) {
        lockForRead(offset, 8);
        try {
            spin(ptr, offset, expect, aUnit.toMillis(aSpinTime));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public void spin(long offset, byte expect, long aSpinTime, TimeUnit aUnit) {
        lockForRead(offset, 8);
        try {
            spin(ptr, offset, expect, aUnit.toMillis(aSpinTime));
        } finally {
            rLock.unlock();
        }
    }

    @Override
    public boolean compareAndSet(long offset, byte[] data) {
        if (data == null) {
            throw new NullPointerException();
        }

        if (data.length != 32) {
            throw new IllegalArgumentException(data.length + " != 32 (array length)");
        }

        lockForReadWrite(offset, 16);
        try {
            return compareAndSet(ptr, offset, data);
        } finally {
            rLock.unlock();
        }
    }

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

    native boolean spinAndSet(long ptr, long offset, long expect, long update, long aSpinTime, long aTimeout);
    native void spinAndSet(long ptr, long offset, long expect, long update, long aSpinTime);
    native boolean spin(long ptr, long offset, long expect, long aSpinTime, long aTimeout);
    native void spin(long ptr, long offset, long expect, long aSpinTime);

    native boolean spinAndSet(long ptr, long offset, int expect, int update, long aSpinTime, long aTimeout);
    native void spinAndSet(long ptr, long offset, int expect, int update, long aSpinTime);
    native boolean spin(long ptr, long offset, int expect, long aSpinTime, long aTimeout);
    native void spin(long ptr, long offset, int expect, long aSpinTime);

    native boolean spinAndSet(long ptr, long offset, short expect, short update, long aSpinTime, long aTimeout);
    native void spinAndSet(long ptr, long offset, short expect, short update, long aSpinTime);
    native boolean spin(long ptr, long offset, short expect, long aSpinTime, long aTimeout);
    native void spin(long ptr, long offset, short expect, long aSpinTime);

    native boolean spinAndSet(long ptr, long offset, byte expect, byte update, long aSpinTime, long aTimeout);
    native void spinAndSet(long ptr, long offset, byte expect, byte update, long aSpinTime);
    native boolean spin(long ptr, long offset, byte expect, long aSpinTime, long aTimeout);
    native void spin(long ptr, long offset, byte expect, long aSpinTime);

    @Override
    public String toString() {
        long ptr = this.ptr;
        if (ptr == 0) {
            return "INVALID";
        }
        return "0x" + Long.toHexString(ptr)  + " - " + Long.toHexString(ptr+size);
    }
}

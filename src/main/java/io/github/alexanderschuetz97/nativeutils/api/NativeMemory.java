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
package io.github.alexanderschuetz97.nativeutils.api;

import java.io.SyncFailedException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Interface for a pointer pointing to a memory region.
 */
public interface NativeMemory extends AutoCloseable {

    /**
     * This is safe to call and will block until all other threads are no longer reading/writing.
     * As soon as its called all other threads will fail with NPE when they will call anything
     * on the memory.
     */
    void close();

    /**
     * Returns true if the close() method of this memory has not yet been called.
     */
    boolean isValid();

    /**
     * Returns true if the close() method of this memory has not yet been called and the memory is valid for the given offset (at least 1 byte can be read/written at the given offset)
     */
    boolean isValid(long off);

    /**
     * Returns true if the close() method of this memory has not yet been called and the memory is valid for the given offset and length
     */
    boolean isValid(long off, long len);

    /**
     * Is the memory marked readable?
     */
    boolean isReadable();

    /**
     * Is the memory marked as writeable?
     */
    boolean isWriteable();

    /**
     * returns the size of this memory.
     */
    long size();

    /**
     * returns the native pointer assosicated with this memory.
     * the returned value is 0 if the close method has been called.
     *
     * Warning: to ensure that the close() method is not called while the pointer is used it is recommended to acquire the readLock or writeLock of this memory while using the native pointer.
     */
    long getNativePointer();

    /**
     * returns the native pointer to the given offset.
     * Warning: to ensure that the close() method is not called while the pointer is used it is recommended to acquire the readLock or writeLock of this memory while using the native pointer.
     */
    long getNativePointer(long off);

    /**
     * Returns the read lock of this native memory object. While the read lock is held calls to "close" will block.
     * This lock will be acquired automatically by any operation (read & write) to prevent async
     * segmentation faults due to other threads calling close. You may wish to manually acquire this lock to perform bulk operations.
     *
     * This lock remains valid even when the memory is closed.
     */
    ReentrantReadWriteLock.ReadLock readLock();

    /**
     * The WriteLock by default is only held when close is called.
     * You may wish to acquire this lock to perform exclusive operations on the memory.
     *
     * This lock remains valid even when the memory is closed.
     * This lock is not fair! Beware of starvation!
     */
    ReentrantReadWriteLock.WriteLock writeLock();

    /**
     * Synchronize the changes made to the memory to the device/file backing the memory.
     * This is a noop for RAM. Depending on the type of mapping, offset and length may be changed internally to align with
     * a size (such as {@link LinuxNativeUtil#getpagesize()}).
     * This change is always guaranteed to contain the entirety of the requested area.
     *
     * @param invalidate if true invalidate other mappings of the same device/file so that they reflect the changes.
     * @throws SyncFailedException if invalidate was true and another mapping has a memory lock on the region to be invalidated.
     */
    void sync(long offset, long length, boolean invalidate) throws SyncFailedException;


    /*
     * Writes len bytes with the given value to the offset.
     */
    void set(long offset, byte value, long len);

    /**
     * writes len bytes starting from the index bufferOffset from the buffer to the offset address in the shared memory.
     */
    void write(long offset, byte[] buffer, int bufferOffset, int len);

    /**
     * writes all bytes from the buffer to the offset address in the shared memory.
     */
    void write(long offset, byte[] buffer);

    /**
     * writes a single byte to the offset address.
     */
    void write(long offset, byte aByte);

    /**
     * writes a pointer value to the given offset.
     *
     * This may be a 64 bit or 32 bit write.
     */
    void writePointer(long offset, long ptr);

    /**
     * writes 4 bytes to the offset address.
     */
    void write(long offset, int aInt);

    /**
     * writes 8 bytes to the offset address.
     */
    void write(long offset, long aLong);

    /**
     * writes 4 bytes to the offset address.
     */
    void write(long offset, float aFloat);

    /**
     * writes 8 bytes to the offset address.
     */
    void write(long offset, double aDouble);

    /**
     * writes 2 bytes to the offset address.
     */
    void write(long offset, short aShort);

    /**
     * reads len bytes from the offset address and stores them into the buffer starting at bufferOffset.
     */
    void read(long offset, byte[] buffer, int bufferOffset, int len);

    /**
     * read 4 bytes from the offset address.
     */
    int readInt(long offset);

    /**
     * read 4 bytes from the offset address.
     * The return value x always satisfies: x >= 0 && x <= 0xFFFFFFFF
     * Note: this is always equivalent to readInt(offset) & 0xFFFFFFFF
     */
    long readUnsignedInt(long offset);

    /**
     * read 8 bytes from the offset address.
     */
    long readLong(long offset);

    /**
     * read a pointer from the given offset. Either a 32 bit or 64 bit read.
     */
    long readPointer(long offset);

    /**
     * read 4 bytes from the offset address.
     */
    float readFloat(long offset);

    /**
     * read 8 bytes from the offset address.
     */
    double readDouble(long offset);

    /**
     * read 2 bytes from the offset address.
     */
    short readShort(long offset);

    /**
     * reads 2 bytes from the offset address and treats them as a unsigned short.
     * Note this is always equivalent to readShort(offset) & 0xFFFF
     */
    int readUnsignedShort(long offset);

    /**
     * read 1 byte from the offset address.
     */
    byte read(long offset);

    /**
     * read 1 byte from the offset address and read it as a unsigned byte.
     * Note this is always equivalent to read(offset) & 0xFF
     */
    int readUnsignedByte(long offset);

    /**
     * returns true if atomic operations are supported.
     * ARM CPU Architecture does not have instructions for atomic operations.
     * AARCH64 Architecture does have "some" of those instructions, but they are not implemented yet...
     *
     * TODO implement AARCH64 CAS
     * Any method below will throw an UnsupportedOperationException if this method returns true.
     */
    boolean supportsAtomicOperations();

    /**
     * adds the parameter to the long at offset. returns the previous value. this operation is atomic.
     *
     * This operations requires offset alignment(offset must be dividable by 8) on i386 (x86 - 32 bit) jvms
     * otherwise an exceptions is thrown.
     */
    long getAndAdd(long offset, long aLong);

    /**
     * adds the parameter to the int at offset. returns the previous value. this operation is atomic.
     */
    int getAndAdd(long offset, int aInt);

    /**
     * adds the parameter to the short at offset. returns the previous value. this operation is atomic.
     */
    short getAndAdd(long offset, short aShort);

    /**
     * adds the parameter to the byte at offset. returns the previous value. this operation is atomic.
     */
    byte getAndAdd(long offset, byte aByte);

    /**
     * sets the value at offset to the given long. returns the previous value. this operation is atomic.
     *
     * This operations requires offset alignment(offset must be dividable by 8) on i386 (x86 - 32 bit) jvms
     * otherwise an exceptions is thrown.
     */
    long getAndSet(long offset, long aLong);

    /**
     * sets the value at offset to the given int. returns the previous value. this operation is atomic.
     */
    int getAndSet(long offset, int aInt);

    /**
     * sets the value at offset to the given short. returns the previous value. this operation is atomic.
     */
    short getAndSet(long offset, short aShort);

    /**
     * sets the value at offset to the given byte. returns the previous value. this operation is atomic.
     */
    byte getAndSet(long offset, byte aByte);

    /*
     * compares the value at offset with expect if equal sets the value at offset to update and returns true otherwise return false.
     * this operation is atomic.
     *
     * This operations requires offset alignment(offset must be dividable by 8) on i386 (x86 - 32 bit) jvms
     * otherwise an exceptions is thrown.
     */
    boolean compareAndSet(long offset, long expect, long update);

    /*
     * compares the value at offset with expect if equal sets the value at offset to update and returns true otherwise return false.
     * this operation is atomic.
     */
    boolean compareAndSet(long offset, int expect, int update);

    /*
     * compares the value at offset with expect if equal sets the value at offset to update and returns true otherwise return false.
     * this operation is atomic.
     */
    boolean compareAndSet(long offset, short expect, short update);

    /*
     * compares the value at offset with expect if equal sets the value at offset to update and returns true otherwise return false.
     * this operation is atomic.
     */
    boolean compareAndSet(long offset, byte expect, byte update);

    /*
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was written false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spinAndSet(long offset, long expect, long update, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /*
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was written false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spinAndSet(long offset, int expect, int update, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /*
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was written false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spinAndSet(long offset, short expect, short update, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /*
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was write false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spinAndSet(long offset, byte expect, byte update, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /*
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was write false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spinAndSet(long offset, long expect, long update, long aSpinTime, TimeUnit aUnit);

    /*
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was write false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spinAndSet(long offset, int expect, int update, long aSpinTime, TimeUnit aUnit);

    /*
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was write false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spinAndSet(long offset, short expect, short update, long aSpinTime, TimeUnit aUnit);

    /*
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was write false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spinAndSet(long offset, byte expect, byte update, long aSpinTime, TimeUnit aUnit);

    /*
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spin(long offset, long expect, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /*
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spin(long offset, int expect, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /*
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spin(long offset, short expect, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /*
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spin(long offset, byte expect, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /*
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spin(long offset, long expect, long aSpinTime, TimeUnit aUnit);

    /*
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spin(long offset, int expect, long aSpinTime, TimeUnit aUnit);

    /*
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spin(long offset, short expect, long aSpinTime, TimeUnit aUnit);

    /*
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spin(long offset, byte expect, long aSpinTime, TimeUnit aUnit);


    /**
     * Is 16 Byte compare and set supported?
     * returns false on anything except amd64 architecture
     *
     */
    boolean supports16ByteCompareAndSet();

    /**
     * Returns true if offset+{@link #getNativePointer()} must be dividable by 4 for all 8 Byte atomic operations.
     */
    boolean atomic8ByteOperationsRequireAlignment();

    /*
     * compares the value of offset with the first 16 bytes of data. if equal write the data at offset to the second 16 bytes of data and return true otherwise return false.
     * this operation is atomic. data must be exactly 32 bytes long. CPU Must support CMPXCHG16B or the JVM will just die (CPU's that can run windows 10 support this).
     *
     * This operation will always throw an exception i386 (x86 - 32 bit) jvms because the cpu instructions set does not support it.
     */
    boolean compareAndSet(long offset, byte[] data);

}

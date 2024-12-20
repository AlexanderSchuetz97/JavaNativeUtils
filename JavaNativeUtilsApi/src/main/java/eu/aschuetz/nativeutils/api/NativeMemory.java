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
package eu.aschuetz.nativeutils.api;

import java.io.SyncFailedException;
import java.nio.ByteBuffer;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Interface for a pointer pointing to a memory region.
 */
public interface NativeMemory extends AutoCloseable {

    /**
     * Closes the memory.
     *
     * Calling this method when other threads are still using the memory will most likely cause use after free and may
     * lead to the application accessing unexpected memory. This may crash the JVM.
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
     * returns the size of this memory.
     */
    long size();

    /**
     * returns the amount of bytes remaining to be read/written to until the end of the memory is reached. This is always greater or equal to 0.
     * @param off must be greater or equal to zero
     */
    long remaining(long off);

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
     *  Writes len bytes with the given value to the offset.
     *  Note: value is treated as if cast to a byte. This means the range of "value" is Byte.MIN_VALUE up to 0xff.
     */
    void set(long offset, int value, long len);

    /**
     * Sets the entire memory to 0.
     */
    void zero();

    /**
     * writes len bytes starting from the index bufferOffset from the buffer to the offset address in the shared memory.
     */
    void write(long offset, byte[] buffer, int bufferOffset, int len);

    /**
     * writes all bytes from the buffer to the offset address in the shared memory.
     */
    void write(long offset, byte[] buffer);

    /**
     * writes len bytes to the offset address from the buffer.
     * The buffers position is incremented by len as a result of this operation.
     */
    void write(long offset, ByteBuffer buffer, int len);

    /**
     * Writes the byte[] to the memory.
     * @param size parameter controls how many bytes are used per index of the array.
     *             size = 1 would just write the byte[] as is
     *             size = 2 would write a '0' byte followed by the byte
     *             size = 3 would write 2 '0' bytes followed by the char
     *             ...
     *
     */
    void write(long offset, byte[] bytes, int size, int off, int len);


    void read(long offset, byte[] bytes, int size, int off, int len);

    /**
     * Writes the char[] to the memory.
     * @param size parameter controls how many bytes are used per index of the array.
     *             size = 1 would first cast each char to a byte.
     *             size = 3 would write a 0 byte followed by the char
     *             size = 4 would write 2 0 bytes followed by the char
     *             ...
     *
     */
    void write(long offset, char[] chars, int size, int off, int len);


    void read(long offset, char[] chars, int size, int off, int len);

    /**
     * Writes the short[] to the memory.
     * @param size parameter controls how many bytes are used per index of the array.
     *             size = 1 would first cast each short to a byte.
     *             size = 3 would write a 0 byte followed by the short
     *             size = 4 would write 2 0 bytes followed by the short
     *             ...
     *
     */
    void write(long offset, short[] shorts, int size, int off, int len);

    void read(long offset, short[] shorts, int size, int off, int len);


    /**
     * Writes the int[] to the memory.
     * @param size parameter controls how many bytes are used per index of the array.
     *             size = 1 would first cast each int to a byte.
     *             ...
     *             size = 3 would write the 24 least significant bits as 3 bytes.
     *             size = 4 would write the int[] as is
     *             ...
     *             size = 5 would prefix each int with a 0 byte
     *      *      ...
     *
     */
    void write(long offset, int[] ints, int size, int off, int len);

    void read(long offset, int[] ints, int size, int off, int len);

    /**
     * Writes the long[] to the memory.
     * @param size parameter controls how many bytes are used per index of the array.
     *             size = 1 would first cast each long to a byte.
     *             ...
     *             size = 3 would write the 24 least significant bits as 3 bytes.
     *             size = 4 would write each long to a int.
     *             ...
     *             size = 9 would prefix each long with a 0 byte
     *      *      ...
     *
     */
    void write(long offset, long[] longs, int size, int off, int len);


    void read(long offset, long[] longs, int size, int off, int len);

    /**
     * Writes the float[] to memory using 4 bytes per float.
     */
    void write(long offset, float[] floats, int off, int len);

    void read(long offset, float[] floats, int off, int len);

    /**
     * Writes the double[] to memory using 8 bytes per float.
     */
    void write(long offset, double[] doubles, int off, int len);


    void read(long offset, double[] doubles, int off, int len);
    /**
     * writes a single byte to the offset address.
     */
    void write(long offset, byte aByte);

    /**
     * writes a single byte to the offset address.
     */
    void writeByte(long offset, byte aByte);

    void writeByte(long offset, int aInt);

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
     * writes 4 bytes to the offset address.
     */
    void writeInt(long offset, int aInt);

    void writeIntBE(long offset, int aInt);

    void writeIntLE(long offset, int aInt);

    /**
     * writes 8 bytes to the offset address.
     */
    void write(long offset, long aLong);

    /**
     * writes 8 bytes to the offset address.
     */
    void writeLong(long offset, long aLong);

    void writeLongBE(long offset, long aLong);

    void writeLongLE(long offset, long aLong);

    /**
     * writes 4 bytes to the offset address.
     */
    void write(long offset, float aFloat);

    /**
     * writes 4 bytes to the offset address.
     */
    void writeFloat(long offset, float aFloat);

    /**
     * writes 8 bytes to the offset address.
     */
    void write(long offset, double aDouble);

    /**
     * writes 8 bytes to the offset address.
     */
    void writeDouble(long offset, double aDouble);

    /**
     * writes 2 bytes to the offset address.
     */
    void write(long offset, short aShort);

    /**
     * writes 2 bytes to the offset address.
     */
    void writeShort(long offset, short aShort);

    /**
     * writes 2 bytes to the offset address.
     * exists for convenience sake, will literally cast the int to short.
     */
    void writeShort(long offset, int aShort);

    void writeShortBE(long offset, int aShort);

    void writeShortLE(long offset, int aShort);

    void writeShortBE(long offset, short aShort);

    void writeShortLE(long offset, short aShort);

    /**
     * reads len bytes from the offset address and stores them into the buffer starting at bufferOffset.
     */
    void read(long offset, byte[] buffer, int bufferOffset, int len);

    /**
     * reads buffer.length bytes from the offset address and stores them into the buffer starting at offset 0.
     */
    void read(long offset, byte[] buffer);

    /**
     * reads len bytes from offset address and stores them into dst.
     * dst may be equal to this memory. This method handles overlap
     * as if the bytes were first copied to temporary buffer before being copied to dst.
     */
    void read(long off, NativeMemory dst, long dstOff, long len);

    /**
     * reads len bytes from the offset address and stores them into the buffer.
     * The buffers position is incremented by len as a result of this operation.
     */
    void read(long offset, ByteBuffer buffer, int len);

    /**
     * read 4 bytes from the offset address.
     */
    int readInt(long offset);

    /**
     * read 4 bytes from the offset address and assume whatever value was read is big endian.
     */
    int readIntBE(long offset);

    /**
     * read 4 bytes from the offset address and assume whatever value was read is big endian.
     */
    int readIntLE(long offset);

    /**
     * read 4 bytes from the offset address.
     * The return value x always satisfies: x >= 0 && x <= 0xFFFFFFFF
     * Note: this is always equivalent to readInt(offset) & 0xFFFFFFFF
     */
    long readUnsignedInt(long offset);

    long readUnsignedIntBE(long offset);

    long readUnsignedIntLE(long offset);

    /**
     * read 8 bytes from the offset address.
     */
    long readLong(long offset);

    long readLongBE(long offset);

    long readLongLE(long offset);

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

    short readShortBE(long offset);

    short readShortLE(long offset);

    /**
     * reads 2 bytes from the offset address and treats them as a unsigned short.
     * Note this is always equivalent to readShort(offset) & 0xFFFF
     */
    int readUnsignedShort(long offset);

    int readUnsignedShortBE(long offset);

    int readUnsignedShortLE(long offset);

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
     * adds the parameter to the long at offset. returns the previous value. this operation is atomic.
     *
     * This operations requires offset alignment(offset must be dividable by 8) on i386 (x86 - 32 bit) jvms
     * otherwise an exceptions is thrown.
     */
    long getAndAdd(long offset, long aLong);

    long getAndAddLong(long offset, long aLong);

    /**
     * adds the parameter to the int at offset. returns the previous value. this operation is atomic.
     */
    int getAndAdd(long offset, int aInt);

    int getAndAddInt(long offset, int aInt);

    /**
     * adds the parameter to the short at offset. returns the previous value. this operation is atomic.
     */
    short getAndAdd(long offset, short aShort);

    short getAndAddShort(long offset, short aShort);

    /**
     * adds the parameter to the byte at offset. returns the previous value. this operation is atomic.
     */
    byte getAndAdd(long offset, byte aByte);

    byte getAndAddByte(long offset, byte aByte);

    /**
     * sets the value at offset to the given long. returns the previous value. this operation is atomic.
     *
     * This operations requires offset alignment(offset must be dividable by 8) on i386 (x86 - 32 bit) jvms
     * otherwise an exceptions is thrown.
     */
    long getAndSet(long offset, long aLong);

    long getAndSetLong(long offset, long aLong);

    /**
     * sets the value at offset to the given int. returns the previous value. this operation is atomic.
     */
    int getAndSet(long offset, int aInt);

    int getAndSetInt(long offset, int aInt);

    /**
     * sets the value at offset to the given short. returns the previous value. this operation is atomic.
     */
    short getAndSet(long offset, short aShort);

    short getAndSetShort(long offset, short aShort);

    /**
     * sets the value at offset to the given byte. returns the previous value. this operation is atomic.
     */
    byte getAndSet(long offset, byte aByte);

    byte getAndSetByte(long offset, byte aByte);

    /**
     * compares the value at offset with expect if equal sets the value at offset to update and returns true otherwise return false.
     * this operation is atomic.
     *
     * This operations requires offset alignment(offset must be dividable by 8) on i386 (x86 - 32 bit) jvms
     * otherwise an exceptions is thrown.
     */
    boolean compareAndSet(long offset, long expect, long update);

    boolean compareAndSetLong(long offset, long expect, long update);

    /**
     * Returns true if the cpu can do 8 byte atomic operations.
     */
    boolean supportsCompareAndSet8Byte();

    /**
     * Returns the amount of alignment needed for addresses to do 8 byte atomic operations on (if supported by cpu)
     */
    long compareAndSet8ByteAlignment();

    /**
     * compares the value at offset with expect if equal sets the value at offset to update and returns true otherwise return false.
     * this operation is atomic.
     */
    boolean compareAndSet(long offset, int expect, int update);

    boolean compareAndSetInt(long offset, int expect, int update);

    /**
     * Returns true if the cpu can do 4 byte atomic operations.
     */
    boolean supportsCompareAndSet4Byte();

    /**
     * Returns the amount of alignment needed for addresses to do 4 byte atomic operations on (if supported by cpu)
     */
    long compareAndSet4ByteAlignment();

    /**
     * compares the value at offset with expect if equal sets the value at offset to update and returns true otherwise return false.
     * this operation is atomic.
     */
    boolean compareAndSet(long offset, short expect, short update);

    boolean compareAndSetShort(long offset, short expect, short update);

    /**
     * Returns the amount of alignment needed for addresses to do 2 byte atomic operations on (if supported by cpu)
     */
    boolean supportsCompareAndSet2Byte();

    /**
     * Returns true if the cpu can do 2 byte atomic operations.
     */
    long compareAndSet2ByteAlignment();

    /**
     * compares the value at offset with expect if equal sets the value at offset to update and returns true otherwise return false.
     * this operation is atomic.
     */
    boolean compareAndSet(long offset, byte expect, byte update);

    boolean compareAndSetByte(long offset, byte expect, byte update);

    /**
     * Returns true if the cpu can do 1 byte atomic operations.
     */
    boolean supportsCompareAndSet1Byte();

    /**
     * Returns the amount of alignment needed for addresses to do 1 byte atomic operations on (if supported by cpu)
     */
    long compareAndSet1ByteAlignment();

    /**
     * Stops/Cancels all java calls that are inside the spin(...) methods. They will all complete exceptionally. further calls to any spin method
     * will always fail immediately.
     * This call only guarantees that threads stuck in spin calls will return eventually.
     * This method returns immediately and does not guarantee that all threads stuck have returned yet.
     */
    void stopSpin();

    /**
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was written false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spinAndSet(long offset, long expect, long update, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /**
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was written false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spinAndSet(long offset, int expect, int update, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /**
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was written false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spinAndSet(long offset, short expect, short update, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /**
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was write false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spinAndSet(long offset, byte expect, byte update, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /**
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was write false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spinAndSet(long offset, long expect, long update, long aSpinTime, TimeUnit aUnit);

    /**
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was write false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spinAndSet(long offset, int expect, int update, long aSpinTime, TimeUnit aUnit);

    /**
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was write false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spinAndSet(long offset, short expect, short update, long aSpinTime, TimeUnit aUnit);

    /**
     * sets the value to update if it ever becomes expect before aTimeout elapses. returns true if the value was write false if the timeout expired.
     * the parameter aSpinTime determines how long the thread should be put to sleep before trying again after a failed attempt.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spinAndSet(long offset, byte expect, byte update, long aSpinTime, TimeUnit aUnit);

    /**
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spin(long offset, long expect, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /**
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spin(long offset, int expect, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /**
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spin(long offset, short expect, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /**
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     * a negative value for aTimeout indicates the method should not timeout and thus never return false.
     */
    boolean spin(long offset, byte expect, long aSpinTime, long aTimeout, TimeUnit aUnit);

    /**
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spin(long offset, long expect, long aSpinTime, TimeUnit aUnit);

    /**
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spin(long offset, int expect, long aSpinTime, TimeUnit aUnit);

    /**
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spin(long offset, short expect, long aSpinTime, TimeUnit aUnit);

    /**
     * returns true if the value at offset becomes expected. After every read the Thread sleeps for aSpinTime.
     * Returns if aTimeout elapsed before the value became expect.
     * a negative value for aSpinTime indicates that the thread shouldn't be put to sleep.
     */
    void spin(long offset, byte expect, long aSpinTime, TimeUnit aUnit);

    boolean supportsCompareAndSet16Byte();

    long compareAndSet16ByteAlignment();

    /*
     * compares the value of offset with the first 16 bytes of data. if equal write the data at offset to the second 16 bytes of data and return true otherwise return false.
     * this operation is atomic. data must be exactly 32 bytes long. CPU Must support CMPXCHG16B or the JVM will just die (CPU's that can run windows 10 support this).
     *
     * This operation will always throw an exception i386 (x86 - 32 bit) jvms because the cpu instructions set does not support it.
     */
    boolean compareAndSet(long offset, byte[] data);

    /**
     * Returns the next offset in the memory that has the given value.
     * the return value is an absolute index meaning it ranges from the given offset up until the maximum valid offset of this memory.
     * returns -1 in case the value is not found anywhere until the end of the memory.
     */
    long indexOf(long offset, byte value);

    /**
     * reads bytes into a buffer until a byte is encountered that is equal to the value parameter.
     * all bytes up until and including the byte equal to value are read into the given buffer.
     * if the end of the memory or buffer is encountered then reading ceases.
     * After reading has ceased the amount of bytes read is returned (this includes the value byte if it was found).
     *
     * Note: each byte is read individually. This ensures that the 'value' byte will never be encountered twice in the resulting buffer.
     * There can however be no guarantees made in terms of integrity of the read data should the memory be modified concurrently.
     *
     *
     * This method can be used to read zero terminated strings from memory.
     *
     * @param len for optimal performance a value <= 512 is recommended.
     * @param offset this method permits offsets beyond the memory size. The method will just return 0 in those cases.
     */
    int readUntilByte(long offset, byte value, byte[] buffer, int off, int len);

    /**
     * Creates a new NativeBuffer instance that can be used to read this memory as one would read a InputStream
     * Every instance of NativeBuffer is completely independent (other than all of them accessing this memory object)
     * Note: the returned object must not be used by multiple threads at once.
     */
    NativeBuffer stream();
    NativeBuffer stream(long offset);


}

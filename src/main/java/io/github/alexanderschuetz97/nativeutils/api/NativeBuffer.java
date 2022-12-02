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

import java.io.DataInput;
import java.io.DataOutput;

/**
 * Stream like representation of a NativeMemory object.
 * Can be useful in constructing/reading structs when one does not want to keep track of the indices.
 */
public interface NativeBuffer extends DataInput, DataOutput {

    @Override
    void write(int b);

    @Override
    void write(byte[] b);

    @Override
    void write(byte[] b, int off, int len);

    @Override
    void writeBoolean(boolean v);

    @Override
    void writeByte(int v);

    @Override
    void writeShort(int v);

    @Override
    void writeChar(int v);

    @Override
    void writeInt(int v);

    @Override
    void writeLong(long v);

    @Override
    void writeFloat(float v);

    @Override
    void writeDouble(double v);

    @Override
    void writeBytes(String s);

    @Override
    void writeChars(String s);

    @Override
    void writeUTF(String s);

    @Override
    void readFully(byte[] b);

    @Override
    void readFully(byte[] b, int off, int len);

    @Override
    int skipBytes(int n);

    @Override
    boolean readBoolean();

    @Override
    byte readByte();

    @Override
    int readUnsignedByte();

    @Override
    short readShort();

    @Override
    int readUnsignedShort();

    @Override
    char readChar();

    @Override
    int readInt();

    @Override
    long readLong();

    @Override
    float readFloat();

    @Override
    double readDouble();

    @Override
    String readLine();

    @Override
    String readUTF();

    /**
     * the returned string does not end with the 0 byte.
     */
    String readZeroTerminatedUTF8();

    /**
     * Writes a zero terminated utf8 string.
     * @param str should not contain or end with the '0' byte character.
     */
    void writeZeroTerminatedUTF8(String str);

    /**
     * writes the value 'value' len times.
     */
    void write(byte value, long len);

    /**
     * Returns the memory that this NativeBuffer backs or null if it is not backed by NativeMemory.
     * The memory can be used to access the data in a random access fashion.
     */
    NativeMemory memory();

    /**
     * Returns the offset of this NativeBuffer in its backing NativeMemory.
     * Note: this does not contain the number of bytes written this contains the offset relative to the start of the backing NativeMemory.
     * call {@link #getPosition()} for that.
     *
     * Returns -1 in case a call to {@link #memory()} would return null;
     */
    long getOffset();

    /**
     * Returns the number of bytes written to this native buffer
     */
    long getPosition();

    /**
     * Returns the exact number of bytes that can be read from this NativeBuffer.
     * Returns -1 if this number is not known or cannot be exactly determined.
     */
    long remaining();

    /**
     * Returns the size of backing NativeMemory.
     */
    long capacity();

    /**
     * Returns the offset of this NativeBuffer in its backing NativeMemory that it would have after a call to setPosition(0).
     * Returns -1 if the {@link NativeBuffer} does not support setting positions.
     *
     * This call does not modify any offsets/positions of the NativeBuffer.
     */
    long getStartOffset();

    /**
     * Changes the offset so that getPosition() would return the given number.
     * Returns false if the {@link NativeBuffer} does not support setting positions. In that case the call was a noop.
     */
    boolean setPosition(long position);

    /**
     * Change the offset in the native memory.
     * This resets the position to zero.
     * Returns false if the {@link NativeBuffer} does not support setting positions. In this case the call was a noop.
     */
    boolean setOffset(long offset);
}

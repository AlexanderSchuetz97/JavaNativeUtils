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

package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.NativeBuffer;
import eu.aschuetz.nativeutils.api.NativeMemory;

import java.io.DataInputStream;
import java.nio.charset.StandardCharsets;
import java.util.Objects;

public class MemoryNativeBuffer implements NativeBuffer {

    private final NativeMemory memory;
    private long offset;
    private long startOffset;

    protected MemoryNativeBuffer(NativeMemory memory, long offset) {
        this.memory = Objects.requireNonNull(memory);
        this.startOffset = offset;
        this.offset  = startOffset;
        if (!memory.isValid(offset)) {
            throw new IllegalArgumentException("offset invalid");
        }
    }

    @Override
    public void readFully(byte[] b) {
        memory.read(offset, b);
        offset +=b.length;
    }

    @Override
    public void readFully(byte[] b, int off, int len) {
        memory.read(offset, b, off, len);
        offset +=len;
    }

    @Override
    public int skipBytes(int n) {
        if (n <= 0) {
            return 0;
        }

        long r = memory.remaining(offset);
        if (r < n) {
            offset +=r;
            return (int) r;
        }
        offset +=n;
        return n;
    }

    @Override
    public boolean readBoolean() {
        boolean result = memory.read(offset) != 0;
        offset++;
        return result;
    }

    @Override
    public byte readByte() {
        byte result = memory.read(offset);
        offset++;
        return result;
    }

    @Override
    public int readUnsignedByte() {
        int result = memory.readUnsignedShort(offset);
        offset++;
        return result;
    }

    @Override
    public short readShort() {
        short result = memory.readShort(offset);
        offset +=2;
        return result;
    }

    @Override
    public int readUnsignedShort() {
        int result = memory.readUnsignedShort(offset);
        offset +=2;
        return result;
    }

    @Override
    public char readChar() {
        int result = memory.readUnsignedShort(offset);
        offset +=2;
        return (char) result;
    }

    @Override
    public int readInt() {
        int result = memory.readInt(offset);
        offset +=4;
        return result;
    }

    @Override
    public long readLong() {
        long result = memory.readLong(offset);
        offset +=8;
        return result;
    }

    @Override
    public float readFloat() {
        float result = memory.readFloat(offset);
        offset +=4;
        return result;
    }

    @Override
    public double readDouble() {
        double result = memory.readDouble(offset);
        offset +=8;
        return result;
    }


    private static final byte NL = (byte) '\n';

    private static final byte CR = (byte) '\r';
    @Override
    public String readLine() {
        long rem = memory.remaining(offset);
        if (rem == 0) {
            return null;
        }

        byte[] buf = new byte[rem < 512 ? (int) rem : 512];

        StringBuilder sb = new StringBuilder();
        while(true) {
            int read = memory.readUntilByte(offset, NL, buf, 0, buf.length);
            if (read == 0) {
                //End of memory, and we haven't found the NL yet...
                return sb.toString();
            }
            offset +=read;
            for (int i = 0; i < read; i++) {
                byte cur = buf[i];
                if (cur == CR) {
                    //We ignore CR's as per readLine() javadoc...
                    continue;
                }

                if (cur == NL) {
                    return sb.toString();
                }

                sb.append((char) cur);
            }
        }
    }

    @Override
    public String readUTF() {
        long prePos = offset;
        try {
            return DataInputStream.readUTF(this);
        } catch (Throwable e) {
            offset = prePos;
            if (e instanceof RuntimeException) {
                throw (RuntimeException) e;
            }

            throw new IllegalStateException(e);
        }
    }

    @Override
    public String readZeroTerminatedUTF8() {
        long rem = memory.remaining(offset);
        if (rem == 0) {
            throw new IndexOutOfBoundsException("0 byte not found, reached end of memory");
        }

        byte[] buf = new byte[rem < 512 ? (int) rem : 512];


        ByteArrayBuilder bbuilder = new ByteArrayBuilder(); //Poor man's StringBuilder
        long total = 0;
        while(true) {
            int read = memory.readUntilByte(offset, NL, buf, 0, buf.length);
            if (read == 0) {
                throw new IndexOutOfBoundsException("0 byte not found, reached end of memory");
            }

            total+=read;

            for (int i = 0; i < read; i++) {
                int cur = buf[i] & 0xff;
                if (cur == 0) {
                    offset +=total;
                    return new String(bbuilder.getBuffer(), 0, bbuilder.getCount(), StandardCharsets.UTF_8);
                }

                bbuilder.append(cur);
            }
        }
    }

    @Override
    public void writeZeroTerminatedUTF8(String str) {
        byte[] buf = str.getBytes(StandardCharsets.UTF_8);
        try {
            memory.readLock().lock();
            memory.write(offset, buf);
            memory.writeByte(offset +buf.length, 0);
            offset +=buf.length+1;
        } finally {
            memory.readLock().unlock();
        }
    }

    @Override
    public void write(byte value, long len) {
        memory.set(offset, value, len);
        offset +=len;
    }

    @Override
    public NativeMemory memory() {
        return memory;
    }

    @Override
    public long getOffset() {
        return offset;
    }

    @Override
    public long getPosition() {
        return offset-startOffset;
    }

    @Override
    public long remaining() {
        return memory.remaining(offset);
    }

    @Override
    public long capacity() {
        return memory.size();
    }

    @Override
    public long getStartOffset() {
        return startOffset;
    }

    @Override
    public boolean setPosition(long position) {
        if (!memory.isValid(startOffset+position)) {
            throw memory.isValid() ? new IndexOutOfBoundsException(""+ position) : new NullPointerException();
        }

        offset = startOffset+position;
        return true;

    }

    @Override
    public boolean setOffset(long offset) {
        if (!memory.isValid(offset)) {
            throw memory.isValid() ? new IndexOutOfBoundsException(""+ offset) : new NullPointerException();
        }

        this.offset = offset;
        this.startOffset = offset;
        return true;
    }

    @Override
    public void write(int b) {
        memory.writeByte(offset, (byte) b);
        offset++;
    }

    @Override
    public void write(byte[] b) {
        memory.write(offset, b);
        offset +=b.length;
    }

    @Override
    public void write(byte[] b, int off, int len) {
        memory.write(offset, b, off, len);
        offset +=len;
    }

    @Override
    public void writeBoolean(boolean v) {
        memory.writeByte(offset, v ? 1 : 0);
        offset++;
    }

    @Override
    public void writeByte(int v) {
        memory.writeByte(offset, (byte) v);
        offset++;
    }

    @Override
    public void writeShort(int v) {
        memory.writeShort(offset, v);
        offset +=2;
    }

    @Override
    public void writeChar(int v) {
        memory.writeShort(offset, v);
        offset +=2;
    }

    @Override
    public void writeInt(int v) {
        memory.writeInt(offset, v);
        offset +=4;
    }

    @Override
    public void writeLong(long v) {
        memory.writeLong(offset, v);
        offset +=8;
    }

    @Override
    public void writeFloat(float v) {
        memory.writeFloat(offset, v);
        offset +=4;
    }

    @Override
    public void writeDouble(double v) {
        memory.writeDouble(offset, v);
        offset +=8;
    }

    @Override
    public void writeBytes(String s) {
        byte[] buf = new byte[s.length()];
        for (int i = 0, end = s.length(); i < end; i++) {
            buf[i] = (byte) s.charAt(i);
        }
        
        memory.write(offset, buf);
        offset +=buf.length;
    }

    @Override
    public void writeChars(String s) {
        int idx = 0;
        byte[] buf = new byte[s.length() * 2];
        for (int i = 0, end = s.length(); i < end; i++) {
            char v = s.charAt(i);
            buf[idx++] = (byte) ((v >>> 8) & 0xFF);
            buf[idx++] = (byte) ((v >>> 0) & 0xFF);
        }

        memory.write(offset, buf);
        offset +=buf.length;
    }

    @Override
    public void writeUTF(String str) {
        //No idea why I have to implement this myself...
        //Thanks java for making DataOutputStream#writeUTF package private.
        //I got absolutely no idea why the 0 char needs 2 bytes in this encoding...

        int length = str.length();
        if (length == 0) {
            return;
        }

        memory.readLock().lock();
        try {
            int length3 = length*3;
            byte[] buffer = new byte[Math.max(length+(length3/2), Math.min(length3, 32))];
            int bufIdx = 0;
            long startPosition = offset +2;
            long utfPosition = startPosition;

            for (int i = 0; i < length; i++) {
                //Generally if our string only contains 1 byte utf chars then we never get to this. we got a 33% 'buffer' which should cover most european languages too.
                //Asia+Russia will just have multiple iterations over the buffer since their chars need more than 33% overhead
                if ((buffer.length-bufIdx) < 3) {
                    memory.write(utfPosition, buffer, 0, bufIdx);
                    utfPosition+=bufIdx;
                    bufIdx = 0;
                }

                int currentChar = str.charAt(i);
                if ((currentChar >= 0x0001) && (currentChar <= 0x007f)) {
                    buffer[bufIdx++] = (byte) currentChar;
                    continue;
                }

                if (currentChar <= 0x07ff) {
                    buffer[bufIdx++] = (byte) (0xc0 | ((currentChar >>  6) & 0x1f));
                    buffer[bufIdx++] = (byte) (0x80 | ((currentChar >>  0) & 0x3f));
                    continue;
                }

                buffer[bufIdx++] = (byte) (0xe0 | ((currentChar >> 12) & 0x0f));
                buffer[bufIdx++] = (byte) (0x80 | ((currentChar >>  6) & 0x3f));
                buffer[bufIdx++] = (byte) (0x80 | ((currentChar >>  0) & 0x3f));
            }

            if (bufIdx > 0) {
                memory.write(utfPosition, buffer, 0, bufIdx);
                utfPosition += bufIdx;
            }

            long bytesInUtf8 = utfPosition-startPosition;

            if (bytesInUtf8 > 0xffff) {
                throw new IllegalArgumentException("string too long " + bytesInUtf8);
            }

            memory.writeShort(offset, (int) bytesInUtf8);
            offset +=bytesInUtf8+2;
        } finally {
            memory.readLock().unlock();
        }


    }
}

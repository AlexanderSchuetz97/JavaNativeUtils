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

import java.nio.ByteOrder;

/**
 * Helper/Util class to help parse/create structs from byte arrays.
 * All values are automatically read/parsed in native byte order.
 */
public class StructHelper {

    private static final boolean BIG_ENDIAN = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN;

    public static int byteSwapInt(int swap) {
        return ((swap >>> 0) & 0xFF) << 24 | ((swap >>> 8) & 0xFF) << 16 | ((swap >>> 16) & 0xFF) << 8 | ((swap >>> 24) & 0xFF) << 0;
    }

    public static long byteSwapUInt(long swap) {
        return ((swap >>> 0) & 0xFFL) << 24 | ((swap >>> 8) & 0xFFL) << 16 | ((swap >>> 16) & 0xFFL) << 8 | ((swap >>> 24) & 0xFFL) << 0;
    }

    public static long byteSwapLong(long swap) {
        return  ((swap >>>  0) & 0xFFL) << 56 |
                ((swap >>>  8) & 0xFFL) << 48 |
                ((swap >>> 16) & 0xFFL) << 40 |
                ((swap >>> 24) & 0xFFL) << 32 |
                ((swap >>> 32) & 0xFFL) << 24 |
                ((swap >>> 40) & 0xFFL) << 16 |
                ((swap >>> 48) & 0xFFL) <<  8 |
                ((swap >>> 56) & 0xFFL) <<  0 ;
    }

    public static short byteSwapShort(short swap) {
        int value = ((swap >>>  0) & 0xFF) << 8 |
                    ((swap >>>  8) & 0xFF) << 0 ;

        return (short) value;
    }

    public static int byteSwapUShort(int swap) {
        return  ((swap >>>  0) & 0xFF) << 8 |
                ((swap >>>  8) & 0xFF) << 0 ;
    }

    public static int readInt(byte[] buf, int off) {
        return BIG_ENDIAN ?
                ((buf[off++] & 0xff) << 24) + ((buf[off++] & 0xff) << 16) + ((buf[off++] & 0xff) << 8) + ((buf[off] & 0xff) << 0)
                :
                ((buf[off++] & 0xff) << 0) + ((buf[off++] & 0xff) << 8) + ((buf[off++] & 0xff) << 16) + ((buf[off] & 0xff) << 24);
    }

    public static short readShort(byte[] buf, int off) {
        return (short) readUShort(buf, off);
    }

    public static long readLong(byte[] buf, int off) {
        return BIG_ENDIAN ?
                (((long)(buf[off++] & 0xff)) << 56) + (((long)(buf[off++] & 0xff)) << 48) + (((long)(buf[off++] & 0xff)) << 40) + (((long)(buf[off++] & 0xff)) << 32) + (((long)(buf[off++] & 0xff)) << 24) + (((long)(buf[off++] & 0xff)) << 16) + (((long)(buf[off++] & 0xff)) << 8) + (((long)(buf[off] & 0xff)) << 0)
                :
                (((long)(buf[off++] & 0xff)) << 0) + (((long)(buf[off++] & 0xff)) << 8) + (((long)(buf[off++] & 0xff)) << 16) + (((long)(buf[off++] & 0xff)) << 24) + (((long)(buf[off++] & 0xff)) << 32) + (((long)(buf[off++] & 0xff)) << 40) + (((long)(buf[off++] & 0xff)) << 48) + (((long)(buf[off] & 0xff)) << 56);
    }

    public static float readFloat(byte[] buf, int off) {
        return Float.intBitsToFloat(readInt(buf, off));
    }

    public static double readDouble(byte[] buf, int off) {
        return Double.longBitsToDouble(readLong(buf, off));
    }

    public static int readUShort(byte[] buf, int off) {
        return BIG_ENDIAN ?
                ((buf[off] & 0xff) << 8) + ((buf[off+1] & 0xff) << 0)
                :
                ((buf[off] & 0xff) << 0) + ((buf[off+1] & 0xff) << 8);
    }

    public static long readUInt(byte[] buf, int off) {
        return readInt(buf, off) & 0xffffffffL;
    }

    public static int readUByte(byte[] buf, int off) {
        return buf[off] & 0xff;
    }

    public static byte readByte(byte[] buf, int off) {
        return buf[off];
    }

    public static void writeByte(byte[] buf, int off, byte value) {
        buf[off] = value;
    }

    public static void writeByte(byte[] buf, int off, int value) {
        buf[off] = (byte) value;
    }

    public static void writeShort(byte[] buf, int off, short value) {
        writeShort(buf, off, (int) value);
    }

    public static void writeShort(byte[] buf, int off, int value) {
        if (BIG_ENDIAN) {
            buf[off++] = (byte) (value >>> 8);
            buf[off] = (byte) (value >>> 0);
            return;
        }

        buf[off++] = (byte) (value >>> 0);
        buf[off] = (byte) (value >>> 8);
    }

    public static void writeInt(byte[] buf, int off, int value) {
        if (BIG_ENDIAN) {
            buf[off++] = (byte) (value >>> 24);
            buf[off++] = (byte) (value >>> 16);
            buf[off++] = (byte) (value >>> 8);
            buf[off] = (byte) (value >>> 0);
            return;
        }

        buf[off++] = (byte) (value >>> 0);
        buf[off++] = (byte) (value >>> 8);
        buf[off++] = (byte) (value >>> 16);
        buf[off] = (byte) (value >>> 24);
    }

    public static void writeInt(byte[] buf, int off, long value) {
        writeInt(buf, off, (int) value);
    }

    public static void writeLong(byte[] buf, int off, long value) {
        if (BIG_ENDIAN) {
            buf[off++] = (byte) (value >>> 56);
            buf[off++] = (byte) (value >>> 48);
            buf[off++] = (byte) (value >>> 40);
            buf[off++] = (byte) (value >>> 32);
            buf[off++] = (byte) (value >>> 24);
            buf[off++] = (byte) (value >>> 16);
            buf[off++] = (byte) (value >>> 8);
            buf[off] = (byte) (value >>> 0);
            return;
        }

        buf[off++] = (byte) (value >>> 0);
        buf[off++] = (byte) (value >>> 8);
        buf[off++] = (byte) (value >>> 16);
        buf[off++] = (byte) (value >>> 24);
        buf[off++] = (byte) (value >>> 32);
        buf[off++] = (byte) (value >>> 40);
        buf[off++] = (byte) (value >>> 48);
        buf[off] = (byte) (value >>> 56);
    }

    public static int htonl(int num) {
        if (BIG_ENDIAN) {
            return num;
        }

        return ((num >>> 24)) | ((num >>   8) &   0xFF00) | ((num << 8) & 0xFF0000) | ((num << 24));
    }

    public static int htons(int num) {
        if (BIG_ENDIAN) {
            return num & 0xffff;
        }

        return ((num >> 8) & 0xFF) | ((num << 8) & 0xFF00);
    }

    public static int ntohl(int num) {
        if (BIG_ENDIAN) {
            return num;
        }

        return ((num >>> 24)) | ((num >>   8) &   0xFF00) | ((num << 8) & 0xFF0000) | ((num << 24));
    }

    public static int ntohs(int num) {
        if (BIG_ENDIAN) {
            return num & 0xffff;
        }

        return ((num >> 8) & 0xFF) | ((num << 8) & 0xFF00);
    }

    public static int ntohs(byte[] buf, int off) {
        return ntohs(readUShort(buf, off));
    }

    public static void htons(byte[] buf, int off, int value) {
        writeShort(buf, off, htons(value));
    }

    public static int ntohl(byte[] buf, int off) {
        return ntohs(readInt(buf, off));
    }

    public static void htonl(byte[] buf, int off, int value) {
        writeInt(buf, off, htonl(value));
    }



}
